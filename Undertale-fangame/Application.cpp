#include "Application.h"

void Application::initWindow(
	size_t width,
	size_t height,
	std::string title,
	unsigned short framerate_limit
)
{
	m_window = std::make_shared<sf::RenderWindow>(
		sf::VideoMode(width, height),
		title
	);
	m_window_width = width;
	m_window_height = height;
	m_framerate_limit = framerate_limit;
	m_delta_clock = sf::Clock();
	m_window->setFramerateLimit(framerate_limit);
}

void Application::initView(
	sf::FloatRect rect,
	sf::Vector2f size
)
{
	m_view = sf::View();
	m_view.reset(
		rect
	);
	m_view.setSize(size);
}

Application::Application()
{
	m_dt = 0.f;
	m_dt_k = 1.f;
	m_framerate_limit = 0;
	m_window_width = 0;
	m_window_height = 0;
	m_event = sf::Event();
}

void Application::update()
{
	m_dt = m_delta_clock.getElapsedTime().asMicroseconds() / m_dt_k;
	m_delta_clock.restart();
	while (m_window->pollEvent(m_event))
		pollEvent(m_event);
	checkKeys();
}


void Application::selfUpdate() {}

void Application::draw() {}

void Application::checkKeys() {}

void Application::pollEvent(sf::Event _event) {}


void Application::runLoop()
{
	while (m_window->isOpen())
	{
		m_window->clear(m_background_color);
		update();
		selfUpdate();
		m_window->setView(m_view);
		draw();
		m_window->display();
	}
}

// Getters
std::shared_ptr<sf::RenderWindow> Application::getWindowPtr() { return m_window; }
size_t Application::getWindowWidth() { return m_window_width; }
size_t Application::getWindowHeight() { return m_window_height; }
sf::View& Application::getView() { return m_view; }
sf::Color Application::getBackgroundColor() { return m_background_color; }
unsigned short Application::getFramerateLimit() { return m_framerate_limit; }
float Application::getDeltaTime() { return m_dt; }
float Application::getDeltaTimeK() { return m_dt_k; }
// Setters
void Application::setBackgroundColor(sf::Color color) { m_background_color = color; }
void Application::setDeltaTimeK(float k) { m_dt_k = k; }
