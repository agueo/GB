/* 
 * Copyright (C) 2020 agueo
 *
 * This file is part of GB emulator
 */
#include "cpu.h"

unsigned cpu_decode_op()
{
    uint8_t *op = &gb->memory[REG_PC];
    printf("PC: 0x%04x - OP: 0x%02x\n", REG_PC, op[0]);
    if (op[0] == 0xcb) {
        ++op;
        switch (op[0]) {
            default:
            break;
        }
    } else {
        switch (op[0]) {
            /* NOP */
            case NOP:
                REG_PC++;
                break;
            /* Default */
            default:
                printf("Uninplemented op\n");
                break;
        }
    }
    return 0;
}