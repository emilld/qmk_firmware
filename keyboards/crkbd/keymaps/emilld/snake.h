#pragma once
#include "ssd1306.h"

enum direction {
    INIT,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

typedef struct
{
    int x;
    int y;
} vec2_t;

typedef struct snake_part_
{
    vec2_t pos;
    struct snake_part_ * next;
} snake_part;

typedef struct
{
    vec2_t pos;
    int dir;
    snake_part * next;
} snake_head;

uint16_t snake_key;
bool snake_key_pressed;

int snake_init(void);
int snake_frame(struct CharacterMatrix *matrix);