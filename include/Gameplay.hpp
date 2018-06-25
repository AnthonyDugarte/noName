# define GAMEPLAY_HPP

# ifndef PAUSED_HPP
# include <Paused.hpp>
# endif

# ifndef CURSOR_HPP
# include <Cursor.hpp>
# endif

# ifndef BULLETS_HPP
# include <Bullets.hpp>
# endif

# ifndef CAMERA_HPP
# include <Camera.hpp>
# endif

# ifndef HUD_HPP
# include <HUD.hpp>
# endif

# ifndef HEALBAGCONTROLLER_HPP
# include <healBagController.hpp>
# endif

//Scene that takes care of the actual game loop
class Gameplay : public Scene
{
	using Map = sf::Sprite;

public:
	Gameplay(sf::RenderWindow &);
	~Gameplay();

	Scene::Id execute();
	void set_up();

private:
	Map map;
	Camera camera;
	Cursor cursor;

	Player player;
	HUD playerHUD;

	Bullets bullets;
	Enemies enemies;
	Explosions explosions;
	healBagController bags;
	bool paused, GOverStarted;

	sf::Sprite m_GameOver;
};
