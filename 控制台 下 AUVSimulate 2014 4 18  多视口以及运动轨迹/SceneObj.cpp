// SceneObj.cpp: implementation of the SceneObj class.
// Load Object to the Scene
// Designer：Anyhow 2012-04-13
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "SceneObj.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
GLfloat	z1=-5.0f;			// Depth Into The Screen
#define WIDTH 100

loadimage Simg;
SceneObj::SceneObj()
{
	//////////////////////////////////////////////////////////////////////////
	qobj1=gluNewQuadric();
}

SceneObj::~SceneObj()
{
	
}

void SceneObj::texture()
{
	Simg.LoadGLTexturesFor();
}

void SceneObj::TopBox()
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D); 
	glBindTexture(GL_TEXTURE_2D,Simg.texture[2]);
	glBegin(GL_QUADS);
	// left Face    底面
	glNormal3f( 0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-30,  3.5, -50);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-30,  3.5,  50);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( -15,  3.5,  50);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( -15,  3.5, -50);
	//right
	glNormal3f( 0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(15,  3.5, -50);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(15,  3.5,  50);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 30,  3.5,  50);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 30,  3.5, -50);
	
	//front face
	glNormal3f( 0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-15,  3.5, -50);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-15,  3.5,  -30);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 15,  3.5,  -30);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 15,  3.5, -50);
	
	//back face
	glNormal3f( 0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-15,  3.5, 30);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-15,  3.5,  50);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 15,  3.5,  50);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 15,  3.5, 30);
	glEnd();
	glPopMatrix();
}

void SceneObj::BottomBox()
{
	glPushMatrix();
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,Simg.texture[2]);
	glBegin(GL_QUADS);
	// left Face
	glNormal3f( 0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-30,  -3.5, -50);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-30,  -3.5,  50);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( -15,  -3.5,  50);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( -15,  -3.5, -50);
	//right
	glNormal3f( 0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(15,  -3.5, -50);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(15,  -3.5,  50);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 30,  -3.5,  50);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 30,  -3.5, -50);
	
	//front face
	glNormal3f( 0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-15,  -3.5, -50);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-15,  -3.5,  -30);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 15,  -3.5,  -30);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 15,  -3.5, -50);
	
	//back face
	glNormal3f( 0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-15,  -3.5, 30);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-15,  -3.5,  50);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 15,  -3.5,  50);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 15,  -3.5, 30);
	glEnd();
	glPopMatrix();
}

void SceneObj::WriteBox()
{
	glPushMatrix();
	glRotatef(90,0,1,0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,Simg.texture[2]);
	glBegin(GL_QUADS);
	// Front Face
	glNormal3f( 0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-30, -3.5,  50);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 30, -3.5,  50);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 30,  3.5,  50);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-30,  3.5,  50);
	// Back Face
	glNormal3f( 0.0f, 0.0f,-1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-30, -3.5, -50);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-30,  3.5, -50);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 30,  3.5, -50);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 30, -3.5, -50);
	// Right face
	glNormal3f( 1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 30, -3.5, -50);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 30,  3.5, -50);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 30,  3.5,  50);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 30, -3.5,  50);
	// Left Face
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-30, -3.5, -50);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-30, -3.5,  50);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-30,  3.5,  50);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-30,  3.5, -50);
	glEnd();
	TopBox();
	BottomBox();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
}

void SceneObj::BlackBox(char* boxT)
{
	glPushMatrix();
	glRotatef(90,0,1,0);
	glBindTexture(GL_TEXTURE_2D,Simg.texture[3]);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	// Front Face
	glNormal3f( 0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-15, -15,  30);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 15, -15,  30);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 15,  3.5,  30);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-15,  3.5,  30);
	glEnd();
	// Back Face
	glNormal3f( 0.0f, 0.0f,-1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-15, -15, -30);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-15,  3.5, -30);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 15,  3.5, -30);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 15, -15, -30);
	glEnd();
	//Right Face
	glNormal3f( 1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 15, -15, -30);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 15,  3.5, -30);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 15,  3.5,  30);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 15, -15,  30);
	// Left Face
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-15, -15, -30);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-15, -15,  30);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-15,  3.5,  30);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-15,  3.5, -30);
	glEnd();
	// Bottom Face
	if(boxT=="DX")glBindTexture(GL_TEXTURE_2D,Simg.texture[4]);
	if(boxT=="XX")glBindTexture(GL_TEXTURE_2D,Simg.texture[5]);
	if(boxT=="DO")glBindTexture(GL_TEXTURE_2D,Simg.texture[6]);
	if(boxT=="XO")glBindTexture(GL_TEXTURE_2D,Simg.texture[7]);
	glBegin(GL_QUADS);
	glNormal3f( 0.0f,-1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-15, -15, -30);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 15, -15, -30);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 15, -15,  30);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-15, -15,  30);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
// 
void SceneObj::Box()
{
	glPushMatrix();//最中间的盒子
	//glTranslatef(0,50,300);
	//glScalef(0.2,0.2,0.2);
	glTranslatef(0,50,0);
	WriteBox();
	BlackBox("DX");
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0,50,100);
	//glScalef(0.2,0.2,0.2);
	WriteBox();
	BlackBox("XX");
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0,50,-100);
	//glScalef(0.2,0.2,0.2);
	WriteBox();
	BlackBox("DO");
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0,50,200);
	//glScalef(0.2,0.2,0.2);
	WriteBox();
	BlackBox("XO");
	glPopMatrix();
}

void SceneObj::redBox()
{
	glPushMatrix(); 
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,Simg.texture[9]);
	glBegin(GL_QUADS);
	// Right face
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.5f, -30.0f, -30.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.5f,  30.0f, -30.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 2.5f,  30.0f,  30.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 2.5f, -30.0f,  30.0f);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D,Simg.texture[8]);
	glBegin(GL_QUADS);
	// Back Face
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.5f, -30.0f, -30.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.5f,  30.0f, -30.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 2.5f,  30.0f, -30.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 2.5f, -30.0f, -30.0f);
	// Top Face
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.5f,  30.0f, -30.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.5f,  30.0f,  30.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.5f,  30.0f,  30.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.5f,  30.0f, -30.0f);
	// Bottom Face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.5f, -30.0f, -30.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 2.5f, -30.0f, -30.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 2.5f, -30.0f,  30.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.5f, -30.0f,  30.0f);
	// Front Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.5f, -30.0f,  30.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.5f, -30.0f,  30.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.5f,  30.0f,  30.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.5f,  30.0f,  30.0f);
	// Left Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.5f, -30.0f, -30.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.5f, -30.0f,  30.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.5f,  30.0f,  30.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.5f,  30.0f, -30.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void SceneObj::blueBox()
{
	glPushMatrix(); 
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,Simg.texture[11]);
	glBegin(GL_QUADS);
	// Left Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.5f, -30.0f, -30.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.5f, -30.0f,  30.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.5f,  30.0f,  30.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.5f,  30.0f, -30.0f);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D,Simg.texture[10]);
	glBegin(GL_QUADS);
	// Back Face
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.5f, -30.0f, -30.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.5f,  30.0f, -30.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 2.5f,  30.0f, -30.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 2.5f, -30.0f, -30.0f);
	// Top Face
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.5f,  30.0f, -30.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.5f,  30.0f,  30.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.5f,  30.0f,  30.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.5f,  30.0f, -30.0f);
	// Bottom Face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.5f, -30.0f, -30.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 2.5f, -30.0f, -30.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 2.5f, -30.0f,  30.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.5f, -30.0f,  30.0f);
	// Front Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.5f, -30.0f,  30.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.5f, -30.0f,  30.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.5f,  30.0f,  30.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.5f,  30.0f,  30.0f);
	// Right face
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.5f, -30.0f, -30.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.5f,  30.0f, -30.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 2.5f,  30.0f,  30.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 2.5f, -30.0f,  30.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}


void SceneObj::CircleBox(int xj,int yj ,int zj)
{
	glPushMatrix();
	glTranslatef(-xj,yj,-zj);
	glScalef(1,2,2);
	glRotatef(-60,0,1,0);
	redBox();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-xj,yj,-zj);
	glScalef(1,2,2);
	glRotatef(-60,0,1,0);
	glTranslatef(-5,0,0);
	blueBox();
	glPopMatrix();
}

void SceneObj::cylinder(float hight, float baseRadius, float topRadius )
{
	
	gluCylinder(qobj1,baseRadius,topRadius,hight,50,50);
}

void SceneObj::Board(float length, float width)
{
	glBegin(GL_QUADS);
	glVertex3f(0,0,0);
	glVertex3f(length,0,0);
	glVertex3f(length,0,width);
	glVertex3f(0,0,width);
	glEnd();
	//glutSolidSphere(10,50,50);
}


void SceneObj:: RenderSkyBox(float sx,float sy,float sz)//显示天空
{
	float width = WIDTH>>1;			// 天空盒的边长
	///////////////////////////////////////////////////////////////////////////////
	glScalef(sx,sy,sz);
	glColor3f(1.0,1.0,1.0);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,Simg.texture[12]);
	//texture(texture[1]);		// 设置BACK贴图左
	glBegin(GL_QUADS);			// 多组独立填充四边形	
	glTexCoord2f(1.0f,0.0f); glVertex3f( width,	-width,	-width);
	glTexCoord2f(1.0f,1.0f); glVertex3f( width,	 width, -width); 
	glTexCoord2f(0.0f,1.0f); glVertex3f(-width,	 width, -width);
	glTexCoord2f(0.0f,0.0f); glVertex3f(-width,	-width,	-width);
	glEnd();
	//	texture(texture[1]);		// 设置FRONT贴图右
//	glBindTexture(GL_TEXTURE_2D,Simg.texture[2]);
	glBegin(GL_QUADS);			// 多组独立填充四边形
	glTexCoord2f(1.0f,0.0f); glVertex3f(-width,	-width,	width);
	glTexCoord2f(1.0f,1.0f); glVertex3f(-width,	 width, width);
	glTexCoord2f(0.0f,1.0f); glVertex3f( width,	 width, width); 
	glTexCoord2f(0.0f,0.0f); glVertex3f( width,	-width,	width);
	glEnd();
	
	//	texture(texture[1]);		// 设置TOP贴图顶
	//glBindTexture(GL_TEXTURE_2D,Simg.texture[3]);
	glBegin(GL_QUADS);			// 多组独立填充四边形		
	glTexCoord2f(0.0f,1.0f); glVertex3f( width, width, -width);
	glTexCoord2f(0.0f,0.0f); glVertex3f( width, width,  width); 
	glTexCoord2f(1.0f,0.0f); glVertex3f(-width,	width,  width);
	glTexCoord2f(1.0f,1.0f); glVertex3f(-width,	width, -width);
	glEnd();
	//	texture(texture[1]);		// 设置LEFT贴图前
	glBegin(GL_QUADS);			// 多组独立填充四边形
	//glBindTexture(GL_TEXTURE_2D,Simg.texture[4]);
	glTexCoord2f(1.0f,1.0f); glVertex3f(-width,	 width, -width);	
	glTexCoord2f(0.0f,1.0f); glVertex3f(-width,	 width,  width); 
	glTexCoord2f(0.0f,0.0f); glVertex3f(-width,	-width,	 width);
	glTexCoord2f(1.0f,0.0f); glVertex3f(-width,	-width,	-width);		
	glEnd();
	//	texture(texture[1]);		// 设置RIGHT贴图后
	//glBindTexture(GL_TEXTURE_2D,Simg.texture[5]);
	glBegin(GL_QUADS);			// 多组独立填充四边形		
	glTexCoord2f(0.0f,0.0f); glVertex3f(width, -width, -width);
	glTexCoord2f(1.0f,0.0f); glVertex3f(width, -width,	width);
	glTexCoord2f(1.0f,1.0f); glVertex3f(width,	width,	width); 
	glTexCoord2f(0.0f,1.0f); glVertex3f(width,	width, -width);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}



//////////////////////////////////////////////////////////////////////////
//
//  for  water










