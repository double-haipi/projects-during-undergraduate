#ifndef _SKYBOX_H
#define _SKYBOX_H
#define WIDTH 100

class SkyBox
{
private:
	UINT		g_cactus[5];	                    //��ͼ
	void        texture(UINT textur);
	bool        LoadT8(char *filename, GLuint &texture);
public:
	SkyBox();
	~SkyBox();
	void Render(float sx,float sy,float sz);
};

SkyBox::SkyBox()
{
	LoadT8("res/2Back.bmp",g_cactus[0]);	//�����ͼ��
	LoadT8("res/2Front.bmp",g_cactus[1]);	//�����ͼǰ
	LoadT8("res/2Top.bmp",	 g_cactus[2]);	//�����ͼ��
	LoadT8("res/2Left.bmp", g_cactus[3]);	//�����ͼ��
	LoadT8("res/2Right.bmp",g_cactus[4]);	//�����ͼ��
}

SkyBox::~SkyBox()
{
	for(int i=0;i<5;i++) 
		glDeleteTextures(1, &g_cactus[i]);
	glDisableClientState(GL_VERTEX_ARRAY);
}

bool SkyBox::LoadT8(char *filename, GLuint &texture)//��8λ��ͼ
{	
	AUX_RGBImageRec *pImage = NULL;
	pImage = auxDIBImageLoad(filename);	 // װ��λͼ			
	if(pImage == NULL)	return false;	 // λͼûװ�뷵�ش���
	glGenTextures(1, &texture);			 // ������ͼ(����)
	glBindTexture    (GL_TEXTURE_2D,texture);// ������ͼ(����)
	gluBuild2DMipmaps(GL_TEXTURE_2D,4,   //
					  pImage->sizeX,     // ͼ�ο�
					  pImage->sizeY,     // ͼ�θ�
					  GL_RGB, GL_UNSIGNED_BYTE,
					  pImage->data       // ͼ������
					 );
	free(pImage->data);                  // �ͷ�λͼ����ռ�ݵ��ڴ���Դ
	free(pImage);	
	return true;                         // ���سɹ�
}

void SkyBox::Render(float sx,float sy,float sz)//��ʾ���
{
	float width = WIDTH>>1;			// ��պеı߳�
///////////////////////////////////////////////////////////////////////////////
	glScalef(sx,sy,sz);
	glColor3f(1.0,1.0,1.0);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	texture(g_cactus[0]);		// ����BACK��ͼ��
	glBegin(GL_QUADS);			// �����������ı���	
		glTexCoord2f(1.0f,0.0f); glVertex3f( width,	-width,	-width);
		glTexCoord2f(1.0f,1.0f); glVertex3f( width,	 width, -width); 
		glTexCoord2f(0.0f,1.0f); glVertex3f(-width,	 width, -width);
		glTexCoord2f(0.0f,0.0f); glVertex3f(-width,	-width,	-width);
	glEnd();
	texture(g_cactus[1]);		// ����FRONT��ͼ��
	glBegin(GL_QUADS);			// �����������ı���
		glTexCoord2f(1.0f,0.0f); glVertex3f(-width,	-width,	width);
		glTexCoord2f(1.0f,1.0f); glVertex3f(-width,	 width, width);
		glTexCoord2f(0.0f,1.0f); glVertex3f( width,	 width, width); 
		glTexCoord2f(0.0f,0.0f); glVertex3f( width,	-width,	width);
	glEnd();

	texture(g_cactus[2]);		// ����TOP��ͼ��
	glBegin(GL_QUADS);			// �����������ı���		
		glTexCoord2f(0.0f,1.0f); glVertex3f( width, width, -width);
		glTexCoord2f(0.0f,0.0f); glVertex3f( width, width,  width); 
		glTexCoord2f(1.0f,0.0f); glVertex3f(-width,	width,  width);
		glTexCoord2f(1.0f,1.0f); glVertex3f(-width,	width, -width);
	glEnd();
	texture(g_cactus[3]);		// ����LEFT��ͼǰ
	glBegin(GL_QUADS);			// �����������ı���
		glTexCoord2f(1.0f,1.0f); glVertex3f(-width,	 width, -width);	
		glTexCoord2f(0.0f,1.0f); glVertex3f(-width,	 width,  width); 
		glTexCoord2f(0.0f,0.0f); glVertex3f(-width,	-width,	 width);
		glTexCoord2f(1.0f,0.0f); glVertex3f(-width,	-width,	-width);		
	glEnd();
	texture(g_cactus[4]);		// ����RIGHT��ͼ��
	glBegin(GL_QUADS);			// �����������ı���		
		glTexCoord2f(0.0f,0.0f); glVertex3f(width, -width, -width);
		glTexCoord2f(1.0f,0.0f); glVertex3f(width, -width,	width);
		glTexCoord2f(1.0f,1.0f); glVertex3f(width,	width,	width); 
		glTexCoord2f(0.0f,1.0f); glVertex3f(width,	width, -width);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}

void SkyBox::texture(UINT textur)//������ͼ�˲�
{
	glBindTexture  (GL_TEXTURE_2D, textur);// ������ͼ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR); //��С���������˲�
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//�Ŵ���������˲�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
}
#endif