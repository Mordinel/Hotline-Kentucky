#include <SFML/Graphics.hpp>

#define LINE_VERTEX_COUNT 2
#define FIRE_ANIMATION_LEN 0.5f

class Gun : public sf::Drawable {
private:
    sf::VertexArray sightLine;
    float totalTime;
    float switchTime;

    void setColor(sf::Color color);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    Gun();
    ~Gun();
    void SetLineCoordinates(sf::Vector2f playerPos, sf::Vector2f cursorPos);
    void Fire();
    void Update(float* deltaTime);
};