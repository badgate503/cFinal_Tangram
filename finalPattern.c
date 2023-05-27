/*
 * makeShape.c -- 图形相关操作函数的实现
 */
  
#include <math.h>
#include <windef.h>
#include "extgraph.h"
#include "finalPattern.h"
#include "tangramMain.h"
#include "linkedlist.h"

extern double sX,sY;

Vect genVec(double deg,double len)
{
	Vect vec = New(Vect);
	vec->deg = deg;
	vec->len = len;
	return vec;
}

void drawVec(void *v)
{
	if (v == NULL) return;
	Vect vec = (Vect)v;
	forwd(vec->len, vec->deg);
}

void drawPattern(linkedlistADT vl, double stX,double stY)
{
	MovePen(stX,stY);
	string pk = GetPenColor();
	SetPenColor("black");
	TraverseLinkedList(vl, drawVec);
	SetPenColor(pk);
}

void adjustPosition(void *shape,linkedlistADT vl)
{
	if (shape == NULL) return;
	Shape shp = (Shape)shape;
	Vect vec = New(Vect);
	linkedlistADT p;
	//p=New(linkedlistADT);
	p=NewLinkedList();
	p=vl;
	
	double distance;
	double x1,y1,vX,vY;
	x1=shp->vertex[0]->x;
	y1=shp->vertex[0]->y;
	vX=sX;
	vY=sY;
	
	if(shp->shapeType <= 2)
	{
		while(p != NULL){
			vec = NodeObj(vl,p);
			p = NextNode(vl,p);
			
			if((int)(vec->deg-shp->rotDeg+135)%180 == 0)
			{
				distance=lineDistance(vec , vX , vY , shp->vertex[0]->x , shp->vertex[0]->y , shp->vertex[1]->x , shp->vertex[1]->y);
				if(distance>0.01 || distance==0){
					vX += cos(degToRad(vec->deg))*vec->len;
					vY += sin(degToRad(vec->deg))*vec->len;
					continue;
				}
				
				if(PointToLine(shp->x,shp->y,vec,vX,vY) > pow(1.414213562 , shp->shapeType)){
					shp->x += distance*cos(degToRad(shp->rotDeg+45));
					shp->y += distance*sin(degToRad(shp->rotDeg+45));
				}else{
					shp->x += distance*cos(degToRad(shp->rotDeg-135));
					shp->y += distance*sin(degToRad(shp->rotDeg-135));
				}
			}
			else if((int)(vec->deg-shp->rotDeg-135)%180 == 0)
			{
				distance=lineDistance(vec , vX , vY , shp->vertex[0]->x , shp->vertex[0]->y , shp->vertex[2]->x , shp->vertex[2]->y);
				if(distance>0.01 || distance==0){
					vX += cos(degToRad(vec->deg))*vec->len;
					vY += sin(degToRad(vec->deg))*vec->len;
					continue;
				}
				
				if(PointToLine(shp->x,shp->y,vec,vX,vY) > pow(1.414213562 , shp->shapeType)){
					shp->x += distance*cos(degToRad(shp->rotDeg-45));
					shp->y += distance*sin(degToRad(shp->rotDeg-45));
				}else{
					shp->x += distance*cos(degToRad(shp->rotDeg+135));
					shp->y += distance*sin(degToRad(shp->rotDeg+135));
				}
			}
			else if((int)(vec->deg-shp->rotDeg+90)%180 == 0)
			{
				distance=lineDistance(vec , vX , vY , shp->vertex[1]->x , shp->vertex[1]->y , shp->vertex[2]->x , shp->vertex[2]->y);
				if(distance>0.01 || distance==0){
					vX += cos(degToRad(vec->deg))*vec->len;
					vY += sin(degToRad(vec->deg))*vec->len;
					continue;
				}
				
				if(PointToLine(x1,y1,vec,vX,vY) > pow(1.414213562 , shp->shapeType-1)){
					shp->x += distance*cos(degToRad(shp->rotDeg-180));
					shp->y += distance*sin(degToRad(shp->rotDeg-180));
				}else{
					shp->x += distance*cos(degToRad(shp->rotDeg));
					shp->y += distance*sin(degToRad(shp->rotDeg));
				}
			}
			
			vX += cos(degToRad(vec->deg))*vec->len;
			vY += sin(degToRad(vec->deg))*vec->len;
		}
	}
	else if(shp->shapeType == 3)
	{
		while(p != NULL){
			vec = NodeObj(vl,p);
			p = NextNode(vl,p);
			double distanceAnother;
			
			if((int)(vec->deg - shp->rotDeg + 90)%180 == 0)
			{
				distance=lineDistance(vec , vX , vY , shp->vertex[0]->x , shp->vertex[0]->y , shp->vertex[3]->x , shp->vertex[3]->y);
				distanceAnother=lineDistance(vec, vX , vY , shp->vertex[1]->x , shp->vertex[1]->y , shp->vertex[2]->x , shp->vertex[2]->y);
				
				if((distance>0.01 || distance==0) && (distanceAnother>0.01 || distanceAnother==0)){
					vX += cos(degToRad(vec->deg))*vec->len;
					vY += sin(degToRad(vec->deg))*vec->len;
					continue;
				}
				else if(!(distance>0.01 || distance==0))
				{
					if(PointToLine(shp->x,shp->y,vec,vX,vY) > 0.5){
						shp->x += distance*cos(degToRad(shp->rotDeg));
						shp->y += distance*sin(degToRad(shp->rotDeg));
					}else{
						shp->x += distance*cos(degToRad(shp->rotDeg-180));
						shp->y += distance*sin(degToRad(shp->rotDeg-180));
					}
				}
				else if(!(distanceAnother>0.01 || distanceAnother==0))
				{
					if(PointToLine(shp->x,shp->y,vec,vX,vY) > 0.5){
						shp->x += distance*cos(degToRad(shp->rotDeg-180));
						shp->y += distance*sin(degToRad(shp->rotDeg-180));
					}else{
						shp->x += distance*cos(degToRad(shp->rotDeg));
						shp->y += distance*sin(degToRad(shp->rotDeg));
					}
				}
			}
			else if((int)(vec->deg - shp->rotDeg)%180 == 0)
			{
				distance=lineDistance(vec , vX , vY , shp->vertex[0]->x , shp->vertex[0]->y , shp->vertex[1]->x , shp->vertex[1]->y);
				distanceAnother=lineDistance(vec, vX , vY , shp->vertex[3]->x , shp->vertex[3]->y , shp->vertex[2]->x , shp->vertex[2]->y);
				
				if((distance>0.01 || distance==0) && (distanceAnother>0.01 || distanceAnother==0)){
					vX += cos(degToRad(vec->deg))*vec->len;
					vY += sin(degToRad(vec->deg))*vec->len;
					continue;
				}
				else if(!(distance>0.01 || distance==0))
				{
					if(PointToLine(shp->x,shp->y,vec,vX,vY) > 0.5){
						shp->x += distance*cos(degToRad(shp->rotDeg+90));
						shp->y += distance*sin(degToRad(shp->rotDeg+90));
					}else{
						shp->x += distance*cos(degToRad(shp->rotDeg-90));
						shp->y += distance*sin(degToRad(shp->rotDeg-90));
					}
				}
				else if(!(distanceAnother>0.01 || distanceAnother==0))
				{
					if(PointToLine(shp->x,shp->y,vec,vX,vY) > 0.5){
						shp->x += distance*cos(degToRad(shp->rotDeg-90));
						shp->y += distance*sin(degToRad(shp->rotDeg-90));
					}else{
						shp->x += distance*cos(degToRad(shp->rotDeg+90));
						shp->y += distance*sin(degToRad(shp->rotDeg+90));
					}
				}
			}
			
			vX += cos(degToRad(vec->deg))*vec->len;
			vY += sin(degToRad(vec->deg))*vec->len;
		}
	}
	else if(shp->shapeType ==4)
	{
		
	}
}

/*
 * Function: forward
 * Usage: forward(distance);
 * -----------------------------------
 * Draw a line along the current direction, 
 * the length is distance, back when distance 
 * is negative
 */

void forwd(double distance, double toward)
{
	double movx = distance * cos(degToRad(toward));
	double movy = distance * sin(degToRad(toward));
	DrawLine(movx,movy);
}

double PointToLine(double x,double y,Vect vec,double vX,double vY)
{
	double x1,y1,x2,y2,s,result;
	x1=vX-x;
	y1=vY-y;
	x2=vec->len * cos(degToRad(vec->deg));
	y2=vec->len * sin(degToRad(vec->deg));
	
	s=x1*y2-y1*x2;
	result=s/(vec->len);
	
	double dMax,tailX,tailY;
	tailX=vX+x2;
	tailY=vY+y2;
	dMax=pow(pow(result,2)+pow(vec->len,2) , 0.5);
	if(Length(x,y,vX,vY)>dMax || Length(x,y,tailX,tailY)>dMax){
		return 0;
	}else{
		return result;
	}
}

double Length(double x1,double y1,double x2,double y2)
{
	return pow(pow(x1-x2,2)+pow(y1-y2,2) , 0.5);
}

double lineDistance(Vect vec,double vX,double vY,double x1,double y1,double x2,double y2)
{
	if(PointToLine(x1,y1,vec,vX,vY) != 0){
		return PointToLine(x1,y1,vec,vX,vY);
	}else if(PointToLine(x2,y2,vec,vX,vY) != 0){
		return PointToLine(x2,y2,vec,vX,vY);
	}else{
		return 0;
	}
}
