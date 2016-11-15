#version 410

out vec4 FragColor;

in vec3 vertexNormalOut;
in vec3 cameraDirectionOut;
in vec3 lightDirectionOut;
in vec2 texCoordsOut;

uniform vec4 ambientMaterialColour;
uniform vec4 diffuseMaterialColour;
uniform vec4 specularMaterialColour;
uniform float specularPower;

uniform vec4 ambientLightColour;
uniform vec4 diffuseLightColour;
uniform vec4 specularLightColour;

uniform sampler2D diffuseSampler;
uniform sampler2D specularSampler;
uniform sampler2D heightSampler;
uniform sampler2D normalSampler;

uniform float bias = 0.03;
uniform float scale = 0.015;

void main()
{
	//retrieve height from texture
	float height = texture(heightSampler, texCoordsOut).x;

	//use offset limits(scale and bias) to move texture coords
	vec2 correctedTexCoords = (scale*texCoordsOut*height)-bias;

	//Calculate new texture coords, we use these instead of normal texture coords
	correctedTexCoords=texCoordsOut-correctedTexCoords;

	//get normals from normal map, rescale from 0 to 1 to -1 to 1
	vec3 bumpNormals = 2.0 * texture(normalSampler, correctedTexCoords).rgb - 1.0;

	//normalize!!
	bumpNormals = normalize(bumpNormals);

	//now use bumpnormals in reflectance calculate
	float diffuseTerm = dot(bumpNormals, lightDirectionOut);
	vec3 halfWayVec = normalize(cameraDirectionOut + lightDirectionOut);
	float specularTerm = pow(dot(bumpNormals, halfWayVec), specularPower);

	vec4 diffuseTextureColour = texture(diffuseSampler, correctedTexCoords);
	vec4 specTextureColour = texture(specularSampler, correctedTexCoords);

	FragColor = (ambientMaterialColour*ambientLightColour) + ((diffuseMaterialColour + diffuseTextureColour)*diffuseLightColour*diffuseTerm) + ((specularMaterialColour + specTextureColour)*specularLightColour*specularTerm);
}
