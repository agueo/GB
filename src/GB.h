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

#include "cpu.h"
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
typedef struct reg_ {
    uint8_t A, F, B, C, D, E, H, L;
    uint16_t SP, PC;
} registers_t;

typedef struct flags_ {
    uint8_t Z;
    uint8_t N;
    uint8_t H;
    uint8_t C;

    bool HALT;
} flags_t;

typedef struct gb_ {
    const char *kName_;
    const char *kVersion_;

    /* Memory - 64 KB addr space*/
    uint8_t memory[MEM_SIZE];

    /* 10 Registers */
    registers_t *reg;
    flags_t *flags;

    /* PPU, APU, MMU */

    /* function callbacks */
    void (* reset) (void);
    void (* read)  (void);
    void (* write) (void);
    void (* run)   (unsigned);

} gb_t;

/* Global GB object */
extern gb_t *gb;

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
