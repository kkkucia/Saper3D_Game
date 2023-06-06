#ifndef SAPER_GAMEFRONTEND_H
#define SAPER_GAMEFRONTEND_H

#include <iostream>
#include <GL/glut.h>
#include <cstdlib>
#include <string>
#include <chrono>
#include <thread>
#include "globalBoard.h"

#include "board.h"



using namespace std;

#define SIZE 800
#define TIME_STEP 25
#define START_BUTT_NUM 49
#define END_BUTT_NUM 56
#define ESC_KEY 27

static float angle = 0;
static GLuint blackArea;

static int rowChosen = -1;
static int columnChosen = -1;
static Board board = *new Board(8, 8, 10);

class GameFrontend {

public:

    void run();

    static void handleKeypress(unsigned char key, int x, int y);

    static void handleResize(int w, int h);

    void draw_BlackArea();

    void initRendering();

    static void drawScene();

    static void update(int value);

};


#endif //SAPER_GAMEFRONTEND_H
