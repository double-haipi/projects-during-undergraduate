// loadimage1.h: interface for the loadimage class.
//
//////////////////////////////////////////////////////////////////////

#pragma once
#include "StdAfx.h"
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <fstream>
#include <GL/glaux.h>
#include "loadimage.h"

class loadimage  
{
public:
	loadimage();
   virtual	~loadimage();

   
public:
	GLuint		texture[12]; 
    AUX_RGBImageRec *TextureImage[12];
	int LoadGLTextures(char* FileName,int i);
	int LoadGLTexturesFor();
    AUX_RGBImageRec *LoadBMP(char *Filename);
	int deletetexture();

};


