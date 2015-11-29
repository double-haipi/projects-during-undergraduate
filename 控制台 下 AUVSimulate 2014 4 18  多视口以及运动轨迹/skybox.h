#ifndef _SKYBOX_H
#define _SKYBOX_H
#define WIDTH 100

class SkyBox
{
private:
	UINT		g_cactus[5];	                    //贴图
	void        texture(UINT textur);
	bool        LoadT8(char *filename, GLuint &texture);
public:
	SkyBox();
	~SkyBox();
	void Render(float sx,float sy,float sz);
};

SkyBox::SkyBox()
{
	LoadT8("res/2Back.bmp",g_cactus[0]);	//天空贴图后
	LoadT8("res/2Front.bmp",g_cactus[1]);	//天空贴图前
	LoadT8("res/2Top.bmp",	 g_cactus[2]);	//天空贴图顶
	LoadT8("res/2Left.bmp", g_cactus[3]);	//天空贴图左
	LoadT8("res/2Right.bmp",g_cactus[4]);	//天空贴图右
}

SkyBox::~SkyBox()
{
	for(int i=0;i<5;i++) 
		glDeleteTextures(1, &g_cactus[i]);
	glDisableClientState(GL_VERTEX_ARRAY);
}

bool SkyBox::LoadT8(char *filename, GLuint &texture)//调8位贴图
{	
	AUX_RGBImageRec *pImage = NULL;
	pImage = auxDIBImageLoad(filename);	 // 装入位图			
	if(pImage == NULL)	return false;	 // 位图没装入返回错误
	glGenTextures(1, &texture);			 // 生成贴图(纹理)
	glBindTexture    (GL_TEXTURE_2D,texture);// 捆绑贴图(纹理)
	gluBuild2DMipmaps(GL_TEXTURE_2D,4,   //
					  pImage->sizeX,     // 图形宽
					  pImage->sizeY,     // 图形高
					  GL_RGB, GL_UNSIGNED_BYTE,
					  pImage->data       // 图形数据
					 );
	free(pImage->data);                  // 释放位图数据占据的内存资源
	free(pImage);	
	return true;                         // 返回成功
}

void SkyBox::Render(float sx,float sy,float sz)//显示天空
{
	float width = WIDTH>>1;			// 天空盒的边长
///////////////////////////////////////////////////////////////////////////////
	glScalef(sx,sy,sz);
	glColor3f(1.0,1.0,1.0);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	texture(g_cactus[0]);		// 设置BACK贴图左
	glBegin(GL_QUADS);			// 多组独立填充四边形	
		glTexCoord2f(1.0f,0.0f); glVertex3f( width,	-width,	-width);
		glTexCoord2f(1.0f,1.0f); glVertex3f( width,	 width, -width); 
		glTexCoord2f(0.0f,1.0f); glVertex3f(-width,	 width, -width);
		glTexCoord2f(0.0f,0.0f); glVertex3f(-width,	-width,	-width);
	glEnd();
	texture(g_cactus[1]);		// 设置FRONT贴图右
	glBegin(GL_QUADS);			// 多组独立填充四边形
		glTexCoord2f(1.0f,0.0f); glVertex3f(-width,	-width,	width);
		glTexCoord2f(1.0f,1.0f); glVertex3f(-width,	 width, width);
		glTexCoord2f(0.0f,1.0f); glVertex3f( width,	 width, width); 
		glTexCoord2f(0.0f,0.0f); glVertex3f( width,	-width,	width);
	glEnd();

	texture(g_cactus[2]);		// 设置TOP贴图顶
	glBegin(GL_QUADS);			// 多组独立填充四边形		
		glTexCoord2f(0.0f,1.0f); glVertex3f( width, width, -width);
		glTexCoord2f(0.0f,0.0f); glVertex3f( width, width,  width); 
		glTexCoord2f(1.0f,0.0f); glVertex3f(-width,	width,  width);
		glTexCoord2f(1.0f,1.0f); glVertex3f(-width,	width, -width);
	glEnd();
	texture(g_cactus[3]);		// 设置LEFT贴图前
	glBegin(GL_QUADS);			// 多组独立填充四边形
		glTexCoord2f(1.0f,1.0f); glVertex3f(-width,	 width, -width);	
		glTexCoord2f(0.0f,1.0f); glVertex3f(-width,	 width,  width); 
		glTexCoord2f(0.0f,0.0f); glVertex3f(-width,	-width,	 width);
		glTexCoord2f(1.0f,0.0f); glVertex3f(-width,	-width,	-width);		
	glEnd();
	texture(g_cactus[4]);		// 设置RIGHT贴图后
	glBegin(GL_QUADS);			// 多组独立填充四边形		
		glTexCoord2f(0.0f,0.0f); glVertex3f(width, -width, -width);
		glTexCoord2f(1.0f,0.0f); glVertex3f(width, -width,	width);
		glTexCoord2f(1.0f,1.0f); glVertex3f(width,	width,	width); 
		glTexCoord2f(0.0f,1.0f); glVertex3f(width,	width, -width);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}

void SkyBox::texture(UINT textur)//设置贴图滤波
{
	glBindTexture  (GL_TEXTURE_2D, textur);// 设置贴图
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR); //缩小采用线性滤波
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//放大采用线性滤波
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
}
#endif