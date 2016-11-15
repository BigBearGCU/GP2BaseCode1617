#version 410

out vec4 FragColor;

in vec3 vertexNormalOut;
in vec3 cameraDirectionOut;
in vec2 vertexTextureCoordsOut;

uniform vec3 lightDirection=vec3(0.0f,0.0f,1.0f);
uniform vec4 ambientMaterialColour=vec4(0.5f,0.0f,0.0f,1.0f);
uniform float specularPower=25.0f;

uniform vec4 ambientLightColour=vec4(1.0f,1.0f,1.0f,1.0f);
uniform vec4 diffuseLightColour=vec4(1.0f,1.0f,1.0f,1.0f);
uniform vec4 specularLightColour=vec4(1.0f,1.0f,1.0f,1.0f);

uniform sampler2D diffuseSampler;
uniform sampler2D specularSampler;

void main()
{
	vec3 lightDir=normalize(-lightDirection);
	float diffuseTerm = dot(vertexNormalOut, lightDir);
	vec3 halfWayVec = normalize(cameraDirectionOut + lightDir);
	float specularTerm = pow(dot(vertexNormalOut, halfWayVec), specularPower);

	vec4 diffuseTextureColour = texture(diffuseSampler, vertexTextureCoordsOut);
	vec4 specularTextureColour = texture(specularSampler, vertexTextureCoordsOut);

	vec4 ambientColour = ambientMaterialColour*ambientLightColour;
	vec4 diffuseColour = diffuseTextureColour*diffuseLightColour*diffuseTerm;
	vec4 specularColour = specularTextureColour*specularLightColour*specularTerm;

	FragColor = (ambientColour + diffuseColour+ specularColour);
}
