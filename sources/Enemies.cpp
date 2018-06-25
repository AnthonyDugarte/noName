# include <Enemies.hpp>

sf::Vector2f randomPos(sf::View & m_view);

Enemies::Enemies(const std::string & folder, const sf::Time & spawnTime)
: m_enemies(),
  m_outside(false),
  m_dtSpawn(spawnTime),
  enemyTemplate(folder),
  m_player(nullptr)
{
  # ifdef DEBUG
  Report::report_id(Report::report::extra, "Enemies class created");
  # endif // DEBUG
}

Enemies::~Enemies()
{
  # ifdef DEBUG
  Report::report_id(Report::report::extra, "Enemies class destroyed");
  # endif // DEBUG

  while(not m_enemies.empty())
  {
    delete m_enemies.back();
    m_enemies.pop_back();
  }
}

void Enemies::setEnemy(Entity * player)
{
  m_player = &*player;
}

void Enemies::setSpawnTime(const sf::Time & dtSpawn)
{
  m_dtSpawn = dtSpawn;
}

void Enemies::spawnInside()
{
  m_outside = false;
}

void Enemies::spawnOutside()
{
  m_outside = true;
}

void Enemies::update(const sf::Time & dt, sf::View * view, Map * map)
{
  m_elapsed += dt;

  if(m_elapsed >= m_dtSpawn)
    addNewOne(&*view, &*map);

  for(auto && enemy : m_enemies)
    enemy->update(dt, m_player , &*map);
}

void Enemies::addNewOne(sf::View * view, Map * map)
{
  m_elapsed = sf::Time::Zero;

  Enemy * enemy { new Enemy(enemyTemplate) };
  enemy->update(m_elapsed);

  if(view != nullptr)
  {
    do
    {
      enemy->setPosition(Helpers::randomPos(*view, m_outside, &*map));
    }while(map != nullptr and Helpers::hasCollision(*enemy, *map, Globals::mapGround));
  }
  else enemy->setPosition(0, 0);

  m_enemies.push_back(std::move(enemy));
}

void Enemies::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  for(auto && enemy : m_enemies)
    target.draw(*enemy, states);
}
