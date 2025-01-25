#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

void myInit(void){
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500.0, 500.0, -500.0, 500.0);
}

void mybres1(int x0, int y0, int x1, int y1){
    int dx = x1 - x0;
    int dy = y1 - y0;
    glVertex2i(x0, y0);
    int dir = 1;
    if (dy < 0) dir = -1;
    dy *= dir;
    if(dx == 0) return;
    int y = y0;
    int p = 2 * dy - dx;
    for (int i = 0; i < dx + 1; i++){
        glVertex2i(x0 + i, y);
        if (p >= 0){
            y += dir;
            p -= 2 * dx;
        }
        p += 2 * dy;
    }
}

void mybres2(int x0, int y0, int x1, int y1){
    int dx = x1 - x0;
    int dy = y1 - y0;
    glVertex2i(x0, y0);
    int dir = 1;
    if (dx < 0) dir = -1;
    dx *= dir;
    if(dy == 0) return;
    int x = x0;
    int p = 2 * dx - dy;
    for (int i = 0; i < dy + 1; i++){
        glVertex2i(x, y0 + i);
        if (p >= 0){
            x += dir;
            p -= 2 * dy;
        }
        p += 2 * dx;
    }
}

void myDisplay(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2i(-500, 0);
    glVertex2i(500, 0);
    glVertex2i(0, 500);
    glVertex2i(0, -500);
    glEnd();
    glColor3f(1.0f, 0.0f, 0.0f);
    int x0, y0, x1, y1;
    printf("Enter the points : x0, y0, x1, y1 -- ");
    scanf("%d %d %d %d", &x0, &y0, &x1, &y1);
    glBegin(GL_POINTS);
    if (abs(y1 - y0) < abs(x1 - x0)){
        if (x0 > x1) mybres1(x1, y1, x0, y0);
        else mybres1(x0, y0, x1, y1);
    } else {
        if (y0 > y1) mybres2(x1, y1, x0, y0);
        else mybres2(x0, y0, x1, y1);
    }
    glEnd();
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1366, 768);
    glutInitWindowPosition(-300, -300);
    glutCreateWindow("Bresenham's Algorithm");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
    return 0;
}