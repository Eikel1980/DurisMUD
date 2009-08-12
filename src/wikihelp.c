#include "sql.h"
#include "wikihelp.h"
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

void debug( const char *format, ... );

/* strip characters from front and back of string */
string trim(string const& str, char const* sep_chars)
{
  string::size_type const first = str.find_first_not_of(sep_chars);
  return ( first == string::npos ) ? string() : str.substr(first, str.find_last_not_of(sep_chars)-first+1);
}

/* replace a string with another string in a string */
string str_replace(string haystack_, const char* needle_, const char* replace_)
{
  string haystack(haystack_);
  string needle(needle_);
  string replace(replace_);
  string::size_type pos = haystack.find(needle);
  
  if( pos == string::npos )
    return haystack;
  
  haystack.replace( pos, needle.length(), replace );
  return str_replace(haystack, needle_, replace_);
}

/* clean up some of the wiki formatting */
string dewikify(string str_)
{
  string str(str_);
  str = str_replace(str, "[[", "&+c");
  str = str_replace(str, "]]", "&n");
  str = str_replace(str, "'''", "");
  return str;
}

string tolower(string str_)
{
  string str(str_);
#ifndef _OSX_
  transform( str.begin(), str.end(), str.begin(), (int(*)(int))tolower );
#endif
  return str;
}

#ifdef __NO_MYSQL__

string wiki_help(string str)
{
  return string("The help system is temporarily disabled.");  
}

#else

string wiki_help(string str)
{
  string return_str;
  
  // send the default help message
  if( str.length() < 1 )
  {
    return wiki_help_single(string("help"));    
  }

  // first, find the list of help topics that match the search string
  if( !qry("select title from pages where title like '%%%s%%' order by title asc limit %d", str.c_str(), WIKIHELP_RESULTS_LIMIT+1) )
  {
    return string("&+GSorry, but there was an error with the help system.");
  }

  MYSQL_RES *res = mysql_store_result(DB);
  MYSQL_ROW row;

  if( mysql_num_rows(res) < 1 )
  {
    mysql_free_result(res);
    return string("&+GSorry, but there are no help topics that match your search.");    
  }

  // if there is only one that matches, go ahead and display it
  if( mysql_num_rows(res) == 1 )
  {
    row = mysql_fetch_row(res); 
    return_str = row[0];
    mysql_free_result(res);
    return wiki_help_single(return_str);    
  }  
  
  // scan through the results to see if the search string matches one exactly.
  // if so, display that one first and then the rest as "see also" links
  vector<string> matching_topics;

  bool exact_match = false;
  while( row = mysql_fetch_row(res) )
  {
    string match(row[0]);
    if( tolower(match) == tolower(str) )
    {
      exact_match = true;
    }
    else
    {
      matching_topics.push_back(match);
    }
  }
  
  mysql_free_result(res);

  if( exact_match )
  {
    return_str += wiki_help_single(str);    
    return_str += "\n\n&+GThe following help topics also matched your search:\n";
  }
  else
  {
    return_str += "&+GThe following help topics matched your search:\n";
  }
  
  // list the topics
  for( int i = 0; i < matching_topics.size(); i++ )
  {
    return_str += " &+c";
    return_str += matching_topics[i];
    return_str += "\n";
  }
  
  return return_str;  
}

// display a single help topic
string wiki_help_single(string str)
{
  string return_str;
  
  if( !qry("select title, text from pages where title = '%s' limit 1", str.c_str()) )
  {
    return string("&+GSorry, but there was an error with the help system.");
  }

  MYSQL_RES *res = mysql_store_result(DB);
  
  if( mysql_num_rows(res) < 1 )
  {
    mysql_free_result(res);
    return string("&+GHelp topic not found.");
  }
  
  MYSQL_ROW row = mysql_fetch_row(res);
  
  return_str += "&+c";
  return_str += row[0];
  return_str += "\n";
  
  return_str += "&+L=========================================\n";
  
  return_str += dewikify(trim(string(row[1]), " \t\n"));
  
  mysql_free_result(res);
  
  return return_str;
}

#endif

