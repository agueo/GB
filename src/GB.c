/* 
 * Copyright (C) 2020 agueo
 *
 * This file is part of GB emulator
 */

#include "GB.h"

gb_t *gb = NULL;

void gb_reset(void) 
{
    /* Reset the gb memory */
    memset(gb->memory, 0, MEM_SIZE);
}

void gb_run(unsigned cycles) 
{
    unsigned cycle_count = 0;
    while (cycle_count <= cycles) {
        cycle_count += cpu_decode_op();
    }
}

unsigned gb_step()
{
    return cpu_decode_op();
}

void gb_load_rom(const void *data, size_t size) 
{
    memcpy(gb->memory, data, size);
}

void gb_unload(void)
{
    memset(gb->memory, 0, sizeof(gb->memory));
}

void gb_read(void) {}
void gb_write(void) {}

/* Helper function to help generate new gb obj */
gb_t *gb_new(void)
{
    gb_t *retval = (gb_t *) calloc(1, sizeof(gb_t));
    if(retval == NULL) {
        return NULL;
    }

    retval->kName_ = "microboy";
    retval->kVersion_ = "0.0.1";

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

void gb_destroy(void) {}

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