#version 150

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
uniform sampler2D normalSampler;
uniform sampler2D heightSampler;

uniform float bias = 0.03;
uniform float scale = 0.02;

void main()
{
	//retrieve height from texture
	float height = texture(heightSampler, texCoordsOut).r;

	//use offset limits(scale and bias) to move texture coords
	vec2 correctedTexCoords = scale*texCoordsOut.xy*height-bias;

	//Calculate new texture coords, we use these instead of normal texture coords
	correctedTexCoords=texCoordsOut-correctedTexCoords;

	//get normals from normal map, rescale from 0 to 1 to -1 to 1
	vec3 bumpNormals = 2.0 * texture(normalSampler, correctedTexCoords).rgb - 1.0;

	//normalize!!
	bumpNormals = normalize(bumpNormals);

	vec3 lightDir = normalize(-lightDirectionOut);
	//now use bumpnormals in reflectance calculate
	float diffuseTerm = dot(bumpNormals, lightDir);
	vec3 halfWayVec = normalize(cameraDirectionOut + lightDir);
	float specularTerm = pow(dot(bumpNormals, halfWayVec), specularPower);

	vec4 diffuseTextureColour = texture(diffuseSampler, correctedTexCoords);
	vec4 specularTextureColour = texture(specularSampler, correctedTexCoords);

	vec4 ambientColour = ambientMaterialColour*ambientLightColour;
	vec4 diffuseColour = diffuseTextureColour*diffuseLightColour*diffuseTerm;
	vec4 specularColour = specularTextureColour*specularLightColour*specularTerm;

	FragColor = (ambientColour + diffuseColour + specularColour);
}
