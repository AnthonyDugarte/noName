# include <healBag.hpp>

healBag::healBag(Animation & animation)
: m_animation(&animation),
  m_picker(nullptr),
  m_pickable(false),
  m_picked(false),
  m_state(bagState::closed),
  m_elapsed()
{
  // empty
}

void healBag::setPicker(Entity * picker)
{
  m_picker = &*picker;
}

bool healBag::isPickable()const
{
  return m_pickable;
}

bool healBag::gotPicked() const
{
  return m_picked;
}

healBag::bagState healBag::getState() const
{
  return m_state;
}

void healBag::update(const sf::Time & dt)
{
  if(m_picker != nullptr and Helpers::hasCollision(*m_picker, *this))
  {
    switch(m_state)
    {
      case bagState::closed:
        m_state = bagState::opening;
      break;

      case bagState::opening:
      break;

      case bagState::opened:
        if(gotPicked())
          break;

        m_picker->healted();
        m_picked = true;

        # ifdef RELEASE
        AssetManager::getMusic("Life.wav").play();
        # endif
      break;
    }
  }

  if(m_state != bagState::closed)
    m_elapsed += dt;

  if(m_animation != nullptr)
  {
    m_animation->reset();
    m_animation->update(m_elapsed);

    setTexture(m_animation->getFrame(), true);
    setOrigin(Helpers::getSpriteLocalCenter(*this));

    if(m_elapsed >= m_animation->getDuration())
      m_state = bagState::opened;
  }
}
