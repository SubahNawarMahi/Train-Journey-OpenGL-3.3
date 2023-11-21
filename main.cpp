//
//  main.cpp
//  3D Object Drawing
//
//  Created by Nazirul Hasan on 4/9/23.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION  
#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "pointLight.h"
#include "spotLight.h"
#include "directionalLight.h"
#include "sphere2.h"
#include "sphere.h"
#include "cube.h"
#include "stb_image.h"
#include <iostream>
#include <corecrt_math_defines.h> 
#include "cylinder.h"
#include "wheel.h"
#include "pyramid.h"
#include "CurvedRoad.h"
#include "Curve.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);
void bed(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);


// settings
const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 900;

// modelling transform
float rotateAngle_X = 45.0;
float rotateAngle_Y = 45.0;
float rotateAngle_Z = 45.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = -0.5;
float translate_Y = 0.0;
float translate_Z = -0.7;
float scale_X = 0.2;
float scale_Y = 0.2;
float scale_Z = 0.2;
float forward = 0.0;
float backward = 0.0; 
float left = 0.0;
float right = 0.0;
bool hotKey = false;

// camera
Camera camera(glm::vec3(3.0, 4.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 3.0, eyeY = 4.0, eyeZ = 3.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);


bool fan_on = false;
float rotateAngle = 0.0;



// positions of the point lights
glm::vec3 pointLightPositions[] = {
   // glm::vec3(1.50f + 10.0f,  1.50f+10.0f,  0.0f),
    glm::vec3(0.0f, 5.39f,3.5f),
    glm::vec3(-0.8f, 5.39f,3.5f-6.0f),
    glm::vec3(13.5f, 8.39f,1.5f),
    glm::vec3(0.0f + 60.5f, 5.39f,3.5f),
    glm::vec3(-0.8f + 60.5f, 5.39f,3.5f - 6.0f),
    glm::vec3(13.5f + 60.5f, 8.39f,1.5f),
   //glm::vec3(30.0f, 28.0f,21.0f),
    /*
    glm::vec3(-1.5f + 10.0f,  -1.5f+10.0f,  0.0f)*/
};
glm::vec3 spotLightPositions[] = {
      glm::vec3(17.5484f - 0.8 + 0.2, 5.76f, 3.05979f - 2.0f - 1.0f),//0
      glm::vec3(17.5484f-0.8+0.2+4, 5.76f, 3.05979f-2.0f-1.0f),
      glm::vec3(17.5484f-0.8+0.2+8, 5.76f, 3.05979f-2.0f-1.0f),
      glm::vec3(17.5484f-0.8+0.2+12, 5.76f, 3.05979f-2.0f-1.0f),
      glm::vec3(17.5484f-0.8+0.2+16, 5.76f, 3.05979f-2.0f-1.0f),
      glm::vec3(17.5484f-0.8+0.2+20, 5.76f, 3.05979f-2.0f-1.0f),
      glm::vec3(17.5484f-0.8+0.2+24, 5.76f, 3.05979f-2.0f-1.0f),
      glm::vec3(17.5484f-0.8+0.2+28, 5.76f, 3.05979f-2.0f-1.0f),
      glm::vec3(17.5484f-0.8+0.2+32, 5.76f, 3.05979f-2.0f-1.0f),
      glm::vec3(17.5484f-0.8+0.2+36, 5.76f, 3.05979f-2.0f-1.0f),
      glm::vec3(17.5484f-0.8+0.2+40-1, 5.76f, 3.05979f-2.0f-1.0f),//10
      

      glm::vec3(17.5484f - 0.8 + 0.2, 5.76f, 3.05979f - 2.0f),//11
      glm::vec3(17.5484f - 0.8 + 0.2+4, 5.76f, 3.05979f - 2.0f),
      glm::vec3(17.5484f - 0.8 + 0.2+8, 5.76f, 3.05979f - 2.0f),
      glm::vec3(17.5484f - 0.8 + 0.2+12, 5.76f, 3.05979f - 2.0f),
      glm::vec3(17.5484f - 0.8 + 0.2+16, 5.76f, 3.05979f - 2.0f),
      glm::vec3(17.5484f - 0.8 + 0.2+20, 5.76f, 3.05979f - 2.0f),
      glm::vec3(17.5484f - 0.8 + 0.2+24, 5.76f, 3.05979f - 2.0f),
      glm::vec3(17.5484f - 0.8 + 0.2+28, 5.76f, 3.05979f - 2.0f),
      glm::vec3(17.5484f - 0.8 + 0.2+32, 5.76f, 3.05979f - 2.0f),
      glm::vec3(17.5484f - 0.8 + 0.2+36, 5.76f, 3.05979f - 2.0f),
      glm::vec3(17.5484f - 0.8 + 0.2+40-1, 5.76f, 3.05979f - 2.0f),//21

     glm::vec3( -4.0+0.44, 0.93, 2.05979 + 0.9 + 0.1 - 0.18 + 0.03-1.05),//22
     glm::vec3(-4.0 + 0.44+4, 0.93, 2.05979 + 0.9 + 0.1 - 0.18 + 0.03 - 1.05),
     glm::vec3(-4.0 + 0.44+8, 0.93, 2.05979 + 0.9 + 0.1 - 0.18 + 0.03 - 1.05),
     glm::vec3(-4.0 + 0.44+12, 0.93, 2.05979 + 0.9 + 0.1 - 0.18 + 0.03 - 1.05),
     glm::vec3(-4.0 + 0.44+16, 0.93, 2.05979 + 0.9 + 0.1 - 0.18 + 0.03 - 1.05),
     glm::vec3(-4.0 + 0.44+20, 0.93, 2.05979 + 0.9 + 0.1 - 0.18 + 0.03 - 1.05),
     glm::vec3(-4.0 + 0.44+24, 0.93, 2.05979 + 0.9 + 0.1 - 0.18 + 0.03 - 1.05),
     glm::vec3(-4.0 + 0.44+28, 0.93, 2.05979 + 0.9 + 0.1 - 0.18 + 0.03 - 1.05),
     glm::vec3(-4.0 + 0.44+32, 0.93, 2.05979 + 0.9 + 0.1 - 0.18 + 0.03 - 1.05),

     glm::vec3(-4.0 + 0.44+44, 0.93, 2.05979 + 0.9 + 0.1 - 0.18 + 0.03 - 1.05),//31
     glm::vec3(-4.0 + 0.44+48, 0.93, 2.05979 + 0.9 + 0.1 - 0.18 + 0.03 - 1.05),
     glm::vec3(-4.0 + 0.44+52, 0.93, 2.05979 + 0.9 + 0.1 - 0.18 + 0.03 - 1.05),
     glm::vec3(-4.0 + 0.44 + 56, 0.93, 2.05979 + 0.9 + 0.1 - 0.18 + 0.03 - 1.05),
     glm::vec3(-4.0 + 0.44 + 60, 0.93, 2.05979 + 0.9 + 0.1 - 0.18 + 0.03 - 1.05),
     glm::vec3(-4.0 + 0.44 + 64, 0.93, 2.05979 + 0.9 + 0.1 - 0.18 + 0.03 - 1.05),
     glm::vec3(-4.0 + 0.44 + 68, 0.93, 2.05979 + 0.9 + 0.1 - 0.18 + 0.03 - 1.05),
   
};
glm::vec3 directionLightPositions[] = {
     glm::vec3(30.0f, 18.0f,21.0f),
    // glm::vec3(30.0f,  59.0f ,  0.0f),
    // glm::vec3(30.0f, 0.0f,-22.0f),
     // glm::vec3(5.0f, 30.0f, 5.0f),

};

PointLight pointlight1(

    pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);
PointLight pointlight2(

    pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2      // light number
);
PointLight pointlight3(

    pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    3      // light number
);
PointLight pointlight4(

    pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    4      // light number
);
PointLight pointlight5(

    pointLightPositions[4].x, pointLightPositions[4].y, pointLightPositions[4].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    5      // light number
);
PointLight pointlight6(

    pointLightPositions[5].x, pointLightPositions[5].y, pointLightPositions[5].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    6      // light number
);
//PointLight pointlight2(
//
//    pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z,  // position
//    0.05f, 0.05f, 0.05f,     // ambient
//    0.8f, 0.8f, 0.8f,     // diffuse
//    1.0f, 1.0f, 1.0f,        // specular
//    1.0f,   //k_c
//    0.09f,  //k_l
//    0.032f, //k_q
//    2       // light number
//);
//PointLight pointlight3(
//
//    pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z,  // position
//    0.05f, 0.05f, 0.05f,     // ambient
//    0.8f, 0.8f, 0.8f,     // diffuse
//    1.0f, 1.0f, 1.0f,        // specular
//    1.0f,   //k_c
//    0.09f,  //k_l
//    0.032f, //k_q
//    3       // light number
//);
//PointLight pointlight4(
//
//    pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z,  // position
//    0.05f, 0.05f, 0.05f,     // ambient
//    0.8f, 0.8f, 0.8f,     // diffuse
//    1.0f, 1.0f, 1.0f,        // specular
//    1.0f,   //k_c
//    0.09f,  //k_l
//    0.032f, //k_q
//   4       // light number
//);

SpotLight spotlight1(

    spotLightPositions[0].x, spotLightPositions[0].y, spotLightPositions[0].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);
SpotLight spotlight2(

    spotLightPositions[1].x, spotLightPositions[1].y, spotLightPositions[1].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);
SpotLight spotlight3(

    spotLightPositions[2].x, spotLightPositions[2].y, spotLightPositions[2].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    3       // light number
);
SpotLight spotlight4(

    spotLightPositions[3].x, spotLightPositions[3].y, spotLightPositions[3].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    4       // light number
);
SpotLight spotlight5(

    spotLightPositions[4].x, spotLightPositions[4].y, spotLightPositions[4].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
   5       // light number
);
SpotLight spotlight6(

    spotLightPositions[5].x, spotLightPositions[5].y, spotLightPositions[5].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
   6       // light number
);
SpotLight spotlight7(

    spotLightPositions[6].x, spotLightPositions[6].y, spotLightPositions[6].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    7       // light number
);
SpotLight spotlight8(

    spotLightPositions[7].x, spotLightPositions[7].y, spotLightPositions[7].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
   8      // light number
);
SpotLight spotlight9(

    spotLightPositions[8].x, spotLightPositions[8].y, spotLightPositions[8].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    9      // light number
);
SpotLight spotlight10(

    spotLightPositions[9].x, spotLightPositions[9].y, spotLightPositions[9].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    10       // light number
);
SpotLight spotlight11(

    spotLightPositions[10].x, spotLightPositions[10].y, spotLightPositions[10].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    11       // light number
);

SpotLight spotlight12(

    spotLightPositions[11].x, spotLightPositions[11].y, spotLightPositions[11].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    12       // light number
);
SpotLight spotlight13(

    spotLightPositions[12].x, spotLightPositions[12].y, spotLightPositions[12].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    13       // light number
);
SpotLight spotlight14(

    spotLightPositions[13].x, spotLightPositions[13].y, spotLightPositions[13].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    14      // light number
);
SpotLight spotlight15(

    spotLightPositions[14].x, spotLightPositions[14].y, spotLightPositions[14].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    15      // light number
);
SpotLight spotlight16(

    spotLightPositions[15].x, spotLightPositions[15].y, spotLightPositions[15].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    16       // light number
);
SpotLight spotlight17(

    spotLightPositions[16].x, spotLightPositions[16].y, spotLightPositions[16].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    17      // light number
);
SpotLight spotlight18(

    spotLightPositions[17].x, spotLightPositions[17].y, spotLightPositions[17].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    18      // light number
);
SpotLight spotlight19(

    spotLightPositions[18].x, spotLightPositions[18].y, spotLightPositions[18].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    19       // light number
);
SpotLight spotlight20(

    spotLightPositions[19].x, spotLightPositions[19].y, spotLightPositions[19].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    20      // light number
);
SpotLight spotlight21(

    spotLightPositions[20].x, spotLightPositions[20].y, spotLightPositions[20].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    21       // light number
);
SpotLight spotlight22(

    spotLightPositions[21].x, spotLightPositions[21].y, spotLightPositions[21].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    22       // light number
);

SpotLight spotlight23(

    spotLightPositions[22].x, spotLightPositions[22].y, spotLightPositions[22].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    23       // light number
);

SpotLight spotlight24(

    spotLightPositions[23].x, spotLightPositions[23].y, spotLightPositions[23].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    24      // light number
);

SpotLight spotlight25(

    spotLightPositions[24].x, spotLightPositions[24].y, spotLightPositions[24].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    25      // light number
);

SpotLight spotlight26(

    spotLightPositions[25].x, spotLightPositions[25].y, spotLightPositions[25].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    26       // light number
);

SpotLight spotlight27(

    spotLightPositions[26].x, spotLightPositions[26].y, spotLightPositions[26].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    27      // light number
);

SpotLight spotlight28(

    spotLightPositions[27].x, spotLightPositions[27].y, spotLightPositions[27].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    28      // light number
);

SpotLight spotlight29(

    spotLightPositions[28].x, spotLightPositions[28].y, spotLightPositions[28].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    29      // light number
);

SpotLight spotlight30(

    spotLightPositions[29].x, spotLightPositions[29].y, spotLightPositions[29].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    30       // light number
);

SpotLight spotlight31(

    spotLightPositions[30].x, spotLightPositions[30].y, spotLightPositions[30].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    31      // light number
);

SpotLight spotlight32(

    spotLightPositions[31].x, spotLightPositions[31].y, spotLightPositions[31].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    32       // light number
);

SpotLight spotlight33(

    spotLightPositions[32].x, spotLightPositions[32].y, spotLightPositions[32].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    33      // light number
);

SpotLight spotlight34(

    spotLightPositions[33].x, spotLightPositions[33].y, spotLightPositions[33].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    34      // light number
);

SpotLight spotlight35(

    spotLightPositions[34].x, spotLightPositions[34].y, spotLightPositions[34].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    35       // light number
);

SpotLight spotlight36(

    spotLightPositions[35].x, spotLightPositions[35].y, spotLightPositions[35].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    36       // light number
);

SpotLight spotlight37(

    spotLightPositions[36].x, spotLightPositions[36].y, spotLightPositions[36].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    37       // light number
);

SpotLight spotlight38(

    spotLightPositions[37].x, spotLightPositions[37].y, spotLightPositions[37].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    38       // light number
);


DirectionLight directionlight1(

    directionLightPositions[0].x, directionLightPositions[0].y, directionLightPositions[0].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);



// light settings
bool pointLightOn = true;
bool spotLightOn = true;
bool directionLightOn = true;
bool ambientToggle = true;
bool diffuseToggle = true;
bool specularToggle = true;

bool journey = false;


// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

// Car parameters
const float wheelRadius = 0.9f;
float carSpeed = 1.0f; // Adjust as needed

// Car transformation variables
glm::vec3 carPosition(0.0f, 0.0f, 0.0f);
float wheelRotation = 0.0f;


bool train_start = false;
bool train_start_release = false;
bool train_reverse_start = false;
bool train_reverse_start_release = false;
float train_translate = 0.0f;
float t = 1.0f;

bool  boatTranslate_forward = true;
float boatSpeed = 1.0;
float boatTranslate = 0.0;

float red_carSpeed = 2.0;
float red_carTranslate = 0.0;
float red_carWheelRotation = 0.0;
bool red_car_forward = true;

float mint_turqudise_carSpeed = 2.0;
float mint_turqudise_carTranslate = 0.0;
float mint_turqudise_carWheelRotation = 0.0;
bool mint_turqudise_car_forward = true;

bool train_door_open = false;
bool train_door_closed = false;
float train_doorSpeed = 0.05;
float train_doorTranslate= 0.0;
bool first = true;

glm::mat4 model_Matrix(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z,float angleX, float angleY, float angleZ)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;


    //floor_lemon_color_cube
    translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X + t_x, translate_Y + t_y, translate_Z + t_z));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f+angleX), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f+angleY), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f+angleZ), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X * s_x, scale_Y * s_y, scale_Z * s_z));
    model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
   
    return model;

}

void railroad_ties_color(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z,float r_x,float r_y,float r_z, unsigned int& cubeVAO, Shader& lightingShader)
{
    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
    lightingShader.setMat4("model", model);
    drawCube(cubeVAO, lightingShader, model, 0.207f, 0.105f, 0.0784f);
}

void yellow_color(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
{
    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
    lightingShader.setMat4("model", model);
    
    drawCube(cubeVAO, lightingShader, model, 0.968f, 0.776f, 0.0f);
}
void red_color(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
{
    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
    lightingShader.setMat4("model", model);

    drawCube(cubeVAO, lightingShader, model, 1.0f, 0.0f, 0.0f);
}
void mint_turqudise_color(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
{
    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
    lightingShader.setMat4("model", model);

    drawCube(cubeVAO, lightingShader, model, 0.0f, 0.6431f, 0.6156f);
}
void light_red_color(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
{
    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
    lightingShader.setMat4("model", model);

    drawCube(cubeVAO, lightingShader, model, 0.3f, 0.0f, 0.0f);
}
void building4_color(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
{
    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
    lightingShader.setMat4("model", model);

    drawCube(cubeVAO, lightingShader, model, 0.909f, 0.694f, 0.501f);
}
void building5_color(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
{
    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
    lightingShader.setMat4("model", model);

    drawCube(cubeVAO, lightingShader, model, 0.639f, 0.337f, 0.211f);
}
void building6_color(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
{
    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
    lightingShader.setMat4("model", model);

    drawCube(cubeVAO, lightingShader, model, 0.682f, 0.694f, 0.713f);
}
void wall_color(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
{
    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
    lightingShader.setMat4("model", model);
    drawCube(cubeVAO, lightingShader, model, 0.741f, 0.549f, 0.898f);
}
void green_color(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
{
    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
    lightingShader.setMat4("model", model);
    drawCube(cubeVAO, lightingShader, model, 0.0f, 1.0f, 0.0f);
}
void grey_color(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
{
    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
    lightingShader.setMat4("model", model);
    drawCube(cubeVAO, lightingShader, model, 0.5f, 0.5f, 0.5f);
}
void black_color(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
{
    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
    lightingShader.setMat4("model", model);
    drawCube(cubeVAO, lightingShader, model, 0.0f, 0.0f, 0.0f);
}

void white_color(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
{
    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
    lightingShader.setMat4("model", model);
    drawCube(cubeVAO, lightingShader, model, 1.0f, 1.0f, 1.0f);
}
//void lemon_color_ceiling(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
//{
//    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
//    lightingShader.setMat4("model", model);
//    drawCube(cubeVAO, lightingShader, model, 0.980f, 0.9490f, 0.733f);
//}
//void almirah(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
//{
//    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
//    lightingShader.setMat4("model", model);
//    drawCube(cubeVAO, lightingShader, model, 1.0f, 1.0f, 1.0f);
//}
//void laptop_low(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
//{
//    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
//    lightingShader.setMat4("model", model);
//    drawCube(cubeVAO, lightingShader, model, 0.9019f, 0.9058f, 0.9098f);
//}
//void laptop_keypad(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
//{
//    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
//    lightingShader.setMat4("model", model);
//    drawCube(cubeVAO, lightingShader, model, 0.9019f, 0.9058f, 0.9098f);
//}
//void laptop_up(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
//{
//    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
//    lightingShader.setMat4("model", model);
//    drawCube(cubeVAO, lightingShader, model, 1.0f, 1.0f, 1.0f);
//}
//void laptop_screen(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
//{
//    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
//    lightingShader.setMat4("model", model);
//    drawCube(cubeVAO, lightingShader, model, 0.04313f, 0.4078f, 0.698f);
//}
//void almirah_shelf(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
//{
//    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
//    lightingShader.setMat4("model", model);
//    drawCube(cubeVAO, lightingShader, model, 0.254f, 0.0078f, 0.0f);
//}
void pink_color(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
{
    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
    lightingShader.setMat4("model", model);
    drawCube(cubeVAO, lightingShader, model, 0.796f, 0.674f, 0.533f);
    // drawCube(cubeVAO, lightingShader, model, 1.0f, 1.0f, 1.0f);
}

void blue_color(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
{
    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
    lightingShader.setMat4("model", model);
    drawCube(cubeVAO, lightingShader, model, 0.0f, 0.0f, 1.0f);
}

void bg_color(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
{
    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
    lightingShader.setMat4("model", model);
    drawCube(cubeVAO, lightingShader, model, 0.898f, 0.964f, 0.998f);
}
//void carpet(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
//{
//    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
//    lightingShader.setMat4("model", model);
//    drawCube(cubeVAO, lightingShader, model, 1.0f, 0.812f, 0.8588f);
//}
//void carpet2(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
//{
//    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
//    lightingShader.setMat4("model", model);
//    drawCube(cubeVAO, lightingShader, model, 0.996f, 0.2039f, 0.494f);
//
//}
//void book_color(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
//{
//    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
//    lightingShader.setMat4("model", model);
//    drawCube(cubeVAO, lightingShader, model, 1.0f, 1.0f, 1.0f);
//}
//void book_color_1(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
//{
//    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
//    lightingShader.setMat4("model", model);
//    drawCube(cubeVAO, lightingShader, model, 0.24f, 0.58f, 0.50f);
//}
//void book_color_2(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
//{
//    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
//    lightingShader.setMat4("model", model);
//    drawCube(cubeVAO, lightingShader, model, 0.494f, 0.505f, 0.16f);
//}
//void book_color_3(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
//{
//    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
//    lightingShader.setMat4("model", model);
//    drawCube(cubeVAO, lightingShader, model, 0.294f, 0.68f, 0.235f);
//}
//
//void book_color_4(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
//{
//    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
//    lightingShader.setMat4("model", model);
//    drawCube(cubeVAO, lightingShader, model, 0.239f, 1.0f, 0.87f);
//}
//void book1(float tx, float ty, float tz, unsigned int& cubeVAO, Shader& lightingShader)
//{
//    book_color(1, 3, 3, 3 + tx, 2 + ty, 2 + tz,0,0,20, cubeVAO, lightingShader);
//    book_color_1(0.2, 3, 3, 2.98 + tx, 1.99 + ty, 2 + tz, 0, 0, 20, cubeVAO, lightingShader);
//    book_color_1(0.2, 3, 3.15, 3.1 + tx, 2.035 + ty, 2 + tz, 0, 0, 20, cubeVAO, lightingShader);
//    book_color_1(1.48, 3, 0.2, 2.98 + tx, 1.99 + ty, 2.3 + tz, 0, 0, 20, cubeVAO, lightingShader);
//}
//void book2(float tx, float ty, float tz, unsigned int& cubeVAO, Shader& lightingShader)
//{
//    book_color(1, 3, 3, 3 + tx, 2 + ty, 2 + tz, 0, 0, 20, cubeVAO, lightingShader);
//    book_color_2(0.2, 3, 3, 2.98 + tx, 1.99 + ty, 2 + tz, 0, 0, 20, cubeVAO, lightingShader);
//    book_color_2(0.2, 3, 3.15, 3.1 + tx, 2.035 + ty, 2 + tz, 0, 0,20, cubeVAO, lightingShader);
//    book_color_2(1.48, 3, 0.2, 2.98 + tx, 1.99 + ty, 2.3 + tz, 0, 0, 20, cubeVAO, lightingShader);
//}
//
//void book3(float tx, float ty, float tz, unsigned int& cubeVAO, Shader& lightingShader)
//{
//    book_color(1, 3, 3, 3 + tx, 2 + ty, 2 + tz, 0, 0, 20, cubeVAO, lightingShader);
//    book_color_3(0.2, 3, 3, 2.98 + tx, 1.99 + ty, 2 + tz, 0, 0, 20, cubeVAO, lightingShader);
//    book_color_3(0.2, 3, 3.15, 3.1 + tx, 2.035 + ty, 2 + tz, 0, 0, 20, cubeVAO, lightingShader);
//    book_color_3(1.48, 3, 0.2, 2.98 + tx, 1.99 + ty, 2.3 + tz, 0, 0, 20, cubeVAO, lightingShader);
//}
//
//void book4(float tx, float ty, float tz, unsigned int& cubeVAO, Shader& lightingShader)
//{
//    book_color(1, 3, 3, 3 + tx, 2 + ty, 2 + tz, 0, 0, 20, cubeVAO, lightingShader);
//    book_color_4(0.2, 3, 3, 2.98 + tx, 1.99 + ty, 2 + tz, 0, 0, 20, cubeVAO, lightingShader);
//    book_color_4(0.2, 3, 3.15, 3.1 + tx, 2.035 + ty, 2 + tz, 0, 0, 20, cubeVAO, lightingShader);
//    book_color_4(1.48, 3, 0.2, 2.98 + tx, 1.99 + ty, 2.3 + tz, 0, 0, 20, cubeVAO, lightingShader);
//}
//void wall_shelf_color(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
//{
//    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
//    lightingShader.setMat4("model", model);
//    drawCube(cubeVAO, lightingShader, model, 0.964f, 0.89f, 0.819f);
//}
//
//void wall_shelf_1(float tx, float ty, float tz,unsigned int& cubeVAO, Shader& lightingShader)
//{
//    wall_shelf_color(8, 0.3, -5, 5 + tx, 2.3 + ty, 8.9 + tz, 0, 0, 0, cubeVAO, lightingShader);
//    wall_shelf_color(0.3, 8, -5, 5 + tx, 2.3 + ty, 8.9 + tz, 0, 0, 0, cubeVAO, lightingShader);
//    wall_shelf_color(0.3, 8, -5, 5.8 + tx, 2.3 + ty, 8.9 + tz, 0, 0, 0, cubeVAO, lightingShader);
//    wall_shelf_color(8.3, 0.3, -5, 5 + tx, 3.1 + ty, 8.9 + tz, 0, 0, 0, cubeVAO, lightingShader);
//}

void white_color2(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
{
    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
    lightingShader.setMat4("model", model);
   // drawCube(cubeVAO, lightingShader, model, 1.0f, 1.0f, 1.0f);
    drawCube(cubeVAO, lightingShader, model, 0.98f, 0.2667f, 0.298f);

}
void color_boat(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
{
    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
    lightingShader.setMat4("model", model);
    drawCube(cubeVAO, lightingShader, model, 0.16f, 0.10f, 0.06f);
}


//void dressing_table_color_1(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
//{
//    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
//    lightingShader.setMat4("model", model);
//    drawCube(cubeVAO, lightingShader, model, 0.494f, 0.207f, 0.133f);
//}
//void dressing_table_color_2(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
//{
//    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
//    lightingShader.setMat4("model", model);
//    drawCube(cubeVAO, lightingShader, model, 0.152f, 0.086f, 0.054f);
//}
void chocolate_color(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
{
    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
    lightingShader.setMat4("model", model);
    drawCube(cubeVAO, lightingShader, model, 0.3529f, 0.24313f, 0.24313f);
}
void chocolate_color2(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
{
    glm::mat4 model = model_Matrix(s_x, s_y, s_z, t_x, t_y, t_z, r_x, r_y, r_z);
    lightingShader.setMat4("model", model);
    drawCube(cubeVAO, lightingShader, model, 0.23529f, 0.14902f, 0.14902f);
}
void train_wheel(float sx, float sy, float sz, float tx, float ty, float tz, float rx, float ry, float rz,float r, float g,float b, Shader& ourShader,Wheel& wheel)
{
    ourShader.use();
    wheel.drawWheel(ourShader, model_Matrix(1*sx, 1*sy, 1*sz, 7+tx, 7+ty, 7+tz, 0+rx, 0+ry, 0+rz), r, g, b);
    wheel.drawWheel(ourShader, model_Matrix(1*sx, 1*sy, 1*sz, 7+tx, 7+ty, 7+tz, 0+rx, 0+ry, 90+rz), r, g, b);
    wheel.drawWheel(ourShader, model_Matrix(1*sx, 1*sy, 1*sz, 7+tx, 7+ty, 7+tz, 0+rx, 0+ry, 180+rz), r, g, b);
    wheel.drawWheel(ourShader, model_Matrix(1*sx, 1*sy, 1*sz, 7+tx, 7+ty, 7+tz, 0+rx, 0+ry, 270+rz), r, g, b);
    //wheel.drawWheel(ourShader, model_Matrix(1, 1, 1, 7, 7, 7, 0, 0, 90), 0.5, 0.5, 0.5);
    //wheel.drawWheel(ourShader, model_Matrix(1, 1, 1, 7, 7, 7, 0, 0, 180), 0.5, 0.5, 0.5);
    //wheel.drawWheel(ourShader, model_Matrix(1, 1, 1, 7, 7, 7, 0, 0, 270), 0.5, 0.5, 0.5);
}

void train_door_left(float sx, float sy, float sz, float tx, float ty, float tz, float rx, float ry, float rz, unsigned int& cubeVAO, Shader& lightingShader)
{
    light_red_color(3+1, 6, 0.2, -3+1 + tx, 2.56, 0+2.92, 0, 0, 0, cubeVAO, lightingShader);
    light_red_color(3+1, 3.5, 0.2, -3+1 + tx, 3.70, 0+2.92, 0, 0, 0, cubeVAO, lightingShader);
    light_red_color(0.7, -6, 0.2, -3+1 + tx, 3.70, 0+2.92, 0, 0, 0, cubeVAO, lightingShader);
    light_red_color(0.7+1, -6, 0.2, -3+1+0.23 + tx, 3.70, 0+2.92, 0, 0, 0, cubeVAO, lightingShader);

   /* white_color2(4, 6, 0.2, -3 + 1+0.5-0.1 + tx, 2.56, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
    white_color2(4, 3.5, 0.2, -3 + 1+0.5-0.1 + tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
    white_color2(0.7, -6, 0.2, -3 + 1+0.73 + tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
    white_color2(0.7+1, -6, 0.2, -3 + 1 + 0.23+0.27-0.1 + tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);*/

}
//void train_door_left_closed(float sx, float sy, float sz, float tx, float ty, float tz, float rx, float ry, float rz, unsigned int& cubeVAO, Shader& lightingShader)
//{
//    white_color2(3 + 1, 6, 0.2, -3 + 1 + tx, 2.56, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
//    white_color2(3 + 1, 3.5, 0.2, -3 + 1 + tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
//    white_color2(0.7, -6, 0.2, -3 + 1 + tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
//    white_color2(0.7 + 1, -6, 0.2, -3 + 1 + 0.23 + tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
//
//    /* white_color2(4, 6, 0.2, -3 + 1+0.5-0.1 + tx, 2.56, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
//     white_color2(4, 3.5, 0.2, -3 + 1+0.5-0.1 + tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
//     white_color2(0.7, -6, 0.2, -3 + 1+0.73 + tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
//     white_color2(0.7+1, -6, 0.2, -3 + 1 + 0.23+0.27-0.1 + tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);*/
//
//}
//void train_door_translate(float sx, float sy, float sz, float tx, float ty, float tz, float rx, float ry, float rz, unsigned int& cubeVAO, Shader& lightingShader)
//{
//    white_color2(3 + 1, 6, 0.2, -3 + 1 + tx, 2.56, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
//    white_color2(3 + 1, 3.5, 0.2, -3 + 1 + tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
//    white_color2(0.7, -6, 0.2, -3 + 1 + tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
//    white_color2(0.7 + 1, -6, 0.2, -3 + 1 + 0.23 + tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
//
//    white_color2(4, 6, 0.2, -3 + 1 + 0.5 - 0.1 + tx, 2.56, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
//    white_color2(4, 3.5, 0.2, -3 + 1 + 0.5 - 0.1 + tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
//    white_color2(0.7, -6, 0.2, -3 + 1 + 0.73 + tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
//    white_color2(0.7 + 1, -6, 0.2, -3 + 1 + 0.23 + 0.27 - 0.1 + tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
//
//}
//void train_door_right_opened(float sx, float sy, float sz, float tx, float ty, float tz, float rx, float ry, float rz, unsigned int& cubeVAO, Shader& lightingShader)
//{
//    /*white_color2(3 + 1, 6, 0.2, -3 + 1 - tx, 2.56, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
//    white_color2(3 + 1, 3.5, 0.2, -3 + 1 - tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
//    white_color2(0.7, -6, 0.2, -3 + 1 - tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
//    white_color2(0.7 + 1, -6, 0.2, -3 + 1 + 0.23 - tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);*/
//
//    white_color2(4, 6, 0.2, -3 + 1 + 0.5 - 0.1 + tx, 2.56, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
//    white_color2(4, 3.5, 0.2, -3 + 1 + 0.5 - 0.1 + tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
//    white_color2(0.7, -6, 0.2, -3 + 1 + 0.73 + tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
//    white_color2(0.7 + 1, -6, 0.2, -3 + 1 + 0.23 + 0.27 - 0.1 + tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
//
//}
void train_door_right(float sx, float sy, float sz, float tx, float ty, float tz, float rx, float ry, float rz, unsigned int& cubeVAO, Shader& lightingShader)
{
    /*white_color2(3 + 1, 6, 0.2, -3 + 1 - tx, 2.56, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
    white_color2(3 + 1, 3.5, 0.2, -3 + 1 - tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
    white_color2(0.7, -6, 0.2, -3 + 1 - tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
    white_color2(0.7 + 1, -6, 0.2, -3 + 1 + 0.23 - tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);*/

    light_red_color(4, 6, 0.2, -3 + 1 + 0.5 - 0.1 + tx, 2.56, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
    light_red_color(4, 3.5, 0.2, -3 + 1 + 0.5 - 0.1 + tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
    light_red_color(0.7, -6, 0.2, -3 + 1 + 0.73 +tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
    light_red_color(0.7 + 1, -6, 0.2, -3 + 1 + 0.23 + 0.27 - 0.1 + tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);

}

void train_door_left2(float sx, float sy, float sz, float tx, float ty, float tz, float rx, float ry, float rz, unsigned int& cubeVAO, Shader& lightingShader)
{
    light_red_color(4.3*sx, 6*sy, 0.2*sz, -3 + 1 + tx, 2.56+ty, 0 + 2.92+tz, 0, 0, 0, cubeVAO, lightingShader);
    light_red_color(4.3 * sx, 3.5 * sy, 0.2 * sz, -3 + 1 + tx, 3.70 + ty, 0 + 2.92 + tz, 0, 0, 0, cubeVAO, lightingShader);
    light_red_color(0.7 * sx, -6 * sy, 0.2 * sz, -3 + 1 + tx, 3.70 + ty, 0 + 2.92 + tz, 0, 0, 0, cubeVAO, lightingShader);
    light_red_color(1 * sx, -6 * sy, 0.2 * sz, -3 + 1 + 0.23 + tx, 3.70 + ty, 0 + 2.92 + tz, 0, 0, 0, cubeVAO, lightingShader);

    /* white_color2(4, 6, 0.2, -3 + 1+0.5-0.1 + tx, 2.56, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
     white_color2(4, 3.5, 0.2, -3 + 1+0.5-0.1 + tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
     white_color2(0.7, -6, 0.2, -3 + 1+0.73 + tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
     white_color2(0.7+1, -6, 0.2, -3 + 1 + 0.23+0.27-0.1 + tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);*/

}
void train_door_right2(float sx, float sy, float sz, float tx, float ty, float tz, float rx, float ry, float rz, unsigned int& cubeVAO, Shader& lightingShader)
{
    /*white_color2(3 + 1, 6, 0.2, -3 + 1 - tx, 2.56, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
    white_color2(3 + 1, 3.5, 0.2, -3 + 1 - tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
    white_color2(0.7, -6, 0.2, -3 + 1 - tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
    white_color2(0.7 + 1, -6, 0.2, -3 + 1 + 0.23 - tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);*/

    light_red_color(4.3*sx, 6*sy, 0.2*sz, -3 + 1 + 0.5 - 0.1 + tx - 0.02, 2.56+ty, 0 + 2.92+tz, 0, 0, 0, cubeVAO, lightingShader);
    light_red_color(4.3 * sx, 3.5 * sy, 0.2 * sz, -3 + 1 + 0.5 - 0.1 + tx - 0.02, 3.70 + ty, 0 + 2.92 + tz, 0, 0, 0, cubeVAO, lightingShader);
    light_red_color(1 * sx, -6 * sy, 0.2 * sz, -3 + 1 + 0.63 + tx - 0.02, 3.70 + ty, 0 + 2.92 + tz, 0, 0, 0, cubeVAO, lightingShader);
    light_red_color(0.9 * sx, -6 * sy, 0.2 * sz, -3 + 1 + 0.23 + 0.27 - 0.1 + tx-0.02, 3.70 + ty, 0 + 2.92 + tz, 0, 0, 0, cubeVAO, lightingShader);

}
void train_door_left3(float sx, float sy, float sz, float tx, float ty, float tz, float rx, float ry, float rz, unsigned int& cubeVAO, Shader& lightingShader)
{
    light_red_color(4.3 * sx, 6 * sy, 0.2 * sz, -3 + 1 + tx - 0.1, 2.56 + ty, 0 + 2.92 + tz, 0, 0, 0, cubeVAO, lightingShader);
    light_red_color(4.3 * sx, 3.5 * sy, 0.2 * sz, -3 + 1 + tx - 0.1, 3.70 + ty, 0 + 2.92 + tz, 0, 0, 0, cubeVAO, lightingShader);
    light_red_color(0.7 * sx, -6 * sy, 0.2 * sz, -3 + 1 + tx-0.1, 3.70 + ty, 0 + 2.92 + tz, 0, 0, 0, cubeVAO, lightingShader);
    light_red_color(1 * sx, -6 * sy, 0.2 * sz, -3 + 1 + 0.23 + tx , 3.70 + ty, 0 + 2.92 + tz, 0, 0, 0, cubeVAO, lightingShader);

    /* white_color2(4, 6, 0.2, -3 + 1+0.5-0.1 + tx, 2.56, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
     white_color2(4, 3.5, 0.2, -3 + 1+0.5-0.1 + tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
     white_color2(0.7, -6, 0.2, -3 + 1+0.73 + tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
     white_color2(0.7+1, -6, 0.2, -3 + 1 + 0.23+0.27-0.1 + tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);*/

}
void train_door_right3(float sx, float sy, float sz, float tx, float ty, float tz, float rx, float ry, float rz, unsigned int& cubeVAO, Shader& lightingShader)
{
    /*white_color2(3 + 1, 6, 0.2, -3 + 1 - tx, 2.56, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
    white_color2(3 + 1, 3.5, 0.2, -3 + 1 - tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
    white_color2(0.7, -6, 0.2, -3 + 1 - tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
    white_color2(0.7 + 1, -6, 0.2, -3 + 1 + 0.23 - tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);*/

    light_red_color(5.5 * sx, 6 * sy, 0.2 * sz, -3 + 1 + 0.5 - 0.1 + tx - 0.11, 2.56 + ty, 0 + 2.92 + tz, 0, 0, 0, cubeVAO, lightingShader);
    light_red_color(5.5 * sx, 3.5 * sy, 0.2 * sz, -3 + 1 + 0.5 - 0.1 + tx - 0.11, 3.70 + ty, 0 + 2.92 + tz, 0, 0, 0, cubeVAO, lightingShader);
    light_red_color(1.3 * sx, -6 * sy, 0.2 * sz, -3 + 1 + 0.63 + tx + 0.08, 3.70 + ty, 0 + 2.92 + tz, 0, 0, 0, cubeVAO, lightingShader);
    light_red_color(1.7 * sx, -6 * sy, 0.2 * sz, -3 + 1 + 0.23 + 0.27 - 0.1 + tx - 0.11, 3.70 + ty, 0 + 2.92 + tz, 0, 0, 0, cubeVAO, lightingShader);

}
void train_door_right4(float sx, float sy, float sz, float tx, float ty, float tz, float rx, float ry, float rz, unsigned int& cubeVAO, Shader& lightingShader)
{
    /*white_color2(3 + 1, 6, 0.2, -3 + 1 - tx, 2.56, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
    white_color2(3 + 1, 3.5, 0.2, -3 + 1 - tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
    white_color2(0.7, -6, 0.2, -3 + 1 - tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);
    white_color2(0.7 + 1, -6, 0.2, -3 + 1 + 0.23 - tx, 3.70, 0 + 2.92, 0, 0, 0, cubeVAO, lightingShader);*/

    light_red_color(4.3 * sx, 6 * sy, 0.2 * sz, -3 + 1 + 0.5 - 0.1 + tx - 0.02, 2.56 + ty, 0 + 2.92 + tz, 0, 0, 0, cubeVAO, lightingShader);
    light_red_color(4.3 * sx, 3.5 * sy, 0.2 * sz, -3 + 1 + 0.5 - 0.1 + tx - 0.02, 3.70 + ty, 0 + 2.92 + tz, 0, 0, 0, cubeVAO, lightingShader);
    light_red_color(1 * sx, -6 * sy, 0.2 * sz, -3 + 1 + 0.63 + tx - 0.02+0.1, 3.70 + ty, 0 + 2.92 + tz, 0, 0, 0, cubeVAO, lightingShader);
    light_red_color(0.9 * sx, -6 * sy, 0.2 * sz, -3 + 1 + 0.23 + 0.27 - 0.1 + tx - 0.02, 3.70 + ty, 0 + 2.92 + tz, 0, 0, 0, cubeVAO, lightingShader);

}
void train(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader,Wheel& wheel,Shader& ourShader)
{
   ourShader.use();
    for (int t = 0; t <= 6; t += 3)
    {
        for (int j = 0; j <= 2; j += 2)
        {
            
                //wheel.drawWheel(ourShader, model_Matrix(.9, .9, 0.2, 5 + j - t + t_x, 2.4, 1.98, 0, 0, 0 + i), 0.5, 0.5, 0.5);
              // train_wheel(.9, .9, 0.2, 5 + j - t + t_x, 2.4, 1.98, 0, 0, 0 , 0.5, 0.5, 0.5,ourShader,wheel);
                wheel.drawWheel(ourShader, model_Matrix(.9, .9, 0.2, 5 + j - t + t_x, 2.4, 1.98, 0, 0, 0+ r_z), 0.5, 0.5, 0.5);
                wheel.drawWheel(ourShader, model_Matrix(.9, .9, 0.2, 5 + j - t + t_x, 2.4, 1.98, 0, 0, 90 + r_z), .4, 0.4, 0.4);
                wheel.drawWheel(ourShader, model_Matrix(.9, .9, 0.2, 5 + j - t + t_x, 2.4, 1.98, 0, 0, 180 + r_z), 0.5, 0.5, 0.5);
                wheel.drawWheel(ourShader, model_Matrix(.9, .9, 0.2, 5 + j - t + t_x, 2.4, 1.98, 0, 0, 270 + r_z), 0.4, 0.4, 0.4);
                /*wheel.drawWheel(ourShader, model_Matrix(1 * sx, 1 * sy, 1 * sz, 7 + tx, 7 + ty, 7 + tz, 0 + rx, 0 + ry, 90 + rz), 0.5, 0.5, 0.5);
                wheel.drawWheel(ourShader, model_Matrix(1 * sx, 1 * sy, 1 * sz, 7 + tx, 7 + ty, 7 + tz, 0 + rx, 0 + ry, 180 + rz), 0.5, 0.5, 0.5);
                wheel.drawWheel(ourShader, model_Matrix(1 * sx, 1 * sy, 1 * sz, 7 + tx, 7 + ty, 7 + tz, 0 + rx, 0 + ry, 270 + rz), 0.5, 0.5, 0.5);*/
                //black_color(.9, .9, 0.2, 5 + j - t+ t_x, 2.4, 1.98, 0, 0, 0 + i+rotateAngle, cubeVAO, lightingShader);
               // black_color(.4, .4, 0.6, 5 + j - t + t_x, 2.4, 1.981, 0, 0, 0 + i+ rotateAngle, cubeVAO, lightingShader);
               // wheel.drawWheel(ourShader, model_Matrix(.4, .4, 0.6, 5 + j - t + t_x, 2.4, 1.981, 0, 0, 0 + i), 0.5, 0.5, 0.5);
                //train_wheel(.4, .4, 0.6, 5 + j - t + t_x, 2.4, 1.981, 0, 0, 0 , 0.5, 0.5, 0.5, ourShader, wheel);
                wheel.drawWheel(ourShader, model_Matrix(.4, .4, 0.6, 5 + j - t + t_x, 2.4, 1.979, 0, 0, 0 + r_z), 0.5, 0.5, 0.5);
                wheel.drawWheel(ourShader, model_Matrix(.4, .4, 0.6, 5 + j - t + t_x, 2.4, 1.979, 0, 0, 90 + r_z), 0.4, 0.4, 0.4);
                wheel.drawWheel(ourShader, model_Matrix(.4, .4, 0.6, 5 + j - t + t_x, 2.4, 1.979, 0, 0, 180 + r_z), 0.5, 0.5, 0.5);
                wheel.drawWheel(ourShader, model_Matrix(.4, .4, 0.6, 5 + j - t + t_x, 2.4, 1.979, 0, 0, 270 + r_z), 0.4, 0.4, 0.4);

                //black_color(.4, .4, 0.6, 5 + j - t + t_x, 2.4, 2.65, 0, 0, 0 + i+ rotateAngle, cubeVAO, lightingShader);
               // wheel.drawWheel(ourShader, model_Matrix(.4, .4, 0.6, 5 + j - t + t_x, 2.4, 2.65, 0, 0, 0 + i), 0.5, 0.5, 0.5);
                //train_wheel(.4, .4, 0.6, 5 + j - t + t_x, 2.4, 1.981, 0, 0, 0 , 0.5, 0.5, 0.5, ourShader, wheel);

                wheel.drawWheel(ourShader, model_Matrix(.4, .4, 0.6, 5 + j - t + t_x, 2.4, 2.66, 0, 0, 0 + r_z), 0.5, 0.5, 0.5);
                wheel.drawWheel(ourShader, model_Matrix(.4, .4, 0.6, 5 + j - t + t_x, 2.4, 2.66, 0, 0, 90 + r_z), 0.4, 0.4, 0.4);
                wheel.drawWheel(ourShader, model_Matrix(.4, .4, 0.6, 5 + j - t + t_x, 2.4, 2.66, 0, 0, 180 + r_z), 0.5, 0.5, 0.5);
                wheel.drawWheel(ourShader, model_Matrix(.4, .4, 0.6, 5 + j - t + t_x, 2.4, 2.66, 0, 0, 270 + r_z), 0.4, 0.4, 0.4);
           
               // wheel.drawWheel(ourShader, model_Matrix(.9, .9, 0.2, 5 + j - t + t_x, 2.4, 2.7, 0, 0, 0 + i), 0.5, 0.5, 0.5);
               // train_wheel(.9, .9, 0.2, 5 + j - t + t_x, 2.4, 2.7, 0, 0, 0 , 0.5, 0.5, 0.5, ourShader, wheel);
                wheel.drawWheel(ourShader, model_Matrix(.9, .9, 0.2, 5 + j - t + t_x, 2.4, 2.7, 0, 0, 0 + r_z), 0.5, 0.5, 0.5);
                wheel.drawWheel(ourShader, model_Matrix(.9, .9, 0.2, 5 + j - t + t_x, 2.4, 2.7, 0, 0, 90 + r_z), 0.4, 0.4, 0.4);
                wheel.drawWheel(ourShader, model_Matrix(.9, .9, 0.2, 5 + j - t + t_x, 2.4, 2.7, 0, 0, 180 + r_z), 0.5, 0.5, 0.5);
                wheel.drawWheel(ourShader, model_Matrix(.9, .9, 0.2, 5 + j - t + t_x, 2.4, 2.7, 0, 0, 270 + r_z), 0.4, 0.4, 0.4);
                //black_color(.9, .9, 0.2, 5 + j - t + t_x, 2.4, 2.7, 0, 0, 0 + i+ rotateAngle, cubeVAO, lightingShader);
            

        }
        black_color(25, 1.2, 0.3, 4.8 - t + t_x, 2.45, 1.95, 0, 0, 0, cubeVAO, lightingShader);
        black_color(25, 1.2, 0.3, 4.8 - t + t_x, 2.45, 2.72, 0, 0, 0, cubeVAO, lightingShader);

        white_color2(25, 0.3, -11, 4.8 - t + t_x, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);

        white_color2(4, 15, 0.3, 4.8 - t + t_x, 2.55, 1.8, 0, 0, 0, cubeVAO, lightingShader);
        white_color2(4, 15, 0.3, 5.6 - t + t_x, 2.55, 1.8, 0, 0, 0, cubeVAO, lightingShader);
        white_color2(6, 15, 0.3, 6.4 - t + t_x, 2.55, 1.8, 0, 0, 0, cubeVAO, lightingShader);

        white_color2(8, 7, 0.3, 4.8 - t + t_x, 2.55, 1.8, 0, 0, 0, cubeVAO, lightingShader);
        white_color2(8, 7, 0.3, 5.6 - t + t_x, 2.55, 1.8, 0, 0, 0, cubeVAO, lightingShader);

        white_color2(8, -4, 0.3, 4.8 - t + t_x, 4.05, 1.8, 0, 0, 0, cubeVAO, lightingShader);
        white_color2(8, -4, 0.3, 5.6 - t + t_x, 4.05, 1.8, 0, 0, 0, cubeVAO, lightingShader);

        //// white_color2(25, 15, 0.3, 4.8 - t, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);

        white_color2(4, 15, 0.3, 4.8 - t + t_x, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);
        white_color2(4, 15, 0.3, 5.6 - t + t_x, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);
        white_color2(6, 15, 0.3, 6.4 - t + t_x, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);

        white_color2(8, 7, 0.3, 4.8 - t + t_x, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);
        white_color2(8, 7, 0.3, 5.6 - t + t_x, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);

        white_color2(8, -4, 0.3, 4.8 - t + t_x, 4.05, 2.9, 0, 0, 0, cubeVAO, lightingShader);
        white_color2(8, -4, 0.3, 5.6 - t + t_x, 4.05, 2.9, 0, 0, 0, cubeVAO, lightingShader);


        // //white_color2(25, 0.3, -3, 4.8 - t, 4.55, 2.65, 0, 0, 0, cubeVAO, lightingShader);
        white_color2(25, 0.3, -4, 4.8 - t + t_x, 4.03, 2.92, 30, 0, 0, cubeVAO, lightingShader);
        white_color2(25, 0.3, -4, 4.8 - t + t_x, 4.05, 1.8, -210, 0, 0, cubeVAO, lightingShader);
        white_color2(25, 0.3, -4.5, 4.8 - t + t_x, 4.22, 2.59, 0, 0, 0, cubeVAO, lightingShader);



        if (t == 0)
        {
           white_color2(10, 0.3, -11, 4 - t + 3 + t_x, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);

       // white_color2(10, 15, 0.3, 4 - t + 3, 2.55, 1.8, 0, 0, 0, cubeVAO, lightingShader);
            white_color2(2, 15, 0.3, 4 - t + 3 + t_x, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);

           white_color2(2, 15, 0.3, 4.8 - t + 3 + t_x, 2.55, 1.8, 0, 0, 0, cubeVAO, lightingShader);
            white_color2(2, 15, 0.3, 4.8 - t + 3 + t_x, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);



           // white_color2(25, 0.3, -3, 4.8 - t, 4.55, 2.65, 0, 0, 0, cubeVAO, lightingShader);
            white_color2(10, 0.3, -4, 4 - t + 3 + t_x, 4.03, 2.92, 30, 0, 0, cubeVAO, lightingShader);
            white_color2(10, 0.3, -4, 4 - t + 3 + t_x, 4.05, 1.8, -210, 0, 0, cubeVAO, lightingShader);
            white_color2(10, 0.3, -4.5, 4 - t + 3 + t_x, 4.22, 2.59, 0, 0, 0, cubeVAO, lightingShader);

            //train front1
            white_color2(0.1, 8, -11, 5 - t + 3 + t_x, 2.55, 2.92, 0, 0, 0, cubeVAO, lightingShader);
            white_color2(0.1, -2, -11, 5 - t + 3 + t_x, 4.03, 2.92, 0, 0, 0, cubeVAO, lightingShader);
            white_color2(0.1, -4, -4.6, 5 - t + 3 + t_x, 4.25, 2.60, 0, 0, 0, cubeVAO, lightingShader);

            white_color2(0.1, 14, -1.5, 5 - t + 3 + t_x, 2.55, 1.95, 0, 0, 0, cubeVAO, lightingShader);
            white_color2(0.1, 14, -1.5, 5 - t + 3 + t_x, 2.55, 2.93, 0, 0, 0, cubeVAO, lightingShader);

            white_color2(0.1, -8, -3, 5 - t + 3 + t_x, 4.03, 2.5, 0, 0, 0, cubeVAO, lightingShader);

            white_color2(0.1, 15, -11, 4 - t + 3 + t_x, 2.55, 2.92, 0, 0, 0, cubeVAO, lightingShader);

           
                //wheel.drawWheel(ourShader, model_Matrix(0.5, 0.1, 0.1, 5.01 - t + 3 + t_x, 2.83, 2.0, 0, 90, 0 + i));
               // train_wheel(0.5, 0.1, 0.1, 5.01 - t + 3 + t_x, 2.83, 2.0, 0, 90, 0, 0.5, 0.5, 0.5, ourShader, wheel);
                wheel.drawWheel(ourShader, model_Matrix(0.4, 0.4, 0.4, 5.01 - t + 3 + t_x-0.03, 2.83, 2.0, 0, 90, 0), 0.5, 0.5, 0.5);
                wheel.drawWheel(ourShader, model_Matrix(0.4, 0.4, 0.4, 5.01 - t + 3 + t_x - 0.03, 2.83, 2.0, 0, 90, 90), 0.5, 0.5, 0.5);
                wheel.drawWheel(ourShader, model_Matrix(0.4, 0.4, 0.4, 5.01 - t + 3 + t_x - 0.03, 2.83, 2.0, 0, 90, 180), 0.5, 0.5, 0.5);
                wheel.drawWheel(ourShader, model_Matrix(0.4, 0.4, 0.4, 5.01 - t + 3 + t_x - 0.03, 2.83, 2.0, 0, 90, 270), 0.5, 0.5, 0.5);
           
                //wheel.drawWheel(ourShader, model_Matrix(0.5, 0.1, 0.1, 5.01 - t + 3 + t_x, 2.83, 2.75, 0, 90, 0 + i));
                //train_wheel(0.5, 0.1, 0.1, 5.01 - t + 3 + t_x, 2.83, 2.75, 0, 90, 0 , 0.5, 0.5, 0.5, ourShader, wheel);
                wheel.drawWheel(ourShader, model_Matrix(0.4, 0.4, 0.4, 5.01 - t + 3 + t_x - 0.03, 2.83, 2.75, 0, 90, 0), 0.5, 0.5, 0.5);
                wheel.drawWheel(ourShader, model_Matrix(0.4, 0.4, 0.4, 5.01 - t + 3 + t_x - 0.03, 2.83, 2.75, 0, 90, 90), 0.5, 0.5, 0.5);
                wheel.drawWheel(ourShader, model_Matrix(0.4, 0.4, 0.4, 5.01 - t + 3 + t_x - 0.03, 2.83, 2.75, 0, 90, 180), 0.5, 0.5, 0.5);
                wheel.drawWheel(ourShader, model_Matrix(0.4, 0.4, 0.4, 5.01 - t + 3 + t_x - 0.03, 2.83, 2.75, 0, 90, 270), 0.5, 0.5, 0.5);
               /* white_color(1, 0.1, .1, 5.01 - t + 3 + t_x, 2.83, 2.0, 0, 90, 0 + i, cubeVAO, lightingShader);
                white_color(1, 0.1, .1, 5.01 - t + 3 + t_x, 2.83, 2.75, 0, 90, 0 + i, cubeVAO, lightingShader);*/
          
            /* for (int i = 0; i < 360; i++)
             {
                 black_color(.9, .9, 0.2, 5 - t+3, 2.4, 1.98, 0, 0, 0 + i, cubeVAO, lightingShader);
                 black_color(.4, .4, 0.6, 5  - t+3, 2.4, 1.981, 0, 0, 0 + i, cubeVAO, lightingShader);


                 black_color(.4, .4, 0.6, 5  - t+3, 2.4, 2.65, 0, 0, 0 + i, cubeVAO, lightingShader);
                 black_color(.9, .9, 0.2, 5  - t+3, 2.4, 2.7, 0, 0, 0 + i, cubeVAO, lightingShader);
             }*/

        }
        else if (t == 3)
        {
            white_color2(10, 0.3, -11, 4 - t + 3 + t_x, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);

            white_color2(2, 15, 0.3, 4 - t + 3 + t_x, 2.55, 1.8, 0, 0, 0, cubeVAO, lightingShader);
            white_color2(2, 15, 0.3, 4 - t + 3 + t_x, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);

            white_color2(2, 15, 0.3, 4.8 - t + 3 + t_x, 2.55, 1.8, 0, 0, 0, cubeVAO, lightingShader);
            white_color2(2, 15, 0.3, 4.8 - t + 3 + t_x, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);

           // white_color2(25, 0.3, -3, 4.8 - t, 4.55, 2.65, 0, 0, 0, cubeVAO, lightingShader);
            white_color2(10, 0.3, -4, 4 - t + 3 + t_x, 4.03, 2.92, 30, 0, 0, cubeVAO, lightingShader);
            white_color2(10, 0.3, -4, 4 - t + 3 + t_x, 4.05, 1.8, -210, 0, 0, cubeVAO, lightingShader);
            white_color2(10, 0.3, -4.5, 4 - t + 3 + t_x, 4.22, 2.59, 0, 0, 0, cubeVAO, lightingShader);

            white_color2(0.1, 15, -2, 4 - t + 3 + t_x, 2.55, 2.03, 0, 0, 0, cubeVAO, lightingShader);
            white_color2(0.1, 15, -2, 4 - t + 3 + t_x, 2.55, 2.92, 0, 0, 0, cubeVAO, lightingShader);
        }
        else if (t == 6)
        {
            white_color2(10, 0.3, -11, 4 - t + 3 + t_x, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);

            white_color2(2, 15, 0.3, 4 - t + 3 + t_x, 2.55, 1.8, 0, 0, 0, cubeVAO, lightingShader);
            white_color2(2, 15, 0.3, 4 - t + 3 + t_x, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);

            white_color2(2, 15, 0.3, 4.8 - t + 3 + t_x, 2.55, 1.8, 0, 0, 0, cubeVAO, lightingShader);
            white_color2(2, 15, 0.3, 4.8 - t + 3 + t_x, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);

            //white_color2(25, 0.3, -3, 4.8 - t, 4.55, 2.65, 0, 0, 0, cubeVAO, lightingShader);
            white_color2(10, 0.3, -4, 4 - t + 3 + t_x, 4.03, 2.92, 30, 0, 0, cubeVAO, lightingShader);
            white_color2(10, 0.3, -4, 4 - t + 3 + t_x, 4.05, 1.8, -210, 0, 0, cubeVAO, lightingShader);
            white_color2(10, 0.3, -4.5, 4 - t + 3 + t_x, 4.22, 2.59, 0, 0, 0, cubeVAO, lightingShader);

            white_color2(0.1, 15, -2, 4 - t + 3 + t_x, 2.55, 2.03, 0, 0, 0, cubeVAO, lightingShader);
            white_color2(0.1, 15, -2, 4 - t + 3 + t_x, 2.55, 2.92, 0, 0, 0, cubeVAO, lightingShader);

            //  white_color2(0.1, -15, -11, 1.8 - t + 3, 4, 2.9, 0, 0, 0, cubeVAO, lightingShader);


              ////train front 2
            white_color2(0.1, 8, -11, 0.8 - t + 3 + t_x, 2.55, 2.92, 0, 0, 0, cubeVAO, lightingShader);
            white_color2(0.1, -2, -11, 0.8 - t + 3 + t_x, 4.03, 2.92, 0, 0, 0, cubeVAO, lightingShader);
            white_color2(0.1, -4, -4.6, 0.8 - t + 3 + t_x, 4.25, 2.60, 0, 0, 0, cubeVAO, lightingShader);

            white_color2(0.1, 14, -1.5, 0.8 - t + 3 + t_x, 2.55, 1.95, 0, 0, 0, cubeVAO, lightingShader);
            white_color2(0.1, 14, -1.5, 0.8 - t + 3 + t_x, 2.55, 2.93, 0, 0, 0, cubeVAO, lightingShader);

            white_color2(0.1, -8, -3, 0.8 - t + 3 + t_x, 4.03, 2.5, 0, 0, 0, cubeVAO, lightingShader);

            white_color2(0.1, 15, -11, 1.8 - t + 3 + t_x, 2.55, 2.92, 0, 0, 0, cubeVAO, lightingShader);

            white_color2(10, 0.3, -4, 0.8 - t + 3 + t_x, 4.03, 2.92, 30, 0, 0, cubeVAO, lightingShader);
            white_color2(10, 0.3, -4, 0.8 - t + 3 + t_x, 4.05, 1.8, -210, 0, 0, cubeVAO, lightingShader);
            white_color2(10, 0.3, -4.5, 0.8 - t + 3 + t_x, 4.22, 2.59, 0, 0, 0, cubeVAO, lightingShader);

            white_color2(10, 0.3, -11, 0.8 - t + 3 + t_x, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);

            white_color2(10, 15, 0.3, 0.8 - t + 3 + t_x, 2.55, 1.8, 0, 0, 0, cubeVAO, lightingShader);
            white_color2(2, 15, 0.3, 0.8 - t + 3 + t_x, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);

            white_color2(2, 15, 0.3, 1.8 - t + 3 + t_x, 2.55, 1.8, 0, 0, 0, cubeVAO, lightingShader);
            white_color2(2, 15, 0.3, 1.8 - t + 3 + t_x, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);


            //wheel.drawWheel(ourShader, model_Matrix(0.5, 0.1, .1, 0.79 - t + 3 + t_x, 2.83, 2.0, 0, 90, 0 + i));
           // train_wheel(0.5, 0.1, .1, 0.79 - t + 3 + t_x, 2.83, 2.0, 0, 90, 0, 0.5, 0.5, 0.5, ourShader, wheel);
            wheel.drawWheel(ourShader, model_Matrix(0.4, 0.4, .4, 0.79 - t + 3 + t_x, 2.83, 2.0, 0, 90, 0), 0.5, 0.5, 0.5);
            wheel.drawWheel(ourShader, model_Matrix(0.4, 0.4, .4, 0.79 - t + 3 + t_x, 2.83, 2.0, 0, 90, 90), 0.5, 0.5, 0.5);
            wheel.drawWheel(ourShader, model_Matrix(0.4, 0.4, .4, 0.79 - t + 3 + t_x, 2.83, 2.0, 0, 90, 180), 0.5, 0.5, 0.5);
            wheel.drawWheel(ourShader, model_Matrix(0.4, 0.4, .4, 0.79 - t + 3 + t_x, 2.83, 2.0, 0, 90, 270), 0.5, 0.5, 0.5);
         
            //wheel.drawWheel(ourShader, model_Matrix(0.5, 0.1, .1, 0.79 - t + 3 + t_x, 2.83, 2.75, 0, 90, 0 + i));
            //train_wheel(0.5, 0.1, .1, 0.79 - t + 3 + t_x, 2.83, 2.75, 0, 90, 0, 0.5, 0.5, 0.5, ourShader, wheel);
            wheel.drawWheel(ourShader, model_Matrix(0.4, 0.4, .4, 0.79 - t + 3 + t_x, 2.83, 2.75, 0, 90, 0), 0.5, 0.5, 0.5);
            wheel.drawWheel(ourShader, model_Matrix(0.4, 0.4, .4, 0.79 - t + 3 + t_x, 2.83, 2.75, 0, 90, 90), 0.5, 0.5, 0.5);
            wheel.drawWheel(ourShader, model_Matrix(0.4, 0.4, .4, 0.79 - t + 3 + t_x, 2.83, 2.75, 0, 90, 180), 0.5, 0.5, 0.5);
            wheel.drawWheel(ourShader, model_Matrix(0.4, 0.4, .4, 0.79 - t + 3 + t_x, 2.83, 2.75, 0, 90, 270), 0.5, 0.5, 0.5);
            //white_color(1, 0.1, .1, 0.79 - t + 3 + t_x, 2.83, 2.0, 0, 90, 0 + i, cubeVAO, lightingShader);

            //  white_color(1, 0.1, .1, 0.79 - t + 3 + t_x, 2.83, 2.75, 0, 90, 0 + i, cubeVAO, lightingShader);


        }

    }
}

void overBridge(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
{
    //over bridge
    //low handle 1
    wall_color(23, 0.5, 0.5, 8.5 + 0.5, 2.4, -0.5 + t_z, 0, 0, 45, cubeVAO, lightingShader);
    wall_color(23, 0.5, 0.5, 8.5 + 0.5, 2.4, -2 + t_z, 0, 0, 45, cubeVAO, lightingShader);

    //upper handle 1
    wall_color(22, 0.5, 0.5, 8.5 + 0.5, 3.4, -0.5 + t_z, 0, 0, 45, cubeVAO, lightingShader);
    wall_color(22, 0.5, 0.5, 8.5 + 0.5, 3.4, -2 + t_z, 0, 0, 45, cubeVAO, lightingShader);
    //stair pillar 1
    wall_color(0.5, 12, 0.5, 8.5 + 0.5, 2.4, -2 + t_z, 0, 0, 0, cubeVAO, lightingShader);
    wall_color(0.5, 12, 0.5, 8.5 + 0.5, 2.4, -0.5 + t_z, 0, 0, 0, cubeVAO, lightingShader);

    //stair1
    wall_color(3, 1, -15, 8.4 + 0.5, 2.4, -0.47 + t_z, 0, 0, 0, cubeVAO, lightingShader);
    wall_color(3, 1, -15, 8.6 + 0.5, 2.6, -0.47 + t_z, 0, 0, 0, cubeVAO, lightingShader);
    wall_color(3, 1, -15, 8.8 + 0.5, 2.8, -0.47 + t_z, 0, 0, 0, cubeVAO, lightingShader);
    wall_color(3, 1, -15, 9.0 + 0.5, 3.0, -0.47 + t_z, 0, 0, 0, cubeVAO, lightingShader);
    wall_color(3, 1, -15, 9.2 + 0.5, 3.2, -0.47 + t_z, 0, 0, 0, cubeVAO, lightingShader);
    wall_color(3, 1, -15, 9.4 + 0.5, 3.4, -0.47 + t_z, 0, 0, 0, cubeVAO, lightingShader);
    wall_color(3, 1, -15, 9.6 + 0.5, 3.6, -0.47 + t_z, 0, 0, 0, cubeVAO, lightingShader);
    wall_color(3, 1, -15, 9.8 + 0.5, 3.8, -0.47 + t_z, 0, 0, 0, cubeVAO, lightingShader);
    wall_color(12, 1, -15, 10.0 + 0.5, 4.0, -0.47 + t_z, 0, 0, 0, cubeVAO, lightingShader);



    //stair pillar 2
    wall_color(0.5, 10, 0.5, 10.0 + 0.5, 4.0, -2 + t_z, 0, 0, 0, cubeVAO, lightingShader);
    wall_color(0.5, 10, 0.5, 10.0 + 0.5, 4.0, -0.5 + t_z, 0, 0, 0, cubeVAO, lightingShader);

    wall_color(0.5, 10, 0.5, 11.2 + 0.5, 4.0, -2 + t_z, 0, 0, 0, cubeVAO, lightingShader);
    wall_color(0.5, 10, 0.5, 11.2 + 0.5, 4.0, -0.5 + t_z, 0, 0, 0, cubeVAO, lightingShader);


    wall_color(1, 17, 1, 10.0 + 0.5, 2.4, -2 + t_z, 0, 0, 0, cubeVAO, lightingShader);
    wall_color(1, 17, 1, 10.0 + 0.5, 2.4, -0.5 + t_z, 0, 0, 0, cubeVAO, lightingShader);

    wall_color(1, 17, 1, 11.2 + 0.5, 2.4, -2 + t_z, 0, 0, 0, cubeVAO, lightingShader);
    wall_color(1, 17, 1, 11.2 + 0.5, 2.4, -0.5 + t_z, 0, 0, 0, cubeVAO, lightingShader);

    //middle handle
    wall_color(12, 0.5, 0.5, 10.54, 4.9, -2 + t_z, 0, 0, 0, cubeVAO, lightingShader);
    wall_color(12, 0.5, 0.5, 10.54, 4.9, -0.5 + t_z, 0, 0, 0, cubeVAO, lightingShader);




    //low handle 2
    wall_color(25, 0.5, 0.5, 11.2 + 0.5, 4.0, -0.5 + t_z, 0, 0, 45, cubeVAO, lightingShader);
    wall_color(25, 0.5, 0.5, 11.2 + 0.5, 4.0, -2 + t_z, 0, 0, 45, cubeVAO, lightingShader);



    //stair2
    wall_color(3, 1, -15, 11.1 + 0.5, 4.0, -0.47 + t_z, 0, 0, 0, cubeVAO, lightingShader);
    wall_color(3, 1, -15, 11.3 + 0.5, 4.2, -0.47 + t_z, 0, 0, 0, cubeVAO, lightingShader);
    wall_color(3, 1, -15, 11.5 + 0.5, 4.4, -0.47 + t_z, 0, 0, 0, cubeVAO, lightingShader);
    wall_color(3, 1, -15, 11.7 + 0.5, 4.6, -0.47 + t_z, 0, 0, 0, cubeVAO, lightingShader);
    wall_color(3, 1, -15, 11.9 + 0.5, 4.8, -0.47 + t_z, 0, 0, 0, cubeVAO, lightingShader);
    wall_color(3, 1, -15, 12.1 + 0.5, 5.0, -0.47 + t_z, 0, 0, 0, cubeVAO, lightingShader);
    wall_color(3, 1, -15, 12.3 + 0.5, 5.2, -0.47 + t_z, 0, 0, 0, cubeVAO, lightingShader);
    wall_color(3, 1, -15, 12.5 + 0.5, 5.4, -0.47 + t_z, 0, 0, 0, cubeVAO, lightingShader);
    wall_color(3, 1, -15, 12.7 + 0.5, 5.6, -0.47 + t_z, 0, 0, 0, cubeVAO, lightingShader);

    //upper handle 2
    wall_color(25, 0.5, 0.5, 11.7, 4.9, -0.5 + t_z, 0, 0, 45, cubeVAO, lightingShader);
    wall_color(25, 0.5, 0.5, 11.7, 4.9, -2 + t_z, 0, 0, 45, cubeVAO, lightingShader);

    wall_color(1, 60, 1, 12.9 + 0.5, 2.4, -2 + t_z, 0, 0, 0, cubeVAO, lightingShader);
    wall_color(1, 60, 1, 12.9 + 0.5, 2.4, -0.5 + t_z, 0, 0, 0, cubeVAO, lightingShader);

    wall_color(1, 60, 1, 14.2 + 0.5, 2.4, -2 + t_z, 0, 0, 0, cubeVAO, lightingShader);
    wall_color(1, 60, 1, 14.2 + 0.5, 2.4, -0.5 + t_z, 0, 0, 0, cubeVAO, lightingShader);

    //top handle 
    wall_color(0.5, 9, 0.5, 12.9 + 0.5, 5.8, -2 + t_z, 0, 0, 0, cubeVAO, lightingShader);
    wall_color(0.5, 9, 0.5, 12.9 + 0.5, 5.8, -0.5 + t_z, 0, 0, 0, cubeVAO, lightingShader);

   
}

void bench(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
{
    white_color(0.5, 5, 0.5, -1.5+t_x, 2.4, -1.2, -10, 0, 0, cubeVAO, lightingShader);
    white_color(0.5, 5, 0.5, 1.5 + t_x, 2.4, -1.2, -10, 0, 0, cubeVAO, lightingShader);

    white_color(0.5, 5, 0.5, 0 + t_x, 2.4, -1.2, -10, 0, 0, cubeVAO, lightingShader);
    white_color(0.5, 5, 0.5, 0 + t_x, 2.4, -1.8, 10, 0, 0, cubeVAO, lightingShader);

    white_color(0.5, 5, 0.5, -1.5 + t_x, 2.4, -1.8, 10, 0, 0, cubeVAO, lightingShader);
    white_color(0.5, 5, 0.5, 1.5 + t_x, 2.4, -1.8, 10, 0, 0, cubeVAO, lightingShader);

    wall_color(32, 0.5, -5, -1.6 + t_x, 2.9, -1.2, -5, 0, 0, cubeVAO, lightingShader);
    wall_color(32, 0.5, -5, -1.6 + t_x, 2.9, -1.7, 80, 0, 0, cubeVAO, lightingShader);
}

void bench_at_counter(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
{
    white_color(0.5, 4, 0.5, -3.1+t_x, 2.4, 5.5, 0, 0, 10, cubeVAO, lightingShader);
    white_color(0.5, 4, 0.5, -3.5 + t_x, 2.4, 5.5, 0, 0, -10, cubeVAO, lightingShader);

    white_color(0.5, 4, 0.5, -3.1 + t_x, 2.4, 4, 0, 0, 10, cubeVAO, lightingShader);
    white_color(0.5, 4, 0.5, -3.5 + t_x, 2.4, 4, 0, 0, -10, cubeVAO, lightingShader);

    yellow_color(5, 0.5, -16.5, -3.5 + t_x, 2.75, 5.6, 0, 0, 5, cubeVAO, lightingShader);
    yellow_color(5, 0.5, -16.5, -3.45 + t_x, 2.75, 5.6, 0, 0, 100, cubeVAO, lightingShader);
}

void wall_strip(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
{
    white_color(25 * s_x, 5 * s_y, 0.1 * s_z, -2.8 + t_x, 1+t_y, -5.8+t_z, 0+r_x, 0+r_y, 0+r_z, cubeVAO, lightingShader);
    white_color(25.5 * s_x, 1 * s_y, 1 * s_z, -2.8 + t_x, 0.88 + t_y, -5.85 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);

    black_color(25 * s_x, 0.5 * s_y, 0.2 * s_z, -2.8 + t_x, 0.95 + t_y, -5.8 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    black_color(25 * s_x, 0.5 * s_y, 0.2 * s_z, -2.8 + t_x, 1.5 + t_y, -5.8 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    black_color(0.5 * s_x, -5 * s_y, 0.2 * s_z, -2.8 + t_x, 1.5 + t_y, -5.8 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);

   
}

void wall_strip_black_front(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
{
    black_color(0.5 * s_x, -6 * s_y, 0.2 * s_z, -0.3 + t_x, 1.55 + t_y, -5.8 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);

    black_color(0.5 * s_x, -6 * s_y, 0.2 * s_z, -0.8 + t_x, 1.55 + t_y, -5.8 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    black_color(0.5 * s_x, -6 * s_y, 0.2 * s_z, -1.3 + t_x, 1.55 + t_y, -5.8 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    black_color(0.5 * s_x, -6 * s_y, 0.2 * s_z, -1.8 + t_x, 1.55 + t_y, -5.8 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    black_color(0.5 * s_x, -6 * s_y, 0.2 * s_z, -2.3 + t_x, 1.55 + t_y, -5.8 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
}
void wall_strip_black_right(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
{
    black_color(0.2 * s_x, -6 * s_y, 0.5 * s_z, -0.0 + t_x, 1.55 + t_y, -6.5 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    black_color(0.2 * s_x, -6 * s_y, 0.5 * s_z, -0.0 + t_x, 1.55 + t_y, -7 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    black_color(0.2 * s_x, -6 * s_y, 0.5 * s_z, -0.0 + t_x, 1.55 + t_y, -7.5 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    black_color(0.2 * s_x, -6 * s_y, 0.5 * s_z, -0.0 + t_x, 1.55 + t_y, -8 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    black_color(0.2 * s_x, -6 * s_y, 0.5 * s_z, -0.0 + t_x, 1.55 + t_y, -8.45 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);

    /*black_color(0.5 * s_x, -6 * s_y, 0.2 * s_z, -0.8 + t_x, 1.55 + t_y, -5.8 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    black_color(0.5 * s_x, -6 * s_y, 0.2 * s_z, -1.3 + t_x, 1.55 + t_y, -5.8 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    black_color(0.5 * s_x, -6 * s_y, 0.2 * s_z, -1.8 + t_x, 1.55 + t_y, -5.8 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    black_color(0.5 * s_x, -6 * s_y, 0.2 * s_z, -2.3 + t_x, 1.55 + t_y, -5.8 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);*/
}

void building_1(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
{
   // wall_color(30*s_x, 60*s_y, 30*s_z, -3+t_x, 0.01+t_y, -8.8+t_z, 0+r_x, 0+r_y, 0+r_z, cubeVAO, lightingShader);

    wall_strip(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 0 + t_y, 0 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    wall_strip_black_front(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 0 + t_y, 0 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);

    wall_strip(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 2 + t_y, 0 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    wall_strip_black_front(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 2 + t_y, 0 + t_z, 0 + r_x, 0 + r_y , 0 + r_z, cubeVAO, lightingShader);

    wall_strip(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 4 + t_y, 0 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    wall_strip_black_front(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 4 + t_y, 0 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);


    wall_strip(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 0 + t_y, -3.01 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    wall_strip_black_front(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 0 + t_y, -3.011 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);

    wall_strip(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 2 + t_y, -3.01 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    wall_strip_black_front(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 2 + t_y, -3.011 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);

    wall_strip(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 4 + t_y, -3.01 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    wall_strip_black_front(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 4 + t_y, -3.011 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);



    wall_strip(1 * s_x, 1 * s_y, 1 * s_z, 2.8 + t_x, 0 + t_y, -0.14 + t_z, 0 + r_x, 90 + r_y, 0 + r_z, cubeVAO, lightingShader);
    wall_strip_black_right(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 0 + t_y, 0 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);

    wall_strip(1 * s_x, 1 * s_y, 1 * s_z, 2.8 + t_x, 2 + t_y, -0.14 + t_z, 0 + r_x, 90 + r_y, 0 + r_z, cubeVAO, lightingShader);
    wall_strip_black_right(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 2 + t_y, 0 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);

    wall_strip(1 * s_x, 1 * s_y, 1 * s_z, 2.8 + t_x, 4 + t_y, -0.14 + t_z, 0 + r_x, 90 + r_y, 0 + r_z, cubeVAO, lightingShader);
    wall_strip_black_right(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 4 + t_y, 0 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
}

void building_2(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
{
   // green_color(30 * s_x, 60 * s_y, 30 * s_z, -3 + t_x, 0.01 + t_y, -8.8 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);

    wall_strip(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 0 + t_y, 0 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    wall_strip_black_front(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 0 + t_y, 0 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);

    wall_strip(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 2 + t_y, 0 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    wall_strip_black_front(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 2 + t_y, 0 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);

    wall_strip(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 4 + t_y, 0 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    wall_strip_black_front(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 4 + t_y, 0 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);


    wall_strip(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 0 + t_y, -3.01 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    wall_strip_black_front(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 0 + t_y, -3.011 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);

    wall_strip(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 2 + t_y, -3.01 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    wall_strip_black_front(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 2 + t_y, -3.011 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);

    wall_strip(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 4 + t_y, -3.01 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    wall_strip_black_front(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 4 + t_y, -3.011 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);



    wall_strip(1 * s_x, 1 * s_y, 1 * s_z, 2.8 + t_x, 0 + t_y, -0.14 + t_z, 0 + r_x, 90 + r_y, 0 + r_z, cubeVAO, lightingShader);
    wall_strip_black_right(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 0 + t_y, 0 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);

    wall_strip(1 * s_x, 1 * s_y, 1 * s_z, 2.8 + t_x, 2 + t_y, -0.14 + t_z, 0 + r_x, 90 + r_y, 0 + r_z, cubeVAO, lightingShader);
    wall_strip_black_right(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 2 + t_y, 0 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);

    wall_strip(1 * s_x, 1 * s_y, 1 * s_z, 2.8 + t_x, 4 + t_y, -0.14 + t_z, 0 + r_x, 90 + r_y, 0 + r_z, cubeVAO, lightingShader);
    wall_strip_black_right(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 4 + t_y, 0 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
}

void building_3(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z, unsigned int& cubeVAO, Shader& lightingShader)
{
    //yellow_color(30 * s_x, 60 * s_y, 30 * s_z, -3 + t_x, 0.01 + t_y, -8.8 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);

    wall_strip(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 0 + t_y, 0 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    wall_strip_black_front(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 0 + t_y, 0 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);

    wall_strip(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 2 + t_y, 0 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    wall_strip_black_front(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 2 + t_y, 0 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);

    wall_strip(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 4 + t_y, 0 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    wall_strip_black_front(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 4 + t_y, 0 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);


    wall_strip(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 0 + t_y, -3.01 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    wall_strip_black_front(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 0 + t_y, -3.011 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);

    wall_strip(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 2 + t_y, -3.01 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    wall_strip_black_front(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 2 + t_y, -3.011 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);

    wall_strip(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 4 + t_y, -3.01 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
    wall_strip_black_front(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 4 + t_y, -3.011 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);



    wall_strip(1 * s_x, 1 * s_y, 1 * s_z, 2.8 + t_x, 0 + t_y, -0.14 + t_z, 0 + r_x, 90 + r_y, 0 + r_z, cubeVAO, lightingShader);
    wall_strip_black_right(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 0 + t_y, 0 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);

    wall_strip(1 * s_x, 1 * s_y, 1 * s_z, 2.8 + t_x, 2 + t_y, -0.14 + t_z, 0 + r_x, 90 + r_y, 0 + r_z, cubeVAO, lightingShader);
    wall_strip_black_right(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 2 + t_y, 0 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);

    wall_strip(1 * s_x, 1 * s_y, 1 * s_z, 2.8 + t_x, 4 + t_y, -0.14 + t_z, 0 + r_x, 90 + r_y, 0 + r_z, cubeVAO, lightingShader);
    wall_strip_black_right(1 * s_x, 1 * s_y, 1 * s_z, 0 + t_x, 4 + t_y, 0 + t_z, 0 + r_x, 0 + r_y, 0 + r_z, cubeVAO, lightingShader);
}

struct Vertex2 {
    float x, y, z;
};

void generateUmbrellaCanopyVertices(float s_x, float s_y, float s_z, float t_x, float t_y, float t_z, glm::vec3 color, float rx, float ry, float rz) {

    std::vector<Vertex2> vertices;
    std::vector<GLuint> indices;

    int numLatitudes = 36;
    int numLongitudes = 36;
    float canopyRadius = 2.0f;

    for (int i = 0; i < numLatitudes; ++i) {  // Adjusted loop condition
        float lat0 = M_PI * (-0.5 + (float)i / numLatitudes);
        float z0 = sin(lat0) * canopyRadius;
        float cosLat0 = cos(lat0);

        float lat1 = M_PI * (-0.5 + (float)(i + 1) / numLatitudes);  // Adjusted loop condition
        float z1 = sin(lat1) * canopyRadius;
        float cosLat1 = cos(lat1);

        for (int j = 0; j <= numLongitudes; ++j) {
            float lng = 2 * M_PI * (float)j / numLongitudes;
            float x = cos(lng) * canopyRadius * cosLat1;
            float y = sin(lng) * canopyRadius * cosLat1;

            Vertex2 vertex = { x, y, z1 };
            vertices.push_back(vertex);
            // Add color attribute to the vertices
            vertex = { color.r, color.g, color.b };
            vertices.push_back(vertex);

            vertex = { x, y, z0 };
            vertices.push_back(vertex);
            // Add color attribute to the vertices
            vertex = { color.r, color.g, color.b };
            vertices.push_back(vertex);
        }
    }

    for (int i = 0; i < numLatitudes - 1; ++i) {  // Adjusted loop condition
        for (int j = 0; j < numLongitudes; ++j) {
            int nextColumn = (2 * numLongitudes + 2);
            int nextRow = (2 * (numLongitudes + 1));

            indices.push_back(i * nextColumn + j * 2);
            indices.push_back(i * nextColumn + j * 2 + 1);
            indices.push_back((i + 1) * nextColumn + j * 2);

            indices.push_back(i * nextColumn + j * 2 + 1);
            indices.push_back((i + 1) * nextColumn + j * 2 + 1);
            indices.push_back((i + 1) * nextColumn + j * 2);
        }
    }



    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), indices.data(), GL_STATIC_DRAW);

    // position attribute
   // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //floor_black_color_cube
    translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X + t_x, translate_Y + t_y, translate_Z + t_z));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + rx), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + ry), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + rz), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X * s_x, scale_Y * s_y, scale_Z * s_z));
    model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    ourShader.setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLE_FAN, indices.size(), GL_UNSIGNED_INT, 0);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);


}

void leaf(float sx, float sy, float sz, float tx, float ty, float tz, float rx, float ry, float rz, unsigned int& cubeVAO, Shader& lightingShader)
{
    green_color((4 + 6) + sx, (4 + 6) + sy, (4 + 6) + sz, 14 + 0.25 + tx, 2.9 + ty+2, 3 - 0.5 + tz, 0 + rx, 0 + ry, 0 + rz, cubeVAO, lightingShader);
    green_color((4 + 6) + sx, (4 + 6) + sy, (4 + 6) + sz, 14 + 0.25 + tx, 3.0 + ty + 2, 3 - 0.5 + tz, 0 + rx, 0 + ry, 30 + rz, cubeVAO, lightingShader);
    green_color((4 + 6) + sx, (4 + 6) + sy, (4 + 6) + sz, 14 + 0.25 + tx, 3.2 + ty + 2, 3 - 0.5 + tz, 0 + rx, 0 + ry, -30 + rz, cubeVAO, lightingShader);
    green_color((4 + 6) + sx, (4 + 6) + sy, (4 + 6) + sz, 14 + 0.25 + tx, 3.2 + ty + 2, 3 - 0.5 + tz, 30 + rx, 0 + ry, 0 + rz, cubeVAO, lightingShader);
    green_color((4 + 6) + sx, (4 + 6) + sy, (4 + 6) + sz, 14 + 0.25 + tx, 3.2 + ty + 2, 3 - 0.5 + tz, -30 + rx, 0 + ry, 0 + rz, cubeVAO, lightingShader);
    green_color((4 + 6) + sx, (4 + 6) + sy, (4 + 6) + sz, 14 + 0.25 + tx, 3.2 + ty + 2, 3 - 0.5 + tz, 0 + rx, 30 + ry, 0 + rz, cubeVAO, lightingShader);
    green_color((4 + 6) + sx, (4 + 6) + sy, (4 + 6) + sz, 14 + 0.25 + tx, 3.2 + ty+2, 3 - 0.5 + tz, 0 + rx, -0 + ry, 0 + rz, cubeVAO, lightingShader);
}
void tree_1(float sx, float sy, float sz, float tx, float ty, float tz, float rx, float ry, float rz, unsigned int& cubeVAO, Shader& lightingShader)
{
    Cylinder cylinder = Cylinder();

    cylinder.drawSphere(lightingShader, model_Matrix(1 * sx, 1 * sy, 1 * sz, 14 + tx, 0.01 + ty, 3 + tz, 0 + rx, 0 + ry, 0 + rz));
    cylinder.drawSphere(lightingShader, model_Matrix(0.6 * sx, 0.7 * sy, 0.6 * sz, 14 + tx, 3.5 + ty, 3 + tz, 0 + rx, 0 + ry, 30 + rz));
    cylinder.drawSphere(lightingShader, model_Matrix(0.6 * sx, 0.7 * sy, 0.6 * sz, 14 + tx, 3.5 + ty, 3 + tz, 0 + rx, 0 + ry, -30 + rz));

}
void red_car(float sx, float sy, float sz, float tx, float ty, float tz, float rx, float ry, float rz, unsigned int& cubeVAO, Shader& lightingShader, Wheel& wheel,Shader& ourShader)
{
    ourShader.use();
    //car 1

    red_color(8, 1, 2.16, -3 - 0.15+tx, 0.01 + 0.2 - 0.01+ty, 0 + 0.5 + 0.01 - 0.007+tz, 0 , 0 , 0 , cubeVAO, lightingShader);
    //red_color(0.02, 2.5, 2.16, -3-0.25+0.75, 0.01+0.2-0.01, 0+0.5+0.01-0.007, 0, 0, 15,cubeVAO,lightingShader);
    light_red_color(0.02, 1.5, 2.16, -3 - 0.25 + 0.75 + tx, 0.3 + ty, 0 + 0.5 + 0.01 - 0.007 + tz, 0 , 0 , 40 , cubeVAO, lightingShader);
    light_red_color(0.02, 1.44, 2.16, -3 - 0.25 + 0.25 + tx, 0.3 + ty, 0 + 0.5 + 0.01 - 0.007 + tz, 0 , 0 , -35 , cubeVAO, lightingShader);
    red_color(3.27, 0.02, 2.16, -3 + 0.037 + 0.044 + tx, 0.415 + ty, 0 + 0.5 + 0.01 - 0.007 + tz, 0 , 0 , 0 , cubeVAO, lightingShader);

    red_color(0.08, -1.4, 0.01, -3 + 0.037 + 0.044 + tx, 0.415 + ty, 0 + 0.5 + 0.01 - 0.007 + 0.21 + tz, 0 , 0 , 0 , cubeVAO, lightingShader);
    red_color(0.25, -1.4, 0.01, -3 + 0.037 + 0.044 + 0.15 + tx, 0.415 + ty, 0 + 0.5 + 0.01 - 0.007 + 0.21 + tz, 0, 0 , 0 , cubeVAO, lightingShader);
    red_color(0.08, -1.4, 0.01, -3 + 0.037 + 0.044 + 0.317 + tx, 0.415 + ty, 0 + 0.5 + 0.01 - 0.007 + 0.21 + tz, 0 , 0 , 0 , cubeVAO, lightingShader);

    red_color(0.08, -1.4, 0.01, -3 + 0.037 + 0.044 + tx, 0.415 + ty, 0 + 0.5 + 0.01 - 0.007 + tz, 0 , 0 , 0 , cubeVAO, lightingShader);
    red_color(0.25, -1.4, 0.01, -3 + 0.037 + 0.044 + 0.15 + tx, 0.415 + ty, 0 + 0.5 + 0.01 - 0.007 + tz, 0 , 0 , 0 , cubeVAO, lightingShader);
    red_color(0.08, -1.4, 0.01, -3 + 0.037 + 0.044 + 0.317 + tx, 0.415 + ty, 0 + 0.5 + 0.01 - 0.007 + tz, 0 , 0 , 0 , cubeVAO, lightingShader);

    //back wheel
    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + tx, 0.2 - 0.01 + ty, 0 + 0.3 + 0.4 + tz, 0 + rx, 0 + ry, 0 + rz),0.5,0.5,0.5);
    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + tx, 0.2 - 0.01 + ty, 0 + 0.3 + 0.4 + tz, 0 + rx, 0 + ry, 90 + rz), 0.4, 0.4, 0.4);
    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + tx, 0.2 - 0.01 + ty, 0 + 0.3 + 0.4 + tz, 0 + rx, 0 + ry, 180 + rz), 0.5, 0.5, 0.5);
    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + tx, 0.2 - 0.01 + ty, 0 + 0.3 + 0.4 + tz, 0 + rx, 0 + ry, 270 + rz), 0.4, 0.4, 0.4);

    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + tx, 0.2 - 0.01 + ty, 0.1 + 0.4 + tz, 0 + rx, 0 + ry, 0 + rz), 0.5, 0.5, 0.5);
    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + tx, 0.2 - 0.01 + ty, 0.1 + 0.4 + tz, 0 + rx, 0 + ry, 90 + rz), 0.4, 0.4, 0.4);
    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + tx, 0.2 - 0.01 + ty, 0.1 + 0.4 + tz, 0 + rx, 0 + ry, 180 + rz), 0.5, 0.5, 0.5);
    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + tx, 0.2 - 0.01 + ty, 0.1 + 0.4 + tz, 0 + rx, 0 + ry, 270 + rz), 0.4, 0.4, 0.4);

    //front wheel
    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + 0.5 + tx, 0.2 - 0.01 + ty, 0 + 0.3 + 0.4 + tz, 0 + rx, 0 + ry, 0 + rz), 0.5, 0.5, 0.5);
    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + 0.5 + tx, 0.2 - 0.01 + ty, 0 + 0.3 + 0.4 + tz, 0 + rx, 0 + ry, 90 + rz), 0.4, 0.4, 0.4);
    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + 0.5 + tx, 0.2 - 0.01 + ty, 0 + 0.3 + 0.4 + tz, 0 + rx, 0 + ry, 180 + rz), 0.5, 0.5, 0.5);
    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + 0.5 + tx, 0.2 - 0.01 + ty, 0 + 0.3 + 0.4 + tz, 0 + rx, 0 + ry, 270 + rz), 0.4, 0.4, 0.4);

    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + 0.5 + tx, 0.2 - 0.01 + ty, 0.1 + 0.4 + tz, 0 + rx, 0 + ry, 0 + rz), 0.5, 0.5, 0.5);
    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + 0.5 + tx, 0.2 - 0.01 + ty, 0.1 + 0.4 + tz, 0 + rx, 0 + ry, 90 + rz), 0.4, 0.4, 0.4);
    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + 0.5 + tx, 0.2 - 0.01 + ty, 0.1 + 0.4 + tz, 0 + rx, 0 + ry, 180 + rz), 0.5, 0.5, 0.5);
    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + 0.5 + tx, 0.2 - 0.01 + ty, 0.1 + 0.4 + tz, 0 + rx, 0 + ry, 270 + rz), 0.4, 0.4, 0.4);

}
void mint_turqudise_car(float sx, float sy, float sz, float tx, float ty, float tz, float rx, float ry, float rz, unsigned int& cubeVAO, Shader& lightingShader, Wheel& wheel, Shader& ourShader)
{
    ourShader.use();
    //car 1

    mint_turqudise_color(8, 1, 2.16, -3 - 0.15 + tx, 0.01 + 0.2 - 0.01 + ty, 0 + 0.5 + 0.01 - 0.007 + tz, 0, 0, 0, cubeVAO, lightingShader);
    //red_color(0.02, 2.5, 2.16, -3-0.25+0.75, 0.01+0.2-0.01, 0+0.5+0.01-0.007, 0, 0, 15,cubeVAO,lightingShader);
    mint_turqudise_color(0.02, 1.5, 2.16, -3 - 0.25 + 0.75 + tx, 0.3 + ty, 0 + 0.5 + 0.01 - 0.007 + tz, 0, 0, 40, cubeVAO, lightingShader);
    mint_turqudise_color(0.02, 1.44, 2.16, -3 - 0.25 + 0.25 + tx, 0.3 + ty, 0 + 0.5 + 0.01 - 0.007 + tz, 0, 0, -35, cubeVAO, lightingShader);
    mint_turqudise_color(3.27, 0.02, 2.16, -3 + 0.037 + 0.044 + tx, 0.415 + ty, 0 + 0.5 + 0.01 - 0.007 + tz, 0, 0, 0, cubeVAO, lightingShader);

    mint_turqudise_color(0.08, -1.4, 0.01, -3 + 0.037 + 0.044 + tx, 0.415 + ty, 0 + 0.5 + 0.01 - 0.007 + 0.21 + tz, 0, 0, 0, cubeVAO, lightingShader);
    mint_turqudise_color(0.25, -1.4, 0.01, -3 + 0.037 + 0.044 + 0.15 + tx, 0.415 + ty, 0 + 0.5 + 0.01 - 0.007 + 0.21 + tz, 0, 0, 0, cubeVAO, lightingShader);
    mint_turqudise_color(0.08, -1.4, 0.01, -3 + 0.037 + 0.044 + 0.317 + tx, 0.415 + ty, 0 + 0.5 + 0.01 - 0.007 + 0.21 + tz, 0, 0, 0, cubeVAO, lightingShader);

    mint_turqudise_color(0.08, -1.4, 0.01, -3 + 0.037 + 0.044 + tx, 0.415 + ty, 0 + 0.5 + 0.01 - 0.007 + tz, 0, 0, 0, cubeVAO, lightingShader);
    mint_turqudise_color(0.25, -1.4, 0.01, -3 + 0.037 + 0.044 + 0.15 + tx, 0.415 + ty, 0 + 0.5 + 0.01 - 0.007 + tz, 0, 0, 0, cubeVAO, lightingShader);
    mint_turqudise_color(0.08, -1.4, 0.01, -3 + 0.037 + 0.044 + 0.317 + tx, 0.415 + ty, 0 + 0.5 + 0.01 - 0.007 + tz, 0, 0, 0, cubeVAO, lightingShader);

    //back wheel
    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + tx, 0.2 - 0.01 + ty, 0 + 0.3 + 0.4 + tz, 0 + rx, 0 + ry, 0 + rz), 0.5, 0.5, 0.5);
    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + tx, 0.2 - 0.01 + ty, 0 + 0.3 + 0.4 + tz, 0 + rx, 0 + ry, 90 + rz), 0.4, 0.4, 0.4);
    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + tx, 0.2 - 0.01 + ty, 0 + 0.3 + 0.4 + tz, 0 + rx, 0 + ry, 180 + rz), 0.5, 0.5, 0.5);
    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + tx, 0.2 - 0.01 + ty, 0 + 0.3 + 0.4 + tz, 0 + rx, 0 + ry, 270 + rz), 0.4, 0.4, 0.4);

    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + tx, 0.2 - 0.01 + ty, 0.1 + 0.4 + tz, 0 + rx, 0 + ry, 0 + rz), 0.5, 0.5, 0.5);
    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + tx, 0.2 - 0.01 + ty, 0.1 + 0.4 + tz, 0 + rx, 0 + ry, 90 + rz), 0.4, 0.4, 0.4);
    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + tx, 0.2 - 0.01 + ty, 0.1 + 0.4 + tz, 0 + rx, 0 + ry, 180 + rz), 0.5, 0.5, 0.5);
    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + tx, 0.2 - 0.01 + ty, 0.1 + 0.4 + tz, 0 + rx, 0 + ry, 270 + rz), 0.4, 0.4, 0.4);

    //front wheel
    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + 0.5 + tx, 0.2 - 0.01 + ty, 0 + 0.3 + 0.4 + tz, 0 + rx, 0 + ry, 0 + rz), 0.5, 0.5, 0.5);
    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + 0.5 + tx, 0.2 - 0.01 + ty, 0 + 0.3 + 0.4 + tz, 0 + rx, 0 + ry, 90 + rz), 0.4, 0.4, 0.4);
    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + 0.5 + tx, 0.2 - 0.01 + ty, 0 + 0.3 + 0.4 + tz, 0 + rx, 0 + ry, 180 + rz), 0.5, 0.5, 0.5);
    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + 0.5 + tx, 0.2 - 0.01 + ty, 0 + 0.3 + 0.4 + tz, 0 + rx, 0 + ry, 270 + rz), 0.4, 0.4, 0.4);

    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + 0.5 + tx, 0.2 - 0.01 + ty, 0.1 + 0.4 + tz, 0 + rx, 0 + ry, 0 + rz), 0.5, 0.5, 0.5);
    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + 0.5 + tx, 0.2 - 0.01 + ty, 0.1 + 0.4 + tz, 0 + rx, 0 + ry, 90 + rz), 0.4, 0.4, 0.4);
    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + 0.5 + tx, 0.2 - 0.01 + ty, 0.1 + 0.4 + tz, 0 + rx, 0 + ry, 180 + rz), 0.5, 0.5, 0.5);
    wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + 0.5 + tx, 0.2 - 0.01 + ty, 0.1 + 0.4 + tz, 0 + rx, 0 + ry, 270 + rz), 0.4, 0.4, 0.4);

}
void boat_front(float sx, float sy, float sz, float tx, float ty, float tz, float rx, float ry, float rz)
{
    float cube_vertices[] = {
          0.0f, 0.5f, 0.5f,  0.364f, 0.364f, 0.364f,//0

         -0.5f, 0.0f, 0.0f,  0.364f, 0.364f, 0.364f,//1
          -0.5f, 0.5f, 0.0f,  0.364f, 0.364f, 0.364f,//2

         -0.6f, 0.0f, 0.0f,  0.364f, 0.364f, 0.364f,//3
         -0.6f, 0.5f, 0.0f,  0.364f, 0.364f, 0.364f,//4

         0.5f, 0.0f, 0.0f,  0.364f, 0.364f, 0.364f,//5
         0.5f, 0.5f, 0.0f,  0.364f, 0.364f, 0.364f,//6

         0.6f, 0.0f, 0.0f,  0.364f, 0.364f, 0.364f,//7
         0.6f, 0.5f, 0.0f,  0.364f, 0.364f, 0.364f,//8

    };
    unsigned int cube_indices[] = {
      0, 1, 2,
      0, 3, 4,
      0,1,3,
      0,2,4,
      0,5,6,
      0,7,8,
      0,6,8,
      0,5,7,

      0,1,5,
      0,2,6,



    };
    // configure global opengl state
    // -----------------------------


    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

    // position attribute
   // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //floor_black_color_cube
    translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X + tx, translate_Y + ty, translate_Z + tz));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + rx), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + ry), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + rz), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X * sx, scale_Y * sy, scale_Z * sz));
    model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    // ourShader.setVec3("color", glm::vec3(0.16f, 0.10f, 0.06f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void boat(float sx, float sy, float sz, float tx, float ty, float tz, float rx, float ry, float rz, unsigned int& cubeVAO, Shader& lightingShader)
{
    color_boat(10 * sx, 2 * sy, 0.2 * sz, 4 + tx + 0.76, 5 + ty, 6.76 + tz + .24, 0 + rx, 0 + ry + 90, 0 + rz, cubeVAO, lightingShader);
    boat_front(2 * sx, 2 * sy, 5 * sz, 4 + tx + 1, 5 + ty, 7 + tz, 0, 0, 0);
    boat_front(2 * sx, 2 * sy, 5 * sz, 5 + tx, 5 + ty, 6 + tz, 0, -180, 0);
    color_boat(10 * sx, 2 * sy, 0.2 * sz, 4 + tx + 1.22, 5 + ty, 7.22 + tz - 0.22, 0 + rx, 0 + ry + 90, 0 + rz, cubeVAO, lightingShader);
    color_boat(-10 * sx, 0.2 * sy, -4.6 * sz, 4 + tx + 0.76, 5 + ty, 7.22 + tz - 0.22, 0 + rx, 0 + ry - 90, 0 + rz, cubeVAO, lightingShader);
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    //Shader lightingShader("vertexShaderForGouraudShading.vs", "fragmentShaderForGouraudShading.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");
    Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");
    
    string diffuseMapPath = "soil.jpg";
    string specularMapPath = "container1.png";

    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 20.0f, 40.0f);


    string diffuseMapPath2 = "ticket_counter.png";
    string specularMapPath2 = "container1.png";
    unsigned int diffMap2 = loadTexture(diffuseMapPath2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap2 = loadTexture(specularMapPath2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube2 = Cube(diffMap2, specMap2, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath3 = "adv1.png";
    string specularMapPath3 = "container1.png";
    unsigned int diffMap3 = loadTexture(diffuseMapPath3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap3 = loadTexture(specularMapPath3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube3 = Cube(diffMap3, specMap3, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

   
    string diffuseMapPath4 = "wall1.jpg";
    string specularMapPath4 = "container1.png";
    unsigned int diffMap4 = loadTexture(diffuseMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap4 = loadTexture(specularMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube4 = Cube(diffMap4, specMap4, 32.0f, 0.0f, 0.0f, 1.0f, 6.0f);

    string diffuseMapPath5 = "road.jpg";
    string specularMapPath5 = "container.png";
    unsigned int diffMap5 = loadTexture(diffuseMapPath5.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap5 = loadTexture(specularMapPath5.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube5 = Cube(diffMap5, specMap5, 32.0f, 0.0f, 0.0f, 40.0f, 1.0f);

    string diffuseMapPath6 = "pillar.jpg";
    string specularMapPath6 = "container.png";
    unsigned int diffMap6 = loadTexture(diffuseMapPath6.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap6 = loadTexture(specularMapPath6.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube6 = Cube(diffMap6, specMap6, 32.0f, 0.0f, 0.0f, 1.0f, 10.0f);


    string diffuseMapPath7 = "rail_track_floor.jpg";
    string specularMapPath7 = "container.png";
    unsigned int diffMap7 = loadTexture(diffuseMapPath7.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap7 = loadTexture(specularMapPath7.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube7 = Cube(diffMap7, specMap7, 32.0f, 0.0f, 0.0f, 50.0f, 1.0f);


    string diffuseMapPath8 = "platform.png";
    string specularMapPath8 = "container.png";
    unsigned int diffMap8 = loadTexture(diffuseMapPath8.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap8 = loadTexture(specularMapPath8.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube8 = Cube(diffMap8, specMap8, 32.0f, 0.0f, 0.0f, 10.0f, 1.0f);

   string diffuseMapPath9 = "stair.png";
    string specularMapPath9 = "container.png";
    unsigned int diffMap9 = loadTexture(diffuseMapPath9.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap9 = loadTexture(specularMapPath9.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube9 = Cube(diffMap9, specMap9, 32.0f, 0.0f, 0.0f, 1.0f, 2.0f);

    string diffuseMapPath10 = "stair.png";
    string specularMapPath10 = "container.png";
    unsigned int diffMap10 = loadTexture(diffuseMapPath10.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap10 = loadTexture(specularMapPath10.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube10 = Cube(diffMap10, specMap10, 32.0f, 0.0f, 0.0f, 2.0f, 1.0f);

    string diffuseMapPath11 = "wall3.jpg";
    string specularMapPath11 = "container.png";
    unsigned int diffMap11 = loadTexture(diffuseMapPath11.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap11 = loadTexture(specularMapPath11.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube11 = Cube(diffMap11, specMap11, 32.0f, 0.0f, 0.0f, 2.0f, 1.0f);

    string diffuseMapPath12 = "wall3.jpg";
    string specularMapPath12 = "container.png";
    unsigned int diffMap12 = loadTexture(diffuseMapPath11.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap12 = loadTexture(specularMapPath11.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube12 = Cube(diffMap12, specMap12, 32.0f, 0.0f, 0.0f, 1.0f, 2.0f);

    string diffuseMapPath13 = "wall3.jpg";
    string specularMapPath13 = "container.png";
    unsigned int diffMap13 = loadTexture(diffuseMapPath13.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap13 = loadTexture(specularMapPath13.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube13 = Cube(diffMap13, specMap13, 32.0f, 0.0f, 0.0f, 0.4f, 0.4f);

 
    string diffuseMapPath14 = "roof3.jpg";
    string specularMapPath14 = "roof3.jpg";
    unsigned int diffMap14 = loadTexture(diffuseMapPath14.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap14 = loadTexture(specularMapPath14.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube14 = Cube(diffMap14, specMap14, 32.0f, 0.0f, 0.0f, 10.0f, 1.0f);


    string diffuseMapPath15 = "stair_handle.jpg";
    string specularMapPath15 = "stair_handle.jpg";
    unsigned int diffMap15 = loadTexture(diffuseMapPath15.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap15 = loadTexture(specularMapPath15.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube15 = Cube(diffMap15, specMap15, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath16 = "bench1.png";
    string specularMapPath16 = "bench1.png";
    unsigned int diffMap16 = loadTexture(diffuseMapPath16.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap16 = loadTexture(specularMapPath16.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube16 = Cube(diffMap16, specMap16, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    string diffuseMapPath17 = "bench4.jpg";
    string specularMapPath17 = "bench2.jpg";
    unsigned int diffMap17 = loadTexture(diffuseMapPath17.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap17 = loadTexture(specularMapPath17.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube17 = Cube(diffMap17, specMap17, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath18 = "building_wall5.png";
    string specularMapPath18 = "building_wall5.png";
    unsigned int diffMap18 = loadTexture(diffuseMapPath18.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap18 = loadTexture(specularMapPath18.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube18 = Cube(diffMap18, specMap18, 32.0f, 0.0f, 0.0f, 3.0f, 4.0f);


    string diffuseMapPath19 = "building_wall6.png";
    string specularMapPath19 = "building_wall6.png";
    unsigned int diffMap19 = loadTexture(diffuseMapPath19.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap19 = loadTexture(specularMapPath19.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube19 = Cube(diffMap19, specMap19, 32.0f, 0.0f, 0.0f, 1.0f, 8.0f);

    string diffuseMapPath20 = "overbridge_stair.jpg";
    string specularMapPath20 = "overbridge_stair.jpg";
    unsigned int diffMap20 = loadTexture(diffuseMapPath20.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap20 = loadTexture(specularMapPath20.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube20 = Cube(diffMap20, specMap20, 32.0f, 0.0f, 0.0f, 0.5f, 1.0f);


    string diffuseMapPath21 = "overbridge_stair.jpg";
    string specularMapPath21 = "overbridge_stair.jpg";
    unsigned int diffMap21 = loadTexture(diffuseMapPath21.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap21 = loadTexture(specularMapPath21.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube21 = Cube(diffMap21, specMap21, 32.0f, 0.0f, 0.0f, 1.0f, 10.0f);

    string diffuseMapPath22 = "overbridge_wall.png";
    string specularMapPath22 = "overbridge_wall.png";
    unsigned int diffMap22 = loadTexture(diffuseMapPath22.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap22 = loadTexture(specularMapPath22.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube22 = Cube(diffMap22, specMap22, 32.0f, 0.0f, 0.0f, 20.0f, 3.0f);

    string diffuseMapPath23 = "overbridge_wall.png";
    string specularMapPath23 = "overbridge_wall.png";
    unsigned int diffMap23 = loadTexture(diffuseMapPath23.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap23 = loadTexture(specularMapPath23.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube23 = Cube(diffMap23, specMap23, 32.0f, 0.0f, 0.0f, 15.0f, 3.0f);

    string diffuseMapPath24 = "overbridge_wall.png";
    string specularMapPath24 = "overbridge_wall.png";
    unsigned int diffMap24 = loadTexture(diffuseMapPath24.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap24 = loadTexture(specularMapPath24.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube24 = Cube(diffMap24, specMap24, 32.0f, 0.0f, 0.0f, 4.0f, 3.0f);


    string diffuseMapPath25 = "overbridge_wall.png";
    string specularMapPath25 = "overbridge_wall.png";
    unsigned int diffMap25 = loadTexture(diffuseMapPath25.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap25 = loadTexture(specularMapPath25.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube25 = Cube(diffMap25, specMap25, 32.0f, 0.0f, 0.0f, 40.0f, 5.0f);


    string diffuseMapPath26 = "overbridge_stair.jpg";
    string specularMapPath26 = "overbridge_stair.jpg";
    unsigned int diffMap26 = loadTexture(diffuseMapPath26.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap26 = loadTexture(specularMapPath26.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube26 = Cube(diffMap26, specMap26, 32.0f, 0.0f, 0.0f, 5.0f, 3.0f);


    string diffuseMapPath27 = "train2.png";
    string specularMapPath27 = "train2.png";
    unsigned int diffMap27 = loadTexture(diffuseMapPath27.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap27 = loadTexture(specularMapPath27.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube27 = Cube(diffMap27, specMap27, 32.0f, 0.0f, 0.0f, 0.5f, 2.0f);

    string diffuseMapPath28 = "train3.png";
    string specularMapPath28 = "train.png";
    unsigned int diffMap28 = loadTexture(diffuseMapPath28.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap28 = loadTexture(specularMapPath28.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube28 = Cube(diffMap28, specMap28, 32.0f, 0.0f, 0.0f, 0.5f, 2.0f);


   


    string diffuseMapPath29 = "train.png";
    string specularMapPath29 = "train.png";
    unsigned int diffMap29 = loadTexture(diffuseMapPath29.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap29 = loadTexture(specularMapPath29.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube29 = Cube(diffMap29, specMap29, 32.0f, 0.0f, 0.0f, 2.0f, 1.0f);

   
    string diffuseMapPath30 = "train3.png";
    string specularMapPath30 = "train3.png";
    unsigned int diffMap30 = loadTexture(diffuseMapPath30.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap30 = loadTexture(specularMapPath30.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube30 = Cube(diffMap30, specMap30, 32.0f, 0.0f, 0.0f, 0.5f, 4.0f);

    string diffuseMapPath31 = "train_roof.jpg";
    string specularMapPath31 = "train_roof.jpg";
    unsigned int diffMap31 = loadTexture(diffuseMapPath31.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap31 = loadTexture(specularMapPath31.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube31 = Cube(diffMap31, specMap31, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath32 = "grass2.png";
    string specularMapPath32 = "grass2.png";
    unsigned int diffMap32 = loadTexture(diffuseMapPath32.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap32 = loadTexture(specularMapPath32.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube32 = Cube(diffMap32, specMap32, 32.0f, 0.0f, 0.0f, 50.0f, 10.0f);


    string diffuseMapPath33 = "river2.png";
    string specularMapPath33 = "river2.png";
    unsigned int diffMap33 = loadTexture(diffuseMapPath33.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap33 = loadTexture(specularMapPath33.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube33 = Cube(diffMap33, specMap33, 32.0f, 0.0f, 0.0f, 2.0f, 5.0f);

  

    string diffuseMapPath34 = "building4.png";
    string specularMapPath34 = "building4.png";
    unsigned int diffMap34 = loadTexture(diffuseMapPath34.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap34 = loadTexture(specularMapPath34.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube34 = Cube(diffMap34, specMap34, 32.0f, 0.0f, 0.0f, 2.0f, 9.5f);
 
    string diffuseMapPath35 = "building_5.jpg";
    string specularMapPath35 = "building_5.jpg";
    unsigned int diffMap35 = loadTexture(diffuseMapPath35.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap35 = loadTexture(specularMapPath35.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube35 = Cube(diffMap35, specMap35, 32.0f, 0.0f, 0.0f, 2.0f, 3.0f);

    string diffuseMapPath36 = "building_6_2.png";
    string specularMapPath36 = "building_6_2.png";
    unsigned int diffMap36 = loadTexture(diffuseMapPath36.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap36 = loadTexture(specularMapPath36.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube36 = Cube(diffMap36, specMap36, 32.0f, 0.0f, 0.0f, 2.0f, 3.0f);

    string diffuseMapPath37 = "building_6.png";
    string specularMapPath37 = "building_6.png";
    unsigned int diffMap37 = loadTexture(diffuseMapPath37.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap37 = loadTexture(specularMapPath37.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube37 = Cube(diffMap37, specMap37, 32.0f, 0.0f, 0.0f, 2.0f, 3.0f);


    string diffuseMapPath38 = "river2.png";
    string specularMapPath38 = "river2.png";
    unsigned int diffMap38 = loadTexture(diffuseMapPath38.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap38 = loadTexture(specularMapPath38.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube38 = Cube(diffMap38, specMap38, 32.0f, 0.0f, 0.0f, 1.0f, 30.0f);


    string diffuseMapPath39 = "soil.jpg";
    string specularMapPath39 = "container1.png";

    unsigned int diffMap39 = loadTexture(diffuseMapPath39.c_str(), GL_REPEAT, GL_REPEAT, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    unsigned int specMap39 = loadTexture(specularMapPath39.c_str(), GL_REPEAT, GL_REPEAT, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    Cube cube39 = Cube(diffMap39, specMap39, 32.0f, 0.0f, 0.0f, 10.0f, 30.0f);

    string diffuseMapPath40 = "grass2.png";
    string specularMapPath40 = "grass2.png";
    unsigned int diffMap40 = loadTexture(diffuseMapPath40.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap40 = loadTexture(specularMapPath40.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube40 = Cube(diffMap40, specMap40, 32.0f, 0.0f, 0.0f, 15.0f, 10.0f);

    string diffuseMapPath41 = "river2.png";
    string specularMapPath41 = "river2.png";
    unsigned int diffMap41 = loadTexture(diffuseMapPath41.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap41 = loadTexture(specularMapPath41.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube41 = Cube(diffMap41, specMap41, 32.0f, 0.0f, 0.0f, 5.0f, 2.0f);

    string diffuseMapPath42 = "sky.jpg";
    string specularMapPath42 = "sky.jpg";
    unsigned int diffMap42 = loadTexture(diffuseMapPath42.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap42 = loadTexture(specularMapPath42.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube42 = Cube(diffMap42, specMap42, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath43 = "tree.jpg";
    string specularMapPath43 = "tree.jpg";
    unsigned int diffMap43 = loadTexture(diffuseMapPath43.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap43 = loadTexture(specularMapPath43.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube43 = Cube(diffMap43, specMap43, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath44 = "top.png";
    string specularMapPath44 = "top.png";
    unsigned int diffMap44 = loadTexture(diffuseMapPath44.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap44 = loadTexture(specularMapPath44.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube44 = Cube(diffMap44, specMap44, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath45 = "left.png";
    string specularMapPath45 = "left.png";
    unsigned int diffMap45 = loadTexture(diffuseMapPath45.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap45 = loadTexture(specularMapPath45.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube45 = Cube(diffMap45, specMap45, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath46 = "right.png";
    string specularMapPath46 = "right.png";
    unsigned int diffMap46 = loadTexture(diffuseMapPath46.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap46 = loadTexture(specularMapPath46.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube46 = Cube(diffMap45, specMap45, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath47 = "back.png";
    string specularMapPath47 = "back.png";
    unsigned int diffMap47 = loadTexture(diffuseMapPath47.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap47 = loadTexture(specularMapPath47.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube47 = Cube(diffMap47, specMap47, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath48 = "sun_2.png";
    string specularMapPath48 = "sun_2.png";
    unsigned int diffMap48 = loadTexture(diffuseMapPath48.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap48 = loadTexture(specularMapPath48.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube48 = Cube(diffMap48, specMap48, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath49 = "road_bridge.png";
    string specularMapPath49 = "road_bridge.png";
    unsigned int diffMap49 = loadTexture(diffuseMapPath49.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap49 = loadTexture(specularMapPath49.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube49 = Cube(diffMap49, specMap49, 32.0f, 0.0f, 0.0f, 2.0f, 1.0f);



    Cylinder cylinder = Cylinder();
    Cylinder cylinder2 = Cylinder(1.0f, 36, 18, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f);

    Wheel wheel = Wheel();

    Sphere cloud = Sphere(1.0f, 36, 18, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f);
    

    //float radius = 1.0f, int sectorCount = 36, int stackCount = 18, glm::vec3 amb = glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3 diff = glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3 spec = glm::vec3(0.5f, 0.5f, 0.5f), float shiny = 32.0f
    Sphere2 sphere =  Sphere2(1.0f,36,18, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f, diffMap43, specMap43,0.0f,0.0f,1.0f,1.0f);
    Sphere2 sun_sphere =  Sphere2(1.0f,36,18, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f, diffMap48, specMap48,0.0f,0.0f,1.0f,1.0f);


    glm::mat4 model = model_Matrix(5,5,5, 26, 6.3, 3 + 4 + 2 - 11.5,0,0,0);
    Pyramid pyramidTree = Pyramid(model, diffuseMapPath43);
    model = model_Matrix(5, 5, 5, 26, 6.3, 3 + 4 + 2 - 11.5, 0, 180, 0);
    Pyramid pyramidTree2 = Pyramid(model, diffuseMapPath43);

    model = model_Matrix(7, 7, 7, 26, 5.5, 3 + 4 + 2 - 11.5, 0, 0, 0);
    Pyramid pyramidTree3 = Pyramid(model, diffuseMapPath43);
    model = model_Matrix(7, 7, 7, 26, 5.5, 3 + 4 + 2 - 11.5, 0, 180, 0);
    Pyramid pyramidTree4 = Pyramid(model, diffuseMapPath43);

    model = model_Matrix(9, 9, 9, 26, 4.7, 3 + 4 + 2 - 11.5, 0, 0, 0);
    Pyramid pyramidTree5 = Pyramid(model, diffuseMapPath43);
    model = model_Matrix(9, 9, 9, 26, 4.7, 3 + 4 + 2 - 11.5, 0, 180, 0);
    Pyramid pyramidTree6 = Pyramid(model, diffuseMapPath43);

    model = model_Matrix(11, 11, 11, 26, 3.9, 3 + 4 + 2 - 11.5, 0, 0, 0);
    Pyramid pyramidTree7 = Pyramid(model, diffuseMapPath43);
    model = model_Matrix(11, 11, 11, 26, 3.9, 3 + 4 + 2 - 11.5, 0, 180, 0);
    Pyramid pyramidTree8 = Pyramid(model, diffuseMapPath43);

    model = model_Matrix(13, 13, 13, 26, 3.1, 3 + 4 + 2 - 11.5, 0, 0, 0);
    Pyramid pyramidTree9 = Pyramid(model, diffuseMapPath43);
    model = model_Matrix(13, 13, 13, 26, 3.1, 3 + 4 + 2 - 11.5, 0, 180, 0);
    Pyramid pyramidTree10 = Pyramid(model, diffuseMapPath43);

    model = model_Matrix(15, 15, 15, 26, 2.8, 3 + 4 + 2 - 11.5, 0, 0, 0);
    Pyramid pyramidTree11 = Pyramid(model, diffuseMapPath43);
    model = model_Matrix(15, 15, 15, 26, 2.8, 3 + 4 + 2 - 11.5, 0, 180, 0);
    Pyramid pyramidTree12 = Pyramid(model, diffuseMapPath43);

    glm::vec3 p0(-4, 5.45, 6);
    glm::vec3 p1(-4, 8.45, 2.0);
    glm::vec3 p2(-4, 6.45, 2.0);
    glm::vec3 p3(-4, 5.45, -2.7);


  /*  glm::vec3 p0(-4, 2.5, 0);
    glm::vec3 p1(32, 2.5, 0);
    glm::vec3 p2(32, 2.5, 0);
    glm::vec3 p3(60, 2.5, 0);*/
    

    model = model_Matrix(5, 5, 5, 0.2, 0, 0,0,0,0);
    Curve tunnel1(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 0.5, 0, 0, 0, 0, 0);
    Curve tunnel2(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 0.8, 0, 0, 0, 0, 0);
    Curve tunnel3(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 1.1, 0, 0, 0, 0, 0);
    Curve tunnel4(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 1.4, 0, 0, 0, 0, 0);
    Curve tunnel5(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 1.7, 0, 0, 0, 0, 0);
    Curve tunnel6(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 2, 0, 0, 0, 0, 0);
    Curve tunnel7(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 2.3, 0, 0, 0, 0, 0);
    Curve tunnel8(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 2.6, 0, 0, 0, 0, 0);
    Curve tunnel9(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 2.9, 0, 0, 0, 0, 0);
    Curve tunnel10(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 3.1, 0, 0, 0, 0, 0);
    Curve tunnel11(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 3.4, 0, 0, 0, 0, 0);
    Curve tunnel12(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 3.7, 0, 0, 0, 0, 0);
    Curve tunnel13(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 4.0, 0, 0, 0, 0, 0);
    Curve tunnel14(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 4.3, 0, 0, 0, 0, 0);
    Curve tunnel15(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 4.6, 0, 0, 0, 0, 0);
    Curve tunnel16(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 4.9, 0, 0, 0, 0, 0);
    Curve tunnel17(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 5.2, 0, 0, 0, 0, 0);
    Curve tunnel18(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 5.5, 0, 0, 0, 0, 0);
    Curve tunnel19(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 5.8, 0, 0, 0, 0, 0);
    Curve tunnel20(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 6.1, 0, 0, 0, 0, 0);
    Curve tunnel21(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 6.4, 0, 0, 0, 0, 0);
    Curve tunnel22(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 6.7, 0, 0, 0, 0, 0);
    Curve tunnel23(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 7.0, 0, 0, 0, 0, 0);
    Curve tunnel24(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 7.3, 0, 0, 0, 0, 0);
    Curve tunnel25(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 7.6, 0, 0, 0, 0, 0);
    Curve tunnel26(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 7.9, 0, 0, 0, 0, 0);
    Curve tunnel27(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 8.2, 0, 0, 0, 0, 0);
    Curve tunnel28(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 8.5, 0, 0, 0, 0, 0);
    Curve tunnel29(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 8.8, 0, 0, 0, 0, 0);
    Curve tunnel30(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 9.1, 0, 0, 0, 0, 0);
    Curve tunnel31(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);

    model = model_Matrix(5, 5, 5, 9.4, 0, 0, 0, 0, 0);
    Curve tunnel32(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 9.7, 0, 0, 0, 0, 0);
    Curve tunnel33(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 10, 0, 0, 0, 0, 0);
    Curve tunnel34(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 10.3, 0, 0, 0, 0, 0);
    Curve tunnel35(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 10.6, 0, 0, 0, 0, 0);
    Curve tunnel36(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 10.9, 0, 0, 0, 0, 0);
    Curve tunnel37(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 11.2, 0, 0, 0, 0, 0);
    Curve tunnel38(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 11.5, 0, 0, 0, 0, 0);
    Curve tunnel39(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 11.8, 0, 0, 0, 0, 0);
    Curve tunnel40(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 12.1, 0, 0, 0, 0, 0);
    Curve tunnel41(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);

    model = model_Matrix(5, 5, 5, 0.2+60.5, 0, 0, 0, 0, 0);
    Curve tunnel42(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 0.5 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel43(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 0.8 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel44(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 1.1 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel45(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 1.4 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel46(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 1.7 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel47(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 2 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel48(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 2.3 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel49(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 2.6 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel50(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 2.9 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel51(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 3.1 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel52(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 3.4 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel53(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 3.7 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel54(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 4.0 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel55(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 4.3 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel56(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 4.6 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel57(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 4.9 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel58(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 5.2 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel59(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 5.5 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel60(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 5.8 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel61(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 6.1 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel62(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 6.4 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel63(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 6.7 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel64(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 7.0 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel65(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 7.3 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel66(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 7.6 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel67(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 7.9 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel68(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 8.2 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel69(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 8.5 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel70(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 8.8 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel71(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 9.1 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel72(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);

    model = model_Matrix(5, 5, 5, 9.4 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel73(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 9.7 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel74(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 10 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel75(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 10.3 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel76(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 10.6 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel77(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 10.9 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel78(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 11.2 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel79(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 11.5 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel80(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 11.8 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel81(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 12.1 + 60.5, 0, 0, 0, 0, 0);
    Curve tunnel82(model, "grey.jpg", p0, p1, p2, p3,
        1000, 0.2f, 16);

   /* model = model_Matrix(50, 15, 50, 1, 1, 0, 90, 0, 0);
    Tunnel tunnel83(model, "sky.jpg", p0, p1, p2, p3,
        1500, 10.0f, 10);

    model = model_Matrix(50, 15, 50, 1, 1, 1, 0, 0, 0);
    Tunnel tunnel84(model, "sky2.jpg", p0, p1, p2, p3,
        1500, 9.9f, 10);*/

   /* model = model_Matrix(5, 5, 5, 12.4, 0, 0, 0, 0, 0);
    Tunnel tunnel42(model, "train3.png", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 12.7, 0, 0, 0, 0, 0);
    Tunnel tunnel43(model, "train3.png", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 13, 0, 0, 0, 0, 0);
    Tunnel tunnel44(model, "train3.png", p0, p1, p2, p3,
        1000, 0.2f, 16);

    model = model_Matrix(5, 5, 5, 13.3, 0, 0, 0, 0, 0);
    Tunnel tunnel45(model, "train3.png", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 13.6, 0, 0, 0, 0, 0);
    Tunnel tunnel46(model, "train3.png", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 13.9, 0, 0, 0, 0, 0);
    Tunnel tunnel47(model, "train3.png", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 14.2, 0, 0, 0, 0, 0);
    Tunnel tunnel48(model, "train3.png", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 14.5, 0, 0, 0, 0, 0);
    Tunnel tunnel49(model, "train3.png", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 14.8, 0, 0, 0, 0, 0);
    Tunnel tunnel50(model, "train3.png", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 15.1, 0, 0, 0, 0, 0);
    Tunnel tunnel51(model, "train3.png", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 15.4, 0, 0, 0, 0, 0);
    Tunnel tunnel52(model, "train3.png", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 15.7, 0, 0, 0, 0, 0);
    Tunnel tunnel53(model, "train3.png", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 16, 0, 0, 0, 0, 0);
    Tunnel tunnel54(model, "train3.png", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 16.3, 0, 0, 0, 0, 0);
    Tunnel tunnel55(model, "train3.png", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 16.6, 0, 0, 0, 0, 0);
    Tunnel tunnel56(model, "train3.png", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 16.9, 0, 0, 0, 0, 0);
    Tunnel tunnel57(model, "train3.png", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 17.2, 0, 0, 0, 0, 0);
    Tunnel tunnel58(model, "train3.png", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 17.5, 0, 0, 0, 0, 0);
    Tunnel tunnel59(model, "train3.png", p0, p1, p2, p3,
        1000, 0.2f, 16);
    model = model_Matrix(5, 5, 5, 17.8, 0, 0, 0, 0, 0);
    Tunnel tunnel60(model, "train3.png", p0, p1, p2, p3,
        1000, 0.2f, 16);*/


   /* model = model_Matrix(5, 5, 5, 0, 0, 0, 0, 0, 0);
    Tunnel tunnel2(model, "train3.png", p0, p1, p2, p3,
        1000, 1.0f, 16);*



    CurvedRoad road = CurvedRoad(model, "sun2.png", p0, p1, p2, p3,
        2000, 0.2f);



   /* model = model_Matrix(5, 5, 5, 5, 9.5, 5, 0, 0, 0);
    Pyramid pyramidTree = Pyramid(model, diffuseMapPath43);
    model = model_Matrix(5, 5, 5, 5, 9.5, 5, 0, 180, 0);
    Pyramid pyramidTree2 = Pyramid(model, diffuseMapPath43);*/

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    float cube_vertices[] = {
     0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.5f,
     0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -0.5f,
     0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -0.5f,
     0.0f, 0.5f, 0.0f, 0.0f, 0.0f, -0.5f,

     0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f,
     0.5f, 0.5f, 0.0f, 0.5f, 0.0f, 0.0f,
     0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 0.0f,
     0.5f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f,

     0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.5f,
     0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 0.5f,
     0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.5f,
     0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 0.5f,

     0.0f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f,
     0.0f, 0.5f, 0.5f, -0.5f, 0.0f, 0.0f,
     0.0f, 0.5f, 0.0f, -0.5f, 0.0f, 0.0f,
     0.0f, 0.0f, 0.0f, -0.5f, 0.0f, 0.0f,

     0.5f, 0.5f, 0.5f, 0.0f, 0.5f, 0.0f,
     0.5f, 0.5f, 0.0f, 0.0f, 0.5f, 0.0f,
     0.0f, 0.5f, 0.0f, 0.0f, 0.5f, 0.0f,
     0.0f, 0.5f, 0.5f, 0.0f, 0.5f, 0.0f,

     0.0f, 0.0f, 0.0f, 0.0f, -0.5f, 0.0f,
     0.5f, 0.0f, 0.0f, 0.0f, -0.5f, 0.0f,
     0.5f, 0.0f, 0.5f, 0.0f, -0.5f, 0.0f,
     0.0f, 0.0f, 0.5f, 0.0f, -0.5f, 0.0f
    };

    unsigned int cube_indices[] = {
         0, 3, 2,
       2, 1, 0,

       4, 5, 7,
       7, 6, 4,

       8, 9, 10,
       10, 11, 8,

       12, 13, 14,
       14, 15, 12,

       16, 17, 18,
       18, 19, 16,

       20, 21, 22,
       22, 23, 20
    };

    unsigned int cubeVAO, cubeVBO, cubeEBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

   // Sphere sphere = Sphere();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    //curvy roof draw
    vector<float> curve1 = {
                     -4, 5.45, 6,
    -4, 8.45, 2.0,
    -4, 6.45, 2.0,
    -4, 5.45, -2.7,
    };


    vector<float>curve2 = {
            -0.3700, 1.6750, 5.1000,
            -0.3850, 1.6100, 5.1000,
            -0.3350, 1.5300, 5.1000,
            -0.2900, 1.4850, 5.1000,
            -0.2600, 1.4350, 5.1000,
            -0.2600, 1.3200, 5.1000,
            -0.3200, 1.2500, 5.1000,
            -0.4000, 1.1200, 5.1000,
            -0.4750, 1.0100, 5.1000,
            -0.5450, 0.8650, 5.1000,
            -0.5800, 0.7350, 5.1000,
            -0.5850, 0.5950, 5.1000,
            -0.5400, 0.4800, 5.1000,
            -0.4400, 0.3550, 5.1000,
            -0.3700, 0.2400, 5.1000,
            -0.3150, 0.1450, 5.1000,
            -0.3050, 0.0650, 5.1000,
            -0.2950, 0.0100, 5.1000,
            -0.1950, 0.0050, 5.1000,
            -0.1050, -0.0050, 5.1000,
            -0.0350, -0.0050, 5.1000,
    };

    Cube curve1_1 = Cube(glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1),32.0);
    curve1_1.initiate(curve1);


    //ourShader.use();
    //lightingShader.use();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {

        if (!hotKey)
        {
            //Hot Key

            cout << "Press F for Watch Tower View" << endl;
            cout << "Press J and A for Inside Train View" << endl;
            cout << "Press T and Hold for  Train Move" << endl;
            cout << "Press R and Hold for  Train Reverse Move" << endl;
            cout << "Press C  for  Under Train View" << endl;
            cout << "Press G  for  Lake View" << endl;
            cout << "Press H  for  Under Platform View" << endl;
            cout << "Press B  for  2nd Platform View" << endl;

            cout << "Press T for train forward" << endl;
            cout << "Press R for train reverse" << endl;


            cout << "Press 1 for point lights on off" << endl;
            cout << "Press 2 for spot lights on off" << endl;
            cout << "Press 3 for direction light on off" << endl;
            cout << "Press 4 for ambient on off" << endl;
            cout << "Press 5 for diffuse on off" << endl;
            cout << "Press 6 for specular on off" << endl;
            
            hotKey = true;
        }

        



        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
       // cout << deltaTime<<" "<< lastFrame << endl;
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.529f, 0.807f, 0.921f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
       
        lightingShader.setVec3("viewPos", camera.Position);
      



        // point light 1
       pointlight1.setUpPointLight(lightingShader);
       
        // point light 2
       pointlight2.setUpPointLight(lightingShader);
     
      // point light 3
      pointlight3.setUpPointLight(lightingShader);
      pointlight4.setUpPointLight(lightingShader);
      pointlight5.setUpPointLight(lightingShader);
      pointlight6.setUpPointLight(lightingShader);
      //
      //  // point light 4
      // pointlight4.setUpPointLight(lightingShader);
        
      
        spotlight1.setUpSpotLight(lightingShader);
        spotlight2.setUpSpotLight(lightingShader);
        spotlight3.setUpSpotLight(lightingShader);
        spotlight4.setUpSpotLight(lightingShader);
        spotlight5.setUpSpotLight(lightingShader);
        spotlight6.setUpSpotLight(lightingShader);
        spotlight7.setUpSpotLight(lightingShader);
        spotlight8.setUpSpotLight(lightingShader);
        spotlight9.setUpSpotLight(lightingShader);
        spotlight10.setUpSpotLight(lightingShader);
        spotlight11.setUpSpotLight(lightingShader);
        spotlight12.setUpSpotLight(lightingShader);
        spotlight13.setUpSpotLight(lightingShader);
        spotlight14.setUpSpotLight(lightingShader);
        spotlight15.setUpSpotLight(lightingShader);
        spotlight16.setUpSpotLight(lightingShader);
        spotlight17.setUpSpotLight(lightingShader);
        spotlight18.setUpSpotLight(lightingShader);
        spotlight19.setUpSpotLight(lightingShader);
        spotlight20.setUpSpotLight(lightingShader);
        spotlight21.setUpSpotLight(lightingShader);
        spotlight22.setUpSpotLight(lightingShader);
        spotlight23.setUpSpotLight(lightingShader);
        spotlight24.setUpSpotLight(lightingShader);
        spotlight25.setUpSpotLight(lightingShader);
        spotlight26.setUpSpotLight(lightingShader);
        spotlight27.setUpSpotLight(lightingShader);
        spotlight28.setUpSpotLight(lightingShader);
        spotlight29.setUpSpotLight(lightingShader);
        spotlight30.setUpSpotLight(lightingShader);
        spotlight31.setUpSpotLight(lightingShader);
        spotlight32.setUpSpotLight(lightingShader);
        spotlight33.setUpSpotLight(lightingShader);
        spotlight34.setUpSpotLight(lightingShader);
        spotlight35.setUpSpotLight(lightingShader);
        spotlight36.setUpSpotLight(lightingShader);
        spotlight37.setUpSpotLight(lightingShader);
        spotlight38.setUpSpotLight(lightingShader);
       
        directionlight1.setUpDirectionalLight(lightingShader);
      
        

        // activate shader
       // lightingShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShader.setMat4("projection", projection);
       


        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        lightingShader.setMat4("view", view);
      

     

        /*glm::mat4 model = model_Matrix(-31, 2, 16, 5.1, 1, 0.2);
        lightingShader.setMat4("model", model);
        drawCube(cubeVAO, lightingShader, model, 0.99207f, 0.99207f, 0.588f);*/

      //  chair_color(-31, 2, 16, 5.1, 1, 0.2,cubeVAO,lightingShader);


       /* glm::mat4 model_chair_1 = model_Matrix(-31, 2, 16, 5.1, 1, 0.2);
        lightingShader.setMat4("model", model_chair_1);
        drawCube(cubeVAO, lightingShader, model_chair_1, 0.99207f, 0.99207f, 0.588f);*/

        //glBindVertexArray(cubeVAO);
        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 36);

       // bed(cubeVAO, lightingShader, model);

      

       // drawWithTexture();

     
       // white_color2(1030, 0.8, -200, -4 , 0, 11, 0, 0, 0, cubeVAO, lightingShader);
       // white_color2(130, 0.8, 100, -4 , 0, 0, 0, 0, 0, cubeVAO, lightingShader);

        //road side 1

      /*  for (int i = 0; i <= 100; i++)
        {
            black_color(10, 1, 6, -4 + i, 0, 0.6, 0, 0, 0, cubeVAO, lightingShader);
            white_color(5, 0.01, 0.2, -4 + i, 0.1, 0.9, 0, 0, 0, cubeVAO, lightingShader);
        }*/



        ////road side 2
        //for (int i = 0; i <= 60; i++)
        //{
        //    black_color(10, 1, 6, -4 + i, 0, 1.6, 0, 0, 0, cubeVAO, lightingShader);
        //    white_color(5, 0.01, 0.2, -4 + i, 0.1, 1.9, 0, 0, 0, cubeVAO, lightingShader);
        //}
        
        ////road piller
        //for (int i = 0; i <= 60; i+=2)
        //{
        //    white_color(1, 20, 1, -4+i, 0.1, 1.4, 0, 0, 0, cubeVAO, lightingShader);
        //    white_color(1, 1, 9.5, -4+i, 2.1, 0.6, 30, 0, 0, cubeVAO, lightingShader);
        //    white_color(1, 1, 9.5, -4+i, 1.63, 1.5, -30, 0, 0, cubeVAO, lightingShader);
        //}

        ////rail track floor
       //  white_color(600, 1, 30, -4, 2.1,0.0, 0, 0, 0, cubeVAO, lightingShader);
        white_color(410, 6, 1, 15.5, 2.1, 0, -10, 0, 0, cubeVAO, lightingShader);
        white_color(410, 6, 1, 15.5, 2.1, 3, 10, 0, 0, cubeVAO, lightingShader);

        for (int i = 1; i <= 800; i++)
        {
            railroad_ties_color(1, 0.3, 5, 0.1 * i - 4.0, 2.2, 0.7, 0, 0, 0, cubeVAO, lightingShader);
            railroad_ties_color(1, 0.3, 5, 0.1 * i - 4.0, 2.2, 2.1, 0, 0, 0, cubeVAO, lightingShader);
            i += 1;
        }
       
        
        chocolate_color(800, 1.5, 1, -4, 2.2, 0.6, 0, 0, 0, cubeVAO, lightingShader);
        chocolate_color(800, 1.5, 1, -4, 2.2, 1.2, 0, 0, 0, cubeVAO, lightingShader);

        //rail track 2
        chocolate_color(800, 1.5, 1, -4, 2.2, 2, 0, 0, 0, cubeVAO, lightingShader);
        chocolate_color(800, 1.5, 1, -4, 2.2, 2.6, 0, 0, 0, cubeVAO, lightingShader);

        
        ////platform
        //white_color(195, 3, -30, -4, 2.1, 0, 0, 0, 0, cubeVAO, lightingShader);
        //white_color(195, 3, 30, -4, 2.1, 3, 0, 0, 0, cubeVAO, lightingShader);

       
      

      /* for (int i = 2, j = 1; i < 20; i += 2, j += 1)
       {
           white_color(3, 1, 15, 0.8 + (i * 0.1), 0.1 + (j * 0.1), 8.0, 0, 0, 0, cubeVAO, lightingShader);
       }
       for (int i = 2, j = 1; i < 24; i += 2, j += 1)
       {
           white_color(15, 1, 3, 2.5, 1.0 + (j * 0.1), 7.9 - (i * 0.1), 0, 0, 0, cubeVAO, lightingShader);
       }*/

      // wall_color(63, 30, 1, -3.8, 2.4, 5.8, 0, 0, 0, cubeVAO, lightingShader);
      //wall_color(1, 30, -20, -3.8, 2.4, 5.8, 0, 0, 0, cubeVAO, lightingShader);
       //wall_color(1, 30, -20, -1, 2.4, 5.8, 0, 0, 0, cubeVAO, lightingShader);
      /*
       wall_color(40, 30, 1, 4, 2.4, 5.8, 0, 0, 0, cubeVAO, lightingShader);

       wall_color(10, 30, 1,7, 2.4, 3.8, 0, 0, 0, cubeVAO, lightingShader);
       wall_color(10, -5, 1,6, 5.4, 3.8, 0, 0, 0, cubeVAO, lightingShader);

       //wall_color(10, 30, 1, -2, 2.4, 3.8, 0, 0, 0, cubeVAO, lightingShader);

       wall_color(1, 30, -20, 8, 2.4, 5.8, 0, 0, 0, cubeVAO, lightingShader);
       */

     

       ////ticket counter
       //wall_color(1, 30, -6,6, 2.4, 5.8, 0, 0, 0, cubeVAO, lightingShader);
       //wall_color(1, 30, -7,6, 2.4, 4.5, 0, 0, 0, cubeVAO, lightingShader);
       //
       //wall_color(1, -10, 14, 6, 5.4, 4.5, 0, 0, 0, cubeVAO, lightingShader);
       //wall_color(1, 10, 14, 6, 2.4, 4.5, 0, 0, 0, cubeVAO, lightingShader);

       /*
       //passenger stand line at counter
       white_color(-16, 0.5, 0.5, 5.8, 3.4, 4.5, 0, 0, 0, cubeVAO, lightingShader);
       white_color(-16, 0.5, 0.5, 5.8, 3.4, 5.1, 0, 0, 0, cubeVAO, lightingShader);

       white_color(-10, 0.5, 0.5, 5.8, 3.4, 5.1, 0, 0, 90, cubeVAO, lightingShader);
       white_color(-10, 0.5, 0.5, 5.8, 3.4, 4.5, 0, 0, 90, cubeVAO, lightingShader);

       white_color(-10, 0.5, 0.5, 5.3, 3.4, 5.1, 0, 0, 90, cubeVAO, lightingShader);
       white_color(-10, 0.5, 0.5, 5.3, 3.4, 4.5, 0, 0, 90, cubeVAO, lightingShader);

       white_color(-10, 0.5, 0.5, 4.8, 3.4, 5.1, 0, 0, 90, cubeVAO, lightingShader);
       white_color(-10, 0.5, 0.5, 4.8, 3.4, 4.5, 0, 0, 90, cubeVAO, lightingShader);

       white_color(-10, 0.5, 0.5, 4.3, 3.4, 5.1, 0, 0, 90, cubeVAO, lightingShader);
       white_color(-10, 0.5, 0.5, 4.3, 3.4, 4.5, 0, 0, 90, cubeVAO, lightingShader);
       */

       ////platform roof
       //chocolate_color(119, 1, -21, -3.8, 5.4, 5.9, 0, 0, 0, cubeVAO, lightingShader);
       //chocolate_color(119, 1, -21, -3.8, 5.4, -0.5, 0, 0, 0, cubeVAO, lightingShader);

  

       /*
       //2nd platform brench
      
       bench(1, 1, 1, 0, 0, 0, 0, 0, 0, cubeVAO, lightingShader);
       bench(1, 1, 1, 5, 0, 0, 0, 0, 0, cubeVAO, lightingShader);
       */


        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

       //2nd side

        //watch tower

        red_color(1, 100, 1, 9.5+3+50+10, 0.01, 10-1, -4,0,0,cubeVAO, lightingShader);
        red_color(1, 100, 1, 9.5+6 + 50 + 10, 0.01, 10 - 1, -4,0,0,cubeVAO, lightingShader);
        red_color(1, 100, 1, 9.5+3 + 50 + 10, 0.01, 7 - 1, 4,0,0,cubeVAO, lightingShader);
        red_color(1, 100, 1, 9.5+6 + 50 + 10, 0.01, 7 - 1, 4,0,0,cubeVAO, lightingShader);

        white_color(1, 30, 1, 9.5 + 3 + 50 + 10, 0.01 + 1.5, 9.9 - 1, -10, 0, -90, cubeVAO, lightingShader);
        white_color(1, 28, 1, 9.5 + 6 + 50 + 10, 0.01 + 1.5, 9.9 - 1, -90, 0, 0, cubeVAO, lightingShader);
        white_color(1, 28, 1, 9.5 + 3 + 50 + 10, 0.01 + 1.5, 7 + 0.2 - 1, 90, 0, 0, cubeVAO, lightingShader);
        white_color(1, 30, 1, 9.5 + 6 + 50 + 10, 0.01 + 1.5, 7 + 0.1 - 1, 0, 0, 90, cubeVAO, lightingShader);

        white_color(1, 30, 1, 9.5 + 3 + 50 + 10, 0.01 + 5, 9.9-0.25 - 1, -10, 0, -90, cubeVAO, lightingShader);
        white_color(1, 22, 1, 9.5 + 6 + 50 + 10, 0.01 + 5, 9.9-0.25 - 1, -90, 0, 0, cubeVAO, lightingShader);
        white_color(1, 23, 1, 9.5 + 3 + 50 + 10, 0.01 + 5, 7 + 0.2+0.2 - 1, 90, 0, 0, cubeVAO, lightingShader);

        white_color(1, 30, 1, 9.5 + 6 + 50 + 10, 0.01 + 5, 7 + 0.1+0.25 - 1, 0, 0, 90, cubeVAO, lightingShader);
       

        white_color(1, 34, 20, 9.5 + 6+0.2 + 50 + 10, 10, 7 + 0.1+0.25+0.2 - 1, 0, 0, 90, cubeVAO, lightingShader);
        white_color(1, 34, 10, 9.5 + 6+0.2 + 50 + 10, 10, 7 + 0.1+0.25+0.2 - 1, -90, 0, 90, cubeVAO, lightingShader);
        white_color(1, 24, 10, 9.5 + 6+0.2 + 50 + 10, 10, 7 + 0.1+0.25+0.2+2 - 1, -90, 0, 90, cubeVAO, lightingShader);
        white_color(1, 20, 10, 9.5 + 6+0.2 + 50 + 10, 10, 7 + 0.1+0.25+0.2 - 1, -90, 0, 180, cubeVAO, lightingShader);
        white_color(1, 20, 10, 9.5 + 6+0.2-3.3 + 50 + 10, 10, 7 + 0.1+0.25+0.2 - 1, -90, 0, 180, cubeVAO, lightingShader);

        white_color(1,100, 1, 9.5 + 6+0.2-3.3+1 + 50 + 10, 0.1, 7 + 0.1+0.25+0.2+2.5+1 - 1, -10, 0, 0, cubeVAO, lightingShader);
        white_color(1,100, 1, 9.5 + 6+0.2-3.3+0.3 + 50 + 10, 0.1, 7 + 0.1+0.25+0.2+2.5+1 - 1, -10, 0, 0, cubeVAO, lightingShader);
        
        for (int i = 1; i < 10; i++)
        {
            white_color(7.1, 1, 0.6, 9.5 + 6 + 0.2 - 3.3 + 0.3 + 50 + 10, 0.1+i, 7 + 0.1 + 0.25 + 0.2 + 2.5 + 1-(i*0.17) - 1, 0, 0, 0, cubeVAO, lightingShader);
        }
        white_color(1,15, 1,12.3 + 50 + 10, 0.1 + 10.5, 7 + 0.1+0.25+0.2+1.9 - 1, 0, 0, 0, cubeVAO, lightingShader);
        white_color(1,15, 1,12.3+3.3 + 50 + 10, 0.1 + 10.5, 7 + 0.1+0.25+0.2+1.9 - 1, 0, 0, 0, cubeVAO, lightingShader);
        white_color(1,15, 1,12.3+3.3 + 50 + 10, 0.1 + 10.5, 7 + 0.1+0.25+0.2-0.1 - 1, 0, 0, 0, cubeVAO, lightingShader);
        white_color(1, 15, 1, 12.3 + 50 + 10, 0.1 + 10.5, 7 + 0.1 + 0.25 + 0.2-0.1 - 1, 0, 0, 0, cubeVAO, lightingShader);
        white_color(1, 34, 20, 9.5 + 6 + 0.2 + 50 + 10, 10+2, 7 + 0.1 + 0.25 + 0.2 - 1, 0, 0, 90, cubeVAO, lightingShader);

        ///watch tower 2

        red_color(1, 100, 1, 9.5 + 3, 0.01, 10, -4, 0, 0, cubeVAO, lightingShader);
        red_color(1, 100, 1, 9.5 + 6, 0.01, 10, -4, 0, 0, cubeVAO, lightingShader);
        red_color(1, 100, 1, 9.5 + 3, 0.01, 7, 4, 0, 0, cubeVAO, lightingShader);
        red_color(1, 100, 1, 9.5 + 6, 0.01, 7, 4, 0, 0, cubeVAO, lightingShader);

        white_color(1, 30, 1, 9.5 + 3, 0.01 + 1.5, 9.9, -10, 0, -90, cubeVAO, lightingShader);
        white_color(1, 28, 1, 9.5 + 6, 0.01 + 1.5, 9.9, -90, 0, 0, cubeVAO, lightingShader);
        white_color(1, 28, 1, 9.5 + 3, 0.01 + 1.5, 7 + 0.2, 90, 0, 0, cubeVAO, lightingShader);
        white_color(1, 30, 1, 9.5 + 6, 0.01 + 1.5, 7 + 0.1, 0, 0, 90, cubeVAO, lightingShader);

        white_color(1, 30, 1, 9.5 + 3, 0.01 + 5, 9.9 - 0.25, -10, 0, -90, cubeVAO, lightingShader);
        white_color(1, 22, 1, 9.5 + 6, 0.01 + 5, 9.9 - 0.25, -90, 0, 0, cubeVAO, lightingShader);
        white_color(1, 23, 1, 9.5 + 3, 0.01 + 5, 7 + 0.2 + 0.2, 90, 0, 0, cubeVAO, lightingShader);

        white_color(1, 30, 1, 9.5 + 6, 0.01 + 5, 7 + 0.1 + 0.25, 0, 0, 90, cubeVAO, lightingShader);


        white_color(1, 34, 20, 9.5 + 6 + 0.2, 10, 7 + 0.1 + 0.25 + 0.2, 0, 0, 90, cubeVAO, lightingShader);
        white_color(1, 34, 10, 9.5 + 6 + 0.2, 10, 7 + 0.1 + 0.25 + 0.2, -90, 0, 90, cubeVAO, lightingShader);
        white_color(1, 24, 10, 9.5 + 6 + 0.2, 10, 7 + 0.1 + 0.25 + 0.2 + 2, -90, 0, 90, cubeVAO, lightingShader);
        white_color(1, 20, 10, 9.5 + 6 + 0.2, 10, 7 + 0.1 + 0.25 + 0.2, -90, 0, 180, cubeVAO, lightingShader);
        white_color(1, 20, 10, 9.5 + 6 + 0.2 - 3.3, 10, 7 + 0.1 + 0.25 + 0.2, -90, 0, 180, cubeVAO, lightingShader);

        white_color(1, 100, 1, 9.5 + 6 + 0.2 - 3.3 + 1, 0.1, 7 + 0.1 + 0.25 + 0.2 + 2.5 + 1, -10, 0, 0, cubeVAO, lightingShader);
        white_color(1, 100, 1, 9.5 + 6 + 0.2 - 3.3 + 0.3, 0.1, 7 + 0.1 + 0.25 + 0.2 + 2.5 + 1, -10, 0, 0, cubeVAO, lightingShader);

        for (int i = 1; i < 10; i++)
        {
            white_color(7.1, 1, 0.6, 9.5 + 6 + 0.2 - 3.3 + 0.3, 0.1 + i, 7 + 0.1 + 0.25 + 0.2 + 2.5 + 1 - (i * 0.17), 0, 0, 0, cubeVAO, lightingShader);
        }
        white_color(1, 15, 1, 12.3, 0.1 + 10.5, 7 + 0.1 + 0.25 + 0.2 + 1.9, 0, 0, 0, cubeVAO, lightingShader);
        white_color(1, 15, 1, 12.3 + 3.3, 0.1 + 10.5, 7 + 0.1 + 0.25 + 0.2 + 1.9, 0, 0, 0, cubeVAO, lightingShader);
        white_color(1, 15, 1, 12.3 + 3.3, 0.1 + 10.5, 7 + 0.1 + 0.25 + 0.2 - 0.1, 0, 0, 0, cubeVAO, lightingShader);
        white_color(1, 15, 1, 12.3, 0.1 + 10.5, 7 + 0.1 + 0.25 + 0.2 - 0.1, 0, 0, 0, cubeVAO, lightingShader);
        white_color(1, 34, 21 , 9.5 + 6 + 0.2, 10 + 2, 7 + 0.1 + 0.25 + 0.10, 0, 0, 90, cubeVAO, lightingShader);


        //cout << camera.Position.x << " " << camera.Position.y << " " << camera.Position.z << endl;

        /*red_color(1, 15, 1, 9.5+3, 0.01+1.5, 10, 0, 0, 0, cubeVAO, lightingShader);
        red_color(1, 15, 1, 9.5 + 6, 0.01+1.5, 10, 0, 0, 0, cubeVAO, lightingShader);
        red_color(1, 15, 1, 9.5+3, 0.01+1.5, 7, 0, 0, 0, cubeVAO, lightingShader);
        red_color(1, 15, 1, 9.5 + 6, 0.01+1.5, 7, 0, 0, 0, cubeVAO, lightingShader);

        red_color(1, 30, 1, 9.5+3, 0.01 + 1.5, 10, 0, 0, -90, cubeVAO, lightingShader);
        red_color(1, 30, 1, 9.5 + 6, 0.01 + 1.5, 10, -90, 0, 0, cubeVAO, lightingShader);
        red_color(1, 30, 1, 9.5+3, 0.01 + 1.5, 7, 90, 0, 0, cubeVAO, lightingShader);
        red_color(1, 30, 1, 9.5 + 6, 0.01 + 1.5, 7, 0, 0, 90, cubeVAO, lightingShader);

        white_color(1, 15, 1, 9.5 + 3, 0.01+3, 10, -3, 0, 0, cubeVAO, lightingShader);
        white_color(1, 15, 1, 9.5 + 6, 0.01+3, 10, -3, 0, 0, cubeVAO, lightingShader);
        white_color(1, 15, 1, 9.5 + 3, 0.01+3, 7, 3, 0, 0, cubeVAO, lightingShader);
        white_color(1, 15, 1, 9.5 + 6, 0.01+3, 7, 3, 0, 0, cubeVAO, lightingShader);

        red_color(1, 15, 1, 9.5 + 3, 0.01 + 4.5, 10, -6, 0, 0, cubeVAO, lightingShader);
        red_color(1, 15, 1, 9.5 + 6, 0.01 + 4.5, 10, -6, 0, 0, cubeVAO, lightingShader);
        red_color(1, 15, 1, 9.5 + 3, 0.01 + 4.5, 7, 6, 0, 0, cubeVAO, lightingShader);
        red_color(1, 15, 1, 9.5 + 6, 0.01 + 4.5, 7, 6, 0, 0, cubeVAO, lightingShader);*/

       //train 1

        //train_wheel(5, 5, 5, 7, 7, 7,0,90,0, 1.0, 0.0, 0.0, ourShader, wheel);
       // train_wheel(0.4, 0.4, 0.4,0+2, -4, -5, 0, 90, 0, 0.5, 0.5, 0.5, ourShader, wheel);
      
       //cout<<train_start<<" "<< train_start_release<<" "<<train_reverse_start<<" "<<train_reverse_start_release<<endl;
        
        
       if (train_start)
        {
           
           if (t < 8)
           {
               t += 1;
           }
           else
           {
               t = 8;
           }
          
            if (carPosition.x > 60)
            {
                train_start = false;
                t = 1.0;
            }

           
            

          // wheelRotation += (carSpeed * t) * deltaTime;
            wheelRotation += 60;
           /*if (wheelRotation > 360.0f) {
               wheelRotation -= 360.0f;
           }*/
            if (wheelRotation <= 360)
            {
               
                train(1, 1, 1, 0+ carPosition.x, 0, 0, 0, 0, wheelRotation, cubeVAO, lightingShader, wheel, ourShader);
               // train_door_translate(1, 1, 1, 0 + carPosition.x, 0, 0, 0, 0, wheelRotation, cubeVAO, lightingShader);
              
            }
            else
            {
                //wheelRotation += 100;

                carPosition.x += (carSpeed * t) * deltaTime;
                train(1, 1, 1, 0 + carPosition.x, 0, 0, 0, 0, wheelRotation, cubeVAO, lightingShader, wheel, ourShader);
             
            }
           
           
         
        }
        else if (train_reverse_start && !train_reverse_start_release)
        {

           if (t < 8)
           {
               t += 1;
           }
           else
           {
               t = 8;
           }

           wheelRotation += 60;
           /*wheelRotation -= (carSpeed*t) * deltaTime;
           if (wheelRotation > 360.0f) {
               wheelRotation -= 360.0f;
           }*/
           if (carPosition.x <=2)
           {
               train_reverse_start = false;
               t = 1.0;
           }
          /* if (carPosition.x < -3)
           {
               train_reverse_start = false;
               t = 1.0;
           }*/

           if (wheelRotation <= 360)
           {
               train(1, 1, 1, 0 + carPosition.x, 0, 0, 0, 0, wheelRotation, cubeVAO, lightingShader, wheel, ourShader);
              // train_door_translate(1, 1, 1, 0 + carPosition.x, 0, 0, 0, 0, wheelRotation, cubeVAO, lightingShader);
             
           }
           else
           {
               carPosition.x -= (carSpeed * t) * deltaTime;
               train(1, 1, 1, 0 + carPosition.x, 0, 0, 0, 0, wheelRotation, cubeVAO, lightingShader, wheel, ourShader);
             
           }
         

        }
        else if (train_start_release)
       {




           if (t <= 1.0)
           {
               t = 1.0;
           }
           else
           {
               t--;
           }

           if (t > 1.0)
           {
               wheelRotation += (carSpeed / t) * deltaTime;
               if (wheelRotation > 360.0f) {
                   wheelRotation -= 360.0f;
               }

               carPosition.x += (carSpeed * t) * deltaTime;

           }
           train(1, 1, 1, 0 + carPosition.x, 0, 0, 0, 0, wheelRotation, cubeVAO, lightingShader, wheel, ourShader);
          // train_door_translate(1, 1, 1, 0 + carPosition.x, 0, 0, 0, 0, wheelRotation, cubeVAO, lightingShader);

       }
       else if (train_reverse_start_release)
       {

       

           if (t <= 1.0)
           {
               t = 1.0;
           }
           else
           {
               t--;
           }

           if (t > 1.0)
           {
               wheelRotation -= (carSpeed / t) * deltaTime;
               if (wheelRotation > 360.0f) {
                   wheelRotation -= 360.0f;
               }

               carPosition.x -= (carSpeed * t) * deltaTime;

           }


           train(1, 1, 1, 0 + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader, wheel, ourShader);
           //train_door_translate(1, 1, 1, 0 + carPosition.x, 0, 0, 0, 0, wheelRotation, cubeVAO, lightingShader);

        }
       else
       {
           train(1, 1, 1, 0 + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader, wheel, ourShader);
          
       }

      //  train(1, 1, 1, 0 , 0, 0, 0, 0, 0, cubeVAO, lightingShader, wheel, ourShader);
      

      // train(1, 1, 1, 0, 0, 2, 0, 0, 0, cubeVAO, lightingShader);

     /*  overBridge(1, 1, 1, 0, 0, 0, 0, 0, 0, cubeVAO, lightingShader);
       overBridge(1, 1, 1, 0, 0, 6, 0, 0, 0, cubeVAO, lightingShader);*/
       /*
       wall_color(13, 1, 75, 12.9 + 0.5, 5.8, -2, 0, 0, 0, cubeVAO, lightingShader);
       
       wall_color(0.5, 10, 13, 12.9 + 0.5, 5.8, -2, 0, 90, 0, cubeVAO, lightingShader);
       wall_color(-75, 10, 0.1, 14.7, 5.8, -2, 0, 90, 0, cubeVAO, lightingShader);
       wall_color(0.5, 10, 13, 12.9 + 0.5, 5.8, 5.5, 0, 90, 0, cubeVAO, lightingShader);
       
       wall_color(0.5, 10, 45, 12.9 + 0.5, 5.8, 4.0, 0, 180, 0, cubeVAO, lightingShader);
       wall_color(14, 1, 76, 12.9 + 0.5, 8.3, -2, 0, 0, 0, cubeVAO, lightingShader);*/
      

       //road side scenario
    

       //wall_strip(1, 1, 1, 3, 4, 0, 0, 90, 0, cubeVAO, lightingShader);
       
       /*

       //other side

        //platform
       white_color(145, 3, -30, -4+100, 2.1, 0, 0, 0, 0, cubeVAO, lightingShader);
       white_color(145, 3, 30, -4 + 100, 2.1, 3, 0, 0, 0, cubeVAO, lightingShader);


       //stair

       white_color(18.5, 1, 1, 1 + 100, 0.1, 9.4, 0, 0, 33, cubeVAO, lightingShader);
       white_color(18.5, 1, 1, 1 + 100, 0.1, 8.0, 0, 0, 33, cubeVAO, lightingShader);

       white_color(18.5, 1, 1, 1 + 100, 1.1, 9.4, 0, 0, 33, cubeVAO, lightingShader);
       white_color(18.5, 1, 1, 1 + 100, 1.1, 8.0, 0, 0, 33, cubeVAO, lightingShader);

       white_color(15, 1, 15, 2.5 + 100, 1.1, 8.0, 0, 0, 0, cubeVAO, lightingShader);


       white_color(1, 1, -25, 3.9 + 100, 1.12, 8, 28, 0, 0, cubeVAO, lightingShader);
       white_color(1, 1, -25, 2.5 + 100, 1.12, 8, 28, 0, 0, cubeVAO, lightingShader);

       white_color(1, 1, -25, 3.9 + 100, 2.12, 8, 28, 0, 0, cubeVAO, lightingShader);
       white_color(1, 1, -25, 2.5 + 100, 2.12, 8, 28, 0, 0, cubeVAO, lightingShader);

       white_color(1, 11, 1, 3.9 + 100, 0.01, 9.4, 0, 0, 0, cubeVAO, lightingShader);
       white_color(1, 11, 1, 3.9 + 100, 0.01, 8, 0, 0, 0, cubeVAO, lightingShader);
       white_color(1, 11, 1, 2.5 + 100, 0.01, 9.4, 0, 0, 0, cubeVAO, lightingShader);
       white_color(1, 11, 1, 2.5 + 100, 0.01, 8.0, 0, 0, 0, cubeVAO, lightingShader);


       white_color(1, 9.84, 1, 1.1 + 100, 0.3, 9.4, 0, 0, 0, cubeVAO, lightingShader);
       white_color(1, 9.84, 1, 1.1 + 100, 0.3, 8, 0, 0, 0, cubeVAO, lightingShader);

       white_color(1, 12, 1, 2.5 + 100, 1.0, 9.4, 0, 0, 0, cubeVAO, lightingShader);
       white_color(1, 12, 1, 2.5 + 100, 2, 6, 0, 0, 0, cubeVAO, lightingShader);

       white_color(1, 12, 1, 3.9 + 100, 2, 6, 0, 0, 0, cubeVAO, lightingShader);

       white_color(1, 12, 1, 2.5 + 100, 1.0, 8, 0, 0, 0, cubeVAO, lightingShader);
       white_color(1, 12, 1, 3.9 + 100, 1.0, 8, 0, 0, 0, cubeVAO, lightingShader);
       white_color(1, 12, 1, 3.9 + 100, 1.0, 9.4, 0, 0, 0, cubeVAO, lightingShader);

       white_color(14, 1, 1, 2.55 + 100, 2.1, 9.4, 0, 0, 0, cubeVAO, lightingShader);
       white_color(14, 1, 1, 3.9 + 100, 2.1, 9.4, 0, 90, 0, cubeVAO, lightingShader);


       for (int i = 2, j = 1; i < 20; i += 2, j += 1)
       {
           white_color(3, 1, 15, 0.8 + (i * 0.1) + 100, 0.1 + (j * 0.1), 8.0, 0, 0, 0, cubeVAO, lightingShader);
       }
       for (int i = 2, j = 1; i < 24; i += 2, j += 1)
       {
           white_color(15, 1, 3, 2.5 + 100, 1.0 + (j * 0.1), 7.9 - (i * 0.1), 0, 0, 0, cubeVAO, lightingShader);
       }

       wall_color(63, 30, 1, -3.8 + 100, 2.4, 5.8, 0, 0, 0, cubeVAO, lightingShader);
       wall_color(1, 30, -20, -3.8 + 100, 2.4, 5.8, 0, 0, 0, cubeVAO, lightingShader);
       wall_color(1, 30, -20, -1 + 100, 2.4, 5.8, 0, 0, 0, cubeVAO, lightingShader);

       wall_color(40, 30, 1, 4 + 100, 2.4, 5.8, 0, 0, 0, cubeVAO, lightingShader);
       wall_color(1, 30, -20, 8 + 100, 2.4, 5.8, 0, 0, 0, cubeVAO, lightingShader);
       wall_color(1, 30, -20, 6 + 100, 2.4, 5.8, 0, 0, 0, cubeVAO, lightingShader);

       //platform roof
       chocolate_color(119, 1, -21, -3.8 + 100, 5.4, 5.9, 0, 0, 0, cubeVAO, lightingShader);





       for (int t = 0; t <= 6; t += 3)
       {
           for (int j = 0; j <= 2; j += 2)
           {
               for (int i = 0; i < 360; i++)
               {
                   black_color(.9, .9, 0.2, 5 + j - t + 100, 2.4, 1.98, 0, 0, 0 + i, cubeVAO, lightingShader);
                   black_color(.4, .4, 0.6, 5 + j - t + 100, 2.4, 1.981, 0, 0, 0 + i, cubeVAO, lightingShader);


                   black_color(.4, .4, 0.6, 5 + j - t + 100, 2.4, 2.65, 0, 0, 0 + i, cubeVAO, lightingShader);
                   black_color(.9, .9, 0.2, 5 + j - t + 100, 2.4, 2.7, 0, 0, 0 + i, cubeVAO, lightingShader);
               }

           }
           white_color2(25, 1.2, 0.3, 4.8 - t + 100, 2.45, 1.95, 0, 0, 0, cubeVAO, lightingShader);
           white_color2(25, 1.2, 0.3, 4.8 - t + 100, 2.45, 2.72, 0, 0, 0, cubeVAO, lightingShader);

           white_color2(25, 0.3, -11, 4.8 - t + 100, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);

           white_color2(4, 15, 0.3, 4.8 - t + 100, 2.55, 1.8, 0, 0, 0, cubeVAO, lightingShader);
           white_color2(4, 15, 0.3, 5.6 - t + 100, 2.55, 1.8, 0, 0, 0, cubeVAO, lightingShader);
           white_color2(6, 15, 0.3, 6.4 - t + 100, 2.55, 1.8, 0, 0, 0, cubeVAO, lightingShader);

           white_color2(8, 7, 0.3, 4.8 - t + 100, 2.55, 1.8, 0, 0, 0, cubeVAO, lightingShader);
           white_color2(8, 7, 0.3, 5.6 - t + 100, 2.55, 1.8, 0, 0, 0, cubeVAO, lightingShader);

           white_color2(8, -4, 0.3, 4.8 - t + 100, 4.05, 1.8, 0, 0, 0, cubeVAO, lightingShader);
           white_color2(8, -4, 0.3, 5.6 - t + 100, 4.05, 1.8, 0, 0, 0, cubeVAO, lightingShader);

           // white_color2(25, 15, 0.3, 4.8 - t, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);

           white_color2(4, 15, 0.3, 4.8 - t + 100, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);
           white_color2(4, 15, 0.3, 5.6 - t + 100, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);
           white_color2(6, 15, 0.3, 6.4 - t + 100, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);

           white_color2(8, 7, 0.3, 4.8 - t + 100, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);
           white_color2(8, 7, 0.3, 5.6 - t + 100, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);

           white_color2(8, -4, 0.3, 4.8 - t + 100, 4.05, 2.9, 0, 0, 0, cubeVAO, lightingShader);
           white_color2(8, -4, 0.3, 5.6 - t + 100, 4.05, 2.9, 0, 0, 0, cubeVAO, lightingShader);


           //white_color2(25, 0.3, -3, 4.8 - t, 4.55, 2.65, 0, 0, 0, cubeVAO, lightingShader);
           white_color2(25, 0.3, -4, 4.8 - t + 100, 4.03, 2.92, 30, 0, 0, cubeVAO, lightingShader);
           white_color2(25, 0.3, -4, 4.8 - t + 100, 4.05, 1.8, -210, 0, 0, cubeVAO, lightingShader);
           white_color2(25, 0.3, -4.5, 4.8 - t + 100, 4.22, 2.59, 0, 0, 0, cubeVAO, lightingShader);



           if (t == 0)
           {
               white_color2(10, 0.3, -11, 4 - t + 3 + 100, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);

               white_color2(10, 15, 0.3, 4 - t + 3 + 100, 2.55, 1.8, 0, 0, 0, cubeVAO, lightingShader);
               white_color2(2, 15, 0.3, 4 - t + 3 + 100, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);

               white_color2(2, 15, 0.3, 4.8 - t + 3 + 100, 2.55, 1.8, 0, 0, 0, cubeVAO, lightingShader);
               white_color2(2, 15, 0.3, 4.8 - t + 3 + 100, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);



               //white_color2(25, 0.3, -3, 4.8 - t, 4.55, 2.65, 0, 0, 0, cubeVAO, lightingShader);
               white_color2(10, 0.3, -4, 4 - t + 3 + 100, 4.03, 2.92, 30, 0, 0, cubeVAO, lightingShader);
               white_color2(10, 0.3, -4, 4 - t + 3 + 100, 4.05, 1.8, -210, 0, 0, cubeVAO, lightingShader);
               white_color2(10, 0.3, -4.5, 4 - t + 3 + 100, 4.22, 2.59, 0, 0, 0, cubeVAO, lightingShader);

               //train front
               white_color2(0.1, 8, -11, 5 - t + 3 + 100, 2.55, 2.92, 0, 0, 0, cubeVAO, lightingShader);
               white_color2(0.1, -2, -11, 5 - t + 3 + 100, 4.03, 2.92, 0, 0, 0, cubeVAO, lightingShader);
               white_color2(0.1, -4, -4.6, 5 - t + 3 + 100, 4.25, 2.60, 0, 0, 0, cubeVAO, lightingShader);

               white_color2(0.1, 14, -1.5, 5 - t + 3 + 100, 2.55, 1.95, 0, 0, 0, cubeVAO, lightingShader);
               white_color2(0.1, 14, -1.5, 5 - t + 3 + 100, 2.55, 2.93, 0, 0, 0, cubeVAO, lightingShader);

               white_color2(0.1, -8, -3, 5 - t + 3 + 100, 4.03, 2.5, 0, 0, 0, cubeVAO, lightingShader);

               white_color2(0.1, 15, -11, 4 - t + 3 + 100, 2.55, 2.92, 0, 0, 0, cubeVAO, lightingShader);

               for (int i = 0; i < 360; i++)
               {
                   white_color(1, 0.1, .1, 5.01 - t + 3 + 100, 2.83, 2.0, 0, 90, 0 + i, cubeVAO, lightingShader);
                   white_color(1, 0.1, .1, 5.01 - t + 3 + 100, 2.83, 2.75, 0, 90, 0 + i, cubeVAO, lightingShader);
               }
              

           }
           else if (t == 3)
           {
               white_color2(10, 0.3, -11, 4 - t + 3 + 100, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);

               white_color2(2, 15, 0.3, 4 - t + 3 + 100, 2.55, 1.8, 0, 0, 0, cubeVAO, lightingShader);
               white_color2(2, 15, 0.3, 4 - t + 3 + 100, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);

               white_color2(2, 15, 0.3, 4.8 - t + 3 + 100, 2.55, 1.8, 0, 0, 0, cubeVAO, lightingShader);
               white_color2(2, 15, 0.3, 4.8 - t + 3 + 100, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);

               //white_color2(25, 0.3, -3, 4.8 - t, 4.55, 2.65, 0, 0, 0, cubeVAO, lightingShader);
               white_color2(10, 0.3, -4, 4 - t + 3 + 100, 4.03, 2.92, 30, 0, 0, cubeVAO, lightingShader);
               white_color2(10, 0.3, -4, 4 - t + 3 + 100, 4.05, 1.8, -210, 0, 0, cubeVAO, lightingShader);
               white_color2(10, 0.3, -4.5, 4 - t + 3 + 100, 4.22, 2.59, 0, 0, 0, cubeVAO, lightingShader);

               white_color2(0.1, 15, -2, 4 - t + 3 + 100, 2.55, 2.03, 0, 0, 0, cubeVAO, lightingShader);
               white_color2(0.1, 15, -2, 4 - t + 3 + 100, 2.55, 2.92, 0, 0, 0, cubeVAO, lightingShader);
           }
           else if (t == 6)
           {
               white_color2(10, 0.3, -11, 4 - t + 3 + 100, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);

               white_color2(2, 15, 0.3, 4 - t + 3 + 100, 2.55, 1.8, 0, 0, 0, cubeVAO, lightingShader);
               white_color2(2, 15, 0.3, 4 - t + 3 + 100, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);

               white_color2(2, 15, 0.3, 4.8 - t + 3 + 100, 2.55, 1.8, 0, 0, 0, cubeVAO, lightingShader);
               white_color2(2, 15, 0.3, 4.8 - t + 3 + 100, 2.55, 2.9, 0, 0, 0, cubeVAO, lightingShader);

               //white_color2(25, 0.3, -3, 4.8 - t, 4.55, 2.65, 0, 0, 0, cubeVAO, lightingShader);
               white_color2(10, 0.3, -4, 4 - t + 3 + 100, 4.03, 2.92, 30, 0, 0, cubeVAO, lightingShader);
               white_color2(10, 0.3, -4, 4 - t + 3 + 100, 4.05, 1.8, -210, 0, 0, cubeVAO, lightingShader);
               white_color2(10, 0.3, -4.5, 4 - t + 3 + 100, 4.22, 2.59, 0, 0, 0, cubeVAO, lightingShader);

               white_color2(0.1, 15, -2, 4 - t + 3 + 100, 2.55, 2.03, 0, 0, 0, cubeVAO, lightingShader);
               white_color2(0.1, 15, -2, 4 - t + 3 + 100, 2.55, 2.92, 0, 0, 0, cubeVAO, lightingShader);

               white_color2(0.1, -15, -11, 1.8 - t + 3 + 100, 4, 2.9, 0, 0, 0, cubeVAO, lightingShader);
           }


       }
       */


      
     

        /*glm::mat4 modelForSphere = glm::mat4(1.0f);
        modelForSphere = glm::translate(model, glm::vec3(1.5f, 1.2f, 0.5f));
        sphere.drawSphere(lightingShader, modelForSphere);*/

        // also draw the lamp object(s)
        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        

        // we now draw as many light bulbs as we have point lights.
        glBindVertexArray(lightCubeVAO);
        for (unsigned int i = 0; i < 6; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            if (i == 2 || i == 5)
            {
                model = glm::scale(model, glm::vec3(0.5, 0.01, 0.5)); // Make it a smaller cube
            }
            else
            {
                model = glm::scale(model, glm::vec3(2, 0.01, 2)); // Make it a smaller cube
            }
          
            lightingShader.setMat4("model", model);
            //ourShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));
           glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
           
        }

        // draw spot light
        for (unsigned int i = 0; i < 22; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, spotLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.4, 0.2, 1)); // Make it a smaller cube
            ourShader.setMat4("model", model);
            ourShader.setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        }
        for (unsigned int i = 22; i < 31; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, spotLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2, 0.1, -0.5)); // Make it a smaller cube
            ourShader.setMat4("model", model);
            ourShader.setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        }
        
        for (unsigned int i = 31; i < 37; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, spotLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2, 0.1, -0.5)); // Make it a smaller cube
            ourShader.setMat4("model", model);
            ourShader.setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        }


       
        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setVec3("viewPos", camera.Position);
        pointlight1.setUpPointLight(lightingShaderWithTexture);
        pointlight2.setUpPointLight(lightingShaderWithTexture);
        pointlight3.setUpPointLight(lightingShaderWithTexture);
        pointlight4.setUpPointLight(lightingShaderWithTexture);
        pointlight5.setUpPointLight(lightingShaderWithTexture);
        pointlight6.setUpPointLight(lightingShaderWithTexture);
       // pointlight4.setUpPointLight(lightingShaderWithTexture);
        spotlight1.setUpSpotLight(lightingShaderWithTexture);
        spotlight2.setUpSpotLight(lightingShaderWithTexture);
        spotlight3.setUpSpotLight(lightingShaderWithTexture);
        spotlight4.setUpSpotLight(lightingShaderWithTexture);
        spotlight5.setUpSpotLight(lightingShaderWithTexture);
        spotlight6.setUpSpotLight(lightingShaderWithTexture);
        spotlight7.setUpSpotLight(lightingShaderWithTexture);
        spotlight8.setUpSpotLight(lightingShaderWithTexture);
        spotlight9.setUpSpotLight(lightingShaderWithTexture);
        spotlight10.setUpSpotLight(lightingShaderWithTexture);
        spotlight11.setUpSpotLight(lightingShaderWithTexture);
        spotlight12.setUpSpotLight(lightingShaderWithTexture);
        spotlight13.setUpSpotLight(lightingShaderWithTexture);
        spotlight14.setUpSpotLight(lightingShaderWithTexture);
        spotlight15.setUpSpotLight(lightingShaderWithTexture);
        spotlight16.setUpSpotLight(lightingShaderWithTexture);
        spotlight17.setUpSpotLight(lightingShaderWithTexture);
        spotlight18.setUpSpotLight(lightingShaderWithTexture);
        spotlight19.setUpSpotLight(lightingShaderWithTexture);
        spotlight20.setUpSpotLight(lightingShaderWithTexture);
        spotlight21.setUpSpotLight(lightingShaderWithTexture);
        spotlight22.setUpSpotLight(lightingShaderWithTexture);
        spotlight23.setUpSpotLight(lightingShaderWithTexture);
        spotlight24.setUpSpotLight(lightingShaderWithTexture);
        spotlight25.setUpSpotLight(lightingShaderWithTexture);
        spotlight26.setUpSpotLight(lightingShaderWithTexture);
        spotlight27.setUpSpotLight(lightingShaderWithTexture);
        spotlight28.setUpSpotLight(lightingShaderWithTexture);
        spotlight29.setUpSpotLight(lightingShaderWithTexture);
        spotlight30.setUpSpotLight(lightingShaderWithTexture);
        spotlight31.setUpSpotLight(lightingShaderWithTexture);
        spotlight32.setUpSpotLight(lightingShaderWithTexture);
        spotlight33.setUpSpotLight(lightingShaderWithTexture);
        spotlight34.setUpSpotLight(lightingShaderWithTexture);
        spotlight35.setUpSpotLight(lightingShaderWithTexture);
        spotlight36.setUpSpotLight(lightingShaderWithTexture);
        spotlight37.setUpSpotLight(lightingShaderWithTexture);
        spotlight38.setUpSpotLight(lightingShaderWithTexture);



        directionlight1.setUpDirectionalLight(lightingShaderWithTexture);
      

        lightingShaderWithTexture.setMat4("projection", projection);
        lightingShaderWithTexture.setMat4("view", view);

      //  for (int j = 0;j < 100; j++)
      // {
      //     for (int i = 2; i <= 200; i += 2)
      //     {
      //         cube.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(10.3, 0.8, -1, -4 + (j*2), -0.1, 11 - (i / 10.0), 0, 0, 0));
      //         // cube.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(10.3, 0.8, -1, -4, -0.1, 11 -0.2, 0, 0, 0));
      //         // cube.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(10.3, 0.8, -1, -4, -0.1, 11 -0.4, 0, 0, 0));
      //     }

      // }


      //for (int i = 0; i <= 1000; i += 206)
      //{
      //    cube.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(10.3, 0.8, -1, -4+(i/1000.0), -0.1, 11, 0, 0, 0));
      //    // cube.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(10.3, 0.8, -1, -4, -0.1, 11 -0.2, 0, 0, 0));
      //    // cube.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(10.3, 0.8, -1, -4, -0.1, 11 -0.4, 0, 0, 0));
      //}

       // cube.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(10.3, 0.8, -1, -4, -0.1, 11 - 0.2, 0, 0, 0));
        
        //sky
       /* cube42.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(900, 0.2, 50, -10, 5, -30, 0, 0, 0));
        cube42.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(900, 0.2, 500, -10, 5, -30+50, 30, 0, 0));*/

        ////sky
        //cube44.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(800, 0.1,600, -10, 60,-20, 0, 0, 0));//top
        //cube45.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(800, 600,0.1, -10, 0.01,-20, 0, 0, 0));//left
        //cube46.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(800, 600,0.1, -10, 0.01, 20, 0, 0,0));//right
        //cube47.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.1, 600,800, -60, 0.01,-20, 0, 0, 0));//front
        //cube47.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.1, 600 , 800, -10, 0.01, -20, 0, 60, 0));//back 

       //ground texture
        cube.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(365, -10, -285, -4, 0, 11, 0, 0, 0));
        cube.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(380, -10, -285, -4+42.5, 0, 11, 0, 0, 0));

        cube39.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(195, -10, -100, -4 , 0, 21, 0, 0, 0));
        cube32.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(195, 1, -60, -4 , 0, 21, 0, 0, 0));
        cube40.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-60, 1, -60, -4 +19.5, 0, 16, 0, 0, 0));
        cube41.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(610, 1, -100, -4 +19.3, -1, 21, 0, 0, 0));

 /*       cube.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(365, -10, 100, -4, 0, 11, 0, 0, 0));
        cube.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(380, -10, 100, -4 + 42.5, 0, 11, 0, 0, 0));*/
      


        //building
        building_1(1, 1, 1, 0, 0, 0, 0, 0, 0, cubeVAO, lightingShader);
        building_2(1, 1, 1, 4, 0, 0, 0, 0, 0, cubeVAO, lightingShader);

        building_3(1, 1, 1, 8, 0, 0, 0, 0, 0, cubeVAO, lightingShader);



        //building_1_wall texture
        cube4.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 60, 30, -3 , 0.01, -8.8, 0, 0, 0));
        //building_2_wall texture
        cube18.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 60, 30, -3 + 4, 0.01, -8.8, 0, 0, 0));
        //building_3_wall texture
        cube19.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 60, 30, -3 + 8, 0.01, -8.8, 0, 0, 0));

        //building_4_wall texture
        cube34.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 70, 30, -3 + 8+8, 0.01, -8.8, 0, 0, 0));
        //roof
        building4_color(30, 0.2, 30, -3 + 8 + 8, 0.01+7, -8.8, 0, 0, 0, cubeVAO, lightingShader);

        //building_5_wall texture
        cube35.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 70, 30, -3 + 8 + 8+4, 0.01, -8.8, 0, 0, 0));
        //roof
        building5_color(30, 0.2, 30, -3 + 8 + 8+4, 0.01 + 7, -8.8, 0, 0, 0, cubeVAO, lightingShader);
        //builing_6
        cube36.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 70, 30, -3 + 8 + 8 + 4+4, 0.01, -8.8, 0, 0, 0));
        //roof
        building6_color(30, 0.2, 30, -3 + 8 + 8 + 4+4, 0.01 + 7, -8.8, 0, 0, 0, cubeVAO, lightingShader);
        
        //building 4,5,6 repeat

        //building_4_wall texture
        cube34.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 70, 30, -3 , 0.01, -8.8-8, 0, 0, 0));
        cube34.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 70, 30, -3, 0.01+7, -8.8 - 8, 0, 0, 0));
        //roof
        building4_color(30, 0.2, 30, -3 , 0.01 + 14, -8.8-8, 0, 0, 0, cubeVAO, lightingShader);

        //building_5_wall texture
        cube35.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 70, 30, -3 + 4, 0.01, -8.8-8, 0, 0, 0));
        cube35.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 70, 30, -3 + 4, 0.01+7, -8.8-8, 0, 0, 0));
        //roof
        building5_color(30, 0.2, 30, -3 + 4, 0.01 + 14, -8.8-8, 0, 0, 0, cubeVAO, lightingShader);
        //builing_6
        cube36.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 70, 30, -3 + 8, 0.01, -8.8-8, 0, 0, 0));
        cube36.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 70, 30, -3 + 8, 0.01+7, -8.8-8, 0, 0, 0));
        //roof
        building6_color(30, 0.2, 30, -3 + 8, 0.01 + 14, -8.8-8, 0, 0, 0, cubeVAO, lightingShader);


        //building_4_wall texture
        cube34.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 70, 30, -3 , 0.01, -8.8+20, 0, 0, 0));
        //roof
        building4_color(30, 0.2, 30, -3 , 0.01 + 7, -8.8+20, 0, 0, 0, cubeVAO, lightingShader);

        //building_5_wall texture
        cube35.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 70, 30, -3 + 4 , 0.01, -8.8+20, 0, 0, 0));
        //roof
        building5_color(30, 0.2, 30, -3 + 4 , 0.01 + 7, -8.8+20, 0, 0, 0, cubeVAO, lightingShader);
        //builing_6
        cube36.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 70, 30, -3 + 8 , 0.01, -8.8+20, 0, 0, 0));
        //roof
        building6_color(30, 0.2, 30, -3 + 8 , 0.01 + 7, -8.8+20, 0, 0, 0, cubeVAO, lightingShader);



        //building 1,2,3 repeat

        building_2(1, 1, 1, 4+19, 0, -7, 0, 0, 0, cubeVAO, lightingShader);
        building_3(1, 1, 1, 8+20, 0, -7, 0, 0, 0, cubeVAO, lightingShader);
        building_1(1, 1, 1, 0+18, 0, -7, 0, 0, 0, cubeVAO, lightingShader);

        
        //building_2_wall texture
        cube18.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 60, 30, -3 + 4+19, 0.01, -8.8-7, 0, 0, 0));
        //building_3_wall texture
        cube19.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 60, 30, -3 + 8+20, 0.01, -8.8-7, 0, 0, 0));
        //building_1_wall texture
        cube4.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 60, 30, -3+18, 0.01, -8.8 - 7, 0, 0, 0));
        building_2(1, 1, 1, 4+19, 0+6, -7, 0, 0, 0, cubeVAO, lightingShader);
        building_3(1, 1, 1, 8+20, 0+6, -7, 0, 0, 0, cubeVAO, lightingShader);
        building_1(1, 1, 1, 0+18, 0+6, -7, 0, 0, 0, cubeVAO, lightingShader);

        //building_2_wall texture
        cube18.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 60, 30, -3 + 4+19, 0.01+6, -8.8 - 7, 0, 0, 0));
        //building_3_wall texture
        cube19.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 60, 30, -3 + 8+20, 0.01+6, -8.8 - 7, 0, 0, 0));
        //building_1_wall texture
        cube4.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 60, 30, -3+18, 0.01+6, -8.8 - 7, 0, 0, 0));



        pyramidTree.draw(lightingShaderWithTexture);
        pyramidTree2.draw(lightingShaderWithTexture);

        pyramidTree3.draw(lightingShaderWithTexture);
        pyramidTree4.draw(lightingShaderWithTexture);

        pyramidTree5.draw(lightingShaderWithTexture);
        pyramidTree6.draw(lightingShaderWithTexture);

       pyramidTree7.draw(lightingShaderWithTexture);
        pyramidTree8.draw(lightingShaderWithTexture);

        pyramidTree9.draw(lightingShaderWithTexture);
        pyramidTree10.draw(lightingShaderWithTexture);
        pyramidTree11.draw(lightingShaderWithTexture);
        pyramidTree12.draw(lightingShaderWithTexture);


        //car 1
       // red_carWheelRotation += red_carSpeed * deltaTime;
        red_carWheelRotation += 60;
        if (red_carWheelRotation > 360.0f) {
            red_carWheelRotation -= 360.0f;
        }

        if (red_car_forward)
        {
            red_carTranslate += red_carSpeed * deltaTime;
        }
        else
        {
            red_carTranslate -= red_carSpeed * deltaTime;
        }
       
        if (red_carTranslate > 62)
        {
            red_car_forward = false;
        }
        if (red_carTranslate < 0)
        {
            red_car_forward = true;
        }
        
        red_car(1, 1, 1, 0+ red_carTranslate, 0, 0, 0, 0, red_carWheelRotation, cubeVAO, lightingShader, wheel, ourShader);
       
        red_carSpeed = 2;
        
        red_car(1, 1, 1, 0 + red_carTranslate, 0, 0-10.7, 0, 0, 0+ red_carWheelRotation, cubeVAO, lightingShader, wheel, ourShader);
       
        //car 2
       // mint_turqudise_carWheelRotation += mint_turqudise_carSpeed * deltaTime;
        mint_turqudise_carWheelRotation += 60;
        if (mint_turqudise_carWheelRotation > 360.0f) {
            mint_turqudise_carWheelRotation -= 360.0f;
        }

        if (mint_turqudise_car_forward)
        {
            mint_turqudise_carTranslate += mint_turqudise_carSpeed * deltaTime;
        }
        else
        {
            mint_turqudise_carTranslate -= mint_turqudise_carSpeed * deltaTime;
        }

        if (mint_turqudise_carTranslate > 62)
        {
            mint_turqudise_car_forward = false;
        }
        if (red_carTranslate < 0)
        {
            mint_turqudise_car_forward = true;
        }

        mint_turqudise_car(1, 1, 1, 0 + mint_turqudise_carTranslate, 0, 0-5.32, 0, 0, 0+ mint_turqudise_carWheelRotation, cubeVAO, lightingShader, wheel, ourShader);
        mint_turqudise_carSpeed = 2.0;
        mint_turqudise_car(1, 1, 1, 0 + mint_turqudise_carTranslate, 0, 0 - 5.32+7.2, 0, 0, 0 + mint_turqudise_carWheelRotation, cubeVAO, lightingShader, wheel, ourShader);
        /*
        red_color(8, 1, 2.16, -3-0.15, 0.01+0.2-0.01, 0+0.5+0.01-0.007, 0, 0, 0,cubeVAO,lightingShader);
        //red_color(0.02, 2.5, 2.16, -3-0.25+0.75, 0.01+0.2-0.01, 0+0.5+0.01-0.007, 0, 0, 15,cubeVAO,lightingShader);
        light_red_color(0.02, 1.5, 2.16, -3-0.25+0.75, 0.3, 0+0.5+0.01-0.007, 0, 0, 40,cubeVAO,lightingShader);
        light_red_color(0.02, 1.44, 2.16, -3-0.25+0.25, 0.3, 0+0.5+0.01-0.007, 0, 0, -35,cubeVAO,lightingShader);
        red_color(3.27, 0.02, 2.16, -3+0.037+0.044, 0.415, 0 + 0.5 + 0.01 - 0.007, 0, 0, 0, cubeVAO, lightingShader);
      
        red_color(0.08, -1.4, 0.01, -3+0.037+0.044, 0.415, 0 + 0.5 + 0.01 - 0.007 + 0.21, 0, 0, 0, cubeVAO, lightingShader);
        red_color(0.25, -1.4, 0.01, -3+0.037+0.044+0.15, 0.415, 0 + 0.5 + 0.01 - 0.007+0.21, 0, 0, 0, cubeVAO, lightingShader);
        red_color(0.08, -1.4, 0.01, -3+0.037+0.044+0.317, 0.415, 0 + 0.5 + 0.01 - 0.007 + 0.21, 0, 0, 0, cubeVAO, lightingShader);
       
        red_color(0.08, -1.4, 0.01, -3 + 0.037 + 0.044, 0.415, 0 + 0.5 + 0.01 - 0.007, 0, 0, 0, cubeVAO, lightingShader);
        red_color(0.25, -1.4, 0.01, -3 + 0.037 + 0.044 + 0.15, 0.415, 0 + 0.5 + 0.01 - 0.007, 0, 0, 0, cubeVAO, lightingShader);
        red_color(0.08, -1.4, 0.01, -3 + 0.037 + 0.044 + 0.317, 0.415, 0 + 0.5 + 0.01 - 0.007, 0, 0, 0, cubeVAO, lightingShader);

        //back wheel
        wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3, 0.2 - 0.01, 0 + 0.3+0.4, 0, 0, 0));
        wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3, 0.2 - 0.01, 0 + 0.3+0.4, 0, 0, 90));
        wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3, 0.2 - 0.01, 0 + 0.3 + 0.4, 0, 0, 180));
        wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3, 0.2 - 0.01, 0 + 0.3 + 0.4, 0, 0, 270));

        wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3, 0.2 - 0.01, 0.1 + 0.4, 0, 0, 0));
        wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3, 0.2 - 0.01, 0.1 + 0.4, 0, 0, 90));
        wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3, 0.2 - 0.01, 0.1 + 0.4, 0, 0, 180));
        wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3, 0.2 - 0.01, 0.1 + 0.4, 0, 0, 270));
        
        //front wheel
        wheel.drawWheel(ourShader, model_Matrix(0.2 , 0.2, 0.2, -3 + 0.5, 0.2 - 0.01, 0 + 0.3 + 0.4, 0, 0, 0));
        wheel.drawWheel(ourShader, model_Matrix(0.2, 0.2, 0.2, -3 + 0.5, 0.2 - 0.01, 0 + 0.3 + 0.4, 0, 0, 90));
        wheel.drawWheel(ourShader, model_Matrix(0.2 , 0.2, 0.2, -3 + 0.5, 0.2 - 0.01, 0 + 0.3 + 0.4, 0, 0, 180));
        wheel.drawWheel(ourShader, model_Matrix(0.2 , 0.2, 0.2, -3 + 0.5, 0.2-0.01, 0 + 0.3 + 0.4, 0, 0, 270));

        wheel.drawWheel(ourShader, model_Matrix(0.2 , 0.2, 0.2, -3 + 0.5, 0.2 - 0.01, 0.1 + 0.4, 0, 0, 0));
        wheel.drawWheel(ourShader, model_Matrix(0.2 , 0.2, 0.2, -3 + 0.5, 0.2 - 0.01, 0.1 + 0.4, 0, 0, 90));
        wheel.drawWheel(ourShader, model_Matrix(0.2 , 0.2, 0.2, -3 + 0.5, 0.2 - 0.01, 0.1 + 0.4, 0, 0, 180));
        wheel.drawWheel(ourShader, model_Matrix(0.2 , 0.2, 0.2, -3 + 0.5, 0.2 - 0.01, 0.1 + 0.4, 0, 0, 270));*/


        //tree 1
        cylinder.drawSphere(lightingShader, model_Matrix(1,1, 1, 11 + 6 + 9, 0.01, 3 + 4 + 2-11.5, 0, 0, 0));
       // generateUmbrellaCanopyVertices(10, 10, 10, 11 + 6 + 9, 6.3, 3 + 4 + 2-11.5, glm::vec3(0.0f, 1.0f, 0.0f), -90, 0, 0);

        //tree 2
        tree_1(1, 1, 1, 2 + 6 + 9, 0, 0 + 4 + 2-11.5, 0, 0, 0, cubeVAO, lightingShader);
        leaf(0, 0, 0, 2 + 6 + 9+0.5, 1, 0 + 4 + 2-11.5, 0, 0, 0, cubeVAO, lightingShader);
        leaf(0, 0, 0, 0 + 6 + 9, 1, 0 + 4 + 2-11.5, 0, 0, 0, cubeVAO, lightingShader);

        //tree 2
        tree_1(1, 1, 1, 2 + 6 + 7, 0, 0 + 4 + 2 - 16, 0, 0, 0, cubeVAO, lightingShader);
        leaf(0, 0, 0, 2 + 6 +7, 0, 0 + 4 + 2 - 16, 0, 0, 0, cubeVAO, lightingShader);
        leaf(0, 0, 0, 0 + 6 + 7, 0, 0 + 4 + 2 - 16, 0, 0, 0, cubeVAO, lightingShader);
       
        //tree 2
        tree_1(1, 1, 1, 2-5.5, 0, 0 + 4 + 2 - 16, 0, 0, 0, cubeVAO, lightingShader);
        leaf(0, 0, 0, 2 -5.5, 0, 0 + 4 + 2 - 16, 0, 0, 0, cubeVAO, lightingShader);
        leaf(0, 0, 0, 0 -5.5, 0, 0 + 4 + 2 - 16, 0, 0, 0, cubeVAO, lightingShader);


        //tree 2
        tree_1(1, 1, 1, 2 - 5, 0, 0 + 4 + 2 - 16-8, 0, 0, 0, cubeVAO, lightingShader);
        leaf(0, 0, 0, 2 - 5, 0, 0 + 4 + 2 - 16-8, 0, 0, 0, cubeVAO, lightingShader);
        leaf(0, 0, 0, 0 - 5, 0, 0 + 4 + 2 - 16-8, 0, 0, 0, cubeVAO, lightingShader);

        //tree 2
        tree_1(1, 1, 1, 2 +30 , 0, 0 + 4 + 2 - 16 - 8, 0, 0, 0, cubeVAO, lightingShader);
        leaf(0, 0, 0, 2 +30 , 0, 0 + 4 + 2 - 16 - 8, 0, 0, 0, cubeVAO, lightingShader);
        leaf(0, 0, 0, 0 + 30, 0, 0 + 4 + 2 - 16 - 8, 0, 0, 0, cubeVAO, lightingShader);

        //tree 2
        tree_1(1, 1, 1, 2+ 39.5, 0, 0 + 4 + 2 - 16, 0, 0, 0, cubeVAO, lightingShader);
        leaf(0, 0, 0, 2 + 39.5, 0, 0 + 4 + 2 - 16, 0, 0, 0, cubeVAO, lightingShader);
        leaf(0, 0, 0, 0 + 39.5, 0, 0 + 4 + 2 - 16, 0, 0, 0, cubeVAO, lightingShader);

        cube32.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(130, 0.1, 65, -3 + 41.5, 0.01, -8.8-8.7, 0, 0, 0));

        //building
        building_1(1, 1, 1, 0+45, 0, 0, 0, 0, 0, cubeVAO, lightingShader);
        building_2(1, 1, 1, 4+45, 0, 0, 0, 0, 0, cubeVAO, lightingShader);

        building_3(1, 1, 1, 8+45, 0, 0, 0, 0, 0, cubeVAO, lightingShader);



        //building_1_wall texture
        cube4.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 60, 30, -3+45, 0.01, -8.8, 0, 0, 0));
        //building_2_wall texture
        cube18.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 60, 30, -3 + 4+45, 0.01, -8.8, 0, 0, 0));
        //building_3_wall texture
        cube19.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 60, 30, -3 + 8+45, 0.01, -8.8, 0, 0, 0));

        //building_4_wall texture
        cube34.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 70, 30, -3 + 8 + 8+45, 0.01, -8.8, 0, 0, 0));
        //roof
        building4_color(30, 0.2, 30, -3 + 8 + 8+45, 0.01 + 7, -8.8, 0, 0, 0, cubeVAO, lightingShader);

        //building_5_wall texture
        cube35.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 70, 30, -3 + 8 + 8 + 4+45, 0.01, -8.8, 0, 0, 0));
        //roof
        building5_color(30, 0.2, 30, -3 + 8 + 8 + 4+45, 0.01 + 7, -8.8, 0, 0, 0, cubeVAO, lightingShader);
        //builing_6
        cube36.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 70, 30, -3 + 8 + 8 + 4 + 4+45, 0.01, -8.8, 0, 0, 0));
        //roof
        building6_color(30, 0.2, 30, -3 + 8 + 8 + 4 + 4+45, 0.01 + 7, -8.8, 0, 0, 0, cubeVAO, lightingShader);

        //building 4,5,6 repeat

        //building_4_wall texture
        cube34.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 70, 30, -3+55.5, 0.01, -8.8 - 8, 0, 0, 0));
        cube34.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 70, 30, -3+55.5, 0.01 + 7, -8.8 - 8, 0, 0, 0));
        //roof
        building4_color(30, 0.2, 30, -3+55.5, 0.01 + 14, -8.8 - 8, 0, 0, 0, cubeVAO, lightingShader);

        //building_5_wall texture
        cube35.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 70, 30, -3 + 4+55.5+3, 0.01, -8.8 - 8, 0, 0, 0));
        cube35.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 70, 30, -3 + 4+55.5+3, 0.01 + 7, -8.8 - 8, 0, 0, 0));
        //roof
        building5_color(30, 0.2, 30, -3 + 4+55.5+3, 0.01 + 14, -8.8 - 8, 0, 0, 0, cubeVAO, lightingShader);
        //builing_6
        cube36.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 70, 30, -3 + 8+55.5+5, 0.01, -8.8 - 8, 0, 0, 0));
        cube36.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 70, 30, -3 + 8+55.5+5, 0.01 + 7, -8.8 - 8, 0, 0, 0));
        //roof
        building6_color(30, 0.2, 30, -3 + 8+55.5+5, 0.01 + 14, -8.8 - 8, 0, 0, 0, cubeVAO, lightingShader);

         //boatTranslate = 36;
        
        if (boatTranslate_forward)
        {
            boatTranslate -= boatSpeed * deltaTime;

        }
        if(!boatTranslate_forward)
        {
            boatTranslate += boatSpeed * deltaTime;
        }
        if (boatTranslate < -33)
        {
            boatTranslate_forward = false;
        }
        if (boatTranslate >-10)
        {
            boatTranslate_forward = true;
        }
        //cout << boatTranslate << endl;
        boat(1, 1, 1, 21 + 8 + 1, -5.40, 20 + boatTranslate, 0, 0, 0, cubeVAO, lightingShader);
        boat(1, 1, 1, 22 + 9 + 1, -5.40, 16 + boatTranslate, 0, 0, 0, cubeVAO, lightingShader);
       /* if (boatTranslate < 36)
        {
            boatTranslate += boatSpeed * deltaTime;

            boat(1, 1, 1, 21 + 8+1, -5.40, 20- boatTranslate, 0, 0, 0, cubeVAO, lightingShader);
            boat(1, 1, 1, 22 + 9+1, -5.40, 16- boatTranslate, 0, 0, 0, cubeVAO, lightingShader);
        }
        else
        {
            boat(1, 1, 1, 21 + 8+1, -5.40, 20- boatTranslate, 0, 0, 0, cubeVAO, lightingShader);
            boat(1, 1, 1, 22 + 9+1, -5.40, 16- boatTranslate, 0, 0, 0, cubeVAO, lightingShader);
        }*/

       

        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //road side 1
        cube5.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(800, 1, 6, -4 , 0, 0.0, 0, 0, 0));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(800, 1, 6, -4 , 0, 0.6, 0, 0, 0));
        //road side 2 10, 1, 6, -4 + i, 0, 1.6, 0, 0, 0
        cube5.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(800, 1, 6, -4 , 0, 1.6, 0, 0, 0));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(800, 1, 6, -4 , 0, 2.2, 0, 0, 0));

        //road behind building left
        cube5.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(800, 1, 6, -4, 0, 0.0-5, 0, 0, 0));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(800, 1, 6, -4, 0, 0.6-5, 0, 0, 0));
        //road side 2 10, 1, 6, -4 + i, 0, 1.6, 0, 0, 0
        cube5.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(800, 1, 6, -4, -0.01, 1.6-12, 0, 0, 0));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(800, 1, 6, -4, -0.01, 2.2-12, 0, 0, 0));

        //road pillar texture

        for (int i = 0; i <= 80; i += 2)
        {
            if (i >= 37 && i<=44)
            {
                if (i == 38 || i == 40 || i == 42)
                {
                    cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 30, 1, -4 + i, -1, 1.4, 0, 0, 0));
                    cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 1, 9.5, -4 + i, 2.1, 0.6, 30, 0, 0));
                    cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 1, 9.5, -4 + i, 1.63 , 1.5, -30, 0, 0));
                    
                    cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 9.99, 1, -4 + i, 0.1-1, 1.4+1, 0, 0, 0));
                    cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 9.99, 1, -4 + i, 0.1 - 1, 1.4 - 1, 0, 0, 0));

                   cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 9.99, 1, -4 + i, 0.1 - 1, 1.4 + 1-7 , 0, 0, 0));
                   cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 9., 1, -4 + i, 0.1 - 1, 1.4 + 1-12.2 , 0, 0, 0));
                   //cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 9.99, 1, -4 + i, 0.1 - 1, 1.4 - 1-3, 0, 0, 0));
                    
                }
               
            }
            else
            {
                cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 20, 1, -4 + i, 0.1, 1.4, 0, 0, 0));
                cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 1, 9.5, -4 + i, 2.1, 0.6, 30, 0, 0));
                cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 1, 9.5, -4 + i, 1.63, 1.5, -30, 0, 0));

            }
           
            /*white_color(1, 20, 1, -4 + i, 0.1, 1.4, 0, 0, 0, cubeVAO, lightingShader);
            white_color(1, 1, 9.5, -4 + i, 2.1, 0.6, 30, 0, 0, cubeVAO, lightingShader);
            white_color(1, 1, 9.5, -4 + i, 1.63, 1.5, -30, 0, 0, cubeVAO, lightingShader);*/
        }

       //road Bridge 1

        cube49.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(70, 5, 0.5, 32, 0.01, 0.0-5.05, 0, 0, 0));
        cube49.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(70, 5, 0.5, 32, 0.01, 0.0-5.05+1.21, 0, 0, 0));

        //road Bridge 2
        cube49.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(70, 5, 0.5, 32, 0.01, 0.0 - 5.05-5.4, 0, 0, 0));
        cube49.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(70, 5, 0.5, 32, 0.01, 0.0 - 5.05 + 1.21-5.4, 0, 0, 0));
        
        //road Bridge 3

        cube49.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(70, 5, 0.5, 32, 0.01, 0.0 - 5.05+5, 0, 0, 0));
        cube49.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(70, 5, 0.5, 32, 0.01, 0.0 - 5.05 + 1.21+5, 0, 0, 0));

        //road Bridge 4

        cube49.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(70, 5, 0.5, 32, 0.01, 0.0 - 5.05+6.6, 0, 0, 0));
        cube49.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(70, 5, 0.5, 32, 0.01, 0.0 - 5.05 + 1.21+6.6, 0, 0, 0));



        //rail track floor
        cube7.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(800, 1, 30, -4, 2.1, 0.0, 0, 0, 0));

        //grass floor

        cube32.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(170, 1, 90, 15.5, -0.01, 2, 0, 0, 0));
        cube32.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(180, 1, 90, 38.5, -0.01, 2, 0, 0, 0));
       
       
        //tree 1
        cylinder.drawSphere(lightingShader, model_Matrix(1, 0.5, 1, 11+6, 0.01, 3+4+2, 0, 0, 0));
        generateUmbrellaCanopyVertices(10, 10, 10, 11+6, 5.5, 3+4+2, glm::vec3(0.0f, 1.0f, 0.0f), -90, 0, 0);

        //tree 2
        tree_1(1, 1, 1, 2+6, 0, 0+4+2, 0, 0, 0, cubeVAO, lightingShader);
        leaf(0, 0, 0, 2+6, 0, 0+4+2, 0, 0, 0, cubeVAO, lightingShader);
        leaf(0, 0, 0, 0+6, 0, 0+4+2, 0, 0, 0, cubeVAO, lightingShader);

        //tree 1
        cylinder.drawSphere(lightingShader, model_Matrix(1, 0.5, 1, 11 + 6+9, 0.01, 3 + 4 + 2, 0, 0, 0));
        generateUmbrellaCanopyVertices(10, 10, 10, 11 + 6+9, 5.5, 3 + 4 + 2, glm::vec3(0.0f, 1.0f, 0.0f), -90, 0, 0);

        //tree 2
        tree_1(1, 1, 1, 2 + 6+9, 0, 0 + 4 + 2, 0, 0, 0, cubeVAO, lightingShader);
        leaf(0, 0, 0, 2 + 6+9, 0, 0 + 4 + 2, 0, 0, 0, cubeVAO, lightingShader);
        leaf(0, 0, 0, 0 + 6+9, 0, 0 + 4 + 2, 0, 0, 0, cubeVAO, lightingShader);

       


        ////tree 1
        //cylinder.drawSphere(lightingShader, model_Matrix(1, 0.5, 1, 11 + 6+20, 0.01, 3 + 4 + 2, 0, 0, 0));
        //generateUmbrellaCanopyVertices(10, 10, 10, 11 + 6+20, 5.5, 3 + 4 + 2, glm::vec3(0.0f, 1.0f, 0.0f), -90, 0, 0);

        //tree 2
        tree_1(1, 1, 1, 2 + 6+20, 0, 0 + 4 + 2, 0, 0, 0, cubeVAO, lightingShader);
        leaf(0, 0, 0, 2 + 6+20, 0, 0 + 4 + 2, 0, 0, 0, cubeVAO, lightingShader);
        leaf(0, 0, 0, 0 + 6+20, 0, 0 + 4 + 2, 0, 0, 0, cubeVAO, lightingShader);

        //tree 1
        cylinder.drawSphere(lightingShader, model_Matrix(1, 0.5, 1, 11 + 6 + 9+20, 0.01, 3 + 4 + 2, 0, 0, 0));
        generateUmbrellaCanopyVertices(10, 10, 10, 11 + 6 + 9+20, 5.5, 3 + 4 + 2, glm::vec3(0.0f, 1.0f, 0.0f), -90, 0, 0);
       
        //tree 2
        tree_1(1, 1, 1, 2 + 6 + 20+9, 0, 0 + 4 + 2, 0, 0, 0, cubeVAO, lightingShader);
        leaf(0, 0, 0, 2 + 6 + 20+9, 0, 0 + 4 + 2, 0, 0, 0, cubeVAO, lightingShader);
        leaf(0, 0, 0, 0 + 6 + 20+9, 0, 0 + 4 + 2, 0, 0, 0, cubeVAO, lightingShader);

        ////tree 2
        //tree_1(1, 1, 1, 2 + 6+9, 0, 0 + 4 + 2, 0, 0, 0, cubeVAO, lightingShader);
        //leaf(0, 0, 0, 2 + 6+9, 0, 0 + 4 + 2, 0, 0, 0, cubeVAO, lightingShader);
        //leaf(0, 0, 0, 0 + 6+9, 0, 0 + 4 + 2, 0, 0, 0, cubeVAO, lightingShader);

        //river

        cube33.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(60, 1, 285, 32.5, -1, -17.5, 0, 0, 0));
        //cube38.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(60, 1, 285, 32.5, -1, -17.5, 0, 90, 0));

        //cube42.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-1800000,0.1, 1800000, -90,35, -90, 0, 90, 0));

        ///tree sphere 1

        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(6, 6, 6, 13-2+1.7,5.5, 15+0.2, 0, 0, 0));


        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13-1,4.8, 15+0.5, 0, 0, 0));
        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13-1,4.8, 14.5+0.5, 0, 0, 0));
        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13-1-0.5,4.8, 15+0.5, 0, 0, 0));

        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 , 4.8, 15 , 0, 0, 0));
        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 , 4.8, 14.5, 0, 0, 0));
        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 - 0.5, 4.8, 15 , 0, 0, 0));

        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13, 4.8, 15 + 0.5+0.7, 0, 0, 0));
        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13, 4.8, 14.5 + 0.5+0.7, 0, 0, 0));
        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 - 0.5, 4.8, 15 + 0.5+0.7, 0, 0, 0));

        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 - 1+2, 4.8, 15 + 0.5, 0, 0, 0));
        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 - 1+2, 4.8, 14.5 + 0.5, 0, 0, 0));
        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 - 1+2 - 0.5, 4.8, 15 + 0.5, 0, 0, 0));

        cylinder.drawSphere(lightingShader, model_Matrix(1, 1,1, 13, -0.1, 15, 0, 0, 0));
        cylinder.drawSphere(lightingShader, model_Matrix(0.6, 0.4,0.6, 13, 0.1+3.5, 15, 0, 0, 60));
        cylinder.drawSphere(lightingShader, model_Matrix(0.6, 0.4,0.6, 13, 0.1+3.5, 15, 0, 0, -60));
        
        //cube tree 6, 6, 6, 13-2+1.7,5.5, 15+0.2, 0, 0, 0
         tree_1(1, 1, 1, 0, 0.01, 16, 0, 0, 0, cubeVAO, lightingShader);
         leaf(0, 0, 0, 0, 0.01, 16, 0, 0, 0, cubeVAO, lightingShader);
         leaf(0, 0, 0, 0-2, 0.01, 16, 0, 0, 0, cubeVAO, lightingShader);

         //cube tree 6, 6, 6, 13-2+1.7,5.5, 15+0.2, 0, 0, 0
         tree_1(1, 1, 1, 0-10, 0.01, 16, 0, 0, 0, cubeVAO, lightingShader);
         leaf(0, 0, 0, 0-10, 0.01, 16, 0, 0, 0, cubeVAO, lightingShader);
         leaf(0, 0, 0, 0 - 2-10, 0.01, 16, 0, 0, 0, cubeVAO, lightingShader);

        ///tree sphere 2

        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(6, 6, 6, 13 - 2 + 1.7-4, 5.5, 15 + 0.2+4, 0, 0, 0));


        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 - 1 - 4, 4.8, 15 + 0.5 + 4, 0, 0, 0));
        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 - 1 - 4, 4.8, 14.5 + 0.5 + 4, 0, 0, 0));
        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 - 1 - 0.5 - 4, 4.8, 15 + 0.5 + 4, 0, 0, 0));

        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 - 4, 4.8, 15 + 4, 0, 0, 0));
        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 - 4, 4.8, 14.5 + 4, 0, 0, 0));
        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 - 0.5 - 4, 4.8, 15 + 4, 0, 0, 0));

        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 - 4, 4.8, 15 + 0.5 + 0.7 + 4, 0, 0, 0));
        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 - 4, 4.8, 14.5 + 0.5 + 0.7 + 4, 0, 0, 0));
        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 - 0.5 - 4, 4.8, 15 + 0.5 + 0.7 + 4, 0, 0, 0));

        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 - 1 + 2 - 4, 4.8, 15 + 0.5 + 4, 0, 0, 0));
        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 - 1 + 2 - 4, 4.8, 14.5 + 0.5 + 4, 0, 0, 0));
        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 - 1 + 2 - 0.5 - 4, 4.8, 15 + 0.5 + 4, 0, 0, 0));

        cylinder.drawSphere(lightingShader, model_Matrix(1, 1, 1, 13 - 4, -0.1, 15 + 4, 0, 0, 0));
        cylinder.drawSphere(lightingShader, model_Matrix(0.6, 0.4, 0.6, 13 - 4, 0.1 + 3.5, 15 + 4, 0, 0, 60));
        cylinder.drawSphere(lightingShader, model_Matrix(0.6, 0.4, 0.6, 13 - 4, 0.1 + 3.5, 15 + 4, 0, 0, -60));


        ///tree sphere 3

        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(6, 6, 6, 13 - 2 + 1.7 - 4-8-2, 5.5, 15 + 0.2 + 4, 0, 0, 0));


        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 - 1 - 4 - 8 - 2, 4.8, 15 + 0.5 + 4, 0, 0, 0));
        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 - 1 - 4 - 8 - 2, 4.8, 14.5 + 0.5 + 4, 0, 0, 0));
        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 - 1 - 0.5 - 4 - 8 - 2, 4.8, 15 + 0.5 + 4, 0, 0, 0));

        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 - 4 - 8 - 2, 4.8, 15 + 4, 0, 0, 0));
        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 - 4 - 8 - 2, 4.8, 14.5 + 4, 0, 0, 0));
        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 - 0.5 - 4 - 8 - 2, 4.8, 15 + 4, 0, 0, 0));

        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 - 4 - 8 - 2, 4.8, 15 + 0.5 + 0.7 + 4, 0, 0, 0));
        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 - 4 - 8 - 2, 4.8, 14.5 + 0.5 + 0.7 + 4, 0, 0, 0));
        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 - 0.5 - 4 - 8 - 2, 4.8, 15 + 0.5 + 0.7 + 4, 0, 0, 0));

        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 - 1 + 2 - 4 - 8 - 2, 4.8, 15 + 0.5 + 4, 0, 0, 0));
        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 - 1 + 2 - 4 - 8 - 2, 4.8, 14.5 + 0.5 + 4, 0, 0, 0));
        sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(4, 4, 4, 13 - 1 + 2 - 0.5 - 4 - 8 - 2, 4.8, 15 + 0.5 + 4, 0, 0, 0));

        cylinder.drawSphere(lightingShader, model_Matrix(1, 1, 1, 13 - 4 - 8 - 2, -0.1, 15 + 4, 0, 0, 0));
        cylinder.drawSphere(lightingShader, model_Matrix(0.6, 0.4, 0.6, 13 - 4 - 8 - 2, 0.1 + 3.5, 15 + 4, 0, 0, 60));
        cylinder.drawSphere(lightingShader, model_Matrix(0.6, 0.4, 0.6, 13 - 4 - 8 - 2, 0.1 + 3.5, 15 + 4, 0, 0, -60));


        /*cloud.drawSphere(lightingShader,model_Matrix(10,10,10,5,25,5,0,0,0));
        cloud.drawSphere(lightingShader,model_Matrix(10, 10, 10,5.2,25,5,0,0,0));
        cloud.drawSphere(lightingShader,model_Matrix(10, 10, 10,5.4,25.1,5,0,0,0));
        cloud.drawSphere(lightingShader,model_Matrix(10, 10, 10,5.6,25.5,5,0,0,0));

        cloud.drawSphere(lightingShader, model_Matrix(10, 10, 10, 5, 25, 5, 0, 0, 0));
        cloud.drawSphere(lightingShader, model_Matrix(10, 10, 10, 5.2, 25, 5.2, 0, 0, 0));
        cloud.drawSphere(lightingShader, model_Matrix(10, 10, 10, 5.4, 25.1, 5.4, 0, 0, 0));
        cloud.drawSphere(lightingShader, model_Matrix(10, 10, 10, 5.6, 25.5, 5.6, 0, 0, 0));*/
       
        
            tunnel1.draw(lightingShaderWithTexture);
            tunnel2.draw(lightingShaderWithTexture);
            tunnel3.draw(lightingShaderWithTexture);
            tunnel4.draw(lightingShaderWithTexture);
            tunnel5.draw(lightingShaderWithTexture);
            tunnel6.draw(lightingShaderWithTexture);
            tunnel7.draw(lightingShaderWithTexture);
            tunnel8.draw(lightingShaderWithTexture);
            tunnel9.draw(lightingShaderWithTexture);
            tunnel10.draw(lightingShaderWithTexture);
            tunnel11.draw(lightingShaderWithTexture);
            tunnel12.draw(lightingShaderWithTexture);
            tunnel13.draw(lightingShaderWithTexture);
            tunnel14.draw(lightingShaderWithTexture);
            tunnel15.draw(lightingShaderWithTexture);
            tunnel16.draw(lightingShaderWithTexture);

           /* tunnel17.draw(lightingShaderWithTexture);
            tunnel18.draw(lightingShaderWithTexture);
            tunnel19.draw(lightingShaderWithTexture);
            tunnel20.draw(lightingShaderWithTexture);
            tunnel21.draw(lightingShaderWithTexture);
            tunnel22.draw(lightingShaderWithTexture);
            tunnel23.draw(lightingShaderWithTexture);
            tunnel24.draw(lightingShaderWithTexture);
            tunnel25.draw(lightingShaderWithTexture);
            tunnel26.draw(lightingShaderWithTexture);
            tunnel27.draw(lightingShaderWithTexture);
            tunnel28.draw(lightingShaderWithTexture);
            tunnel29.draw(lightingShaderWithTexture);
            tunnel30.draw(lightingShaderWithTexture);
            tunnel31.draw(lightingShaderWithTexture);
            tunnel32.draw(lightingShaderWithTexture);
            tunnel33.draw(lightingShaderWithTexture);
            tunnel34.draw(lightingShaderWithTexture);
            tunnel35.draw(lightingShaderWithTexture);
            tunnel36.draw(lightingShaderWithTexture);
            tunnel37.draw(lightingShaderWithTexture);
            tunnel38.draw(lightingShaderWithTexture);
            tunnel39.draw(lightingShaderWithTexture);
            tunnel40.draw(lightingShaderWithTexture);
            tunnel41.draw(lightingShaderWithTexture);
            tunnel42.draw(lightingShaderWithTexture);*/
          

           /* tunnel43.draw(lightingShaderWithTexture);
            tunnel44.draw(lightingShaderWithTexture);
            tunnel45.draw(lightingShaderWithTexture);
            tunnel46.draw(lightingShaderWithTexture);
            tunnel47.draw(lightingShaderWithTexture);
            tunnel48.draw(lightingShaderWithTexture);
            tunnel49.draw(lightingShaderWithTexture);
            tunnel50.draw(lightingShaderWithTexture);
            tunnel51.draw(lightingShaderWithTexture);
            tunnel52.draw(lightingShaderWithTexture);
            tunnel53.draw(lightingShaderWithTexture);
            tunnel54.draw(lightingShaderWithTexture);
            tunnel55.draw(lightingShaderWithTexture);
            tunnel56.draw(lightingShaderWithTexture);
            tunnel57.draw(lightingShaderWithTexture);
            tunnel58.draw(lightingShaderWithTexture);*/

            /*tunnel59.draw(lightingShaderWithTexture);
            tunnel60.draw(lightingShaderWithTexture);
            tunnel61.draw(lightingShaderWithTexture);
            tunnel62.draw(lightingShaderWithTexture);
            tunnel63.draw(lightingShaderWithTexture);
            tunnel64.draw(lightingShaderWithTexture);
            tunnel65.draw(lightingShaderWithTexture);
            tunnel66.draw(lightingShaderWithTexture);
            tunnel67.draw(lightingShaderWithTexture);
            tunnel68.draw(lightingShaderWithTexture);
            tunnel69.draw(lightingShaderWithTexture);
            tunnel70.draw(lightingShaderWithTexture);
            tunnel71.draw(lightingShaderWithTexture);
            tunnel72.draw(lightingShaderWithTexture);
            tunnel73.draw(lightingShaderWithTexture);
            tunnel74.draw(lightingShaderWithTexture);
            tunnel75.draw(lightingShaderWithTexture);
            tunnel76.draw(lightingShaderWithTexture);
            tunnel77.draw(lightingShaderWithTexture);
            tunnel78.draw(lightingShaderWithTexture);
            tunnel79.draw(lightingShaderWithTexture);
            tunnel80.draw(lightingShaderWithTexture);
            tunnel81.draw(lightingShaderWithTexture);
            tunnel82.draw(lightingShaderWithTexture);*/
          /*  tunnel83.draw(lightingShaderWithTexture);
            tunnel84.draw(lightingShaderWithTexture);*/
           /* tunnel83.draw(lightingShaderWithTexture);
            tunnel84.draw(lightingShaderWithTexture);*/

       // road.draw(lightingShaderWithTexture);

       
           // red_color(10, 10, 10, 30.0, 50.0, 21.0, 0, 0,0, cubeVAO, lightingShader);

        //sun
        sun_sphere.drawSphereWithTexture(lightingShaderWithTexture, model_Matrix(20, 20, 20, 33,80, -60, 0, 0, 0));

        //fan
       // curve1_1.drawObject(lightingShader, model_Matrix(0.2, 50, 0.5, 0.2, 0, 0, 90, 0, 0));

        // grey_color(0.5,5, 0.5, 4, 5, 4.5, 0,0,0,cubeVAO, lightingShader);
         
        // train track lights lamp
       

        for (int i = 0; i < 41; i+=4)
        {
            if (i == 40)
            {
                cylinder2.drawSphere(lightingShader, model_Matrix(0.2, 1, 0.2, 14.5484 + 3 + i-1, 2, 2.05979 + 0.9, 0, 0, 0));
                cylinder2.drawSphere(lightingShader, model_Matrix(0.2, 0.25, 0.2, 14.5484 + 3 + i-1, 5.8, 2.05979 + 0.9 + 0.1, -90, 0, 0));


                cylinder2.drawSphere(lightingShader, model_Matrix(0.2, 1, 0.2, 14.5484 + 3 + i-1, 2, 2.05979 + 0.9 - 2.8, 0, 0, 0));
                cylinder2.drawSphere(lightingShader, model_Matrix(0.2, 0.25, 0.2, 14.5484 + 3 + i-1, 5.8, 2.05979 + 0.9 + 0.1 - 2, -90, 0, 0));

            }
            else
            {
                cylinder2.drawSphere(lightingShader, model_Matrix(0.2, 1, 0.2, 14.5484 + 3 + i, 2, 2.05979 + 0.9, 0, 0, 0));
                cylinder2.drawSphere(lightingShader, model_Matrix(0.2, 0.25, 0.2, 14.5484 + 3 + i, 5.8, 2.05979 + 0.9 + 0.1, -90, 0, 0));


                cylinder2.drawSphere(lightingShader, model_Matrix(0.2, 1, 0.2, 14.5484 + 3 + i, 2, 2.05979 + 0.9 - 2.8, 0, 0, 0));
                cylinder2.drawSphere(lightingShader, model_Matrix(0.2, 0.25, 0.2, 14.5484 + 3 + i, 5.8, 2.05979 + 0.9 + 0.1 - 2, -90, 0, 0));
            }
          
        }

        for (int i = 1; i < 36; i += 4)
        {
            //cylinder2.drawSphere(lightingShader, model_Matrix(0.1, 0.3, 0.1, -3 + i, 0.01, 2.05979 + 0.9, 0, 0, 0));
            //cylinder2.drawSphere(lightingShader, model_Matrix(0.2, 0.1, 0.2, -4 + i, 3, 2.05979 + 0.9 + 0.1, -90, 0, 0));
            if (i == 39)
            {
                cylinder2.drawSphere(lightingShader, model_Matrix(0.1, 0.3, 0.1, -3 + i, 0.01, 2.05979 + 0.9, 0, 0, 0));
               
            }
            else
            {
                cylinder2.drawSphere(lightingShader, model_Matrix(0.1, 0.25, 0.1, -3 + i-1, 0.01, 2.05979 + 0.9-0.1, 0, 0, 0));
                cylinder2.drawSphere(lightingShader, model_Matrix(0.1, 0.15, 0.1, -4 + i, 0.95, 2.05979 + 0.9 + 0.1-0.18+0.03, -90, 0, 0));
            }

           /* cylinder2.drawSphere(lightingShader, model_Matrix(0.2, 1, 0.2, -4 + i, 0.01, 2.05979 + 0.9 - 2.8, 0, 0, 0));
            cylinder2.drawSphere(lightingShader, model_Matrix(0.2, 0.25, 0.2, -4 + i, 5.8-2, 2.05979 + 0.9 + 0.1 - 2, -90, 0, 0));*/
        }

        for (int i = 45; i < 68; i += 4)
        {
            //cylinder2.drawSphere(lightingShader, model_Matrix(0.1, 0.3, 0.1, -3 + i, 0.01, 2.05979 + 0.9, 0, 0, 0));
            //cylinder2.drawSphere(lightingShader, model_Matrix(0.2, 0.1, 0.2, -4 + i, 3, 2.05979 + 0.9 + 0.1, -90, 0, 0));
            
                cylinder2.drawSphere(lightingShader, model_Matrix(0.1, 0.25, 0.1, -3 + i - 1, 0.01, 2.05979 + 0.9 - 0.1, 0, 0, 0));
                cylinder2.drawSphere(lightingShader, model_Matrix(0.1, 0.15, 0.1, -4 + i, 0.95, 2.05979 + 0.9 + 0.1 - 0.18 + 0.03, -90, 0, 0));
            

            /* cylinder2.drawSphere(lightingShader, model_Matrix(0.2, 1, 0.2, -4 + i, 0.01, 2.05979 + 0.9 - 2.8, 0, 0, 0));
             cylinder2.drawSphere(lightingShader, model_Matrix(0.2, 0.25, 0.2, -4 + i, 5.8-2, 2.05979 + 0.9 + 0.1 - 2, -90, 0, 0));*/
        }

       
       /* for (int i = 0; i < 10; i++)
        {
            cylinder2.drawSphere(lightingShader, model_Matrix(0.2, 0.25, 0.2, 14.5484 + 3, 5.8, 2.05979 + 0.9 + 0.1, -90, 0, 0));
            cylinder2.drawSphere(lightingShader, model_Matrix(0.2, 0.25, 0.2, 14.5484 + 3, 5.8, 2.05979 + 0.9 + 0.1, -90, 0, 0));
        }*/
       
        
        /*wheel.drawWheel(lightingShader, model_Matrix(.5, 0.2, 0.5, 4, 4.5, 4.5, 0, 0, 0));
        wheel.drawWheel(lightingShader, model_Matrix(.5, 0.2, 0.5, 4, 4.5, 4.5, 0, 0, 90));
        wheel.drawWheel(lightingShader, model_Matrix(.5, 0.2, 0.5, 4, 4.5, 4.5, 0, 0, 180));
        wheel.drawWheel(lightingShader, model_Matrix(.5, 0.5, 0.5, 4, 4.5, 4.5, 0, 0, 270));*/

         

       // train_wheel(1,1,1,5,5,5,0,0,0,)










        /////////////////////////////////////////////// 1st Station start ////////////////////////////////////////////
      
       
        ////platform
      
        //rail track side wall
        cube8.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(195, 3, -30, -4, 2.1, 0, 0, 0, 0));
        cube8.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(195, 3, 30, -4, 2.1, 3, 0, 0, 0));
      
        //stair
        for (int i = 2, j = 1; i < 20; i += 2, j += 1)
        {
           // white_color(3, 1, 15, 0.8 + (i * 0.1), 0.1 + (j * 0.1), 8.0, 0, 0, 0, cubeVAO, lightingShader);
           
            cube9.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, 15, 0.8 + (i * 0.1), 0.1 + (j * 0.1), 8.0, 0, 0, 0));
        }
        for (int i = 2, j = 1; i < 24; i += 2, j += 1)
        {
          //  white_color(15, 1, 3, 2.5, 1.0 + (j * 0.1), 7.9 - (i * 0.1), 0, 0, 0, cubeVAO, lightingShader);
           cube10.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(15, 1, 3, 2.5, 1.0 + (j * 0.1), 7.9 - (i * 0.1), 0, 0, 0));

        }
        cube9.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(15, 1, 15, 2.5, 1.1, 8.0, 0, 0, 0));
        
        //63, 30, 1, -3.8, 2.4, 5.8, 0, 0, 0

        cube11.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(63, 30, 1, -3.8, 2.4, 5.8, 0, 0, 0));
        cube12.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 30, -20, -3.8, 2.4, 5.8, 0, 0, 0));

      
        //platform 1 wall
        cube11.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(40, 30, 1, 4, 2.4, 5.8, 0, 0, 0));
        cube12.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(10.9, 30, 1, 7, 2.4, 3.8, 0, 0, 0));
        cube13.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(10, -6, 1, 6, 5.4, 3.8, 0, 0, 0));
        cube11.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 30, -19.5, 8, 2.4, 5.8, 0, 0, 0));


        ////ticket counter
        
        cube12.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 30, -6, 6, 2.39, 5.8, 0, 0, 0));
        cube12.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 30, -7, 6, 2.391, 4.5, 0, 0, 0));
        cube12.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, -10, 14, 6, 5.391, 4.5, 0, 0, 0));
        cube12.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 10, 14, 6, 2.39, 4.5, 0, 0, 0));

        ////platform roof
       

        cube14.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(119, 1, -21, -3.8, 5.4, 5.9, 0, 0, 0));
        cube14.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(119, 1, -21, -3.8, 5.4, -0.5, 0, 0, 0));

        //passenger stand line at counter

        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-16, 0.5, 0.5, 5.8, 3.4, 4.5, 0, 0, 0));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-16, 0.5, 0.5, 5.8, 3.4, 5.1, 0, 0, 0));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-10, 0.5, 0.5, 5.8, 3.4, 5.1, 0, 0, 90));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-10, 0.5, 0.5, 5.8, 3.4, 4.5, 0, 0, 90));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-10, 0.5, 0.5, 5.3, 3.4, 5.1, 0, 0, 90));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-10, 0.5, 0.5, 5.3, 3.4, 4.5, 0, 0, 90));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-10, 0.5, 0.5, 4.8, 3.4, 5.1, 0, 0, 90));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-10, 0.5, 0.5, 4.8, 3.4, 4.5, 0, 0, 90));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-10, 0.5, 0.5, 4.3, 3.4, 5.1, 0, 0, 90));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-10, 0.5, 0.5, 4.3, 3.4, 4.5, 0, 0, 90));

        //seat at ticket counter
    


        //bench1
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.1, 2.4, 5.5, 0, 0, 10));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.5, 2.4, 5.5, 0, 0, -10));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.1, 2.4, 4, 0, 0, 10));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.5, 2.4, 4, 0, 0, -10));
        cube16.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(5, 0.5, -16.5, -3.5, 2.75, 5.6, 0, 0, 5));
        cube16.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(5, 0.5, -16.5, -3.45, 2.75, 5.6, 0, 0, 100));
        //bench2
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.1+1, 2.4, 5.5, 0, 0, 10));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.5+1, 2.4, 5.5, 0, 0, -10));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.1+1, 2.4, 4, 0, 0, 10));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.5+1, 2.4, 4, 0, 0, -10));
        cube16.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(5, 0.5, -16.5, -3.5+1, 2.75, 5.6, 0, 0, 5));
        cube16.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(5, 0.5, -16.5, -3.45+1, 2.75, 5.6, 0, 0, 100));
        //bench3
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.1 + 2, 2.4, 5.5, 0, 0, 10));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.5 + 2, 2.4, 5.5, 0, 0, -10));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.1 + 2, 2.4, 4, 0, 0, 10));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.5 + 2, 2.4, 4, 0, 0, -10));
        cube16.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(5, 0.5, -16.5, -3.5 + 2, 2.75, 5.6, 0, 0, 5));
        cube16.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(5, 0.5, -16.5, -3.45 + 2, 2.75, 5.6, 0, 0, 100));
        //bench4
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.1 + 3, 2.4, 5.5, 0, 0, 10));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.5 + 3, 2.4, 5.5, 0, 0, -10));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.1 + 3, 2.4, 4, 0, 0, 10));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.5 + 3, 2.4, 4, 0, 0, -10));
        cube16.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(5, 0.5, -16.5, -3.5 + 3, 2.75, 5.6, 0, 0, 5));
        cube16.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(5, 0.5, -16.5, -3.45 + 3, 2.75, 5.6, 0, 0, 100));
        //bench5
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.1 + 4, 2.4, 5.5, 0, 0, 10));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.5 + 4, 2.4, 5.5, 0, 0, -10));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.1 + 4, 2.4, 4, 0, 0, 10));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.5 + 4, 2.4, 4, 0, 0, -10));
        cube16.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(5, 0.5, -16.5, -3.5 + 4, 2.75, 5.6, 0, 0, 5));
        cube16.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(5, 0.5, -16.5, -3.45 + 4, 2.75, 5.6, 0, 0, 100));


        //2nd platform brench

        //bench1

        cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 5, 0.5, -1.5, 2.4, -1.2, -10, 0, 0));
        cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 5, 0.5, 1.5 , 2.4, -1.2, -10, 0, 0));
        cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 5, 0.5, 0 , 2.4, -1.2, -10, 0, 0));
        cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 5, 0.5, 0 ,2.4, -1.8, 10, 0, 0));
        cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 5, 0.5, -1.5 , 2.4, -1.8, 10, 0, 0));
        cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 5, 0.5, 1.5 , 2.4, -1.8, 10, 0, 0));
        cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(32, 0.5, -5, -1.6 , 2.9, -1.2, -5, 0, 0));
        cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(32, 0.5, -5, -1.6 , 2.9, -1.7, 80, 0, 0));
        //bench 2
        cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 5, 0.5, -1.5+5, 2.4, -1.2, -10, 0, 0));
        cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 5, 0.5, 1.5+5, 2.4, -1.2, -10, 0, 0));
        cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 5, 0.5, 0+5, 2.4, -1.2, -10, 0, 0));
        cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 5, 0.5, 0+5, 2.4, -1.8, 10, 0, 0));
        cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 5, 0.5, -1.5+5, 2.4, -1.8, 10, 0, 0));
        cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 5, 0.5, 1.5+5, 2.4, -1.8, 10, 0, 0));
        cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(32, 0.5, -5, -1.6+5, 2.9, -1.2, -5, 0, 0));
        cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(32, 0.5, -5, -1.6+5, 2.9, -1.7, 80, 0, 0));

       


        //overbridge 
        // 
        // overbridge left stair
        //low handle 1

        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(23, 0.5, 0.5, 8.5 + 0.5, 2.4, -0.5, 0, 0, 45));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(23, 0.5, 0.5, 8.5 + 0.5, 2.4, -2, 0, 0, 45));

        //upper handle 1
        
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(22, 0.5, 0.5, 8.5 + 0.5, 3.4, -0.5 , 0, 0, 45));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(22, 0.5, 0.5, 8.5 + 0.5, 3.4, -2, 0, 0, 45));

        //stair pillar 1
   
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 12, 0.5, 8.5 + 0.5, 2.4, -2 , 0, 0, 0));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 12, 0.5, 8.5 + 0.5, 2.4, -0.5, 0, 0, 0));

        //stair1

        cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 8.4 + 0.5, 2.4, -0.47, 0, 0, 0));
        cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 8.6 + 0.5, 2.6, -0.47, 0, 0, 0));
        cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 8.8 + 0.5, 2.8, -0.47, 0, 0, 0));
        cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 9.0 + 0.5, 3.0, -0.47, 0, 0, 0));
        cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 9.2 + 0.5, 3.2, -0.47, 0, 0, 0));
        cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 9.4 + 0.5, 3.4, -0.47, 0, 0, 0));
        cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 9.6 + 0.5, 3.6, -0.47, 0, 0, 0));
        cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 9.8 + 0.5, 3.8, -0.47, 0, 0, 0));
        cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(12, 1, -15, 10.0 + 0.5, 4.0, -0.47, 0, 0, 0));

        //stair2

       // cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 11.1 + 0.5, 4.0, -0.47, 0, 0, 0));
        cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 11.3 + 0.5, 4.2, -0.47, 0, 0, 0));
        cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 11.5 + 0.5, 4.4, -0.47, 0, 0, 0));
        cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 11.7 + 0.5, 4.6, -0.47, 0, 0, 0));
        cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 11.9 + 0.5, 4.8, -0.47, 0, 0, 0));

        cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 12.1 + 0.5, 5.0, -0.47, 0, 0, 0));
        cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 12.3 + 0.5, 5.2, -0.47, 0, 0, 0));
        cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 12.5 + 0.5, 5.4, -0.47, 0, 0, 0));
        cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 12.7 + 0.5, 5.6, -0.47, 0, 0, 0));


        //stair pillar 2

        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 10, 0.5, 10.0 + 0.5, 4.0, -2, 0, 0, 0));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 10, 0.5, 10.0 + 0.5, 4.0, -0.5, 0, 0, 0));

        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 10, 0.5, 11.2 + 0.5, 4.0, -2, 0, 0, 0));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 10, 0.5, 11.2 + 0.5, 4.0, -0.5, 0, 0, 0));
        
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 17, 1, 10.0 + 0.5, 2.4, -2, 0, 0, 0));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 17, 1, 10.0 + 0.5, 2.4, -0.5, 0, 0, 0));

        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 17, 1, 11.2 + 0.5, 2.4, -2, 0, 0, 0));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 17, 1, 11.2 + 0.5, 2.4, -0.5, 0, 0, 0));

     

        //middle handle
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(12, 0.5, 0.5, 10.54, 4.9, -2, 0, 0, 0));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(12, 0.5, 0.5, 10.54, 4.9, -0.5, 0, 0, 0));



        ////low handle 2
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(25, 0.5, 0.5, 11.2 + 0.5, 4.0, -0.5, 0, 0, 45));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(25, 0.5, 0.5, 11.2 + 0.5, 4.0, -2, 0, 0, 45));
      
        //upper handle 2

        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(25, 0.5, 0.5, 11.7, 4.9, -0.5, 0, 0, 45));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(25, 0.5, 0.5, 11.7, 4.9, -2, 0, 0, 45));

        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 60, 1, 12.9 + 0.5, 2.4, -2, 0, 0, 0));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 60, 1, 12.9 + 0.5, 2.4, -0.5, 0, 0, 0));


        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 60, 1, 14.2 + 0.5, 2.4, -2, 0, 0, 0));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 60, 1, 14.2 + 0.5, 2.4, -0.5, 0, 0, 0));

        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 60, 1, 14.2 + 0.5, 2.4, -2, 0, 0, 0));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 60, 1, 14.2 + 0.5, 2.4, -0.5, 0, 0, 0));

        //top handle 
        
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 9, 0.5, 12.9 + 0.5, 5.8, -2, 0, 0, 0));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 9, 0.5, 12.9 + 0.5, 5.8, -0.5, 0, 0, 0));

       //over Bridge wall + floor
       cube21.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(13, 1, 75, 12.9 + 0.5, 5.8, -2, 0, 0, 0));
       cube22.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-75, 10, 0.1, 14.7, 5.8, -2, 0, 90, 0));
       cube23.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 10, 45, 12.9 + 0.5, 5.8, 4.0, 0, 180, 0));
       cube24.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 10, 13, 12.9 + 0.5, 5.8, -2, 0, 90, 0));
       cube24.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 10, 13, 12.9 + 0.5, 5.8, 5.5, 0, 90, 0));
       cube24.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 10, 13, 12.9 + 0.5, 5.8, 5.5, 0, 90, 0));
       cube24.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(14, 1, 76, 12.9 + 0.5, 8.4, -2, 0, 0, 0));
      

       //overbridge right stair

        //low handle 1

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(23, 0.5, 0.5, 8.5 + 0.5, 2.4, -0.5+6, 0, 0, 45));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(23, 0.5, 0.5, 8.5 + 0.5, 2.4, -2+6, 0, 0, 45));

       //upper handle 1

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(22, 0.5, 0.5, 8.5 + 0.5, 3.4, -0.5+6, 0, 0, 45));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(22, 0.5, 0.5, 8.5 + 0.5, 3.4, -2+6, 0, 0, 45));

       //stair pillar 1
    
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 12, 0.5, 8.5 + 0.5, 2.4, -2+6, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 12, 0.5, 8.5 + 0.5, 2.4, -0.5+6, 0, 0, 0));

       //stair1

       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 8.4 + 0.5, 2.4, -0.47+6, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 8.6 + 0.5, 2.6, -0.47+6, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 8.8 + 0.5, 2.8, -0.47+6, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 9.0 + 0.5, 3.0, -0.47+6, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 9.2 + 0.5, 3.2, -0.47+6, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 9.4 + 0.5, 3.4, -0.47+6, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 9.6 + 0.5, 3.6, -0.47+6, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 9.8 + 0.5, 3.8, -0.47+6, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(12, 1, -15, 10.0 + 0.5, 4.0, -0.47+6, 0, 0, 0));

       //stair2

      // cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 11.1 + 0.5, 4.0, -0.47, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 11.3 + 0.5, 4.2, -0.47+6, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 11.5 + 0.5, 4.4, -0.47+6, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 11.7 + 0.5, 4.6, -0.47+6, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 11.9 + 0.5, 4.8, -0.47+6, 0, 0, 0));

       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 12.1 + 0.5, 5.0, -0.47+6, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 12.3 + 0.5, 5.2, -0.47+6, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 12.5 + 0.5, 5.4, -0.47+6, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 12.7 + 0.5, 5.6, -0.47+6, 0, 0, 0));


       //stair pillar 2

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 10, 0.5, 10.0 + 0.5, 4.0, -2+6, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 10, 0.5, 10.0 + 0.5, 4.0, -0.5+6, 0, 0, 0));

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 10, 0.5, 11.2 + 0.5, 4.0, -2+6, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 10, 0.5, 11.2 + 0.5, 4.0, -0.5+6, 0, 0, 0));

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 17, 1, 10.0 + 0.5, 2.4, -2+6, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 17, 1, 10.0 + 0.5, 2.4, -0.5+6, 0, 0, 0));

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 17, 1, 11.2 + 0.5, 2.4, -2+6, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 17, 1, 11.2 + 0.5, 2.4, -0.5+6, 0, 0, 0));

      

        //middle handle
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(12, 0.5, 0.5, 10.54, 4.9, -2+6, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(12, 0.5, 0.5, 10.54, 4.9, -0.5+6, 0, 0, 0));



       ////low handle 2
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(25, 0.5, 0.5, 11.2 + 0.5, 4.0, -0.5+6, 0, 0, 45));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(25, 0.5, 0.5, 11.2 + 0.5, 4.0, -2+6, 0, 0, 45));

       //upper handle 2

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(25, 0.5, 0.5, 11.7, 4.9, -0.5+6, 0, 0, 45));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(25, 0.5, 0.5, 11.7, 4.9, -2+6, 0, 0, 45));

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 60, 1, 12.9 + 0.5, 2.4, -2+6, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 60, 1, 12.9 + 0.5, 2.4, -0.5+6, 0, 0, 0));


       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 60, 1, 14.2 + 0.5, 2.4, -2+6, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 60, 1, 14.2 + 0.5, 2.4, -0.5+6, 0, 0, 0));

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 60, 1, 14.2 + 0.5, 2.4, -2+6, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 60, 1, 14.2 + 0.5, 2.4, -0.5+6, 0, 0, 0));

       //top handle 

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 9, 0.5, 12.9 + 0.5, 5.8, -2+6, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 9, 0.5, 12.9 + 0.5, 5.8, -0.5+6, 0, 0, 0));


         //stair

        white_color(18.5, 1, 1, 1, 1.1, 9.4, 0, 0, 33, cubeVAO, lightingShader);
        white_color(18.5, 1, 1, 1, 1.1, 8.0, 0, 0, 33, cubeVAO, lightingShader);

       // white_color(15, 1, 15, 2.5, 1.1, 8.0, 0, 0, 0, cubeVAO, lightingShader);


       white_color(1, 1, -25, 3.9, 1.12, 8, 28, 0, 0, cubeVAO, lightingShader);
       white_color(1, 1, -25, 2.5, 1.12, 8, 28, 0, 0, cubeVAO, lightingShader);

       white_color(1, 1, -25, 3.9, 2.12, 8, 28, 0, 0, cubeVAO, lightingShader);
       white_color(1, 1, -25, 2.5, 2.12, 8, 28, 0, 0, cubeVAO, lightingShader);

       white_color(1, 11, 1, 3.9, 0.01, 9.4, 0, 0, 0, cubeVAO, lightingShader);
       white_color(1, 11, 1, 3.9, 0.01, 8, 0, 0, 0, cubeVAO, lightingShader);
       white_color(1, 11, 1, 2.5, 0.01, 9.4, 0, 0, 0, cubeVAO, lightingShader);
       white_color(1, 11, 1, 2.5, 0.01, 8.0, 0, 0, 0, cubeVAO, lightingShader);


       white_color(1, 9.84, 1, 1.1, 0.3, 9.4, 0, 0, 0, cubeVAO, lightingShader);
       white_color(1, 9.84, 1, 1.1, 0.3, 8, 0, 0, 0, cubeVAO, lightingShader);

       white_color(1, 12, 1, 2.5, 1.0, 9.4, 0, 0, 0, cubeVAO, lightingShader);
       white_color(1, 12, 1, 2.5, 2,6, 0, 0, 0, cubeVAO, lightingShader);

       white_color(1, 12, 1, 3.9, 2,6, 0, 0, 0, cubeVAO, lightingShader);

       white_color(1, 12, 1, 2.5, 1.0, 8, 0, 0, 0, cubeVAO, lightingShader);
       white_color(1, 12, 1, 3.9, 1.0, 8, 0, 0, 0, cubeVAO, lightingShader);
       white_color(1, 12, 1, 3.9, 1.0, 9.4, 0, 0, 0, cubeVAO, lightingShader);

       white_color(14, 1, 1, 2.55, 2.1, 9.4, 0, 0, 0, cubeVAO, lightingShader);
       white_color(14, 1, 1, 3.9, 2.1, 9.4, 0, 90, 0, cubeVAO, lightingShader);

         //ticket counter texture
        cube2.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.1, 2, 4, 5.99, 4.5, 4.65, 0, 0, 0));

             //2nd platform pillar
       white_color(1, 30, 1, -3.5, 2.4, -1.5, 0, 0, 0, cubeVAO, lightingShader);
       chocolate_color(1, 1, -20, -3.5, 5.3, -0.5, 0, 0, 0, cubeVAO, lightingShader);

       white_color(1, 30, 1, 2.8, 2.4, -1.5, 0, 0, 0, cubeVAO, lightingShader);
       chocolate_color(1, 1, -20, 2.8, 5.3, -0.5, 0, 0, 0, cubeVAO, lightingShader);

       white_color(1, 30, 1, 7.5, 2.4, -1.5, 0, 0, 0, cubeVAO, lightingShader);
       chocolate_color(1, 1, -20, 7.5, 5.3, -0.5, 0, 0, 0, cubeVAO, lightingShader);

       //advertise texture
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.2, 9, 7, -3.4, 3.5, -1.8, 0, 0, 0));


         //under platform pillar
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 20.9, 3, -3.8, 0.01, -2.8, 0, 0, 0));
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 20.9, 3, -3.8, 0.01, 5.5, 0, 0, 0));
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 20.9, 3, -3.8 + 4, 0.01, -2.8, 0, 0, 0));
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 20.9, 3, -3.8 + 4, 0.01, 5.5, 0, 0, 0));
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 20.9, 3, -3.8 + 8, 0.01, -2.8, 0, 0, 0));
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 20.9, 3, -3.8 + 8, 0.01, 5.5, 0, 0, 0));
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 20.9, 3, -3.8 + 12, 0.01, -2.8, 0, 0, 0));
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 20.9, 3, -3.8 + 12, 0.01, 5.5, 0, 0, 0));
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 20.9, 3, -3.8 + 16, 0.01, -2.8, 0, 0, 0));
        /*cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 20, 3, -3.8 + 16, 0.01, 5.5, 0, 0, 0));
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 20, 3, -3.8 + 18.8, 0.01, -2.8, 0, 0, 0));
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 20, 3, -3.8 + 19, 0.01, 5.5, 0, 0, 0));*/

        /////////////////////////////////////////////// 1st Station End ////////////////////////////////////////////
      
       //train


       //for (int t = 0; t <= 6; t += 3)
       //{
       //   cube26.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(30, 0.3, -11, 4.8 - t, 2.55, 2.9, 0, 0, 0));


       //    cube27.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-24, 3.5, 0.3, 7.2 - t, 2.55, 1.8, 0, 0, 0));

       //    cube28.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-24, 3.5, 0.3, 7.2 - t, 2.9, 1.8, 0, 0, 0));
       //    cube28.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-24, 4.5, 0.3, 7.2 - t, 3.62, 1.8, 0, 0, 0)); 
       //   
       //    cube30.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-4, 8, 0.3, 7.2 - t, 3.25, 1.8, 0, 0, 0));

       //    cube28.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-2, -3.8, 0.3, 2 - t+3, 3.62, 1.8, 0, 0, 0));

       //    cube28.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-2, -3.8, 0.3, 2.7 - t + 3, 3.62, 1.8, 0, 0, 0));
       //    cube28.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-2, -3.8, 0.3, 3.4 - t +3, 3.62, 1.8, 0, 0, 0));



       //    cube27.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-24, 3.5, 0.3, 7.2 - t, 2.55, 2.9, 0, 0, 0));
       //    cube28.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-24, 3.5, 0.3, 7.2 - t, 2.9, 2.9, 0, 0, 0));
       //    cube28.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-24, 4.5, 0.3, 7.2 - t, 3.62, 2.9, 0, 0, 0));

       //    cube30.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-4, 8, 0.3, 7.2 - t, 3.25, 2.9, 0, 0, 0));

       //    cube28.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-2, -3.8, 0.3, 2 - t + 3, 3.62, 2.9, 0, 0, 0));

       //    cube28.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-2, -3.8, 0.3, 2.7 - t + 3, 3.62, 2.9, 0, 0, 0));
       //    cube28.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-2, -3.8, 0.3, 3.4 - t + 3, 3.62, 2.9, 0, 0, 0));


       //    ///train roof

       //    cube28.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(42, 0.3, -4, 3.8 - t, 4.03, 2.92, 30, 0, 0));
       //    cube28.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(42, 0.3, -4, 3.8 - t, 4.05, 1.8, -210, 0, 0));
       //    cube28.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(42, 0.3, -4.5, 3.8 - t, 4.22, 2.59, 0, 0, 0));


       //    if (t == 0)
       //    {
       //      
       //        cube26.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(10, 0.3, -11, 4 - t + 3, 2.55, 2.9, 0, 0, 0));

       //        cube27.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(10, 3.5, 0.3, 4 - t + 3, 2.55, 1.8, 0, 0, 0));
       //        cube28.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(10, 3.5, 0.3, 4 - t + 3, 2.9, 1.8, 0, 0, 0));
       //        cube28.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(10, 3.5, 0.3, 4 - t + 3, 3.25, 1.8, 0, 0, 0));
       //        cube28.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(10, 4.5, 0.3, 4 - t + 3, 3.58, 1.8, 0, 0, 0));

       //       
       //        //train front1
       //        cube27.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.1, 5, -11.2, 5 - t + 3, 2.55, 2.93, 0, 0, 0));
       //        cube28.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.1, 3, -11.2, 5 - t + 3, 3.05, 2.93, 0, 0, 0));
       //        cube30.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.1, 7, -1.5, 5 - t + 3, 3.35, 2.93, 0, 0, 0));
       //        cube30.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.1, 9, -3, 5 - t + 3, 3.35, 2.93 - 0.42, 0, 0, 0));
       //        cube30.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.1, 7, -1.5, 5 - t + 3, 3.35, 2.93 - 0.96, 0, 0, 0));
       //        cube28.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.1, 3, -2.7, 5 - t + 3, 3.75, 2.93 - .15, 0, 0, 0));
       //        cube28.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.1, 3, -2.7, 5 - t + 3, 3.75, 2.93 - .72, 0, 0, 0));


       //        //train middle 1
       //     
       //        cube30.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.1, 15, -2, 5 - t -0.19 , 2.55, 2.93 , 0, 0, 0));
       //        cube30.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.1, 15, -2, 5 - t- 0.19, 2.55, 2.93 - 0.96+0.05, 0, 0, 0));
       //       
       //        //train middle 2

       //        cube30.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.1, 15, -11, 5 - t - 0.19 - 6, 2.55, 2.93, 0, 0, 0));
       //       // cube30.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.1, 15, -2, 5 - t - 0.19 - 6, 2.55, 2.93 - 0.96 + 0.05, 0, 0, 0));

       //        //train middle 3

       //        cube30.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.1, 15, -2, 5 - t - 0.19 - 3, 2.55, 2.93, 0, 0, 0));
       //        cube30.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.1, 15, -2, 5 - t - 0.19 - 3, 2.55, 2.93 - 0.96 + 0.05, 0, 0, 0));

       //        //train middle 4

       //        cube30.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.1, 15, -11, 5 - t + 2.2, 2.55, 2.93, 0, 0, 0));
       //       // cube30.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.1, 15, -2, 5 - t + 2.2, 2.55, 2.93 - 0.96 + 0.05, 0, 0, 0));

       //       
       //         //train front2
       //        cube27.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.1, 5, -11.2, 5 - t - 7.2, 2.55, 2.93, 0, 0, 0));
       //        cube28.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.1, 3, -11.2, 5 - t - 7.2, 3.05, 2.93, 0, 0, 0));
       //        cube30.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.1, 7, -1.5, 5 - t - 7.2, 3.35, 2.93, 0, 0, 0));
       //        cube30.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.1, 9, -3, 5 - t - 7.2, 3.35, 2.93 - 0.42, 0, 0, 0));
       //        cube30.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.1, 7, -1.5, 5 - t - 7.2, 3.35, 2.93 - 0.96, 0, 0, 0));
       //        cube28.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.1, 3, -2.7, 5 - t - 7.2, 3.75, 2.93 - .15, 0, 0, 0));
       //        cube28.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.1, 3, -2.7, 5 - t - 7.2, 3.75, 2.93 - .72, 0, 0, 0));


       //        cube27.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(10, 3.5, 0.3, 4 - t - 6.2, 2.55, 1.8, 0, 0, 0));
       //        cube28.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(10, 3.5, 0.3, 4 - t - 6.2, 2.9, 1.8, 0, 0, 0));
       //        cube28.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(10, 3.5, 0.3, 4 - t - 6.2, 3.25, 1.8, 0, 0, 0));
       //        cube28.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(10, 4.5, 0.3, 4 - t - 6.2, 3.58, 1.8, 0, 0, 0));


       //        cube27.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 3.5, 0.3, 4 - t - 5.5, 2.55, 2.9, 0, 0, 0));
       //        cube28.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 3.5, 0.3, 4 - t - 5.5, 2.9, 2.9, 0, 0, 0));
       //        cube28.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 3.5, 0.3, 4 - t - 5.5, 3.25, 2.9, 0, 0, 0));
       //        cube28.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 4.5, 0.3, 4 - t - 5.5, 3.58, 2.9, 0, 0, 0));

       //        for (int i = 0; i < 360; i++)
       //         {
       //             white_color(1, 0.1, .1, 5.01 - t + 3, 2.83, 2.0, 0, 90, 0 + i, cubeVAO, lightingShader);
       //             white_color(1, 0.1, .1, 5.01 - t + 3, 2.83, 2.75, 0, 90, 0 + i, cubeVAO, lightingShader);
       //         }
       //    }
       //    else if (t == 6)
       //    {
       //        cube26.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-10, 0.3, -11, 5 - t - 0.2, 2.55, 2.9, 0, 0, 0));

       //        for (int i = 0; i < 360; i++)
       //        {
       //            white_color(1, 0.1, .1, 0.79 - t + 3, 2.83, 2.0, 0, 90, 0 + i, cubeVAO, lightingShader);
       //            white_color(1, 0.1, .1, 0.79 - t + 3, 2.83, 2.75, 0, 90, 0 + i, cubeVAO, lightingShader);
       //        }
       //    }
       //  
       //   

       //}


       ///////////////////////////////////////////////////////////2nd station//////////////////////////////////////////////////

       ////platform

        //rail track side wall
       cube8.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(195, 3, -30, -4 + 60.5, 2.1, 0, 0, 0, 0));
       cube8.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(195, 3, 30, -4 + 60.5, 2.1, 3, 0, 0, 0));
       
       //stair
       for (int i = 2, j = 1; i < 20; i += 2, j += 1)
       {
           // white_color(3, 1, 15, 0.8 + (i * 0.1), 0.1 + (j * 0.1), 8.0, 0, 0, 0, cubeVAO, lightingShader);

           cube9.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, 15, 0.8 + (i * 0.1) + 60.5, 0.1 + (j * 0.1), 8.0, 0, 0, 0));
       }
       for (int i = 2, j = 1; i < 24; i += 2, j += 1)
       {
           //  white_color(15, 1, 3, 2.5, 1.0 + (j * 0.1), 7.9 - (i * 0.1), 0, 0, 0, cubeVAO, lightingShader);
           cube10.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(15, 1, 3, 2.5 + 60.5, 1.0 + (j * 0.1), 7.9 - (i * 0.1), 0, 0, 0));

       }
       cube9.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(15, 1, 15, 2.5 + 60.5, 1.1, 8.0, 0, 0, 0));

       //63, 30, 1, -3.8, 2.4, 5.8, 0, 0, 0

       cube11.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(63, 30, 1, -3.8 + 60.5, 2.4, 5.8, 0, 0, 0));
       cube12.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 30, -20, -3.8 + 60.5, 2.4, 5.8, 0, 0, 0));


       //platform 1 wall
       cube11.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(40, 30, 1, 4 + 60.5, 2.4, 5.8, 0, 0, 0));
       cube12.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(10.9, 30, 1, 7 + 60.5, 2.4, 3.8, 0, 0, 0));
       cube13.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(10, -6, 1, 6 + 60.5, 5.4, 3.8, 0, 0, 0));
       cube11.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 30, -19.5, 8 + 60.5, 2.4, 5.8, 0, 0, 0));


       ////ticket counter

       cube12.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 30, -6, 6 + 60.5, 2.39, 5.8, 0, 0, 0));
       cube12.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 30, -7, 6 + 60.5, 2.391, 4.5, 0, 0, 0));
       cube12.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, -10, 14, 6 + 60.5, 5.391, 4.5, 0, 0, 0));
       cube12.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 10, 14, 6 + 60.5, 2.39, 4.5, 0, 0, 0));

       ////platform roof


       cube14.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(119, 1, -21, -3.8 + 60.5, 5.4, 5.9, 0, 0, 0));
       cube14.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(119, 1, -21, -3.8 + 60.5, 5.4, -0.5, 0, 0, 0));

       //passenger stand line at counter

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-16, 0.5, 0.5, 5.8 + 60.5, 3.4, 4.5, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-16, 0.5, 0.5, 5.8 + 60.5, 3.4, 5.1, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-10, 0.5, 0.5, 5.8 + 60.5, 3.4, 5.1, 0, 0, 90));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-10, 0.5, 0.5, 5.8 + 60.5, 3.4, 4.5, 0, 0, 90));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-10, 0.5, 0.5, 5.3 + 60.5, 3.4, 5.1, 0, 0, 90));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-10, 0.5, 0.5, 5.3 + 60.5, 3.4, 4.5, 0, 0, 90));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-10, 0.5, 0.5, 4.8 + 60.5, 3.4, 5.1, 0, 0, 90));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-10, 0.5, 0.5, 4.8 + 60.5, 3.4, 4.5, 0, 0, 90));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-10, 0.5, 0.5, 4.3 + 60.5, 3.4, 5.1, 0, 0, 90));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-10, 0.5, 0.5, 4.3 + 60.5, 3.4, 4.5, 0, 0, 90));

      
       //seat at ticket counter



       //bench1
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.1 + 60.5, 2.4, 5.5, 0, 0, 10));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.5 + 60.5, 2.4, 5.5, 0, 0, -10));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.1 + 60.5, 2.4, 4, 0, 0, 10));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.5 + 60.5, 2.4, 4, 0, 0, -10));
       cube16.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(5, 0.5, -16.5, -3.5 + 60.5, 2.75, 5.6, 0, 0, 5));
       cube16.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(5, 0.5, -16.5, -3.45 + 60.5, 2.75, 5.6, 0, 0, 100));
       //bench2
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.1 + 1 + 60.5, 2.4, 5.5, 0, 0, 10));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.5 + 1 + 60.5, 2.4, 5.5, 0, 0, -10));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.1 + 1 + 60.5, 2.4, 4, 0, 0, 10));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.5 + 1 + 60.5, 2.4, 4, 0, 0, -10));
       cube16.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(5, 0.5, -16.5, -3.5 + 1 + 60.5, 2.75, 5.6, 0, 0, 5));
       cube16.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(5, 0.5, -16.5, -3.45 + 1 + 60.5, 2.75, 5.6, 0, 0, 100));
       //bench3
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.1 + 2 + 60.5, 2.4, 5.5, 0, 0, 10));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.5 + 2 + 60.5, 2.4, 5.5, 0, 0, -10));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.1 + 2 + 60.5, 2.4, 4, 0, 0, 10));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.5 + 2 + 60.5, 2.4, 4, 0, 0, -10));
       cube16.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(5, 0.5, -16.5, -3.5 + 2 + 60.5, 2.75, 5.6, 0, 0, 5));
       cube16.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(5, 0.5, -16.5, -3.45 + 2 + 60.5, 2.75, 5.6, 0, 0, 100));
       //bench4
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.1 + 3 + 60.5, 2.4, 5.5, 0, 0, 10));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.5 + 3 + 60.5, 2.4, 5.5, 0, 0, -10));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.1 + 3 + 60.5, 2.4, 4, 0, 0, 10));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.5 + 3 + 60.5, 2.4, 4, 0, 0, -10));
       cube16.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(5, 0.5, -16.5, -3.5 + 3 + 60.5, 2.75, 5.6, 0, 0, 5));
       cube16.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(5, 0.5, -16.5, -3.45 + 3 + 60.5, 2.75, 5.6, 0, 0, 100));
       //bench5
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.1 + 4 + 60.5, 2.4, 5.5, 0, 0, 10));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.5 + 4 + 60.5, 2.4, 5.5, 0, 0, -10));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.1 + 4 + 60.5, 2.4, 4, 0, 0, 10));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 4, 0.5, -3.5 + 4 + 60.5, 2.4, 4, 0, 0, -10));
       cube16.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(5, 0.5, -16.5, -3.5 + 4 + 60.5, 2.75, 5.6, 0, 0, 5));
       cube16.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(5, 0.5, -16.5, -3.45 + 4 + 60.5, 2.75, 5.6, 0, 0, 100));


       //2nd platform brench

       //bench1

       cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 5, 0.5, -1.5 + 60.5, 2.4, -1.2, -10, 0, 0));
       cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 5, 0.5, 1.5 + 60.5, 2.4, -1.2, -10, 0, 0));
       cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 5, 0.5, 0 + 60.5, 2.4, -1.2, -10, 0, 0));
       cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 5, 0.5, 0 + 60.5, 2.4, -1.8, 10, 0, 0));
       cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 5, 0.5, -1.5 + 60.5, 2.4, -1.8, 10, 0, 0));
       cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 5, 0.5, 1.5 + 60.5, 2.4, -1.8, 10, 0, 0));
       cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(32, 0.5, -5, -1.6 + 60.5, 2.9, -1.2, -5, 0, 0));
       cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(32, 0.5, -5, -1.6 + 60.5, 2.9, -1.7, 80, 0, 0));
       //bench 2
       cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 5, 0.5, -1.5 + 5 + 60.5, 2.4, -1.2, -10, 0, 0));
       cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 5, 0.5, 1.5 + 5 + 60.5, 2.4, -1.2, -10, 0, 0));
       cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 5, 0.5, 0 + 5 + 60.5, 2.4, -1.2, -10, 0, 0));
       cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 5, 0.5, 0 + 5 + 60.5, 2.4, -1.8, 10, 0, 0));
       cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 5, 0.5, -1.5 + 5 + 60.5, 2.4, -1.8, 10, 0, 0));
       cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 5, 0.5, 1.5 + 5 + 60.5, 2.4, -1.8, 10, 0, 0));
       cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(32, 0.5, -5, -1.6 + 5 + 60.5, 2.9, -1.2, -5, 0, 0));
       cube17.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(32, 0.5, -5, -1.6 + 5 + 60.5, 2.9, -1.7, 80, 0, 0));




       //overbridge 
       // 
       // overbridge left stair
       //low handle 1

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(23, 0.5, 0.5, 8.5 + 0.5 + 60.5, 2.4, -0.5, 0, 0, 45));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(23, 0.5, 0.5, 8.5 + 0.5 + 60.5, 2.4, -2, 0, 0, 45));

       //upper handle 1

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(22, 0.5, 0.5, 8.5 + 0.5 + 60.5, 3.4, -0.5, 0, 0, 45));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(22, 0.5, 0.5, 8.5 + 0.5 + 60.5, 3.4, -2, 0, 0, 45));

       //stair pillar 1

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 12, 0.5, 8.5 + 0.5 + 60.5, 2.4, -2, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 12, 0.5, 8.5 + 0.5 + 60.5, 2.4, -0.5, 0, 0, 0));

       //stair1

       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 8.4 + 0.5 + 60.5, 2.4, -0.47, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 8.6 + 0.5 + 60.5, 2.6, -0.47, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 8.8 + 0.5 + 60.5, 2.8, -0.47, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 9.0 + 0.5 + 60.5, 3.0, -0.47, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 9.2 + 0.5 + 60.5, 3.2, -0.47, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 9.4 + 0.5 + 60.5, 3.4, -0.47, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 9.6 + 0.5 + 60.5, 3.6, -0.47, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 9.8 + 0.5 + 60.5, 3.8, -0.47, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(12, 1, -15, 10.0 + 0.5 + 60.5, 4.0, -0.47, 0, 0, 0));

       //stair2

      // cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 11.1 + 0.5, 4.0, -0.47, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 11.3 + 0.5 + 60.5, 4.2, -0.47, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 11.5 + 0.5 + 60.5, 4.4, -0.47, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 11.7 + 0.5 + 60.5, 4.6, -0.47, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 11.9 + 0.5 + 60.5, 4.8, -0.47, 0, 0, 0));

       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 12.1 + 0.5 + 60.5, 5.0, -0.47, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 12.3 + 0.5 + 60.5, 5.2, -0.47, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 12.5 + 0.5 + 60.5, 5.4, -0.47, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 12.7 + 0.5 + 60.5, 5.6, -0.47, 0, 0, 0));


       //stair pillar 2

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 10, 0.5, 10.0 + 0.5 + 60.5, 4.0, -2, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 10, 0.5, 10.0 + 0.5 + 60.5, 4.0, -0.5, 0, 0, 0));

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 10, 0.5, 11.2 + 0.5 + 60.5, 4.0, -2, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 10, 0.5, 11.2 + 0.5 + 60.5, 4.0, -0.5, 0, 0, 0));

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 17, 1, 10.0 + 0.5 + 60.5, 2.4, -2, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 17, 1, 10.0 + 0.5 + 60.5, 2.4, -0.5, 0, 0, 0));

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 17, 1, 11.2 + 0.5 + 60.5, 2.4, -2, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 17, 1, 11.2 + 0.5 + 60.5, 2.4, -0.5, 0, 0, 0));



       //middle handle
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(12, 0.5, 0.5, 10.54 + 60.5, 4.9, -2, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(12, 0.5, 0.5, 10.54 + 60.5, 4.9, -0.5, 0, 0, 0));



       ////low handle 2
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(25, 0.5, 0.5, 11.2 + 0.5 + 60.5, 4.0, -0.5, 0, 0, 45));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(25, 0.5, 0.5, 11.2 + 0.5 + 60.5, 4.0, -2, 0, 0, 45));

       //upper handle 2

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(25, 0.5, 0.5, 11.7 + 60.5, 4.9, -0.5, 0, 0, 45));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(25, 0.5, 0.5, 11.7 + 60.5, 4.9, -2, 0, 0, 45));

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 60, 1, 12.9 + 0.5 + 60.5, 2.4, -2, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 60, 1, 12.9 + 0.5 + 60.5, 2.4, -0.5, 0, 0, 0));


       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 60, 1, 14.2 + 0.5 + 60.5, 2.4, -2, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 60, 1, 14.2 + 0.5 + 60.5, 2.4, -0.5, 0, 0, 0));

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 60, 1, 14.2 + 0.5 + 60.5, 2.4, -2, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 60, 1, 14.2 + 0.5 + 60.5, 2.4, -0.5, 0, 0, 0));

       //top handle 

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 9, 0.5, 12.9 + 0.5 + 60.5, 5.8, -2, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 9, 0.5, 12.9 + 0.5 + 60.5, 5.8, -0.5, 0, 0, 0));

       //over Bridge wall + floor
       cube21.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(13, 1, 75, 12.9 + 0.5 + 60.5, 5.8, -2, 0, 0, 0));
       cube22.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(-75, 10, 0.1, 14.7 + 60.5, 5.8, -2, 0, 90, 0));
       cube23.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 10, 45, 12.9 + 0.5 + 60.5, 5.8, 4.0, 0, 180, 0));
       cube24.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 10, 13, 12.9 + 0.5 + 60.5, 5.8, -2, 0, 90, 0));
       cube24.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 10, 13, 12.9 + 0.5 + 60.5, 5.8, 5.5, 0, 90, 0));
       cube24.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 10, 13, 12.9 + 0.5 + 60.5, 5.8, 5.5, 0, 90, 0));
       cube24.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(14, 1, 76, 12.9 + 0.5 + 60.5, 8.4, -2, 0, 0, 0));


       //overbridge right stair

        //low handle 1

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(23, 0.5, 0.5, 8.5 + 0.5 + 60.5, 2.4, -0.5 + 6, 0, 0, 45));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(23, 0.5, 0.5, 8.5 + 0.5 + 60.5, 2.4, -2 + 6, 0, 0, 45));

       //upper handle 1

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(22, 0.5, 0.5, 8.5 + 0.5 + 60.5, 3.4, -0.5 + 6, 0, 0, 45));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(22, 0.5, 0.5, 8.5 + 0.5 + 60.5, 3.4, -2 + 6, 0, 0, 45));

       //stair pillar 1

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 12, 0.5, 8.5 + 0.5 + 60.5, 2.4, -2 + 6, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 12, 0.5, 8.5 + 0.5 + 60.5, 2.4, -0.5 + 6, 0, 0, 0));

       //stair1

       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 8.4 + 0.5 + 60.5, 2.4, -0.47 + 6, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 8.6 + 0.5 + 60.5, 2.6, -0.47 + 6, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 8.8 + 0.5 + 60.5, 2.8, -0.47 + 6, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 9.0 + 0.5 + 60.5, 3.0, -0.47 + 6, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 9.2 + 0.5 + 60.5, 3.2, -0.47 + 6, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 9.4 + 0.5 + 60.5, 3.4, -0.47 + 6, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 9.6 + 0.5 + 60.5, 3.6, -0.47 + 6, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 9.8 + 0.5 + 60.5, 3.8, -0.47 + 6, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(12, 1, -15, 10.0 + 0.5 + 60.5, 4.0, -0.47 + 6, 0, 0, 0));

       //stair2

      // cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 11.1 + 0.5, 4.0, -0.47, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 11.3 + 0.5 + 60.5, 4.2, -0.47 + 6, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 11.5 + 0.5 + 60.5, 4.4, -0.47 + 6, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 11.7 + 0.5 + 60.5, 4.6, -0.47 + 6, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 11.9 + 0.5 + 60.5, 4.8, -0.47 + 6, 0, 0, 0));

       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 12.1 + 0.5 + 60.5, 5.0, -0.47 + 6, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 12.3 + 0.5 + 60.5, 5.2, -0.47 + 6, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 12.5 + 0.5 + 60.5, 5.4, -0.47 + 6, 0, 0, 0));
       cube20.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 1, -15, 12.7 + 0.5 + 60.5, 5.6, -0.47 + 6, 0, 0, 0));


       //stair pillar 2

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 10, 0.5, 10.0 + 0.5 + 60.5, 4.0, -2 + 6, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 10, 0.5, 10.0 + 0.5 + 60.5, 4.0, -0.5 + 6, 0, 0, 0));

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 10, 0.5, 11.2 + 0.5 + 60.5, 4.0, -2 + 6, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 10, 0.5, 11.2 + 0.5 + 60.5, 4.0, -0.5 + 6, 0, 0, 0));

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 17, 1, 10.0 + 0.5 + 60.5, 2.4, -2 + 6, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 17, 1, 10.0 + 0.5 + 60.5, 2.4, -0.5 + 6, 0, 0, 0));

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 17, 1, 11.2 + 0.5 + 60.5, 2.4, -2 + 6, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 17, 1, 11.2 + 0.5 + 60.5, 2.4, -0.5 + 6, 0, 0, 0));



       //middle handle
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(12, 0.5, 0.5, 10.54 + 60.5, 4.9, -2 + 6, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(12, 0.5, 0.5, 10.54 + 60.5, 4.9, -0.5 + 6, 0, 0, 0));



       ////low handle 2
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(25, 0.5, 0.5, 11.2 + 0.5 + 60.5, 4.0, -0.5 + 6, 0, 0, 45));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(25, 0.5, 0.5, 11.2 + 0.5 + 60.5, 4.0, -2 + 6, 0, 0, 45));

       //upper handle 2

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(25, 0.5, 0.5, 11.7 + 60.5, 4.9, -0.5 + 6, 0, 0, 45));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(25, 0.5, 0.5, 11.7 + 60.5, 4.9, -2 + 6, 0, 0, 45));

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 60, 1, 12.9 + 0.5 + 60.5, 2.4, -2 + 6, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 60, 1, 12.9 + 0.5 + 60.5, 2.4, -0.5 + 6, 0, 0, 0));


       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 60, 1, 14.2 + 0.5 + 60.5, 2.4, -2 + 6, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 60, 1, 14.2 + 0.5 + 60.5, 2.4, -0.5 + 6, 0, 0, 0));

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 60, 1, 14.2 + 0.5 + 60.5, 2.4, -2 + 6, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(1, 60, 1, 14.2 + 0.5 + 60.5, 2.4, -0.5 + 6, 0, 0, 0));

       //top handle 

       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 9, 0.5, 12.9 + 0.5 + 60.5, 5.8, -2 + 6, 0, 0, 0));
       cube15.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.5, 9, 0.5, 12.9 + 0.5 + 60.5, 5.8, -0.5 + 6, 0, 0, 0));


       //stair

       white_color(18.5, 1, 1, 1 + 60.5, 1.1, 9.4, 0, 0, 33, cubeVAO, lightingShader);
       white_color(18.5, 1, 1, 1 + 60.5, 1.1, 8.0, 0, 0, 33, cubeVAO, lightingShader);

       // white_color(15, 1, 15, 2.5, 1.1, 8.0, 0, 0, 0, cubeVAO, lightingShader);


       white_color(1, 1, -25, 3.9 + 60.5, 1.12, 8, 28, 0, 0, cubeVAO, lightingShader);
       white_color(1, 1, -25, 2.5 + 60.5, 1.12, 8, 28, 0, 0, cubeVAO, lightingShader);

       white_color(1, 1, -25, 3.9 + 60.5, 2.12, 8, 28, 0, 0, cubeVAO, lightingShader);
       white_color(1, 1, -25, 2.5 + 60.5, 2.12, 8, 28, 0, 0, cubeVAO, lightingShader);

       white_color(1, 11, 1, 3.9 + 60.5, 0.01, 9.4, 0, 0, 0, cubeVAO, lightingShader);
       white_color(1, 11, 1, 3.9 + 60.5, 0.01, 8, 0, 0, 0, cubeVAO, lightingShader);
       white_color(1, 11, 1, 2.5 + 60.5, 0.01, 9.4, 0, 0, 0, cubeVAO, lightingShader);
       white_color(1, 11, 1, 2.5 + 60.5, 0.01, 8.0, 0, 0, 0, cubeVAO, lightingShader);


       white_color(1, 9.84, 1, 1.1 + 60.5, 0.3, 9.4, 0, 0, 0, cubeVAO, lightingShader);
       white_color(1, 9.84, 1, 1.1 + 60.5, 0.3, 8, 0, 0, 0, cubeVAO, lightingShader);

       white_color(1, 12, 1, 2.5 + 60.5, 1.0, 9.4, 0, 0, 0, cubeVAO, lightingShader);
       white_color(1, 12, 1, 2.5 + 60.5, 2, 6, 0, 0, 0, cubeVAO, lightingShader);

       white_color(1, 12, 1, 3.9 + 60.5, 2, 6, 0, 0, 0, cubeVAO, lightingShader);

       white_color(1, 12, 1, 2.5 + 60.5, 1.0, 8, 0, 0, 0, cubeVAO, lightingShader);
       white_color(1, 12, 1, 3.9 + 60.5, 1.0, 8, 0, 0, 0, cubeVAO, lightingShader);
       white_color(1, 12, 1, 3.9 + 60.5, 1.0, 9.4, 0, 0, 0, cubeVAO, lightingShader);

       white_color(14, 1, 1, 2.55 + 60.5, 2.1, 9.4, 0, 0, 0, cubeVAO, lightingShader);
       white_color(14, 1, 1, 3.9 + 60.5, 2.1, 9.4, 0, 90, 0, cubeVAO, lightingShader);

       //ticket counter texture
       cube2.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.1, 2, 4, 5.99 + 60.5, 4.5, 4.65, 0, 0, 0));

       //2nd platform pillar
       white_color(1, 30, 1, -3.5 + 60.5, 2.4, -1.5, 0, 0, 0, cubeVAO, lightingShader);
       chocolate_color(1, 1, -20, -3.5 + 60.5, 5.3, -0.5, 0, 0, 0, cubeVAO, lightingShader);

       white_color(1, 30, 1, 2.8 + 60.5, 2.4, -1.5, 0, 0, 0, cubeVAO, lightingShader);
       chocolate_color(1, 1, -20, 2.8 + 60.5, 5.3, -0.5, 0, 0, 0, cubeVAO, lightingShader);

       white_color(1, 30, 1, 7.5 + 60.5, 2.4, -1.5, 0, 0, 0, cubeVAO, lightingShader);
       chocolate_color(1, 1, -20, 7.5 + 60.5, 5.3, -0.5, 0, 0, 0, cubeVAO, lightingShader);

       //advertise texture
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(0.2, 9, 7, -3.4 + 60.5, 3.5, -1.8, 0, 0, 0));

       //under platform pillar
       cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 20, 3, -3.8 + 60.5, 0.1, -2.8, 0, 0, 0));
       cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 20, 3, -3.8 + 60.5, 0.1, 5.5, 0, 0, 0));
       cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 20, 3, -3.8 + 4 + 60.5, 0.1, -2.8, 0, 0, 0));
       cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 20, 3, -3.8 + 4 + 60.5, 0.1, 5.5, 0, 0, 0));
       cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 20, 3, -3.8 + 8 + 60.5, 0.1, -2.8, 0, 0, 0));
       cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 20, 3, -3.8 + 8 + 60.5, 0.1, 5.5, 0, 0, 0));
       cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 20, 3, -3.8 + 12 + 60.5, 0.1, -2.8, 0, 0, 0));
       cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 20, 3, -3.8 + 12 + 60.5, 0.1, 5.5, 0, 0, 0));
       cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 20, 3, -3.8 + 16 + 60.5, 0.1, -2.8, 0, 0, 0));
       cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 20, 3, -3.8 + 16 + 60.5, 0.1, 5.5, 0, 0, 0));
       cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 20, 3, -3.8 + 18.8 + 60.5, 0.1, -2.8, 0, 0, 0));
       cube6.drawCubeWithTexture(lightingShaderWithTexture, model_Matrix(3, 20, 3, -3.8 + 19 + 60.5, 0.1, 5.5, 0, 0, 0));


       /////////////////////////////////////////////// 2nd Station End ////////////////////////////////////////////


       /////////////////////////////////////////////////Date:13-11-23/////////////////////////////////////////////

      /* train_door_left2(0.7, 1, 1, 0+3.2, 0, 0, 0, 0, 0, cubeVAO, lightingShader);
       train_door_right2(0.7, 1, 1, 0+3.12, 0, 0, 0, 0, 0, cubeVAO, lightingShader);*/

  /*     train_door_left2(0.7, 1, 1, 0 + 3.2 + 3.5-0.5, 0, 0, 0, 0, 0, cubeVAO, lightingShader);
       train_door_right2(0.7, 1, 1, 0 + 3.12 + 3.5-.5, 0, 0, 0, 0, 0, cubeVAO, lightingShader);


       train_door_left2(0.7, 1, 1, 0 + 3.2 + 3.5 - 0.5-3, 0, 0-1.15, 0, 0, 0, cubeVAO, lightingShader);
       train_door_right2(0.7, 1, 1, 0 + 3.12 + 3.5 - .5-3, 0, 0-1.15, 0, 0, 0, cubeVAO, lightingShader);


        train_door_left2(0.7, 1, 1, 0+3.2+3, 0, 0 - 1.13, 0, 0, 0, cubeVAO, lightingShader);
        train_door_right2(0.7, 1, 1, 0+3.12+3, 0, 0 - 1.13, 0, 0, 0, cubeVAO, lightingShader);


        train_door_left2(0.7, 1, 1, 0 + 3.2 + 6, 0,0, 0, 0, 0, cubeVAO, lightingShader);
        train_door_right2(0.7, 1, 1, 0 + 3.12 + 6, 0, 0, 0, 0, 0, cubeVAO, lightingShader);

        train_door_left3(1, 1, 1, 0 + 3.2 + 5.85, 0, -1.13, 0, 0, 0, cubeVAO, lightingShader);
       train_door_right3(1, 1, 1, 0 + 3.12 + 5.85, 0, -1.13, 0, 0, 0, cubeVAO, lightingShader);*/

       train_doorSpeed = 0.6;

      // cout <<"train_reverse_start"<< train_reverse_start << endl;

       if (!train_start && !train_reverse_start)
       {   

         /*  if (train_door_open)
           {*/
               //train_doorTranslate = carPosition.x;
               // train_door_translate(1, 1, 1, 0 + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);
               train_doorTranslate += train_doorSpeed * deltaTime;
               if (train_doorTranslate > 0.590132)
               {
                   train_doorTranslate = 0.590132;

               }
                train_door_left(1, 1, 1, 0 - train_doorTranslate + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);//left door1 open
                train_door_right(1, 1, 1, 0 + train_doorTranslate + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);//right door1 open


                train_door_left2(0.7, 1, 1, 0 + 3.2 - train_doorTranslate + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);//left door2 open
                train_door_right2(0.7, 1, 1, 0 + 3.12 + train_doorTranslate + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);//right door2 open

                train_door_left2(0.7, 1, 1, 0 + 3.2 + 3.5 - 0.5 - train_doorTranslate + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);
                train_door_right2(0.7, 1, 1, 0 + 3.12 + 3.5 - .5 + train_doorTranslate + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);


                train_door_left2(0.7, 1, 1, 0 + 3.2 + 3.5 - 0.5 - 3 - train_doorTranslate + carPosition.x, 0, 0 - 1.15, 0, 0, 0, cubeVAO, lightingShader);
                train_door_right2(0.7, 1, 1, 0 + 3.12 + 3.5 - .5 - 3 + train_doorTranslate + carPosition.x, 0, 0 - 1.15, 0, 0, 0, cubeVAO, lightingShader);


                train_door_left2(0.7, 1, 1, 0 + 3.2 + 3 - train_doorTranslate + carPosition.x, 0, 0 - 1.13, 0, 0, 0, cubeVAO, lightingShader);
                train_door_right2(0.7, 1, 1, 0 + 3.12 + 3 + train_doorTranslate + carPosition.x, 0, 0 - 1.13, 0, 0, 0, cubeVAO, lightingShader);


                train_door_left2(1, 1, 1, 0 + 3.2 + 6 - train_doorTranslate + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);
                train_door_right4(1, 1, 1, 0 + 3.12 + 6 + train_doorTranslate + carPosition.x-0.3, 0, 0, 0, 0, 0, cubeVAO, lightingShader);

                train_door_left3(1, 1, 1, 0 + 3.2 + 6 - train_doorTranslate + carPosition.x, 0, -1.13, 0, 0, 0, cubeVAO, lightingShader);
                train_door_right3(1, 1, 1, 0 + 3.12 + 6 + train_doorTranslate + carPosition.x, 0, -1.13, 0, 0, 0, cubeVAO, lightingShader);

               //train_door_translate(1, 1, 1, 0 + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);
               //train_door_translate(1, 1, 1, 0 + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);
              // train_door_left_opened(1, 1, 1, 0 + train_doorTranslate, 0, 0, 0, 0, 0, cubeVAO, lightingShader);
              // train_door_right_opened(1, 1, 1, 0 + train_doorTranslate, 0, 0, 0, 0, 0, cubeVAO, lightingShader);
          /* }
           else
           {
               train_door_translate(1, 1, 1, 0 + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);
           }*/
           

       }
       else if (train_reverse_start)
       {
           

               train_doorTranslate -= train_doorSpeed * deltaTime;
               if (train_doorTranslate < 0.00366335)
               {
                   train_doorTranslate = 0.00366335;

               }
               train_door_left(1, 1, 1, 0 + train_doorTranslate + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);//left door closed
               train_door_right(1, 1, 1, 0 - train_doorTranslate + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);//right door closed
           
               train_door_left2(0.7, 1, 1, 0 + 3.2 + train_doorTranslate + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);//left door2 open
               train_door_right2(0.7, 1, 1, 0 + 3.12 - train_doorTranslate + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);//right door2 open

               train_door_left2(0.7, 1, 1, 0 + 3.2 + 3.5 - 0.5 + train_doorTranslate + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);
               train_door_right2(0.7, 1, 1, 0 + 3.12 + 3.5 - .5 - train_doorTranslate + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);


               train_door_left2(0.7, 1, 1, 0 + 3.2 + 3.5 - 0.5 - 3 + train_doorTranslate + carPosition.x, 0, 0 - 1.15, 0, 0, 0, cubeVAO, lightingShader);
               train_door_right2(0.7, 1, 1, 0 + 3.12 + 3.5 - .5 - 3 - train_doorTranslate + carPosition.x, 0, 0 - 1.15, 0, 0, 0, cubeVAO, lightingShader);


               train_door_left2(0.7, 1, 1, 0 + 3.2 + 3 + train_doorTranslate + carPosition.x, 0, 0 - 1.13, 0, 0, 0, cubeVAO, lightingShader);
               train_door_right2(0.7, 1, 1, 0 + 3.12 + 3 - train_doorTranslate + carPosition.x, 0, 0 - 1.13, 0, 0, 0, cubeVAO, lightingShader);


               train_door_left2(0.7, 1, 1, 0 + 3.2 + 6 + train_doorTranslate + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);
               train_door_right2(0.7, 1, 1, 0 + 3.12 + 6 - train_doorTranslate + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);

               train_door_left3(1, 1, 1, 0 + 3.2 + 5.85 + train_doorTranslate + carPosition.x, 0, -1.13, 0, 0, 0, cubeVAO, lightingShader);
               train_door_right3(1, 1, 1, 0 + 3.12 + 5.85 - train_doorTranslate + carPosition.x, 0, -1.13, 0, 0, 0, cubeVAO, lightingShader);
       }
       else
       {
          
             
           
          
               train_doorTranslate -= train_doorSpeed * deltaTime;
               if (train_doorTranslate < 0.00366335)
               {
                   train_doorTranslate = 0.00366335;
                   train_door_closed = false;
               }
               train_door_left(1, 1, 1, 0 + train_doorTranslate + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);//left door closed
               train_door_right(1, 1, 1, 0 - train_doorTranslate + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);//right door closed

               train_door_left2(0.7, 1, 1, 0 + 3.2 + train_doorTranslate + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);//left door2 open
               train_door_right2(0.7, 1, 1, 0 + 3.12 - train_doorTranslate + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);//right door2 open
               
               train_door_left2(0.7, 1, 1, 0 + 3.2 + 3.5 - 0.5 + train_doorTranslate + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);
               train_door_right2(0.7, 1, 1, 0 + 3.12 + 3.5 - .5 - train_doorTranslate + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);


               train_door_left2(0.7, 1, 1, 0 + 3.2 + 3.5 - 0.5 - 3 + train_doorTranslate + carPosition.x, 0, 0 - 1.15, 0, 0, 0, cubeVAO, lightingShader);
               train_door_right2(0.7, 1, 1, 0 + 3.12 + 3.5 - .5 - 3 - train_doorTranslate + carPosition.x, 0, 0 - 1.15, 0, 0, 0, cubeVAO, lightingShader);


               train_door_left2(0.7, 1, 1, 0 + 3.2 + 3 + train_doorTranslate + carPosition.x, 0, 0 - 1.13, 0, 0, 0, cubeVAO, lightingShader);
               train_door_right2(0.7, 1, 1, 0 + 3.12 + 3 - train_doorTranslate + carPosition.x, 0, 0 - 1.13, 0, 0, 0, cubeVAO, lightingShader);


               train_door_left2(0.7, 1, 1, 0 + 3.2 + 6 + train_doorTranslate + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);
               train_door_right2(0.7, 1, 1, 0 + 3.12 + 6 - train_doorTranslate + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);

               train_door_left3(1, 1, 1, 0 + 3.2 + 5.85 + train_doorTranslate + carPosition.x, 0, -1.13, 0, 0, 0, cubeVAO, lightingShader);
               train_door_right3(1, 1, 1, 0 + 3.12 + 5.85 - train_doorTranslate + carPosition.x, 0, -1.13, 0, 0, 0, cubeVAO, lightingShader);
          
              
               //train_door_left_closed(1, 1, 1, 0 + train_doorTranslate + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);
              // train_door_left_closed(1, 1, 1, 0 + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);
              // train_door_right_closed(1, 1, 1, 0 + train_doorTranslate + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);
              // train_door_right_closed(1, 1, 1, 0 + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);
               //train_door_translate(1, 1, 1, 0 + carPosition.x, 0, 0, 0, 0, 0, cubeVAO, lightingShader);
         /*  else
           {
               train_door_off(1, 1, 1, 0 + train_doorTranslate, 0, 0, 0, 0, 0, cubeVAO, lightingShader);
               train_door_opened(1, 1, 1, 0 + train_doorTranslate, 0, 0, 0, 0, 0, cubeVAO, lightingShader);
           }*/
       }
      
      
       ///camera controll
       
       if (journey)
       {
          camera.Position.x = carPosition.x;
       }
    
      // cout << "car position " << carPosition.x<<" "<< carPosition.y<<" "<< carPosition.z<< endl;




        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &cubeEBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
   // lightingShader.setVec3("material.emission", glm::vec3(0.0f, 0.0f, 0.0));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(cubeVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}




//void bed(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
//{
//    float baseHeight = 0.3;
//    float width = 1;
//    float length = 2;
//    float pillowWidth = 0.3;
//    float pillowLength = 0.15;
//    float blanketWidth = 0.8;
//    float blanketLength = 0.7;
//    float headHeight = 0.6;
//
//    //base
//    glm::mat4 model = glm::mat4(1.0f);
//    glm::mat4 translate = glm::mat4(1.0f);
//    glm::mat4 translate2 = glm::mat4(1.0f);
//    glm::mat4 scale = glm::mat4(1.0f);
//    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
//    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
//    model = alTogether * scale * translate;
//    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);
//
//    //foam
//    model = glm::mat4(1.0f);
//    translate = glm::mat4(1.0f);
//    translate2 = glm::mat4(1.0f);
//    scale = glm::mat4(1.0f);
//    translate2 = glm::translate(model, glm::vec3(0, baseHeight, 0));
//    scale = glm::scale(model, glm::vec3(width, 0.06, length));
//    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
//    model = alTogether * translate2 * scale * translate;
//    drawCube(cubeVAO, lightingShader, model, 0.804, 0.361, 0.361);
//
//    //pillow 1
//    model = glm::mat4(1.0f);
//    translate = glm::mat4(1.0f);
//    translate2 = glm::mat4(1.0f);
//    scale = glm::mat4(1.0f);
//    translate2 = glm::translate(model, glm::vec3((width / 2) - (0.1 + pillowWidth / 2), baseHeight + 1 * 0.06, (length / 2) - (0.025 + pillowWidth / 2)));
//    scale = glm::scale(model, glm::vec3(pillowWidth, 0.04, pillowLength));
//    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
//    model = alTogether * translate2 * scale * translate;
//    drawCube(cubeVAO, lightingShader, model, 1, 0.647, 0);
//
//    //pillow 2
//    model = glm::mat4(1.0f);
//    translate = glm::mat4(1.0f);
//    translate2 = glm::mat4(1.0f);
//    scale = glm::mat4(1.0f);
//    translate2 = glm::translate(model, glm::vec3((-width / 2) + (0.1 + pillowWidth / 2), baseHeight + 1 * 0.06, (length / 2) - (0.025 + pillowWidth / 2)));
//    scale = glm::scale(model, glm::vec3(pillowWidth, 0.04, pillowLength));
//    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
//    model = alTogether * translate2 * scale * translate;
//    drawCube(cubeVAO, lightingShader, model, 1, 0.647, 0);
//
//    //blanket
//    model = glm::mat4(1.0f);
//    translate = glm::mat4(1.0f);
//    translate2 = glm::mat4(1.0f);
//    scale = glm::mat4(1.0f);
//    translate2 = glm::translate(model, glm::vec3(0, baseHeight + 1 * 0.06, -(length / 2 - 0.025) + blanketLength / 2));
//    scale = glm::scale(model, glm::vec3(blanketWidth, 0.015, blanketLength));
//    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
//    model = alTogether * translate2 * scale * translate;
//    drawCube(cubeVAO, lightingShader, model, 0.541, 0.169, 0.886);
//
//    //head
//    model = glm::mat4(1.0f);
//    translate = glm::mat4(1.0f);
//    translate2 = glm::mat4(1.0f);
//    scale = glm::mat4(1.0f);
//    translate2 = glm::translate(model, glm::vec3(0, 0, (length / 2 - 0.02 / 2) + 0.02));
//    scale = glm::scale(model, glm::vec3(width, headHeight, 0.02));
//    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
//    model = alTogether * translate2 * scale * translate;
//    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);
//
//}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
   
   
 /*   if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
        camera.Position.x = 6.87976;
        camera.Position.y = 3.47278;
        camera.Position.z = 2.04601;
    }*/
    ////Station first
    //if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
    //    camera.Position.x = 1;
    //    camera.Position.x = 1;
    //    camera.Position.x = 1;
    //}
    ////OverBridge of first station
    //if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
    //    camera.Position.x = 13.7022;
    //    camera.Position.x = 7.5667;
    //    camera.Position.x = 1.1337;
    //}

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        if (rotateAxis_X) rotateAngle_X -= 0.1;
        else if (rotateAxis_Y) rotateAngle_Y -= 0.1;
        else rotateAngle_Z -= 0.1;
    }
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) translate_Y += 0.001;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) translate_Y -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) translate_X += 0.001;
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) translate_X -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) translate_Z += 0.001;
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) translate_Z -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) scale_X += 0.001;
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) scale_X -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) scale_Y += 0.001;
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) scale_Y -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) scale_Z += 0.001;
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) scale_Z -= 0.001;

   if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
       /* rotateAngle_X += 0.1;
        rotateAxis_X = 1.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;*/
     
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
       /* rotateAngle_Y += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 1.0;
        rotateAxis_Z = 0.0;*/
        camera.ProcessKeyboard(PITCH_L, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        /*rotateAngle_Z += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 1.0;*/
        camera.ProcessKeyboard(YAW_LEFT, deltaTime);
    }

    /*if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    {
        eyeX += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        eyeX -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        eyeZ += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        eyeZ -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        eyeY += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        eyeY -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }*/

    //watch tower view
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {

        camera.Position.x = 13.7739;
        camera.Position.y = 10.9974;
        camera.Position.z = 6.44895;


    }
    //lake View
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {

        camera.Position.x = 40.0016;
        camera.Position.y = 3.25747;
        camera.Position.z = 9.91365;

    }
    //under platform view
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {

        camera.Position.x = -3.83701;
        camera.Position.y = 0.646074;
        camera.Position.z = 1.37649;

    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {

        camera.Position.x = 62.576;
        camera.Position.y = 4.47686;
        camera.Position.z = -1.54892;

    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {

        camera.Position.x = -0.95148;
        camera.Position.y = 2.39266;
        camera.Position.z = 1.69789;

    }
}

//toggle button

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        if (pointLightOn)
        {
            pointlight1.turnOff();
            pointlight2.turnOff();
            pointlight3.turnOff();
            pointlight4.turnOff();
            pointlight5.turnOff();
            pointlight6.turnOff();
            pointLightOn = !pointLightOn; 
        }
        else
        {
            pointlight1.turnOn();
            pointlight2.turnOn();
             pointlight3.turnOn();
             pointlight4.turnOn();
             pointlight5.turnOn();
             pointlight6.turnOn();
             /* pointlight4.turnOn();*/
            pointLightOn = !pointLightOn;
        }
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
        if (spotLightOn)
        {
            spotlight1.turnOff();
            spotlight2.turnOff();
            spotlight3.turnOff();
            spotlight4.turnOff();
            spotlight5.turnOff();
            spotlight6.turnOff();
            spotlight7.turnOff();
            spotlight8.turnOff();
            spotlight9.turnOff();
            spotlight10.turnOff();
            spotlight11.turnOff();
            spotlight12.turnOff();
            spotlight13.turnOff();
            spotlight14.turnOff();
            spotlight15.turnOff();
            spotlight16.turnOff();
            spotlight17.turnOff();
            spotlight18.turnOff();
            spotlight19.turnOff();
            spotlight20.turnOff();
            spotlight21.turnOff();
            spotlight22.turnOff();
            spotlight23.turnOff();
            spotlight24.turnOff();
            spotlight25.turnOff();
            spotlight26.turnOff();
            spotlight27.turnOff();
            spotlight28.turnOff();
            spotlight29.turnOff();
            spotlight30.turnOff();
            spotlight31.turnOff();
            spotlight32.turnOff();
            spotlight33.turnOff();
            spotlight34.turnOff();
            spotlight35.turnOff();
            spotlight36.turnOff();
            spotlight37.turnOff();
            spotlight38.turnOff();

            spotLightOn = !spotLightOn;
        }
        else
        {


            spotlight1.turnOn();
            spotlight2.turnOn();
            spotlight3.turnOn();
            spotlight4.turnOn();
            spotlight5.turnOn();
            spotlight6.turnOn();
            spotlight7.turnOn();
            spotlight8.turnOn();
            spotlight9.turnOn();
            spotlight10.turnOn();
            spotlight11.turnOn();
            spotlight12.turnOn();
            spotlight13.turnOn();
            spotlight14.turnOn();
            spotlight15.turnOn();
            spotlight16.turnOn();
            spotlight17.turnOn();
            spotlight18.turnOn();
            spotlight19.turnOn();
            spotlight20.turnOn();
            spotlight21.turnOn();
            spotlight22.turnOn();
            spotlight23.turnOn();
            spotlight24.turnOn();
            spotlight25.turnOn();
            spotlight26.turnOn();
            spotlight27.turnOn();
            spotlight28.turnOn();
            spotlight29.turnOn();
            spotlight30.turnOn();
            spotlight31.turnOn();
            spotlight32.turnOn();
            spotlight33.turnOn();
            spotlight34.turnOn();
            spotlight35.turnOn();
            spotlight36.turnOn();
            spotlight37.turnOn();
            spotlight38.turnOn();
            
            spotLightOn = !spotLightOn;
        }
    }
    if (key == GLFW_KEY_3 && action == GLFW_PRESS)
    {
        if (directionLightOn)
        {
            directionlight1.turnOff();
            directionLightOn = !directionLightOn;
        }
        else
        {
            directionlight1.turnOn();
            directionLightOn = !directionLightOn;
        }
    }
    if (key == GLFW_KEY_F && action == GLFW_PRESS)
    {
        if (!fan_on)
        {
            fan_on = true;
        }
        else
        {
            fan_on = false;
        }

    }

    if (key == GLFW_KEY_4 && action == GLFW_PRESS)
    {
        // cout << "Hi" << endl;
        if (ambientToggle)
        {

            pointlight1.turnAmbientOff();
            pointlight2.turnAmbientOff();
            pointlight3.turnAmbientOff();
            pointlight4.turnAmbientOff();
            pointlight5.turnAmbientOff();
            pointlight6.turnAmbientOff();
            ambientToggle = !ambientToggle;
        }
        else
        {
            pointlight1.turnAmbientOn();
            pointlight2.turnAmbientOn();
            pointlight3.turnAmbientOn();
            pointlight4.turnAmbientOn();
            pointlight5.turnAmbientOn();
            pointlight6.turnAmbientOn();
            ambientToggle = !ambientToggle;
        }
    }
    if (key == GLFW_KEY_5 && action == GLFW_PRESS)
    {
        // cout << "Hi" << endl;
        if (diffuseToggle)
        {

            pointlight1.turnDiffuseOff();
            pointlight2.turnDiffuseOff();
            pointlight3.turnDiffuseOff();
            pointlight4.turnDiffuseOff();
            pointlight5.turnDiffuseOff();
            pointlight6.turnDiffuseOff();
            diffuseToggle = !diffuseToggle;
        }
        else
        {
            pointlight1.turnDiffuseOn();
            pointlight2.turnDiffuseOn();
            pointlight3.turnDiffuseOn();
            pointlight4.turnDiffuseOn();
            pointlight5.turnDiffuseOn();
            pointlight6.turnDiffuseOn();
            diffuseToggle = !diffuseToggle;
        }
    }
    if (key == GLFW_KEY_6 && action == GLFW_PRESS)
    {
        // cout << "Hi" << endl;
        if (specularToggle)
        {

            pointlight1.turnSpecularOff();
            pointlight2.turnSpecularOff();
            pointlight3.turnSpecularOff();
            pointlight4.turnSpecularOff();
            pointlight5.turnSpecularOff();
            pointlight6.turnSpecularOff();
            specularToggle = !specularToggle;
        }
        else
        {
            pointlight1.turnSpecularOn();
            pointlight2.turnSpecularOn();
            pointlight3.turnSpecularOn();
            pointlight4.turnSpecularOn();
            pointlight5.turnSpecularOn();
            pointlight6.turnSpecularOn();
            specularToggle = !specularToggle;
        }
    }
    if (key == GLFW_KEY_T && action == GLFW_PRESS)
    {
        if (!train_start)
        {
            train_start = true;
            train_start_release = false;
            train_reverse_start = false;
            train_reverse_start_release = false;
            carSpeed = 1.0f;
            glm::vec3 carPosition(0.0f, 0.0f, 0.0f);
            wheelRotation = 0.0f;
            t = 1.0f;
        }
        
    }
   if (key == GLFW_KEY_T && action == GLFW_RELEASE)
    {
        
       train_start = false;
       train_start_release = true;
       train_reverse_start = false;
       train_reverse_start_release = false;
           
       
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS)
    {
        if (!train_reverse_start)
        {
            train_start = false;
            train_start_release = false;
            train_reverse_start = true;
            train_reverse_start_release = false;

            carSpeed = 1.0f;
            glm::vec3 carPosition(0.0f, 0.0f, 0.0f);
            wheelRotation = 0.0f;
            t = 1.0f;

        }
       
    }
    if (key == GLFW_KEY_R && action == GLFW_RELEASE)
    {
        //cout << "R release" << endl;
        train_start = false;
        train_start_release = false;
        train_reverse_start = false;
        train_reverse_start_release = true;

    }

    if (key== GLFW_KEY_J && action == GLFW_PRESS) {

        if (!journey)
        {
            journey = true;
           // cout << "journey true" << endl;
        }
        else
        {
            journey = false;
          //  cout << "journey false" << endl;
        }


    }
   
    
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
