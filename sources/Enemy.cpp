# include <Enemy.hpp>

Enemy::Enemy(const std::string & folder)
  : Entity(folder),
    m_attacking(false),
    m_rage(false)
{
  # ifdef DEBUG
  Report::report_id(Report::report::enemy_created);
  # endif // DEBUG
}

Enemy::Enemy(const Enemy & copy)
  : Entity(copy),
    m_attackRange(copy.m_attackRange),
    m_attacking(copy.m_attacking),
    m_velocityVec(copy.m_velocityVec)
{
  setScale(copy.getScale());

  # ifdef DEBUG
  Report::report_id(Report::report::enemy_created, "copy constructor");
  # endif // DEBUG
}

Enemy::~Enemy()
{
  # ifdef DEBUG
  Report::report_id(Report::report::enemy_killed);
  # endif // DEBUG
}

void Enemy::setVelocity(const float & velocity)
{
  m_velocity = velocity * getScale().x;

  m_velocityVec.x = m_velocityVec.y = m_velocity;
}

void Enemy::setAttackRange(float range)
{
  m_attackRange = range / getScale().x;
}

bool Enemy::begRage()
{
  if(recentlyAttacked())
    return (m_rage = true);

  return false;
}

void Enemy::endRage()
{
  m_rage = false;
}

bool Enemy::inRage()
{
  return m_rage;
}

void Enemy::update(const sf::Time & dt,  Entity * player, Map * map)
{
  if(player != nullptr)
  {
    sf::Vector2f m(player->getPosition().x - getPosition().x, player->getPosition().y - getPosition().y);

    float Distance { m.y * m.y + m.x * m.x }; // h^2 = co^2 + ca^2

    if(begRage())
      m_deadLock = sf::seconds(5.3f);

    if((inRage() or Distance <= m_attackRange * m_attackRange) // hd ^ 2 <= h ^ 2
      and (player->attackable() or player->getState() == EntityState::spinning))
    {
      m_deadLock -= dt;

      if(m_deadLock <= sf::seconds(2.f))
        endRage();

      if(player->attackable())
      {
        if(Helpers::hasCollision(*this, *player, Globals::unitbody - 1))
        {
          player->attacked();
          m_velocityVec.x = m_velocityVec.y = m_velocity;
          m_attacking  = false;
        }
        else
        {
          double angle{ std::atan2(m.y, m.x) };
          m_velocityVec.x = std::cos(angle) * m_velocity;
          m_velocityVec.y = std::sin(angle) * m_velocity;
          m_attacking = true;
        }
      }
      else if(player->getState()  == EntityState::spinning and Helpers::hasCollision(*this, *player, Globals::unitbody - 1))
          attacked();
      else
      {
        m_velocityVec.x = m_velocityVec.y = m_velocity;
        m_attacking  = false;
      }
    }
    else
    {
      m_velocityVec.x = m_velocityVec.y = m_velocity;
      m_attacking  = false;
    }
  }

  if(m_attacking)
    attack(dt);
  else move_to(dt, &*map);

  AnimatedSprite::update(dt);
}

void Enemy::attack(const sf::Time & dt)
{
  move(m_velocityVec.x * dt.asSeconds(), m_velocityVec.y * dt.asSeconds());
  setState(EntityState::attacking, true);
}

void Enemy::move_to(const sf::Time & dt, Map * map)
{
  setState(EntityState::standing, true);
  m_elapsed += dt;

  if (m_elapsed >= sf::seconds(3.f))
  {
    randomDir();
    m_elapsed = sf::seconds(0.f);
  }

  handleInput();

  if(wsad.W)
  {
    moveUp(dt);
    if(map != nullptr and Helpers::hasCollision(*this, *map, Globals::unitbody))
    {
      moveUp(-dt);
      wsad.W = false;
      wsad.S = true;
    }
  }
  else if(wsad.S)
  {
    moveDown(dt);
    if(map != nullptr and Helpers::hasCollision(*this, *map, Globals::unitbody))
    {
      moveDown(-dt);
      wsad.W = true;
      wsad.S = false;
    }
  }

  if(wsad.A)
  {
    moveLeft(dt);
    if(map != nullptr and Helpers::hasCollision(*this, *map, Globals::unitbody))
    {
      moveLeft(-dt);
      wsad.A = false;
      wsad.D = true;
    }
  }
  else if(wsad.D)
  {
    moveRight(dt);
    if(map != nullptr and Helpers::hasCollision(*this, *map, Globals::unitbody))
    {
      moveRight(-dt);
      wsad.A = true;
      wsad.D = false;
    }
  }

  if(not (wsad.W or wsad.S or wsad.A or wsad.D))
    setState(EntityState::standing, true);
}

void Enemy::randomDir()
{
  uint directions{ static_cast<uint>(Helpers::random(0, 15)) };

  if(directions & (1 << 0))
    wsad.W = true;
  else wsad.W = false;

  if(directions & (1 << 1))
    wsad.S = true;
  else wsad.S = false;

  if(directions & (1 << 2))
    wsad.A = true;
  else wsad.A = false;

  if(directions & (1 << 3))
    wsad.D = true;
  else wsad.D = false;
}
