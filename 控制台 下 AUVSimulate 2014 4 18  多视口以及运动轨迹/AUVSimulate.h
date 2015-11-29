//////////////////////////////////////////////////////////////////////////
//  这里加载的是不需要改变的 
#pragma  once
#include "StdAfx.h"
#include "loadimage.h"
#include "vec3.h"
//////////////////////////////////////////////////////////////////////////


//控制黄红绿球 h r b
bool CollasionRed = false;
bool CollasionBlue = false;
bool CollasionYellow = false;

//控制投球  p o i   下落球1 2
bool PitchSphere1 = false;
bool PitchSphere2 = false;
bool PitchSphere3 = false;
bool DropSphere1 = false;
bool DropSphere2 = false;
bool ControlSphere1Stop = false;
bool rotateSpeedForZAix = false;


//控制开始撞球时的轨线  t n s
bool track = false;
bool NextTrack = false;
bool ThirdTrack = false;

GLfloat roty = 0.0f;
GLfloat rotx = 0.0f;
GLfloat rotz = 0.0f;//控制整个场景的视角

GLfloat a = 0.0f;//控制潜器前进或后退
GLfloat b = 0.0f;//控制潜器左转或右转
GLfloat z = 0;
GLfloat g_rotate = 0;
GLfloat visual_distance = 1500;

GLfloat s = 1.0;
GLfloat t = 0.0;
GLfloat stv = 0.0;
GLfloat stb = 0.0;


GLUquadricObj	*qobj;


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#define DIMX 200
#define DIMZ 200
#define SIZE 25
#define length(A) sqrt(A.x*A.x+A.y*A.y+A.z*A.z)

vec3 Terrain[DIMX][DIMZ];

//////////////////////////////////////////////////////////////////////////
void GLInit(bool IsFlat);
void GLReshape(int width,int height);
void Display();
void Draw();
void KeyPressFunc(unsigned char key, int x, int y);
void SpecialKeys(int key, int x, int y);
void DrawTerrain(void);
void InitTerrain(void);
void MoveTrack(void) ;
void circle(float Lradius, float Dradius, float theta , int n);
void IdelPos(void);
void draw1xian();
void draw2xian();
void draw2door();
void Drawqiu();
void draw1Door(float x,float y,float z);
//void draw1Door(float x,float y,float z, float x1,float y1,float z1);
void DrawXian(float x,float y,float z);
void DrawDoor(float x,float y,float z);
void SphereForPitch();
void DrawWater();
void garland();//花环;
void PickCasing();

bool DrawLineLink()   ;
bool DeleteLineLink();

//////////////////////////////////////////////////////////////////////////


void DrawXian(float x,float y,float z)//y=15;
{
	glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0.7,0.3,0.0);
	glVertex3f(x-30,y,z-7);	
	glVertex3f(x+30,y,z-7);
	glVertex3f(x+30,y,z+7);
	glVertex3f(x-30,y,z+7);
	glEnd();
	glPopMatrix();
	glPopAttrib();	
}



void draw1Door(float x,float y,float z)//x=250;y=100,z=0 x为所处x的值，y 为门的高度，z为所在的中心  x1 y1 z1
{
	
	//近视口的柱子
    glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	glColor3f(0,1.0,1.0);
	
	glTranslatef(x,y,z+150);
	
	
	glRotatef(90,1,0,0);
	
	gluCylinder(qobj,12.5,12.5,200,20,20);
	glPopMatrix();
	//远视口的柱子
	glPushMatrix();
	
	
	glTranslatef(x,y,z-150);
	
	glRotatef(90,1,0,0);
	
	gluCylinder(qobj,12.5,12.5,200,20,20);
	glPopMatrix();
	//横梁
	glPushMatrix();
	
	
	glTranslatef(x,y-10,z-150);
	
	gluCylinder(qobj,12.5,12.5,300,20,20);
	glPopMatrix();	
	glPopAttrib();
}


void circle(float Lradius, float Dradius, float theta , int n)
{
	//glEnable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i=0;i<n;i++)
	{
		glTexCoord2f(0,0);
		glVertex3f(0,0,0);
		glTexCoord2f(cos(theta+i),sin(theta+i));
		glVertex3f(Lradius*cos(theta+i),4,Dradius*sin(theta+i));
		glTexCoord2f(cos(theta+i+1),sin(theta+i+1));
		glVertex3f(Lradius*cos(theta+i+1),4,Dradius*sin(theta+i+1));	
	}
	glEnd();

	//glDisable(GL_TEXTURE_2D);
}


void DrawDoor(float x,float y,float z)//z=0  
{
	
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	glColor3f(0,1.0,0.0);
	//	glTranslatef(200,150,90);
	glTranslatef(x,100+y,z+90);
	glRotatef(90,1,0,0);
	gluCylinder(qobj,12.5,12.5,60,20,20);
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(0,1.0,0.0);
	//	glTranslatef(200,150,-90);
	glTranslatef(x,100+y,z-90);
	glRotatef(90,1,0,0);
	gluCylinder(qobj,12.5,12.5,60,20,20);
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(0,1.0,0.0);
	//	glTranslatef(200,40,-90);
	glTranslatef(x,y-10,z-90);
	gluCylinder(qobj,12.5,12.5,180,20,20);
	glPopMatrix();
	//画黑线
	glPushMatrix();
	glColor3f(0.0,0.0,0.0);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex3f(x,y,z+90);
	glVertex3f(x,y+40,z+90);
    glVertex3f(x,y,z-90);
    glVertex3f(x,y+40,z-90);
	glEnd();
	glPopMatrix();
    glPopAttrib();	
	
}

//////////////////////////////////////////////////////////////////////////
// 这些不需要调整  x\z:-2500~+2500
void InitTerrain(void)
{
	int x,z;
	double xi,zi;
	
	for(z=0;z<DIMZ;z++)
	{
		zi=(double)z-((double)DIMZ/2);
		zi=zi*SIZE;//倍数
		for(x=0;x<DIMX;x++)
		{
			xi=(double)x-((double)DIMX/2);
			xi=xi*SIZE;
			Terrain[x][z].x=xi;
			Terrain[x][z].y=0; 
			Terrain[x][z].z=zi;
		}
	}
}

void DrawTerrain(void)
{
	// 	register int x,z;
	// 	register float fk=(float)1/100;
	// 	for(z=0;z<DIMZ-1;z++)
	// 	{
	// 		for(x=0;x<DIMX-1;x++)
	// 		{
	// 			glBegin(GL_QUADS);
	// 			glTexCoord2d( (Terrain[x][z].x+2600)/800,-(Terrain[x][z].z+2600)/800);
	// 			glVertex3f(Terrain[x][z].x,Terrain[x][z].y,Terrain[x][z].z);	
	// 			glTexCoord2d( (Terrain[x][z+1].x+2600)/800, -(Terrain[x][z+1].z+2600)/800 );
	// 			glVertex3f(Terrain[x][z+1].x,Terrain[x][z+1].y,Terrain[x][z+1].z);
	// 			glTexCoord2d( (Terrain[x+1][z+1].x+2600)/800, -(Terrain[x+1][z+1].z+2600)/800 );
	// 			glVertex3f(Terrain[x+1][z+1].x,Terrain[x+1][z+1].y,Terrain[x+1][z+1].z);
	// 			glTexCoord2d( (Terrain[x+1][z].x+2600)/800, -(Terrain[x+1][z].z+2600)/800);
	// 			glVertex3f(Terrain[x+1][z].x,Terrain[x+1][z].y,Terrain[x+1][z].z);
	// 			glEnd();
	// 		}
	// 	}
	
	glBegin(GL_QUADS);
	glTexCoord2f(s,t+stv); glVertex3f(-1500,-5,-1500);
	glTexCoord2f(s,s+stv); glVertex3f(1500,-5,-1500);
	glTexCoord2f(t,s+stv); glVertex3f(1500, -5,1500);
	glTexCoord2f(t,t+stv); glVertex3f(-1500, -5,1500);
	glEnd();
	stv += 0.0001;
	stb += 0.0001;
	
//	glDisable(GL_TEXTURE_2D);
	
}