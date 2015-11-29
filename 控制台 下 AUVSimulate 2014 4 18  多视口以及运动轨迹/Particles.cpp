#include "StdAfx.h"
#include "vec3.h"
#include "Particles.h"

GLfloat	speedFator = 0.033f;
PARTICLES bubble[MAX_PARTICLES];

extern vec3 g_AUVPos ;//vec3 g_AUVPos = vec3(400,100,700);

void BubbleInit(void)
{

//	glPushMatrix();
//	glTranslatef(100,0,100);
	for (int loop =0;loop<MAX_PARTICLES; loop++)
	{
		bubble[loop].life=1.0f;
		bubble[loop].fade=float(rand()%100)/20000.0f+0.0003f;
// 		bubble[loop].x = float(rand()%10)+50.0f;//35
// 		bubble[loop].y = float(rand()%100)-50;
// 		bubble[loop].z = float(-1*(rand()%100)-85.0f)-130;

		bubble[loop].x = g_AUVPos.x;//35float(-1*rand()%5)-30.0f
		bubble[loop].y = g_AUVPos.y;//float(rand()%10)+100
		bubble[loop].z = g_AUVPos.z;//float(-1*(rand()%10)-85.0f)-80
		
		bubble[loop].xSpeed =0.0f;
		bubble[loop].ySpeed =1.0f+float(rand()%2);
		bubble[loop].zSpeed =0.0f;
		
		bubble[loop].xg =0.0f;
		bubble[loop].yg =-9.8f;
		bubble[loop].zg =0.0f;	
		
	}
//	glPopMatrix();
}


void DrawBubble(void)
{	
	glPushAttrib(GL_CURRENT_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);	
	glEnable(GL_TEXTURE_2D);		
	glDisable(GL_DEPTH_TEST);
    float x,y,z;
	for (int loop=0; loop<MAX_PARTICLES; loop++)						// ѭ������
	{			
		x = bubble[loop].x;											// ������������
		y = bubble[loop].y;
		z = bubble[loop].z;		
		glColor4f(0.5, 0.5, 0.5, bubble[loop].life);	
		glColor3f(0.0,1.0,0.0);
		glBegin(GL_TRIANGLE_STRIP);										// ��������
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 0.5f, y + 0.5f, z);
		glTexCoord2d(0.0f, 1.0f); glVertex3f(x - 0.5f, y + 0.5f, z);
		glTexCoord2d(1.0f, 0.0f); glVertex3f(x + 0.5f, y - 0.5f, z);
		glTexCoord2d(0.0f, 0.0f); glVertex3f(x - 0.5f, y - 0.5f, z);
		glEnd();							 
		// ����λ�ø���
		bubble[loop].x += bubble[loop].xSpeed/(speedFator*1000.0f);
		bubble[loop].y += bubble[loop].ySpeed/(speedFator*1000.0f);
		bubble[loop].z += bubble[loop].zSpeed/(speedFator*1000.0f);
		// �����ٶȸ���
		bubble[loop].xSpeed += bubble[loop].xg/(speedFator*1000.0f);
		bubble[loop].ySpeed += bubble[loop].yg/(speedFator*1000.0f);
		bubble[loop].zSpeed += bubble[loop].zg/(speedFator*1000.0f);
		
		bubble[loop].life -= bubble[loop].fade;	// ����������˥�� 		 	
		if (bubble[loop].life <= 0.0f)			// �������˥����0
		{
			bubble[loop].life = 1.0f;				// ����������
			bubble[loop].fade = ((-1)*float(rand()%3)+96)/10000;
			
// 			bubble[loop].x = float(rand()%10)+50.0f;//
// 			bubble[loop].y = float(rand()%100)-50;
// 			bubble[loop].z = float(-1*(rand()%1000)-130.0f);

		bubble[loop].x = g_AUVPos.x + rand()%5;//35float(-1*rand()%5)-50.0f
	  	bubble[loop].y = g_AUVPos.y + rand()%5 ;//float(rand()%10)+100
		bubble[loop].z =g_AUVPos.z + rand()%5 ;//float(-1*(rand()%10)-85.0f)-80
			
			bubble[loop].xSpeed =0.0f/*+float(rand()%2)*/;
			bubble[loop].ySpeed =1.0f;
			bubble[loop].zSpeed =0.0f;				// z���ٶ��뷽��
			
			bubble[loop].xg = 0.0f;										// ��x��ļ��ٶ�
			bubble[loop].yg = 1.0f;										// ��y��ļ��ٶ�
			bubble[loop].zg = 0.0f;										// ��z��ļ��ٶ�														
		}	
	}


	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);	
	//glPopMatrix();
	glPopAttrib();
}