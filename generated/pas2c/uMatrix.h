#pragma once

#include "pas2c.h"

#include "uTypes.h"
extern Integer MATRIX_MODELVIEW;
extern Integer MATRIX_PROJECTION;
void umatrix_MatrixLoadIdentity(TMatrix4x4f (*Result));
void umatrix_MatrixMultiply(TMatrix4x4f (*Result),TMatrix4x4f lhs,TMatrix4x4f rhs);
void umatrix_hglMatrixMode(Integer t);
void umatrix_hglLoadIdentity();
void umatrix_hglPushMatrix();
void umatrix_hglPopMatrix();
void umatrix_hglMVP(TMatrix4x4f (*res));
void umatrix_hglScalef(GLfloat x,GLfloat y,GLfloat z);
void umatrix_hglTranslatef(GLfloat x,GLfloat y,GLfloat z);
void umatrix_hglRotatef(GLfloat a,GLfloat x,GLfloat y,GLfloat z);
void umatrix_initModule();
void umatrix_freeModule();

