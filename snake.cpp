// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.

#include "snake.h"

void snake_init (Snake * s)
{
    s->head_x = 5;
    s->head_y = 5;
    s->head_px = 0;
    s->head_py = 0;
    
    s->length = 3;
    
    s->locations[0].x = 5;
    s->locations[0].y = 5;
    s->locations[1].x = 4;
    s->locations[1].y = 5; 
    s->locations[2].x = 3;
    s->locations[2].y = 5;
    
    s->score = 0;
}
