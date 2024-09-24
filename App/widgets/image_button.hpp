#pragma once

#include "logger.hpp"
#include "button.hpp"
#include "image.hpp"

namespace App
{
class ImageButton: public Button
{
	std::unique_ptr<Image> m_image;
	std::filesystem::path m_filename;
public:
	ImageButton(const std::string_view &label,
				const ImVec2 &size,
				const ImVec2 &position,
				const std::function<void()> &callback,
				const std::filesystem::path &&filename)
		: Button(label, size, position, callback), m_filename(filename)
	{
		m_image = std::make_unique<Image>(std::move(m_filename), size);
	}

	bool operator()() override
	{
		render();
		return get_state();
	}

private:
	void render() override
	{
		throw std::runtime_error("Not implemented");
	}
};

}