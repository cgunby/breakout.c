//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"


// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// paddle demensions
#define PWIDTH 80
#define PHEIGHT 10

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);
    
    
        
        
     while(MOUSE_CLICKED)
   {
        GEvent event = getNextEvent(MOUSE_EVENT);
        
        if(event != NULL) 
        {   
            printf("i ran\n\n");
            double velocityX = 2;
            double velocityY = 2;
            if(getEventType(event) == MOUSE_CLICKED)
            {
            while(true)
            {
                move(ball, velocityX, velocityY);
                
                if(getX(ball) + getWidth(ball) >= getWidth(window))
                {
                    velocityX = -velocityX;
                }
                else if(getX(ball) <= 0)
                {
                    velocityX = -velocityX;
                }
                if(getY(ball) + getHeight(ball) >=  getHeight(window))
                {
                    velocityY = -velocityY;
                }
                else if(getY(ball) <= 0)
                {
                    velocityY = -velocityY;
                }
                pause(10);
                }
            }
      
        }
        
    }
    
    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);
    
    while(true)
    {
        GEvent event = getNextEvent(MOUSE_EVENT);
        
        if(event != NULL)
        {
            if(getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event) - getWidth(paddle) / 2;
                double y = 525; 
                setLocation(paddle, x, y);  
            }
        }
    }

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // TODO
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // TODO
    
    
    for(int i = 0, Y = 100; i < ROWS ; i++, Y = Y + 15)
    {
        for(int j = 0, X = 7; j < COLS ; j++, X = X + 39 )
        {
            GRect rect = newGRect(X, Y, 35, 10);
            setFilled(rect, true);
            
            if(i == 0)
                setColor(rect, "#800080");
            if(i == 1)
                setColor(rect, "BLUE");
            if(i == 2)
                setColor(rect, "RED");
            if(i == 3)
                setColor(rect, "ORANGE");
            if(i == 4)
                setColor(rect, "GREEN");                
            add(window, rect);
            
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
    GOval ball = newGOval(190,292,15,15);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // TODO
      GRect rect = newGRect(150, 525, PWIDTH, PHEIGHT);
      setFilled(rect, true);
      setColor(rect, "BLACK");
      add(window, rect);
    return rect;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    return NULL;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
