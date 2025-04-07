#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

int windowWidth = 1366;
int windowHeight = 768;

void myInit(void){
	glClearColor(0.0,0.0,0.0,0.0);
	glColor3f(1.0f,0.0f,0.0f);
	glPointSize(3.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (windowWidth > windowHeight) {
        glOrtho(-windowWidth / 2.0, windowWidth / 2.0, -windowHeight / 2.0, windowHeight / 2.0, -1.0, 1.0);
    } else {
        glOrtho(-windowWidth / 2.0, windowWidth / 2.0, -windowWidth / 2.0, windowWidth / 2.0, -1.0, 1.0);
    }
}

void myReshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, w, h);
    myInit();
    glutPostRedisplay();
}

void myDisplay(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2i(-1000, 0);
    glVertex2i(1000, 0);
    glVertex2i(0, -500);
    glVertex2i(0, 500);
    glEnd();
    glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	int cx,cy,r;
	printf("Enter the center points and radius :- ");
	scanf("%d %d %d",&cx,&cy,&r);
	int x=0,y=-r,p=-r;
	while (x<=-y){
		if (p>0){
			y++;
			p+=2*y;
		}
		p+=2*x+1;
		glVertex2i(cx+x,cy+y);
		glVertex2i(cx-x,cy+y);
		glVertex2i(cx+x,cy-y);
		glVertex2i(cx-x,cy-y);
		glVertex2i(cx+y,cy+x);
		glVertex2i(cx-y,cy+x);
		glVertex2i(cx+y,cy-x);
		glVertex2i(cx-y,cy-x);
		x++;
	}
    glEnd();
	glFlush();
}


void main(int argc, char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1366, 768);
	glutInitWindowPosition(-500,-500);
	glutCreateWindow("Middle Point Circle Theorem");
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	myInit();
	glutMainLoop();
}