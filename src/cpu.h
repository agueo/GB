/* 
 * Copyright (c) 2020-2021 agueo
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * This file is part of GB emulator
 */

#ifndef CPU_H
#define CPU_H
#include "GB.h"
#include "mmu.h"

/* Helper macros */
#define REG_PC (gb->reg->PC)
#define REG_SP (gb->reg->SP)
#define REG_A (gb->reg->A)
#define REG_B (gb->reg->B)
#define REG_C (gb->reg->C)
#define REG_D (gb->reg->D)
#define REG_E (gb->reg->E)
#define REG_H (gb->reg->H)
#define REG_L (gb->reg->L)
#define u16(h,l) ((h << 8) | l)

#define FLAG_Z (gb->flags->Z)
#define FLAG_N (gb->flags->N)
#define FLAG_H (gb->flags->H)
#define FLAG_C (gb->flags->C)

typedef enum instruction_ {
    NOP,            /* 0x00 NOP */
    LD_BC_u16,      /* 0x01 */
    LD_BC_A,        /* 0x02 ld (BC), A */
    INC_BC,         /* 0x03 inc bc */
    INC_B,          /* 0x04 */
    DEC_B,          /* 0x05 */
    LD_B_u8,        /* 0x06 */
    RLCA,           /* 0x07 RLCA*/
    LD_u16_SP,      /* 0x08 ld (u16), SP */
    ADD_HL_BC,      /* 0x09 */
    LD_A_BC,        /* 0x0A ld A (BC) */
    DEC_BC,         /* 0x0B */
    INC_C,          /* 0x0C */
    DEC_C,          /* 0x0D */
    LD_C_u8,        /* 0x0E */
    RRCA,           /* 0x0F */
    STOP,           /* 0x10 */
    LD_DE_u16,      /* 0x11 */
    LD_DE_A,        /* 0x12 ld (DE), A */
    INC_DE,         /* 0x13 */
    INC_D,          /* 0x14 */
    DEC_D,          /* 0x15 */
    LD_D_u8,        /* 0x16 */
    RLA,            /* 0x17 */
    JR_u8,          /* 0x18 */
    ADD_HL_DE,      /* 0x19 */
    LD_A_DE,        /* 0x1A ld A, (DE) */
    DEC_DE,         /* 0x1B */
    INC_E,          /* 0x1C */
    DEC_E,          /* 0x1D */
    LD_E_u8,        /* 0x1E */
    RRA,            /* 0x1F */
    LD_SP_u16 = 0x31,
    UNINPLEMENTED = 256
} INSTRUCTION;

unsigned cpu_decode_op(void);

/* Common opcode functions */
unsigned opcode_ld_u8(uint8_t *reg, uint8_t value);
unsigned opcode_ld_u16(uint8_t *reg1, uint8_t *reg2, uint8_t valueL, uint8_t valueH);
unsigned opcode_ld16_u16(uint16_t *reg, uint16_t value);
unsigned opcode_ld_mem_u16();
unsigned opcode_add_u8();
unsigned opcode_add_u16();
unsigned opcode_sub_u8();
unsigned opcode_sub_u16();
unsigned opcode_and();
unsigned opcode_or();
unsigned opcode_xor();
unsigned opcode_inc_u8(uint8_t *);
unsigned opcode_inc_u16(uint8_t *, uint8_t *);
unsigned opcode_dec_u8(uint8_t *);
unsigned opcode_dec_u16(uint8_t *, uint8_t *);
#endif
