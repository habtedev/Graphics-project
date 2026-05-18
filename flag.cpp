#include <GL/glut.h>
#include <math.h>
#define WIN_W 600
#define WIN_H 400
void drawStar(float cx, float cy, float R, float r)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 10; i++) {
        float angle = -3.14159265f / 2.0f + i * 3.14159265f / 5.0f;
        float radius = (i % 2 == 0) ? R : r;
        glVertex2f(cx + radius * cosf(angle), cy + radius * sinf(angle));
    }
    glEnd();
}
