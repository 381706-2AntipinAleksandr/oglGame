#pragma once

#include <glad/glad.h>
#include <string>

namespace Render {
    class ShaderRender {
    public:
        ShaderRender() = delete;
        ShaderRender(const std::string& vertexShader, const std::string& fragmentShader);
        ShaderRender(const ShaderRender& copy) = delete;
        ShaderRender(ShaderRender&& copy) noexcept;
        ~ShaderRender();
        ShaderRender& operator=(const ShaderRender& copy) = delete;
        ShaderRender& operator=(ShaderRender&& copy) noexcept;
        bool IsCompiled() const { return isCompiled; }
        void Use() const;
    private:
        bool CreateShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
        bool isCompiled;
        GLuint id;
    };
}