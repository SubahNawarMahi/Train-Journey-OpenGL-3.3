#ifndef CURVE_H
#define CURVE_H

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "shader.h"
#include "CurvedRoad.h"

// Vertex structure

class Curve {
public:
    Curve(const glm::mat4& model, const std::string& texturePath,
        const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3,
        int numSegments, float tunnelRadius, int circlePoints);

    ~Curve();

    void init();
    void draw(Shader& shader);

private:
    GLuint VAO, VBO, texture;
    glm::mat4 modelMatrix;
    std::vector<Vertex> vertices;
    std::string texturePath;
    glm::vec3 p0, p1, p2, p3;
    int numSegments, circlePoints;
    float tunnelRadius;

    GLuint loadTexture(const std::string& filename);
    void createMesh();
    std::vector<glm::vec3> tessellateBezier();
    glm::vec3 bezierPoint(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, float t);
};

#endif // TUNNEL_H
