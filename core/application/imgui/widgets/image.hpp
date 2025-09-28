#pragma once

#include <filesystem>

#include "core.hpp"
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

#include "imgui.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

namespace Core::Application::ImGuiImpl::Widgets {

class Image : public Core::EnableSharedFromThis<Image> {
public:
    ~Image() override = default;
    explicit Image(std::filesystem::path &&filename) : m_filename(filename){
        m_textureID = load_texture_from_file(m_filename);
        logger.debug("Image {} loaded with ID: {}, size: {}x{}", m_filename.string(), m_textureID, m_size.x, m_size.y);
    }

    void Render() const {
        ImGui::Image(m_textureID, {m_size.x, m_size.y});
    }

    void operator()() const {
        Render();
    }

    void operator()(const glm::vec2& size) {
        Resize(size);
        operator()();
    }

    void operator()(const glm::vec2& size, const glm::vec2& position) {
        ImGui::SetCursorPos({position.x, position.y});
        operator()(size);
    }

    [[nodiscard]] uint32_t ID() const {
        return m_textureID;
    }

    [[nodiscard]] const glm::vec2 &Size() const {
        return m_size;
    }

private:

    uint32_t load_texture_from_file(const std::filesystem::path &filename) {

        int32_t width = 0, height = 0;
        auto image_data = stbi_load(filename.string().c_str(), &width, &height, NULL, m_channels);
        if (!image_data) {
            std::string msg = "STBI_LOAD FAILS TO LOAD THE IMAGE";
            logger.error("{}", msg);
            throw std::runtime_error(msg);
        }
        m_size = {static_cast<float>(width), static_cast<float>(height)};

        // Create a OpenGL texture identifier
        uint32_t textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        // Setup filtering parameters for display
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_WRAP_S,
                        GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

        // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
        // Free image_data*
        stbi_image_free(image_data);

        return textureID;
    }

    void Resize(const glm::vec2 &size) {
        // Calculate resize ratio
        float width_ratio = (float)size.x / (float)m_size.x ;
        float height_ratio = (float)size.y / (float)m_size.y ;
        // Choose the smaller ratio to maintain aspect ratio
        float resize_ratio = (width_ratio < height_ratio) ? width_ratio : height_ratio;
        // Calculate new dimensions
        m_size.x *= resize_ratio;
        m_size.y *= resize_ratio;
    }

private:
    uint32_t m_textureID;
    glm::vec2 m_size = {0.0f, 0.0f};
    int32_t m_channels = STBI_rgb_alpha;
    std::filesystem::path m_filename;
};
}