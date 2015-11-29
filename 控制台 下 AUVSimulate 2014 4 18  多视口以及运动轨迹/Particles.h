#pragma once
#define	MAX_PARTICLES	500


typedef struct 
{
	float	life;														// 粒子生命
	float	fade;														// 粒子衰减速度
	float	r,g,b;														// 粒子的颜色
	float	x,y,z;														// 粒子位置
	float	xSpeed,ySpeed,zSpeed;										// 粒子的速度
	float	xg,yg,zg;													// 粒子的运动加速度	
} PARTICLES;