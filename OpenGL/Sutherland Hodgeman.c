#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

int windowWidth = 1366;
int windowHeight = 768;

int n=9;

int pts[20][2]={{50,150},{200,50},{350,150},{350,300},{250,300},{200,250},{150,350},{100,250},{100,200}};
int clipper[4][2]={{100,100},{300,100},{300,300},{100,300}};

typedef struct{
    float x,y;
}Point;

Point ans[20];
int cnt;

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

void axes(){
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2i(-1000, 0);
    glVertex2i(1000, 0);
    glVertex2i(0, -500);
    glVertex2i(0, 500);
    glEnd();
}

void polygon_boundary(){
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < n; i++) {
        glVertex2i(pts[i][0], pts[i][1]);
    }
    glEnd();
}

void myReshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, w, h);
    myInit();
    glutPostRedisplay();
}

void make_clip_window(){
    glColor3f(0.5f,0.5f,1.0f);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<4;i++){
        glVertex2i(clipper[i][0],clipper[i][1]);
    }
    glEnd();
}

Point ints(Point st, Point end, int bound, int dim){
    Point res;
    if(st.x==end.x){
        res.x=st.x;
        res.y=bound;
    }
    else if(st.y==end.y){
        res.x=bound;
        res.y=st.y;
    }
    else{
        float m=(end.y-st.y)/(end.x-st.x);
        if(dim==0){
            res.x=bound;
            res.y=st.y+m*(bound-st.x);
        }
        else{
            res.y=bound;
            res.x=st.x+(bound-st.y)/m;
        }
    }
    return res;
}

void clips(int bound, int dim, int lowerbound){
    Point temp[20];
    int tempcount=0;
    for (int i = 0; i < cnt; i++) {
        Point a;
        a=ans[i];
        Point b;
        b=ans[(i + 1) % cnt];
        bool ain, bin;
        if (dim == 0) {
            if (lowerbound) {
                ain = (a.x >= bound);
                bin = (b.x >= bound);
            } 
            else {
                ain = (a.x <= bound);
                bin = (b.x <= bound);
            }
        } 
        else {
            if (lowerbound) {
                ain = (a.y >= bound);
                bin = (b.y >= bound);
            } 
            else {
                ain = (a.y <= bound);
                bin = (b.y <= bound);
            }
        }
        // in-in
        if (ain && bin) {
            temp[tempcount].x=b.x;
            temp[tempcount].y=b.y;
            tempcount++;
        } 
        // in-out
        else if (ain && !bin) {
            temp[tempcount]=ints(a,b,bound,dim);
            tempcount++;
        } 
        // out-in 
        else if (!ain && bin) {
            temp[tempcount]=ints(a,b,bound,dim);
            tempcount++;
            temp[tempcount].x=b.x;
            temp[tempcount].y=b.y;
            tempcount++;
        }
        // out-out
        else{
            // do nothing
        }
    }
    for (int i = 0; i < tempcount; i++) {
        ans[i] = temp[i];
    }
    cnt=tempcount;
}

void final(){
    for(int i=0; i<n; i++){
        ans[i].x=pts[i][0];
        ans[i].y=pts[i][1];
    }
    cnt=n;
    clips(100,0,1);
    clips(300,0,0); 
    clips(100,1,1);
    clips(300,1,0);
}

void myDisplay(void){
    glClear(GL_COLOR_BUFFER_BIT);
    axes();
    polygon_boundary();
    make_clip_window();
    final();
    glColor4f(1.0f, 0.0f, 0.0f, 0.7f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < cnt; i++) {
        glVertex2i(ans[i].x, ans[i].y);
    }
    glEnd();
    glFlush();
}

void main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1366, 768);
    glutInitWindowPosition(-500,-500);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glEnable(GL_BLEND);
    glutCreateWindow("Sutherland Hodgeman Theorem");
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myReshape);
    myInit();
    glutMainLoop();
}