# include <Menu.hpp>

Menu::Menu(sf::RenderWindow & _win)
: Scene(Id::Menu, _win),
	m_selected(Option::Play)
{
	# ifdef DEBUG
  Report::report_id(Report::report::extra, "Menu created");
  # endif // DEBUG

	auto && play_texture{ AssetManager::getTexture("menu/main/play.png") };
	auto && quit_texture{ AssetManager::getTexture("menu/main/quit.png") };

	float fullscreen_scaleX{ static_cast <float>(_win.getSize().x) / play_texture.getSize().x };
	float fullscreen_scaleY{ static_cast <float>(_win.getSize().y) / play_texture.getSize().y };

	m_sprite_play.setTexture(play_texture);
	m_sprite_quit.setTexture(quit_texture);

	m_sprite_play.setScale(fullscreen_scaleX, fullscreen_scaleY);
	m_sprite_quit.setScale(fullscreen_scaleX, fullscreen_scaleY);
}

Menu::~Menu()
{
	# ifdef DEBUG
  Report::report_id(Report::report::extra, "Menu destroyed");
  # endif // DEBUG
}


Scene::Id Menu::execute()
{
	# ifdef RELEASE
	AssetManager & manager{ AssetManager::get_instance() };
	auto && menu_musc = manager.getMusic("Menú.flac", true);
	auto && start_music = manager.getMusic("start.wav", true);
	auto && game_music = manager.getMusic("game.wav", true);
	game_music.stop();
	if(menu_musc.getStatus() == sf::SoundSource::Stopped)
		menu_musc.play();
	# endif // RELEASE

	while (true)
	{
		// Event Handling
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				return Scene::Id::Quit;

			if (event.type != sf::Event::KeyPressed)
				continue;

			switch (m_selected)
			{
				case Option::Play:
					if (event.key.code == sf::Keyboard::Key::Return)
					{
						# ifdef RELEASE
						menu_musc.pause();
						# endif // RELEASE
						return Scene::Id::Gameplay;
					}
					if (event.key.code == sf::Keyboard::Key::Down)
						m_selected = Option::Quit;
				break;

				case Option::Quit:
					if (event.key.code == sf::Keyboard::Key::Return)
						return Scene::Id::Quit;
					if (event.key.code == sf::Keyboard::Key::Up)
						m_selected = Option::Play;
				break;
			}
		}

		// Draw
		switch (m_selected)
		{
			case Option::Play:
				m_window.draw(m_sprite_play);
			break;

			case Option::Quit:
				m_window.draw(m_sprite_quit);
			break;
		}

		// Show
		m_window.display();
	}

}
