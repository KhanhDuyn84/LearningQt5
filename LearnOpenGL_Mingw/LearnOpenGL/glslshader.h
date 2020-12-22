#ifndef GLSLSHADER_H
#define GLSLSHADER_H

#include "glad/glad.h"
#include "noncopyable.h"
#include "glm/glm.hpp"
#include <map>
#include <iostream>

namespace GSEngine
{

class GLSLShader : public Noncopyable
{
private:
    GLuint ID;
    std::map<std::string, GLuint> m_Uniforms;
    std::map<std::string, GLuint> m_Attributes;
    void checkCompileErrors(unsigned int shader, std::string type);
public:
    GLSLShader(const char* vertexPath, const char* fragmentPath);
    ~GLSLShader();

    void addUniform(const std::string& uniform);
    void addAttribute(const std::string& attribute);
    GLuint operator[](const std::string& attribute);
    GLuint operator()(const std::string& uniform);
    void setBool(const std::string &name,const bool &value) const;
    void setInt(const std::string &name,const int &value) const;
    void setFloat(const std::string &name,const float &value) const;
    void setVec2(const std::string &name,const glm::vec2 &value) const;
    void setVec3(const std::string &name,const glm::vec3 &value) const;
    void setVec4(const std::string &name,const glm::vec4 &value) const;
    void setMat4(const std::string &name,const glm::mat4 &value) const;
    void Use();
    void UnUse();
};

}
#endif // GLSLSHADER_H
