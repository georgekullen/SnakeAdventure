//=================================================================
// The main program file.
//
// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================

// Project includes
#include "globals.h"
#include "hardware.h"
#include "map.h"
#include "graphics.h"
#include "snake.h"

#include <math.h>
#include<stdio.h>

#define CITY_HIT_MARGIN 1
#define CITY_UPPER_BOUND (SIZE_Y-(LANDSCAPE_HEIGHT+MAX_BUILDING_HEIGHT))

// Helper function declarations
void playSound(char* wav);

/**
 * The main game state. Must include snake locations and previous locations for
 * drawing to work properly. Other items can be added as needed.
 */

/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possbile return values are defined below.
 */
Snake snake;

// Function prototypes

/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possible return values are defined below.
 */
#define NO_RESULT 0
#define NO_ACTION 0
#define ACTION_BUTTON 1
#define MENU_BUTTON 2
#define GO_LEFT 3
#define GO_RIGHT 4
#define GO_UP 5
#define GO_DOWN 6
#define GAME_OVER 7
#define FULL_DRAW 8
#define BUTTON_THREE 9
// Get Actions from User (push buttons & accelerometer)
// Based on push button and accelerometer inputs, determine which action
// needs to be performed (may be no action).
int get_action(GameInputs inputs)
{
    if(!inputs.b1) {
        return ACTION_BUTTON;
    } else if(!inputs.b2)
        return MENU_BUTTON;
    else if(!inputs.b3)
        return BUTTON_THREE;   
    else if (inputs.ax > 0.4)
        return GO_DOWN;
    else if (inputs.ax < -0.4)
        return GO_UP;
    else if (inputs.ay > 0.4)
        return GO_RIGHT;
    else if (inputs.ay < -0.4)  
        return GO_LEFT;
    else
        return NO_ACTION;
}
/**
 * Update the game state based on the user action. For example, if the user
 * requests GO_UP, then this function should determine if that is possible by
 * consulting the map, and update the snake position accordingly.
 *
 * Return values are defined below. FULL_DRAW indicates that for this frame,
 * draw_game should not optimize drawing and should draw every tile, even if
 * the snake has not moved.
 */
int shield = 0; //shield buff
int shieldp = 0;
int doubleUp = 0; //doubleUp buff
int doubleUpp = 0;
int pointBlocker = 0; //pointBlocker debuff
int pointBlockerp = 0;
int invincibility = 0;
int invincibilityp = 0;
int update_game(int action)
{
    if (snake.length == 49) {
        return GAME_OVER;   
    }
    invincibilityp = invincibility;
    shieldp = shield;
    doubleUpp = doubleUp;
    pointBlockerp = pointBlocker;
    snake.head_py = snake.head_y;
    snake.head_px = snake.head_x;
    if (action == ACTION_BUTTON) {
        if (invincibility == 1) {
            invincibility = 0;
            wait(0.5);
        } else {
            invincibility = 1;
            wait(0.5);
        }
        return 0;   
    }
    int returnCommand = 0;
    MapItem* target;
    if (action == GO_UP || action == GO_DOWN || action == GO_LEFT || action == GO_RIGHT) {
        switch (action) {
            case GO_UP:
                target = get_north(snake.head_x, snake.head_y);
                if (!target || target->walkable != 0) { //checks to make sure target tile exists and is walkable
                    snake.head_y -= 1;
                            
                    returnCommand = 0;
                }
                break;
            case GO_DOWN:
                target = get_south(snake.head_x, snake.head_y);
                if (!target || target->walkable != 0) { //checks to make sure target tile exists and is walkable
                    snake.head_y += 1;
                                                 
                    returnCommand = 0;
                }
                break;
            case GO_LEFT:
                target = get_west(snake.head_x, snake.head_y);
                if (!target || target->walkable != 0) { //checks to make sure target tile exists and is walkable
                    snake.head_x -= 1;
                    
                    returnCommand = 0;
                }
                break;
            case GO_RIGHT:
                target = get_east(snake.head_x, snake.head_y);
                if (!target || target->walkable != 0) { //checks to make sure target tile exists and is walkable
                    snake.head_x += 1;
                           
                    returnCommand = 0;
                }
                break;
            default:
                return 0;
        }
        if (!target || target->walkable != 0) { //only update snake if target was walkable
            //check to see if the snake traversed a walkable item
            if (target->type == POINTBLOCKER) {
                map_erase(snake.head_x, snake.head_y);
                if (pointBlocker == 0) {
                    pointBlocker = 1;   
                }
            } else if (target->type == SHIELD) {
                map_erase(snake.head_x, snake.head_y);
                if (shield == 0) {
                    shield = 1;
                }
            } else if (target->type == MINUSONE) {
                map_erase(snake.head_x, snake.head_y);
                if (doubleUp == 1) {
                    snake.score = snake.score - 2;
                    doubleUp = 0;
                } else {
                    snake.score = snake.score - 1;
                }
            } else if (target->type == DOUBLEUP) {
                map_erase(snake.head_x, snake.head_y);
                if (doubleUp == 0) {
                    doubleUp = 1;    
                }
            } else if (target->type == MUSHROOM) {
                map_erase(snake.head_x, snake.head_y);
                snake.length = snake.length + 1;
            } else if (target->type == GOODIE) {
                map_erase(snake.head_x, snake.head_y);
                playGoodieSound();
                //way more implementation needed here
                if (doubleUp == 1) {
                    snake.score += 2;
                    snake.length = snake.length + 1;
                    doubleUp = 0;
                } else if (pointBlocker == 1) {
                    snake.length = snake.length + 1;
                    pointBlocker = 0;
                } else {
                    snake.score = snake.score + 1;
                    snake.length = snake.length + 1;
                }
            }
            
            //move snake array locations and delete from map
            for (int i = snake.length - 1; i >= 0; i--) {
                map_erase(snake.locations[i].x, snake.locations[i].y);
            }
            
            add_plant(snake.locations[snake.length - 1].x, snake.locations[snake.length - 1].y);
            
            for (int i = snake.length - 1; i > 0; i--) {
                snake.locations[i].x = snake.locations[i - 1].x;
                snake.locations[i].y = snake.locations[i - 1].y;   
            }
            snake.locations[0].x = snake.head_x;
            snake.locations[0].y = snake.head_y;
            
            //add snake back to map
            add_snake_head(snake.locations[0].x, snake.locations[0].y);
            for (int i = 1; i < snake.length - 1; i++) {
                add_snake_body(snake.locations[i].x, snake.locations[i].y);
            }
            add_snake_tail(snake.locations[snake.length - 1].x, snake.locations[snake.length - 1].y);
                      
        } else if (target->walkable == 0) {
            if (shield == 1) {
                shield = 0;   
            } else {
                if (invincibility == 1) {
                    returnCommand = 0;   
                } else {
                    returnCommand = GAME_OVER;
                    draw_snakeDeath(58, 59);
                    wait(0.2);
                    playGameOverSound();
                    wait(1);
                }
            }
        }
    }
    return returnCommand;
}

/**
 * Draw the upper status bar. -print snake coords and score here too
 */
void draw_upper_status()
{
    if (snake.head_px == snake.head_x && snake.head_y == snake.head_py && snake.score == snake.score) {
        uLCD.line(0, 9, 127, 9, GREEN);
        return;
    }
    uLCD.filled_rectangle(0, 0, 127, 8, BLACK); //Erase old status
    char status[30];
    sprintf(status, "Pos:%d,%d Score:%d", snake.head_x, snake.head_y, snake.score); //define new status
    
    uLCD.text_string(status, 0, 0, FONT_5X7, RED);
    
    uLCD.line(0, 9, 127, 9, GREEN);
}

/**
 * Draw the lower status bar.
 */
void draw_lower_status()
{
    if (doubleUp == doubleUpp && pointBlockerp == pointBlocker && shield == shieldp && invincibility == invincibilityp) {
        uLCD.line(0, 118, 127, 118, GREEN);
        return;
    }
    uLCD.filled_rectangle(0, 119, 127, 127, BLACK); //Erase old status
    if (doubleUp == 1) {
        draw_double_up(30, 119);
    }
    if (pointBlocker == 1) {
        draw_pointblocker(15, 119);
    }
    if (shield == 1) {
        draw_shield(0, 119);
    }
    if (invincibility == 1) {
        draw_invincibility(45, 119);  
    }
    uLCD.line(0, 118, 127, 118, GREEN);
}

/**
 * Draw the border for the map.
 */
void draw_border()
{
    uLCD.filled_rectangle(0,     9, 127,  14, WHITE); // Top
    uLCD.filled_rectangle(0,    13,   2, 114, WHITE); // Left
    uLCD.filled_rectangle(0,   114, 127, 117, WHITE); // Bottom
    uLCD.filled_rectangle(124,  14, 127, 117, WHITE); // Right
}

/**
 * Entry point for frame drawing. This should be called once per iteration of
 * the game loop. This draws all tiles on the screen, followed by the status
 * bars. Unless init is nonzero, this function will optimize drawing by only
 * drawing tiles that have changed from the previous frame.
 */
void draw_game(int draw_option)
{
    // Draw game border first
    if(draw_option == FULL_DRAW) 
    {
        draw_border();
        //int u = 58;
        //int v = 56;
        //draw_snake_head(u, v);
        //draw_snake_body(u-11, v);
        //draw_snake_tail(u-22, v);
        //return;
    }
    
    // Iterate over all visible map tiles
    for (int i = -5; i <= 5; i++) { // Iterate over columns of tiles
        for (int j = -4; j <= 4; j++) { // Iterate over one column of tiles
            // Here, we have a given (i,j)

            // Compute the current map (x,y) of this tile
            int x = i + snake.head_x;
            int y = j + snake.head_y;

            // Compute the previous map (px, py) of this tile
            int px = i + snake.head_px;
            int py = j + snake.head_py;

            // Compute u,v coordinates for drawing
            int u = (i+5)*11 + 3;
            int v = (j+4)*11 + 15;

            // Figure out what to draw
            DrawFunc draw = NULL;
            if (x >= 0 && y >= 0 && x < map_width() && y < map_height()) { // Current (i,j) in the map
                MapItem* curr_item = get_here(x, y);
                MapItem* prev_item = get_here(px, py);
                if (draw_option || curr_item != prev_item) { // Only draw if they're different
                    if (curr_item) { // There's something here! Draw it
                        draw = curr_item->draw;
                    } else { // There used to be something, but now there isn't
                        draw = draw_nothing;
                    }
                } else if (curr_item && curr_item->type == CLEAR) {
                    // This is a special case for erasing things like doors.
                    draw = curr_item->draw; // i.e. draw_nothing
                }
            } else if (draw_option) { // If doing a full draw, but we're out of bounds, draw the walls.
                draw = draw_wall;
            }

            // Actually draw the tile
            if (draw) draw(u, v);
        }
    }
    // Draw status bars
    draw_upper_status();
    draw_lower_status();
}

/**
 * Initialize the main world map. Add walls around the edges, interior chambers,
 * and plants in the background so you can see motion.
 */
void init_main_map()
{
    // "Random" plants
    Map* map = set_active_map(0);
    for(int i = map_width() + 3; i < map_area(); i = i +((rand() % ((42 - 32) + 1)) + 32)) {
        add_goodie(i % map_width(), i / map_width());
    }
    pc.printf("plants\r\n");
    
    //random powerups
    //doubleup
    for(int i = map_width() + 3; i < map_area(); i += ((rand() % (85 - 55 + 1)) + 55)) {
        add_double_up(i % map_width(), i / map_width());
    }
    //(rand() % (85 – 55 + 1)) + 55
    //shield
    for(int i = map_width() + 3; i < map_area(); i += ((rand() % (85 - 55 + 1)) + 55)) {
        add_shield(i % map_width(), i / map_width());
    }
    
    //minusone
    for(int i = map_width() + 3; i < map_area(); i += ((rand() % (85 - 55 + 1)) + 55)) {
        add_minus_one(i % map_width(), i / map_width());
    }
    
    //pointblocker
    for(int i = map_width() + 3; i < map_area(); i += ((rand() % (90 - 65 + 1)) + 65)) {
        add_pointblocker(i % map_width(), i / map_width());
    }
    
    //mushroom
    for(int i = map_width() + 3; i < map_area(); i += ((rand() % (85 - 55 + 1)) + 55)) {
        add_mushroom(i % map_width(), i / map_width());
    }

    pc.printf("Adding walls!\r\n");
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
    pc.printf("Walls done!\r\n");
    
    add_snake_head(snake.locations[0].x, snake.locations[0].y);
    add_snake_body(snake.locations[1].x, snake.locations[1].y);
    add_snake_tail(snake.locations[2].x, snake.locations[2].y);
    
    pc.printf("Add extra chamber\r\n");
    add_wall(30, 0, VERTICAL, 10);
    add_wall(30, 10, HORIZONTAL, 10);
    add_wall(39, 0, VERTICAL, 10);
    pc.printf("Added!\r\n");


    // Add stairs to chamber (map 1)
    //add_stairs(15, 5, 1, 5, 5);

//    profile_hashtable();
    print_map();
}

/**
 * Program entry point! This is where it all begins.
 * This function or all the parts of the game. Most of your
 * implementation should be elsewhere - this holds the game loop, and should
 * read like a road map for the rest of the code.
 */
int main()
{
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");
    srand(time(0));
    snake_init(&snake);
    // 0. Initialize the maps -- implement this function:
    maps_init();
    init_main_map();

    // Initialize game state
    set_active_map(0);
    snake.head_x = snake.head_y = 5;
    // Initial drawing
    draw_game(FULL_DRAW);
    // Main game loop
    while(1) {
        // Timer to measure game update speed
        Timer t;
        t.start();

        // 1. Read inputs -- implement this function:
        GameInputs inputs = read_inputs();
        
        // 2. Determine action (move, act, menu, etc.) -- implement this function:
        int action = get_action(inputs);
        
        //Pause loop
        if (action == MENU_BUTTON) {
            wait(0.5);
            draw_pause(100, 119);
            GameInputs inputPause = read_inputs();
            while(!inputPause.b2) {
                wait(0.5);
                inputPause = read_inputs();   
            }
            uLCD.filled_rectangle(100, 119, 127, 127, BLACK);
        }
        
        // 3. Update game -- implement this function:
        int result = update_game(action);
        
        // 3b. Check for game over based on result
        // and if so, handle game over -- implement this.
        if (result == GAME_OVER) {
            uLCD.cls();
            uLCD.text_width(2);
            uLCD.text_height(2);
            uLCD.locate(0,1);
            uLCD.printf("GAME OVER\n");
            uLCD.printf("Nice Job\n");
            uLCD.printf("Score:%d\n", snake.score);
            int u = 58;
            int v = 96;
            draw_snake_head(u, v);
            draw_snake_body(u-11, v);
            draw_snake_body(u-22, v);
            draw_snake_body(u-33, v);
            draw_snake_body(u-44, v);
            draw_snake_body(u-44, v + 11);
            draw_snake_body(u-44, v + 22);
            draw_snake_body(u-33, v + 22);
            draw_snake_body(u-22, v + 22);
            draw_snake_body(u-11, v + 22);
            draw_snake_body(u, v + 22);
            draw_snake_body(u+11, v + 22);
            draw_snake_body(u+22, v + 22);
            draw_snake_body(u+33, v + 22);
            draw_snake_tail(u+44, v + 22);
            while(1);   
        }
                
        // 4. Draw screen -- provided:
        draw_game(result);
        
        // Compute update time
        t.stop();
        int dt = t.read_ms();

        // Display and wait
        // NOTE: Text is 8 pixels tall
        if (dt < 100) wait_ms(100 - dt);
    }
}

// Plays a wavfile
void playSound(char* wav)
{
    
}