#include "SemiCircle.hpp"
#include <cmath>

SemiCircle::SemiCircle(sf::Vector2f radius, std::size_t start, std::size_t end, std::size_t pointCount) :
m_radius(radius),
m_start(start),
m_end(end),
m_pointCount(pointCount),
m_fillColor(255, 255, 255),
m_highlightColor(255, 255, 255),
m_outlineColor(255, 255, 255),
m_outlineThickness(0),
m_vertices(sf::TriangleFan),
m_outlineVertices(sf::TriangleStrip),
m_insideBounds(),
m_bounds()
{
    update();
}

void SemiCircle::setFillColor(sf::Color color)
{
    m_highlightColor = color; // Fill with default as solid
    m_fillColor = color;
    updateFillColors();
}

sf::Color SemiCircle::getFillColor()
{
    return m_fillColor;
}

void SemiCircle::setHighlightColor(sf::Color color)
{
    m_highlightColor = color;
    updateFillColors();
}

sf::Color SemiCircle::getHighlightColor()
{
    return m_highlightColor;
}

void SemiCircle::setOutlineColor(sf::Color color)
{
    m_outlineColor = color;
    updateOutlineColors();
}

sf::Color SemiCircle::getOutlineColor() 
{
    return m_outlineColor;
}

void SemiCircle::setRadius(sf::Vector2f radius)
{
    m_radius = radius;
    update();
}

sf::Vector2f SemiCircle::getRadius()
{
    return m_radius;
}

void SemiCircle::setStartEnd(std::size_t start, std::size_t end)
{
    m_start = start;
    m_end = end;
    update();
}

void SemiCircle::setOutlineThickness(float thickness)
{
    m_outlineThickness = thickness;
    update(); // recompute everything because the whole shape must be offset
}

float SemiCircle::getOutlineThickness()
{
    return m_outlineThickness;
}

sf::FloatRect SemiCircle::getLocalBounds() const
{
    return m_bounds;
}

sf::FloatRect SemiCircle::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}

void SemiCircle::setPointCount(std::size_t count)
{
    m_pointCount = count;
    update();
}

std::size_t SemiCircle::getPointCount()
{
    return m_pointCount;
}

sf::Vector2f SemiCircle::getPoint(std::size_t index) const
{
    static const float pi = 3.141592654f;
    
    float angle = index * 2 * pi / m_pointCount - pi / 2;
    float x = std::cos(angle) * m_radius.x;
    float y = std::sin(angle) * m_radius.y;

    return sf::Vector2f(m_radius.x + x, m_radius.y + y);
}

void SemiCircle::update()
{
    std::size_t count = m_end - m_start;
    std::size_t index = 1;
    m_vertices.resize(count+2);

    // updated this section
    if(count < (m_pointCount / 2))
    {
        m_vertices.resize(count+3);
        m_vertices[index].position = m_radius;
        ++index;
    }
    for(std::size_t i = m_start; i < m_end; ++i)
    {
        m_vertices[index].position = getPoint(i);
        ++index;
    }
    m_vertices[index].position = m_vertices[1].position;

    // Update the bounding rectangle
    m_vertices[0] = m_vertices[1]; // so that the result of getBounds() is correct
    m_insideBounds = m_vertices.getBounds();

    // Compute the center and make it the first vertex
    m_vertices[0].position.x = m_insideBounds.left + m_insideBounds.width / 2;
    m_vertices[0].position.y = m_insideBounds.top + m_insideBounds.height / 2;

    // Color
    updateFillColors();

    // Outline
    updateOutline();
}

void SemiCircle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    states.texture = NULL;
    target.draw(m_vertices, states);

    if (m_outlineThickness != 0)
    {
        target.draw(m_outlineVertices, states);
    }
}

void SemiCircle::updateFillColors()
{
    m_vertices[0].color = m_highlightColor;
    for (std::size_t i = 1; i < m_vertices.getVertexCount(); ++i)
        m_vertices[i].color = m_fillColor;
}

void SemiCircle::updateOutline()
{
    // Return if there is no outline
    if (m_outlineThickness == 0.f)
    {
        m_outlineVertices.clear();
        m_bounds = m_insideBounds;
        return;
    }

    std::size_t count = m_vertices.getVertexCount() - 2;
    m_outlineVertices.resize((count + 1) * 2);

    for (std::size_t i = 0; i < count; ++i)
    {
        std::size_t index = i + 1;

        // Get the two segments shared by the current point
        sf::Vector2f p0 = (i == 0) ? m_vertices[count].position : m_vertices[index - 1].position;
        sf::Vector2f p1 = m_vertices[index].position;
        sf::Vector2f p2 = m_vertices[index + 1].position;

        // Compute their normal
        sf::Vector2f n1 = computeNormal(p0, p1);
        sf::Vector2f n2 = computeNormal(p1, p2);

        // Make sure that the normals point towards the outside of the shape
        // (this depends on the order in which the points were defined)
        if (dotProduct(n1, m_vertices[0].position - p1) > 0)
            n1 = -n1;
        if (dotProduct(n2, m_vertices[0].position - p1) > 0)
            n2 = -n2;

        // Combine them to get the extrusion direction
        float factor = 1.f + (n1.x * n2.x + n1.y * n2.y);
        sf::Vector2f normal = (n1 + n2) / factor;

        // Update the outline points
        m_outlineVertices[i * 2 + 0].position = p1;
        m_outlineVertices[i * 2 + 1].position = p1 + normal * m_outlineThickness;
    }

    // Duplicate the first point at the end, to close the outline
    m_outlineVertices[count * 2 + 0].position = m_outlineVertices[0].position;
    m_outlineVertices[count * 2 + 1].position = m_outlineVertices[1].position;

    // Update outline colors
    updateOutlineColors();

    // Update the shape's bounds
    m_bounds = m_outlineVertices.getBounds();
}

void SemiCircle::updateOutlineColors()
{
    for (std::size_t i = 0; i < m_outlineVertices.getVertexCount(); ++i)
        m_outlineVertices[i].color = m_outlineColor;
}

sf::Vector2f SemiCircle::computeNormal(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
    sf::Vector2f normal(p1.y - p2.y, p2.x - p1.x);
    float length = std::sqrt(normal.x * normal.x + normal.y * normal.y);
    if (length != 0.f)
        normal /= length;
    return normal;
}

float SemiCircle::dotProduct(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
    return p1.x * p2.x + p1.y * p2.y;
}
