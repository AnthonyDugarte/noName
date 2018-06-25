# include <Player.hpp>

Player::Player(const std::string & folder)
  : Entity(folder, 0.f),
    m_bullets(nullptr)
{
  # ifdef DEBUG
  Report::report_id(Report::report::player_created);
  # endif // DEBUG
}

Player::~Player()
{
  # ifdef DEBUG
  Report::report_id(Report::report::player_killed);
  # endif // DEBUG

  m_bullets = nullptr;
}

void Player::setBullets(Bullets & bullets)
{
  m_bullets = &bullets;
}

void Player::shoot(const sf::Vector2f & target)
{
  if(m_bullets != nullptr and not dead())
    m_bullets->createBullet(getPosition() , target);
}

void Player::spin()
{
  if(dead())
    return;

  m_spinBeg = true;

  if(not attackable())
  {
    sf::Color fade { getColor() };
    fade.a = 255.f;
    setColor(fade);
  }

  inmortal();
  setState(EntityState::spinning, true);
}

bool Player::initSpin()
{
  if(m_spinBeg)
  {
    m_spinBeg = false;
    return (m_spinning = true);
  }
  return false;
}


void Player::update(const sf::Time& dt, Map * map)
{
  if(getState() == EntityState::dead)
  {
    AnimatedSprite::update(dt);
    return;
  }

  if(dead())
  {
    setState(EntityState::dead, true);
    return;
  }

  if(initSpin())
  {
    m_deadLock  = sf::seconds(2.6f);
  }
  else  if(recentlyAttacked())
    m_deadLock  = sf::seconds(5.3f);


  if(m_spinning)
  {
    m_deadLock -= dt;

    if(m_deadLock <= sf::seconds(2.f))
    {
      m_spinning = false;
      restoreAttackable();
      setState(EntityState::standing, true);
    }
  }

  if(not (attackable() or m_spinning))
  {
    m_deadLock -= dt;

    sf::Color fade { getColor() };

    if(m_deadLock <= sf::seconds(2.f))
    {
      m_deadLock = sf::Time::Zero;
      fade.a = 255.f;
      restoreAttackable();
    }
    else  fade.a = static_cast<int>(m_deadLock.asSeconds() / 1.f /*fade in - fade out time*/ * 255) % 255;

    setColor(fade);
  }

  handleInput();

  if(wsad.W)
  {
    moveUp(dt);
    if(map != nullptr and Helpers::hasCollision(*this, *map, Globals::unitbody))
      moveUp(-dt);
  }
  else if(wsad.S)
  {
    moveDown(dt);
    if(map != nullptr and Helpers::hasCollision(*this, *map, Globals::unitbody))
      moveDown(-dt);
  }

  if(wsad.A)
  {
    moveLeft(dt);
    if(map != nullptr and Helpers::hasCollision(*this, *map, Globals::unitbody))
      moveLeft(-dt);
  }
  else if(wsad.D)
  {
    moveRight(dt);
    if(map != nullptr and Helpers::hasCollision(*this, *map, Globals::unitbody))
      moveRight(-dt);
  }

  if(not (wsad.W or wsad.S or wsad.A or wsad.D or m_spinning))
    setState(EntityState::standing, true);

  AnimatedSprite::update(dt);
}

void Player::handleInput()
{
  wsad.W = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
  wsad.S = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
  wsad.A = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
  wsad.D = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

  if(wsad.W and wsad.S)
    wsad.W = wsad.S = false;

  if(wsad.A and wsad.D)
    wsad.A = wsad.D = false;
}
