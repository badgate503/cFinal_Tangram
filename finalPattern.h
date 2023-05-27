/*
 * makeShape.h -- 绘制两种形状相关函数接口. 
 */
 
#ifndef __FINALPATTERN_H__
#define __FINALPATTERN_H__

#include "genlib.h"
#include "tangramMain.h"
#include "linkedlist.h"
#include "makeShape.h"

typedef struct{
    double deg;
    double len;
} *Vect;

Vect genVec(double deg,double len);
void drawVec(void *v);
void drawPattern(linkedlistADT vl,double stX,double stY);
void adjustPosition(void *shape,linkedlistADT vl);
void forwd(double distance, double toward);
double PointToLine(double x,double y,Vect vec,double vx,double vy);
double lineDistance(Vect vec,double vx,double vy,double x1,double y1,double x2,double y2);
double Length(double x1,double y1,double x2,double y2);

#endif
