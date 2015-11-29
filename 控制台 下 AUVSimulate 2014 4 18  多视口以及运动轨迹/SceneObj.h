// SceneObj.h: interface for the SceneObj class.
//
//////////////////////////////////////////////////////////////////////

#pragma once
#include "StdAfx.h"
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/glaux.h>
#include "loadimage.h"

class SceneObj 
{
public:
	SceneObj();
	virtual ~SceneObj();
	
public:
	void redBox();
	void blueBox();
	void TopBox();
	void BottomBox();
	void WriteBox();
	void BlackBox(char* boxT);
	void CircleBox(int xj,int yj ,int zj);
	void Box();
	void texture();
    void cylinder(float hight, float baseRadius, float topRadius );
	void Board(float length, float width);
	void RenderSkyBox(float sx,float sy,float sz);
	
private:
	GLUquadricObj	*qobj1;
	
};


