// loadimage1.cpp: implementation of the loadimage class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "loadimage.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
char* pic[]={
	"a.bmp","111.bmp"/*"FLOOR24.bmp"*/,"bai.bmp","hei.bmp","DX.bmp",//0-4
"XX.bmp","DO.bmp","XO.bmp","red0.bmp","red1.bmp",		 //5-9
"blue0.bmp","blue1.bmp","seawater1.bmp"};	

loadimage::loadimage()
{
	//////////////////////////////////////////////////////////////////////////
	//多个贴图时，依次绑定，后面依次是0,1,2,3……
	//这么做的好处是，场景中的纹理不会乱套
	// 	LoadGLTextures("FLOOR33.bmp",0);
	// 	LoadGLTextures("FLOOR22.bmp",1);
	// 	LoadGLTextures("bai.bmp",2);
	// 	LoadGLTextures("hei.bmp",3);
}


loadimage::~loadimage()
{
	
}

int loadimage::LoadGLTextures(char* FileName,int i)
{
	int Status=FALSE;	
	
    // 产生和绑定纹理  
    // 载入纹理 
	memset(TextureImage,0,sizeof(void *)*2);
	
	if (TextureImage[i]=LoadBMP(FileName))
	{
		Status=TRUE;
		glGenTextures(1, &texture[i]);					// 创建纹理	
		// 使用来自位图数据生成的典型纹理
		glBindTexture(GL_TEXTURE_2D, texture[i]);//创建纹理对象
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[i]->sizeX, TextureImage[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[i]->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// 线形滤波
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// 线形滤波
	}
	if (TextureImage[i])							// 纹理是否存在
	{
		if (TextureImage[i]->data)					// 纹理图像是否存在
		{
			free(TextureImage[i]->data);				// 释放纹理图像占用的内存
		}
		
		free(TextureImage[i]);						// 释放图像结构
	}
	return Status;			
}


int loadimage::LoadGLTexturesFor()
{
	int Status=FALSE;	
	int po=sizeof(pic)/4;
    // 产生和绑定纹理  
    // 载入纹理 
	memset(TextureImage,0,sizeof(void *)*po);
	for(int i=0;i<po;i++)
	{
		if (TextureImage[i]=LoadBMP(pic[i]))
		{
			Status=TRUE;
			glGenTextures(1, &texture[i]);					// 创建纹理	
			// 使用来自位图数据生成的典型纹理
			glBindTexture(GL_TEXTURE_2D, texture[i]);//创建纹理对象
			glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[i]->sizeX, TextureImage[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[i]->data);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// 线形滤波
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// 线形滤波
		}
		if (TextureImage[i])							// 纹理是否存在
		{
			if (TextureImage[i]->data)					// 纹理图像是否存在
			{
				free(TextureImage[i]->data);				// 释放纹理图像占用的内存
			}
			
			free(TextureImage[i]);						// 释放图像结构
		}
	}
	return Status;			
}




AUX_RGBImageRec *loadimage::LoadBMP(char *Filename)
{
	  	FILE *File=NULL;									// File Handle
		
		if (!Filename)										// Make Sure A Filename Was Given
		{
			return NULL;									// If Not Return NULL
		}
		
		File=fopen(Filename,"r");
		if (File)											// Does The File Exist?
		{
			fclose(File);	// Close The Handle
			
			return auxDIBImageLoad(Filename);
		}
		return NULL;
}

int loadimage::deletetexture()
{
	glDeleteTextures(1,texture);
	return 0;
}
