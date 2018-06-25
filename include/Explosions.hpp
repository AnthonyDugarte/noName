# define EXPLOSIONS_HPP

# ifndef ANIMATION_HPP
# include <Animation.hpp>
# endif

# include <list>
# include <tuple>

//it's aimed to be an animator that carries temporal secuences of explotions, maybe it could
//be implemented with the animator, lets see
class Explosions : public Animation, public sf::Drawable
{
  using explosion_info = std::tuple<sf::Time, sf::Sprite>;

public:
  Explosions(const sf::Time &, bool = false, float = 480.f);
~Explosions();

  void setScale(const sf::Vector2f &);

  void addNewOne(const sf::Vector2f &);
  void update(const sf::Time &);

private:
  virtual void draw(sf::RenderTarget &, sf::RenderStates) const;

  std::list<explosion_info> m_explosions;

  sf::Vector2f m_ExplosionScale;
  bool m_rotate;
  float m_rotationAngle;
};
