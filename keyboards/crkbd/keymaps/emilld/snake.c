#include "snake.h"
#include <stdlib.h>

void snake_init(void)
{
    timer_init();
    last_time = timer_read();

    // Initialize the snake head and one body part
    // The snake is essentially a linked list
    // snake_head->pos.x = (int)(DisplayWidth/2.) / 8. - 1;
    // snake_head->pos.y = (int)(DisplayHeight/2.) / 8. - 1;
    snake_head->pos.x = 3;
    snake_head->pos.y = 1;
    snake_head->next = NULL;

    currentDirection = RIGHT;

    // Spawn food
    food->x = 4;
    food->y = 1;
    
    return;
}

void snake_clear(void)
{
    while (snake_head->next != NULL)
    {
        snake_pop_back();
    }
}

void snake_pop_back(void)
{
    SnakeNode * tmp = snake_head;
    SnakeNode * secondToLast = snake_head;

    while (tmp->next != NULL)
    {
        secondToLast = tmp;
        tmp = tmp->next;
    }

    secondToLast->next = NULL; 
    free(tmp);
}

void snake_push_front(vec2_t pos)
{
    SnakeNode * newHead = (SnakeNode*)malloc(sizeof(SnakeNode));
    newHead->next = snake_head;
    newHead->pos.x = pos.x;
    newHead->pos.y = pos.y;
    snake_head = newHead;
}

void snake_set_direction(uint16_t keycode)
{
    // The keycode is a local direction and can be either left or right relative to the direction,
    // the snake is already moving.

    switch (currentDirection)
    {
    case UP:
        if (snake_key == KC_LEFT)
        {
            currentDirection = LEFT;
        }
        else if (snake_key == KC_RIGHT)
        {
            currentDirection = RIGHT;
        }
        break;

    case DOWN:
        if (snake_key == KC_LEFT)
        {
            currentDirection = RIGHT;
        }
        else if (snake_key == KC_RIGHT)
        {
            currentDirection = LEFT;
        }
        break;

    case LEFT:
        if (snake_key == KC_LEFT)
        {
            currentDirection = DOWN;
        }
        else if (snake_key == KC_RIGHT)
        {
            currentDirection = UP;
        }
        break;

    case RIGHT:
        if (snake_key == KC_LEFT)
        {
            currentDirection = UP;
        }
        else if (snake_key == KC_RIGHT)
        {
            currentDirection = DOWN;
        }
        break;
    
    default:
        break;
    }
}

vec2_t snake_move(void)
{ // Moves the snake one step in the currentDirection
    vec2_t move;
    
    switch (currentDirection)
    {
    case UP:
        move.x = snake_head->pos.x;
        move.y = snake_head->pos.y - 1;
        break;

    case RIGHT:
        move.x = snake_head->pos.x + 1;
        move.y = snake_head->pos.y;
        break;

    case DOWN:
        move.x = snake_head->pos.x;
        move.y = snake_head->pos.y + 1;
        break;

    case LEFT:
        move.x = snake_head->pos.x - 1;
        move.y = snake_head->pos.y;
        break;
    
    default:
        move.x = 0;
        move.y = 0;
        break;
    }

    return move;
}

bool snake_found_food(void)
{
    return (snake_head->pos.x == food->x) & (snake_head->pos.y == food->y);
}

int snake_update(void)
{
    if (timer_elapsed(last_time) < 500) // if time elapsed is larger than 500 ms, then do something
    {
        return 0;
    }

    if (snake_key_pressed)
    {
        snake_set_direction(snake_key);
    }

    vec2_t move = snake_move();

    // Add a new head.
    snake_push_front(move);

    // if (snake_found_food())
    // {
    //     food = NULL;
    // }
    // else
    // {
    //     // Delete the tail
    //     snake_pop_back();
    // }
    
   
    last_time = timer_read();

    return 1;
}

int  snake_frame(struct CharacterMatrix *matrix)
{
    snake_update();

    // matrix_clear(matrix);
    // // Test output
    // snprintf(snake_string, sizeof(snake_string), "x: %d", head.pos.x);
    // matrix_write_ln(matrix, snake_string);    

    // snprintf(snake_string, sizeof(snake_string), "y: %d", head.pos.y);
    // matrix_write_ln(matrix, snake_string);

    // matrix_write_char(matrix, 0xFF);

    // Draw the head
    // matrix->display[i][0] = 0x07;

    matrix_clear(matrix);
    
    char snake_string[24];

    // snprintf(snake_string, sizeof(snake_string), "x: %d, y: %d", snake_head->pos.x, snake_head->pos.y);
    // matrix_write_ln(matrix, snake_string);

    // // Updates the snake positions
    // SnakeNode * tmp = snake_head;
    // while (tmp != NULL)
    // {
    //     matrix->display[tmp->pos.y][tmp->pos.x] = 0x2A;
    //     // snprintf(snake_string, sizeof(snake_string), "x: %d, y: %d", tmp->pos.x, tmp->pos.y);
    //     // matrix_write_ln(matrix, snake_string);
    //     tmp = tmp->next;
    // }

    // // draw food
    // matrix->display[food->y][food->x] = 0x02;

    matrix->display[0][0] = 0x02;
    matrix->display[1][1] = 0x02;
    matrix->display[2][2] = 0x02;
    matrix->display[2][3] = 0x02;

    // food->x = 4;
    // food->y = 2;

    matrix->display[food->y][food->x] = 0x03;

    snprintf(snake_string, sizeof(snake_string), "x: %d, y: %d", food->x, food->y);
    matrix_write_ln(matrix, snake_string);
    
    return 1;
}