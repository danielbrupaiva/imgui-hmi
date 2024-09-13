#include "fakeit.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace fakeit;

#include "screen_manager.hpp"

TEST_CASE("ScreenManager class")
{
	std::vector<std::unique_ptr<App::IScreen>> screens_container;

	auto screen1 = std::make_unique<App::Screen1>("Screen1", ImVec2(1280, 720));
	screens_container.push_back(std::move(screen1));
	auto screen2 = std::make_unique<App::Screen2>("Screen2", ImVec2(1280, 720));
	screens_container.push_back(std::move(screen2));
	auto screen3 = std::make_unique<App::Screen3>("Screen3", ImVec2(1280, 720));
	screens_container.push_back(std::move(screen3));
	auto screen4 = std::make_unique<App::Screen4>("Screen4", ImVec2(1280, 720));
	screens_container.push_back(std::move(screen4));
	auto screen5 = std::make_unique<App::Screen5>("Screen5", ImVec2(1280, 720));
	screens_container.push_back(std::move(screen5));

	App::ScreenManager app{App::ScreenManager::eState::SCREEN1, screens_container};
	REQUIRE(app.get_current_state() == App::ScreenManager::eState::SCREEN1);

	app.set_current_state(App::ScreenManager::eState::SCREEN4);
	REQUIRE(app.get_current_state() == App::ScreenManager::eState::SCREEN4);
}
