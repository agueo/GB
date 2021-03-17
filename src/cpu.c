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

#include "cpu.h"

unsigned cpu_decode_op()
{
    unsigned cycles = 0;
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
            case NOP:
                REG_PC++;
                cycles = 1;
                break;
            case LD_BC_u16:
                cycles = opcode_ld_u16(&REG_B, &REG_C, op[1], op[2]);
                break;
            case LD_BC_A:
                /* TODO - Need MMU for write ? */
                mmu_write(u16(REG_B, REG_C), REG_A);
                REG_PC++;
                break;
            case INC_BC:
                cycles = opcode_inc_u16(&REG_B, &REG_C);
                break;
            case INC_B:
                cycles = opcode_inc_u8(&REG_B);
                break;
            case DEC_B:
                cycles = opcode_dec_u8(&REG_B);
                break;
            case LD_B_u8:
                cycles = opcode_ld_u8(&REG_B, op[1]);
                break;
            case RLCA:
                /* TODO - find out how this is done */
                REG_PC++;
                break;
            case LD_u16_SP: /* ld (u16), SP*/
                mmu_write(u16(op[2],op[1]), REG_SP & 0xFF);
                mmu_write(u16(op[2],op[1])+1, (REG_SP >> 8) & 0xFF);
                REG_PC += 3;
                break;
            case ADD_HL_BC:
                /* TODO - figure out carry bits */
                break;
            case LD_A_BC:
                REG_A = mmu_read(u16(REG_B, REG_C));
                REG_PC++;
                break;
            case DEC_BC:
                cycles = opcode_dec_u16(&REG_B, &REG_C);
                break;
            case INC_C:
                cycles = opcode_inc_u8(&REG_C);
               break;
            case DEC_C:
                cycles = opcode_dec_u8(&REG_C);
               break;
            case LD_C_u8:
                cycles = opcode_ld_u8(&REG_C, op[1]);
                break;
            case RRCA:
                /* TODO */
                break;
            case STOP:
                /* TODO */
                break;
            case LD_DE_u16:
                cycles = opcode_ld_u16(&REG_D, &REG_E, op[1], op[2]);
                break;
            case LD_DE_A:
                mmu_write(u16(REG_D, REG_E), REG_A);
                REG_PC++;
                break;
            case INC_DE:
                cycles = opcode_inc_u16(&REG_D, &REG_E);
                break;
            case INC_D:
                cycles = opcode_inc_u8(&REG_D);
                break;
            case DEC_D:
                cycles = opcode_dec_u8(&REG_D);
                break;
            case LD_D_u8:
                cycles = opcode_ld_u8(&REG_D, op[1]);
                break;
            case RLA:
                /* TODO */
                break;
            case JR_u8:
                /* TODO Jump code */
                break;
            case ADD_HL_DE:
                break;
            case LD_A_DE:
                REG_A = mmu_read(u16(REG_D, REG_E));
                REG_PC++;
                break;
            case DEC_DE:
                cycles = opcode_dec_u16(&REG_D, &REG_E);
                break;
            case INC_E:
                cycles = opcode_inc_u8(&REG_E);
                break;
            case DEC_E:
                cycles = opcode_dec_u8(&REG_E);
            case LD_E_u8:
                cycles = opcode_ld_u8(&REG_E, op[1]);
                break;
            case RRA:
                /* TODO */
                break;
            case LD_SP_u16: /* 0x31 */
                cycles = opcode_ld16_u16(&REG_SP, u16(op[2], op[1]));
                break;
            /* Default */
            default:
                printf("Uninplemented op\n");
                break;
        }
    }
    return cycles;
}


/* Opcode functions */
unsigned opcode_ld_u8(uint8_t *reg, uint8_t value)
{
    *reg = value;
    REG_PC += 2;
    return 2;
}

unsigned opcode_ld_u16(uint8_t *regH, uint8_t *regL, uint8_t valueL, uint8_t valueH)
{
    *regH = valueH;
    *regL = valueL;
    REG_PC += 3;
    return 3;
}

unsigned opcode_ld16_u16(uint16_t *reg, uint16_t value)
{
    *reg = value;
    REG_PC += 3;
    return 3;
}

unsigned opcode_ld_mem_u16();
unsigned opcode_ld_u16_mem();
unsigned opcode_add_u8();
unsigned opcode_add_u16();
unsigned opcode_sub_u8();
unsigned opcode_sub_u16();
unsigned opcode_and();
unsigned opcode_or();
unsigned opcode_xor();

unsigned opcode_inc_u8(uint8_t *reg)
{
    FLAG_N = 0;
    FLAG_Z = (*reg+1 == 0) ? 1:0;
    /* TODO - Figure out half carry */
    FLAG_H = 0;
    *reg += 1;
    REG_PC++;
    return 1;
}

unsigned opcode_inc_u16(uint8_t *regH, uint8_t *regL)
{
    if ((*regL + 1) % 16 == 0) {
        *regH += 1;
    }
    *regL += 1;
    REG_PC++;
    return 2;
}

unsigned opcode_dec_u8(uint8_t *reg)
{
    FLAG_N = 1;
    FLAG_Z = (*reg - 1 == 0) ? 1:0;
    /* TODO - Figure out half carry */
    FLAG_H = 0;
    *reg -= 1;
    REG_PC++;
    return 1;
}

unsigned opcode_dec_u16(uint8_t *regH, uint8_t *regL)
{
    uint16_t res = u16(*regH, *regL) - 1;
    *regL = res & 0xff;
    *regH = (res >> 8) & 0xff;
    REG_PC++;
    return 2;
}
