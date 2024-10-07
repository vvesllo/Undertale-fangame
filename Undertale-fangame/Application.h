#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

class Application
{
private:
	float m_dt, m_dt_k;
	unsigned short m_framerate_limit;
	size_t m_window_width;
	size_t m_window_height;
	std::shared_ptr<sf::RenderWindow> m_window;
	sf::Color m_background_color;
	sf::Event m_event;
	sf::Clock m_delta_clock;
	sf::Time m_delta_time;
	sf::View m_view;

	void update();

protected:
	
	void initWindow(
		size_t width,
		size_t height,
		std::string title,
		unsigned short framerate_limit
	);
	void initView(
		sf::FloatRect rect,
		sf::Vector2f size
	);

	// custom update
	virtual void selfUpdate();
	// draw everything
	virtual void draw();
	// check every keys
	virtual void checkKeys();
	// polling every events(like window close button press)
	virtual void pollEvent(sf::Event _event);

	// Getters
	std::shared_ptr<sf::RenderWindow> getWindowPtr();
	size_t getWindowWidth();
	size_t getWindowHeight();
	sf::Color getBackgroundColor();
	sf::View& getView();
	float getDeltaTime();
	float getDeltaTimeK();
	unsigned short getFramerateLimit();

	// Setters
	void setBackgroundColor(sf::Color color);
	void setDeltaTimeK(float k);

public:
	Application();
	void runLoop();
};

