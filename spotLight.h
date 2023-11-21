
#ifndef spotLight_h
#define spotLight_h

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "shader.h"
class SpotLight {
public:
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 emission;

    float k_c;
    float k_l;
    float k_q;
    
    int lightNumber;

    SpotLight(float posX, float posY, float posZ, float ambR, float ambG, float ambB, float diffR, float diffG, float diffB, float specR, float specG, float specB, float constant, float linear, float quadratic, int num) {

     
        position = glm::vec3(posX, posY, posZ);
        ambient = glm::vec3(ambR, ambG, ambB);
        diffuse = glm::vec3(diffR, diffG, diffB);
        specular = glm::vec3(specR, specG, specB);
        k_c = constant;
        k_l = linear;
        k_q = quadratic;
        lightNumber = num;
        
    }
    void setUpSpotLight(Shader& lightingShader)
    {
        lightingShader.use();

        if (lightNumber == 1) {
            lightingShader.setVec3("spotLights[0].position", position);
            lightingShader.setVec3("spotLights[0].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[0].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[0].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[0].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[0].k_c", k_c);
            lightingShader.setFloat("spotLights[0].k_l", k_l);
            lightingShader.setFloat("spotLights[0].k_q", k_q);
        }

        else if (lightNumber == 2)
        {
            lightingShader.setVec3("spotLights[1].position", position);
        
            lightingShader.setVec3("spotLights[1].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[1].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[1].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[1].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[1].k_c", k_c);
            lightingShader.setFloat("spotLights[1].k_l", k_l);
            lightingShader.setFloat("spotLights[1].k_q", k_q);
        }
        else if (lightNumber == 3)
        {
            lightingShader.setVec3("spotLights[2].position", position);
            lightingShader.setVec3("spotLights[2].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[2].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[2].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[2].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[2].k_c", k_c);
            lightingShader.setFloat("spotLights[2].k_l", k_l);
            lightingShader.setFloat("spotLights[2].k_q", k_q);
        }
        else if (lightNumber == 4)
        {
            lightingShader.setVec3("spotLights[3].position", position);
            lightingShader.setVec3("spotLights[3].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[3].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[3].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[3].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[3].k_c", k_c);
            lightingShader.setFloat("spotLights[3].k_l", k_l);
            lightingShader.setFloat("spotLights[3].k_q", k_q);
        }
        else if (lightNumber == 5)
        {
            lightingShader.setVec3("spotLights[4].position", position);
            lightingShader.setVec3("spotLights[4].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[4].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[4].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[4].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[4].k_c", k_c);
            lightingShader.setFloat("spotLights[4].k_l", k_l);
            lightingShader.setFloat("spotLights[4].k_q", k_q);
        }
        else if (lightNumber == 6)
        {
            lightingShader.setVec3("spotLights[5].position", position);
            lightingShader.setVec3("spotLights[5].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[5].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[5].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[5].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[5].k_c", k_c);
            lightingShader.setFloat("spotLights[5].k_l", k_l);
            lightingShader.setFloat("spotLights[5].k_q", k_q);
        }
        else if (lightNumber == 7)
        {
            lightingShader.setVec3("spotLights[6].position", position);
            lightingShader.setVec3("spotLights[6].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[6].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[6].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[6].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[6].k_c", k_c);
            lightingShader.setFloat("spotLights[6].k_l", k_l);
            lightingShader.setFloat("spotLights[6].k_q", k_q);
        }
        else if (lightNumber == 8)
        {
            lightingShader.setVec3("spotLights[7].position", position);
            lightingShader.setVec3("spotLights[7].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[7].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[7].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[7].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[7].k_c", k_c);
            lightingShader.setFloat("spotLights[7].k_l", k_l);
            lightingShader.setFloat("spotLights[7].k_q", k_q);
        }
        else if (lightNumber == 9)
        {
            lightingShader.setVec3("spotLights[8].position", position);
            lightingShader.setVec3("spotLights[8].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[8].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[8].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[8].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[8].k_c", k_c);
            lightingShader.setFloat("spotLights[8].k_l", k_l);
            lightingShader.setFloat("spotLights[8].k_q", k_q);
        }
        else if (lightNumber == 10)
        {
            lightingShader.setVec3("spotLights[9].position", position);
            lightingShader.setVec3("spotLights[9].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[9].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[9].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[9].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[9].k_c", k_c);
            lightingShader.setFloat("spotLights[9].k_l", k_l);
            lightingShader.setFloat("spotLights[9].k_q", k_q);
        }
        else if (lightNumber == 11)
        {
            lightingShader.setVec3("spotLights[10].position", position);
            lightingShader.setVec3("spotLights[10].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[10].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[10].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[10].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[10].k_c", k_c);
            lightingShader.setFloat("spotLights[10].k_l", k_l);
            lightingShader.setFloat("spotLights[10].k_q", k_q);
            }

        else if (lightNumber == 12)
        {
            lightingShader.setVec3("spotLights[11].position", position);
            lightingShader.setVec3("spotLights[11].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[11].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[11].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[11].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[11].k_c", k_c);
            lightingShader.setFloat("spotLights[11].k_l", k_l);
            lightingShader.setFloat("spotLights[11].k_q", k_q);
            }
        else if (lightNumber == 13)
        {
            lightingShader.setVec3("spotLights[12].position", position);
            lightingShader.setVec3("spotLights[12].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[12].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[12].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[12].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[12].k_c", k_c);
            lightingShader.setFloat("spotLights[12].k_l", k_l);
            lightingShader.setFloat("spotLights[12].k_q", k_q);
            }
        else if (lightNumber == 14)
        {
            lightingShader.setVec3("spotLights[13].position", position);
            lightingShader.setVec3("spotLights[13].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[13].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[13].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[13].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[13].k_c", k_c);
            lightingShader.setFloat("spotLights[13].k_l", k_l);
            lightingShader.setFloat("spotLights[13].k_q", k_q);
            }
        else if (lightNumber == 15)
        {
            lightingShader.setVec3("spotLights[14].position", position);
            lightingShader.setVec3("spotLights[14].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[14].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[14].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[14].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[14].k_c", k_c);
            lightingShader.setFloat("spotLights[14].k_l", k_l);
            lightingShader.setFloat("spotLights[14].k_q", k_q);

            }

        else if (lightNumber == 16)
        {
            lightingShader.setVec3("spotLights[15].position", position);
            lightingShader.setVec3("spotLights[15].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[15].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[15].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[15].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[15].k_c", k_c);
            lightingShader.setFloat("spotLights[15].k_l", k_l);
            lightingShader.setFloat("spotLights[15].k_q", k_q);

            }
        else if (lightNumber == 17)
        {
            lightingShader.setVec3("spotLights[16].position", position);
            lightingShader.setVec3("spotLights[16].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[16].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[16].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[16].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[16].k_c", k_c);
            lightingShader.setFloat("spotLights[16].k_l", k_l);
            lightingShader.setFloat("spotLights[16].k_q", k_q);

            }
        else if (lightNumber == 18)
        {
            lightingShader.setVec3("spotLights[17].position", position);
            lightingShader.setVec3("spotLights[17].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[17].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[17].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[17].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[17].k_c", k_c);
            lightingShader.setFloat("spotLights[17].k_l", k_l);
            lightingShader.setFloat("spotLights[17].k_q", k_q);

            }
        else if (lightNumber == 19)
        {
            lightingShader.setVec3("spotLights[18].position", position);
            lightingShader.setVec3("spotLights[18].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[18].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[18].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[18].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[18].k_c", k_c);
            lightingShader.setFloat("spotLights[18].k_l", k_l);
            lightingShader.setFloat("spotLights[18].k_q", k_q);

            }
        else if (lightNumber == 20)
        {
            lightingShader.setVec3("spotLights[19].position", position);
            lightingShader.setVec3("spotLights[19].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[19].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[19].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[19].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[19].k_c", k_c);
            lightingShader.setFloat("spotLights[19].k_l", k_l);
            lightingShader.setFloat("spotLights[19].k_q", k_q);

            }
        else if (lightNumber == 21)
        {
            lightingShader.setVec3("spotLights[20].position", position);
            lightingShader.setVec3("spotLights[20].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[20].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[20].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[20].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[20].k_c", k_c);
            lightingShader.setFloat("spotLights[20].k_l", k_l);
            lightingShader.setFloat("spotLights[20].k_q", k_q);

            }
        else if (lightNumber == 22)
        {
            lightingShader.setVec3("spotLights[21].position", position);
            lightingShader.setVec3("spotLights[21].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[21].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[21].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[21].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[21].k_c", k_c);
            lightingShader.setFloat("spotLights[21].k_l", k_l);
            lightingShader.setFloat("spotLights[21].k_q", k_q);

            }
        else if (lightNumber == 23)
        {
            lightingShader.setVec3("spotLights[22].position", position);
            lightingShader.setVec3("spotLights[22].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[22].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[22].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[22].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[22].k_c", k_c);
            lightingShader.setFloat("spotLights[22].k_l", k_l);
            lightingShader.setFloat("spotLights[22].k_q", k_q);

            }
        else if (lightNumber == 24)
        {
            lightingShader.setVec3("spotLights[23].position", position);
            lightingShader.setVec3("spotLights[23].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[23].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[23].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[23].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[23].k_c", k_c);
            lightingShader.setFloat("spotLights[23].k_l", k_l);
            lightingShader.setFloat("spotLights[23].k_q", k_q);

            }
        else if (lightNumber == 25)
        {
            lightingShader.setVec3("spotLights[24].position", position);
            lightingShader.setVec3("spotLights[24].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[24].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[24].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[24].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[24].k_c", k_c);
            lightingShader.setFloat("spotLights[24].k_l", k_l);
            lightingShader.setFloat("spotLights[24].k_q", k_q);

            }
        else if (lightNumber == 26)
        {
            lightingShader.setVec3("spotLights[25].position", position);
            lightingShader.setVec3("spotLights[25].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[25].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[25].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[25].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[25].k_c", k_c);
            lightingShader.setFloat("spotLights[25].k_l", k_l);
            lightingShader.setFloat("spotLights[25].k_q", k_q);

            }
        else if (lightNumber == 27)
        {
            lightingShader.setVec3("spotLights[26].position", position);
            lightingShader.setVec3("spotLights[26].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[26].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[26].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[26].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[26].k_c", k_c);
            lightingShader.setFloat("spotLights[26].k_l", k_l);
            lightingShader.setFloat("spotLights[26].k_q", k_q);

            }
        else if (lightNumber == 28)
        {
            lightingShader.setVec3("spotLights[27].position", position);
            lightingShader.setVec3("spotLights[27].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[27].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[27].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[27].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[27].k_c", k_c);
            lightingShader.setFloat("spotLights[27].k_l", k_l);
            lightingShader.setFloat("spotLights[27].k_q", k_q);

            }
        else if (lightNumber == 29)
        {
            lightingShader.setVec3("spotLights[28].position", position);
            lightingShader.setVec3("spotLights[28].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[28].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[28].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[28].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[28].k_c", k_c);
            lightingShader.setFloat("spotLights[28].k_l", k_l);
            lightingShader.setFloat("spotLights[28].k_q", k_q);

            }
        else if (lightNumber == 30)
        {
            lightingShader.setVec3("spotLights[29].position", position);
            lightingShader.setVec3("spotLights[29].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[29].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[29].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[29].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[29].k_c", k_c);
            lightingShader.setFloat("spotLights[29].k_l", k_l);
            lightingShader.setFloat("spotLights[29].k_q", k_q);

            }
        else if (lightNumber == 31)
        {
            lightingShader.setVec3("spotLights[30].position", position);
            lightingShader.setVec3("spotLights[30].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[30].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[30].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[30].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[30].k_c", k_c);
            lightingShader.setFloat("spotLights[30].k_l", k_l);
            lightingShader.setFloat("spotLights[30].k_q", k_q);

            }
        else if (lightNumber == 32)
        {
            lightingShader.setVec3("spotLights[31].position", position);
            lightingShader.setVec3("spotLights[31].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[31].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[31].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[31].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[31].k_c", k_c);
            lightingShader.setFloat("spotLights[31].k_l", k_l);
            lightingShader.setFloat("spotLights[31].k_q", k_q);

            }
        else if (lightNumber == 33)
        {
            lightingShader.setVec3("spotLights[32].position", position);
            lightingShader.setVec3("spotLights[32].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[32].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[32].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[32].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[32].k_c", k_c);
            lightingShader.setFloat("spotLights[32].k_l", k_l);
            lightingShader.setFloat("spotLights[32].k_q", k_q);

            }
        else if (lightNumber == 34)
        {
            lightingShader.setVec3("spotLights[33].position", position);
            lightingShader.setVec3("spotLights[33].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[33].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[33].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[33].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[33].k_c", k_c);
            lightingShader.setFloat("spotLights[33].k_l", k_l);
            lightingShader.setFloat("spotLights[33].k_q", k_q);

            }
        else if (lightNumber == 35)
        {
            lightingShader.setVec3("spotLights[34].position", position);
            lightingShader.setVec3("spotLights[34].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[34].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[34].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[34].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[34].k_c", k_c);
            lightingShader.setFloat("spotLights[34].k_l", k_l);
            lightingShader.setFloat("spotLights[34].k_q", k_q);

            }
        else if (lightNumber == 36)
        {
            lightingShader.setVec3("spotLights[35].position", position);
            lightingShader.setVec3("spotLights[35].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[35].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[35].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[35].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[35].k_c", k_c);
            lightingShader.setFloat("spotLights[35].k_l", k_l);
            lightingShader.setFloat("spotLights[35].k_q", k_q);

            }
        else if (lightNumber == 37)
        {
            lightingShader.setVec3("spotLights[36].position", position);
            lightingShader.setVec3("spotLights[36].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[36].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[36].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[36].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[36].k_c", k_c);
            lightingShader.setFloat("spotLights[36].k_l", k_l);
            lightingShader.setFloat("spotLights[36].k_q", k_q);

            }
        else if (lightNumber == 38)
        {
            lightingShader.setVec3("spotLights[37].position", position);
            lightingShader.setVec3("spotLights[37].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[37].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[37].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[37].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[37].k_c", k_c);
            lightingShader.setFloat("spotLights[37].k_l", k_l);
            lightingShader.setFloat("spotLights[37].k_q", k_q);

            }

      /*  else
        {
            lightingShader.setVec3("spotLights[3].position", position);
            lightingShader.setVec3("spotLights[3].ambient", ambientOn * ambient);
            lightingShader.setVec3("spotLights[3].diffuse", diffuseOn * diffuse);
            lightingShader.setVec3("spotLights[3].specular", specularOn * specular);
            lightingShader.setVec3("spotLights[3].emission", glm::vec3(0.2f, 0.2f, 0.2f));
            lightingShader.setFloat("spotLights[3].k_c", k_c);
            lightingShader.setFloat("spotLights[3].k_l", k_l);
            lightingShader.setFloat("spotLights[3].k_q", k_q);
        }*/
    }
    void turnOff()
    {
        ambientOn = 0.0;
        diffuseOn = 0.0;
        specularOn = 0.0;
    }
    void turnOn()
    {
        ambientOn = 1.0;
        diffuseOn = 1.0;
        specularOn = 1.0;
    }
    void turnAmbientOn()
    {
        ambientOn = 1.0;
    }
    void turnAmbientOff()
    {
        ambientOn = 0.0;
    }
    void turnDiffuseOn()
    {
        diffuseOn = 1.0;
    }
    void turnDiffuseOff()
    {
        diffuseOn = 0.0;
    }
    void turnSpecularOn()
    {
        specularOn = 1.0;
    }
    void turnSpecularOff()
    {
        specularOn = 0.0;
    }
private:
    float ambientOn = 1.0;
    float diffuseOn = 1.0;
    float specularOn = 1.0;
};

#endif