# include <healBagController.hpp>

healBagController::healBagController(const sf::Time & spawnTime, uint maxBags)
: m_spawnTime(spawnTime),
  m_maxBags(maxBags),
  m_scale(1.f, 1.f),
  m_animation(sf::seconds(1.f), false) // default animation going to last a second and won't loop
{
  // empty
}

uint healBagController::getMaxBags() const
{
  return m_maxBags;
}

void healBagController::setMaxBags(const uint & bags)
{
  m_maxBags = bags;
}

void healBagController::setScale(const sf::Vector2f & scale)
{
  m_scale = scale;
}


void healBagController::addNewOne(Entity * picker, Map * map)
{
  if(m_currentBags.size() >= m_maxBags)
    return;

  healBag bag(m_animation);
  bag.setScale(m_scale);
  bag.update(sf::Time::Zero);
  bag.setPicker(picker);

  do
  {
    bag.setPosition(Helpers::randomMapPos(&*map));
  }while(Helpers::hasCollision(bag, *map, Globals::mapGround + 1));

  m_currentBags.push_back(std::move(bag));
}

void healBagController::update(const sf::Time & dt, Entity * picker, Map * map)
{
  m_elapsed += dt;

  if(m_elapsed >=m_spawnTime)
  {
    addNewOne(picker, map);
    m_elapsed = sf::Time::Zero;
  }

  if(m_currentBags.empty())
    return;

  m_currentBags.remove_if([&](auto && bag)
  {
    bag.update(dt);

    if(bag.gotPicked())
      return true;
    return false;
  });
}

void healBagController::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  for(auto && bag : m_currentBags)
    target.draw(bag, states);
}
