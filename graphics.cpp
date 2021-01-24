// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.

#include "graphics.h"

#include "globals.h"

void draw_nothing(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, BLACK);
}

void draw_img(int u, int v, const char* img)
{
    int colors[11*11];
    for (int i = 0; i < 11*11; i++)
    {
        if (img[i] == 'R') colors[i] = RED;
        else if (img[i] == 'Y') colors[i] = 0xFFFF00; // Yellow
        else if (img[i] == 'G') colors[i] = GREEN;
        else if (img[i] == 'B') colors[i] = BLUE;
        else if (img[i] == 'D') colors[i] = 0xD2691E; // "Dirt"
        else if (img[i] == '5') colors[i] = LGREY; // 50% grey
        else if (img[i] == '3') colors[i] = DGREY;
        else colors[i] = BLACK;
    }
    uLCD.BLIT(u, v, 11, 11, colors);
    wait_us(250); // Recovery time!
}

void draw_wall(int u, int v)
{
    char* wallImg = "BBB-BBB-BBBB-BBB-BBB-BBBB-BBB-BBBB-BBB-BBB-BBBB-BBB-BBBB-BBB-BBB-BBBB-BBB-BBBB-BBB-BBB-BBBB-BBB-BBBB-BBB-BBB-BBBB-BBB-BBB";
    draw_img(u, v, wallImg);
    
    
    //uLCD.filled_rectangle(u, v, u+10, v+10, BLACK);
}

void draw_plant(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, BLACK);
}

void draw_goodie(int u, int v)
{
    char* goodieImg = "-----------DDDDDDDDDDD-DDDDDDDDD--YYYYYRRYY---YRRYYYY----YYYYRRY-----YRRYY------YYYRY-------YYR---------Y----------------";
    draw_img(u, v, goodieImg);
    //uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
}

void draw_snake_body(int u, int v)
{
    char* snakeBodyImg = "GGGGGGGGGGGGGGRRGGGRRGGGGGGGGGGGGGRRGGGRRGGGGGGGGGGGGGGGGGRRGGGRRGGGGGGGGGGGGGRRGGGRRGGGGGGGGGGGGGGGGGRRGGGRRGGGGGGGGGGGG";
    draw_img(u, v, snakeBodyImg);
    //uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
}

void draw_snake_head(int u, int v)
{
     //May need to design a snake head sprite
     //Tile still need to be designed on paper
     char* snakeHeadImg = "GGGGGGGGGGGGGGGGGGGGGGGGRRGGGRRGGGGRRGGGRRGGGGRRGGGRRGGGGGGGGGGGGGGGGGGGGGGGGGGRRRRRRRGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG";
     draw_img(u, v, snakeHeadImg);

    //uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
}

void draw_snake_tail(int u, int v)
{
     char* snakeTailImg = "GGGGGGGGGGGGGGGGGGGRRGGGGGGGGGGGGGGGGGGRRGGGGGGGGGGGGGGGGGGGGGGRRGGGGGGGGGGGGGGGGGGRRGGGGGGGGGGGGGGGGGGGGGGRRGGGGGGGGGGGG";
     draw_img(u, v, snakeTailImg);
     //May need to design a snake tail sprite
     //Tile still need to be designed on paper
    //uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
}

void draw_double_up(int u, int v)
{
    char* doubleUpImg = "---------------------------RRRR------RR--RR-----RR---RRR-R-----RR--R-----RR--R-R---RR--------RR--------RRRRRRR-----------";
    draw_img(u,v, doubleUpImg);   
}

void draw_shield(int u, int v)
{
    char* shieldImg = "-----------3333333333335555555553-355555553--355555553---3555553----3555553-----35553-------353---------3----------------";
    draw_img(u,v, shieldImg);   
}

void draw_minus_one(int u, int v)
{
    char* minusOneImg = "-------------------Y--------YYY---------YY---------YY--YYYYY--YY--YYYYY--YY---------YY---------YY-------YYYYYY-----------";
    draw_img(u,v, minusOneImg);   
}

void draw_pointblocker(int u, int v)
{
    char* pointblockerImg = "--------------55555-----5555555---55RR5RR55--55RR5RR55--5555R5555--555R5R555---5RRRRR5----55R5R55-----55555--------------";
    draw_img(u,v, pointblockerImg);   
}

void draw_invincibility(int u, int v)
{
    char* invincibilityImg = "------------RRRRRRRRR--RRRRRRRRR-----RRR--------RRR--------RRR--------RRR--------RRR------RRRRRRRRR--RRRRRRRRR------------";
    draw_img(u,v,invincibilityImg);   
}

void draw_mushroom(int u, int v)
{
    char* mushroomImg = "--------------RRRRR-----RRRR33R---RR33RRRRR--3RRR33RRR-R3RRRRRR33R---DDDDD------DDDDD------DDDDD------DDDDD--------------";
    draw_img(u,v,mushroomImg);   
}

void draw_pause(int u, int v)
{
    char* pauseImg = "-----------------------YYY---YYY--YYY---YYY--YYY---YYY--YYY---YYY--YYY---YYY--YYY---YYY--YYY---YYY-----------------------";
    draw_img(u,v,pauseImg);   
}

void draw_snakeDeath(int u, int v)
{
    char* snakeHeadSmileImg = "-----R----RR----R---R--R---R--R----R-YRY-------YYRYY---RRRRRYRRRRR---YYRYY-----R-YRY-----R---R--R--R----R---R------R----R";
    draw_img(u, v, snakeHeadSmileImg);
}
