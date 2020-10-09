#include "ShaderRender.h"
#include <iostream>

namespace Render {
    ShaderRender::ShaderRender(const std::string& vertexShader, const std::string& fragmentShader) {
        GLuint vertexShaderID;
        if (!CreateShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID)) {
            std::cout << "VERTEX SHASER: Compile time error! " << std::endl;
            return;
        }

        GLuint fragmentShaderID;
        if (!CreateShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID)) {
            std::cout << "FRAGMENT SHASER: Compile time error! " << std::endl;
            glDeleteShader(vertexShaderID);
            return;
        }

        id = glCreateProgram();
        glAttachShader(id, vertexShaderID);
        glAttachShader(id, fragmentShaderID);
        glLinkProgram(id);

        GLint success;
        glGetShaderiv(id, GL_LINK_STATUS, &success);
        if (!success) {
            isCompiled = false;
            GLchar infoLog[1024];
            glGetShaderInfoLog(id, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER: Link time error! " << infoLog << std::endl;
        } else {
            isCompiled = true;
        }

        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }

    ShaderRender::ShaderRender(ShaderRender&& copy) noexcept {
        isCompiled = copy.isCompiled;
        id = copy.id;

        copy.isCompiled = false;
        copy.id = 0;
    }

    ShaderRender& ShaderRender::operator=(ShaderRender&& copy) noexcept {
        glDeleteProgram(id);
        isCompiled = copy.isCompiled;
        id = copy.id;

        copy.isCompiled = false;
        copy.id = 0;

        return *this;
    }

    ShaderRender::~ShaderRender() {
        glDeleteProgram(id);
    }

    void ShaderRender::Use() const {
        glUseProgram(id);
    }

    bool ShaderRender::CreateShader(const std::string& source, const GLenum shaderType, GLuint& shaderID) {
        shaderID = glCreateShader(shaderType);
        const char* code = source.c_str();
        glShaderSource(shaderID, 1, &code, nullptr);
        glCompileShader(shaderID);

        GLint success;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLchar infoLog[1024];
            glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER: Compile time error! " << infoLog << std::endl;
            return false;
        }
        return true;
    }
}