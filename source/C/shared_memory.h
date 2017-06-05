/*
 * shared_memory.h
 *
 *  Created on: Dec 9, 2016
 *      Author: Administrator
 */

#ifndef SHARED_MEMORY_H_
#define SHARED_MEMORY_H_

void printWithError(const char *prefix, int occurred, int err);
void printWithStatus(const char *prefix, int occurred);
int openSharedMemory(char *name, void *p);
int checkVersions(struct dcaf_version *info);
void waitForDCAF();
int setCpuParams(int cpuCore, int priority);
void addTimes(struct timespec *tp1, struct timespec *tp2);
double timeDiff(struct timespec *startTp, struct timespec *finishTp);
void loopPeriodSec(double *period, struct timespec *current, struct timespec *previous);
void printAnalog(char *prefix, char* suffix, int numChannels, double *values);
void printDigital(char *prefix, int numChannels, uint8_t *values);
void printAnalogColumn(char *prefix, char* suffix, int numChannels, double *values);
void printDigitalColumn(char *prefix, int numChannels, uint8_t *values);

#endif /* SHARED_MEMORY_H_ */
