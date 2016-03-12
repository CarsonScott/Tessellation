std::string to_string(float number)
{
    std::stringstream ss(std::stringstream::in | std::stringstream::out);
    ss << number;
    return ss.str();
}

sf::Vector2f getOffset(sf::Vector2f a, sf::Vector2f b)
{
    sf::Vector2f offset(b.x - a.x, b.y - a.y);
    return offset;
}

float getDistance(sf::Vector2f a, sf::Vector2f b)
{
    sf::Vector2f offset = getOffset(a, b);
    float distance = sqrt(pow(offset.x, 2) + pow(offset.y, 2));
    return distance;
}

class AdjustableView: public sf::View
{
public:
    void handleEvent(sf::Event& event)
    {
        if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::S){
                setSize(getSize().x * 1.25, getSize().y * 1.25);
            }
            if(event.key.code == sf::Keyboard::W){
                setSize(getSize().x / 1.25, getSize().y / 1.25);
            }
        }
    }
};

class Button: public sf::Text
{
    bool active;
public:
    Button()
    {
        active = false;
    }

    void handleEvent(sf::Event& event, sf::Vector2f mousePos)
    {
        if(event.type == sf::Event::MouseButtonPressed)
        {
            if(getGlobalBounds().contains(mousePos))
            {
                active = true;
            }
        }
    }

    bool selected()
    {
        return active;
    }

    void update()
    {
        active = false;
    }
};
