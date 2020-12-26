/* 
 * Copyright (C) 2020 agueo
 *
 * This file is part of GB emulator
 */

#ifndef CPU_H
#define CPU_H
#include "GB.h"

typedef enum instruction_ {
    NOP,
    UNINPLEMENTED
} INSTRUCTION;

unsigned cpu_decode_op(void);

#endif
