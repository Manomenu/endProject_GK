#version 450 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    vec3 color_diffuse;

    sampler2D specular;
    vec3 color_specular;
    //float shininess;
}; 

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform Material material;

// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

void main()
{    
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    vec3 result = CalcDirLight(dirLight, norm, viewDir);

    FragColor = vec4(result, 1.0);
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
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
    vec3 specular = light.specular * spec * (material.color_specular.x != -1 ? material.color_specular : vec3(texture(material.diffuse, TexCoords)));
    return (ambient + diffuse + specular);
}

