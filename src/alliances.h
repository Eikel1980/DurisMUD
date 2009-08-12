#ifndef _ALLIANCES_H_
#define _ALLIANCES_H_

#include <vector>
using namespace std;

extern vector<struct alliance_data> alliances;

struct alliance_data {
  int forging_assoc_id;
  int joining_assoc_id;
  int tribute_owed;
};

#define IS_FORGING_ASSOC(alliance, assoc_id) ( alliance && alliance->forging_assoc_id == assoc_id )
#define IS_JOINING_ASSOC(alliance, assoc_id) ( alliance && alliance->joining_assoc_id == assoc_id )

void load_alliances();
void save_alliances();

void do_acc(P_char ch, char *argument, int cmd);
void do_alliance(P_char ch, char *arg, int cmd);

void alliance_forge(P_char ch, char *arg, int cmd);
void alliance_sever(P_char ch, char *arg, int cmd);

void sever_alliance(int assoc_id);

alliance_data *get_alliance(int assoc_id);

void send_to_alliance(char *str, int alliance_id);

bool is_allied_with(int assoc_id1, int assoc_id2);

void sever_revert_sethome(int);

#endif // _ALLIANCES_H_
