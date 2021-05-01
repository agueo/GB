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

#include "GB.h"
#include "cpu.h"

/* Fetch */
/* Decode */
/* Execute */
unsigned cpu_decode_op(void)
{
    uint8_t *op = mmu_read(gb_ctx->reg->PC);
    printf("%s\n", opcodes[0].disassembly);

    return 0;
}

unsigned opcode_nop(void *reg, uint16_t value) {

    return 4;
}

unsigned opcode_ld_reg16_u16(void *reg, uint16_t value);
unsigned opcode_ld_mem_u16(void *reg, uint16_t);
unsigned opcode_add_u16(void * reg, uint16_t value);
unsigned opcode_sub_u16(void * reg, uint16_t value);
unsigned opcode_and(void *reg, uint16_t value);
unsigned opcode_or(void *reg, uint16_t value);
unsigned opcode_xor(void *reg, uint16_t value);
unsigned opcode_inc_u16(void * reg, uint16_t value);
unsigned opcode_dec_u16(void * reg, uint16_t value);

