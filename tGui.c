/*
 * makeShape.c -- ͼ����ز���������ʵ��
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
	text[0]=(string)CopyString("���ɰ���Ϸ��tgm��������10��");
	text[1]=(string)CopyString("��Ϸ����ѡ��Ҳ����ѡ����");
	text[2]=(string)CopyString("����ͼ�Ρ���ͨ���ƶ�����ת"); 
	text[3]=(string)CopyString("���֮������Ŀ��ͼ������Ϸ");
	text[4]=(string)CopyString("��ս�ɹ���ÿ����Ϸ������Ӧ");
	text[5]=(string)CopyString("��ʱ�����ƣ�����ʱ��δ���");
	text[6]=(string)CopyString("����սʧ�ܡ���Ϸ���Ա��浱"); 
	text[7]=(string)CopyString("ǰ��Ϸ���ȣ�������һ�ε���"); 
	text[8]=(string)CopyString("Ϸ��¼��������������Թر�");
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
