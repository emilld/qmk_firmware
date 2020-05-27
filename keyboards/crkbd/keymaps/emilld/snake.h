#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include "ssd1306.h"
#include "timer.h"

enum direction {
    NONE,
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

typedef struct snake_node_
{
    vec2_t pos;
    struct snake_node_ * next;
} SnakeNode;


// typedef struct
// {
//     int dir;
//     SnakePart head;
// } SnakeHead;

uint16_t snake_key;
bool snake_key_pressed;
uint16_t last_time;

SnakeNode * snake_head;

enum direction currentDirection; // in global space

void snake_init(void);
void snake_clear(void);
void snake_pop_back(void);
void snake_push_front(vec2_t pos);
int snake_update(void);
int snake_frame(struct CharacterMatrix *matrix);
void snake_set_direction(uint16_t keycode);
vec2_t snake_move(void);
bool snake_found_food(void);

vec2_t * food;

// vec2_t get_direction_vec(enum direction);

#endif