# include <Game.hpp>

# include <iostream>

Game::Game()
# ifdef RELEASE
: m_window(Helpers::getBestVideoMode(), "NanoSurgeon", sf::Style::Fullscreen)
# else
: m_window(Helpers::getBestVideoMode(), "NanoSurgeon", sf::Style::Titlebar | sf::Style::Close)
# endif // DEBUG
{
	# ifdef RELEASE
	m_current_scene = new Intro(m_window);
	# elif defined DEBUG

	m_current_scene = new Gameplay(m_window);
	Report::report_id(Report::report::extra, "Game created");

	# else
	m_current_scene = new Menu(m_window);
	#endif // RELEASE / DEBUG

	m_window.setFramerateLimit(60);
	m_window.setMouseCursorVisible(false);

	start();
}

Game::~Game()
{
	# ifdef DEBUG
	Report::report_id(Report::report::extra, "Game ended");
	# endif // DEBUG
}

void Game::start()
{
	while (true)
	{
		Scene::Id new_id = m_current_scene->execute();

		delete m_current_scene;
		m_current_scene = nullptr;

		if (new_id == Scene::Id::Quit)
			break;

		switch (new_id)
		{
			case Scene::Id::Menu:
				m_current_scene = new Menu(m_window);
			break;

			case Scene::Id::Gameplay:
				m_current_scene = new Gameplay(m_window);
			break;

			case Scene::Id::Paused:
				m_current_scene = new Menu(m_window);
			break;

			default:
			break;
		}
	}

	m_window.close();
}
