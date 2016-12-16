#version 410

out vec4 FragColor;

in vec3 vertexNormalOut;
in vec3 cameraDirectionOut;
in vec2 vertexTextureCoordsOut;
in vec3 lightDirectionOut;

uniform vec4 ambientMaterialColour;
uniform float specularPower;

uniform vec4 ambientLightColour;
uniform vec4 diffuseLightColour;
uniform vec4 specularLightColour;

uniform sampler2D diffuseSampler;
uniform sampler2D specularSampler;
uniform sampler2D normalSampler;

void main()
{
	//get normals from normal map, rescale from 0 to 1 to -1 to 1
	vec3 bumpNormals = 2.0 * texture(normalSampler, vertexTextureCoordsOut).rgb - 1.0;

	//normalize!!
	bumpNormals = normalize(bumpNormals);

	vec3 lightDir=normalize(-lightDirectionOut);

	float diffuseTerm = dot(bumpNormals, lightDir);
	vec3 halfWayVec = normalize(cameraDirectionOut + lightDir);
	float specularTerm = pow(dot(bumpNormals, halfWayVec), specularPower);

	vec4 diffuseTextureColour = texture(diffuseSampler, vertexTextureCoordsOut);
	vec4 specularTextureColour = texture(specularSampler, vertexTextureCoordsOut);

	vec4 ambientColour = ambientMaterialColour*ambientLightColour;
	vec4 diffuseColour = diffuseTextureColour*diffuseLightColour*diffuseTerm;
	vec4 specularColour = specularTextureColour*specularLightColour*specularTerm;
	ambientColour.a=ambientMaterialColour.a;
	diffuseColour.a=diffuseTextureColour.a;
	specularColour.a=specularTextureColour.a;

	FragColor = (ambientColour + diffuseColour+ specularColour);
}
