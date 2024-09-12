#include <config.h>

struct SpotLightData
{
    glm::vec3 position;
    glm::vec3 direction;
    float cutOff;
    float outerCutOff;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float constant;
    float linear;
    float quadratic;

    bool hasBulb = false;

    struct 
    {
        bool isFollowing = false;
        uint target;

        struct
        {
            glm::vec3 space = glm::vec3(0);
            float r = 0;
            float time = 0;
        } offset;

    } follow; // move to follow_data.h and use it as component inside
};
