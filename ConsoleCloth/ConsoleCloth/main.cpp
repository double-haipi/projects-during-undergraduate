//
//  main.cpp
//  MatrixGL


#include <iostream>

#ifdef __APPLE__

#include <glut/glut.h>
#else
//Windows系统glut
#include <gl/glut.h>
#endif
#include "camera.h"
#include "lighting.h"
#include "volumetricMesh.h"
#include "sceneObjectDeformable.h"
#include "btSoftBody.h"
#include "btQuickprof.h"
#include "btAlignedObjectArray.h"
#include "btBulletDynamicsCommon.h"
#include "btSoftBodyHelpers.h"
#include "btDynamicsWorld.h"
#include "btSoftRigidDynamicsWorld.h"
#include "btSoftBodyRigidBodyCollisionConfiguration.h"

// h-file for bullet triangle mesh
#include "cloth.h"
///////////////////////////////////////////////////////////////////////////////////////////////////
// Global Variable defination
const int maxProxies = 32766;
const int maxOverlap = 65535;

// dynamic world gravity
btVector3 d_gravity(0.0, -10.0, 0.0);

// Cloth obj mesh file
const char* ClothMeshFilename = "../models/cloth.obj";
double *d_RestDeformablePosition = NULL, *d_DeformableDispalcement = NULL;
///////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// \brief camera and light
// camera radius
double cameraRadius = 12.6;
// Spherical camera
SphericalCamera *camera = NULL;
// Lighting
Lighting *lighting = NULL;

btSoftBody* m_pCloth = NULL;
SceneObjectDeformable *deformableClothMesh = NULL, *rigidBox = NULL;

//////////////////////////////////////////////////////////
/// Bullet Physics
btCollisionObject *bt_Box = NULL;
btAlignedObjectArray<btCollisionShape*> m_collisionShapes;
btBroadphaseInterface* m_broadphase = NULL;
btCollisionDispatcher* m_dispatcher = NULL;
btConstraintSolver* m_solver = NULL;
btDynamicsWorld* m_dynamicWorld = NULL;
btSoftBodyWorldInfo m_softBodyWorldInfo;
btDefaultCollisionConfiguration* m_collisionConfiguration = NULL;

btSoftRigidDynamicsWorld* getSoftDynamicWorld(){
	return (btSoftRigidDynamicsWorld*)m_dynamicWorld;
}

// mouse pose
int g_vMousePos[2];
// mouse button
int g_leftButton, g_MidButton, g_rightButton;

void InitModel(){
	// deformableObjRenderingMesh
	deformableClothMesh = new SceneObjectDeformable(ClothMeshFilename);
	deformableClothMesh->ResetDeformationToRest();
	deformableClothMesh->BuildNeighboringStructure();
	deformableClothMesh->BuildNormals();
	deformableClothMesh->SetUpTextures(SceneObject::MODULATE, SceneObject::NOMIPMAP);

	rigidBox = new SceneObjectDeformable("../models/box.obj");
	rigidBox->ResetDeformationToRest();
	rigidBox->BuildNeighboringStructure();
	rigidBox->BuildNormals();
	rigidBox->SetUpTextures(SceneObject::MODULATE, SceneObject::NOMIPMAP);
}
void InitPhysics(){
	// CollisionShape[0] == BOX
	btCollisionShape *groundBox = new btBoxShape(btVector3(100,1.5,100));
	m_collisionShapes.push_back(groundBox);

	// CollisionShape[1] == Sphere
	btCollisionShape *t_box = new btBoxShape(btVector3(1.5,1.5,1.5));
	m_collisionShapes.push_back(t_box);

	m_collisionConfiguration = new btSoftBodyRigidBodyCollisionConfiguration();
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
	m_softBodyWorldInfo.m_dispatcher = m_dispatcher;

	btVector3 worldAabbMin(-1000,-1000,-1000);
	btVector3 worldAabbMax( 1000, 1000, 1000);

	m_broadphase = new btAxisSweep3(worldAabbMin, worldAabbMax, maxProxies);
	m_softBodyWorldInfo.m_broadphase = m_broadphase;

	btSequentialImpulseConstraintSolver *solver = new btSequentialImpulseConstraintSolver();
	m_solver = solver;

	// new SoftRigidDynamicWorld
	btDiscreteDynamicsWorld *world = new btSoftRigidDynamicsWorld(m_dispatcher,m_broadphase,m_solver,m_collisionConfiguration);
	m_dynamicWorld = world;
	m_dynamicWorld->setGravity(d_gravity);
	m_dynamicWorld->getDispatchInfo().m_enableSPU = true;

	//create ground object
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin(btVector3(0,-1.6,0));

	btCollisionObject* newOb = new btCollisionObject();
	newOb->setWorldTransform(tr);

	//[0]ground
	newOb->setCollisionShape(m_collisionShapes[0]);
	m_dynamicWorld->addCollisionObject(newOb);

	//[1]Box
	bt_Box = new btCollisionObject();
	bt_Box->setCollisionShape(m_collisionShapes[1]);
	m_dynamicWorld->addCollisionObject(bt_Box);

	tr.setIdentity();
	tr.setOrigin(btVector3(1.5,1.52,0));
	bt_Box->setWorldTransform(tr);

	m_softBodyWorldInfo.m_gravity = d_gravity;
	m_softBodyWorldInfo.m_sparsesdf.Initialize();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Client reset sence
	///
	m_softBodyWorldInfo.m_sparsesdf.Reset();
	m_softBodyWorldInfo.air_density    = (btScalar)1.2;
	m_softBodyWorldInfo.water_density  = 0.0;
	m_softBodyWorldInfo.water_offset   = 0;
	m_softBodyWorldInfo.water_normal   = btVector3(0,0,0);
	m_softBodyWorldInfo.m_gravity      = d_gravity;

	/// \Soft Cloth Body
	m_pCloth=btSoftBodyHelpers::CreateFromTriMesh(m_softBodyWorldInfo,gVertices,
		&gIndices[0][0],NUM_TRIANGLES);
	m_pCloth->generateBendingConstraints(2);
	m_pCloth->m_cfg.piterations=12;
	//m_pCloth->m_cfg.kDF				=	0.5;
	//m_pCloth->m_cfg.kMT				=	0.05;
	m_pCloth->m_cfg.collisions|=btSoftBody::fCollision::VF_SS;
	m_pCloth->setTotalMass(5,true);
	m_pCloth->m_materials[0]->m_kLST = 0.06;
	m_pCloth->m_materials[0]->m_kAST = 0.04;
	getSoftDynamicWorld()->addSoftBody(m_pCloth);

	btSoftBody::tNodeArray &nodes(m_pCloth->m_nodes);
	d_RestDeformablePosition = (double*)calloc(3 * nodes.size(), sizeof(double));
	d_DeformableDispalcement = (double*)calloc(3 * nodes.size(), sizeof(double));
	for(int i=0; i< nodes.size(); ++i){
		d_RestDeformablePosition[3*i] = nodes[i].m_x.x();
		d_RestDeformablePosition[3*i + 1] = nodes[i].m_x.y();
		d_RestDeformablePosition[3*i + 2] = nodes[i].m_x.z();

		// Fix an edge
		if(nodes[i].m_x.z() < 0.1)
			m_pCloth->setMass(i,0);
	}
}

void InitializeGL()
{
	// Background color
	glClearColor(0.0f,0.5f,0.5f,1.0f);
	// Enable Depth Test
	glEnable(GL_DEPTH_TEST);
	// Smooth shade
	glShadeModel(GL_SMOOTH);

	InitModel();

	InitPhysics();

	///////////////////////////////////////////////////////////////////////////////////////////
	/// Setup Lighting and Camera
	/// !1
	lighting = new Lighting();
	lighting->ModifyLight(3, -10.0f, 20.0f, 20.0f);
	lighting->ModifyLight(6,  10.0f, 20.0f, 20.0f);

	//# define M_PI		3.14159265358979323846	/* pi */
	double cameraLongitude = -103.0, cameraLattitude = 8.0;
	double upPos[3] = {0,1,0}, focusPos[3] = {0.0,3.0,0.0};
	camera = new SphericalCamera(cameraRadius, 1.0 * cameraLongitude / 360 *(2*M_PI), 1.0 * cameraLattitude / 360*(2*M_PI), focusPos,upPos,0.05,1.0);
}

void IdleFunc()
{
	// Fixed timestep
	if(m_dynamicWorld)
		m_dynamicWorld->stepSimulation(1.0/60);

	// Update position
	if(NULL != m_pCloth){
		btSoftBody::tNodeArray &nodes(m_pCloth->m_nodes);
		for(int i=0; i<nodes.size(); ++i){
			d_DeformableDispalcement[3*i + 0] = nodes[i].m_x.x() - d_RestDeformablePosition[3*i + 0];
			d_DeformableDispalcement[3*i + 1] = nodes[i].m_x.y() - d_RestDeformablePosition[3*i + 1];
			d_DeformableDispalcement[3*i + 2] = nodes[i].m_x.z() - d_RestDeformablePosition[3*i + 2];
		}
	}

	deformableClothMesh->SetVertexDeformations(d_DeformableDispalcement);

	glutPostRedisplay();
}

//渲染函数
void Rendering()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	if(camera)
		camera->Look();

	glEnable(GL_TEXTURE_2D);
	lighting->GetLightPtr(3)->b_Enabled = true;
	lighting->GetLightPtr(6)->b_Enabled = true;
	//lighting->LightScene();

	glPushMatrix();
	GLfloat m[16];
	bt_Box->getWorldTransform().getOpenGLMatrix(m);
	glMultMatrixf(m);
	rigidBox->Render();
	glPopMatrix();
	deformableClothMesh->Render();

#define XLength 100
#define ZLength 100
#define Spacing 5

	int current = 0;
	// Draw Floor
	glBegin(GL_QUADS);
	for(int i= - XLength/2; i< XLength/2; i+= Spacing)
		for(int j= -ZLength / 2; j< ZLength/2; j+= Spacing){
			if(current %2 == 0)
				glColor3f(0.1f,0.1f,0.1f);
			else
				glColor3f(0.8f,0.8f,0.8f);
			glVertex3i(i,0,j);
			glVertex3i(i,0,j+Spacing);
			glVertex3i(i+Spacing,0,j+Spacing);
			glVertex3i(i+Spacing,0,j);
			if(j+Spacing < ZLength/2)
				current++;
		}
		glEnd();

		glColor3f(1.0f,1.0f,1.0f);
		// Show m_pCloth.nodes
#if 0
		glPointSize(4);
		glBegin(GL_POINTS);
		btSoftBody::tNodeArray &nodes(m_pCloth->m_nodes);
		for(int i=0; i<nodes.size(); i++){
			glVertex3f(nodes[i].m_x.x(),nodes[i].m_x.y(),nodes[i].m_x.z());
		}
		glEnd();
#endif

	glutSwapBuffers();
}

void GLReshape(int width,int height)
{
	if(0 == height)
		height = 1;
	glViewport(0,0,width,height);
	// frustrum
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// ensure the display ratio
	gluPerspective(45.0,(double)width/height, cameraRadius*0.01, cameraRadius*100);
	glMatrixMode(GL_MODELVIEW);
}

void Keypressed(unsigned char key, int x, int y){

	if(key == 27)
		exit(0);

	if(key == 'R' || key == 'r'){
		if(NULL!=m_pCloth){
			btSoftBody::tNodeArray &nodes(m_pCloth->m_nodes);
			for(int i=0; i<nodes.size(); ++i){
				nodes[i].m_x.setX(d_RestDeformablePosition[3*i]);
				nodes[i].m_x.setY(d_RestDeformablePosition[3*i + 1]);
				nodes[i].m_x.setZ(d_RestDeformablePosition[3*i + 2]);

				nodes[i].m_v.setX(0);nodes[i].m_v.setY(0);nodes[i].m_v.setZ(0);
			}
		}
	}
}

void MousePressed(int button, int state, int x, int y){
	g_vMousePos[0] = x;
	g_vMousePos[1] = y;

	if(state == GLUT_DOWN){
		if(button == GLUT_LEFT_BUTTON)
			g_leftButton = 1;
		else if(button == GLUT_RIGHT_BUTTON)
			g_rightButton = 1;
	}
	else{
		g_leftButton = 0;
		g_rightButton = 0;
	}
}

void MouseMotion(int x, int y){
	int mouseDeltaX = x - g_vMousePos[0];
	int mouseDeltaY = y - g_vMousePos[1];

	if(g_leftButton){
		static double factor = 0.1;
		camera->ZoomIn(cameraRadius * factor * mouseDeltaY);
	}
	else if(g_rightButton){
		static double factor = 0.2;
		camera->MoveRight(factor * mouseDeltaX);
		camera->MoveUp(factor * mouseDeltaY);
	}

	g_vMousePos[0] = x;
	g_vMousePos[1] = y;
}

int main(int argc, char * argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	GLsizei iWidth = 800;
	GLsizei iHeight = 600;

	//根据屏幕分辨率，让窗口始终位于窗口中间
	GLsizei wpx = 1240/2 - iWidth/2;
	GLsizei wpy = 1080/2 - iHeight/2;

	glutInitWindowSize(iWidth, iHeight);
	glutInitWindowPosition(wpx, wpy);

	glutCreateWindow("Xcode Glut Demo");

	glutReshapeFunc(GLReshape);
	glutDisplayFunc(Rendering);
	glutIdleFunc(IdleFunc);
	glutKeyboardFunc(Keypressed);
	glutMouseFunc(MousePressed);
	glutMotionFunc(MouseMotion);

	//在mac下,Opengl指令都应放在glutCreateWindow后
	glEnable(GL_DEPTH_TEST);

	InitializeGL();

	glutMainLoop();

	return 0;
}

