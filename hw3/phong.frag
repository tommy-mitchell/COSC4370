
#version 330 core
out vec4 color;

in vec3 FragPos;  
in vec3 Normal;  
  
uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

vec3 getAmbientLight();
vec3 getDiffuseLight();
vec3 getSpecularLight();

void normalizeLight(inout vec3 norm, inout vec3 lightDir);

void main()
{
    vec3 ambient  = getAmbientLight();
	vec3 diffuse  = getDiffuseLight();
	vec3 specular = getSpecularLight();

	vec3 result = (ambient + diffuse + specular) * objectColor;
	color = vec4(result, 1.0);
} 

vec3 getAmbientLight()
{
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

	return ambient * objectColor;;
}

vec3 getDiffuseLight()
{
	vec3 norm, lightDir;
	normalizeLight(norm, lightDir);

	float diff = max(dot(norm, lightDir), 0.0);

	return diff * lightColor;
}

vec3 getSpecularLight()
{
	float specularStrength = 0.5;

	vec3 norm, lightDir;
	normalizeLight(norm, lightDir);
	
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

	return specularStrength * spec * lightColor;
}

void normalizeLight(inout vec3 norm, inout vec3 lightDir)
{
	norm = normalize(Normal);
	lightDir = normalize(lightPos - FragPos);
}