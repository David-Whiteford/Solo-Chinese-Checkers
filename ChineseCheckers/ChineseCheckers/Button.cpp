 #include "Button.h"

Button::Button()
{
	//Setting up Font
	if (!m_font.loadFromFile("Assets/Fonts/QuickSmart.otf"))
	{
	}

	m_height = 30;
	m_width = 100;
	m_colorRect = sf::Color::White;
}

Button::~Button()
{
}

void Button::setInfo(std::string t_string, float t_width, float t_height, sf::Vector2f t_pos)
{
	m_button.setSize(sf::Vector2f(t_width, t_height));
	m_button.setPosition(sf::Vector2f(t_pos.x, t_pos.y));
	m_button.setOutlineThickness(2);
	m_button.setOutlineColor(m_colorRect);
	m_button.setFillColor(sf::Color::Black);
	m_text.setFillColor(sf::Color::White);
	m_text.setCharacterSize(20);
	m_text.setFont(m_font);
	m_text.setString(t_string);

	m_text.setPosition(sf::Vector2f(t_pos));
}

void Button::update(sf::Time t_deltaTime)
{

}

void Button::render(sf::RenderWindow& t_window)
{
	if (m_selected)
	{
		//std::cout << "drawing button" << std::endl;
		t_window.draw(m_button);
	}
	t_window.draw(m_text);
}

void Button::setup(sf::Font& t_font)
{
	m_font = t_font;
}

void Button::setSize(int t_size)
{
	m_text.setCharacterSize(t_size);
}

void Button::loadTextures()
{
}

void Button::setSelected(bool t_selected)
{
	m_selected = t_selected;
}
