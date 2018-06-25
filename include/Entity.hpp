# define ENTITY_HPP

# ifndef ANIMATEDSPRITE_HPP
# include <AnimatedSprite.hpp>
# endif

# ifndef ATTRIBUTES_HPP
# include <Attributes.hpp>
# endif

enum class EntityState
{
  standing, moveLeft, moveRight, moveUp, moveDown, chill, attacking, dead, inmortal, spinning
};

class Entity : public AnimatedSprite<EntityState>, public Attributes
{
public:
  Entity(const std::string & folder, const float & = 500.f);
  Entity(const Entity &);
  ~Entity();

  virtual void setVelocity(const float &);

  virtual void handleInput();

  virtual void moveUp(const sf::Time &);
  virtual void moveDown(const sf::Time &);
  virtual void moveLeft(const sf::Time &);
  virtual void moveRight(const sf::Time &);

protected:
  struct{ bool W = false, S = false, A = false, D = false; } wsad;

  float m_velocity;
};
