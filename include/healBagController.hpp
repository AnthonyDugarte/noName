# define HEALBAGCONTROLLER_HPP

# ifndef HEALBAG_HPP
# include <healBag.hpp>
# endif

class healBagController : public sf::Drawable
{
  using Map = sf::Sprite;

public:
  healBagController(const sf::Time &, uint);

  uint getMaxBags() const;
  void setMaxBags(const uint &);

  void setScale(const sf::Vector2f &);

  void addNewOne(Entity *, Map *);

  void update(const sf::Time &, Entity *, Map *);

  Animation m_animation;

private:
  virtual void draw(sf::RenderTarget &, sf::RenderStates) const;

  std::list<healBag> m_currentBags;

  sf::Vector2f m_scale;

  uint m_maxBags;
  sf::Time m_elapsed, m_spawnTime;
};
