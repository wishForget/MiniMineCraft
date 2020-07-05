#version 330 core
out vec4 FragColor;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
// 雾效果
struct FogInfo {
  float maxDist;
  float minDist;
  vec4 color;
};

struct WaterInfo{
  float maxDist;
  float waterLevel;
  vec4 color;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in mat4 Model;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform FogInfo Fog;
uniform WaterInfo Water;
uniform bool ifTransparency;
uniform bool useLight;  //启用光照
uniform bool useFog;  //启用雾气效果

vec4 getColor(){
	if(!useLight){
		return texture(material.diffuse, TexCoords);
	}
	else {
		vec4 nolightColor = texture(material.diffuse, TexCoords);
		// ambient
    	vec3 ambient = light.ambient * nolightColor.xyz;

    	// diffuse 
    	vec3 norm = normalize(Normal);
    	vec3 lightDir = normalize(light.position - FragPos);
    	float diff = max(dot(norm, lightDir), 0.0);
    	vec3 diffuse = light.diffuse * diff * nolightColor.rgb;

    	// specular
    	vec3 viewDir = normalize(viewPos - FragPos);
    	vec3 reflectDir = reflect(-lightDir, norm);
    	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    	vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

    	return vec4(ambient + diffuse + specular, nolightColor.a);
    }
}

void main()
{
	float dist = length(viewPos - FragPos);
	vec4 shaderColor = getColor();

	
	if(useFog){
		float fogFactor = (Fog.maxDist - dist) /
                      (Fog.maxDist - Fog.minDist);
    	fogFactor = clamp( fogFactor, 0.0, 1.0 );
    	vec4 color = mix(Fog.color, shaderColor, fogFactor);
    	FragColor = vec4(color.rgb, shaderColor.a);
	}else{
		FragColor = vec4(shaderColor.rgba);
	}

	if(viewPos.y < Water.waterLevel){
		float waterFactor = (Water.maxDist - dist)/
						(Water.maxDist - 0);
		waterFactor = clamp( waterFactor, 0.0, 1.0 );
		vec4 color = mix(Water.color, shaderColor, waterFactor);
    	FragColor = vec4(color.rgb, shaderColor.a);
	}
}