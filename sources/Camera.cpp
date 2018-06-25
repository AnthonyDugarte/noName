# include <Camera.hpp>

Camera::Camera()
: View()
{
  // empty
}

Camera::Camera(const sf::FloatRect & rectangle)
: View(rectangle)
{
  // empty
}

Camera::Camera(const sf::Vector2f & center, const sf::Vector2f & size)
: View(center, size)
{
  // empty
}

void Camera::fitWith(sf::Sprite * target, Map * map)
{
  if(target == nullptr or map == nullptr)
    return; // for now, I don't what would this mean.

  auto && targetPos{ target->getPosition() };
  auto && mapSize{ map->getGlobalBounds() };
  auto && cameraSize{ getSize() };

  auto newCenter{ targetPos };

  if(targetPos.x < cameraSize.x * .5f)
    newCenter.x = cameraSize.x * .5f;
  else if(targetPos.x > mapSize.width - cameraSize.x * .5f)
    newCenter.x = mapSize.width - cameraSize.x * .5f;

    if(targetPos.y < cameraSize.y * .5f)
      newCenter.y = cameraSize.y * .5f;
  else if(targetPos.y > mapSize.height - cameraSize.y * .5f)
    newCenter.y = mapSize.height - cameraSize.y * .5f;

  setCenter(newCenter);
}
