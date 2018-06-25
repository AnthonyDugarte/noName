# define PLAYER_HPP

# ifndef BULLETS_HPP
# include <Bullets.hpp>
# endif

class Player : public Entity
{
  using Map = sf::Sprite;

public:
  Player(const std::string &);
  ~Player();

  void setBullets(Bullets &);
  void shoot(const sf::Vector2f &);
  void spin();

  void update(const sf::Time &,  Map * = nullptr);

private:
  Bullets * m_bullets;
  sf::Time m_deadLock;

  bool initSpin();

  bool m_spinBeg;
  bool m_spinning;

  void handleInput() override;
};
