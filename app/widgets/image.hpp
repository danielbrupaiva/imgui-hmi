#pragma once
//https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples#example-for-opengl-users
#include <filesystem>
#include <glfw.hpp>
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

#include "logger.hpp"
#include "i_widget.hpp"

namespace App::Widget
{
class Image: public IWidget
{
public:
	enum class Format
	{
		None, RGBA, RGBA32F
	};

public:
	explicit Image(IMGUI &ui, std::filesystem::path &&filename)
		: IWidget(ui), m_filename(filename)
	{
		set_id(load_texture_from_file(m_filename));
		set_label(m_filename.stem().string());
	};

	explicit Image(IMGUI &ui,
				   const ImVec2 &size,
				   const ImVec2 &position,
				   const std::filesystem::path &&filename)
		: IWidget(ui, filename.stem().string(), size, position), m_filename(filename)
	{
		set_id(load_texture_from_file(m_filename));
	}

	virtual void operator()()
	{
		render();
	}

	virtual void operator()(const ImVec2 &size, const ImVec2 &position)
	{
		set_position(position);
		set_size(size);
		operator()();
	}

	void resize(const ImVec2 &size)
	{
		// Calculate resize ratio
		float width_ratio = (float)size.x / (float)get_width();
		float height_ratio = (float)size.y / (float)get_height();
		// Choose the smaller ratio to maintain aspect ratio
		float resize_ratio = (width_ratio < height_ratio) ? width_ratio : height_ratio;
		// Calculate new dimensions
		m_size.x *= resize_ratio;
		m_size.y *= resize_ratio;
	}

	void render() override
	{
		Layout::set_position(m_gravity, m_position, m_size);
		ImGui::Image(ID(), m_size);
	}

	uint32_t load_texture_from_file(const std::filesystem::path &filename)
	{
		int32_t width = 0;
		int32_t height = 0;

		unsigned char *image_data = stbi_load(filename.string().c_str(), &width, &height, NULL, m_channels);
		if (!image_data) {
			std::string msg = "STBI_LOAD FAILS TO LOAD THE IMAGE";
			logger.error("{}", msg);
			throw std::runtime_error(msg);
		}
		ImVec2 size{static_cast<float>(width), static_cast<float>(height)};
		set_size(size);
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

private:
	Format m_format = Format::None;
	int32_t m_channels = STBI_rgb_alpha;
	std::filesystem::path m_filename;
};
}