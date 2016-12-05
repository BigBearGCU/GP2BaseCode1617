#include "GameObject.h"

GameObject::GameObject()
{
	m_Position = vec3(0.0f, 0.0f, 0.0f);
	m_Rotation = vec3(0.0f, 0.0f, 0.0f);
	m_Scale = vec3(1.0f, 1.0f, 1.0f);

	m_ModelMatrix = mat4(1.0f);
	m_TranslationMatrix = mat4(1.0f);
	m_ScaleMatrix = mat4(1.0f);

	m_RotationMatrix = mat4(1.0f);

	m_VBO=0;
	m_EBO=0;
	m_VAO=0;
	m_NumberOfVerts=0;
	m_NumberOfIndices=0;

	//Shader Program
	m_ShaderProgram=0;
	m_DiffuseTexture =0;
	m_SpecularTexture = 0;
	m_NormalTexture = 0;
	m_HeightTexture = 0;

	m_Sampler=0;
	m_pParent = nullptr;

	m_AmbientMaterialColour=vec4(0.0f,0.0f,0.0f,1.0f);
	m_DiffuseMaterialColour=vec4(0.5f,0.5f,0.5f,1.0f);
	m_SpecularMaterialColour=vec4(1.0f,1.0f,1.0f,1.0f);
	m_SpecularMaterialPower=25.0f;
}

GameObject::~GameObject()
{

}

void GameObject::onUpdate()
{
	m_RotationMatrix=eulerAngleYXZ(m_Rotation.y,m_Rotation.x,m_Rotation.z);


	m_ScaleMatrix = scale(m_Scale);

	m_TranslationMatrix = translate(m_Position);

	m_ModelMatrix = m_TranslationMatrix*m_RotationMatrix*m_ScaleMatrix;
	if (m_pParent)
	{
		m_ModelMatrix *= m_pParent->getModelMatrix();
	}
}

void GameObject::onRender(mat4& view, mat4& projection)
{
	GLint MVPLocation = glGetUniformLocation(m_ShaderProgram, "MVP");
	mat4 MVP = projection*view*m_ModelMatrix;
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));

	GLint ModelLocation = glGetUniformLocation(m_ShaderProgram, "Model");
	glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, glm::value_ptr(m_ModelMatrix));

	glBindSampler(0, m_Sampler);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_DiffuseTexture);
	GLint diffuseTextureLocation = glGetUniformLocation(m_ShaderProgram, "diffuseSampler");
	glUniform1i(diffuseTextureLocation, 0);

	glBindSampler(1, m_Sampler);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_SpecularTexture);
	GLint specularTextureLocation = glGetUniformLocation(m_ShaderProgram, "specularSampler");
	glUniform1i(specularTextureLocation, 1);

	glBindSampler(2, m_Sampler);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_NormalTexture);
	GLint normalTextureLocation = glGetUniformLocation(m_ShaderProgram, "normalSampler");
	glUniform1i(normalTextureLocation, 2);

	glBindSampler(3, m_Sampler);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, m_HeightTexture);
	GLint heightTextureLocation = glGetUniformLocation(m_ShaderProgram, "heightSampler");
	glUniform1i(heightTextureLocation, 3);

	GLint ambientLocation = glGetUniformLocation(m_ShaderProgram, "ambientMaterialColour");
	glUniform4fv(ambientLocation, 1, value_ptr(m_AmbientMaterialColour));

	GLint diffuseLocation = glGetUniformLocation(m_ShaderProgram, "diffuseMaterialColour");
	glUniform4fv(diffuseLocation, 1, value_ptr(m_DiffuseMaterialColour));

	GLint specularLocation = glGetUniformLocation(m_ShaderProgram, "specularMaterialColour");
	glUniform4fv(specularLocation, 1, value_ptr(m_SpecularMaterialColour));

	GLint specularPowerLocation = glGetUniformLocation(m_ShaderProgram, "specularPower");
	glUniform1f(specularPowerLocation, m_SpecularMaterialPower);

	glDrawElements(GL_TRIANGLES, m_NumberOfIndices, GL_UNSIGNED_INT, NULL);

	//glUseProgram(0);
	glBindVertexArray(0);
}

void GameObject::onBeginRender()
{
	glUseProgram(m_ShaderProgram);
	glBindVertexArray(m_VAO);
}

void GameObject::onInit()
{

}

void GameObject::onDestroy()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteSamplers(1, &m_Sampler);
	glDeleteTextures(1, &m_DiffuseTexture);
	glDeleteTextures(1, &m_SpecularTexture);
	glDeleteTextures(1, &m_NormalTexture);
	glDeleteTextures(1, &m_HeightTexture);
	glDeleteProgram(m_ShaderProgram);
}

void GameObject::addChild(shared_ptr<GameObject> gameobject)
{
	gameobject->m_pParent = this;
	m_ChildrenGameObjects.push_back(gameobject);
}

void GameObject::rotate(const vec3 & delta)
{
	m_Rotation += delta;
}

void GameObject::loadDiffuseTexture(const string & filename)
{
	m_DiffuseTexture = loadTextureFromFile(filename);
	glBindTexture(GL_TEXTURE_2D, m_DiffuseTexture);
	glGenerateMipmap(GL_TEXTURE_2D);

	glGenSamplers(1, &m_Sampler);
	glSamplerParameteri(m_Sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glSamplerParameteri(m_Sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glSamplerParameteri(m_Sampler, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glSamplerParameteri(m_Sampler, GL_TEXTURE_WRAP_T, GL_CLAMP);

}

void GameObject::loadSpecularTexture(const string & filename)
{
	m_SpecularTexture = loadTextureFromFile(filename);
	glBindTexture(GL_TEXTURE_2D, m_SpecularTexture);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void GameObject::loadNormalTexture(const string & filename)
{
	m_NormalTexture = loadTextureFromFile(filename);
	glBindTexture(GL_TEXTURE_2D, m_NormalTexture);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void GameObject::loadHeightTexture(const string & filename)
{
	m_HeightTexture = loadTextureFromFile(filename);
	glBindTexture(GL_TEXTURE_2D, m_HeightTexture);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void GameObject::loadShaders(const string & vsFilename, const string & fsFilename)
{
	GLuint vertexShaderProgram = loadShaderFromFile(vsFilename, VERTEX_SHADER);

	GLuint fragmentShaderProgram = loadShaderFromFile(fsFilename, FRAGMENT_SHADER);

	m_ShaderProgram = glCreateProgram();
	glAttachShader(m_ShaderProgram, vertexShaderProgram);
	glAttachShader(m_ShaderProgram, fragmentShaderProgram);
	glLinkProgram(m_ShaderProgram);
	checkForLinkErrors(m_ShaderProgram);

	//now we can delete the VS & FS Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);

	logShaderInfo(m_ShaderProgram);
}

void GameObject::copyVertexData(Vertex * pVertex, int numberOfVertices, int * pIndices, int numberOfIndices)
{
	m_NumberOfVerts = numberOfVertices;
	m_NumberOfIndices = numberOfIndices;
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(Vertex), pVertex, GL_STATIC_DRAW);

	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfIndices * sizeof(int), pIndices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		NULL);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void**)(offsetof(Vertex, colours)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void**)(offsetof(Vertex, texCoords0)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void**)(offsetof(Vertex, normal)));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void**)(offsetof(Vertex, tangent)));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void**)(offsetof(Vertex, binormal)));
}
