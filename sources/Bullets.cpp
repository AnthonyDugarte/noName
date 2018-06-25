# include <Bullets.hpp>

Bullets::Bullets(const std::string & textureName)
  : m_bullets(),
    m_bulletTexture(AssetManager::getTexture(textureName)),
    m_bulletScale(1.f, 1.f),
    m_velocity(0.f),
    m_enemies(nullptr), m_explosions(nullptr)
{
  # ifdef DEBUG
  Report::report_id(Report::report::extra, "Bullet's class created");
  # endif // DEBUG
}

Bullets::~Bullets()
{
  # ifdef DEBUG
  Report::report_id(Report::report::extra, "Bullet's class destroyed");
  # endif // DEBUG

  m_enemies = nullptr;
  m_explosions = nullptr;
}

void Bullets::createBullet(const sf::Vector2f & playerPos, const sf::Vector2f & mousePos)
{
  m_bullets.push_back(Bullet(playerPos, mousePos, m_velocity));

  auto && bullet { m_bullets.back() };
  bullet.setTexture(m_bulletTexture, true);
  bullet.setOrigin(Helpers::getSpriteLocalCenter(bullet));
  bullet.setScale(m_bulletScale);
  bullet.setPosition(playerPos);
}

void Bullets::setScale(const sf::Vector2f & scale)
{
  m_bulletScale = scale;
}

void Bullets::setVelocity(float velocity)
{
  m_velocity = velocity * m_bulletScale.x;
}

sf::Texture & Bullets::getTexture()
{
  return m_bulletTexture;
}

void Bullets::setEnemies(Enemies & enemies)
{
  m_enemies = &enemies;
}

void Bullets::setExplosions(Explosions & explosions)
{
  m_explosions = &explosions;
}

void Bullets::update(const sf::Time & dt, sf::View * view, Map * map)
{
  m_bullets.remove_if([&](auto && bullet)
  {
    bullet.update(dt, &*view);

    sf::Vector2f position{ bullet.getPosition()};
    bool bulletHit = false;

    if(m_enemies != nullptr)
      m_enemies->m_enemies.remove_if([&](auto && enemy)
      {
        if(Helpers::hasCollision(bullet, *enemy))
        {
          enemy->attacked();

          if (m_explosions != nullptr)
            m_explosions->addNewOne(position);

          bulletHit = true;

          if(enemy->dead())
          {
            delete enemy;
            return true;
          }
          return false;
        }
        return false;
      });

    if(bulletHit)
      return true;

    if(map != nullptr and Helpers::hasCollision(bullet, *map, Globals::mapObjects))
    {
      if (m_explosions != nullptr)
        m_explosions->addNewOne(position);
      return true;
    }

    auto && state{ bullet.getState() };

    if(state != Bullet::State::moving)
    {
      if (m_explosions != nullptr)
      {
        if(state == Bullet::State::leftCollision)
          position.x += bullet.getGlobalBounds().width;
        else if(state == Bullet::State::rightCollision)
          position.x -= bullet.getGlobalBounds().width;
        else if(state == Bullet::State::upCollision)
          position.y += bullet.getGlobalBounds().height;
        else if(state == Bullet::State::downCollision)
          position.y -= bullet.getGlobalBounds().height;

        m_explosions->addNewOne(position);
      }
      return true;
    }

    return false;
  });
}

void Bullets::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  for(auto && bullet : m_bullets)
      target.draw(bullet, states);
}
