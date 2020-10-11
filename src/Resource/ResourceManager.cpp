#include "ResourceManager.h"
#include "../Render/ShaderRender.h"

#include <iostream>
#include <sstream>
#include <fstream>

namespace Resource {
    ResourceManager::ResourceManager(const std::string& programPath) {
        uint16_t number = programPath.find_last_of("/\\");
        path = programPath.substr(0, number);
    }

    std::shared_ptr<Render::ShaderRender> ResourceManager::LoadShader(const std::string& shaderName,
        const std::string& vertexShader, const std::string& fragmentShader) {
        std::string vertex_Shader = GetFileSource(vertexShader);
        if (vertex_Shader.empty()) {
            std::cout << "ERROR: Vertex shader file is empty!" << std::endl;
            return nullptr;
        }
        std::string fragment_Shader = GetFileSource(fragmentShader);
        if (fragment_Shader.empty()) {
            std::cout << "ERROR: Fragment shader file is empty!" << std::endl;
            return nullptr;
        }

        std::shared_ptr<Render::ShaderRender>& shader = shaderProgram.emplace(shaderName, std::make_shared<Render::ShaderRender>(
            vertex_Shader, fragment_Shader)).first->second;
        if (!shader->IsCompiled()) {
            std::cout << "ERROR: Can't create shader!" << std::endl;
            return nullptr;
        }

        return shader;
    }

    std::shared_ptr<Render::ShaderRender> ResourceManager::GetShader(const std::string& shaderName) {
        ResourceManagerMap::iterator res = shaderProgram.find(shaderName);
        if (res == shaderProgram.end()) {
            std::cout << "ERROR: Shader was not found!" << std::endl;
            return nullptr;
        }
        return res->second;
    }

    std::string ResourceManager::GetFileSource(const std::string& relativePath) const {
        std::ifstream file(path + '/' + relativePath, std::ios_base::in | std::ios_base::binary);
        if (!file.is_open()) {
            std::cout << "ERROR: opening resource file " << relativePath << " is failed!" << std::endl;
            return std::string();
        }

        std::stringstream ss;
        ss << file.rdbuf();
        file.close();
        return ss.str();
    }


}