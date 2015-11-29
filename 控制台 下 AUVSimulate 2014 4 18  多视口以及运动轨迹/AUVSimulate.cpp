// AUVSimulate.cpp : Defines the entry point for the console application.
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
///
//    ʵ����Ǳ��ײ�� ���� Ͷ�� ���� ץȡ �ȶ���
//    ��ʵ��Ǳ����תǰ��

//			��ݼ�
//     h����ʼ�˶�  ���� ��ͣ
///   ��ݼ� �ı��ӿ� 
//    c�� �ı��ӿ� 
//    b�� ײ����
//    r�� ײ����
//    k�� Ǳ����ת

//    p o i ��Ͷ�����
//    m ѡ���Ҳ໨��  n ѡ����໨��
//    1 3 ����  2 �� ����ʱ ƽ��Ǳ��
//    -> <-  �ϼ� �¼�����ǰ������ ����ƽ��
//    made by  ���»�  �Ž���  ���� @408 ����΢������ʵ����
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

//     ��Ӷ�������  2012 6 12
#define MASSOFAUV				10            //Auv����
#define MASSOFBALL				0.05          //��ײ�������
#define MAXFORCEFROMLINE        100           // ��ײ�����������������
#define RESISTANCECoFFICIENT	0.05          // ˮ��Ħ��ϵ��    
  

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
vec3 g_AUVPosForDropSphere2 = vec3(410,100,710);//Ϊ����������1��׼��
vec3 g_AUVPosForDropSphere1 = vec3(410,100,720);  // ������2 

vec3 g_vSpherePos1 = vec3(450,120,370);   //��ײ��1 λ��    ����
vec3 g_vSpherePos2 = vec3(480,100,360 );  //��ײ��2 λ��     ��
vec3 g_vSpherePos3 = vec3(420,80,350);   //��ײ��3 λ��     ��
vec3 g_AuvMicroY = vec3(0,0,0);     //ײ������� AUV�Զ����ڸ߶�ֵ
vec3 g_ChangeEyeForBoxes = vec3(0,0,0);

vec3 g_AdjustVelocityLookAtForNotRotate = vec3(0,0,0);

vec3 g_AdjustLookAtForNotRotateThirdDoor = vec3(0,0,0);
vec3 g_AdjustVelocityLookAtForNotRotateThirdDoor = vec3(0,0,0);

vec3 g_vPitchSphereMove1 = vec3(0,0,0);  // Ͷ�����˶�
vec3 g_vPitchSphereMove2 = vec3(0,0,0);  
vec3 g_vPitchSphereMove3 = vec3(0,0,0);

vec3 g_vDropSphereMove1 = vec3(0,0,0);  //�������˶�
vec3 g_vDropSphereMove2 = vec3(0,0,0);


vec3 g_AUVVelocity = vec3(0,0,-0.5*3 );  // Ǳ��û������ǰ�˶��ٶ�0.014,0.0,-0.2  // ����2�� 
vec3 g_AUVVelocityForDropSphere1 = g_AUVVelocity; //vec3(0.0,0.0,-0.5)
vec3 g_AUVVelocityForDropSphere2 = g_AUVVelocity;//0.0,0.-0,5 ��ô���������ҵ����˺ܾ� �Ժ�ע����ЩСϸ��vec3(0.0,0,-0.5)
vec3 g_BubbleVelocityAloneToControl = vec3(0,0,0);

vec3 g_GarlandPosLeft = vec3(-600,80,200);
vec3 g_GarlandVelocityLeft = vec3(0,0,0);

vec3 g_GarlandPosRight = vec3(-550,80,50);//�Ķ��� zcc
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
typedef struct linelink    //�������˶�������
{
	GLfloat x;		
	GLfloat y;		
	GLfloat z;		
	struct linelink * next;
}lineLink; 

typedef struct 
{
	float	life;														// ��������
	float	fade;														// ����˥���ٶ�
	float	r,g,b;														// ���ӵ���ɫ
	float	x,y,z;														// ����λ��
	float	xSpeed,ySpeed,zSpeed;										// ���ӵ��ٶ�
	float	xg,yg,zg;													// ���ӵ��˶����ٶ�	
} PARTICLES;

GLfloat	speedFator = 0.033f;
PARTICLES bubble[MAX_PARTICLES];
lineLink * headline=NULL,* tailline=NULL;   //ͬ�ϣ�lineLink{x,y,z,*next}���������켣�ߵ�

//extern vec3 g_AUVPos ;//vec3 g_AUVPos = vec3(400,100,700);

//500������
void BubbleInit(void)
{
	for (int loop =0;loop<MAX_PARTICLES; loop++)
	{
		bubble[loop].life=1.0f;
		bubble[loop].fade=float(rand()%100)/20000.0f+0.0003f;//0.0003~0.0053

		//AUV��λ�ü�Ϊ�����ĵ��λ��
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
	for (int loop=0; loop<MAX_PARTICLES; loop++)						// ѭ������
	{			
		x = bubble[loop].x;											// ������������
		y = bubble[loop].y;
		z = bubble[loop].z;		
		glColor4f(0.5, 0.5, 0.5, bubble[loop].life);	
	//	glColor3f(1.0,1.0,1.0);
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
			
			bubble[loop].x = g_AUVPos.x + rand()%20;
			bubble[loop].y = g_AUVPos.y;
			bubble[loop].z = g_AUVPos.z + rand()%20;
			
			bubble[loop].xSpeed =0.0f;
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

void wave()
{
	
}

// //////////////////////////////////////////////////////////////////////////
//GLenum mode = GL_LINEAR;
//////////////////////////////////////////////////////////////////////////

//  ��������ʱ�õ��Ĺ�ʽ
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



float TwoVectorAngle(vec3 x1, vec3 y1)// ���ص��ǻ�����
{
	float temp;
	float cosAngle;
	temp = DoProduct(x1,y1);
	cosAngle = temp/(Length(x1)*Length(y1));
	return acos(cosAngle);
}

float convertAngle(float angle)// ����ת���ɽǶ�
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
	
	glClearColor(fog_r, fog_g, fog_b, 1);			// �ڱ�����ɫ
	glBlendFunc(GL_SRC_ALPHA,GL_DST_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	
	//����
	GLfloat lightPos1[]={0.0f,4.0f,-1.0f,0.0f};//���λ��
	GLfloat LightAmb[]={0.4f,0.4f,0.4f,1.0f};//���������ɫ
	GLfloat LightDif[]={1.0f,1.0f,1.0f,1.0f};//����������ɫ
	GLfloat MatAmb[]={0.7f,0.7f,0.7f,1.0f};//���ʵĻ�������ɫ
	GLfloat MatDif[]={1.0f,1.0f,1.0f,1.0f};//���ʵ����������ɫ
    GLfloat matShininess[] = { 5.0 };
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDif);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDif);// ���������ɷ֣����Դ
	glLightfv(GL_LIGHT0,GL_AMBIENT,LightAmb);
 	glMaterialfv(GL_FRONT,GL_SHININESS,matShininess);
   
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	
	//////////////////////////////////////////////////////////////////////////
	GLuint	fogMode[]= { GL_EXP, GL_EXP2, GL_LINEAR };	// �����������ģʽ
	GLuint	fogfilter = 0;								// ��ǰʹ�õ����ģʽ 
	GLfloat	fogColor[4] = {fog_r, fog_g, fog_b, 1};		// �����ɫ
	
	glFogi(GL_FOG_MODE, fogMode[2]);			        // �������ģʽ
	glFogfv(GL_FOG_COLOR, fogColor);					// ���������ɫ
	glFogf(GL_FOG_DENSITY, 0.3024f);						// �������Ũ��
	glHint(GL_FOG_HINT, GL_NICEST);					    // Fog Hint Value
	glFogf(GL_FOG_START, 300.0f);						// ������Ŀ�ʼ���
	glFogf(GL_FOG_END, visual_distance);				// ������Ľ������
	glEnable(GL_FOG);
	
	//////////////////////////////////////////////////////////////////////////
	
	glEnable(GL_COLOR_MATERIAL); 
	glClearDepth(1.0f);					
	glEnable(GL_DEPTH_TEST);
	qobj=gluNewQuadric();//�������ƶ����������
	InitTerrain();
	
	glPushMatrix();
	glTranslatef(0,0,0);

	glScalef(10,10,10);//���ݻ���ʱ����
	BubbleInit();
	glPopMatrix();	
}


void GLReshape(int width,int height)
{    
      
	
		 glViewport(0,0,width,height);
	     glMatrixMode(GL_PROJECTION);
		 glLoadIdentity();
		 glFrustum(-10, 10, -10, 10,10, 2000);//˵������͸��ͶӰ
 	//   gluPerspective(60.0,(GLfloat)width/(GLfloat)height,1.5,20.0); 
         glMatrixMode(GL_MODELVIEW);
	
// 
// 		if(!isVisible)
// 		{
// 			glViewport(0,0,width/1.5,height);
// 			glMatrixMode(GL_PROJECTION);
// 			glLoadIdentity();
// 			glFrustum(-10, 10, -10, 10,10, 2000);//˵������͸��ͶӰ
// 	//   gluPerspective(60.0,(GLfloat)width/(GLfloat)height,1.5,20.0); 
// 			glMatrixMode(GL_MODELVIEW);
// 		}

}



void Control3DS()			  //Ǳ��ģ�͵���ʾ�����
{   
    glPushMatrix();		
	glTranslatef((g_AUVPos.x + g_AuvMicroControl.x + g_AuvMicroY.x + g_AuvTranslationAlongZ.x),
		(g_AUVPos.y + g_AuvMicroControl.y + g_AuvMicroY.y + g_AuvTranslationAlongZ.y),
		(g_AUVPos.z + g_AuvMicroControl.z + g_AuvMicroY.y + g_AuvTranslationAlongZ.z));

	glRotated(-180+b,0.0,1.0,0.0);	// ������Բ�Ĺ�ת
	glRotatef(rotateY,0,1,0);	// ������Ǳ����ת
	glEnable(GL_TEXTURE_2D);
	m_3ds.show3ds(0,0,0,0,0.5);//��ʾǱ��	
	glPopMatrix();

	glPushMatrix();
	DrawLineLink();// ��ӹ켣·��
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);	
	
}

bool DrawLineLink()           
{
	lineLink * p=NULL;
	p=(lineLink *)malloc(sizeof(lineLink));    //���ڴ�Ķ�̬�������洢�ռ�
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
	}          // �����Ǵ����켣����Ĺ���

	
	{
		// �������ô������������켣��
		if(headline==NULL) return false;
		glDisable(GL_LIGHTING);

		glPushAttrib(GL_CURRENT_BIT);//����������ԣ�����Ӱ������������ɫ��
		glColor3f(0.0,1.0,0.0);
		glLineWidth(4);               //���Ըı�켣�ߵĿ�ȣ�����Ч������
		glBegin(GL_LINE_STRIP);       //�����������Щ�����ò���յ�ֱ����������������
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


void garland()//����
{
	glPushMatrix();
	//glTranslatef(g_GarlandPosLeft.x,  g_GarlandPosLeft.y,  g_GarlandPosLeft.z);
	glTranslatef(-600,80,200);
	glScalef(30,30,30);
	m_3ds.show3ds(1,0,0,0,0.5);//��ʾ��������
	glPopMatrix();
	
	glPushMatrix();
//	glTranslatef(-600,80,-20);//ԭʼ����
	glTranslatef(-550,80,50);
	glScalef(30,30,30);
	m_3ds.show3ds(1,0,0,0,0.5);//��ʾ��������
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(g_GarlandPosLeft.x,  g_GarlandPosLeft.y,  g_GarlandPosLeft.z);
	//glScalef(0.2,0.2,0.5);
	m_3ds.show3ds(2,0,0,0,0.5);//����
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(g_GarlandPosRight.x,  g_GarlandPosRight.y,  g_GarlandPosRight.z);
	//	glScalef(0.2,0.2,0.5);
	//m_3ds.show3ds(3,0,0,0,1.5);// ����
	m_3ds.show3ds(2,0,0,0,1.5);//����
	glPopMatrix();


	glPushAttrib(GL_CURRENT_BIT);
	//skyBox1.Render(100,100,100);
	glColor3f(1.0,0.0,0.0);
	m_obj.RenderSkyBox(25,25,25);
	glPopAttrib();
	
}



//////////////////////////////////////////////////////////////////////////
//               ��һ�δ���д�ĺ��ú���  һ��Ū��� ��д��ο��ƴ��� 
//  
//					�޸��뷨����ʸ������׼����������Ǳ����ת       
//							  ���붯�� ���� ����ˮ��
//                            ����ȫ�ֱ�������Ӹ��ֿ��ƺ�����
//							  �ڿ��ƺ������÷���ֵ����ȫ�ֱ���
//
//									     hua    2012 5 15
//
//////////////////////////////////////////////////////////////////////////

void UpDateVelocity()

{
	if (start)
	{
		g_AUVPos += g_AUVVelocity;// ����Ǳ��λ��
		g_AUVPosForDropSphere1 += g_AUVVelocityForDropSphere1;// ����������1λ��
		g_AUVPosForDropSphere2 += g_AUVVelocityForDropSphere2;// ����������2λ��
		g_AdjustLookAtForNotRotateThirdDoor += g_AdjustVelocityLookAtForNotRotateThirdDoor;
		
		g_vSpherePos1 += g_Sphere1Velocity; // �����׳��� 1λ��
		g_vSpherePos2 += g_Sphere2Velocity; // �����׳��� 2λ��
		g_vSpherePos3 += g_Sphere3Velocity; // �����׳��� 3λ��
		
		g_GarlandPosLeft  += g_GarlandVelocityLeft;// �����󻨻���λ��
		g_GarlandPosRight += g_GarlandVelocityRight;// �����һ�����λ��	
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
		if (!CollasionYellow) //��������Ҳ������
		{
			
			if (ForYellowLookAt.x<30)
			{
				ForYellowLookAt.x += 0.5;
			}
			
			if (a1<56)   //��ײ������
			{
				IsCollasionYellow = true; 
			}	
			if (IsCollasionYellow)  //��ײ�ɹ�
			{
				g_Sphere2Velocity = vec3(0.1*3,0.0,-0.4*3);	// ��ײ������ٶ�
				isBackYellow = true;
				isBackBlue = false;
				//isBackRed = false;
				NextTrack = true;
				ThirdTrack = true;
				stop = true;			
			}						
		}
		
		//  ����ײ�� �˶�
		if (g_vSpherePos2.x>490)
		{
			g_Sphere2Velocity = vec3(-0.05*3,0.0,0.2*3);// ���򷴵��ٶ�
			g_AUVVelocity = vec3(-0.1*3,0.0,0.3*3);// Ǳ������
			g_AUVVelocityForDropSphere1 = g_AUVVelocity;
			g_AUVVelocityForDropSphere2 =g_AUVVelocity ;
			
		}
		//  ����ͣ����
		if (g_vSpherePos2.x<450)
		{
			g_Sphere2Velocity = vec3(-0.0,0.0,0.0);
		}
		
		// ��Ǳ���˶����켣��1ʱͣ����
		if (g_AUVPos.x<410)
		{
			g_AUVVelocity = vec3(-0.0,0.0,0.0);// Ǳ������
			g_AUVVelocityForDropSphere1 = vec3(-0.0,0,0.0);
			g_AUVVelocityForDropSphere2 = vec3(-0.0,0,0.0);
		}
		
		// �������򷵻�ԭ����λ��
		////////////////////////////// ////////////////////////////////////////////
		// ����
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
					// ���Ƶ�һ�����䴦
			if (g_AUVPos.z<550)
			{
						// ȥײ����
						//��AUVͣ����ת-17��
				if (b>-17.0)
				{
					b -= 0.3;
						//	g_AuvMicroControl.x += 0.02;
					g_AUVVelocity = vec3(0.0,0,-0.0);
					g_AUVVelocityForDropSphere1 = vec3(0.0,0,-0.0);
					g_AUVVelocityForDropSphere2 = vec3(0.,0,-0.0);
				}
						
						//////////////////////////////////////////////////////////////////////////
						// ת���ʼǰ��
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
		track = true;// ��ס������
		//////////////////////////////////////////////////////////////////////////
		// Ǳ��ͣ��������������ĸ߶�
		if (isControlAuvForRedRotateAndUp) // Ϊ���˳� if (g_AUVPos.y>115.0)���ѭ��
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
				isControlAuvForRedRotate = true; // �����������ת
				isControlAuvForRedRotateAndUp = false;// �ر� ���������
			}
			
		}
		
		
		//////////////////////////////////////////////////////////////////////////
		// ��ת             ����������ת
		if (isControlAuvForRedRotate)
		{
			
			if(b<-9.0)
			{
				b += 0.3;
				//g_AuvMicroControl.x -= 0.025;
			}
			
			else    //��ת��ǰ��
			{
				g_AUVVelocity = vec3(0.085*2,0,-0.3*3);
				g_AUVVelocityForDropSphere1 = g_AUVVelocity;
				g_AUVVelocityForDropSphere2 = g_AUVVelocity;
			}
		}
		
		//��ײ����
		if (b1<68)
		{
			IsCollasionRedBall = true;
		}
		
		// ��ײ����
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
	// ��ײ�����˶���460�ٷ���450��ͣ����
	if (g_vSpherePos1.x>460)
	{
		isControlAuvForRedRotate = false;
		g_Sphere1Velocity = vec3(-0.05*3,0.0,0.2*3);// �����ٶ�
		g_AUVVelocity = vec3(-0.085*3,0,0.3*3);
		g_AUVVelocityForDropSphere1 = g_AUVVelocity;
		g_AUVVelocityForDropSphere2 = g_AUVVelocity;
	}
	
	
	if (g_vSpherePos1.x<450)
	{
		g_Sphere1Velocity = vec3(-0.0,0.0,0.0);
	}	
	
	// ײ������ Ǳ�����˵�390ʱͣ����
	//  ����Ǳ��ͣ����
	if (g_AUVPos.x<399)
	{
		g_AUVVelocity = vec3(-0.0,0.0,0.0);// Ǳ������
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
		//��תǱ��  Ϊ����ײ����������Ϻ���
		//////////////////////////////////////////////////////////////////////////]
		// ����λ�ø߶� ʹ��Ǳ��������������
		if(isControlAuvForBlueRotateAndDown)  // Ǳ��λ�������� ���رո�if
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
				isControlAuvForBlueRotate = true; // �����������ת
				isControlAuvForBlueRotateAndDown = false;// �ر� ������½�
			}
			
		}
		//////////////////////////////////////////////////////////////////////////
		
		
		if(isControlAuvForBlueRotate)
		{
			
			// ת������
			if (b<0)
			{
				b += 0.3;
			}
			
			//ת���ʼǰ��
			else
				
			{
				g_AUVVelocity = vec3(0.06,0,-0.3*2);
				g_AUVVelocityForDropSphere1 = g_AUVVelocity;//vec3(0.04,0,-0.3)
				g_AUVVelocityForDropSphere2 =g_AUVVelocity ;//vec3(0.04,0,-0.3)
				// Ϊ�˿���������Ǳ��  �����ӿ� 
				if (g_AjustLookAtForBlueSphere.x < 30)
				{
					g_AjustLookAtForBlueSphere.x += 0.05;
				}	
			}	
		}	
		//////////////////////////////////////////////////////////////////////////
		
		
		//ʵ��ײ��				
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
		//  ��������� ΢С�ص���Ǳ���ĸ߶�
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
		
		//����ǰ����430 �ٷ��ص�420ͣ����
		if (g_vSpherePos3.x<420)
		{
			IsRotateToSecondDoor = true;	// ͣ��ʱȥ����Ǳ��ת��ڶ�����					
			g_Sphere3Velocity = vec3(-0.0,0.0,0.0);						
		}
		
		
		if (g_vSpherePos3.x>430)
		{
			g_Sphere3Velocity = vec3(-0.1*3,0.0,0.4*3);// ���ٶȻص�420��
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
				//�����ӿ� Ϊ�˿���������Ǳ��
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
		g_AUVVelocity = vec3(-0.10*3,0,-0.01*3);// Ͷ�����  ����Я���������� ���ü��ٶ�
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
			g_AUVVelocityForDropSphere1 = vec3(-0.10*3,0,-0.01*3);//   ����������ٶ�
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
			g_AUVVelocityForDropSphere2 = vec3(-0.10*3,0,-0.01*3);//   ����������ٶ�
		}
	}
				
	else
	{
		g_AUVVelocity = vec3(0.0,0,0.00) ;//
		g_AUVVelocityForDropSphere2 = vec3(-0.0,0,-0.0);
		g_AUVVelocityForDropSphere1 = vec3(-0.0,0,0.0);
		IsChangeAuvVelocity = true;
	//	IsControlAuvBackYellowSphereDrop = true;// ͬʱ����ʱ
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
				IsControlAuvBackRedSphereDrop = true;// ͬʱ����ʱ
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
	if (IsGoToLeftForTheGarland) // n������
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
		
		// ��Ǳ��ǰ��
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
	if (IsGoToRightForTheGarland)//m ������
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
			//���Ż���һ������
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
			c = 180 - c + 10;	//  ע������ת�����Ƕ۽� ͨ��cos������������ ������180-c
			if (rotateY<(c+82.0))
			{
				rotateY += 0.5;
			}
			
			if (rotateY>=(c+82.0))
			{
				//cout<<"�������������";
				rotateY = c+82.0;
				IstTurnToDeepSea = true;
				isRight = true;
				isGoToShallowSea = false; // ��ס����ĳ���
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
			g_GarlandVelocityLeft.y = 0.8;// ������ںܴ��bug ��0.3��ʱ�����  1.3ʱ Ǳ����ǰ����
			g_GarlandVelocityLeft.z = 0.0;	
			//���Ż���һ������
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
			d = 180 - d + 10;	//  ע������ת�����Ƕ۽� ͨ��cos������������ ������180-c
			if (rotateY<(d+82.0))
			{
				rotateY += 0.5;
			}
			
			if (rotateY>=(d+82.0))
			{
		
				rotateY = d+82.0;
				IstTurnToDeepSea = true;
				isLeft = true;
				isGoToShallowSea = false; // ��ס����ĳ���
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
			g_AUVVelocity = Normalize(tempForGarlandvelocity); // ûͣ����ʱ���ٶ�
		}		
			
		if(g_AUVPos.z>=560)   //ԭʼ������560
		{
			g_AUVPos.z = 560;   // Ǳ����ͣ��λ�� x z
			g_AUVPos.x = -200;
			IsControlLastStop = true;    //  ����Ǳ��ͣ���� 
			g_AUVVelocity = vec3(0,0,0);
			isRightPichCasing = true;
			
		}			
	}
}




void GoToDeepSeaFromLeft() 
{
	if (isLeft)
	{		

		//   �յ��׹ܵ�λ�� ��0,80,618)

		vec3 tempForGarlandvelocity1 = vec3(0+600.0083,80-80,618-151.303);
	
		
		if (!IsControlLastStop)
		{
			g_AUVVelocity = Normalize(tempForGarlandvelocity1); // ûͣ����ʱ���ٶ�

		}	
		
					
		if(g_AUVPos.z>=560)  //ԭʼ������560
		{
			g_AUVPos.z = 560;   // Ǳ����ͣ��λ�� x z
			g_AUVPos.x = -200;  //ԭʼ������0
			IsControlLastStop = true;    //  ����Ǳ��ͣ���� 
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
	if (camer<=1)// ����
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
	
	else if (camer<=2) // ����
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
	
	else if (camer<=3)  // ����ͼ(�������ǿ����Ͻ�)
	{
		gluLookAt(-150,530,-650,  500.48, 0, 400,  0,1, 0);
	}
	
	
	

	else if (camer<=4)  // ����ͼ ƫǰ��
	{	
		gluLookAt(-950  + g_ChangeEyeForBoxes.x ,530 + g_ChangeEyeForBoxes.y,450 + g_ChangeEyeForBoxes.z,  500.48, 0, 400,  0, 1, 0);
	}

	else if(camer<=5)// Ϊ�˿��ι�ϸ��
	{
		gluLookAt(-250  + g_ChangeEyeForBoxes.x ,530 + g_ChangeEyeForBoxes.y,450 + g_ChangeEyeForBoxes.z,  500.48, 0, 400,  0, 1, 0);
	}


	


	if (isChangeLookAtForOverlook)  // ���� ����
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
	glPushMatrix();//��ջ
	//////////////////////////////////////////////////////////////////////////
	glEnable(GL_TEXTURE_2D);	
	glBindTexture( GL_TEXTURE_2D, ye.texture[0] );
	//glColor4f(0.0f,0.5f,1.0f,0.3f);//����ı���ɫ��
	DrawTerrain();//�����׵���
//	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	glPushMatrix();
//	glEnable(GL_TEXTURE_2D);
	glTranslatef(-210,0,600);
	glBindTexture( GL_TEXTURE_2D, ye.texture[1] );
	circle(250,200,30,3000);    //����ˮ��
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}


void DrawAuvAndGarland()
{
	glPushMatrix();	
	Control3DS();//��Ǳ��
	glPopMatrix();

	glPushMatrix();
	garland();//����
	glPopMatrix();
}

void DrawDoor()
{
	glPushMatrix();
	glTranslatef(400,0,600);
	glRotatef(-60,0,1,0);
    draw1Door(0,200,0);// ��ʼ��
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(250,0,150);
	glRotatef(-30,0,1.0,0);
	DrawDoor(0,50,0);//��һ������
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-300,0,50);
	DrawDoor(0,50,-10);//�ڶ�������
	glPopMatrix();
}

void DrawGuideLine()
{
	glPushMatrix();
	glTranslatef(400,0,550);
	glRotatef(-270,0,1.0,0.0);
	DrawXian(0,15,0);//����һ
	glPopMatrix();

	glPushMatrix();
	//glTranslatef(450,0,300);
	glTranslatef(430,0,260);
	glRotatef(-30,0,1,0);
	DrawXian(0,15,0);//����2
	glPopMatrix();
	
	// ����3
	glPushMatrix();

	glTranslatef(200,0,100);
	glRotatef(-30,0,1,0);
	DrawXian(0,15,0);
	glPopMatrix();
	
	// ����4
	glPushMatrix();
	glTranslatef(200,0,150);
	glRotatef(-120,0,1,0);
	DrawXian(0,15,0);
	glPopMatrix();

	// ����5
	glPushMatrix();
	glTranslatef(-100,0,0);
	glRotatef(30,0,1,0);
	DrawXian(0,15,0);
	glPopMatrix();
	
	// ����6
	glPushMatrix();
	glTranslatef(-75,0,50);
	glRotatef(-90,0,1,0);
	DrawXian(0,15,0);
	glPopMatrix();
}

void DrawBallForCollision()
{
	glPushAttrib(GL_CURRENT_BIT);
	
	glColor3f(1.0,1.0,0.0);//����2����  ��
	
	glPushMatrix();
	glTranslatef(g_vSpherePos2.x,g_vSpherePos2.y,g_vSpherePos2.z);
	glRotatef(-60,0,1.0,0);
	glutSolidSphere(10.0,32,32);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(g_vSpherePos1.x,g_vSpherePos1.y,g_vSpherePos1.z);
	glColor3f(1.0,0.0,0.0);//����һ����  ��
	//glRotatef(-60,0,1.0,0);
	glutSolidSphere(10.0,32,32);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(g_vSpherePos3.x,g_vSpherePos3.y,g_vSpherePos3.z);
	glColor3f(0.0,1.0,0);//����������  ��
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
	// �̶��׹�
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
//	glTranslatef(50,150,600);//ԭʼ����
	glTranslatef(-150,150,600);
	glColor3f(1.0,1.0,0.0);
	m_obj.cylinder(18,2.5,2.5);		
	glPopMatrix();
	
	// ��Ҫ�ƶ����׹�

	glPushMatrix();
	glColor3f(0,1,1);
	glTranslatef(casingMov.x,casingMov.y,casingMov.z);
//	glTranslatef(50,150,600); //ԭʼ����
	glTranslatef(-150,150,600);
	m_obj.cylinder(12,5.5,5.5);		
	glPopMatrix();

//	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	glColor4f(1.0,0.0,0.0,0.0);	
//	glTranslatef(0,100,618);   //ԭʼ����
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
	//�����ں�
	glEnable(GL_BLEND);
	//����Դ�ں�������Ŀ������
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	//ˮ��Ϊ�ӽ�����ɫ����������AlphaΪ0.3
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
	//�����ں�
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
	//             �������
	// ���������  ����
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
	//     ���������  ����
	glPushMatrix();
	//glLineWidth(10);
	//	glColor3f(1.0,1.0,0.0);
	glBegin(GL_LINES);
	glVertex3f(450,0,370);
	glVertex3f(g_vSpherePos1.x,g_vSpherePos1.y,g_vSpherePos1.z);
	glEnd();
	glPopMatrix();
	
	//  ���������  
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
	glPushMatrix();//������ 2
	glPushAttrib(GL_CURRENT_BIT);
	glTranslatef(g_AUVPosForDropSphere2.x + g_AuvMicroControl.x + g_AuvMicroY.x + g_vDropSphereMove2.x -3,  
		g_AUVPosForDropSphere2.y + g_AuvMicroControl.y + g_AuvMicroY.y + g_vDropSphereMove2.y,
		g_AUVPosForDropSphere2.z + g_AuvMicroControl.z + g_AuvMicroY.z + g_vDropSphereMove2.z);//�����1
	
	glRotated(-180+b,0.0,1.0,0.0);	
	glRotatef(rotateY,0,1,0);
	
	glColor3f(1.0,0.0,0.0);
	glutSolidSphere(2.5,30,30);
	glPopAttrib();
	glPopMatrix();
	
	glPushMatrix();//������ 1
	glPushAttrib(GL_CURRENT_BIT);
	glTranslatef(g_AUVPosForDropSphere1.x + g_AuvMicroControl.x + g_AuvMicroY.x + g_vDropSphereMove1.x - 3,
		g_AUVPosForDropSphere1.y + g_AuvMicroControl.y + g_AuvMicroY.y + g_vDropSphereMove1.y ,
		g_AUVPosForDropSphere1.z + g_AuvMicroControl.z + g_AuvMicroY.z + g_vDropSphereMove1.z);// �����1
	
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
	glPushMatrix();//������ 1
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
	glPushMatrix();//������ 2
	glPushAttrib(GL_CURRENT_BIT);
	glTranslatef((g_AUVPos.x + g_AuvMicroControl.x + g_AuvMicroY.x),
		(g_AUVPos.y + g_AuvMicroControl.y + g_AuvMicroY.y),
		(g_AUVPos.z + g_AuvMicroControl.z + g_AuvMicroY.y));
	glTranslatef(g_vPitchSphereMove2.x,g_vPitchSphereMove2.y,g_vPitchSphereMove2.z);
	glColor3f(0,1,0);
	glutSolidSphere(5,30,30);
	glPopAttrib();
	glPopMatrix();
	
	glPushMatrix();//������ 3
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
		// ����������������ת
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
		  
		  
		  //���ƺ��̻����ײ��
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
		  
		  // �����½���
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
	case GLUT_KEY_LEFT://�����ϵ��������¼�]
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
		// �仯��ֵ
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
	glutReshapeFunc(resizeGL);//�޸ĵĵط�
   
//	glutDisplayFunc(Display); 
	glutDisplayFunc(paintGL);  //�޸ĵĵط�

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
	// ���ƹ���
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
		// �����й��¼�
		if (ThirdTrack)
		{
			CollasionBuleBall();	
		}
		//////////////////////////////////////////////////////////////////////////
		//  Ǳ��ת��ڶ�����
		if (IsRotateToSecondDoor)
		{	
			// ͣ���� ת����
			auvStop();
			// ����Ǳ��ͣ������ת  ��ת��ȥ�ڶ����ŵ�ʱ��   ��תǱ�� ��Ǳ��������
			if (!IsStopRotateAndChangeLookAtForSecondDoor)
			{	
				RotateAuvAndEye();
			}	
		}	
		//////////////////////////////////////////////////////////////////////////	
		// ����Ǳ��������������  ΪͶ����׼������
		//////////////////////////////////////////////////////////////////////////
		if (!isBackForPitch)
		{
		// ��g_AUVPos.x2�ﵽ00��ʱ����Ǳ������ͣ���� ׼������	
			auvStopForPitch();		
		}

		// Ͷ����� ��ʼ��ǰ��	
		else
		{
			// ��תǱ��
			RotateAUVForPitch();

			//////////////////////////////////////////////////////////////////////////			
			//  �ı俴�����ĵ�  Ϊ�˱��⵱Ǳ������ooo��ʱ ������ǰ�������
			RotateEyeForPitch();
			//////////////////////////////////////////////////////////////////////////
			//�����¼�
			if (!IsChangeAuvVelocity)
			{
				StopForBox();	
			}	
			//////////////////////////////////////////////////////////////////////////
			DropSphere1IntoBox();
			DropSphere2IntoBox();
			// ����������
			//////////////////////////////////////////////////////////////////////////
			DropBallIntoBox();
			//////////////////////////////////////////////////////////////////////////
			//�����򶼵���ʱ ���������¼�
			if (IsControlAuvBackRedSphereDrop && IsControlAuvBackYellowSphereDrop)
			{
				// ת���������
				
				//////////////////////////////////////////////////////////////////////////	
				TurnToThirdDoor();	
			}	
		}
		//////////////////////////////////////////////////////////////////////////
		PitchBalls();
		//////////////////////////////////////////////////////////////////////////
	
		//////////////////////////////////////////////////////////////////////////	
		// k
		if (!stop)// ���µ��ݺ�
		{
			CollasionYellowReady(); // ����Ͳ��÷���
		}
		//    ��Ǳ���ں����Ϸ�ͣ����  Ϊ������׼��
		AUVStopOnBox();
		//////////////////////////////////////////////////////////////////////////
		//   ǳ����
		if (isGoToShallowSea)
		{		
			AuvStopForGarland();
			ControlAUVToRight();
			ControlAUVToLeft();
			//////////////////////////////////////////////////////////////////////////
		}
	// 	//////////////////////////////////////////////////////////////////////////
	// 	//  ���ƻ����˶�
		//��������˶�
	ControlRightGarland();

	// ������໨���˶�
	ControlLeftGarland();
	//////////////////////////////////////////////////////////////////////////	
	}
	//////////////////////////////////////////////////////////////////////////
	//  ����ǰ���if��Ӧ   IsGlobalControl  ����ǰ�����в���
	else
	{
		if (IstTurnToDeepSea)
		{
			//cout<<"�Ѿ��������"<<endl;
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
	//������
	DrawHand();
	DrawBox();
	DrawCasingAndBoard();
	//��ˮ��
	DrawBubbles();
	
	//	DrawWaters();
	////////////////////////////////////////////////////////////////////////////
	IdelPos();// ����λ��	
//	glutSwapBuffers();	
	/*glutPostRedisplay();	*///2015.08.02HL�޸�  Ӱ���������ʾ
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
	//������
	DrawHand();
	DrawBox();
	DrawCasingAndBoard();
	//��ˮ��
	DrawBubbles();
	
	//	DrawWaters();
	////////////////////////////////////////////////////////////////////////////
	IdelPos();// ����λ��	
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
	//������
	DrawHand();
	DrawBox();
	DrawCasingAndBoard();
	//��ˮ��
	DrawBubbles();
	
	//	DrawWaters();
	////////////////////////////////////////////////////////////////////////////
	IdelPos();// ����λ��	
	//glutSwapBuffers();	
	/*glutPostRedisplay();*///201508.05 HL�޸�   ɾ��
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
	
	glViewport(0,0,width,height);//�����ӿڴ�С
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-10, 10, -10, 10,10, 2000);//˵������͸��ͶӰ
	gluPerspective(90, 1, 10, 2000);//����ĺ�����Ŀ���ת��
    Display();
////	glutPostRedisplay();
}
  

void paintViewportLeft()
{
   	glViewport(0,0,width/1.7,height);
//	gluPerspective(50, (GLfloat)width/(GLfloat)height,1.5,20.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-10, 10, -10, 10,10, 2000);//˵������͸��ͶӰ
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
	glFrustum(-10, 10, -10, 10,10, 2000);//˵������͸��ͶӰ
	Display1();
//	glutPostRedisplay();
}
void  paintViewportRight1()
{
	glViewport(width/1.7,0,width/1.7,height/2.6);
//	gluPerspective(50, (GLfloat)width/(GLfloat)height,1.5,20.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-10, 10, -10, 10,10, 2000);//˵������͸��ͶӰ
    Display2();
//	glutPostRedisplay();
}

void resizeGL(int w, int h)
{
	//�ڻ����������ù���
	//glMatrixMode(GL_PROJECTION);  
 //   glLoadIdentity();  
 //   gluOrtho2D(0, 1 , 0, 1);  //�ü����ڶ���
 //   glMatrixMode(GL_MODELVIEW);  
	//glLoadIdentity();
  
	
    width = w;  
    height = h; 
	glutPostRedisplay();//���ڸı��Ҫ�ص���ʾ

}
//////////////////////////////////////////////////////////////////////////


