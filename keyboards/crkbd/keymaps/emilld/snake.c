#include "snake.h"

char snake_string[24];

int snake_init(void)
{
    snake_key_pressed_last = false;
    return 0;
}

int  snake_frame(struct CharacterMatrix *matrix)
{
    matrix_clear(matrix);
    // matrix_write_ln(matrix, "snake");

    // Initialize the snake head and one body part
    // The snake is essentially a linked list
    static snake_part element = {{(int)DisplayWidth/2., (int)DisplayHeight/2. - 1}, NULL};
    static snake_head head = {{(int)DisplayWidth/2., (int)DisplayHeight/2.}, INIT, &element};

    if (snake_key_pressed)
    {
        switch (snake_key)
        {
        case KC_LEFT:
            head.pos.x--;
            head.pos.y++;
            break;

        case KC_RIGHT:
            head.pos.x++;
            head.pos.y--;
            break;

        default:
            break;
        }
    }
    

    // Test output
    snprintf(snake_string, sizeof(snake_string), "x: %d", head.pos.x);
    matrix_write_ln(matrix, snake_string);    

    snprintf(snake_string, sizeof(snake_string), "y: %d", head.pos.y);
    matrix_write_ln(matrix, snake_string);    

    return 1;
}