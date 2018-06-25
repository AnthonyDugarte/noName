# include <Paused.hpp>

Paused::Paused(sf::RenderWindow & _win)
: Scene(Id::Paused, _win)
{
	# ifdef DEBUG
  Report::report_id(Report::report::extra, "Paused created");
  # endif // DEBUG

	auto && continue_texture{ AssetManager::getTexture("menu/paused/continue.png") };
	auto && quit_texture{ AssetManager::getTexture("menu/paused/quit.png") };

	float fullscreen_scaleX{ static_cast <float>(_win.getSize().x) / continue_texture.getSize().x };
	float fullscreen_scaleY{ static_cast <float>(_win.getSize().y) / continue_texture.getSize().y };

	m_sprite_continue.setTexture(continue_texture);
	m_sprite_quit.setTexture(quit_texture);

	m_sprite_continue.setScale(fullscreen_scaleX, fullscreen_scaleY);
	m_sprite_quit.setScale(fullscreen_scaleX, fullscreen_scaleY);
}

Paused::~Paused()
{
	# ifdef DEBUG
  Report::report_id(Report::report::extra, "Paused destroyed");
  # endif // DEBUG
}

Scene::Id Paused::execute()
{
	# ifdef RELEASE
	AssetManager & manager(AssetManager::get_instance());
	auto && menu_music = manager.getMusic("Menú.flac", true);
	auto && start_music = manager.getMusic("start.wav", true);
	auto && game_music = manager.getMusic("game.wav", true);
	game_music.pause();
	menu_music.play();
	# endif // RELEASE

	while (true)
	{
		// Event handling
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				return Scene::Id::Quit;

			if (event.type != sf::Event::KeyPressed)
				continue;

			if (event.key.code == sf::Keyboard::Key::Escape)
			{
				# ifdef RELEASE
				game_music.play();
				menu_music.pause();
				#endif // RELEASE

				return Scene::Id::Gameplay;
			}

			switch (m_selected)
			{
				case Option::Continue:
					if (event.key.code == sf::Keyboard::Key::Return)
					{
						# ifdef RELEASE
						game_music.play();
						menu_music.pause();
						# endif // RELEASE

						return Scene::Id::Gameplay;
					}
					if (event.key.code == sf::Keyboard::Key::Down)
						m_selected = Option::Quit;
				break;

				case Option::Quit:
					if (event.key.code == sf::Keyboard::Key::Return)
						return Scene::Id::Menu;
					if (event.key.code == sf::Keyboard::Key::Up)
						m_selected = Option::Continue;
				break;
			}
		}

		// Draw
		switch (m_selected)
		{
			case Option::Continue:
				m_window.draw(m_sprite_continue);
			break;

			case Option::Quit:
				m_window.draw(m_sprite_quit);
			break;
		}

		// Show
		m_window.display();
	}
}
