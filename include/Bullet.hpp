# define BULLET_HPP

# ifndef HELPERS_HPP
# include <Helpers.hpp>
# endif

# include <cmath>
# include <algorithm>

// @Note: This class doesn't take care of destroying instances of bullets
class Bullet : public sf::Sprite //if we want to animate it, an animator is needed, not for now
{
public:
  // Bullet states on the main view,
  // their collision state refers just to the viewport, those collisions aren't from
  // any other source
  enum class State
  {
    moving, leftCollision, rightCollision, upCollision, downCollision
  };

  // @  param 1: View that defines bullet existance
  // @  param 2: Player position, start of movement
  // @  param 3: Objective position, for now, point on space that defines
  //          Bullets direction.
  // @  param 4: Bullet's Initial velocity
  Bullet(const sf::Vector2f &, const sf::Vector2f &, float);
  ~Bullet();

  State getState() const;
  const sf::Vector2f & getVelocityVector() const;

  // @Param 1: dt to be updated with
  //  @Param 2: if a view is setted, the bullet will colide when it reaches the end of it.
  void update(const sf::Time &, sf::View * = nullptr);

private:
  State m_state;
  sf::Vector2f m_velocity;
};
