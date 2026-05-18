#ifdef _WIN32
  #include <windows.h>
  #include <GL/glut.h>
#elif defined(APPLE)
  #include <GLUT/glut.h>
  #include <OpenGL/glu.h>
#else
  #include <GL/glut.h>
  #include <GL/glu.h>
#endif

#include <cstdlib>
#include <cmath>
#include <vector>
#include <array>


static const int WIN_W = 600;
static const int WIN_H = 600;


static std::vector< std::array<double,3> > g_verts;
static float g_cx = 0, g_cy = 0;

// Rotation angle in degrees (positive = counter-clockwise)
static float g_angle = 0.0f;
// Step size per key press (degrees)
static const float ROTATE_STEP = 5.0f;

static void penMove(float x, float y) { g_cx=x; g_cy=y; }

static void emit(float x, float y)
{
    std::array<double,3> v;
    v[0]=(double)x; v[1]=(double)y; v[2]=0.0;
    g_verts.push_back(v);
}

static void cubicRel(float dx1,float dy1,
                     float dx2,float dy2,
                     float dx, float dy,
                     int N=32)
{
    float x0=g_cx,y0=g_cy;
    float x1=x0+dx1,y1=y0+dy1;
    float x2=x0+dx2,y2=y0+dy2;
    float x3=x0+dx, y3=y0+dy;
    for(int i=1;i<=N;i++){
        float t=(float)i/N, u=1.f-t;
        emit(u*u*u*x0+3*u*u*t*x1+3*u*t*t*x2+t*t*t*x3,
             u*u*u*y0+3*u*u*t*y1+3*u*t*t*y2+t*t*t*y3);
    }
    g_cx+=dx; g_cy+=dy;
}

static void lineRel(float dx,float dy){ g_cx+=dx; g_cy+=dy; emit(g_cx,g_cy); }
static void vlineRel(float dy)        { g_cy+=dy;            emit(g_cx,g_cy); }
static void buildPath()
{
    g_verts.clear();
    penMove(1101.1943f,432.0749f); emit(g_cx,g_cy);

    cubicRel(0,-20.8f,         10.6f,-24.8f,      30.3f,-13.6f);
    cubicRel(36.4f,20.f,       74.2f,41.6f,        74.2f,41.6f);
    cubicRel(1.5f,-12.f,       11.6f,-21.6f,       33.3f,-16.8f);
    cubicRel(20.2f,4.8f,       42.9f,9.6f,         42.9f,9.6f);
    cubicRel(0,0,             -12.1f,-27.2f,       -17.7f,-39.2f);
    cubicRel(-10.1f,-22.4f,   -0.5f,-33.6f,         9.6f,-36.f);
    cubicRel(0,0,             -14.1f,-9.6f,        -23.2f,-16.f);
    cubicRel(-19.7f,-13.6f,  -15.1f,-27.2f,         4.f,-35.2f);
    cubicRel(25.8f,-11.2f,    58.6f,-25.6f,        58.6f,-25.6f);
    cubicRel(-10.6f,-6.4f,   -22.7f,-23.2f,        -9.1f,-42.4f);
    cubicRel(13.6f,-20.f,     33.3f,-47.2f,        33.3f,-47.2f);
    cubicRel(0,0,            -35.3f,0.8f,          -58.6f,0.f);
    cubicRel(-21.7f,0,       -26.8f,-16.8f,        -26.3f,-28.8f);
    cubicRel(0,0,            -34.8f,24.f,          -59.6f,40.8f);
    cubicRel(-21.2f,14.4f,   -39.9f,0.8f,          -36.9f,-23.2f);
    cubicRel(5.f,-38.4f,       9.6f,-79.9f,          9.6f,-79.9f);
    cubicRel(-13.1f,8.8f,    -35.3f,8.f,           -44.9f,-12.8f);
    cubicRel(-14.4f,-31.f,   -31.1f,-67.8f,        -31.1f,-67.8f);
    cubicRel(0,0,            -16.7f,36.8f,         -30.8f,67.9f);
    cubicRel(-10.1f,20.8f,   -32.3f,21.6f,         -44.9f,12.8f);
    cubicRel(0,0,              4.5f,41.6f,           9.6f,79.9f);
    cubicRel(3.f,24.f,       -16.2f,37.6f,         -36.9f,23.2f);
    cubicRel(-24.7f,-16.8f,  -59.6f,-40.8f,        -59.6f,-40.8f);
    cubicRel(0,12.f,          -5.1f,28.8f,         -26.3f,28.8f);
    cubicRel(-23.7f,0.8f,    -58.6f,0.f,           -58.6f,0.f);
    cubicRel(0,0,             19.7f,27.2f,          32.8f,47.2f);
    cubicRel(13.6f,19.2f,      1.5f,36.f,           -8.6f,42.4f);
    cubicRel(0,0,             32.3f,14.4f,          58.1f,25.6f);
    cubicRel(19.2f,8.f,       23.7f,21.6f,           4.f,35.2f);
    cubicRel(-9.1f,6.4f,     -22.7f,16.f,          -22.7f,16.f);
    cubicRel(9.6f,2.4f,       19.2f,13.6f,           9.1f,36.f);
    cubicRel(-5.6f,12.f,     -17.7f,39.2f,         -17.7f,39.2f);
    cubicRel(0,0,             22.7f,-4.8f,          42.9f,-9.6f);
    cubicRel(22.2f,-4.8f,     32.3f,4.8f,           33.3f,16.8f);
    cubicRel(0,0,             37.9f,-21.6f,         74.2f,-41.6f);
    cubicRel(19.7f,-11.2f,    30.3f,-7.2f,          30.3f,13.6f);
    vlineRel(50.4f);
    cubicRel(0.5f,29.6f,      -5.f,61.5f,          -16.2f,79.1f);
    cubicRel(-139.3f,-15.2f, -255.f,-127.1f,      -255.5f,-274.2f);
    cubicRel(0,-151.9f,       126.7f,-275.f,        283.2f,-275.f);
    cubicRel(156.f,0.f,       283.2f,123.1f,        283.2f,275.f);
    cubicRel(0,141.5f,       -110.6f,257.4f,       -251.9f,272.6f);
    vlineRel(37.6f);
    cubicRel(166.1f,-15.2f,   295.8f,-148.7f,       295.8f,-310.2f);
    cubicRel(0.4f,-172.8f,   -146.1f,-311.9f,      -326.8f,-311.9f);
    cubicRel(-180.7f,0.f,    -327.2f,139.1f,       -327.2f,311.8f);
    cubicRel(0,151.1f,        113.6f,277.4f,        264.f,305.4f);
    cubicRel(25.2f,4.8f,       41.4f,8.8f,           55.f,24.8f);
    cubicRel(15.7f,-28.8f,     19.7f,-91.1f,         19.7f,-126.3f);
    lineRel(0.1f,-59.3f);
}
static void getBBox(double &x0,double &y0,double &x1,double &y1)
{
    x0=y0=1e30; x1=y1=-1e30;
    for(int i=0;i<(int)g_verts.size();i++){
        if(g_verts[i][0]<x0) x0=g_verts[i][0];
        if(g_verts[i][0]>x1) x1=g_verts[i][0];
        if(g_verts[i][1]<y0) y0=g_verts[i][1];
        if(g_verts[i][1]>y1) y1=g_verts[i][1];
    }
}


#ifndef CALLBACK
  #define CALLBACK
#endif

static void CALLBACK cb_begin (GLenum t)     { glBegin(t); }
static void CALLBACK cb_end   ()             { glEnd();    }
static void CALLBACK cb_vertex(void *d)      { glVertex3dv((GLdouble*)d); }
static void CALLBACK cb_error (GLenum /*e*/) {}


static void display()
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);

    double bx0,by0,bx1,by1;
    getBBox(bx0,by0,bx1,by1);

    double svgW=bx1-bx0, svgH=by1-by0;
    double margin=40.0;
    double sx=(WIN_W-2*margin)/svgW;
    double sy=(WIN_H-2*margin)/svgH;
    double s = sx<sy ? sx : sy;
    double ox=margin+(WIN_W-2*margin-svgW*s)/2.0-bx0*s;
    double oy=margin+(WIN_H-2*margin-svgH*s)/2.0-by0*s;

    // Compute center of the shape in screen space (before rotation)
    double cx = WIN_W / 2.0;
    double cy = WIN_H / 2.0;

    int N=(int)g_verts.size();
    std::vector< std::array<double,3> > tv(N);
    for(int i=0;i<N;i++){
        // Transform to screen space
        double sx_ = g_verts[i][0]*s + ox;
        double sy_ = WIN_H - (g_verts[i][1]*s + oy);

        // Rotate around screen center
        double dx = sx_ - cx;
        double dy = sy_ - cy;
        double rad = g_angle * 3.14159265358979323846 / 180.0;
        double cosA = cos(rad);
        double sinA = sin(rad);

        tv[i][0] = cosA * dx - sinA * dy + cx;
        tv[i][1] = sinA * dx + cosA * dy + cy;
        tv[i][2] = 0.0;
    }

    GLUtesselator *tess = gluNewTess();
    gluTessCallback(tess,GLU_TESS_BEGIN,  (GLvoid(CALLBACK*)())cb_begin);
    gluTessCallback(tess,GLU_TESS_END,    (GLvoid(CALLBACK*)())cb_end);
    gluTessCallback(tess,GLU_TESS_VERTEX, (GLvoid(CALLBACK*)())cb_vertex);
    gluTessCallback(tess,GLU_TESS_ERROR,  (GLvoid(CALLBACK*)())cb_error);
    gluTessProperty(tess,GLU_TESS_WINDING_RULE,GLU_TESS_WINDING_NONZERO);

    glColor3f(1,0,0);
    gluTessBeginPolygon(tess,NULL);
    gluTessBeginContour(tess);
    for(int i=0;i<N;i++)
        gluTessVertex(tess,tv[i].data(),tv[i].data());
    gluTessEndContour(tess);
    gluTessEndPolygon(tess);
    gluDeleteTess(tess);

    glutSwapBuffers();
}
static void reshape(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,w,0,h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void keyboard(unsigned char key,int,int)
{
    switch(key) {
        case 27: case 'q': case 'Q':
            exit(0);
            break;
        case 'l': case 'L':
            // Rotate left (counter-clockwise)
            g_angle += ROTATE_STEP;
            glutPostRedisplay();
            break;
        case 'r': case 'R':
            // Rotate right (clockwise)
            g_angle -= ROTATE_STEP;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

static void specialKeys(int key, int, int)
{
    switch(key) {
        case GLUT_KEY_LEFT:
            g_angle += ROTATE_STEP;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            g_angle -= ROTATE_STEP;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

int main(int argc,char **argv)
{
    buildPath();
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(WIN_W,WIN_H);
    glutCreateWindow("Logo - L/R or Arrow Keys to Rotate");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);   // register arrow key handler
    glutMainLoop();
    return 0;
}
