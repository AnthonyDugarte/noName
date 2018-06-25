# define BULLETS_HPP

# ifndef BULLET_HPP
# include <Bullet.hpp>
# endif

# ifndef ENEMIES_HPP
# include <Enemies.hpp>
# endif

# ifndef EXPLOSIONS_HPP
# include <Explosions.hpp>
# endif

// Bullet's destructions are handled here.
class Bullets : public sf::Drawable
{
  // @Important: this was settet temporaly until Map class is created, I believe that one is
  // the one that is going to take care of collisions but, for now collisions are inside this class.
  using Map = sf::Sprite;
public:
  // @ Param 1: View that is refered to bullets constructed.
  // @ Param 2: Texture name of the bullet
  // @ Param 3: Velocity that bullets are going to have
  Bullets(const std::string &);

  // @Important: Destructor had to be implemented because explicit one was
  //    Killing pointers.
  // @Note: Those pointers aren't created on construction nor mhetods avaiable
  //    on this class, I think, that's why they should not be destroyed here.
  ~Bullets();

  // @ Param1: Origin
  // @ Param2: Target
  void createBullet(const sf::Vector2f &, const sf::Vector2f &);

  //  this scale is the one all bullets created are going to have
  void setScale(const sf::Vector2f &);
  void setVelocity(float);

  sf::Texture & getTexture();
  // Enemies that are going to interact with bullets, if they collide, they shall
  // be destroyed, that's done here, for now.
  void setEnemies(Enemies &);

  // Explosions animator that is going to have control of animating the
  //  bullets collision destruction cinematic
  void setExplosions(Explosions &);

  // @ Important: Collisions are handled here.
  void update(const sf::Time &, sf::View * = nullptr, Map * = nullptr);

private:
  // Method herited from abstract class sf::Drawable, it defines that this class
  // can be passed to RenderTarget's draw method.
  virtual void draw(sf::RenderTarget &, sf::RenderStates) const;

  std::list<Bullet> m_bullets;

  sf::Texture & m_bulletTexture;
  sf::Vector2f m_bulletScale;

  float m_velocity;

  Enemies * m_enemies;
  Explosions * m_explosions;
};
