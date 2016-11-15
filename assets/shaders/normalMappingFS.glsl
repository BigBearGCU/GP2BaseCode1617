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
	vec3 bumpNormals = texture(normalSampler, vertexTextureCoordsOut).xyz;
	bumpNormals=normalize(2.0*bumpNormals-1.0f);


	float diffuseTerm = dot(bumpNormals, lightDirectionOut);
	vec3 halfWayVec = normalize(cameraDirectionOut + lightDirectionOut);
	float specularTerm = pow(dot(bumpNormals, halfWayVec), specularPower);

	vec4 diffuseTextureColour = texture(diffuseSampler, vertexTextureCoordsOut);
	vec4 specularTextureColour = texture(specularSampler, vertexTextureCoordsOut);

	vec4 ambientColour = ambientMaterialColour*ambientLightColour;
	vec4 diffuseColour = diffuseTextureColour*diffuseLightColour*diffuseTerm;
	vec4 specularColour = specularTextureColour*specularLightColour*specularTerm;

	FragColor = (ambientColour + diffuseColour+ specularColour);
}
