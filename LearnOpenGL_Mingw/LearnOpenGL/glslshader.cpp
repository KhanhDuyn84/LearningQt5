#include "glslshader.h"
#include "glm/gtc/type_ptr.hpp"
#include <fstream>
#include <sstream>

namespace GSEngine
{

GLSLShader::GLSLShader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char * fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void GLSLShader::checkCompileErrors(unsigned int shader, std::string type)
   {
       int success;
       char infoLog[1024];
       if (type != "PROGRAM")
       {
           glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
           if (!success)
           {
               glGetShaderInfoLog(shader, 1024, NULL, infoLog);
               std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
           }
       }
       else
       {
           glGetProgramiv(shader, GL_LINK_STATUS, &success);
           if (!success)
           {
               glGetProgramInfoLog(shader, 1024, NULL, infoLog);
               std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
           }
       }
   }

void GLSLShader::addUniform(const std::string &uniform)
{
    m_Uniforms[uniform] = glGetUniformLocation(ID, uniform.c_str());
}

void GLSLShader::addAttribute(const std::string& attribute)
{
    m_Attributes[attribute] = glGetAttribLocation(ID, attribute.c_str());
}

void GLSLShader::Use()
{
    glUseProgram(ID);
}

void GLSLShader::UnUse()
{
     glUseProgram(0);
}

void GLSLShader::setBool(const std::string &name,const bool &value) const
{
    if(m_Uniforms.find(name) == m_Uniforms.end())
        return;
    glUniform1i(m_Uniforms.at(name), (int)value);
}

void GLSLShader::setInt(const std::string &name,const int &value) const
{
    if(m_Uniforms.find(name) == m_Uniforms.end())
        return;
    glUniform1i(m_Uniforms.at(name), value);
}

void GLSLShader::setFloat(const std::string &name,const float &value) const
{
    if(m_Uniforms.find(name) == m_Uniforms.end())
        return;
    glUniform1f(m_Uniforms.at(name), value);
}

void GLSLShader::setVec2(const std::string &name,const glm::vec2 &value) const
{
    if(m_Uniforms.find(name) == m_Uniforms.end())
        return;
   glUniform2fv(m_Uniforms.at(name), 1, glm::value_ptr(value));
}

void GLSLShader::setVec3(const std::string &name,const glm::vec3 &value) const
{
    if(m_Uniforms.find(name) == m_Uniforms.end())
    {
        return;
    }
   glUniform3fv(m_Uniforms.at(name), 1,  &value[0]);
}

void GLSLShader::setVec4(const std::string &name,const glm::vec4 &value) const
{
    if(m_Uniforms.find(name) == m_Uniforms.end())
        return;
    glUniform4fv(m_Uniforms.at(name), 1,  &value[0]);
}

void GLSLShader::setMat4(const std::string &name,const glm::mat4 &value) const
{
    if(m_Uniforms.find(name) == m_Uniforms.end())
        return;
    glUniformMatrix4fv(m_Uniforms.at(name), 1, GL_FALSE, glm::value_ptr(value));
}


GLuint GLSLShader::operator()(const std::string &uniform)
{
    if(m_Uniforms.find(uniform) != m_Uniforms.end())
    {
        return m_Uniforms[uniform];
    }
    else
    {
        std::cout<<"UNIFORM COULD NOT BE FOUND"<<std::endl;
        return -1;
    }
}

GLuint GLSLShader::operator[](const std::string &attribute)
{
    if(m_Attributes.find(attribute) != m_Attributes.end())
    {
        return m_Attributes[attribute];
    }
    else
    {
        std::cout<<"ATTRIBUTE COULD NOT BE FOUND"<<std::endl;
        return -1;
    }
}

GLSLShader::~GLSLShader()
{
    glDeleteProgram(ID);
}

}
