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
#include "mmu.h"

/* Memory Map */
/* 0000 - 3FFF 16KB ROM bank 00
 * 4000 - 7FFF 16KB ROM bank 01-NN
 * 8000 - 9FFF  8KB Video RAM
 * A000 - BFFF  8KB External RAM
 * C000 - CFFF  4KB Work RAM bank 0
 * D000 - DFFF  4KB Work RAM bank 1-N
 * E000 - FDFF Mirror of C000 - DDFF - USE PROHIBITED
 * FE00 - FE9F Sprite attribute table (OAM)
 * FEA0 - FEFF Not Usable
 * FF00 - FF7F I/O Registers
 * FF80 - FFFE High RAM
 * FFFF - FFFF Interrupts Enable Register (IE)
 */

uint8_t * mmu_read(uint16_t addr)
{
    return &gb_ctx->memory[addr];
}

/* mmu_write
 *
 * \params u16 addr, u8 data
 * write data to memory location addr if possible
 */
void mmu_write(uint16_t addr, uint8_t data)
{
    /* Go to memory location, do a write if possible */
    gb_ctx->memory[addr] = data;
}
