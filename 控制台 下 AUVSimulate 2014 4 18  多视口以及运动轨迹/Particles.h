#pragma once
#define	MAX_PARTICLES	500


typedef struct 
{
	float	life;														// ��������
	float	fade;														// ����˥���ٶ�
	float	r,g,b;														// ���ӵ���ɫ
	float	x,y,z;														// ����λ��
	float	xSpeed,ySpeed,zSpeed;										// ���ӵ��ٶ�
	float	xg,yg,zg;													// ���ӵ��˶����ٶ�	
} PARTICLES;