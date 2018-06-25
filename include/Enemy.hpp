# define ENEMY_HPP

# ifndef EXPLOSIONS_HPP
# include <Entity.hpp>
# endif

# ifndef GLOBALS_HPP
# include <Globals.hpp>
# endif

# include <cmath>

class Enemy : public Entity
{
 using Map = sf::Sprite;

public:
Enemy(const std::string &);
Enemy(const Enemy &);
 ~Enemy();

 void setVelocity(const float &) override;

 void setAttackRange(float);
 bool begRage();
 void endRage();
 bool inRage();


 // @Param 1: Time to update with
 // @Param 2: if player is setted, it will take care of the attackRange and if the player
 //     is close enough, it will haunte him untill he goes away of the attackRange
 // @Param3: if map is setted, enemy would colide with it.
 //     this collision is just handled when no player
 void update(const sf::Time &, Entity * player = nullptr, Map * map = nullptr);
private:
  void attack(const sf::Time &);
  void move_to(const sf::Time &, Map *);

 void randomDir();

 float m_attackRange;
 bool m_attacking;
 bool m_rage;

 sf::Time m_deadLock;
 sf::Vector2f m_velocityVec;

sf::Time m_elapsed;
};
