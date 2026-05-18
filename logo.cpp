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