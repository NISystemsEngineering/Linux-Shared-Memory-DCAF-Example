/*
 * shared_memory.c
 *
 *  Created on: Dec 9, 2016
 *      Author: Administrator
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sched.h>
#include <pthread.h>

#include "dcaf_shared_memory.h"

/***** Print Colors *****/
#define TRED "\x1B[31m"
#define TNORM "\x1B[0m"
#define TGREEN "\x1B[32m"
#define TCYAN "\x1B[36m"

#define MILLION 1000000
#define BILLION 1000000000


void printWithError(const char *prefix, int occurred, int err){
	printf("%s", prefix);

	if(occurred)
		printf("%sFailed with error %d.%s\n", TRED, err, TNORM);
	else
		printf("%sSuccess.%s", TGREEN, TNORM);
}

void printWithStatus(const char *prefix, int occurred){
	printf("%s", prefix);

	if(occurred)
		printf("%sFailed.%s\n", TRED, TNORM);
	else
		printf("%sSuccess.%s", TGREEN, TNORM);
}

void printDots(int count){
	int i = 0;
	for(i = 0; i < count; i++){
		printf(".");
	}
}

int openSharedMemory(char *name, void **p){
	/** Opens and maps a shared memory file.
	 *  By default, files are opened with read & write access and all permissions allowed.
	 */

	int fd, err = 0;

	if(!err){
//		printf("\nOpening shared memory at %s... ", name);
		fd = shm_open(name, O_RDWR, (mode_t) 0777);
		err = fd < 0;
//		printWithStatus("", err);
	}

	if(!err){
//		printf("\nMapping %s shared memory... ", name);
		*p = mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
		err = (*p == (void *) -1);
//		printWithStatus("", err);
//		printf("\nMemory address for map: %s%p%s", TCYAN, *p, TNORM);
	}

	if(!err){
//		printf("\nClosing %s file descriptor... ", name);
		err = close(fd);
//		printWithStatus("", err);
	}

	char printStr[128];
	printStr[0] = '\0';
	strcat(printStr, "Opening shared memory at ");
	strcat(printStr, name);
	printf("%s", printStr);

	if(strlen(printStr) < 70)
		printDots(70 - strlen(printStr));

	printWithStatus("", err);
	printf("\n");

	return err;
}

int setCpuParams(int cpuCore, int priority){
	int err = 0;
	cpu_set_t cpu;
	struct sched_param params;
	char printStr[128], temp[16];

	if(!err){
		CPU_ZERO(&cpu);
		CPU_SET(cpuCore, &cpu);
		err = sched_setaffinity(0, sizeof(cpu_set_t), &cpu);
		printStr[0] = '\0';
		strcat(printStr, "Setting CPU Affinity to CPU");
		sprintf(temp, "%d", cpuCore);
		strcat(printStr, temp);
		printf("%s", printStr);
		if(strlen(printStr) < 70)
				printDots(70 - strlen(printStr));
		printWithStatus("", err);
		printf("\n");
	}

	if(!err){
		params.sched_priority = priority;
		err = pthread_setschedparam(pthread_self(), SCHED_FIFO, &params);

		printStr[0] = '\0';
		strcat(printStr, "Setting thread priority to ");
		sprintf(temp, "%d", priority);
		strcat(printStr, temp);
		printf("%s", printStr);
		if(strlen(printStr) < 70)
				printDots(70 - strlen(printStr));
		printWithStatus("", err);
		printf("\n");
	}

	return err;
}

int checkVersions(struct standard_engine_info *info){
	char printStr[128];
	int diff = 0;

	printStr[0] = '\0';
	strcat(printStr, "Checking version information");
	printf("%s", printStr);
	if(strlen(printStr) < 70)
			printDots(70 - strlen(printStr));

	if(info->rev_major == STANDARD_ENGINE_REV_MAJOR &&
	   info->rev_minor == STANDARD_ENGINE_REV_MINOR){
		diff = 0;
	}
	else{
		diff = 1;
	}

	printWithStatus("", diff);

	printf("\n\nDeployed version: %d.%d\n", info->rev_major, info->rev_minor);
	printf("Compiled version: %d.%d\n\n", STANDARD_ENGINE_REV_MAJOR, STANDARD_ENGINE_REV_MINOR);

	return diff;
}

void waitForDCAF(){
	char printStr[128];
	struct timespec tp_1ms;

	tp_1ms.tv_sec = 0;
	tp_1ms.tv_nsec = 1000000;

	printStr[0] = '\0';
	strcat(printStr, "\nWaiting for DCAF to create shared memory.\n\n");
	printf("%s", printStr);

	// Get path to dcaf_info shared memory and check if file exists. Waits indefinitely.
	char path[100] = "/dev/shm";
	strcat(path, STANDARD_ENGINE_INFO);
	while(access(path, F_OK) != 0){
		clock_nanosleep(CLOCK_MONOTONIC, 0, &tp_1ms, NULL);
	}
}

void addTimes(struct timespec *tp1, struct timespec *tp2){
	tp1->tv_sec += tp2->tv_sec;
	tp1->tv_nsec += tp2->tv_nsec;

	if(tp1->tv_nsec >= BILLION){
		tp1->tv_sec += 1;
		tp1->tv_nsec -= BILLION;
	}
}

// Calculates the difference, in seconds, between two timespecs.
double timeDiff(struct timespec *startTp, struct timespec *finishTp){
	double start = startTp->tv_sec + ((double) startTp->tv_nsec) / BILLION;
	double finish = finishTp->tv_sec + ((double) finishTp->tv_nsec) / BILLION;
	return (finish - start);
}

void loopPeriodSec(double *period, struct timespec *current, struct timespec *previous){
	*period = current->tv_sec - previous->tv_sec;
	*period += ((double)(current->tv_nsec - previous->tv_nsec)) / BILLION;
}

void printAnalog(char *prefix, char* suffix, int numChannels, double *values){
	int i;
	for(i = 0; i < numChannels; i++){
		printf("\r%s%d: %+02.3f%s", prefix, i, values[i], suffix);
	}
}

void printAnalogColumn(char *prefix, char* suffix, int numChannels, double *values){
	int i;
	for(i = 0; i < numChannels; i++){
		printf("%s%d: %+02.4f%s \n", prefix, i, values[i], suffix);
	}
}

void printDigital(char *prefix, int numChannels, uint8_t *values){
	int i;
	for(i = 0; i < numChannels; i++){
		printf("\r%s%d: %i", prefix, i, values[i]);
	}
}

void printDigitalColumn(char *prefix, int numChannels, uint8_t *values){
	int i;
	for(i = 0; i < numChannels; i++){
		printf("%s%d: %i \n", prefix, i, values[i]);
	}
}
