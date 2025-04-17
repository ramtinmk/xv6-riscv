#include "types.h"
#include "riscv.h"
#include "defs.h"       // Provides printf, panic, spinlock functions (acquire/release/initlock)
#include "spinlock.h"   // Provides struct spinlock definition
#include "custom_logger.h"

// --- Global Variables ---

// Lock to ensure log messages don't interleave when called from multiple cores
// or interrupt handlers concurrently.
struct spinlock log_lock;

// Current logging threshold. Messages with a level numerically
// higher (less important) than this will be ignored.
// Example: Set to LOG_LEVEL_WARNING (2) to only see errors and warnings.
// Set to LOG_LEVEL_INFO (3) to see everything.
// Note: You might want to make this configurable, e.g., via kernel cmdline args.
int kernel_log_level = LOG_LEVEL_INFO; // Default: log everything up to INFO

// --- Initialization ---


// --- Logging Function ---

// Logs a message to the console if its level is at or below
// the current kernel_log_level threshold.
// Ensures atomicity of the entire log line using a spinlock.
void
log_message(int level, const char *message)
{
  // 1. Check if this message level should be logged based on the global setting
  if (level > kernel_log_level) {
    return; // Ignore messages above the current threshold
  }

  // 2. Acquire the lock to prevent interleaved output from different CPUs/processes
  //    acquire() also disables interrupts on the current core.
  acquire(&log_lock);

  // 3. Print the level prefix
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

  // 4. Print the actual message followed by a newline
  //    Using printf ensures output goes to the console via consoleputc.
  printf("%s\n", message);

  // 5. Release the lock, re-enabling interrupts if they were enabled before acquire.
  release(&log_lock);
}