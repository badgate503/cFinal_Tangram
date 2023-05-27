/*
 * makeShape.c -- 图形相关操作函数的实现
 */
  
#include <math.h>
#include <windef.h>
#include "extgraph.h"
#include "tGui.h"
#include "tangramMain.h"

double aT, aL;


Button genBtn(double top,double left,double width,double height,string label,int fontSize)
{
	Button gBtn = New(Button);
	gBtn->top = top;
	gBtn->left = left;
	gBtn->width = width;
	gBtn->height = height;
	gBtn->isShow = TRUE;
	gBtn->floatAbove = FALSE;
	gBtn->isClicked = FALSE;
	gBtn->label = label;
	gBtn->fontSize = fontSize;
    return gBtn;
}

void renderBtn(Button btn)
{
	aT = GetWindowHeight() - btn->top;
	aL = btn->left;
	SetFont("arial");
	SetPointSize(btn->fontSize);
	MovePen(aL + (btn->width - TextStringWidth(btn->label)) / 2, aT - (btn->height + (1.0*btn->fontSize/200)) / 2);
	SetPenColor("btn_text");
	DrawTextString(btn->label);
	MovePen(aL + (btn->width - TextStringWidth(btn->label)) / 2, aT - (btn->height + (1.0*btn->fontSize/200)) / 2 - 0.07);
	SetPenColor(btn->isClicked ? "btn_clicked" : (btn->floatAbove ? "btn_above" : "btn_normal"));
	StartFilledRegion(1);
	DrawLine(TextStringWidth(btn->label),0);
	DrawLine(0,-0.05);
	DrawLine(-TextStringWidth(btn->label),0);
	DrawLine(0,0.05);
	EndFilledRegion();
	
}

bool isInsideBtn(Button btn, double x, double y)
{
	aT = GetWindowHeight() - btn->top;
	aL = btn->left;
	return (x >= aL) && (x <= aL + btn->width) && (y <= aT) &&(y >= aT - btn->height);
}

void displayIllustrate(bool isDisplayI)
{
	int i=0; 
	string text[9];
	text[0]=(string)CopyString("七巧板游戏（tgm），共有10种");
	text[1]=(string)CopyString("游戏可以选择，也可以选择自");
	text[2]=(string)CopyString("定义图形。可通过移动或旋转"); 
	text[3]=(string)CopyString("板块之后填满目标图形则游戏");
	text[4]=(string)CopyString("挑战成功，每个游戏都有相应");
	text[5]=(string)CopyString("的时间限制，超过时间未完成");
	text[6]=(string)CopyString("则挑战失败。游戏可以保存当"); 
	text[7]=(string)CopyString("前游戏进度，加载上一次的游"); 
	text[8]=(string)CopyString("戏记录。按下任意键可以关闭");
	if(isDisplayI){
		SetPenColor("Red");
		MovePen(GetWindowWidth() * 0.16,GetWindowHeight() * 0.45);
		for(;i<9;i++)
		{
			//SetPenSize(0); 
			DrawTextString(text[i]);
			MovePen(GetWindowWidth() * 0.16,GetCurrentY()-GetWindowHeight() * 0.05);
		}
	}else{
		clearArea(GetWindowWidth() * 0.16,GetWindowHeight() * 0.04,TextStringWidth(text[0]),GetWindowHeight()*0.45);
	}
}
