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

#ifndef GB_H
#define GB_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "cpu.h"
#include "mmu.h"

/* Other "class" files here */

/* Constants */
#define SCREEN_WIDTH (160)
#define SCREEN_HEIGHT (144)
#define MEM_SIZE (65536)
#define FPS (59.7f)
#define SAMPLE_RATE (44100)
#define EMU_NAME "microboy"
#define EMU_VERSION "0.0.1"

/* GB definition */
typedef struct gb_ {
    const char *kName_;
    const char *kVersion_;

    /* 10 Registers */
    registers_t *reg;
    flags_t *flags;

    /* Memory - 64 KB addr space*/
    /* Might be good to use a sort of struct for this */
    uint8_t memory[MEM_SIZE];

    /* PPU, APU, MMU */

    /* function callbacks */
    void (* reset_cb) (void);
    void (* read_cb)  (void);
    void (* write_cb) (void);
    void (* run_cb)   (unsigned);

} gb_t;

/* Global GB object */
extern gb_t *gb_ctx;

/* Functions */
void gb_init(void);
void gb_reset(void);
void gb_load_rom(const void *, size_t);
void gb_unload(void);
void gb_run(unsigned);
unsigned gb_step(void);


/* creation functions */
gb_t * gb_new(void);
void gb_destroy(void);

#endif
