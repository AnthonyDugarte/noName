# include <HUD.hpp>

HUD::HUD(const Attributes & attributes, const std::string & folder)
:  healt(folder),
    m_attributes(attributes)
{
  // empty
}

void HUD::update(const sf::Time & dt, sf::RenderWindow & window)
{
  healt.update(dt, false);
  healt.setState(static_cast<healtState>(m_attributes.get_health()), true);

  healt.setPosition(window.mapPixelToCoords(sf::Vector2i(0, 0)));
}

void HUD::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  target.draw(healt, states);
}
