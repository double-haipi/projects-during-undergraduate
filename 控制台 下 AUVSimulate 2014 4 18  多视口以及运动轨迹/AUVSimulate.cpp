// AUVSimulate.cpp : Defines the entry point for the console application.
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
///
//    实现了潜器撞球 过门 投靶 掉球 抓取 等动作
//    能实现潜器自转前进

//			快捷键
//     h键开始运动  启动 暂停
///   快捷键 改变视口 
//    c键 改变视口 
//    b键 撞绿球
//    r键 撞红球
//    k键 潜器自转

//    p o i 键投球射靶
//    m 选择右侧花环  n 选择左侧花环
//    1 3 掉球  2 键 掉球时 平移潜器
//    -> <-  上键 下键控制前进后退 左右平移
//    made by  陈新华  张建国  黄乐 @408 仿生微机器人实验室
//    						
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AUVSimulate.h"
#include "3DS.H"
#include "vec3.h"
#include "SceneObj.h"
#include "skybox.h"
//#include "Particles.h"
#include <iostream>
using namespace std;

#include "glFrame.h"  

int width = 0;  
int height = 0;
  
bool isVisible = true;  // whether the border is visible or not, by left button  

void paintCenter(); 
void paintViewportLeft();  
void paintViewportRight(); 
void paintViewportRight1(); 
void paintGL();


//////////////////////////////////////////////////////////////////////////

//     添加动量冲量  2012 6 12
#define MASSOFAUV				10            //Auv质量
#define MASSOFBALL				0.05          //被撞球的质量
#define MAXFORCEFROMLINE        100           // 被撞球被绳子拉的最大拉力
#define RESISTANCECoFFICIENT	0.05          // 水的摩擦系数    
  

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////


CLoad3DS m_3ds;
loadimage ye;
SceneObj m_obj;
int  path=0;
const float PI = 3.1415926;
float fogStart = 300;
float fogEnd = 1500;
float rotateY =  0;
float lookAtRotateAlongY ;
float x = 0;
float y = 0;
float h = 0;

vec3 eye = vec3(0,0,0);
vec3 ForYellowLookAt = vec3(0,0,0);
vec3 center = vec3(0,0,0);
vec3 g_AUVPos = vec3(415,100,700);//vec3 g_AUVPos = vec3(400,100,700);
vec3 g_AUVPosForDropSphere2 = vec3(410,100,710);//为控制下落球1做准备
vec3 g_AUVPosForDropSphere1 = vec3(410,100,720);  // 下落球2 

vec3 g_vSpherePos1 = vec3(450,120,370);   //被撞球1 位置    红球
vec3 g_vSpherePos2 = vec3(480,100,360 );  //被撞球2 位置     黄
vec3 g_vSpherePos3 = vec3(420,80,350);   //被撞球3 位置     绿
vec3 g_AuvMicroY = vec3(0,0,0);     //撞完绿球后 AUV自动调节高度值
vec3 g_ChangeEyeForBoxes = vec3(0,0,0);

vec3 g_AdjustVelocityLookAtForNotRotate = vec3(0,0,0);

vec3 g_AdjustLookAtForNotRotateThirdDoor = vec3(0,0,0);
vec3 g_AdjustVelocityLookAtForNotRotateThirdDoor = vec3(0,0,0);

vec3 g_vPitchSphereMove1 = vec3(0,0,0);  // 投掷球运动
vec3 g_vPitchSphereMove2 = vec3(0,0,0);  
vec3 g_vPitchSphereMove3 = vec3(0,0,0);

vec3 g_vDropSphereMove1 = vec3(0,0,0);  //下落球运动
vec3 g_vDropSphereMove2 = vec3(0,0,0);


vec3 g_AUVVelocity = vec3(0,0,-0.5*3 );  // 潜器没被控制前运动速度0.014,0.0,-0.2  // 成以2了 
vec3 g_AUVVelocityForDropSphere1 = g_AUVVelocity; //vec3(0.0,0.0,-0.5)
vec3 g_AUVVelocityForDropSphere2 = g_AUVVelocity;//0.0,0.-0,5 这么个错误让我调试了很久 以后注意这些小细节vec3(0.0,0,-0.5)
vec3 g_BubbleVelocityAloneToControl = vec3(0,0,0);

vec3 g_GarlandPosLeft = vec3(-600,80,200);
vec3 g_GarlandVelocityLeft = vec3(0,0,0);

vec3 g_GarlandPosRight = vec3(-550,80,50);//改动了 zcc
vec3 g_GarlandVelocityRight = vec3(0,0,0);


vec3 g_Sphere1Velocity = vec3(0,0.0,0.0);
vec3 g_Sphere2Velocity = vec3(0.0,0.0,0.0);
vec3 g_Sphere3Velocity = vec3(0.0,0.0,0.0);
vec3 g_AuvMicroControl = vec3(0,0,0);
vec3 g_AuvTranslationAlongZ = vec3(0,0,0);
vec3 g_AuvTowardGarlandLookAt = vec3(0,0,0);
vec3 g_AuvAjustLookAtForDeepSea = vec3(0,0,0);
vec3 g_AjustLookAtForBlueSphere = vec3(0,0,0);
vec3 g_AjustLookAtForLastTarget = vec3(0,0,0);
vec3 g_AdjustVel = vec3(0,0,0);
vec3 g_AdjustEye = vec3(0,0,0);
vec3 g_AdjustEye1 = vec3(0,0,0);
vec3 casingMov = vec3(0,0,0);


bool stop = false;
bool stop1 = false;
bool stop2 = false;
bool isChangeLookAt = false; 
static bool isBackYellow = false;
static bool isBackRed = false;
static bool isBackBlue = false;
bool isBackForPitch = false;
bool isGoToDeepSea = false;
bool isGoToShallowSea = true;
bool isGoToSecondDoor = false;
bool isRightGarlandMove = false;
bool isLeftGarlandMove = false;
bool isLeftMouseDown = false;
bool isRightMouseDown = false;
bool isBPostive = true;
bool IsBNegtive = false;
bool IsTempChangeAUVY = false;
bool IsRotateToSecondDoor = false;
bool IsMicaoControlAuvY = false;
bool IsControlAUVBackSphereDrop = false;
bool IsControlAuvBackRedSphereDrop = false;
bool IsControlAuvBackYellowSphereDrop = false;
bool IsChangeAuvVelocity = false;
bool IsStopDropingRedSphere = false;
bool IsStopDropingYellowSphere = false;
bool IsStopControlAuvMoveRed = true;
bool IsStopControlAuvMoveYellow = true;
bool IsControlAuvUp = false;
bool IstTurnToDeepSea = false;
bool IsGlobalControl = true;
bool IsControlLastStop = false;
bool isChangeLookAtForOverlook = false;
bool IsChangeLookAtForFront = false;
bool IsStopToRotateSecondDoor = false;
bool isStopToRotateBox = false;
bool isControlAuvForRedRotateAndUp = true;
bool isControlAuvForRedRotate = false;

bool isControlAuvForBlueRotateAndDown = true;
bool isControlAuvForBlueRotate = false;
bool isAgainControlAuvMoveToThirdDoor = false;
bool IsStopRotateAndChangeLookAtForSecondDoor = false;
bool IsGoToLeftForTheGarland = false;
bool IsGoToRightForTheGarland = false;
bool IsChangeDirectionForGarland = false;	
bool IsGoNotRotateForLeftGarland = false;
bool IsGoNotRotateForRightGarland = false;
bool IsChangeLookAtType = false;
bool xa = false;
bool isLeft = false;
bool isRight = false;
bool isLeftPickCasing = false;
bool isRightPichCasing = false;
bool start = false;


float a1;
float b1;
float c1;

//int Camtype = 0;
enum  EYETYPE  {BACK,FRONT,LEFT,RIGHT,DOWN, DETAILFORPICK
};
EYETYPE cam ;

static int camer = 1;
float shoulder = 60;
float elbow = 150;

 

void BubbleInit();
void DrawBubble();


#define	MAX_PARTICLES	500


//////////////////////////////////////////////////////////////////////////
typedef struct linelink    //机器人运动跟踪线
{
	GLfloat x;		
	GLfloat y;		
	GLfloat z;		
	struct linelink * next;
}lineLink; 

typedef struct 
{
	float	life;														// 粒子生命
	float	fade;														// 粒子衰减速度
	float	r,g,b;														// 粒子的颜色
	float	x,y,z;														// 粒子位置
	float	xSpeed,ySpeed,zSpeed;										// 粒子的速度
	float	xg,yg,zg;													// 粒子的运动加速度	
} PARTICLES;

GLfloat	speedFator = 0.033f;
PARTICLES bubble[MAX_PARTICLES];
lineLink * headline=NULL,* tailline=NULL;   //同上，lineLink{x,y,z,*next}，用来画轨迹线的

//extern vec3 g_AUVPos ;//vec3 g_AUVPos = vec3(400,100,700);

//500个气泡
void BubbleInit(void)
{
	for (int loop =0;loop<MAX_PARTICLES; loop++)
	{
		bubble[loop].life=1.0f;
		bubble[loop].fade=float(rand()%100)/20000.0f+0.0003f;//0.0003~0.0053

		//AUV的位置即为其中心点的位置
		bubble[loop].x =g_AUVPos.x + rand()%10;
		bubble[loop].y = g_AUVPos.y;
		bubble[loop].z = -g_AUVPos.z +rand()%10;
		
		bubble[loop].xSpeed =0.0f;
		bubble[loop].ySpeed =1.0f+float(rand()%2);//1~3
		bubble[loop].zSpeed =0.0f;
		
		bubble[loop].xg =0.0f;
		bubble[loop].yg =-9.8f;
		bubble[loop].zg =0.0f;	
	}
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
	//	glColor3f(1.0,1.0,1.0);
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
			
			bubble[loop].x = g_AUVPos.x + rand()%20;
			bubble[loop].y = g_AUVPos.y;
			bubble[loop].z = g_AUVPos.z + rand()%20;
			
			bubble[loop].xSpeed =0.0f;
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

void wave()
{
	
}

// //////////////////////////////////////////////////////////////////////////
//GLenum mode = GL_LINEAR;
//////////////////////////////////////////////////////////////////////////

//  计算向量时用到的公式
//////////////////////////////////////////////////////////////////////////
float SqrLength(vec3 vec) 
{ 
	return (vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
 }


float Length(vec3 vec) 
{	
	return (float)sqrt(SqrLength(vec)); 
}


vec3  Normalize(vec3 x)
{
	vec3 temp;
	float temp1;
	temp.x = x.x;
	temp.y = x.y;
	temp.z = x.z;
	temp1 = Length(temp);
	temp.x = temp.x/temp1;
	temp.y = temp.y/temp1;
	temp.z = temp.z/temp1;
	return temp;
}


float DoProduct(vec3 x1, vec3 y1)
{
	return (x1.x*y1.x+x1.y*y1.y+x1.z*y1.z);
}



float TwoVectorAngle(vec3 x1, vec3 y1)// 返回的是弧度制
{
	float temp;
	float cosAngle;
	temp = DoProduct(x1,y1);
	cosAngle = temp/(Length(x1)*Length(y1));
	return acos(cosAngle);
}

float convertAngle(float angle)// 弧度转换成角度
{
	return( angle*180/3.1415926 );
}

//////////////////////////////////////////////////////////////////////////
void DrawHand()
{
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	glPushMatrix();
	glScalef(10,10,10);
	glColor3f(0.15,0.0,0.0);
	glTranslatef(-1.0,0.0,0.0);
	glRotatef(shoulder,0,0,1);
	glTranslatef(0.15,0.0,0.0);
	glPushMatrix();
	glScalef(0.3,0.02,0.01);
	glutWireCube(1.0);
	glPopMatrix();
	glTranslatef(0.15,0.0,0.0);
	glRotatef(elbow,0,0,1.0);
	glTranslatef(0.15,0.0,0.0);
	glPushMatrix();
	glScalef(0.3,0.02,0.01);
	glutWireCube(1);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glPopAttrib();
	
}
//////////////////////////////////////////////////////////////////////////


void GLInit(bool IsFlat)
{
	//////////////////////////////////////////////////////////////////////////
	m_3ds = *new CLoad3DS();
	m_obj.texture();
	
	ye.LoadGLTexturesFor();
	
	glShadeModel(GL_SMOOTH);
	float fog_r = 70.f/255.f;
	float fog_g = 180.f/255.f;
	float fog_b = 220.f/255.f;
	
	glClearColor(fog_r, fog_g, fog_b, 1);			// 黑背景颜色
	glBlendFunc(GL_SRC_ALPHA,GL_DST_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	
	//光照
	GLfloat lightPos1[]={0.0f,4.0f,-1.0f,0.0f};//光的位置
	GLfloat LightAmb[]={0.4f,0.4f,0.4f,1.0f};//环境光的颜色
	GLfloat LightDif[]={1.0f,1.0f,1.0f,1.0f};//漫反射光的颜色
	GLfloat MatAmb[]={0.7f,0.7f,0.7f,1.0f};//材质的环境光颜色
	GLfloat MatDif[]={1.0f,1.0f,1.0f,1.0f};//材质的漫反射光颜色
    GLfloat matShininess[] = { 5.0 };
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDif);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDif);// 设置漫射光成分，点光源
	glLightfv(GL_LIGHT0,GL_AMBIENT,LightAmb);
 	glMaterialfv(GL_FRONT,GL_SHININESS,matShininess);
   
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	
	//////////////////////////////////////////////////////////////////////////
	GLuint	fogMode[]= { GL_EXP, GL_EXP2, GL_LINEAR };	// 保存三种雾的模式
	GLuint	fogfilter = 0;								// 当前使用的雾的模式 
	GLfloat	fogColor[4] = {fog_r, fog_g, fog_b, 1};		// 雾的颜色
	
	glFogi(GL_FOG_MODE, fogMode[2]);			        // 设置雾的模式
	glFogfv(GL_FOG_COLOR, fogColor);					// 设置雾的颜色
	glFogf(GL_FOG_DENSITY, 0.3024f);						// 设置雾的浓度
	glHint(GL_FOG_HINT, GL_NICEST);					    // Fog Hint Value
	glFogf(GL_FOG_START, 300.0f);						// 设置雾的开始深度
	glFogf(GL_FOG_END, visual_distance);				// 设置雾的结束深度
	glEnable(GL_FOG);
	
	//////////////////////////////////////////////////////////////////////////
	
	glEnable(GL_COLOR_MATERIAL); 
	glClearDepth(1.0f);					
	glEnable(GL_DEPTH_TEST);
	qobj=gluNewQuadric();//用来绘制二次曲面对象
	InitTerrain();
	
	glPushMatrix();
	glTranslatef(0,0,0);

	glScalef(10,10,10);//气泡绘制时放缩
	BubbleInit();
	glPopMatrix();	
}


void GLReshape(int width,int height)
{    
      
	
		 glViewport(0,0,width,height);
	     glMatrixMode(GL_PROJECTION);
		 glLoadIdentity();
		 glFrustum(-10, 10, -10, 10,10, 2000);//说明用了透视投影
 	//   gluPerspective(60.0,(GLfloat)width/(GLfloat)height,1.5,20.0); 
         glMatrixMode(GL_MODELVIEW);
	
// 
// 		if(!isVisible)
// 		{
// 			glViewport(0,0,width/1.5,height);
// 			glMatrixMode(GL_PROJECTION);
// 			glLoadIdentity();
// 			glFrustum(-10, 10, -10, 10,10, 2000);//说明用了透视投影
// 	//   gluPerspective(60.0,(GLfloat)width/(GLfloat)height,1.5,20.0); 
// 			glMatrixMode(GL_MODELVIEW);
// 		}

}



void Control3DS()			  //潜器模型的显示与控制
{   
    glPushMatrix();		
	glTranslatef((g_AUVPos.x + g_AuvMicroControl.x + g_AuvMicroY.x + g_AuvTranslationAlongZ.x),
		(g_AUVPos.y + g_AuvMicroControl.y + g_AuvMicroY.y + g_AuvTranslationAlongZ.y),
		(g_AUVPos.z + g_AuvMicroControl.z + g_AuvMicroY.y + g_AuvTranslationAlongZ.z));

	glRotated(-180+b,0.0,1.0,0.0);	// 控制绕圆心公转
	glRotatef(rotateY,0,1,0);	// 控制绕潜器自转
	glEnable(GL_TEXTURE_2D);
	m_3ds.show3ds(0,0,0,0,0.5);//显示潜器	
	glPopMatrix();

	glPushMatrix();
	DrawLineLink();// 添加轨迹路线
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);	
	
}

bool DrawLineLink()           
{
	lineLink * p=NULL;
	p=(lineLink *)malloc(sizeof(lineLink));    //在内存的动态区域分配存储空间
	if(p==NULL) return false;

	p->x= g_AUVPos.x + g_AuvMicroControl.x + g_AuvMicroY.x + g_AuvTranslationAlongZ.x;
	p->y= g_AUVPos.y + g_AuvMicroControl.y + g_AuvMicroY.y + g_AuvTranslationAlongZ.y;
	p->z= g_AUVPos.z + g_AuvMicroControl.z + g_AuvMicroY.y + g_AuvTranslationAlongZ.z;


	p->next=NULL;
	if(headline==NULL) 
	{
		headline=p;
		tailline=p;
	}
	else 
	{
		tailline->next=p;
		tailline=p;
	}          // 以上是创建轨迹链表的过程

	
	{
		// 以下是用创建的链表画出轨迹线
		if(headline==NULL) return false;
		glDisable(GL_LIGHTING);

		glPushAttrib(GL_CURRENT_BIT);//保存光照属性，否则影响整个场景的色彩
		glColor3f(0.0,1.0,0.0);
		glLineWidth(4);               //可以改变轨迹线的宽度，但是效果不好
		glBegin(GL_LINE_STRIP);       //将下面给的这些顶点用不封闭的直线连接来近似曲线
		for(p=headline;p!=NULL;p=p->next)
		{
			glVertex3f(p->x,p->y,p->z);       
		}
		glEnd();
		glPopAttrib();
		glEnable(GL_LIGHTING);
	}
	return true;

}


bool DeleteLineLink()
{
	lineLink * p=NULL,*q=NULL;
	if(headline==NULL) return false;
	for(p=headline;p!=NULL;)
	{
		q=p;
		p=p->next;
		free( q);
	}
	headline=NULL;
	tailline=NULL;
	return true;

}


void garland()//花环
{
	glPushMatrix();
	//glTranslatef(g_GarlandPosLeft.x,  g_GarlandPosLeft.y,  g_GarlandPosLeft.z);
	glTranslatef(-600,80,200);
	glScalef(30,30,30);
	m_3ds.show3ds(1,0,0,0,0.5);//显示花环架子
	glPopMatrix();
	
	glPushMatrix();
//	glTranslatef(-600,80,-20);//原始数据
	glTranslatef(-550,80,50);
	glScalef(30,30,30);
	m_3ds.show3ds(1,0,0,0,0.5);//显示花环架子
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(g_GarlandPosLeft.x,  g_GarlandPosLeft.y,  g_GarlandPosLeft.z);
	//glScalef(0.2,0.2,0.5);
	m_3ds.show3ds(2,0,0,0,0.5);//花环
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(g_GarlandPosRight.x,  g_GarlandPosRight.y,  g_GarlandPosRight.z);
	//	glScalef(0.2,0.2,0.5);
	//m_3ds.show3ds(3,0,0,0,1.5);// 花环
	m_3ds.show3ds(2,0,0,0,1.5);//花环
	glPopMatrix();


	glPushAttrib(GL_CURRENT_BIT);
	//skyBox1.Render(100,100,100);
	glColor3f(1.0,0.0,0.0);
	m_obj.RenderSkyBox(25,25,25);
	glPopAttrib();
	
}



//////////////////////////////////////////////////////////////////////////
//               这一段代码写的很烂很烂  一切弄完后 从写这段控制代码 
//  
//					修改想法：用矢量，找准方向向量，潜器自转       
//							  加入动量 能量 加上水波
//                            减少全局变量，添加各种控制函数，
//							  在控制函数中用返回值代替全局变量
//
//									     hua    2012 5 15
//
//////////////////////////////////////////////////////////////////////////

void UpDateVelocity()

{
	if (start)
	{
		g_AUVPos += g_AUVVelocity;// 更新潜器位置
		g_AUVPosForDropSphere1 += g_AUVVelocityForDropSphere1;// 更新下落球1位置
		g_AUVPosForDropSphere2 += g_AUVVelocityForDropSphere2;// 更新下落球2位置
		g_AdjustLookAtForNotRotateThirdDoor += g_AdjustVelocityLookAtForNotRotateThirdDoor;
		
		g_vSpherePos1 += g_Sphere1Velocity; // 更新抛出球 1位置
		g_vSpherePos2 += g_Sphere2Velocity; // 更新抛出球 2位置
		g_vSpherePos3 += g_Sphere3Velocity; // 更新抛出球 3位置
		
		g_GarlandPosLeft  += g_GarlandVelocityLeft;// 更新左花环的位置
		g_GarlandPosRight += g_GarlandVelocityRight;// 更新右花环的位置	
	}

	//g_AdjustLookAtForNotRotate += g_AdjustVelocityLookAtForNotRotate;
	


}


void ReadyCollisionCondition()
{
	vec3 temp;
	vec3 temp1;
	vec3 temp2;
	vec3 temp3;
	
	temp = g_AUVPos - g_vSpherePos2;	
	temp1 = g_AUVPos - g_vSpherePos1;
	temp2 = g_AUVPos - g_vSpherePos3;
	
	
	a1 = length(temp);
	b1 = length(temp1);
	c1 = length(temp2);

	//a1 = temp.Length();
	
	
}

void CollisionYellowBall()
{
	bool IsCollasionYellow = false;
		if (!CollasionYellow) //如果黄球键也按下了
		{
			
			if (ForYellowLookAt.x<30)
			{
				ForYellowLookAt.x += 0.5;
			}
			
			if (a1<56)   //碰撞的条件
			{
				IsCollasionYellow = true; 
			}	
			if (IsCollasionYellow)  //碰撞成功
			{
				g_Sphere2Velocity = vec3(0.1*3,0.0,-0.4*3);	// 被撞黄球的速度
				isBackYellow = true;
				isBackBlue = false;
				//isBackRed = false;
				NextTrack = true;
				ThirdTrack = true;
				stop = true;			
			}						
		}
		
		//  黄球被撞后 运动
		if (g_vSpherePos2.x>490)
		{
			g_Sphere2Velocity = vec3(-0.05*3,0.0,0.2*3);// 黄球反弹速度
			g_AUVVelocity = vec3(-0.1*3,0.0,0.3*3);// 潜器后退
			g_AUVVelocityForDropSphere1 = g_AUVVelocity;
			g_AUVVelocityForDropSphere2 =g_AUVVelocity ;
			
		}
		//  黄球停下来
		if (g_vSpherePos2.x<450)
		{
			g_Sphere2Velocity = vec3(-0.0,0.0,0.0);
		}
		
		// 当潜器运动到轨迹线1时停下来
		if (g_AUVPos.x<410)
		{
			g_AUVVelocity = vec3(-0.0,0.0,0.0);// 潜器后退
			g_AUVVelocityForDropSphere1 = vec3(-0.0,0,0.0);
			g_AUVVelocityForDropSphere2 = vec3(-0.0,0,0.0);
		}
		
		// 将各个球返回原来的位置
		////////////////////////////// ////////////////////////////////////////////
		// 黄球
		if (g_vSpherePos2.x>500)
		{
			g_Sphere2Velocity = vec3(-0.1*3,0.0,0.4*3);
		}	
		if (g_vSpherePos2.x<480)
		{
			g_Sphere2Velocity = vec3(-0.0,0.0,0.0);
		}	
	//////////////////////////////////////////////////////////////////////////
}


void CollasionYellowReady()
{
	if (!isBackYellow)
		{
					// 控制第一个拐弯处
			if (g_AUVPos.z<550)
			{
						// 去撞黄球
						//让AUV停下来转-17度
				if (b>-17.0)
				{
					b -= 0.3;
						//	g_AuvMicroControl.x += 0.02;
					g_AUVVelocity = vec3(0.0,0,-0.0);
					g_AUVVelocityForDropSphere1 = vec3(0.0,0,-0.0);
					g_AUVVelocityForDropSphere2 = vec3(0.,0,-0.0);
				}
						
						//////////////////////////////////////////////////////////////////////////
						// 转完后开始前进
				else
				{
					g_AUVVelocity = vec3(0.1*3,0,-0.3*3);
					g_AUVVelocityForDropSphere1 =g_AUVVelocity ;//vec3(0.1,0,-0.3)
					g_AUVVelocityForDropSphere2 = g_AUVVelocity;//vec3(0.1,0,-0.3)
				}
						
			}
					
		}	
}
	
	
void CollasionRedBall()
{
	bool IsCollasionRedBall = false;
	if (CollasionRed)
	{
		track = true;// 锁住黄球轨道
		//////////////////////////////////////////////////////////////////////////
		// 潜器停下来上升到红球的高度
		if (isControlAuvForRedRotateAndUp) // 为了退出 if (g_AUVPos.y>115.0)这个循环
		{
			if (g_AUVPos.y<=115.0)
			{
				g_AUVPos.y += 0.3;
				g_AUVPosForDropSphere1.y += 0.3;
				g_AUVPosForDropSphere2.y += 0.3;		
			}
			
			if (g_AUVPos.y>115.0)
				
			{
				g_AUVPos.y += 0.0;
				g_AUVPosForDropSphere1.y += 0.0;
				g_AUVPosForDropSphere2.y += 0.0;			
				isControlAuvForRedRotate = true; // 开启下面的旋转
				isControlAuvForRedRotateAndUp = false;// 关闭 上面的上升
			}
			
		}
		
		
		//////////////////////////////////////////////////////////////////////////
		// 旋转             先上升后自转
		if (isControlAuvForRedRotate)
		{
			
			if(b<-9.0)
			{
				b += 0.3;
				//g_AuvMicroControl.x -= 0.025;
			}
			
			else    //自转后前进
			{
				g_AUVVelocity = vec3(0.085*2,0,-0.3*3);
				g_AUVVelocityForDropSphere1 = g_AUVVelocity;
				g_AUVVelocityForDropSphere2 = g_AUVVelocity;
			}
		}
		
		//碰撞条件
		if (b1<68)
		{
			IsCollasionRedBall = true;
		}
		
		// 碰撞产生
		if (IsCollasionRedBall)
		{
			g_Sphere1Velocity = vec3(0.1*3,0.0,-0.4*3);
			//isBackRed = true;
			isBackBlue = false;
			isBackYellow = false;
			ThirdTrack = true;
			//track = false;
		}
		
	}
	
	//////////////////////////////////////////////////////////////////////////
	// 被撞红球运动到460再返回450处停下来
	if (g_vSpherePos1.x>460)
	{
		isControlAuvForRedRotate = false;
		g_Sphere1Velocity = vec3(-0.05*3,0.0,0.2*3);// 返回速度
		g_AUVVelocity = vec3(-0.085*3,0,0.3*3);
		g_AUVVelocityForDropSphere1 = g_AUVVelocity;
		g_AUVVelocityForDropSphere2 = g_AUVVelocity;
	}
	
	
	if (g_vSpherePos1.x<450)
	{
		g_Sphere1Velocity = vec3(-0.0,0.0,0.0);
	}	
	
	// 撞完红球后 潜器后退到390时停下来
	//  控制潜器停下来
	if (g_AUVPos.x<399)
	{
		g_AUVVelocity = vec3(-0.0,0.0,0.0);// 潜器后退
		g_AUVVelocityForDropSphere1 = vec3(-0.0,0,0.0);
		g_AUVVelocityForDropSphere2 = vec3(-0.0,0,0.0);
	}
	
	//////////////////////////////////////////////////////////////////////////
}


void CollasionBuleBall()
{
	bool IsCollasionBlueBall = false;
	
	if (CollasionBlue)
	{	
		NextTrack = false;
		track = false;
		//////////////////////////////////////////////////////////////////////////
		//旋转潜器  为了在撞完绿球后不碰上红球
		//////////////////////////////////////////////////////////////////////////]
		// 调整位置高度 使得潜器正好碰上绿球
		if(isControlAuvForBlueRotateAndDown)  // 潜器位置上升后 将关闭该if
		{
			
			if (g_AUVPos.y>=80.0)
			{
				g_AUVPos.y -= 0.3;
				g_AUVPosForDropSphere1.y -= 0.3;
				g_AUVPosForDropSphere2.y -= 0.3;
				
			}
			
			if (g_AUVPos.y<80.0)		
			{
				//	cout<<"chenxinhua";			
				isControlAuvForBlueRotate = true; // 开启下面的旋转
				isControlAuvForBlueRotateAndDown = false;// 关闭 上面的下降
			}
			
		}
		//////////////////////////////////////////////////////////////////////////
		
		
		if(isControlAuvForBlueRotate)
		{
			
			// 转向绿球
			if (b<0)
			{
				b += 0.3;
			}
			
			//转完后开始前进
			else
				
			{
				g_AUVVelocity = vec3(0.06,0,-0.3*2);
				g_AUVVelocityForDropSphere1 = g_AUVVelocity;//vec3(0.04,0,-0.3)
				g_AUVVelocityForDropSphere2 =g_AUVVelocity ;//vec3(0.04,0,-0.3)
				// 为了看到完整的潜器  调节视口 
				if (g_AjustLookAtForBlueSphere.x < 30)
				{
					g_AjustLookAtForBlueSphere.x += 0.05;
				}	
			}	
		}	
		//////////////////////////////////////////////////////////////////////////
		
		
		//实现撞球				
		if (c1<50)
		{
			IsCollasionBlueBall = true;
		}
		
		if (IsCollasionBlueBall)
		{
			
			g_Sphere3Velocity = vec3(0.1*2,0.0,-0.4*2);
			isBackYellow = false;
			isBackBlue = true;
			//isBackRed = false;	
			IsMicaoControlAuvY = true;
		}
		
		//////////////////////////////////////////////////////////////////////////
		//  碰到绿球后 微小地调整潜器的高度
		if (IsMicaoControlAuvY)
		{
			if (g_AuvMicroY.y < 20)
			{
				g_AuvMicroY.y += 0.5;
				while(g_AuvMicroY.y > 20)
				{
					g_AuvMicroY.y = 20;
				}
			}
		}
		
		//绿球前进到430 再返回到420停下来
		if (g_vSpherePos3.x<420)
		{
			IsRotateToSecondDoor = true;	// 停下时去控制潜器转向第二格门					
			g_Sphere3Velocity = vec3(-0.0,0.0,0.0);						
		}
		
		
		if (g_vSpherePos3.x>430)
		{
			g_Sphere3Velocity = vec3(-0.1*3,0.0,0.4*3);// 球返速度回到420处
			//isGoToSecondDoor = true;
		}		
	}	
	
}



void auvStop()
{
	if (!IsStopToRotateSecondDoor)
	{
			g_AUVVelocity = vec3(0,0,0);
			g_AUVVelocityForDropSphere1 = vec3(0, 0, 0);
			g_AUVVelocityForDropSphere2 = vec3(0, 0, 0);
	}
	else
	{
			g_AUVVelocity = vec3(-0.14*2,0,-0.1*2);
			g_AUVVelocityForDropSphere1 = g_AUVVelocity ;//vec3(-0.17, 0, -0.1)
			g_AUVVelocityForDropSphere2 = g_AUVVelocity;//vec3(-0.17, 0, -0.1)
	}
}



void  RotateAuvAndEye()
{
	if (rotateY<50)
	{
		rotateY += 0.1*3;
		
	}
	
	if(rotateY>=50)
	{
		rotateY = 50;
		IsStopToRotateSecondDoor = true;
		IsStopRotateAndChangeLookAtForSecondDoor = true;
					//////////////////////////////////////////////////////////////////////////	
		}
				
				//////////////////////////////////////////////////////////////////////////
				//调节视口 为了看到完整的潜器
	if (g_AjustLookAtForBlueSphere.x < 100 && g_AjustLookAtForBlueSphere.z > -30)
					
		{	
			g_AjustLookAtForBlueSphere.x += 0.16;	
			g_AjustLookAtForBlueSphere.z -= 0.05;
		}
}



void auvStopForPitch()
{
	if (g_AUVPos.x<210)
	{
		//////////////////////////////////////////////////////////////////////////	
		g_AUVVelocity = vec3(0.00,0,0.00);
		g_AUVVelocityForDropSphere1 = vec3(0.0,0,0.0);
		g_AUVVelocityForDropSphere2 = vec3(0.0,0,0.0);	
	}
}



void RotateAUVForPitch()
{
	if (rotateY < 85)
	{
		rotateY += 0.1*3;	
	}
				
	if (rotateY>=85)
	{
		isStopToRotateBox = true;
	}
}


void RotateEyeForPitch()
{
	if (center.z > -100)
	{
		center.z -=1.1;
	}	
				
				
	if (center.x >-1600)
	{
		center.x -=1.1;	
	}
}



void StopForBox()
{
	if (!isStopToRotateBox)
	{
		g_AUVVelocity = vec3(0.0,0,0.0);
	}
	else
	{	
		g_AUVVelocity = vec3(-0.10*3,0,-0.01*3);// 投完球后  随身携带的三个球 不用加速度
	}
}


void DropSphere1IntoBox()
{
	if (!DropSphere1)
	{
		if (!isStopToRotateBox)
		{
			g_AUVVelocityForDropSphere1 = vec3(0,0,0);
		}
		else
		{
			g_AUVVelocityForDropSphere1 = vec3(-0.10*3,0,-0.01*3);//   下落球跟随速度
		}
					
	}
							
	else
	{
		g_AUVVelocityForDropSphere1 = vec3(-0.0,0,0.0);
		g_AUVVelocityForDropSphere2 = vec3(-0.0,0,0.0);
		g_AUVVelocity = vec3(0.0,0,0.00) ;//
					
					//////////////////////////////////////////////////////////////////////////
		IsChangeAuvVelocity = true;	
	}
}


void DropSphere2IntoBox()
{
	if (!DropSphere2)
	{
		if (!isStopToRotateBox)
		{
			g_AUVVelocityForDropSphere2 = vec3(0,0,0);

		}
		else
		{
			g_AUVVelocityForDropSphere2 = vec3(-0.10*3,0,-0.01*3);//   下落球跟随速度
		}
	}
				
	else
	{
		g_AUVVelocity = vec3(0.0,0,0.00) ;//
		g_AUVVelocityForDropSphere2 = vec3(-0.0,0,-0.0);
		g_AUVVelocityForDropSphere1 = vec3(-0.0,0,0.0);
		IsChangeAuvVelocity = true;
	//	IsControlAuvBackYellowSphereDrop = true;// 同时产生时
		IsStopControlAuvMoveYellow = false;
	}
}


void TurnToThirdDoor()
{
	if (!isAgainControlAuvMoveToThirdDoor)
	{	
		if (g_AUVPos.x<-100)
		{		
			g_AUVVelocity = vec3(-0.0,0,0.00);
			
			if (g_AUVPos.x<-20)
			{
				if(rotateY<95)
				{
					rotateY += 0.3*3;	
					if(rotateY>=95)
					{
						isAgainControlAuvMoveToThirdDoor = true;
					}
				}	
			}
		}
		else
			g_AUVVelocity = vec3(-0.3*3,0,0.01*3);
	}
				
	else
	{
		g_AUVVelocity = vec3(-0.3*3,0,0.01*3);	
	}
}


void PitchBalls()
{
	if (PitchSphere1)
	{
		//////////////////////////////////////////////////////////////////////////
		g_vPitchSphereMove1.z -= 5.3;
		g_vPitchSphereMove1.x -= 2.3;
	}
	
	
	if (PitchSphere2)
	{
		g_vPitchSphereMove2.z -= 5.3;
		g_vPitchSphereMove2.x -= 2.3;
	}
	
	if (PitchSphere3)
	{
		g_vPitchSphereMove3.z -= 5.3;
		g_vPitchSphereMove3.x -= 2.3;
	}
}


void DropBallIntoBox()
{
	if (DropSphere1)
	{
		g_AUVVelocityForDropSphere1 =vec3(0,0,0);
		if (!IsStopDropingRedSphere)
		{	
			if (g_vDropSphereMove1.y > -73.0)
			{
				g_vDropSphereMove1.y -= 0.5;
			}

			if (g_vDropSphereMove1.y<=-73.0)
			{
				g_vDropSphereMove1.y = -73;
				IsStopDropingRedSphere = true;
				IsControlAuvBackRedSphereDrop = true;// 同时产生时
			}
		}
	}
	
	//////////////////////////////////////////////////////////////////////////
	if (DropSphere2)
	{
		g_AUVVelocityForDropSphere2 = vec3(0,0,0);
		
		if (!IsStopDropingYellowSphere)
		{
			if (g_vDropSphereMove2.y > -73.0)
			{
				g_vDropSphereMove2.y -= 0.5;
			}
			if(g_vDropSphereMove2.y<=-73.0)
			{
				g_vDropSphereMove2.y = -73;
				IsControlAuvBackYellowSphereDrop = true;
				IsStopDropingYellowSphere = true;
			}
		}
	}	
}


void AUVStopOnBox()
{
	if (g_AUVPos.x < 0 &&  IsStopControlAuvMoveYellow) 
	{
		g_AUVVelocity = vec3(0,0,0);
		g_AUVVelocityForDropSphere1 = vec3(0,0,0);
		g_AUVVelocityForDropSphere2 = vec3(0,0,0);
	}	//////////////////////////////////////////////////////////////////////////
}


void AuvStopForGarland()
{
	if (!IsChangeDirectionForGarland)
	{
		if (g_AUVPos.x < -350 )
		{	
			g_AUVVelocity = vec3(-0.0,0.0,0.0);	
		}
	}
}



void ControlAUVToLeft()
{
	if (IsGoToLeftForTheGarland) // n键控制
	{
		vec3 tempDirectionLeft = vec3(-600+350.155, 0, 200-13.4854);
		vec3 tempAngle1 = vec3(-600+350,0,0);

		float b ;
		b = TwoVectorAngle(tempAngle1,tempDirectionLeft);
		b = convertAngle(b);
	
		IsChangeDirectionForGarland = true;
		IsGoToRightForTheGarland = false;
		//////////////////////////////////////////////////////////////////////////
	
		if (rotateY<(90+b))
		{
			rotateY += 0.5;
		}
		if (rotateY >= (90+b))
		{
			rotateY = (90+b);
			IsGoNotRotateForLeftGarland = true;
		}
		
		//////////////////////////////////////////////////////////////////////////
		
		// 让潜器前进
		if (IsGoNotRotateForLeftGarland)
		{
			if (g_AUVPos.x<-600)
			{
				g_AUVVelocity = vec3(0,0,0);
				isLeftGarlandMove = true;
			}
			else if (g_AUVPos.x < -350 )
			{	
				g_AUVVelocity = Normalize(tempDirectionLeft);	
			}		 
		}
	}
}


void ControlAUVToRight()
{
	if (IsGoToRightForTheGarland)//m 键控制
	{
		IsChangeDirectionForGarland = true;
		IsGoToLeftForTheGarland = false;
				
		vec3 tempAngle = vec3(-600+350,0,-20-15);
		vec3 tempAngle1 = vec3(-600+350,0,0);
		float a;
		a = TwoVectorAngle(tempAngle,tempAngle1);
		a = convertAngle(a);
		if (rotateY>(90-a))
		{
			
		    rotateY -= 0.3;
		}
					
		if (rotateY<=(95-a))
		{
			rotateY = 90-a;
			IsGoNotRotateForRightGarland = true;
		}	
		if (IsGoNotRotateForRightGarland)
		{
			
			if (g_AUVPos.x <= -600.0 )
			{	
				g_AUVVelocity = vec3(0,0,0);
				isRightGarlandMove = true;	
			}
			else if (g_AUVPos.x<-350)
			{
				g_AUVVelocity = Normalize(tempAngle);									
			}
		}
	}	
}



void ControlRightGarland()
{
	if (isRightGarlandMove)
	{

		IsGoToRightForTheGarland = false;

		if (g_GarlandPosRight.y <200)
		{
			g_GarlandVelocityRight.x = 0.0;
			g_GarlandVelocityRight.y = 1.0;
			g_GarlandVelocityRight.z = 0.0;	
			//跟着花环一起上升
			g_AUVVelocity = vec3(0,0,0);
		}
		if (g_AUVPos.y<150)
		{
			
			g_AUVPos.x += 0.0;
			g_AUVPos.y += 1.3;
			g_AUVPos.z += 0.0;
			g_AUVVelocity = vec3(0,0,0);
		}
		
		else
		{

			g_GarlandVelocityRight.x = 0.0;
			g_GarlandVelocityRight.y = 0.0;
			g_GarlandVelocityRight.y = 0.0;
			

			vec3 tempForGarland = vec3(g_AUVPos.x+350,g_AUVPos.y-80,g_AUVPos.z-15);
			vec3 tempForGarland1 = vec3(0-600.903,80-80,618+38.3915);
			float c;
			c = TwoVectorAngle(tempForGarland,tempForGarland1);
			c = convertAngle(c);
			c = 180 - c + 10;	//  注意这里转过的是钝角 通过cos球出来的是锐角 所以用180-c
			if (rotateY<(c+82.0))
			{
				rotateY += 0.5;
			}
			
			if (rotateY>=(c+82.0))
			{
				//cout<<"进入深海区的条件";
				rotateY = c+82.0;
				IstTurnToDeepSea = true;
				isRight = true;
				isGoToShallowSea = false; // 锁住上面的程序
				IsGlobalControl = false;
			}		
		}	 		
	}
	
}


void ControlLeftGarland()
{
	if (isLeftGarlandMove)
	{
		IsGoToLeftForTheGarland = false;
		
		if (g_GarlandPosLeft.y <=120)
		{
		
			g_GarlandVelocityLeft.x = 0.0;
			g_GarlandVelocityLeft.y = 0.8;// 这里存在很大的bug 是0.3的时候成立  1.3时 潜器往前跑了
			g_GarlandVelocityLeft.z = 0.0;	
			//跟着花环一起上升
			g_AUVVelocity = vec3(0,0,0);
		}
		
		
		if (g_AUVPos.y<=120.0)
		{
			
			g_AUVPos.x += 0;
			g_AUVPos.y += 1.30;
			g_AUVPos.z += 0.0;
			g_AUVVelocity = vec3(0,0,0);
		}
		
		
		else
		{

			g_GarlandVelocityLeft.x = 0.0;
			g_GarlandVelocityLeft.y = 0.0;
			g_GarlandVelocityLeft.y = 0.0;
			
	
			
			vec3 tempForGarland2 = vec3(-600.0083+350,80-80,151.303-38.3915);
			vec3 tempForGarland3 = vec3(0-600.0083,80-80,618-151.303);
			float d;
			d = TwoVectorAngle(tempForGarland2,tempForGarland3);
			d = convertAngle(d);
			d = 180 - d + 10;	//  注意这里转过的是钝角 通过cos球出来的是锐角 所以用180-c
			if (rotateY<(d+82.0))
			{
				rotateY += 0.5;
			}
			
			if (rotateY>=(d+82.0))
			{
		
				rotateY = d+82.0;
				IstTurnToDeepSea = true;
				isLeft = true;
				isGoToShallowSea = false; // 锁住上面的程序
				IsGlobalControl = false;
			}		
		}	 				
	}
}


void GoToDeepSeaFromRight()
{
	if (isRight)
	{			
		vec3 tempForGarlandvelocity = vec3(0+600.903,80-80,618+38.3915);

					
		if (!IsControlLastStop)
		{
			g_AUVVelocity = Normalize(tempForGarlandvelocity); // 没停下来时的速度
		}		
			
		if(g_AUVPos.z>=560)   //原始数据是560
		{
			g_AUVPos.z = 560;   // 潜器所停的位置 x z
			g_AUVPos.x = -200;
			IsControlLastStop = true;    //  控制潜器停下来 
			g_AUVVelocity = vec3(0,0,0);
			isRightPichCasing = true;
			
		}			
	}
}




void GoToDeepSeaFromLeft() 
{
	if (isLeft)
	{		

		//   终点套管的位置 （0,80,618)

		vec3 tempForGarlandvelocity1 = vec3(0+600.0083,80-80,618-151.303);
	
		
		if (!IsControlLastStop)
		{
			g_AUVVelocity = Normalize(tempForGarlandvelocity1); // 没停下来时的速度

		}	
		
					
		if(g_AUVPos.z>=560)  //原始数据是560
		{
			g_AUVPos.z = 560;   // 潜器所停的位置 x z
			g_AUVPos.x = -200;  //原始数据是0
			IsControlLastStop = true;    //  控制潜器停下来 
			g_AUVVelocity = vec3(0,0,0);
			isLeftPickCasing = true;
		}					
	}
}

void PickCasing()
{
	if(isLeftPickCasing||isRightPichCasing)
	{
		if (casingMov.x >-10||casingMov.z>-10)
		{
			casingMov.x -= 0.2;
	
			casingMov.z -= 0.2;
		}
		else
		{
			casingMov.x -= 0;
			casingMov.z -= 0;
		}
		
	}

}



void CameraType()
{
	if (camer<=1)// 近景
	{
		gluLookAt(  eye.x  +  g_AuvAjustLookAtForDeepSea.x  + g_AjustLookAtForBlueSphere.x + g_AjustLookAtForLastTarget.x + g_AdjustEye1.x +40 ,     
			eye.y   +  g_AuvAjustLookAtForDeepSea.y + g_AjustLookAtForBlueSphere.y + g_AdjustVel.y + g_AdjustEye1.y ,  
			eye.z  + g_AuvAjustLookAtForDeepSea.z +  g_AjustLookAtForBlueSphere.z + g_AdjustVel.z + g_AdjustEye1.z, 
			center.x + g_AdjustEye.x,   center.y + g_AdjustEye.y,  center.z + g_AdjustEye.z,
			0,   1,   0);
		isChangeLookAtForOverlook = false;
// 		cout<< (eye.x  +  g_AuvAjustLookAtForDeepSea.x  + g_AjustLookAtForBlueSphere.x + g_AjustLookAtForLastTarget.x + g_AdjustEye1.x +40 );
// 		cout<<(eye.y   +  g_AuvAjustLookAtForDeepSea.y + g_AjustLookAtForBlueSphere.y + g_AdjustVel.y + g_AdjustEye1.y);
//         cout<<(eye.z  + g_AuvAjustLookAtForDeepSea.z +  g_AjustLookAtForBlueSphere.z + g_AdjustVel.z + g_AdjustEye1.z);
 //		cout<<(	center.x + g_AdjustEye.x);    
	}
	
	else if (camer<=2) // 俯视
	{
		gluLookAt(  eye.x  +  g_AuvAjustLookAtForDeepSea.x  + g_AjustLookAtForBlueSphere.x + g_AjustLookAtForLastTarget.x + g_AdjustEye1.x +40 ,     
			eye.y   +  g_AuvAjustLookAtForDeepSea.y + g_AjustLookAtForBlueSphere.y + g_AdjustVel.y + g_AdjustEye1.y ,  
			eye.z  + g_AuvAjustLookAtForDeepSea.z +  g_AjustLookAtForBlueSphere.z + g_AdjustVel.z + g_AdjustEye1.z, 
			center.x + g_AdjustEye.x,   center.y + g_AdjustEye.y,  center.z + g_AdjustEye.z,
			0,   1,   0);
		isChangeLookAtForOverlook = true;
  //	cout<<(eye.x  +  g_AuvAjustLookAtForDeepSea.x  + g_AjustLookAtForBlueSphere.x + g_AjustLookAtForLastTarget.x + g_AdjustEye1.x +40 )<<endl;
  //    cout<<(eye.y   +  g_AuvAjustLookAtForDeepSea.y + g_AjustLookAtForBlueSphere.y + g_AdjustVel.y + g_AdjustEye1.y)<<endl;
 //		cout<<(eye.z  + g_AuvAjustLookAtForDeepSea.z +  g_AjustLookAtForBlueSphere.z + g_AdjustVel.z + g_AdjustEye1.z)<<endl;
 //		cout<<(center.x + g_AdjustEye.x)<<endl;
// 		cout<<eye.x<<endl;
// 		cout<<eye.y<<endl;
// 		cout<<eye.z<<endl;
	}
	
	else if (camer<=3)  // 右视图(从西北角看向东南角)
	{
		gluLookAt(-150,530,-650,  500.48, 0, 400,  0,1, 0);
	}
	
	
	

	else if (camer<=4)  // 左视图 偏前面
	{	
		gluLookAt(-950  + g_ChangeEyeForBoxes.x ,530 + g_ChangeEyeForBoxes.y,450 + g_ChangeEyeForBoxes.z,  500.48, 0, 400,  0, 1, 0);
	}

	else if(camer<=5)// 为了看拔管细节
	{
		gluLookAt(-250  + g_ChangeEyeForBoxes.x ,530 + g_ChangeEyeForBoxes.y,450 + g_ChangeEyeForBoxes.z,  500.48, 0, 400,  0, 1, 0);
	}


	


	if (isChangeLookAtForOverlook)  // 俯视 调整
	{
		eye.x = g_AUVPos.x + g_ChangeEyeForBoxes.x + g_AuvTowardGarlandLookAt.x ;
		eye.y = g_AUVPos.y +50 + g_ChangeEyeForBoxes.y + g_AuvTowardGarlandLookAt.y + 700;
		eye.z = g_AUVPos.z + 100 + g_ChangeEyeForBoxes.z + g_AuvTowardGarlandLookAt.z + 150;
	}
	
	else
	{
		eye.x = g_AUVPos.x + g_ChangeEyeForBoxes.x + g_AuvTowardGarlandLookAt.x;
		eye.y = g_AUVPos.y +50 + g_ChangeEyeForBoxes.y + g_AuvTowardGarlandLookAt.y;
		eye.z = g_AUVPos.z + 100 + g_ChangeEyeForBoxes.z + g_AuvTowardGarlandLookAt.z;
	}




}


void DrawTerrainAndDeepSea()
{
	glPushMatrix();//入栈
	//////////////////////////////////////////////////////////////////////////
	glEnable(GL_TEXTURE_2D);	
	glBindTexture( GL_TEXTURE_2D, ye.texture[0] );
	//glColor4f(0.0f,0.5f,1.0f,0.3f);//这个改变颜色的
	DrawTerrain();//画海底地形
//	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	glPushMatrix();
//	glEnable(GL_TEXTURE_2D);
	glTranslatef(-210,0,600);
	glBindTexture( GL_TEXTURE_2D, ye.texture[1] );
	circle(250,200,30,3000);    //画深水区
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}


void DrawAuvAndGarland()
{
	glPushMatrix();	
	Control3DS();//画潜器
	glPopMatrix();

	glPushMatrix();
	garland();//花环
	glPopMatrix();
}

void DrawDoor()
{
	glPushMatrix();
	glTranslatef(400,0,600);
	glRotatef(-60,0,1,0);
    draw1Door(0,200,0);// 开始门
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(250,0,150);
	glRotatef(-30,0,1.0,0);
	DrawDoor(0,50,0);//第一个绿门
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-300,0,50);
	DrawDoor(0,50,-10);//第二个绿门
	glPopMatrix();
}

void DrawGuideLine()
{
	glPushMatrix();
	glTranslatef(400,0,550);
	glRotatef(-270,0,1.0,0.0);
	DrawXian(0,15,0);//导线一
	glPopMatrix();

	glPushMatrix();
	//glTranslatef(450,0,300);
	glTranslatef(430,0,260);
	glRotatef(-30,0,1,0);
	DrawXian(0,15,0);//导线2
	glPopMatrix();
	
	// 导线3
	glPushMatrix();

	glTranslatef(200,0,100);
	glRotatef(-30,0,1,0);
	DrawXian(0,15,0);
	glPopMatrix();
	
	// 导线4
	glPushMatrix();
	glTranslatef(200,0,150);
	glRotatef(-120,0,1,0);
	DrawXian(0,15,0);
	glPopMatrix();

	// 导线5
	glPushMatrix();
	glTranslatef(-100,0,0);
	glRotatef(30,0,1,0);
	DrawXian(0,15,0);
	glPopMatrix();
	
	// 导线6
	glPushMatrix();
	glTranslatef(-75,0,50);
	glRotatef(-90,0,1,0);
	DrawXian(0,15,0);
	glPopMatrix();
}

void DrawBallForCollision()
{
	glPushAttrib(GL_CURRENT_BIT);
	
	glColor3f(1.0,1.0,0.0);//画第2个球  黄
	
	glPushMatrix();
	glTranslatef(g_vSpherePos2.x,g_vSpherePos2.y,g_vSpherePos2.z);
	glRotatef(-60,0,1.0,0);
	glutSolidSphere(10.0,32,32);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(g_vSpherePos1.x,g_vSpherePos1.y,g_vSpherePos1.z);
	glColor3f(1.0,0.0,0.0);//画第一个球  红
	//glRotatef(-60,0,1.0,0);
	glutSolidSphere(10.0,32,32);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(g_vSpherePos3.x,g_vSpherePos3.y,g_vSpherePos3.z);
	glColor3f(0.0,1.0,0);//画第三个球  绿
	glutSolidSphere(10.0,32,32);
	glPopMatrix();
	glPopAttrib();
}


void DrawBox()
{
	glPushMatrix();
	glScalef(0.7,0.7,0.7);
	m_obj.Box();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0,0,-340);
	m_obj.CircleBox(0,120,0);
	glPopMatrix();
}


void DrawCasingAndBoard()
{
	// 固定套管
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
//	glTranslatef(50,150,600);//原始数据
	glTranslatef(-150,150,600);
	glColor3f(1.0,1.0,0.0);
	m_obj.cylinder(18,2.5,2.5);		
	glPopMatrix();
	
	// 需要移动的套管

	glPushMatrix();
	glColor3f(0,1,1);
	glTranslatef(casingMov.x,casingMov.y,casingMov.z);
//	glTranslatef(50,150,600); //原始数据
	glTranslatef(-150,150,600);
	m_obj.cylinder(12,5.5,5.5);		
	glPopMatrix();

//	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	glColor4f(1.0,0.0,0.0,0.0);	
//	glTranslatef(0,100,618);   //原始数据
	glTranslatef(-190,100,618);
	glRotatef(-90,1,0,0);
	
	m_obj.Board(100,100);
	glPopMatrix();
//	glPopAttrib();

	glPopAttrib();
}

void DrawBubbles()
{
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();

	DrawBubble();
	glEnable(GL_DEPTH_TEST);
	glPopMatrix();	
	glPopAttrib();
}


void DrawWater()
{
	glPushMatrix();
	// 		 	glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D,texture[3]);
	//	glDisable(GL_LIGHTING);
	//启动融合
	glEnable(GL_BLEND);
	//定义源融合因子与目的因子
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	//水面为接近背景色，但稍亮；Alpha为0.3
	glColor4f(0.0f,0.5f,1.0f,0.3f);
	glTranslatef(0.0f,13.0f,0.0f);
	static int i=0,j=0;
	int A=15;
	j=i++%A;
	for(int x=-1500;x<1500;x+=20)
	{
		glBegin(GL_QUADS);
		glTexCoord2f(0.0,0.0);   glVertex3f(x,1500,1.5+2.0*sin(x+150+360/A*j*PI/180));
		glTexCoord2f(1.0,0.0);   glVertex3f(x+20,1500,1.5+2.0*sin((x+150+20)+360/A*j*PI/180));
		glTexCoord2f(1.0,1.0);   glVertex3f(x+20,-1500,1.5+2.0*sin((x+150+20)+360/A*j*PI/180));
		glTexCoord2f(0.0,1.0);   glVertex3f(x,-1500,1.5+2.0*sin(x+150+360/A*j*PI/180));
		glEnd();
	}
	//屏蔽融合
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();	
}

void DrawWaters()
{
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	DrawWater();
	glPopMatrix();
	glPopAttrib();
}


void DrawLineOfCollisionBalls()
{
	//////////////////////////////////////////////////////////////////////////
	//             画球的线
	// 画黄球的线  红线
	glPushAttrib(GL_CURRENT_BIT);
	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
	glPushMatrix();
	//glLineWidth(10);
	glLineWidth(0.5);
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINES);
	glVertex3f(480,0,360);
	glVertex3f(g_vSpherePos2.x,g_vSpherePos2.y,g_vSpherePos2.z);
	glEnd();
	glPopMatrix();
	//     画红球的线  蓝线
	glPushMatrix();
	//glLineWidth(10);
	//	glColor3f(1.0,1.0,0.0);
	glBegin(GL_LINES);
	glVertex3f(450,0,370);
	glVertex3f(g_vSpherePos1.x,g_vSpherePos1.y,g_vSpherePos1.z);
	glEnd();
	glPopMatrix();
	
	//  画蓝球的线  
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex3f(420,0,350);
	glVertex3f(g_vSpherePos3.x,g_vSpherePos3.y,g_vSpherePos3.z);
	glEnd();
	glPopMatrix();	
	glPopAttrib();

}

void DrawDropBalls()
{
	glPushMatrix();//下落球 2
	glPushAttrib(GL_CURRENT_BIT);
	glTranslatef(g_AUVPosForDropSphere2.x + g_AuvMicroControl.x + g_AuvMicroY.x + g_vDropSphereMove2.x -3,  
		g_AUVPosForDropSphere2.y + g_AuvMicroControl.y + g_AuvMicroY.y + g_vDropSphereMove2.y,
		g_AUVPosForDropSphere2.z + g_AuvMicroControl.z + g_AuvMicroY.z + g_vDropSphereMove2.z);//添加了1
	
	glRotated(-180+b,0.0,1.0,0.0);	
	glRotatef(rotateY,0,1,0);
	
	glColor3f(1.0,0.0,0.0);
	glutSolidSphere(2.5,30,30);
	glPopAttrib();
	glPopMatrix();
	
	glPushMatrix();//下落球 1
	glPushAttrib(GL_CURRENT_BIT);
	glTranslatef(g_AUVPosForDropSphere1.x + g_AuvMicroControl.x + g_AuvMicroY.x + g_vDropSphereMove1.x - 3,
		g_AUVPosForDropSphere1.y + g_AuvMicroControl.y + g_AuvMicroY.y + g_vDropSphereMove1.y ,
		g_AUVPosForDropSphere1.z + g_AuvMicroControl.z + g_AuvMicroY.z + g_vDropSphereMove1.z);// 添加了1
	
	glRotated(-180+b,0,1.0,0.0);	
	glRotatef(rotateY,0,1,0);
	
	glColor3f(1.0,1.0,0.0);
	glutSolidSphere(2.5,30,30);
	glPopAttrib();
	glPopMatrix();	
	//////////////////////////////////////////////////////////////////////////
}


//////////////////////////////////////////////////////////////////////////
void SphereForPitch()
{
	//////////////////////////////////////////////////////////////////////////
	glPushMatrix();//发射球 1
	glPushAttrib(GL_CURRENT_BIT);
	glTranslatef((g_AUVPos.x + g_AuvMicroControl.x + g_AuvMicroY.x),
		(g_AUVPos.y + g_AuvMicroControl.y + g_AuvMicroY.y),
		(g_AUVPos.z + g_AuvMicroControl.z + g_AuvMicroY.y));
	glTranslatef(g_vPitchSphereMove1.x,g_vPitchSphereMove1.y,g_vPitchSphereMove1.z);
	glRotated(-180+b,0.0,1.0,0.0);	
	glRotatef(rotateY,0,1,0);
	
	glColor3f(1.0,0.0,0.0);
	glutSolidSphere(5,30,30);
	glPopAttrib();
	glPopMatrix();
	glPushMatrix();//发射球 2
	glPushAttrib(GL_CURRENT_BIT);
	glTranslatef((g_AUVPos.x + g_AuvMicroControl.x + g_AuvMicroY.x),
		(g_AUVPos.y + g_AuvMicroControl.y + g_AuvMicroY.y),
		(g_AUVPos.z + g_AuvMicroControl.z + g_AuvMicroY.y));
	glTranslatef(g_vPitchSphereMove2.x,g_vPitchSphereMove2.y,g_vPitchSphereMove2.z);
	glColor3f(0,1,0);
	glutSolidSphere(5,30,30);
	glPopAttrib();
	glPopMatrix();
	
	glPushMatrix();//发射球 3
	glPushAttrib(GL_CURRENT_BIT);
	glTranslatef((g_AUVPos.x + g_AuvMicroControl.x + g_AuvMicroY.x),
		(g_AUVPos.y + g_AuvMicroControl.y + g_AuvMicroY.y),
		(g_AUVPos.z + g_AuvMicroControl.z + g_AuvMicroY.y));
	glTranslatef(g_vPitchSphereMove3.x,g_vPitchSphereMove3.y,g_vPitchSphereMove3.z);
	glColor3f(0,0,1);
	glutSolidSphere(5,30,30);
	glPopAttrib();
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
}


void KeyPressFunc(unsigned char key, int x, int y)
{
    switch (key)
    {
	case' ':		
		g_AUVVelocity = -g_AUVVelocity;
		g_AUVVelocityForDropSphere2 =- g_AUVVelocityForDropSphere2;
		g_AUVVelocityForDropSphere1 =- g_AUVVelocityForDropSphere1;	
		break;
		// 控制整个场景的旋转
	case 'x':
		g_ChangeEyeForBoxes.x += 10.5;
		break;
	case 'X':
		g_ChangeEyeForBoxes.x -= 10.5;        
		break;
	case 'y':
		g_ChangeEyeForBoxes.y += 10.5;
		break;
	case 'Y':
		g_ChangeEyeForBoxes.y -= 10.5;
		break;
		
	case 'z':
		g_ChangeEyeForBoxes.z += 10.5;
		break;
 	  case 'Z':
		g_ChangeEyeForBoxes.z -= 10.5;
		  
		  break;
		  
		  
		  //控制红绿黄球的撞击
	  case'r':
	  case'R':
		  CollasionRed = !CollasionRed;
		  break;

	  case 'h':
	  case 'H':
		  start=!start;
		  break;

	  case'b':
	  case 'B':
		  CollasionBlue = !CollasionBlue;
		  break;
		  
	  case'p':  
	  case 'P':
		  
		  PitchSphere1 = true;
		  break;
	  case'o':
	  case'O':
		  PitchSphere2 = true;
		  break;
	  case'i':
	  case'I':
		  PitchSphere3 = true;
		  isBackForPitch = true;
		  stop = true;

		  //stop1 = false;
		 // stop2 = false;
		  break;
		  
	  case'n':
	  case'N':
		  IsGoToLeftForTheGarland = true;
		  break;
		  
	  case 'm':
	  case'M':
		  IsGoToRightForTheGarland = true;
		  break;
	  case 'u':
	  case 'U':
		  IsChangeLookAtType = !IsChangeLookAtType;
		  break;
		  
		  // 控制下降球
	  case'1':
		  DropSphere1 = true;
		  break;
	  case'3':
		  DropSphere2 = true;
		  IsStopControlAuvMoveYellow = false;
		  break;
		  
	  case'4':
		  g_AUVPos.z += cos(0.5*3.1415926/180);
		  g_AUVPosForDropSphere1.z += cos(0.5*3.1415926/180);
		  break;
	  case'8':
		  g_AUVPos.z += cos(0.5*3.1415926/180);
		  g_AUVPosForDropSphere2.z += cos(0.5*3.1415926/180);
		  break;
		  
	  case'6':
		  g_AUVPos.z -= cos(0.5*3.1415926/180);
		  g_AUVPosForDropSphere1.z -= cos(0.5*3.1415926/180);
		  break;
	  case'2':
		  g_AUVPos.z -=cos(0.5*3.1415926/180);
		  g_AUVPosForDropSphere2.z -= cos(0.5*3.1415926/180);
		  
		  break;				
	  case'c':
	  case 'C':
		  // IsControlAUVBackSphereDrop = !IsControlAUVBackSphereDrop;
		  isVisible=true;
		  camer += 1;
		  if (camer>5)
		  {
			  camer = 0;
		  }
		  break;

	  case'g':
	  case 'G':
		  // IsControlAUVBackSphereDrop = !IsControlAUVBackSphereDrop;
		isVisible=false;
		camer += 1;
		if (camer>5)
		{
			camer = 0;
		}
          break;
		  
	  case 'f':
	  case'F':
		  isChangeLookAtForOverlook = !isChangeLookAtForOverlook;
		  
		  //Camtype = 1;
		  break;
		  
	  case 'w':
		  IsChangeLookAtForFront =!IsChangeLookAtForFront;
		  break;
	  case 't':
		  g_AdjustEye.x += 100;
		  break;
	  case 'T':
		  g_AdjustEye.x -= 100;
		  break;
	  case'v':
		  g_AdjustEye.y += 100;
		  break;
	  case 'V':
		  g_AdjustEye.y -= 100;
		  break;
		  
	  case 's':
		  g_AdjustEye.z += 100;
		  break;
	  case 'S':
		  g_AdjustEye.z -= 100;
		  break;
		  
	  case 'k':
		  rotateY += 0.5;
		  break;
	  case 'K':
		  rotateY  -= 0.5;
		  break;
		  
	  case 'W':
		  elbow += 10;
		  break;
		  
	  case 'q':
	  case 'Q':
	  case 27 :			/* ESC */
		  exit(0);
    }
    glutPostRedisplay();
}



void SpecialKeys(int key, int x, int y)
{
    switch (key)
    {
	case GLUT_KEY_LEFT://键盘上的左右上下键]
		g_AUVPos.z += 1.5;
		g_AUVPosForDropSphere2.z += 1.5;	
		g_AUVPosForDropSphere1.z += 1.5;	
		break;
		
	case GLUT_KEY_RIGHT:
		g_AUVPos.z -= 1.5;
		g_AUVPosForDropSphere2.z -= 1.5;
		g_AUVPosForDropSphere1.z -= 1.5;	
		break;
		
	case GLUT_KEY_UP:
		g_AUVPos.x += 5;
		g_AUVPosForDropSphere2.x += 5;	
		g_AUVPosForDropSphere1.x += 5;
		break;
		
		
	case GLUT_KEY_DOWN:
		g_AUVPos.x -= 5;
		g_AUVPosForDropSphere2.x -= 5;	
		g_AUVPosForDropSphere1.x -= 5;
		
		break;	
    default:
        break;
    }
    glutPostRedisplay();
}


void handleMenu(int ID)
{
    switch(ID) 
    {
	case 0:
		exit(0);
	case 1:
		// 变化的值
		break;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
void mouse(int btn, int state, int x, int y)
{
    if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
		if (btn = GLUT_LEFT_BUTTON)
		{
			
			switch(state)
			{
			case GLUT_DOWN: 
				isLeftMouseDown = TRUE;
				break;
			case GLUT_UP:          
				break;	
			}
		}
		//glutPostRedisplay();
    }
	
	
    if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {			
        if(btn==GLUT_RIGHT_BUTTON)
		{
			switch(state)
			{
			case GLUT_DOWN: 
				isRightMouseDown = TRUE;
				break;
			case GLUT_UP:          
				break;			
			}
			glutPostRedisplay();
		}
    } 
}


void mouseMotion(int x, int y)
{
    if(isLeftMouseDown)
	{	
			
	}
	if (isRightMouseDown)
	{
		// 		eye.x  = x+100;
		eye.z = y-100;
		//		eye.z += 1.0;
	}
	
    glutPostRedisplay();
}

////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("AUVSimulate");
	GLInit(0);
	
//	glutReshapeFunc(GLReshape);
	glutReshapeFunc(resizeGL);//修改的地方
   
//	glutDisplayFunc(Display); 
	glutDisplayFunc(paintGL);  //修改的地方

	glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
	glutKeyboardFunc(KeyPressFunc);
	glutSpecialFunc(SpecialKeys);
	
	//     glutCreateMenu(handleMenu); 
	//     glutAddMenuEntry("Reverse Charge", 1);
	//     glutAttachMenu(GLUT_RIGHT_BUTTON);
	//     glutAddMenuEntry("Quit", 0);
	//     glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();

	DeleteLineLink();
	return 0;
}


void IdelPos(void)
{
	UpDateVelocity();
	ReadyCollisionCondition();
	// 控制轨线
	//////////////////////////////////////////////////////////////////////////
	if(IsGlobalControl)
	{
		//////////////////////////////////////////////////////////////////////////	
		if (!track) // 
		{
			CollisionYellowBall();
		}
		//////////////////////////////////////////////////////////////////////////
		if (NextTrack)
		{
			CollasionRedBall();	
			//////////////////////////////////////////////////////////////////////////	
		}		
		//////////////////////////////////////////////////////////////////////////
		// 绿球有关事件
		if (ThirdTrack)
		{
			CollasionBuleBall();	
		}
		//////////////////////////////////////////////////////////////////////////
		//  潜器转向第二个门
		if (IsRotateToSecondDoor)
		{	
			// 停下来 转向门
			auvStop();
			// 控制潜器停下来旋转  在转向去第二个门的时候   旋转潜器 让潜器对着门
			if (!IsStopRotateAndChangeLookAtForSecondDoor)
			{	
				RotateAuvAndEye();
			}	
		}	
		//////////////////////////////////////////////////////////////////////////	
		// 控制潜器到第三个导线  为投球做准备工作
		//////////////////////////////////////////////////////////////////////////
		if (!isBackForPitch)
		{
		// 当g_AUVPos.x2达到00的时候让潜器和球都停下来 准备发射	
			auvStopForPitch();		
		}

		// 投完球后 开始往前走	
		else
		{
			// 旋转潜器
			RotateAUVForPitch();

			//////////////////////////////////////////////////////////////////////////			
			//  改变看的中心点  为了避免当潜器到达ooo点时 看不到前面的物体
			RotateEyeForPitch();
			//////////////////////////////////////////////////////////////////////////
			//常开事件
			if (!IsChangeAuvVelocity)
			{
				StopForBox();	
			}	
			//////////////////////////////////////////////////////////////////////////
			DropSphere1IntoBox();
			DropSphere2IntoBox();
			// 控制下落球
			//////////////////////////////////////////////////////////////////////////
			DropBallIntoBox();
			//////////////////////////////////////////////////////////////////////////
			//两个球都掉下时 产生下列事件
			if (IsControlAuvBackRedSphereDrop && IsControlAuvBackYellowSphereDrop)
			{
				// 转向第三个门
				
				//////////////////////////////////////////////////////////////////////////	
				TurnToThirdDoor();	
			}	
		}
		//////////////////////////////////////////////////////////////////////////
		PitchBalls();
		//////////////////////////////////////////////////////////////////////////
	
		//////////////////////////////////////////////////////////////////////////	
		// k
		if (!stop)// 留下的贻害
		{
			CollasionYellowReady(); // 早起就不该放这
		}
		//    让潜器在盒子上方停下来  为掉球做准备
		AUVStopOnBox();
		//////////////////////////////////////////////////////////////////////////
		//   浅海区
		if (isGoToShallowSea)
		{		
			AuvStopForGarland();
			ControlAUVToRight();
			ControlAUVToLeft();
			//////////////////////////////////////////////////////////////////////////
		}
	// 	//////////////////////////////////////////////////////////////////////////
	// 	//  控制花环运动
		//控制左侧运动
	ControlRightGarland();

	// 控制左侧花环运动
	ControlLeftGarland();
	//////////////////////////////////////////////////////////////////////////	
	}
	//////////////////////////////////////////////////////////////////////////
	//  跟最前面的if对应   IsGlobalControl  屏蔽前面所有操作
	else
	{
		if (IstTurnToDeepSea)
		{
			//cout<<"已经进入深海区"<<endl;
			GoToDeepSeaFromRight();
			GoToDeepSeaFromLeft();	
			PickCasing();
		}
	}
}



void Display()
{
    //glClear( GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT );
    glClear(  GL_DEPTH_BUFFER_BIT );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
	CameraType();
	DrawTerrainAndDeepSea();
	DrawAuvAndGarland(); 	
	DrawDoor();
	DrawGuideLine();
	DrawLineOfCollisionBalls();
	DrawBallForCollision();	
	SphereForPitch(); 
	DrawDropBalls();
	//画盒子
	DrawHand();
	DrawBox();
	DrawCasingAndBoard();
	//画水泡
	DrawBubbles();
	
	//	DrawWaters();
	////////////////////////////////////////////////////////////////////////////
	IdelPos();// 更新位置	
//	glutSwapBuffers();	
	/*glutPostRedisplay();	*///2015.08.02HL修改  影响最初的显示
}
void  Display1()
{
	//  glClear( GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT );
    glClear(  GL_DEPTH_BUFFER_BIT );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-200,0,-100);
    gluLookAt(50,800,500,0,0,0,0,1,0);
	
//	CameraType();
	DrawTerrainAndDeepSea();
	DrawAuvAndGarland(); 	
	DrawDoor();
	DrawGuideLine();
	DrawLineOfCollisionBalls();
	DrawBallForCollision();	
	SphereForPitch(); 
	DrawDropBalls();
	//画盒子
	DrawHand();
	DrawBox();
	DrawCasingAndBoard();
	//画水泡
	DrawBubbles();
	
	//	DrawWaters();
	////////////////////////////////////////////////////////////////////////////
	IdelPos();// 更新位置	
	//glutSwapBuffers();	
	//glutPostRedisplay();	
}

void Display2()
{
	
	//  glClear( GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT );
    glClear(  GL_DEPTH_BUFFER_BIT );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(-100,830,-550,  500.48, 0, 400,  0, 1, 0);
	
	//	CameraType();
	DrawTerrainAndDeepSea();
	DrawAuvAndGarland(); 	
	DrawDoor();
	DrawGuideLine();
	DrawLineOfCollisionBalls();
	DrawBallForCollision();	
	SphereForPitch(); 
	DrawDropBalls();
	//画盒子
	DrawHand();
	DrawBox();
	DrawCasingAndBoard();
	//画水泡
	DrawBubbles();
	
	//	DrawWaters();
	////////////////////////////////////////////////////////////////////////////
	IdelPos();// 更新位置	
	//glutSwapBuffers();	
	/*glutPostRedisplay();*///201508.05 HL修改   删除
}

void paintGL()
{
//	glClear(GL_DEPTH_BUFFER_BIT );
   	glClear(GL_COLOR_BUFFER_BIT);

     if ( isVisible)
 	{   
 		 paintCenter();
      
 	}
 
     	if (!isVisible)
 	{  
	   /* gluPerspective(60.0,(GLfloat)width/(GLfloat)height,1.5,20.0); */
	    paintViewportLeft();
        paintViewportRight();
	    paintViewportRight1();
	}
    
 //    glFlush(); 

	glutSwapBuffers();	
	/*glutPostRedisplay();*/
	

	
}

void  paintCenter()
{
	
	glViewport(0,0,width,height);//定义视口大小
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-10, 10, -10, 10,10, 2000);//说明用了透视投影
	gluPerspective(90, 1, 10, 2000);//上面的和下面的可以转换
    Display();
////	glutPostRedisplay();
}
  

void paintViewportLeft()
{
   	glViewport(0,0,width/1.7,height);
//	gluPerspective(50, (GLfloat)width/(GLfloat)height,1.5,20.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-10, 10, -10, 10,10, 2000);//说明用了透视投影
	/*glMatrixMode(GL_MODELVIEW);	*/
    Display();
//	glutPostRedisplay();
}

void  paintViewportRight()
{
    glViewport(width/1.7,height/2.6,width/1.7,height);
//	gluPerspective(50, (GLfloat)width/(GLfloat)height,1.5,20.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-10, 10, -10, 10,10, 2000);//说明用了透视投影
	Display1();
//	glutPostRedisplay();
}
void  paintViewportRight1()
{
	glViewport(width/1.7,0,width/1.7,height/2.6);
//	gluPerspective(50, (GLfloat)width/(GLfloat)height,1.5,20.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-10, 10, -10, 10,10, 2000);//说明用了透视投影
    Display2();
//	glutPostRedisplay();
}

void resizeGL(int w, int h)
{
	//在绘制里面设置过了
	//glMatrixMode(GL_PROJECTION);  
 //   glLoadIdentity();  
 //   gluOrtho2D(0, 1 , 0, 1);  //裁剪窗口定义
 //   glMatrixMode(GL_MODELVIEW);  
	//glLoadIdentity();
  
	
    width = w;  
    height = h; 
	glutPostRedisplay();//窗口改变后要回调显示

}
//////////////////////////////////////////////////////////////////////////


