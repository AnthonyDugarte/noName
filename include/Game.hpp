# define GAME_HPP

# ifndef INTRO_HPP
# include <Intro.hpp>
# endif

# ifndef MENU_HPP
# include <Menu.hpp>
# endif

# ifndef GAMEPLAY_HPP
# include <Gameplay.hpp>
# endif

// Begining of everything, it creates the main window and handles
// the chanage between scenes, it's ful of swag
class Game
{
public:
	//yep, it has a constructor
	Game();
	~Game();

private:
	//	thing in charge of begining everything
	void start();

	sf::RenderWindow m_window;
	Scene * m_current_scene = nullptr;
};
