#include "snake.h"

int snake_init(void)
{
    timer_init();
    last_time = timer_read();

    // Initialize the snake head and one body part
    // The snake is essentially a linked list
    snake_head.pos.x = (int)DisplayWidth/2.;
    snake_head.pos.y = (int)DisplayHeight/2.;
    snake_head.next = &snake_part;
    snake_head.dir = RIGHT;

    snake_part.pos.x = (int)DisplayWidth/2.;
    snake_part.pos.y = (int)DisplayHeight/2. - 1;
    snake_part.next = NULL;
    snake_part.dir = snake_head.dir;

    return 0;
}

vec2_t get_direction_vec(enum direction dir)
{
    vec2_t out;

    switch (dir)
    {
    case RIGHT:
        out.x = 1;
        out.y = 0;
        break;

    case LEFT:
        out.x = -1;
        out.y = 0;
        break;

    case UP:
        out.x = 0;
        out.y = 1;
        break;

    case DOWN:
        out.x = 0;
        out.y = -1;
        break;
    
    default:
        out.x = 0;
        out.y = 0;
        break;
    }

    return out;
}

int snake_update(void)
{
    if (timer_elapsed(last_time) < 500) // if time elapsed is larger than 1s, then do something
    {
        return 0;
    }

    vec2_t dir;

    if (snake_key_pressed)
    {
        switch (snake_key)
        {
        case KC_LEFT:
            switch (snake_head.dir)
            {
            case LEFT:
                dir.x = 0;
                dir.y = -1;
                break;
            
            case UP:
                dir.x = -1;
                dir.y = 0;
                break;

            case RIGHT:
                dir.x = 0;
                dir.y = 1;
                break;

            case DOWN:
                dir.x = 1;
                dir.y = 0;
                break;

            default:
                dir.x = 0;
                dir.y = 0;
                break;
            }
            break;

        case KC_RIGHT:
            switch (snake_head.dir)
            {
            case LEFT:
                dir.x = 0;
                dir.y = 1;
                break;
            
            case UP:
                dir.x = 1;
                dir.y = 0;
                break;

            case RIGHT:
                dir.x = 0;
                dir.y = -1;
                break;

            case DOWN:
                dir.x = -1;
                dir.y = 0;
                break;

            default:
                dir.x = 0;
                dir.y = 0;
                break;
            }
            break;

        default:
            dir.x = 0;
            dir.y = 0;
            break;
        }
    } 
    else
    {
        return 0;
    }
    

    // Update the positions for all the parts of the snake.
    // Percolate the dir downwards
    SnakePart * tmp = &snake_head;
    vec2_t tmp_dir;
    while (tmp != NULL)
    {
        tmp_dir = get_direction_vec(tmp->dir);

        tmp->pos.x += tmp_dir.x;
        tmp->pos.y += tmp_dir.y;

        // set the next dir to the this
        tmp->next->dir = tmp->dir;
        tmp = tmp->next;
    }


    if ((dir.x == 1) & (dir.y == 0))
    {
        snake_head.dir = RIGHT;
    }
    else if ((dir.x == -1) & (dir.y == 0))
    {
        snake_head.dir = LEFT;
    }
    else if ((dir.x == 0) & (dir.y == 1))
    {
        snake_head.dir = UP;
    }
    else if ((dir.x == 0) & (dir.y == -1))
    {
        snake_head.dir = DOWN;
    }
    else
    {
        snake_head.dir = INIT;
    }

    last_time = timer_read();

    return 1;
}

int  snake_frame(struct CharacterMatrix *matrix)
{
    // matrix_write_ln(matrix, "snake");

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
    // char snake_string[24];

    // Updates the snake positions
    SnakePart * tmp = &snake_head;
    while (tmp != NULL)
    {
        matrix->display[tmp->pos.y / 8][tmp->pos.x / 8] = 0x2A;
        // snprintf(snake_string, sizeof(snake_string), "x: %d, y: %d", tmp->pos.x, tmp->pos.y);
        // matrix_write_ln(matrix, snake_string);
        tmp = tmp->next;
    }
    

    return 1;
}