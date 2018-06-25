# define HEALBAG_HPP

# ifndef ENTITY_HPP
# include <Entity.hpp>
# endif

class healBag : public sf::Sprite
{
  enum class bagState
  {
    closed, opening, opened
  };

public:
  healBag() = delete;
  healBag(Animation &);

  void setPicker(Entity *);

  bool isPickable()const;
  bool gotPicked() const;
  bagState getState() const;

  void update(const sf::Time & dt);

private:
  Entity * m_picker;
  bool m_pickable, m_picked;
  bagState m_state;
  sf::Time m_elapsed;

  Animation * m_animation;
};
