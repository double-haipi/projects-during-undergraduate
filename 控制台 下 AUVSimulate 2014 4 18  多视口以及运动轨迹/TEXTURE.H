// Texture.h: interface for the Texture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTURE_H__E6521308_11A2_4EC7_A551_A46DC70C1958__INCLUDED_)
#define AFX_TEXTURE_H__E6521308_11A2_4EC7_A551_A46DC70C1958__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Texture  
{
public:
	Texture();
	virtual ~Texture();

	AUX_RGBImageRec *LoadBMP(const char *Filename);
	GLuint LoadGLTexture( const char *filename );
	int LoadTextures();
};

#endif // !defined(AFX_TEXTURE_H__E6521308_11A2_4EC7_A551_A46DC70C1958__INCLUDED_)
