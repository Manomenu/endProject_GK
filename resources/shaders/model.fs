#version 450 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    vec3 color_diffuse;

    sampler2D specular;
    vec3 color_specular;
    //float shininess;
}; 

struct Light {
    vec3 position;  
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
};

#define NR_SPOT_LIGHTS 4

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Light dirLight;
uniform Light spotLights[NR_SPOT_LIGHTS];
uniform Material material;

// function prototypes
vec3 CalcDirLight(Light light, vec3 normal, vec3 viewDir);
vec3 CalcSpotLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{    
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = vec3(0, 0, 0);

    if (material.color_diffuse.r >= 100.0 && material.color_diffuse.g >= 100.0 && material.color_diffuse.b >= 100.0)
    {
        result = material.color_diffuse - vec3(100.0, 100.0, 100.0);
    }
    else
    {
        result = CalcDirLight(dirLight, norm, viewDir);

        for(int i = 0; i < NR_SPOT_LIGHTS; i++)
            result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir);
    }
    
    FragColor = vec4(result, 1.0);
}

vec3 CalcSpotLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * (material.color_diffuse.x != -1 ? material.color_diffuse : vec3(texture(material.diffuse, TexCoords)));
    vec3 diffuse = light.diffuse * diff * (material.color_diffuse.x != -1 ? material.color_diffuse : vec3(texture(material.diffuse, TexCoords)));
    vec3 specular = light.specular * spec * (material.color_specular.x != -1 ? material.color_specular : vec3(texture(material.specular, TexCoords)));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}

// calculates the color when using a directional light.
vec3 CalcDirLight(Light light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32); // material.shininess
    // combine results
    vec3 ambient = light.ambient * (material.color_diffuse.x != -1 ? material.color_diffuse : vec3(texture(material.diffuse, TexCoords)));
    vec3 diffuse = light.diffuse * diff * (material.color_diffuse.x != -1 ? material.color_diffuse : vec3(texture(material.diffuse, TexCoords)));
    vec3 specular = light.specular * spec * (material.color_specular.x != -1 ? material.color_specular : vec3(texture(material.specular, TexCoords)));
    return (ambient + diffuse + specular);
}