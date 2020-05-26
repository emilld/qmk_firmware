#pragma once
#include "ssd1306.h"
#include "timer.h"

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
    int dir;
    struct snake_part_ * next;
} SnakePart;

// typedef struct
// {
//     int dir;
//     SnakePart head;
// } SnakeHead;

uint16_t snake_key;
bool snake_key_pressed;
uint16_t last_time;

SnakePart snake_part;
SnakePart snake_head;

int snake_init(void);
int snake_update(void);
int snake_frame(struct CharacterMatrix *matrix);

vec2_t get_direction_vec(enum direction);