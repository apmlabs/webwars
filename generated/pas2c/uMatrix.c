#include "fpcrtl.h"

#include "uMatrix.h"
Integer MATRIX_MODELVIEW = 0;
Integer MATRIX_PROJECTION = 1;
#include "uDebug.h"
enum{MATRIX_STACK_SIZE = 10};
typedef struct __TMatrixStack {
            Integer top;
            TMatrix4x4f stack[(9 + 1)];
        } TMatrixStack;
typedef TMatrixStack MatrixStacks_tt[(1 + 1)];
static MatrixStacks_tt MatrixStacks;
static Integer CurMatrix;
void umatrix_MatrixLoadIdentity(TMatrix4x4f (*Result))
{
    (*Result)[0][0] = 1.0;
    (*Result)[1][0] = 0.0;
    (*Result)[2][0] = 0.0;
    (*Result)[3][0] = 0.0;
    (*Result)[0][1] = 0.0;
    (*Result)[1][1] = 1.0;
    (*Result)[2][1] = 0.0;
    (*Result)[3][1] = 0.0;
    (*Result)[0][2] = 0.0;
    (*Result)[1][2] = 0.0;
    (*Result)[2][2] = 1.0;
    (*Result)[3][2] = 0.0;
    (*Result)[0][3] = 0.0;
    (*Result)[1][3] = 0.0;
    (*Result)[2][3] = 0.0;
    (*Result)[3][3] = 1.0;
};
void umatrix_hglMatrixMode(Integer t)
{
    CurMatrix = t;
};
void umatrix_hglLoadIdentity()
{
    umatrix_MatrixLoadIdentity(&(MatrixStacks[CurMatrix].stack[MatrixStacks[CurMatrix].top]));
};
void umatrix_hglScalef(GLfloat x,GLfloat y,GLfloat z)
{
    TMatrix4x4f m;
    TMatrix4x4f t;
    m[0][0] = x;
    m[1][0] = 0;
    m[2][0] = 0;
    m[3][0] = 0;
    m[0][1] = 0;
    m[1][1] = y;
    m[2][1] = 0;
    m[3][1] = 0;
    m[0][2] = 0;
    m[1][2] = 0;
    m[2][2] = z;
    m[3][2] = 0;
    m[0][3] = 0;
    m[1][3] = 0;
    m[2][3] = 0;
    m[3][3] = 1;
    umatrix_MatrixMultiply(&(t), MatrixStacks[CurMatrix].stack[MatrixStacks[CurMatrix].top], m);
    fpcrtl_memcpy(MatrixStacks[CurMatrix].stack[MatrixStacks[CurMatrix].top], t, sizeof(t));
};
void umatrix_hglTranslatef(GLfloat x,GLfloat y,GLfloat z)
{
    TMatrix4x4f m;
    TMatrix4x4f t;
    m[0][0] = 1;
    m[1][0] = 0;
    m[2][0] = 0;
    m[3][0] = x;
    m[0][1] = 0;
    m[1][1] = 1;
    m[2][1] = 0;
    m[3][1] = y;
    m[0][2] = 0;
    m[1][2] = 0;
    m[2][2] = 1;
    m[3][2] = z;
    m[0][3] = 0;
    m[1][3] = 0;
    m[2][3] = 0;
    m[3][3] = 1;
    umatrix_MatrixMultiply(&(t), MatrixStacks[CurMatrix].stack[MatrixStacks[CurMatrix].top], m);
    fpcrtl_memcpy(MatrixStacks[CurMatrix].stack[MatrixStacks[CurMatrix].top], t, sizeof(t));
};
void umatrix_hglRotatef(GLfloat a,GLfloat x,GLfloat y,GLfloat z)
{
    TMatrix4x4f m;
    TMatrix4x4f t;
    GLfloat c;
    GLfloat s;
    GLfloat xn;
    GLfloat yn;
    GLfloat zn;
    GLfloat l;
    a = (a * 3.14159265368) /(float) 180;
    c = cos(a);
    s = sin(a);
    l = 1.0 /(float) sqrt(((x * x) + (y * y)) + (z * z));
    xn = x * l;
    yn = y * l;
    zn = z * l;
    m[0][0] = c + ((xn * xn) * (1 - c));
    m[1][0] = ((xn * yn) * (1 - c)) - (zn * s);
    m[2][0] = ((xn * zn) * (1 - c)) + (yn * s);
    m[3][0] = 0;
    m[0][1] = ((yn * xn) * (1 - c)) + (zn * s);
    m[1][1] = c + ((yn * yn) * (1 - c));
    m[2][1] = ((yn * zn) * (1 - c)) - (xn * s);
    m[3][1] = 0;
    m[0][2] = ((zn * xn) * (1 - c)) - (yn * s);
    m[1][2] = ((zn * yn) * (1 - c)) + (xn * s);
    m[2][2] = c + ((zn * zn) * (1 - c));
    m[3][2] = 0;
    m[0][3] = 0;
    m[1][3] = 0;
    m[2][3] = 0;
    m[3][3] = 1;
    umatrix_MatrixMultiply(&(t), MatrixStacks[CurMatrix].stack[MatrixStacks[CurMatrix].top], m);
    fpcrtl_memcpy(MatrixStacks[CurMatrix].stack[MatrixStacks[CurMatrix].top], t, sizeof(t));
};
void umatrix_hglMVP(TMatrix4x4f (*res))
{
    umatrix_MatrixMultiply(&((*res)), MatrixStacks[MATRIX_PROJECTION].stack[MatrixStacks[MATRIX_PROJECTION].top], MatrixStacks[MATRIX_MODELVIEW].stack[MatrixStacks[MATRIX_MODELVIEW].top]);
};
void umatrix_hglPushMatrix()
{
    Integer t;
    t = MatrixStacks[CurMatrix].top;
    fpcrtl_memcpy(MatrixStacks[CurMatrix].stack[t + 1], MatrixStacks[CurMatrix].stack[t], sizeof(MatrixStacks[CurMatrix].stack[t]));
    ++t;
    MatrixStacks[CurMatrix].top = t;
};
void umatrix_hglPopMatrix()
{
    Integer t;
    t = MatrixStacks[CurMatrix].top;
    --t;
    MatrixStacks[CurMatrix].top = t;
};
void umatrix_initModule()
{
    MatrixStacks[MATRIX_MODELVIEW].top = 0;
    MatrixStacks[MATRIX_PROJECTION].top = 0;
    umatrix_MatrixLoadIdentity(&(MatrixStacks[MATRIX_MODELVIEW].stack[0]));
    umatrix_MatrixLoadIdentity(&(MatrixStacks[MATRIX_PROJECTION].stack[0]));
};
void umatrix_freeModule()
{
};
void umatrix_MatrixMultiply(TMatrix4x4f (*Result),TMatrix4x4f lhs,TMatrix4x4f rhs)
{
    TMatrix4x4f test;
    Integer i;
    Integer j;
    boolean error;
    (*Result)[0][0] = (((lhs[0][0] * rhs[0][0]) + (lhs[1][0] * rhs[0][1])) + (lhs[2][0] * rhs[0][2])) + (lhs[3][0] * rhs[0][3]);
    (*Result)[0][1] = (((lhs[0][1] * rhs[0][0]) + (lhs[1][1] * rhs[0][1])) + (lhs[2][1] * rhs[0][2])) + (lhs[3][1] * rhs[0][3]);
    (*Result)[0][2] = (((lhs[0][2] * rhs[0][0]) + (lhs[1][2] * rhs[0][1])) + (lhs[2][2] * rhs[0][2])) + (lhs[3][2] * rhs[0][3]);
    (*Result)[0][3] = (((lhs[0][3] * rhs[0][0]) + (lhs[1][3] * rhs[0][1])) + (lhs[2][3] * rhs[0][2])) + (lhs[3][3] * rhs[0][3]);
    (*Result)[1][0] = (((lhs[0][0] * rhs[1][0]) + (lhs[1][0] * rhs[1][1])) + (lhs[2][0] * rhs[1][2])) + (lhs[3][0] * rhs[1][3]);
    (*Result)[1][1] = (((lhs[0][1] * rhs[1][0]) + (lhs[1][1] * rhs[1][1])) + (lhs[2][1] * rhs[1][2])) + (lhs[3][1] * rhs[1][3]);
    (*Result)[1][2] = (((lhs[0][2] * rhs[1][0]) + (lhs[1][2] * rhs[1][1])) + (lhs[2][2] * rhs[1][2])) + (lhs[3][2] * rhs[1][3]);
    (*Result)[1][3] = (((lhs[0][3] * rhs[1][0]) + (lhs[1][3] * rhs[1][1])) + (lhs[2][3] * rhs[1][2])) + (lhs[3][3] * rhs[1][3]);
    (*Result)[2][0] = (((lhs[0][0] * rhs[2][0]) + (lhs[1][0] * rhs[2][1])) + (lhs[2][0] * rhs[2][2])) + (lhs[3][0] * rhs[2][3]);
    (*Result)[2][1] = (((lhs[0][1] * rhs[2][0]) + (lhs[1][1] * rhs[2][1])) + (lhs[2][1] * rhs[2][2])) + (lhs[3][1] * rhs[2][3]);
    (*Result)[2][2] = (((lhs[0][2] * rhs[2][0]) + (lhs[1][2] * rhs[2][1])) + (lhs[2][2] * rhs[2][2])) + (lhs[3][2] * rhs[2][3]);
    (*Result)[2][3] = (((lhs[0][3] * rhs[2][0]) + (lhs[1][3] * rhs[2][1])) + (lhs[2][3] * rhs[2][2])) + (lhs[3][3] * rhs[2][3]);
    (*Result)[3][0] = (((lhs[0][0] * rhs[3][0]) + (lhs[1][0] * rhs[3][1])) + (lhs[2][0] * rhs[3][2])) + (lhs[3][0] * rhs[3][3]);
    (*Result)[3][1] = (((lhs[0][1] * rhs[3][0]) + (lhs[1][1] * rhs[3][1])) + (lhs[2][1] * rhs[3][2])) + (lhs[3][1] * rhs[3][3]);
    (*Result)[3][2] = (((lhs[0][2] * rhs[3][0]) + (lhs[1][2] * rhs[3][1])) + (lhs[2][2] * rhs[3][2])) + (lhs[3][2] * rhs[3][3]);
    (*Result)[3][3] = (((lhs[0][3] * rhs[3][0]) + (lhs[1][3] * rhs[3][1])) + (lhs[2][3] * rhs[3][2])) + (lhs[3][3] * rhs[3][3]);
};
