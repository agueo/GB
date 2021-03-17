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

gb_t *gb = NULL;

/* Reset
 * Reset the gameboy memory, registers and flags
 */
void gb_reset(void) 
{
    /* Reset the gb memory */
    memset(gb->memory, 0, MEM_SIZE);
    /* Reset Registers & flags */
    memset(gb->flags, 0, sizeof(flags_t));
    memset(gb->reg, 0, sizeof(registers_t));
}

/* gb_run
 * \params: cycles we want to run 
 * iterate through opcodes in memory while current cycle count is less than 
 * cycles given
 */
void gb_run(unsigned cycles) 
{
    unsigned cycle_count = 0;
    while (cycle_count <= cycles) {
        cycle_count += gb_step();
    }
}

/* gb_step
 * step through a single opcode returning the cycles taken
 */
unsigned gb_step()
{
    return cpu_decode_op();
}

/* gb_load_data
 * \params: data buffer, size
 * load the rom data into the memory buffer making sure it is not over size
 */
void gb_load_rom(const void *data, size_t size) 
{
    memcpy(gb->memory, data, size);
}

/* gb_unload
 * clear out the memory
 */
void gb_unload(void)
{
    memset(gb->memory, 0, sizeof(gb->memory));
}

/* TODO Find what this was */
void gb_read(void) {}
void gb_write(void) {}

/* Helper function to help generate new gb obj */
gb_t *gb_new(void)
{
    /* Create new gameboy object */
    gb_t *retval = (gb_t *) calloc(1, sizeof(gb_t));
    if(retval == NULL) {
        return NULL;
    }

    /* Set emulator name and version */
    retval->kName_ = EMU_NAME;
    retval->kVersion_ = EMU_VERSION;

    retval->reg = (registers_t *) calloc(1, sizeof(registers_t));

    if (retval->reg == NULL) {
        free(retval);
        return NULL;
    }

    retval->flags = (flags_t *) calloc(1, sizeof(flags_t));
    if (retval->flags == NULL) {
        free(retval->reg);
        free(retval);
        return NULL;
    }

    return retval;
}

void gb_destroy(void) 
{
    if (gb == NULL) {
        return;
    }
}

void gb_init(void)
{
    /* Make sure GB is not already initialized */
    if(gb != NULL) {
        return;
    }

    gb = gb_new();
    /* set up callbacks */
    if (gb != NULL) {
        gb->reset = &gb_reset;
        gb->run = &gb_run;
    }

    printf("===============================\n");
    printf("%s COPYRIGHT (C) 2020 agueo\n", gb->kName_);
    printf("Version: %s\n\n", gb->kVersion_);
    printf("Initial Register state:\n");
    printf("PC: 0x%04x\nSP: 0x%04x\n", gb->reg->PC, gb->reg->SP);
    printf("AF: 0x%02x%02x\n", gb->reg->A, gb->reg->F);
    printf("BC: 0x%02x%02x\n", gb->reg->B, gb->reg->C);
    printf("DE: 0x%02x%02x\n", gb->reg->D, gb->reg->E);
    printf("HL: 0x%02x%02x\n", gb->reg->H, gb->reg->L);
    printf("Initial Flag state:\n");
    printf("Z: 0x%x\n", gb->flags->Z);
    printf("N: 0x%x\n", gb->flags->N);
    printf("H: 0x%x\n", gb->flags->H);
    printf("C: 0x%x\n", gb->flags->C);
    printf("===============================\n");
}