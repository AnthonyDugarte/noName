# include <Entity.hpp>

Entity::Entity(const std::string & folder, const float & velocity)
: AnimatedSprite(folder),
  Attributes(3u),
  m_velocity(velocity)
{
  # ifdef DEBUG
  Report::report_id(Report::report::entity_created);
  # endif // DEBUG
}

Entity::Entity(const Entity & copy)
: AnimatedSprite(copy),
  m_velocity(copy.m_velocity)
{
  # ifdef DEBUG
  Report::report_id(Report::report::entity_created, "copy constructor");
  # endif // DEBUG
}

Entity::~Entity()
{
  # ifdef DEBUG
  Report::report_id(Report::report::entity_killed);
  # endif // DEBUG
}


void Entity::setVelocity(const float & velocity)
{
  m_velocity = velocity * getScale().x; // we assume scales are equal.
}

void Entity::handleInput()
{
  if(wsad.W and wsad.S)
    wsad.W = wsad.S = false;

  if(wsad.A and wsad.D)
    wsad.A = wsad.D = false;
}

void Entity::moveUp(const sf::Time & dt)
{
  move(0, -m_velocity * dt.asSeconds());
  if(getState() != EntityState::spinning)
    setState(EntityState::moveUp, true);
}
void Entity::moveDown(const sf::Time & dt)
{
  move(0, m_velocity * dt.asSeconds());
  if(getState() != EntityState::spinning)
    setState(EntityState::moveDown, true);
}

void Entity::moveLeft(const sf::Time & dt)
{
  move(-m_velocity * dt.asSeconds(), 0);
  if(getState() != EntityState::spinning)
  {
    if(not (wsad.W or wsad.S))
    setState(EntityState::moveLeft, true);
    else setState(EntityState::moveLeft, false);
  }
}

void Entity::moveRight(const sf::Time & dt)
{
  move(m_velocity * dt.asSeconds(), 0);
  if(getState() != EntityState::spinning)
  {
    if(not (wsad.W or wsad.S))
      setState(EntityState::moveRight, true);
    else setState(EntityState::moveRight, false);
  }
}
