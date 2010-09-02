#ifndef _SHIP_NPC_H_
#define _SHIP_NPC_H_

#include "ship_npc_ai.h"

struct NPCShipSetup
{
    int m_class;
    int level;
    void (*setup)(P_ship, NPC_AI_Type);
};

struct NPCShipCrewData
{
    int level;
    int captain_mob;
    int firstmate_mob;
    /*int quartermaster_mob;
    int gunmaster_mob;
    int helmsman_mob;
    int doctor_mob;
    int lookout_mob;*/
    int spec_mobs[10];
    int inner_grunts[10];
    int outer_grunts[10];
    int treasure_chest;
    int treasure_chest_key;
    int ship_crew_index;
};

P_ship try_load_npc_ship(P_ship target);
P_ship try_load_npc_ship(P_ship target, NPC_AI_Type type, int level, P_char dbg_ch);
P_ship try_load_npc_ship(P_ship target, NPC_AI_Type type, int level, int location, P_char dgb_ch);
P_ship load_npc_ship(int level, NPC_AI_Type type, int speed, int m_class, int room, P_char dgb_ch);
bool try_unload_npc_ship(P_ship ship);
bool load_cyrics_revenge();
extern P_ship cyrics_revenge;


extern NPCShipCrewData npcShipCrewData[];
P_char load_npc_ship_crew_member(P_ship ship, int room_no, int vnum);
bool load_npc_ship_crew(P_ship ship, int crew_size, int crew_level);

int npc_ship_crew_member_func(P_char ch, P_char player, int cmd, char *arg);
int npc_ship_crew_captain_func(P_char ch, P_char player, int cmd, char *arg);
int npc_ship_crew_board_func(P_char ch, P_char player, int cmd, char *arg);

#endif // _SHIP_NPC_H_
