# define PAUSED_HPP

# ifndef SCENE_HPP
# include <Scene.hpp>
# endif

# ifndef ASSET_MANAGER_HPP
# include <AssetManager.hpp>
# endif

class Paused : public Scene
{
public:
	Paused(sf::RenderWindow &);
	~Paused();

	Scene::Id execute();

private:
	enum class Option { Continue, Quit };

	Option m_selected = Option::Continue;
	sf::Sprite m_sprite_continue, m_sprite_quit;
};
