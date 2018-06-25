# include <Bullet.hpp>

Bullet::Bullet(const sf::Vector2f & playerPos, const sf::Vector2f & mousePos, float velocity)
  : m_state(State::moving)
{
  # ifdef DEBUG
  Report::report_id(Report::report::bullet_created);
  # endif // DEBUG

  sf::Vector2f m(mousePos.x - playerPos.x, mousePos.y - playerPos.y);

  double angle{ std::atan2(m.y, m.x) };

  m_velocity.x = std::cos(angle) * velocity;
  m_velocity.y = std::sin(angle) * velocity;
}

Bullet::~Bullet()
{
  # ifdef DEBUG
  Report::report_id(Report::report::bullet_killed);
  # endif // DEBUG
}

Bullet::State Bullet::getState() const
{
  return m_state;
}

const sf::Vector2f & Bullet::getVelocityVector() const
{
  return m_velocity;
}

void Bullet::update(const sf::Time & dt, sf::View * view)
{
  move(m_velocity.x * dt.asSeconds(),
      m_velocity.y * dt.asSeconds());

  if (view == nullptr)
    return;

  auto && bulletBounds{ getGlobalBounds() };
  sf::FloatRect limit(view->getCenter() - view->getSize() * .5f, view->getSize());

  if(not bulletBounds.intersects(view->getViewport()))
  {
    if(bulletBounds.left <= limit.left)
      m_state = State::leftCollision;
    else if(bulletBounds.top <= limit.top)
      m_state = State::upCollision;
    else if(bulletBounds.left + bulletBounds.width >= limit.left + limit.width)
      m_state = State::rightCollision;
    else if(bulletBounds.top + bulletBounds.height >= limit.top + limit.height)
      m_state = State::downCollision;
  }
  else  m_state = State::moving;
}
