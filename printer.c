#include "types.h"
#include "stat.h"
#include "pstat.h"
#include "user.h"

int main (int argc, char *argv[])
{

  struct pstat process_stats = { {0}, {0}, {0}, {0} };

  if (settickets(10) < 0) {
    printf(1, "Something went wrong with settickets\n");
    exit();
  }


  if (getpinfo(&process_stats)) {
    printf(1, "Something went wrong with settickets\n");
    exit();
  }
  printf(1, "Success!\n");
  for (int i = 0; i < NPROC; i++) {
    if (process_stats.inuse[i]) {
      printf(1, "pid: %d, tickets: %d, ticks: %d\n", 
          process_stats.pid[i], process_stats.tickets[i], process_stats.ticks[i]);
    }
  }
  exit();
}
