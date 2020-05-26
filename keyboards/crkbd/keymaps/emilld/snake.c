#include "snake.h"

char snake_string[24];

int snake_init(void)
{
    timer_init();
    last_time = timer_read();
    return 0;
}

int  snake_frame(struct CharacterMatrix *matrix)
{
    // matrix_write_ln(matrix, "snake");

    // Initialize the snake head and one body part
    // The snake is essentially a linked list
    static snake_part element = {{(int)DisplayWidth/2., (int)DisplayHeight/2. - 1}, NULL};
    static snake_head head = {{(int)DisplayWidth/2., (int)DisplayHeight/2.}, INIT, &element};

    if (timer_elapsed(last_time) > 500) // if time elapsed is larger than 1s, then do something
    {
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

        last_time = timer_read();  
    }

    matrix_clear(matrix);
    // Test output
    snprintf(snake_string, sizeof(snake_string), "x: %d", head.pos.x);
    matrix_write_ln(matrix, snake_string);    

    snprintf(snake_string, sizeof(snake_string), "y: %d", head.pos.y);
    matrix_write_ln(matrix, snake_string);

    return 1;
}