/*
 * sync.c
 *
 *  Created on: Oct 24, 2016
 *      Author: Administrator
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/mman.h>
#include <semaphore.h>

// Miscellaneous functions defined to clean up this code.
#include "dcaf_shared_memory.h"
#include "shared_memory.h"

#define MILLION 1000000
#define BILLION 1000000000
#define PERIOD_NS 1000000


int main(int argc, char *argv[]){

	// Local Variables.
	void *p;
	int err = 0;
	uint8_t boolean;
	double sync_latency, max_latency;  		// Used to calculate latency between DCAF and this application.
	double dcaf_period;		// Used to track DCAF execution period.
	double voltage, current;

	// Instantiate DCAF data variables.
	struct standard_engine_shm_info *dcaf_info;
	struct standard_engine_sync *dcaf_sync;
	struct standard_engine_double_input_data *analogInput;
	struct standard_engine_double_output_data *analogOutput;
	struct standard_engine_boolean_input_data *digitalInput;
	struct standard_engine_boolean_output_data *digitalOutput;

	// Instantiate timing variables
	struct timespec dcaf_cycle_start_tp;  // Used to store time that current dcaf cycle started.
	struct timespec prev_dcaf_cycle_start_tp;
	struct timespec c_cycle_start_tp;
	struct timespec tp_5ms, tp_10ms;

	tp_5ms.tv_sec = 0;
	tp_5ms.tv_nsec = 5000000;  		// 5ms

	tp_10ms.tv_sec = 0;
	tp_10ms.tv_nsec = 10000000;  	// 10ms

	// Clear terminal.
	printf("\033c");

	// Set main to run on CPU 1 and elevate priority to 99.
	if(setCpuParams(1, 99)) return -1;

	// Wait for DCAF to create shared memory files by checking if they exist.
	waitForDCAF();

	// Open and obtain shared memory pointers for DCAF Engine Info (contains version info).
	if(openSharedMemory(STANDARD_ENGINE_SHM_INFO, &p)) return -1;
	dcaf_info = (struct standard_engine_shm_info*) p;

	// Short sleep to ensure DCAF has time to publish version values.
	clock_nanosleep(CLOCK_MONOTONIC, 0, &tp_5ms, NULL);

	// Check that deployed version matches compiled version.
	if(checkVersions(dcaf_info)) return -1;


	/** Map DCAF data structs to shared memory */

	// Open and obtain shared memory pointers for DCAF Engine Sync
	if(openSharedMemory(STANDARD_ENGINE_SYNC, &p)) return -1;
	dcaf_sync = (struct standard_engine_sync*) p;

	// Open and obtain shared memory pointers for DCAF Engine AI data
	if(openSharedMemory(STANDARD_ENGINE_DOUBLE_INPUT, &p)) return -1;
	analogInput = (struct standard_engine_double_input_data*) p;

	// Open and obtain shared memory pointers for DCAF Engine AO data
	if(openSharedMemory(STANDARD_ENGINE_DOUBLE_OUTPUT, &p)) return -1;
	analogOutput = (struct standard_engine_double_output_data*) p;

	// Open and obtain shared memory pointers for DCAF Engine DI data
	if(openSharedMemory(STANDARD_ENGINE_BOOLEAN_INPUT, &p)) return -1;
	digitalInput = (struct standard_engine_boolean_input_data*) p;

	// Open and obtain shared memory pointers for DCAF Engine DO data
	if(openSharedMemory(STANDARD_ENGINE_BOOLEAN_OUTPUT, &p)) return -1;
	digitalOutput = (struct standard_engine_boolean_output_data*) p;

	printf("\n\n");


	int i = 0;	  		// Loop iterations.
	int numLines; 		// Used for tracking number of lines printed.
	int sem_value = 0;
	max_latency = 0;
	sync_latency = 0;
	dcaf_period = 0;

	while(1){
		// Wait for DCAF to send start signal.
//		err = sem_wait(&(*dcaf_sync).start_sem);
		err = sem_wait(&dcaf_sync->start_sem);

		if(err)
			break;

		// Get wake up time.
		clock_gettime(CLOCK_REALTIME, &c_cycle_start_tp);

		// Get DCAF start time from shared memory.
		prev_dcaf_cycle_start_tp = dcaf_cycle_start_tp;
		dcaf_cycle_start_tp.tv_sec =  (*dcaf_sync).cycle_start_sec;		// Put sec into timespec
		dcaf_cycle_start_tp.tv_nsec = (*dcaf_sync).cycle_start_nsec;	// Put nsec into timespec


		// Skip first few cycles.
		if(i > 3){
			// Calculate latency between DCAF cycle start time and this thread's wake up time.
			sync_latency = timeDiff(&dcaf_cycle_start_tp, &c_cycle_start_tp);  // Get time diff in seconds.
			if(sync_latency > max_latency)
				max_latency = sync_latency;

			// Calculate loop period of DCAF.
			loopPeriodSec(&dcaf_period, &dcaf_cycle_start_tp, &prev_dcaf_cycle_start_tp);

			// Read new inputs from shared memory and do normal execution here.
			// Calculate new output values based on loop time.
			voltage = (dcaf_cycle_start_tp.tv_sec % 20) - 10; // Rotate voltage -10V to +9V in increments of 1V per second.
			voltage += ((double) dcaf_cycle_start_tp.tv_nsec) / BILLION; // Add fractional voltage to integer voltage.

			current = (dcaf_cycle_start_tp.tv_sec % 16) + 4; // Rotate current from 4 to 19
			current += ((double) dcaf_cycle_start_tp.tv_nsec) / BILLION; // Add fractional current
			current /= 1000; // Scale to Amps

			boolean = !boolean; // Toggle every cycle.

			// Write new outputs to shared memory.

			(*analogOutput).mod1_ao0 = voltage;
			(*analogOutput).mod1_ao1 = voltage;
			(*analogOutput).mod1_ao2 = voltage;
			(*analogOutput).mod1_ao3 = voltage;

			(*analogOutput).mod5_ao0 = current;
			(*analogOutput).mod5_ao1 = current;
			(*analogOutput).mod5_ao2 = current;
			(*analogOutput).mod5_ao3 = current;

			(*digitalOutput).mod3_do0 = boolean;
			(*digitalOutput).mod3_do1 = boolean;
			(*digitalOutput).mod3_do2 = boolean;
			(*digitalOutput).mod3_do3 = boolean;
		}

		// Print timing metrics.
		printf("Iterations: %07d             \n", i);
		printf("DCAF Period: %5.0f us        \n", dcaf_period * MILLION);
		printf("Latency:     %5.0f us        \n", sync_latency * MILLION);
		printf("Max latency: %5.0f us        \n", max_latency * MILLION);
		printf("\n");

		// Set numLines
		numLines = 5;

		// Print channel data.
		printAnalogColumn("AI", "V", 4, &(*analogInput).mod2_ai0);
		printAnalogColumn("AI", "A", 4, &(*analogInput).mod6_ai0);
		numLines += 8;
		printf("\n");
		numLines ++;

		/*

		printDigitalColumn("DI", 4, &(*digitalInput).mod4_di0);
		numLines += 4;
		printf("\n");
		numLines ++;

		printAnalogColumn("AO", "V", 4, &(*analogOutput).mod1_ao0);
		printAnalogColumn("AO", "A", 4, &(*analogOutput).mod5_ao0);
		numLines +=8;
		printf("\n");
		numLines ++;

		printDigitalColumn("DO", 4, &(*digitalOutput).mod3_do0);
		numLines +=4;
		printf("\n");
		numLines ++;

		*/

		// Move cursor back up to overwrite previous output.
		printf("\033[%dA", numLines);
		printf("\r");

		// Signal to DCAF that C is done executing on the shared data.
		err = sem_getvalue(&dcaf_sync->stop_sem, &sem_value);
		if(err)
			break;
		if(sem_value == 0)
			err = sem_post(&dcaf_sync->stop_sem);
//		err = sem_post(&(dcaf_sync->stop_sem));
		if(err)
			break;

		i++;
	}

	printf("\nExiting.\n");

	// Short sleep before close.
	clock_nanosleep(CLOCK_MONOTONIC, 0, &tp_10ms, NULL);

	// If we exit loop, go ahead and unmap everything.
	munmap(analogOutput, 4096);
	munmap(analogInput, 4096);
	munmap(digitalOutput, 4096);
	munmap(digitalInput, 4096);
	munmap(dcaf_sync, 4096);
	munmap(dcaf_info, 4096);

	return 0;
}
