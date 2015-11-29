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
	for (int loop=0; loop<MAX_PARTICLES; loop++)						// 循环绘制
	{			
		x = bubble[loop].x;											// 定义粒子坐标
		y = bubble[loop].y;
		z = bubble[loop].z;		
		glColor4f(0.5, 0.5, 0.5, bubble[loop].life);	
		glColor3f(0.0,1.0,0.0);
		glBegin(GL_TRIANGLE_STRIP);										// 绘制粒子
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 0.5f, y + 0.5f, z);
		glTexCoord2d(0.0f, 1.0f); glVertex3f(x - 0.5f, y + 0.5f, z);
		glTexCoord2d(1.0f, 0.0f); glVertex3f(x + 0.5f, y - 0.5f, z);
		glTexCoord2d(0.0f, 0.0f); glVertex3f(x - 0.5f, y - 0.5f, z);
		glEnd();							 
		// 粒子位置更新
		bubble[loop].x += bubble[loop].xSpeed/(speedFator*1000.0f);
		bubble[loop].y += bubble[loop].ySpeed/(speedFator*1000.0f);
		bubble[loop].z += bubble[loop].zSpeed/(speedFator*1000.0f);
		// 粒子速度更新
		bubble[loop].xSpeed += bubble[loop].xg/(speedFator*1000.0f);
		bubble[loop].ySpeed += bubble[loop].yg/(speedFator*1000.0f);
		bubble[loop].zSpeed += bubble[loop].zg/(speedFator*1000.0f);
		
		bubble[loop].life -= bubble[loop].fade;	// 粒子生命的衰减 		 	
		if (bubble[loop].life <= 0.0f)			// 如果粒子衰减到0
		{
			bubble[loop].life = 1.0f;				// 赋予新生命
			bubble[loop].fade = ((-1)*float(rand()%3)+96)/10000;
			
// 			bubble[loop].x = float(rand()%10)+50.0f;//
// 			bubble[loop].y = float(rand()%100)-50;
// 			bubble[loop].z = float(-1*(rand()%1000)-130.0f);

		bubble[loop].x = g_AUVPos.x + rand()%5;//35float(-1*rand()%5)-50.0f
	  	bubble[loop].y = g_AUVPos.y + rand()%5 ;//float(rand()%10)+100
		bubble[loop].z =g_AUVPos.z + rand()%5 ;//float(-1*(rand()%10)-85.0f)-80
			
			bubble[loop].xSpeed =0.0f/*+float(rand()%2)*/;
			bubble[loop].ySpeed =1.0f;
			bubble[loop].zSpeed =0.0f;				// z轴速度与方向
			
			bubble[loop].xg = 0.0f;										// 沿x轴的加速度
			bubble[loop].yg = 1.0f;										// 沿y轴的加速度
			bubble[loop].zg = 0.0f;										// 沿z轴的加速度														
		}	
	}


	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);	
	//glPopMatrix();
	glPopAttrib();
}