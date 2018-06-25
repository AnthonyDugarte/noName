# include <Helpers.hpp>

namespace Helpers
{
  sf::Vector2f GetSpriteCenter(const sf::Sprite & sprite)
  {
    sf::FloatRect bounds = sprite.getGlobalBounds();

    return sf::Vector2f (bounds.left+bounds.width * .5f, bounds.top + bounds.height * .5f);
  }

  sf::Vector2f getSpriteLocalCenter(const sf::Sprite & sprite)
  {
    return sf::Vector2f(static_cast<sf::Vector2f>(sprite.getTexture()->getSize()) * .5f);
  }

  sf::Vector2f getViewOrigin(sf::View & view)
  {
    return sf::Vector2f(view.getCenter().x - view.getSize().x * .5f,
             view.getCenter().y - view.getSize().y * .5f);
  }

  sf::Uint8 getPixel (const sf::Uint8 * mask, const sf::Texture * texture, size_t x, size_t y)
  {
    if (x > texture->getSize().x or y > texture->getSize().y)
      return 0;

    return mask[x + y * texture->getSize().x];
  }

  bool hasCollision(const sf::Sprite & Ob1, const sf::Sprite & Ob2, sf::Uint8 alphaLimit)
  {
    sf::FloatRect IntersectionRect;

    if(Ob1.getGlobalBounds().intersects(Ob2.getGlobalBounds(), IntersectionRect))
    {
      auto && Ob1subRect{ Ob1.getTextureRect() };
      auto && Ob2subRect{ Ob2.getTextureRect() };

      auto && Ob1mask{ AssetManager::getBitMask(Ob1.getTexture()) };
      auto && Ob2mask{ AssetManager::getBitMask(Ob2.getTexture()) };

      for(size_t x = IntersectionRect.left; x < IntersectionRect.left + IntersectionRect.width; ++x)
        for(size_t y = IntersectionRect.top; y < IntersectionRect.top + IntersectionRect.height; ++y)
        {
          sf::Vector2f Ob1v{ Ob1.getInverseTransform().transformPoint(x, y) };
          sf::Vector2f Ob2v{ Ob2.getInverseTransform().transformPoint(x, y) };

          if(Ob1v.x > 0 and Ob1v.y > 0 and
              Ob2v.x > 0 and Ob2v.y > 0 and
              Ob1v.x < Ob1subRect.width and Ob1v.y < Ob1subRect.height and
              Ob2v.x < Ob2subRect.width and Ob2v.y < Ob2subRect.height)
          {
            if(getPixel(&*Ob1mask, &*Ob1.getTexture(), Ob1v.x + Ob1subRect.left, Ob1v.y + Ob1subRect.top) > alphaLimit and
                getPixel(&*Ob2mask, &*Ob2.getTexture(), Ob2v.x + Ob2subRect.left, Ob2v.y + Ob2subRect.top) > alphaLimit)
      return true;
          }
        }
    }

    return false;
  }

  std::random_device seed_device;
  std::default_random_engine engine(seed_device());

  int random(int l, int r)
  {
    assert(l < r);
    std::uniform_int_distribution<uint> distribution(l, r);

    return distribution(engine);
  }

  float random(float l, float r)
  {
    assert(l < r);
    std::uniform_real_distribution<float> distribution(l, r);

    return distribution(engine);
  }

  sf::Vector2f randomPos(sf::View & view, bool outside, Map * map)
  {
   sf::Vector2f start(getViewOrigin(view));

   std::uniform_int_distribution<int> Xdistribution(start.x,
     start.x + view.getSize().x);
   std::uniform_int_distribution<int> Ydistribution(start.y,
     start.y + view.getSize().y);

    if(not outside)
      return sf::Vector2f( static_cast<float>(Xdistribution(engine)),
                                            static_cast<float>(Ydistribution(engine)));

    if(map == nullptr)
      throw std::logic_error("no boundries where specified");

    auto && boundries{ map->getGlobalBounds() };

    std::uniform_int_distribution<int> Xdistribution1(0, boundries.width);
    std::uniform_int_distribution<int> Ydistribution1(0, boundries.height);

    sf::Vector2f position;

    do
    {
      position.x = static_cast<float>(Xdistribution1(engine));
    }while(position.x > start.x and position.x < start.x + view.getSize().x);

    do
    {
      position.y = static_cast<float>(Ydistribution1(engine));
    }while(position.y > start.y and position.y < start.y + view.getSize().y);

    return position;
  }

  sf::Vector2f randomMapPos(Map * map)
  {
    if(map == nullptr)
      return sf::Vector2f(0, 0);

    auto && boundries{ map->getGlobalBounds() };

    std::uniform_int_distribution<int> Xdistribution1(0, boundries.width);
    std::uniform_int_distribution<int> Ydistribution1(0, boundries.height);

    return sf::Vector2f(Xdistribution1(engine), Ydistribution1(engine));
  }

  sf::VideoMode getBestVideoMode()
  {
    for(auto && it : sf::VideoMode::getFullscreenModes())
      if(it.width / 16 == it.height / 9)
        return it;

    return *sf::VideoMode::getFullscreenModes().begin(); // best one
    throw std::logic_error("couldn't set a nice resolution");
  }

  sf::Vector2f getProportionalScale(const sf::View & camera, const sf::Sprite & sprite, float porcentage)
  {
    return sf::Vector2f((camera.getSize().x * porcentage) /  sprite.getTextureRect().width /*x*/,
                          (camera.getSize().y * porcentage) /  sprite.getTextureRect().height /*y*/ );
  }
} // Helpers
