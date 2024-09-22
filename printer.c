#include "types.h"
#include "stat.h"
#include "pstat.h"
#include "user.h"

int main (int argc, char *argv[])
{

  int pid1 = fork();

  if (pid1 == 0) {
    // Child process 1
    //
    //

    int pid2 = fork();
    if (pid2 == 0) {
      int pid3 = fork();
      if (pid3 == 0) {
        // Set tickets and loop forever for child 3
        if (settickets(30) < 0) {
          printf(1, "Something went wrong with settickets\n");
          exit();
        }
        for (;;) {
        }
      } else {
        // Set tickets and loop forever for child 2
        if (settickets(20) < 0) {
          printf(1, "Something went wrong with settickets\n");
          exit();
        }
        for (;;) {
        }

      }
    } else {
      // Set tickets and loop forever for child 1
      if (settickets(10) < 0) {
        printf(1, "Something went wrong with settickets\n");
        exit();
      }
      for (;;) {
      }
    }
  } else {
    int i = 0;
    struct pstat process_stats = { {0}, {0}, {0}, {0} };
    if (settickets(1000) < 0) {
      printf(1, "Something went wrong with settickets\n");
      exit();
    }

    for (;;) {
      i++;
      if (i % 100000000 != 0)
        continue;

      printf(1, "i: %d\n", i);
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
    }
  }
  exit();
}
