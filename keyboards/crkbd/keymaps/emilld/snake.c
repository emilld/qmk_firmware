#include "snake.h"

void snake_frame(struct CharacterMatrix *matrix)
{
    matrix_clear(matrix);
    matrix_write_ln(matrix, "snake");
}