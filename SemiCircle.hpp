#ifndef SEMI_CIRCLE_HPP
#define SEMI_CIRCLE_HPP

#include <SFML/Graphics.hpp>

class SemiCircle : public sf::Drawable , public sf::Transformable 
{
public:
    SemiCircle(sf::Vector2f radius = sf::Vector2f(0.f,0.f), std::size_t start = 18, std::size_t end = 36, std::size_t pointCount = 36);
    virtual ~SemiCircle() {}
    
    void setFillColor(sf::Color color);
    void setHighlightColor(sf::Color color);
    void setOutlineColor(sf::Color color);
    void setOutlineThickness(float thickness);
    void setRadius(sf::Vector2f radius);
    void setPointCount(std::size_t count);
    void setStartEnd(std::size_t start, std::size_t end);
    sf::Color getFillColor();
    sf::Color getHighlightColor();
    sf::Color getOutlineColor();
    sf::Vector2f getRadius();
    float getOutlineThickness();
    std::size_t getPointCount();
    sf::Vector2f getPoint(std::size_t index) const;
    sf::FloatRect getLocalBounds() const;
    sf::FloatRect getGlobalBounds() const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update();
    void updateFillColors();
    void updateTexCoords();
    void updateOutline();
    void updateOutlineColors();
    sf::Vector2f computeNormal(const sf::Vector2f& p1, const sf::Vector2f& p2);
    float dotProduct(const sf::Vector2f& p1, const sf::Vector2f& p2);
 
    sf::Vector2f m_radius;
    std::size_t m_pointCount;
    std::size_t m_startCount;
    std::size_t m_endCount;
    sf::FloatRect m_bounds;
    sf::FloatRect m_insideBounds;
    sf::Color m_fillColor;
    sf::Color m_highlightColor;
    sf::Color m_outlineColor;
    float m_outlineThickness;
    sf::VertexArray m_vertices;
    sf::VertexArray m_outlineVertices;
};

#endif // SEMI_CIRCLE_HPP
