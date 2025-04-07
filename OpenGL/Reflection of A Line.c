#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

int x0, yy, x2, y2;
int xr1, yr1, xr2, yr2;
double ans1, ans2, ans3, ans4;

int windowWidth = 1366;
int windowHeight = 768;

void myInit(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double aspect = (double)windowWidth / windowHeight;
    if (windowWidth >= windowHeight) {
        glOrtho(-windowWidth / 2.0, windowWidth / 2.0, -windowWidth / (2.0 * aspect), windowWidth / (2.0 * aspect), -1.0, 1.0);
    } else {
        glOrtho(-windowHeight * aspect / 2.0, windowHeight * aspect / 2.0, -windowHeight / 2.0, windowHeight / 2.0, -1.0, 1.0);
    }
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
}

void axes() {
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINES);
    glVertex2i(-windowWidth / 2, 0);
    glVertex2i(windowWidth / 2, 0);
    glVertex2i(0, -windowHeight / 2);
    glVertex2i(0, windowHeight / 2);
    glEnd();
}

void take_inp() {
    printf("Enter the line to be reflected\n");
    printf("Point 1 (x0 yy): ");
    scanf("%d %d", &x0, &yy);
    printf("Point 2 (x2 y2): ");
    scanf("%d %d", &x2, &y2);
    printf("Enter the reflection axis line\n");
    printf("Point 1 (xr1 yr1): ");
    scanf("%d %d", &xr1, &yr1);
    printf("Point 2 (xr2 yr2): ");
    scanf("%d %d", &xr2, &yr2);
}

void myReshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, w, h);
    myInit();
}

void plotline(double w, double x, double y, double z, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_LINES);
    glVertex2d(w, x);
    glVertex2d(y, z);
    glEnd();
}

void solve() {
    double tx0 = x0 - xr1;
    double ty0 = yy - yr1;
    double tx2 = x2 - xr1;
    double ty2 = y2 - yr1;
    double txr2 = xr2 - xr1;
    double tyr2 = yr2 - yr1;

    double reflected_tx0, reflected_ty0, reflected_tx2, reflected_ty2;

    if (fabs(txr2) < 1e-9) {
        reflected_tx0 = -tx0;
        reflected_ty0 = ty0;
        reflected_tx2 = -tx2;
        reflected_ty2 = ty2;
    }
    else if (fabs(tyr2) < 1e-9) {
        reflected_tx0 = tx0;
        reflected_ty0 = -ty0;
        reflected_tx2 = tx2;
        reflected_ty2 = -ty2;
    }
    else {
        double m = tyr2 / txr2;
        double m_sq = m * m;
        double d = m_sq + 1.0;

        double R[2][2];
        R[0][0] = (1.0 - m_sq) / d;
        R[0][1] = (2.0 * m) / d;
        R[1][0] = (2.0 * m) / d;
        R[1][1] = (m_sq - 1.0) / d;

        reflected_tx0 = R[0][0] * tx0 + R[1][0] * ty0;
        reflected_ty0 = R[0][1] * tx0 + R[1][1] * ty0;
        reflected_tx2 = R[0][0] * tx2 + R[1][0] * ty2;
        reflected_ty2 = R[0][1] * tx2 + R[1][1] * ty2;
    }

    ans1 = reflected_tx0 + xr1;
    ans2 = reflected_ty0 + yr1;
    ans3 = reflected_tx2 + xr1;
    ans4 = reflected_ty2 + yr1;


    printf("Original Points  : (%d, %d) to (%d, %d)\n", x0, yy, x2, y2);
    printf("Reflection Axis: (%d, %d) to (%d, %d)\n", xr1, yr1, xr2, yr2);
    printf("Reflected Points : (%.2f, %.2f) to (%.2f, %.2f)\n", ans1, ans2, ans3, ans4);
}

void myDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    axes();

    plotline(x0, yy, x2, y2, 1.0f, 0.0f, 0.0f);

    plotline(xr1, yr1, xr2, yr2, 0.0f, 1.0f, 0.0f);

    solve();
    plotline(ans1, ans2, ans3, ans4, 0.0f, 1.0f, 1.0f);

    glFlush();
}

int main(int argc, char** argv) {
    take_inp();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
    glutInitWindowPosition((screenWidth - windowWidth) / 2, (screenHeight - windowHeight) / 2);

    glutCreateWindow("Reflection of Line about an Arbitrary Axis");

    myInit();

    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myReshape);

    glutMainLoop();

    return 0;
}