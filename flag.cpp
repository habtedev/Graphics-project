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
#define POLE_X       30.0f
#define POLE_TOP     20.0f
#define POLE_BOTTOM 395.0f
#define POLE_W        8.0f
#define BALL_R        9.0f

#define FLAG_OFFSET_X  34.0f
#define FLAG_SCALE     0.62f

void drawPole()
{

    glColor3f(0.55f, 0.55f, 0.58f);
    glBegin(GL_QUADS);
        glVertex2f(POLE_X - POLE_W, POLE_TOP);
        glVertex2f(POLE_X + POLE_W, POLE_TOP);
        glVertex2f(POLE_X + POLE_W, POLE_BOTTOM);
        glVertex2f(POLE_X - POLE_W, POLE_BOTTOM);
    glEnd();


    glColor3f(0.80f, 0.80f, 0.83f);
    glBegin(GL_QUADS);
        glVertex2f(POLE_X - POLE_W,          POLE_TOP);
        glVertex2f(POLE_X - POLE_W + 3.0f,   POLE_TOP);
        glVertex2f(POLE_X - POLE_W + 3.0f,   POLE_BOTTOM);
        glVertex2f(POLE_X - POLE_W,           POLE_BOTTOM);
    glEnd();


    glColor3f(0.75f, 0.65f, 0.20f);   // gold-ish
    int   segs  = 32;
    float pi    = 3.14159265f;
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(POLE_X, POLE_TOP - BALL_R);
        for (int i = 0; i <= segs; i++) {
            float a = 2.0f * pi * i / segs;
            glVertex2f(POLE_X + BALL_R * cosf(a),
                       (POLE_TOP - BALL_R) + BALL_R * sinf(a));
        }
    glEnd();


    glColor3f(0.40f, 0.40f, 0.42f);
    glBegin(GL_QUADS);
        glVertex2f(POLE_X - 18.0f, POLE_BOTTOM);
        glVertex2f(POLE_X + 18.0f, POLE_BOTTOM);
        glVertex2f(POLE_X + 18.0f, POLE_BOTTOM + 10.0f);
        glVertex2f(POLE_X - 18.0f, POLE_BOTTOM + 10.0f);
    glEnd();
}

void display()
{
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawPole();

    glPushMatrix();
        glTranslatef(FLAG_OFFSET_X, POLE_TOP, 0.0f);
        glScalef(FLAG_SCALE, FLAG_SCALE, 1.0f);
        drawFlag();
    glPopMatrix();

    glutSwapBuffers();
}
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIN_W, WIN_H, 0);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIN_W, WIN_H);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bosnia & Herzegovina - Flag");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}