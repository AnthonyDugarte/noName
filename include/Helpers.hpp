# define HELPERS_HPP

# ifndef ASSET_MANAGER_HPP
# include <AssetManager.hpp>
# endif

# ifndef GLOBALS_HPP
# include <Globals.hpp>
# endif

# include <random>
# include <cassert>
# include <vector>

namespace Helpers
{
  // This function takes a sprite and get's it's center in GLOBAL Coordinates
  sf::Vector2f GetSpriteCenter(const sf::Sprite &);

  // This function takes a sprite and get's it's center in LOCAL Coordinates
  sf::Vector2f getSpriteLocalCenter(const sf::Sprite &);

  sf::Vector2f getViewOrigin(sf::View &);

  // as it's name sais, it gets the pixel x ,y of the texture's mask, supoing it belongs to it.
  sf::Uint8 getPixel(const sf::Uint8 * mask, const sf::Texture * texture, size_t x, size_t y);

  /*@Description: this function uses the alpha value of the pixels that are overlapping to
   *      get an amazingly precise collision test of their textures
   *
   *  @note: The Uint8 parameter is used to set a sort of limit that defines the collision
   *       condition of those textures, it can be used to make different types of collisions
   *         creating a kind of level masks.
   *
   *  @note 2: for a more detail Description of the algorithm, the original files were placed at:
   *                                NanoSurgeon/AddOns/SFML_CollisionSystem
   */
  bool hasCollision(const sf::Sprite &, const sf::Sprite &, sf::Uint8 = 0);

  using Map = sf::Sprite;

  int random(int l, int r);
  float random(float l, float r);

  // it returns a position,
  // if boolean is true, it returns a position ouside the viewport
  sf::Vector2f randomPos(sf::View & m_view, bool = false, Map * = nullptr);
  sf::Vector2f randomMapPos(Map * map);

  sf::VideoMode getBestVideoMode();

  sf::Vector2f getProportionalScale(const sf::View &, const sf::Sprite &, float porcentage);

  template <typename T>
  T getVector2Min(sf::Vector2<T> vec)
  {
      return vec.x < vec.y ? vec.x : vec.y;
  }
}
