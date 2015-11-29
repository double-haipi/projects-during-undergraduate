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
	//�����ͼʱ�����ΰ󶨣�����������0,1,2,3����
	//��ô���ĺô��ǣ������е�����������
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
	
    // �����Ͱ�����  
    // �������� 
	memset(TextureImage,0,sizeof(void *)*2);
	
	if (TextureImage[i]=LoadBMP(FileName))
	{
		Status=TRUE;
		glGenTextures(1, &texture[i]);					// ��������	
		// ʹ������λͼ�������ɵĵ�������
		glBindTexture(GL_TEXTURE_2D, texture[i]);//�����������
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[i]->sizeX, TextureImage[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[i]->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// �����˲�
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// �����˲�
	}
	if (TextureImage[i])							// �����Ƿ����
	{
		if (TextureImage[i]->data)					// ����ͼ���Ƿ����
		{
			free(TextureImage[i]->data);				// �ͷ�����ͼ��ռ�õ��ڴ�
		}
		
		free(TextureImage[i]);						// �ͷ�ͼ��ṹ
	}
	return Status;			
}


int loadimage::LoadGLTexturesFor()
{
	int Status=FALSE;	
	int po=sizeof(pic)/4;
    // �����Ͱ�����  
    // �������� 
	memset(TextureImage,0,sizeof(void *)*po);
	for(int i=0;i<po;i++)
	{
		if (TextureImage[i]=LoadBMP(pic[i]))
		{
			Status=TRUE;
			glGenTextures(1, &texture[i]);					// ��������	
			// ʹ������λͼ�������ɵĵ�������
			glBindTexture(GL_TEXTURE_2D, texture[i]);//�����������
			glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[i]->sizeX, TextureImage[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[i]->data);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// �����˲�
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// �����˲�
		}
		if (TextureImage[i])							// �����Ƿ����
		{
			if (TextureImage[i]->data)					// ����ͼ���Ƿ����
			{
				free(TextureImage[i]->data);				// �ͷ�����ͼ��ռ�õ��ڴ�
			}
			
			free(TextureImage[i]);						// �ͷ�ͼ��ṹ
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
