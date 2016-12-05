#ifndef MATERIAL_H
#define MATERIAL_H

#include "Common.h"

class Material
{
public:
	Material();
	virtual ~Material();

private:
	GLuint m_ShaderProgram;
};
#endif
