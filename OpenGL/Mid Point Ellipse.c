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
	int rx,ry,xc,yc;
	printf("Input rx, ry, xc, yc : ");
	scanf("%d %d %d %d",&rx,&ry,&xc,&yc);
	double x=0,y=ry;
	double rx2=rx*(double)rx;
	double ry2=ry*(double)ry;
	double p1=ry2-rx2*ry+(rx2/4.0);
	glVertex2i(xc+(int)x,yc+(int)y);
	while(2.0*ry2*x<2.0*rx2*y){
		x++;
		if(p1>=0){
			y--;
			p1-=2.0*y*rx2;
		}
		p1+=2.0*ry2*x+ry2;
		glVertex2i(xc+(int)x,yc+(int)y);
		glVertex2i(xc-(int)x,yc+(int)y);
		glVertex2i(xc+(int)x,yc-(int)y);
		glVertex2i(xc-(int)x,yc-(int)y);
	}
	double p2=ry2*(x+0.5)*(x+0.5)+rx2*(y-1.0)*(y-1.0)-rx2*ry2;
	glVertex2i(xc+(int)x,yc+(int)y);
	while(y>0){
		y--;
		if(p2<=0){
			x++;
			p2+=2.0*ry2*x;
		}
		p2+=rx2-2.0*y*rx2;
		glVertex2i(xc+(int)x,yc+(int)y);
		glVertex2i(xc-(int)x,yc+(int)y);
		glVertex2i(xc+(int)x,yc-(int)y);
		glVertex2i(xc-(int)x,yc-(int)y);
	}
    glEnd();
	glFlush();
}

int main(int argc, char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1366, 768);
	glutInitWindowPosition(-500,-500);
	glutCreateWindow("Ellipse Midpoint Algorithm");
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	myInit();
	glutMainLoop();
	return 0;
}