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

#include <stdlib.h>
#include <string.h>

#include "libretro.h"
#include "../GB.h"

/*
 * Constants and externs
 */
extern gb_t *gb_ctx;


/* 
 * Callbacks
 */
static retro_log_printf_t log_cb;
static retro_video_refresh_t video_cb;
static retro_input_poll_t input_poll_cb;
static retro_input_state_t input_state_cb;
static retro_environment_t environ_cb;
static retro_audio_sample_t audio_cb;
// static retro_audio_sample_batch_t audio_batch_cb;

unsigned retro_api_version(void) { return RETRO_API_VERSION; }

/* TODO - custom vars? */
/* 
 * static void update_variables(void);
 */

/*
 * Cheats
 */
void retro_cheat_reset(void) {}
void retro_cheat_set(unsigned index, bool enabled, const char *code) {}

/*
 * Tell libretro about this core
 */
void retro_get_system_info(struct retro_system_info *info)
{
    if(info == NULL) {
        return;
    }

    memset(info, 0, sizeof(*info));
    /* TODO update this to use the info from GB.c */
    info->library_name = EMU_NAME;
    info->library_version = EMU_VERSION;
    info->need_fullpath = false;
    info->valid_extensions = "gb|gbc";
    info->block_extract = false;
}

/*
 * Tell libretro about the AV system; The fps, sample rate,
 * and resolution of the display
 */
void retro_get_system_av_info(struct retro_system_av_info *info)
{
    if(info == NULL) {
        return;
    }
    int pixel_format = RETRO_PIXEL_FORMAT_RGB565;
    memset(info, 0, sizeof(*info));
    info -> timing.fps                  = FPS;
    info -> timing.sample_rate          = SAMPLE_RATE;
    info -> geometry.base_width         = SCREEN_WIDTH;
    info -> geometry.base_height        = SCREEN_HEIGHT;
    info -> geometry.max_width          = SCREEN_WIDTH;
    info -> geometry.max_height         = SCREEN_HEIGHT;
    // info -> geometry.aspect_ratio       = 160.0f / 144.0f;

    environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &pixel_format);
}

/* Load a game */
bool retro_load_game(const struct retro_game_info *info)
{
    if (info == NULL) return true;
    printf("================================\n");
    printf("Retro game info: \n");
    printf("Game: %s\n", info->path);
    printf("Size: %lu\n", info->size);
    printf("================================\n");
    gb_load_rom(info->data, info->size);
    return true;
}

bool retro_load_game_special(unsigned game_type, const struct retro_game_info *info, size_t num_info) { return false; }

/* Unload game */
void retro_unload_game(void) 
{
    gb_unload();
}

unsigned retro_get_region(void) { return RETRO_REGION_PAL; }

/* libretro unused api */
void retro_set_controller_port_device(unsigned port, unsigned device) {}

void *retro_get_memory_data(unsigned id) { return NULL; }
size_t retro_get_memory_size(unsigned id) { return 0; }


/* Serialization methods */
size_t retro_serialize_size(void) { return 0; }
bool retro_serialize(void * data, size_t size) { return false; }
bool retro_unserialize(const void *data, size_t size) { return false; }

/* End of retrolib */
void retro_deinit() {}


/* libretro global setters */
void retro_set_environment(retro_environment_t cb)
{
    environ_cb = cb;
    /* TODO - Look if we need to do anything special here */
    bool no_game = true;
    environ_cb(RETRO_ENVIRONMENT_SET_SUPPORT_NO_GAME, &no_game);
}

void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb) {}
void retro_set_video_refresh(retro_video_refresh_t cb) { video_cb = cb; }
void retro_set_audio_sample(retro_audio_sample_t cb) { audio_cb = cb; }
void retro_set_input_poll(retro_input_poll_t cb) { input_poll_cb = cb; }
void retro_set_input_state(retro_input_state_t cb) { input_state_cb = cb; }

/* TODO - Write these */
void retro_init(void) 
{
    /* Setup some logging */
    struct retro_log_callback log;
    unsigned level = 4;

    if (environ_cb(RETRO_ENVIRONMENT_GET_LOG_INTERFACE, &log)) {
        log_cb = log.log;
    }
    else {
        log_cb = NULL;
    }
    /* give performance level to frontend */
    environ_cb(RETRO_ENVIRONMENT_SET_PERFORMANCE_LEVEL, &level);

    gb_init();

    gb_ctx->reset_cb();
}

void retro_reset(void) {}

/* TODO - update with real video memory */
unsigned short frame_buffer[160*144];
void retro_run(void) 
{
    /* CPU is 4.16MHz at 59.7 fps */
    //gb->run(69681);
    gb_ctx->run_cb(12);

    /* 738 samples per frame */
    for(int i = 0; i < 738; ++i) {
        audio_cb(1, 1);
    }

    video_cb(frame_buffer, 160, 144, sizeof(unsigned short) * 160);
}
