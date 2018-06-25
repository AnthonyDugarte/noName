# define CAMERA_HPP

# ifndef HELPERS_HPP
# include <Helpers.hpp>
# endif

class Camera : public sf::View
{
  using Map = sf::Sprite;

public:
  Camera();
  Camera(const sf::FloatRect &);
  Camera(const sf::Vector2f &, const sf::Vector2f &);

  // what this does is to put the viewport in the middle of the sprite
  // and if the camera is going to the map boundries
  // it fits the viewport so that it doesn't pass it away.

  // if no map or target is setted, it just do nothing
  void fitWith(sf::Sprite * target, Map * map); // just for this
};
