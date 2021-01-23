#include <SFML/Graphics.hpp>
#include "SemiCircle.hpp"

int main()
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));

	float aspect = sf::VideoMode::getDesktopMode().width * 1.f / sf::VideoMode::getDesktopMode().height;
	float touchscale = sf::VideoMode::getDesktopMode().height * 1.f / 1080;
	
    // Define some constants
    const float pi = 3.14159f;
    const int gameWidth = (int)(1080 * aspect);
    const int gameHeight = 1080;
    
    sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 32), "SFML SemiCircle", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(60);
    text.setString("SemiCircle Test");
    text.setPosition(sf::Vector2f(700,15));
    
    SemiCircle semi(sf::Vector2f(50.f,50.f));
    semi.setPosition(500.f,500.f);
    semi.setOutlineThickness(2.f);
    semi.setOutlineColor({0,0,0});
    
    SemiCircle semi2(sf::Vector2f(50.f,50.f),0,18);
    semi2.setPosition(sf::Vector2f(575.f,500.f));
    semi2.setOutlineThickness(2.f);
    semi2.setOutlineColor({0,0,0});
    
    SemiCircle semi3(sf::Vector2f(50.f,50.f),9,28);
    semi3.setPosition(700.f,500.f);
    semi3.setOutlineThickness(2.f);
    semi3.setOutlineColor({0,0,0});
    
    SemiCircle semi4(sf::Vector2f(100.f,100.f),9,19);
    semi4.setPosition(800.f,400.f);
    semi4.setOutlineThickness(2.f);
    semi4.setOutlineColor({0,0,0});
        
    SemiCircle semi5(sf::Vector2f(50.f,50.f),18,23);
    semi5.setPosition(400.f,500.f);
    semi5.setOutlineThickness(2.f);
    semi5.setOutlineColor({0,0,0});
    
    
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }
        
        window.clear(sf::Color::Green);
        window.draw(text);
        window.draw(semi);
        window.draw(semi2);
        window.draw(semi3);
        window.draw(semi4);
        window.draw(semi5);
        window.display();
    }
    return 0;
}