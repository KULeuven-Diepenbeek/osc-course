To be able to use "#include "mbed_memory_status.h"

you need to:
* mbed add https://github.com/nuket/mbed-memory-status.git mbed-memory-status
* put in mbed_app.json:
  "macros": [
    "DEBUG_ISR_STACK_USAGE=1", 
    "MBED_HEAP_STATS_ENABLED=1", 
    "MBED_STACK_STATS_ENABLED=1"
  ]