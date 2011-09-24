#include "structs.h"
#include "utils.h"
#include "interp.h"
#include "comm.h"
#include "prototypes.h"

// This is an old proc for Lohrr's eq..
void proc_lohrr( P_obj obj, P_char ch, int cmd, char *argument )
{
   int locwearing;

   // First, verify that it was called properly
   if( !obj || !ch )
      return;

   // Verify object is worn by cy
   if( !OBJ_WORN( obj ) || obj->loc.wearing != ch)
      return;

   for(locwearing = 0;locwearing < MAX_WEAR; locwearing++ )
   {
      if( ch->equipment[locwearing] == obj )
         break;
   }
   // obj is not worn !  This must be a bug if true.
   if( locwearing = MAX_WEAR )
      return;

   switch( locwearing )
   {
      // For his quiver first
      case WEAR_QUIVER:
	// Heal if down more than 10 hps
	if( GET_HIT(ch) < GET_MAX_HIT(ch) - 10 )
	   spell_full_heal( 60, ch, 0, 0, ch, 0);
      break;
   }
}

// It's a percentage chance to make them attack a few extra times.
// It's size dependdent: < medium = 10, medium/large = 6, > large = 4
void dagger_of_wind( P_obj obj, P_char ch, int cmd, char *argument )
{
   int numhits = 0;
   int i = 0;

   // Verify that obj is dagger of wind and being wielded by ch.
   if( cmd != CMD_MELEE_HIT || !ch || !obj || !OBJ_WORN(obj) || obj->loc.wearing != ch )
      return;
   // Verify that ch is in battle with someone.
   if( !IS_FIGHTING(ch) || !ch->specials.fighting )
      return;

   // 50% chance to proc.
   if( number(1,100) > 50 )
   {
       act("You move with a blur of speed!",
          FALSE, ch, obj, 0, TO_CHAR);
       act("$n moves with a blur of speed!",
          FALSE, ch, obj, 0, TO_ROOM);

      // Calculate number of hits based on size.
      if( GET_SIZE(ch) < SIZE_MEDIUM )
         numhits = 10;
      else if( GET_SIZE(ch) == SIZE_MEDIUM || GET_SIZE(ch) == SIZE_LARGE )
         numhits = 6;
      else
         numhits = 4;

      while( i < numhits )
      {
         // Stop hitting if no one to hit.
         if( !ch->specials.fighting )
            break;
         hit(ch, ch->specials.fighting, obj );
         i++;
      }
   }
}
