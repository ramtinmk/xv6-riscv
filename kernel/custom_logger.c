#include "types.h"
#include "riscv.h"
#include "defs.h"       // Provides printf, panic, spinlock functions (acquire/release/initlock)
#include "spinlock.h"   // Provides struct spinlock definition
#include "custom_logger.h"

// --- Global Variables ---

// Lock to ensure log messages don't interleave when called from multiple cores
// or interrupt handlers concurrently.
struct spinlock log_lock;


int kernel_log_level = LOG_LEVEL_INFO; // Default: log everything up to INFO

// --- Initialization ---



void
log_message(int level, const char *message)
{
  
  if (level > kernel_log_level) {
    return; 
  }

  // Acquire the lock to prevent interleaved output from different CPUs/processes
  //    acquire() also disables interrupts on the current core.
  acquire(&log_lock);

  //  Print the level prefix
  switch (level) {
    case LOG_LEVEL_ERROR:
      printf("ERROR: ");
      break;
    case LOG_LEVEL_WARNING:
      printf("WARNING: ");
      break;
    case LOG_LEVEL_INFO:
      printf("INFO: ");
      break;
    default:
      // Handle unknown levels gracefully, maybe just print the number
      printf("LOG(%d): ", level);
      break;
  }

  
  printf("%s\n", message);

  
  release(&log_lock);
}