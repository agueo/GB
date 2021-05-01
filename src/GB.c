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

gb_t *gb_ctx = NULL;

/* Reset
 * Reset the gameboy memory, registers and flags
 */
void gb_reset(void) 
{
    assert(gb_ctx != NULL);

    /* Reset the gb memory */
    memset(gb_ctx->memory, 0, MEM_SIZE);

    /* Reset Registers & flags */
    memset(gb_ctx->reg, 0, sizeof(registers_t));
    memset(gb_ctx->flags, 0, sizeof(flags_t));
}

/* gb_run
 * @param: cycles we want to run 
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
    memcpy(gb_ctx->memory, data, size);
}

/* gb_unload
 * clear out the memory
 */
void gb_unload(void)
{
    memset(gb_ctx->memory, 0, sizeof(gb_ctx->memory));
}

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
    assert(gb_ctx != NULL);
    free(gb_ctx->flags);
    free(gb_ctx->reg);
    free(gb_ctx);
}

void gb_init(void)
{
    /* Make sure GB is not already initialized */
    if(gb_ctx != NULL) {
        return;
    }

    gb_ctx = gb_new();

    if (gb_ctx == NULL) {
        return;
    }

    /* set up callbacks */
    gb_ctx->reset_cb = &gb_reset;
    gb_ctx->run_cb = &gb_run;

    printf("===============================\n");
    printf("%s COPYRIGHT (C) 2020 agueo\n", gb_ctx->kName_);
    printf("Version: %s\n\n", gb_ctx->kVersion_);
    printf("Initial Register state:\n");
    printf("PC: 0x%04x\nSP: 0x%04x\n", gb_ctx->reg->PC, gb_ctx->reg->SP);
    printf("AF: 0x%02x%02x\n", gb_ctx->reg->A, gb_ctx->reg->F);
    printf("BC: 0x%02x%02x\n", gb_ctx->reg->B, gb_ctx->reg->C);
    printf("DE: 0x%02x%02x\n", gb_ctx->reg->D, gb_ctx->reg->E);
    printf("HL: 0x%02x%02x\n", gb_ctx->reg->H, gb_ctx->reg->L);
    printf("Initial Flag state:\n");
    printf("Z: 0x%x\n", Z(gb_ctx->reg->F));
    printf("N: 0x%x\n", N(gb_ctx->reg->F));
    printf("H: 0x%x\n", H(gb_ctx->reg->F));
    printf("C: 0x%x\n", C(gb_ctx->reg->F));
    printf("===============================\n");
}