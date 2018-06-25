# define MENU_HPP

# ifndef SCENE_HPP
# include <Scene.hpp>
# endif

# ifndef ASSET_MANAGER_HPP
# include <AssetManager.hpp>
# endif

/** Main menu of the game, it allows the player to start playing
	or closing the game
*/
class Menu : public Scene
{
public:
	Menu(sf::RenderWindow &);
	~Menu();

	Scene::Id execute();

private:
	enum class Option { Play, Quit };

	Option m_selected;
	sf::Sprite m_sprite_play, m_sprite_quit;
};
