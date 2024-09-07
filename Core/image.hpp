#pragma once
//https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples#example-for-opengl-users
#include <iostream>
#include <filesystem>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "logger.hpp"
#include "i_widget.hpp"

namespace Core
{
class Image: public IWidget
{
public:
	enum class Format
	{
		None, RGBA, RGBA32F
	};
private:
	Format m_format = Format::None;
	int32_t m_channels = STBI_rgb_alpha;
	std::filesystem::path m_filename;

public:
	explicit Image(const std::string_view filename)
		: m_filename(filename)
	{
		set_id(load_texture_from_file(m_filename));
		set_label(m_filename.stem().string());
	};

	explicit Image(const std::string_view filename, const ImVec2 &size)
		: m_filename(filename)
	{
		set_id(load_texture_from_file(m_filename));
		set_label(m_filename.stem().string());
		set_size(size);
	};

	void operator()()
	{
		ImGui::SetCursorPos(get_position());
		ImGui::Image(ID(), get_size());
	}

	void operator()(const ImVec2 &size)
	{
		set_size(size);
		operator()();
	}

	void operator()(const ImVec2 &size, const ImVec2 &position)
	{
		set_position(position);
		operator()(size);
	}

	void resize(const ImVec2 &size)
	{
		// Calculate resize ratio
		float width_ratio = (float)size.x / (float)get_width();
		float height_ratio = (float)size.y / (float)get_height();
		// Choose the smaller ratio to maintain aspect ratio
		float resize_ratio = (width_ratio < height_ratio) ? width_ratio : height_ratio;
		// Calculate new dimensions
		float target_width = (float)m_width * resize_ratio;
		float target_height = (float)m_height * resize_ratio;

		set_size(ImVec2(std::floor(target_width), std::floor(target_height)));
	}
private:
	uint32_t load_texture_from_file(const std::filesystem::path &filename)
	{
		unsigned char *image_data = stbi_load(filename.string().c_str(), &m_width, &m_height, NULL, m_channels);
		if (!image_data) {
			std::string msg = "STBI_LOAD FAILS TO LOAD THE IMAGE";
			logger.error("{}", msg);
			throw std::runtime_error(msg);
		}
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
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
		// Free image_data*
		stbi_image_free(image_data);

		return textureID;
	};

public:

	[[nodiscard]] inline Format get_format() const
	{
		return m_format;
	}
	inline void set_format(Format format)
	{
		m_format = format;
	}
	[[nodiscard]] inline ImTextureID ID() const
	{
		return reinterpret_cast<ImTextureID>(get_id());
	}

};
}