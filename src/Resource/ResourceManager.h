#pragma once

#include <map>
#include <string>
#include <memory>

namespace Render {
    class ShaderRender;
}

namespace Resource {
    class ResourceManager {
    public:
        ResourceManager(const std::string& programPath);
        ~ResourceManager() = default;

        ResourceManager() = delete;
        ResourceManager(const ResourceManager&) = delete;
        ResourceManager(ResourceManager&&) = delete;
        ResourceManager& operator=(const ResourceManager&) = delete;
        ResourceManager& operator=(ResourceManager&&) = delete;

        std::shared_ptr<Render::ShaderRender> LoadShader(const std::string& shaderName, const std::string& vertexShader,
            const std::string& fragmentShader);
        std::shared_ptr<Render::ShaderRender> GetShader(const std::string& shaderName);
    private:
        std::string GetFileSource(const std::string& relativePath) const;

        using ResourceManagerMap = std::map<std::string, std::shared_ptr<Render::ShaderRender>>;
        ResourceManagerMap shaderProgram;
        std::string path;
    };
}