
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "ships.h"
#include "comm.h"
#include "db.h"
#include "graph.h"
#include "interp.h"
#include "objmisc.h"
#include "prototypes.h"
#include "ship_ai.h"
#include "spells.h"
#include "structs.h"
#include "utils.h"
#include "events.h"
#include <math.h>

int read_cargo()
{
  FILE    *f = NULL;
  int      i, j;

  f = fopen("Ships/CargoData", "r");
  if (!f)
  {
    return FALSE;
  }
  for (i = 0; i < MAXCARGO; i++)
  {
    for (j = 0; j < MAXCARGO; j++)
    {
      fscanf(f, "%f %f %f %f\n", &shipcargo[i].buy[j], &shipcargo[i].sell[j], &shipcontra[i].buy[j], &shipcontra[i].sell[j]);
    }
  }
  fclose(f);
  return TRUE;
}

int write_cargo()
{
  FILE    *f = NULL;
  int      i, j;

  f = fopen("Ships/CargoData", "w");
  if (!f)
  {
    return FALSE;
  }
  for (i = 0; i < MAXCARGO; i++)
  {
    for (j = 0; j < MAXCARGO; j++)
    {
      fprintf(f, "%d %d %d %d\n", (int) shipcargo[i].buy[j], (int) shipcargo[i].sell[j], (int) shipcontra[i].buy[j], (int) shipcontra[i].sell[j]);
    }
  }
  fclose(f);
  return TRUE;
}



void cargo_activity()
{
  int      i, j;

  for (i = 0; i < MAXCARGO; i++)
  {
    for (j = 0; j < MAXCARGO; j++)
    {
      if (shipcargo[i].buy[j] > MINBUYMOD)
      {
        shipcargo[i].buy[j] = max((float)MINBUYMOD, shipcargo[i].buy[j] - BUYADJUSTAUTO);
      }
      if (shipcontra[i].buy[j] > MINBUYMOD)
      {
        shipcontra[i].buy[j] = max((float)MINBUYMOD, shipcontra[i].buy[j] - BUYADJUSTAUTO);
      }
      if (shipcargo[i].sell[j] < MAXSELLMODAUTO)
      {
        shipcargo[i].sell[j] = MIN((float)MAXSELLMODAUTO, shipcargo[i].sell[j] + SELLADJUSTAUTOINC);
      }
      if (shipcargo[i].sell[j] > MAXSELLMODAUTO)
      {
        shipcargo[i].sell[j] = MAX((float)MAXSELLMODAUTO, shipcargo[i].sell[j] - SELLADJUSTAUTODEC);
      }
      if (shipcontra[i].sell[j] < MAXSELLMODAUTO)
      {
        shipcontra[i].sell[j] = MIN((float)MAXSELLMODAUTO, shipcontra[i].sell[j] + SELLADJUSTAUTOINC);
      }
      if (shipcontra[i].sell[j] > MAXSELLMODAUTO)
      {
        shipcontra[i].sell[j] = MAX((float)MAXSELLMODAUTO, shipcontra[i].sell[j] - SELLADJUSTAUTODEC);
      }
    }
  }
}

