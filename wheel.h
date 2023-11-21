//
//  cube.h
//  test
//
//  Created by Nazirul Hasan on 4/10/23.
//

#ifndef wheel_h
#define wheel_h

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include <corecrt_math_defines.h> 

using namespace std;

class Wheel {
public:

    // materialistic property
   /* glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;*/

    //// texture property
    //float TXmin = 0.0f;
    //float TXmax = 1.0f;
    //float TYmin = 0.0f;
    //float TYmax = 1.0f;
    //unsigned int diffuseMap;
    //unsigned int specularMap;

    // common property
   /* float shininess;*/

    // constructors
    Wheel()
    {
        setUpCubeVertexDataAndConfigureVertexAttribute();
    }

    /*Wheel(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float shiny)
    {
        this->ambient = amb;
        this->diffuse = diff;
        this->specular = spec;
        this->shininess = shiny;

        setUpCubeVertexDataAndConfigureVertexAttribute();
    }

    Cube(unsigned int dMap, unsigned int sMap, float shiny, float textureXmin, float textureYmin, float textureXmax, float textureYmax)
    {
        this->diffuseMap = dMap;
        this->specularMap = sMap;
        this->shininess = shiny;
        this->TXmin = textureXmin;
        this->TYmin = textureYmin;
        this->TXmax = textureXmax;
        this->TYmax = textureYmax;

        setUpCubeVertexDataAndConfigureVertexAttribute();
    }*/

    // destructor
    ~Wheel()
    {
        glDeleteVertexArrays(1, &VAO1);
        glDeleteVertexArrays(1, &VAO2);
        glDeleteVertexArrays(1, &VAO3);
        glDeleteBuffers(1, &VBO1);
        glDeleteBuffers(1, &VBO2);
        glDeleteBuffers(1, &VBO3);
        glDeleteBuffers(1, &EBO1);
        glDeleteBuffers(1, &EBO2);
        glDeleteBuffers(1, &EBO3);
    }

    //void drawCubeWithTexture(Shader& lightingShaderWithTexture, glm::mat4 model = glm::mat4(1.0f))
    //{
    //    lightingShaderWithTexture.use();

    //    lightingShaderWithTexture.setInt("material.diffuse", 0);
    //    lightingShaderWithTexture.setInt("material.specular", 1);
    //    lightingShaderWithTexture.setFloat("material.shininess", this->shininess);


    //    // bind diffuse map
    //    glActiveTexture(GL_TEXTURE0);
    //    glBindTexture(GL_TEXTURE_2D, this->diffuseMap);
    //    // bind specular map
    //    glActiveTexture(GL_TEXTURE1);
    //    glBindTexture(GL_TEXTURE_2D, this->specularMap);

    //    lightingShaderWithTexture.setMat4("model", model);

    //    glBindVertexArray(lightTexCubeVAO);
    //    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //}

    //void drawCubeWithMaterialisticProperty(Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f))
    //{
    //    lightingShader.use();

    //    lightingShader.setVec3("material.ambient", this->ambient);
    //    lightingShader.setVec3("material.diffuse", this->diffuse);
    //    lightingShader.setVec3("material.specular", this->specular);
    //    lightingShader.setFloat("material.shininess", this->shininess);

    //    lightingShader.setMat4("model", model);

    //    glBindVertexArray(lightCubeVAO);
    //    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //}

    void drawWheel(Shader& shader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
    {
        shader.use();
        shader.setVec3("color", glm::vec3(r, g, b));
        shader.setMat4("model", model);

        glBindVertexArray(VAO1);
        glDrawElements(GL_TRIANGLES, wheelIndices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(VAO2);
        glDrawElements(GL_TRIANGLES, wheelIndices2.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(VAO3);
        glDrawElements(GL_TRIANGLES, wheelIndices3.size(), GL_UNSIGNED_INT, 0);
    }

    /*void setMaterialisticProperty(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float shiny)
    {
        this->ambient = amb;
        this->diffuse = diff;
        this->specular = spec;
        this->shininess = shiny;
    }

    void setTextureProperty(unsigned int dMap, unsigned int sMap, float shiny)
    {
        this->diffuseMap = dMap;
        this->specularMap = sMap;
        this->shininess = shiny;
    }*/

private:
    unsigned int VAO1;
    unsigned int VAO2;
    unsigned int VAO3;

    unsigned int VBO1;
    unsigned int VBO2;
    unsigned int VBO3;
    unsigned int EBO1;
    unsigned int EBO2;
    unsigned int EBO3;

    std::vector<float> wheelVertices, wheelVertices2, wheelVertices3;
    std::vector<unsigned int> wheelIndices, wheelIndices2, wheelIndices3;

    void setUpCubeVertexDataAndConfigureVertexAttribute()
    {
        const int numSegments = 36; // Number of segments in the wheel
        const float radius = 1.0f;  // Radius of the wheel

        // Specify color (black)
        float r = 1.0f;
        float g = 0.0f;
        float b = 1.0f;

        // Specify origin (center)
        float originX = 0.0f;
        float originY = 0.0f;
        float originZ = 0.0f;

        // Center vertex
        wheelVertices.push_back(originX);
        wheelVertices2.push_back(originX);
        wheelVertices.push_back(originY);
        wheelVertices2.push_back(originY);
        wheelVertices.push_back(originZ);
        wheelVertices2.push_back(0.5f);

        // Color for the center vertex
        wheelVertices.push_back(r);
        wheelVertices2.push_back(r);
        wheelVertices.push_back(g);
        wheelVertices2.push_back(g);
        wheelVertices.push_back(b);
        wheelVertices2.push_back(b);

        // Generate vertices and indices for the wheel
        for (int i = 1; i <= numSegments; i++) {
            float angle = (2 * M_PI * i) / numSegments;
            float x = originX + radius * cos(angle);
            float y = originY + radius * sin(angle);

            // Vertex
            wheelVertices.push_back(x);
            wheelVertices2.push_back(x);
            wheelVertices.push_back(y);
            wheelVertices2.push_back(y);
            wheelVertices.push_back(originZ);
            wheelVertices2.push_back(0.5f);

            // Color for the vertex
            wheelVertices.push_back(r);
            wheelVertices2.push_back(r);
            wheelVertices.push_back(g);
            wheelVertices2.push_back(g);
            wheelVertices.push_back(b);
            wheelVertices2.push_back(b);

            // Indices for the triangle fan
            wheelIndices.push_back(0);
            wheelIndices2.push_back(0);
            wheelIndices.push_back(i);
            wheelIndices2.push_back(i);
            wheelIndices.push_back((i + 1) % (numSegments + 1));
            wheelIndices2.push_back((i + 1) % (numSegments + 1));
        }
        // Indices for the triangle fan
        wheelIndices.push_back(0);
        wheelIndices2.push_back(0);
        wheelIndices.push_back(36);
        wheelIndices2.push_back(36);
        wheelIndices.push_back(1);
        wheelIndices2.push_back(1);



        for (int i = 0; i < wheelVertices.size(); i++)
        {
            wheelVertices3.push_back(wheelVertices[i]);
        }
        for (int i = 0; i < wheelVertices2.size(); i++)
        {
            wheelVertices3.push_back(wheelVertices2[i]);
        }
        for (int i = 1; i < wheelVertices2.size(); i++)
        {
            if (i < 36)
            {

                wheelIndices3.push_back(i);
                wheelIndices3.push_back(i + 37);
                wheelIndices3.push_back(i + 1);

                wheelIndices3.push_back(i + 1);
                wheelIndices3.push_back(i + 37);
                wheelIndices3.push_back(i + 37 + 1);
            }
            else if (i == 36)
            {
                wheelIndices3.push_back(i);
                wheelIndices3.push_back(i + 37);
                wheelIndices3.push_back(i + 1);

                wheelIndices3.push_back(i + 1);
                wheelIndices3.push_back(i + 37);
                wheelIndices3.push_back(i + 37 + 1);
            }
        }

        glGenVertexArrays(1, &VAO1);
        glGenVertexArrays(1, &VAO2);
        glGenVertexArrays(1, &VAO3);
        glGenBuffers(1, &VBO1);
        glGenBuffers(1, &VBO2);
        glGenBuffers(1, &VBO3);
        glGenBuffers(1, &EBO1);
        glGenBuffers(1, &EBO2);
        glGenBuffers(1, &EBO3);


        glBindVertexArray(VAO1);

        glBindBuffer(GL_ARRAY_BUFFER, VBO1);
        glBufferData(GL_ARRAY_BUFFER, wheelVertices.size() * sizeof(float), wheelVertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, wheelIndices.size(), wheelIndices.data(), GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // vertex normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
        glEnableVertexAttribArray(1);


        glBindVertexArray(VAO2);

        glBindBuffer(GL_ARRAY_BUFFER, VBO2);
        glBufferData(GL_ARRAY_BUFFER, wheelVertices2.size() * sizeof(float), wheelVertices2.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, wheelIndices2.size(), wheelIndices2.data(), GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // vertex normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
        glEnableVertexAttribArray(1);

        glBindVertexArray(VAO3);

        glBindBuffer(GL_ARRAY_BUFFER, VBO3);
        glBufferData(GL_ARRAY_BUFFER, wheelVertices3.size() * sizeof(float), wheelVertices3.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO3);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, wheelIndices3.size(), wheelIndices3.data(), GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // vertex normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
        glEnableVertexAttribArray(1);

    }

};


#endif /* wheel_h */
