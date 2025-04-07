#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int windowWidth = 1366;
int windowHeight = 768;

int x0, yy, x2, y2, t1, t2, a;
float s1, s2;
int xb1, yb1, xb2, yb2;

void myInit(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(3.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (windowWidth > windowHeight)
    {
        glOrtho(-windowWidth / 2.0, windowWidth / 2.0, -windowHeight / 2.0, windowHeight / 2.0, -1.0, 1.0);
    }
    else
    {
        glOrtho(-windowWidth / 2.0, windowWidth / 2.0, -windowWidth / 2.0, windowWidth / 2.0, -1.0, 1.0);
    }
}

void axes()
{
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2i(-1000, 0);
    glVertex2i(1000, 0);
    glVertex2i(0, -500);
    glVertex2i(0, 500);
    glEnd();
}

void take_inp()
{
    printf("Enter the points x1,y1 and x2,y2 : ");
    scanf("%d %d %d %d", &x0, &yy, &x2, &y2);
    printf("Enter the scaling factors sx, sy : ");
    scanf("%f %f", &s1, &s2);
    if (s1 < 0.2 || s2 < 0.2 || s1 > 3.0 || s2 > 3.0)
    {
        printf("Please remain in the range {0.2-3.0}.\n");
        exit(0);
    }
    printf("Enter translation amount tx, ty : ");
    scanf("%d %d", &t1, &t2);
    if (t1 < 50 || t2 < 50 || t1 > 150 || t2 > 150)
    {
        printf("Please remain in the range {50-150}.\n");
        exit(0);
    }
    printf("Enter angle of rotation A : ");
    scanf("%d", &a);
    if (a < 10 || a > 80)
    {
        printf("Please remain in the range {10-80}.\n");
        exit(0);
    }
}

void draw_og()
{
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2i(x0, yy);
    glVertex2i(x2, y2);
    glEnd();
}

void scale(int x4, int y4, int x5, int y5)
{
    int mat[2][2] = {s1, 0, 0, s2};
    int inp[2] = {x4, y4};
    int out[2];
    for (int i = 0; i < 2; i++)
    {
        out[i] = inp[i] * mat[i][i];
    }
    int a = out[0], b = out[1];
    int inp2[2] = {x5, y5};
    for (int i = 0; i < 2; i++)
    {
        out[i] = inp2[i] * mat[i][i];
    }
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2i(a, b);
    glVertex2i(out[0], out[1]);
    glEnd();
    xb1 = a;
    yb1 = b;
    xb2 = out[0];
    yb2 = out[1];
}

void translate(int x4, int y4, int x5, int y5)
{
    int mat[2][2] = {t1, t2, t1, t2};
    int inp[2][2] = {x4, y4, x5, y5};
    int out[2][2];
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            out[i][j] = inp[i][j] + mat[i][j];
        }
    }
    glColor3f(0.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2i(out[0][0], out[0][1]);
    glVertex2i(out[1][0], out[1][1]);
    glEnd();
    xb1 = out[0][0];
    yb1 = out[0][1];
    xb2 = out[1][0];
    yb2 = out[1][1];
}

void rotation(int x4, int y4, int x5, int y5)
{
    float rad = a * 3.14 / 180.0f;
    float mat[2][2] = {cos(rad), -sin(rad), sin(rad), cos(rad)};
    float out[2];
    float inp[2] = {x4, y4};
    out[0] = inp[0] * mat[0][0] + inp[1] * mat[0][1];
    out[1] = inp[0] * mat[1][0] + inp[1] * mat[1][1];
    float a1 = out[0], b1 = out[1];
    float inp2[2] = {x5, y5};
    out[0] = inp2[0] * mat[0][0] + inp2[1] * mat[0][1];
    out[1] = inp2[0] * mat[1][0] + inp2[1] * mat[1][1];
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f(a1, b1);
    glVertex2f(out[0], out[1]);
    glEnd();
}

void myReshape(int w, int h)
{
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, w, h);
    myInit();
    glutPostRedisplay();
}

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    axes();
    take_inp();
    draw_og();
    scale(x0, yy, x2, y2);
    translate(xb1, yb1, xb2, yb2);
    rotation(xb1, yb1, xb2, yb2);
    glFlush();
}

void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1366, 768);
    glutInitWindowPosition(-500, -500);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glEnable(GL_BLEND);
    glutCreateWindow("Line niye kichu korchi");
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myReshape);
    myInit();
    glutMainLoop();
}