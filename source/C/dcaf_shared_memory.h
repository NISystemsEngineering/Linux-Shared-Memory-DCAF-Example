/* This header file defines the names and structures 
 * used by the DCAF Shared Memory module when publishing 
 * to shared memory. 
 */

#include <stdint.h>
#include <semaphore.h>

// Definitions
// Engine version information
#define STANDARD_ENGINE_REV_MAJOR 1
#define STANDARD_ENGINE_REV_MINOR 0
#define STANDARD_ENGINE_REV_FIX 0
#define STANDARD_ENGINE_REV_BUILD 1

// Shared memory filenames
#define STANDARD_ENGINE_VERSION "/standard_engine_version"
#define STANDARD_ENGINE_SYNC "/standard_engine_sync"
#define STANDARD_ENGINE_DOUBLE_INPUT "/standard_engine_input_double"
#define STANDARD_ENGINE_U64_INPUT "/standard_engine_input_u64"
#define STANDARD_ENGINE_U32_INPUT "/standard_engine_input_u32"
#define STANDARD_ENGINE_BOOLEAN_INPUT "/standard_engine_input_boolean"
#define STANDARD_ENGINE_DOUBLE_OUTPUT "/standard_engine_output_double"
#define STANDARD_ENGINE_BOOLEAN_OUTPUT "/standard_engine_output_boolean"

// Structures
struct standard_engine_version {
   uint16_t rev_major;
   uint16_t rev_minor;
   uint16_t rev_fix;
   uint16_t rev_build;
};

struct standard_engine_sync {
   int64_t cycle_start_sec;
   int64_t cycle_start_nsec;
   sem_t start_sem;
   sem_t stop_sem;
};

#define STANDARD_ENGINE_DOUBLE_INPUT_NUMCHANS 8

struct standard_engine_double_input_data {
   double mod2_ai0;
   double mod2_ai1;
   double mod2_ai2;
   double mod2_ai3;
   double _stdeng_duration_inputs;
   double _stdeng_duration_outputs;
   double _stdeng_duration_process;
   double _stdeng_iterstarttime;
};

#define STANDARD_ENGINE_U64_INPUT_NUMCHANS 2

struct standard_engine_u64_input_data {
   uint64_t _stdeng_exectime;
   uint64_t _stdeng_iteratedt;
};

#define STANDARD_ENGINE_U32_INPUT_NUMCHANS 1

struct standard_engine_u32_input_data {
   uint32_t _stdeng_latecount;
};

#define STANDARD_ENGINE_BOOLEAN_INPUT_NUMCHANS 5

struct standard_engine_boolean_input_data {
   uint8_t mod4_di0;
   uint8_t mod4_di1;
   uint8_t mod4_di2;
   uint8_t mod4_di3;
   uint8_t _stdeng_late;
};

#define STANDARD_ENGINE_DOUBLE_OUTPUT_NUMCHANS 4

struct standard_engine_double_output_data {
   double mod1_ao0;
   double mod1_ao1;
   double mod1_ao2;
   double mod1_ao3;
};

#define STANDARD_ENGINE_BOOLEAN_OUTPUT_NUMCHANS 4

struct standard_engine_boolean_output_data {
   uint8_t mod3_do0;
   uint8_t mod3_do1;
   uint8_t mod3_do2;
   uint8_t mod3_do3;
};

