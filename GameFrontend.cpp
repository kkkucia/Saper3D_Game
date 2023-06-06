#include "GameFrontend.h"

using namespace std;

//tryb fullscreen
void GameFrontend::handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double) w / (double) h, 1.0, 200);
    gluLookAt(0.0f, 5.5f, 15.0f,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);
}

//rysowanie pojedynczego sześcianu planszy
void GameFrontend::draw_BlackArea() {
    glBegin(GL_QUADS);
    glColor3f(0.05f, 0.05f, 0.05f);
    glTranslatef(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.50f, 0.0f, 0.0f);
    glVertex3f(1.5f, 0.3f, 0.0f);
    glVertex3f(0.0f, 0.3f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.05f, 0.05f, 0.05f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, -1.5f);
    glVertex3f(0.0f, 0.3f, -1.5f);
    glVertex3f(0.0f, 0.3f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.05f, 0.05f, 0.05f);
    glVertex3f(1.5f, 0.0f, 0.0f);
    glVertex3f(1.5f, 0.0f, -1.5f);
    glVertex3f(1.5f, 0.3f, -1.5f);
    glVertex3f(1.5f, 0.3f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.05f, 0.05f, 0.05f);
    glVertex3f(0.0f, 0.0f, -1.5f);
    glVertex3f(1.50f, 0.0f, -1.5f);
    glVertex3f(1.5f, 0.3f, -1.5f);
    glVertex3f(0.0f, 0.3f, -1.5f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.05f, 0.05f, 0.05f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.50f, 0.0f, 0.0f);
    glVertex3f(1.5f, 0.0f, -1.5f);
    glVertex3f(0.0f, 0.0f, -1.5f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.3f, 0.0f);
    glVertex3f(1.50f, 0.3f, 0.0f);
    glVertex3f(1.5f, 0.3f, -1.5f);
    glVertex3f(0.0f, 0.3f, -1.5f);
    glEnd();

    glLineWidth(4.0f);

    glBegin(GL_LINE_LOOP);
    glColor3f(0.54f, 0.0f, 0.0f);  // Ustawiamy kolor obramowania na biały
    glVertex3f(0.0f, 0.3f, 0.0f);
    glVertex3f(1.50f, 0.3f, 0.0f);
    glVertex3f(1.5f, 0.3f, -1.5f);
    glVertex3f(0.0f, 0.3f, -1.5f);
    glEnd();

}

void GameFrontend::initRendering() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.15, 0.0, 0.45, 1.0f);

    //Ustawienia display list do rysowania sześcianu
    blackArea = glGenLists(1); //Stworzenie miejsca dla display list
    glNewList(blackArea, GL_COMPILE); //Inicjalizacja display listy

    draw_BlackArea(); //Dodanie komand do rysowania w display list
    glEndList(); //Zakończenie display list
}

//rysowanie sceny
void GameFrontend::drawScene() {
    float textPosX = 0.65f;
    float textPosY = 0.45f;
    float textPosZ = -0.65f;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(-angle, 0.0f, 1.0f, 0.0f);
    glTranslatef(-4 * 1.5, 0.0, 4 * 1.5);

    for (int j = 0; j < 8; j += 1) {
        for (int i = 0; i < 8; i += 1) {
            glPushMatrix();
            glTranslatef(i * 1.5, 0.0, -j * 1.5);
            glCallList(blackArea);

            if(matrix[i][j] == "BUM"){
                glColor3f(1.0f, 0.0f, 0.0f);
            }else if(matrix[i][j][1] != '_'){
                glColor3f(0.1f, 0.5f, 0.9f);
            }else{
                glColor3f(0.78f, 0.75f, 0.79f);
            }
            glRasterPos3f(textPosX, textPosY, textPosZ);
            glLineWidth(12.0f);

            for (char c: matrix[i][j]) {

                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c); // Wyświetlamy pojedynczy znak tekstu
            }
            glPopMatrix();


        }
    }

    string text[6] = {"JAK KLIKAC?",
                      "- Gre w sapera znasz ;)",
                      "- Wcisnij na klawiaturze numerki pol opisane na planszy",
                      "- Przykladowo numerek 1_2 odpowiada kolejno wcisnietym przyciskom '1' oraz '2'",
                      "- W dowolnym momencie możesz opuscic rozgrywke klikajac klawisz ECS",
                      "- Nie traf bomby, oczekuj zwyciestwa!"};

    glColor3f(1.0f, 1.0f, 1.0f);  // Ustawiamy kolor napisu na żółty
    float i = 5.6;

    for (string t : text){
        glRasterPos3f(6.0f, i, -6.0f);

        for (char c : t) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c); // Wyświetlamy pojedynczy znak tekstu
        }

        i = i - 0.3;
    }

    if (fail) {
        std::string lostText = "You lost my friend :C  Press ESC";
        glColor3f(1.0f, 1.0f, 0.0f);  // Ustawiamy kolor napisu na żółty
        glRasterPos3f(6.0f, 3.0f, -6.0f);

        for (char c : lostText) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c); // Wyświetlamy pojedynczy znak tekstu
        }
    }

    if (victory) {
        std::string victoryText = "Sweet victory!!! You won nothing :D  Press ESC";
        glColor3f(1.0f, 1.0f, 0.0f);  // Ustawiamy kolor napisu na żółty
        glRasterPos3f(6.0f, 3.0f, -6.0f);

        for (char c : victoryText) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c); // Wyświetlamy pojedynczy znak tekstu
        }
    }

    glutSwapBuffers();
}

//aktualizacja która zmienia kąt i obraca planszę
void GameFrontend::update(int value) {
    angle += 1.0f;
    if (angle > 360) {
        angle -= 360;
    }
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}


//obsługa przycisku
void GameFrontend::handleKeypress(unsigned char key, int x, int y) {

    //jeśli esc to wychodzi z programu
    switch (key) {
        case ESC_KEY:
            exit(0);
    }

    //obsługa dwóch kliknięć pod rząd, zapisywany jest obecny stan przycisku który został wcześniej wciśnięty
    if(key >= START_BUTT_NUM and key <= END_BUTT_NUM and !victory and !fail){
        if (rowChosen == -1) {
            rowChosen = key - START_BUTT_NUM;
        } else {
            columnChosen = key - START_BUTT_NUM;

            board.uncover(rowChosen, columnChosen);

            rowChosen = -1;
            columnChosen = -1;
        }
    }
}

//inicjalizacja
void GameFrontend::run() {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(SIZE, SIZE);

    glutCreateWindow("Saper");
    initRendering();
    glutFullScreen();

    glutDisplayFunc(drawScene);

    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);
    glutTimerFunc(TIME_STEP, update, 0);

    glutMainLoop();
}

