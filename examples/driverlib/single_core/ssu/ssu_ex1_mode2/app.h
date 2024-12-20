#ifndef APP_H_
#define APP_H_

#include "bitfield_structs.h"
#include "board.h"
#include "device.h"
#include "ssu_config.h"
#include "ssu.h"

// Function prototypes
void systemInit(void);

void execDMATask(void) __attribute__((c29_protected_call));
void commTask(void) __attribute__((c29_protected_call));
void Interrupt_SSU_Init(void);

#endif
