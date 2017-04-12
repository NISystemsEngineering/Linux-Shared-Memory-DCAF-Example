/* This header file defines the names and structures 
 * used by the DCAF Shared Memory module when publishing 
 * to shared memory. 
 */

#include <stdint.h>
#include <semaphore.h>

// Definitions
// Header revision information
#define STANDARD_ENGINE_SHM_REV_MAJOR 2
#define STANDARD_ENGINE_SHM_REV_MINOR 0

// Shared memory filenames
#define STANDARD_ENGINE_SHM_INFO "/standard_engine_shm_info"
#define STANDARD_ENGINE_SYNC "/standard_engine_sync"
#define STANDARD_ENGINE_DOUBLE_INPUT "/standard_engine_input_double"
#define STANDARD_ENGINE_BOOLEAN_INPUT "/standard_engine_input_boolean"
#define STANDARD_ENGINE_DOUBLE_OUTPUT "/standard_engine_output_double"
#define STANDARD_ENGINE_BOOLEAN_OUTPUT "/standard_engine_output_boolean"

// Structures
struct standard_engine_shm_info {
   uint8_t rev_major;
   uint8_t rev_minor;
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
   double mod6_ai0;
   double mod6_ai1;
   double mod6_ai2;
   double mod6_ai3;
};

#define STANDARD_ENGINE_BOOLEAN_INPUT_NUMCHANS 4

struct standard_engine_boolean_input_data {
   uint8_t mod4_di0;
   uint8_t mod4_di1;
   uint8_t mod4_di2;
   uint8_t mod4_di3;
};

#define STANDARD_ENGINE_DOUBLE_OUTPUT_NUMCHANS 8

struct standard_engine_double_output_data {
   double mod1_ao0;
   double mod1_ao1;
   double mod1_ao2;
   double mod1_ao3;
   double mod5_ao0;
   double mod5_ao1;
   double mod5_ao2;
   double mod5_ao3;
};

#define STANDARD_ENGINE_BOOLEAN_OUTPUT_NUMCHANS 4

struct standard_engine_boolean_output_data {
   uint8_t mod3_do0;
   uint8_t mod3_do1;
   uint8_t mod3_do2;
   uint8_t mod3_do3;
};

