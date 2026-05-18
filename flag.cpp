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
void drawFlag()
{
    float x0 = 0.0f,  x1 = (float)WIN_W;
    float y0 = 0.0f,  y1 = (float)WIN_H;
    float w  = x1 - x0;   // 600
    float h  = y1 - y0;   // 400
    float stripeW = w * 0.148f;
    float diagStartX = x0 + stripeW;
    float diagStartY = y0;
    float diagEndX   = x1 - stripeW;
    float diagEndY   = y1;
    float dxD = diagEndX - diagStartX;
    float dyD = diagEndY - diagStartY;
    float len  = sqrtf(dxD * dxD + dyD * dyD);
    float udx  = dxD / len;
    float udy  = dyD / len;
    float px = -udy;
    float py =  udx;
    glColor3f(0.0f, 0.133f, 0.58f);
    glBegin(GL_QUADS);
        glVertex2f(x0, y0);
        glVertex2f(x1, y0);
        glVertex2f(x1, y1);
        glVertex2f(x0, y1);
    glEnd();
    glColor3f(0.992f, 0.792f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(diagStartX, y0);
        glVertex2f(diagEndX,   y1);
        glVertex2f(x1,         y1);
        glVertex2f(x1,         y0);
    glEnd();
    glColor3f(0.0f, 0.133f, 0.58f);
    glBegin(GL_QUADS);
        glVertex2f(x1 - stripeW, y0);
        glVertex2f(x1,           y0);
        glVertex2f(x1,           y1);
        glVertex2f(x1 - stripeW, y1);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
    int   nStars = 9;
    float starR  = 13.0f;
    float starr  = 5.5f;
    float offset = 22.0f;
    float tStart = 0.05f;
    float tEnd   = 0.95f;
    for (int i = 0; i < nStars; i++) {
        float t  = tStart + (float)i / (nStars - 1) * (tEnd - tStart);
        float sx = diagStartX + t * dxD;
        float sy = diagStartY + t * dyD;
        sx += px * offset;
        sy += py * offset;
        drawStar(sx, sy, starR, starr);
    }
}