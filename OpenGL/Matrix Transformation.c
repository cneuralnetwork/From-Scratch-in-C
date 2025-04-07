#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct
{
    float x;
    float y;
} Point2D;

Point2D start_point, rotation_center, result_point;
float translate_x, translate_y, rotation_angle, scale_angle, scale_factor, deg1, deg2;
float composite_matrix[3][3];

void draw_og()
{
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-7.5f, 0.0f);
    glVertex2f(7.5f, 0.0f);
    glVertex2f(0.0f, -7.5f);
    glVertex2f(0.0f, 7.5f);
    glEnd();
}

void solve()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            composite_matrix[i][j] = (i == j) ? 1.0f : 0.0f;
    deg1=((rotation_angle) * 3.14159 / 180.0);
    float sin_val = sin(deg1);
    float cos_val = cos(deg1);
    float rot_mat[3][3] = {{cos_val, -sin_val, rotation_center.x * (1 - cos_val) + rotation_center.y * sin_val}, {sin_val, cos_val, rotation_center.y * (1 - cos_val) - rotation_center.x * sin_val}, {0, 0, 1}};
    float trans_mat[3][3] = {{1, 0, translate_x}, {0, 1, translate_y}, {0, 0, 1}};
    deg2=((scale_angle) * 3.14159 / 180.0);
    float dir_x = sin(deg2);
    float dir_y = cos(deg2);
    float scale_mat[3][3] = {{scale_factor * dir_x * dir_x + (1 - dir_x * dir_x), (scale_factor - 1) * dir_x * dir_y, 0}, {(scale_factor - 1) * dir_x * dir_y, scale_factor * dir_y * dir_y + (1 - dir_y * dir_y), 0}, {0, 0, 1}};
    float temp_mat[3][3];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            temp_mat[i][j] = 0;
            for (int k = 0; k < 3; k++)
                temp_mat[i][j] += trans_mat[i][k] * rot_mat[k][j];
        }
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            composite_matrix[i][j] = 0;
            for (int k = 0; k < 3; k++)
                composite_matrix[i][j] += scale_mat[i][k] * temp_mat[k][j];
        }
    }
}

void plot_point(float px, float py, float r, float g, float b)
{
    glPointSize(8.0f);
    glBegin(GL_POINTS);
    glColor3f(r, g, b);
    glVertex2f(px / 80.0f, py / 80.0f);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    draw_og();
    plot_point(start_point.x, start_point.y, 1.0f, 0.4f, 0.2f);
    float rot_x = cos(deg1) * (start_point.x - rotation_center.x) - sin(deg1) * (start_point.y - rotation_center.y) + rotation_center.x;
    float rot_y = sin(deg1) * (start_point.x - rotation_center.x) + cos(deg1) * (start_point.y - rotation_center.y) + rotation_center.y;
    plot_point(rot_x, rot_y, 0.0f, 0.0f, 1.0f);
    plot_point(rot_x + translate_x, rot_y + translate_y, 1.0f, 0.0f, 1.0f);
    result_point.x = composite_matrix[0][0] * start_point.x + composite_matrix[0][1] * start_point.y + composite_matrix[0][2];
    result_point.y = composite_matrix[1][0] * start_point.x + composite_matrix[1][1] * start_point.y + composite_matrix[1][2];
    plot_point(result_point.x, result_point.y, 1.0f, 1.0f, 1.0f);
    glFlush();
}

void take_input(){
    printf("Enter initial coordinates x, y: ");
    scanf("%f %f", &start_point.x, &start_point.y);

    printf("Enter rotation center xr, yr: ");
    scanf("%f %f", &rotation_center.x, &rotation_center.y);

    printf("Enter translation t1, t2: ");
    scanf("%f %f", &translate_x, &translate_y);
    if (translate_x < 50 || translate_x > 150 || translate_y < 50 || translate_y > 150) {
        printf("Error: t1 and t2 must be between 50 and 150\n");
        exit(1);
    }

    printf("Enter rotation angle d1: ");
    scanf("%f", &rotation_angle);
    if (rotation_angle < 10 || rotation_angle > 30) {
        printf("Error: d1 must be between 10 and 30\n");
        exit(1);
    }

    printf("Enter scaling direction d2: ");
    scanf("%f", &scale_angle);
    if (scale_angle < 10 || scale_angle > 30) {
        printf("Error: d2 must be between 10 and 30\n");
        exit(1);
    }

    printf("Enter scaling factor s: ");
    scanf("%f", &scale_factor);
    if (scale_factor < 2.0 || scale_factor > 3.0) {
        printf("Error: s must be between 2.0 and 3.0\n");
        exit(1);
    }

}

int main(int argc, char **argv)
{
    take_input();
    solve();
    printf("\nFinal Transformation Matrix:\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            printf("%.4f ", composite_matrix[i][j]);
        printf("\n");
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Transformation Matrices");
    glClearColor(0.0f,0.0f,0.0f, 1.0f);
    gluOrtho2D(-7.5f, 7.5f, -7.5f, 7.5f);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}