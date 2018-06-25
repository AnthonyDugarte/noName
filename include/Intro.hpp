# define INTRO_HPP

# ifndef SCENE_HPP
# include <Scene.hpp>
# endif

# ifndef ASSET_MANAGER_HPP
# include <AssetManager.hpp>
# endif

class Intro : public Scene
{
public:
  Intro(sf::RenderWindow &);
  ~Intro();

  Scene::Id execute();
};
