#ifndef GLSLSHADER_H
#define GLSLSHADER_H

#include "glad/glad.h"
#include "noncopyable.h"
#include <map>
#include <iostream>
class GLSLShader : public Noncopyable
{
private:
    GLuint ID;
    std::map<std::string, GLuint> m_Uniforms;
    void checkCompileErrors(unsigned int shader, std::string type);
public:
    GLSLShader(const char* vertexPath, const char* fragmentPath);
    ~GLSLShader();

    void addUniform(std::string name);
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void Use();
};

#endif // GLSLSHADER_H
