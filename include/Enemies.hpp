# define ENEMIES_HPP

# ifndef ENEMY_HPP
# include <Enemy.hpp>
# endif

// This class is mean to define the set of enemies in common that another
//    instance may have, this helps to avoid collision between equals
class Enemies : public sf::Drawable
{
  // @Important: this was settet temporaly until Map class is created, I believe that one is
  // the one that is going to take care of collisions but, for now collisions are inside this class.
  using Map = sf::Sprite;

public:
  // Millestone: Set a global animator for set of enemies, in other words
  // create an animator here and handle their updates with reset method and taking care of
  // timings
  //  @Param 1: enemies animation folder
  // @Param 1: time between Spawn of enemies.
  // @Param 2: enemies velocity
  Enemies(const std::string &, const sf::Time &);
  ~Enemies();

  void setEnemy(Entity *); // you got it?

  //if enemies spwan inside or outside the viewport, if outside, map must be specified
  void spawnInside();
  void spawnOutside();

  // Change spawn time of enemies.
  void setSpawnTime(const sf::Time &);

  // Spawns are handled here,
  void update(const sf::Time &, sf::View * = nullptr, Map * = nullptr);

  void addNewOne(sf::View *, Map *);

  Enemy enemyTemplate;
private:
  // Method herited from abstract class sf::Drawable, it defines that this class
  // can be passed to RenderTarget's draw method.
  virtual void draw(sf::RenderTarget &, sf::RenderStates) const;

  std::list<Enemy *> m_enemies;

  bool m_outside;

  sf::Time m_dtSpawn;
  sf::Time m_elapsed;

  Entity * m_player;

  friend class Bullets;
};
