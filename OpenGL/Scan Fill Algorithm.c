#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

int windowWidth = 1366;
int windowHeight = 768;

int n=11;

typedef struct{
    int x;
    int y;
}Point;

Point pts[]={{10,60},{30,140},{50,60},{80,220},{100,60},
    {150,100},{180,50},{200,40},{250,90},{300,30},{120,10}};

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
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2i(-1000, 0);
    glVertex2i(1000, 0);
    glVertex2i(0, -500);
    glVertex2i(0, 500);
    glEnd();
    glColor3f(1.0f, 0.0f, 0.0f);
    // glBegin(GL_LINES);
     glPointSize(3.0);
    int ymin=pts[0].y;
    int ymax=pts[0].y;
    for (int i=1;i<n;i++){
        if (ymax<pts[i].y) ymax=pts[i].y;
        if (ymin>pts[i].y) ymin=pts[i].y;
    }
    // printf("%d %d",ymin,ymax);
    for (int y=ymin;y<=ymax;y++){
        int ints[200];
        int cnt=0; int y1,y2;
        for(int i=0;i<n;i++){
            int j=(i+1)%n;
            y1=pts[i].y;
            y2=pts[j].y;
             if (y1<y2){
            if (y>=y1 && y<y2){
                int x=pts[i].x+(y-y1)*(pts[j].x-pts[i].x)/(y2-y1);
                ints[cnt++]=x;
            }
        } else if (y1>y2){
            if(y>=y2 && y<y1){
                int x=pts[j].x+(y-y2)*(pts[i].x-pts[j].x)/(y1-y2);
                ints[cnt++]=x;
            }
        }    
        }
        for (int i=0;i<cnt-1;i++){
            for (int j=i+1;j<cnt;j++){
                if(ints[i]>ints[j]){
                    int k=ints[i];
                    ints[i]=ints[j];
                    ints[j]=k;
                }
            }
        }
        for(int i=0;i<cnt;i+=2){
            glBegin(GL_LINES);
            glVertex2i(ints[i],y);
            glVertex2i(ints[i+1],y);
            glEnd();
        }
    }
    // glVertex2i(0,0);
    // glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
     glPointSize(3.0);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<n;i++){
        glVertex2i(pts[i].x,pts[i].y);
    }
    glEnd();
    glFlush();
}

void main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1366, 768);
    glutInitWindowPosition(-500,-500);
    glutCreateWindow("Ellipse Midpoint Theorem");
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myReshape);
    myInit();
    glutMainLoop();
}