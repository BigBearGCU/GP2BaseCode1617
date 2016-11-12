#include "MyGame.h"

const std::string ASSET_PATH = "assets";
const std::string SHADER_PATH = "/shaders";
const std::string TEXTURE_PATH = "/textures";
const std::string MODEL_PATH = "/models";

MyGame::MyGame()
{

}

MyGame::~MyGame()
{

}

void MyGame::initScene()
{
	string modelPath = ASSET_PATH + MODEL_PATH + "/MultiplayerArena.fbx";

	string vsParallaxFilename = ASSET_PATH + SHADER_PATH + "/parallaxMappingVS.glsl";
	string fsParallaxFilename = ASSET_PATH + SHADER_PATH + "/parallaxMappingFS.glsl";
	string vsBumpFilename=ASSET_PATH+SHADER_PATH+"/normalMappingVS.glsl";
	string fsBumpFilename=ASSET_PATH+SHADER_PATH+"/normalMappingFS.glsl";
	string vsTextureFilename=ASSET_PATH+SHADER_PATH+"/lightTextureVS.glsl";
	string fsTextureFilename=ASSET_PATH+SHADER_PATH+"/lightTextureFS.glsl";

	string diffuseTexturePath = ASSET_PATH + TEXTURE_PATH + "/bricks_diff.jpg";
	string specularTexturePath = ASSET_PATH + TEXTURE_PATH + "/bricks_spec.png";
	string normalTexturePath = ASSET_PATH + TEXTURE_PATH + "/bricks_norm.png";
	string heightTexturePath=ASSET_PATH+TEXTURE_PATH+"/bricks_height.png";

	shared_ptr<GameObject> testGO=shared_ptr<GameObject>(loadModelFromFile(modelPath));
	testGO->loadShaders(vsParallaxFilename, fsParallaxFilename);
	testGO->loadDiffuseTexture(diffuseTexturePath);
	testGO->loadSpecularTexture(specularTexturePath);
	testGO->loadNormalTexture(normalTexturePath);
	testGO->loadHeightTexture(heightTexturePath);
	m_GameObjectList.push_back(testGO);

	m_CameraPosition = vec3(0.0f, 0.0f, 20.0f);

	m_Light = shared_ptr<Light>(new Light());
	m_Light->DiffuseColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SpecularColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->Direction = vec3(0.0f, 0.0f, -1.0f);
	m_AmbientLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);


}

void MyGame::destroyScene()
{
	for (auto& go:m_GameObjectList)
	{
		go->onDestroy();
	}

	m_GameObjectList.clear();
}

void MyGame::update()
{
	GameApplication::update();

	m_ProjMatrix = perspective(radians(45.0f), (float)m_WindowWidth / (float)m_WindowHeight, 0.1f, 1000.0f);
	m_ViewMatrix = lookAt(m_CameraPosition, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	for (auto& go:m_GameObjectList)
	{
		go->onUpdate();
	}
}

void MyGame::render()
{
	GameApplication::render();
	for(auto& go:m_GameObjectList)
	{
		GLuint currentShader = go->getShaderProgram();
		go->onBeginRender();

		GLint ambientLightColourLocation = glGetUniformLocation(currentShader, "ambientLightColour");
		glUniform4fv(ambientLightColourLocation, 1, value_ptr(m_AmbientLightColour));

		GLint diffuseLightColourLocation = glGetUniformLocation(currentShader, "diffuseLightColour");
		glUniform4fv(diffuseLightColourLocation, 1, value_ptr(m_Light->DiffuseColour));

		GLint specularLightColourLocation = glGetUniformLocation(currentShader, "specularLightColour");
		glUniform4fv(specularLightColourLocation, 1, value_ptr(m_Light->SpecularColour));

		GLint lightDirectionLocation = glGetUniformLocation(currentShader, "lightDirection");
		glUniform3fv(lightDirectionLocation, 1, value_ptr(m_Light->Direction));

		GLint cameraPositionLocation = glGetUniformLocation(currentShader, "cameraPos");
		glUniform3fv(cameraPositionLocation, 1, value_ptr(m_CameraPosition));

		go->onRender(m_ViewMatrix, m_ProjMatrix);
	}
}
