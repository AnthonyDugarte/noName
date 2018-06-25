# include "Explosions.hpp"

Explosions::Explosions(const sf::Time & duration, bool rotate, float rotationAngle)
  : Animation(duration),
    m_explosions(),
    m_ExplosionScale(1.f, 1.f),
    m_rotate(rotate),
    m_rotationAngle(rotationAngle)
{
  # ifdef DEBUG
  Report::report_id(Report::report::extra, "Explosions class created");
  # endif // DEBUG
}

Explosions::~Explosions()
{
  # ifdef DEBUG
  Report::report_id(Report::report::extra, "Explosions class destroyed");
  # endif // DEBUG
}

void Explosions::setScale(const sf::Vector2f & scale)
{
  m_ExplosionScale = scale;
}

void Explosions::addNewOne(const sf::Vector2f & position)
{
  Animation::reset();

  sf::Sprite sprite(getFrame());
  sprite.setOrigin(Helpers::GetSpriteCenter(sprite));
  sprite.setScale(m_ExplosionScale);
  sprite.setPosition(position);

  m_explosions.push_back(std::make_tuple(sf::Time::Zero, std::move(sprite)));
}

void Explosions::update(const sf::Time & dt)
{
  m_explosions.remove_if([&](auto && it)
  {
    if((std::get<0>(it) += dt) >= getDuration())
      return true;

    Animation::reset();
    Animation::update(std::get<0>(it));

    auto && sprite{ std::get<1>(it) };
    sprite.setTexture(getFrame(), true);
    sprite.setOrigin(Helpers::getSpriteLocalCenter(sprite));
    if(m_rotate)
      sprite.rotate(m_rotationAngle * dt.asSeconds());

    return false;
  });
}

void Explosions::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  for(auto && it : m_explosions)
    target.draw(std::get<1>(it), states);
}
