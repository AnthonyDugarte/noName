# include <Gameplay.hpp>

Gameplay::Gameplay(sf::RenderWindow & _win)
: Scene(Id::Gameplay, _win),
  map(AssetManager::getTexture("maps/mapita.png")),
  camera(sf::Vector2f(0.f, 0.f), static_cast<sf::Vector2f>(m_window.getSize())),
  cursor(),
 	player("witch"), // assets folder to animate it's states and velocity it will have
  playerHUD(player, "attributes"),
  bullets("bullets/blueBullet.png"), // bullets asset and velocity
	explosions(sf::seconds(.5f), true, 270.f), // explsions duration, rotation and rotation per second
	enemies("plant", sf::seconds(1.f)), // enemies folder of assets and spawn time
  paused(false),
  bags(sf::seconds(30.f), 5u),
  m_GameOver(AssetManager::getTexture("gameover.png")),
  GOverStarted(false)
{
  # ifdef DEBUG
  Report::report_id(Report::report::extra, "Game init");
  # endif // DEBUG

	set_up();
}


Gameplay::~Gameplay()
{
  # ifdef DEBUG
  Report::report_id(Report::report::extra, "Game end");
  # endif // DEBUG
}

Scene::Id Gameplay::execute()
{
  #ifdef RELEASE
  auto && game_music{ AssetManager::getMusic("game.wav", true) };
  auto && start_music{ AssetManager::getMusic("start.wav", true) };
  auto && gameOverMusic { AssetManager::getMusic("GameOverShort.wav") };
  auto && menu_musc { AssetManager::getMusic("Menú.flac", true) };
  start_music.play();
  sf::sleep(sf::milliseconds(1000));
  start_music.stop();
  game_music.play();
  #endif


	sf::Clock gameClock;
	sf::Time dt;

  gameClock.restart();
	while (true) // game loop
	{
		dt = gameClock.restart();

		sf::Event event;
    while (m_window.pollEvent(event))
		{
      if(not paused)
        cursor.handleEvent(event);

			switch (event.type)
			{
				case sf::Event::Closed:
					return Scene::Id::Quit;
				break; // sf::Event::Closed

				case sf::Event::KeyPressed:
					switch (event.key.code)
					{
						case sf::Keyboard::Key::Escape:
						{
              m_window.setView(m_window.getDefaultView());

              if(player.dead())
              {
                # ifdef RELEASE
                gameOverMusic.stop();
                menu_musc.play();
                # endif


                return Scene::Id::Menu;
              }

              paused = true;
              sf::Time dtAux { dt };
							auto result = Paused(m_window).execute();

							if (result == Scene::Id::Gameplay)
              {
                dt = sf::Time::Zero;
                //dt = dtAux;
                paused = false;
                continue;
              }
							else return result;
						}
						break; // sf::Keyboard::Key::Escape:

						default: break;
					}
				break; // sf::Event::KeyPressed:

        default: break;
      }
		}// event type

    if(not paused)
    {
      player.update(dt, &map); // map specifies that collisions are handled
      bags.update(dt, &player, &map);
      // fits the camera so don't get away form the map
      // and still follows the player
      camera.fitWith(&player, &map);

      // If camera is not setted, enemies spawn at the origion,
      // if map is not specified, there are to cases:
      // ** if spawnInside() is activated, it doesn't matter not to pass a map, for now
      // ** if spwanOutside() is activated, it needs a map because these are going to be
      //      the boundries for spawning.
      enemies.update(dt, &camera, &map);

      // if camera is specified, bullets crash when they go out of it
      // if map is specified, bullets take care of map collisions.
      bullets.update(dt, &camera, &map);
      explosions.update(dt);

      m_window.setView(camera);

      //updates the window relative cursor's position
      cursor.update(m_window);

      //updates player's HUD stuff and fits them on the window
      playerHUD.update(dt, m_window);

      if(player.dead() and not GOverStarted)
      {
          GOverStarted = true;
          game_music.pause();
          gameOverMusic.play();

        m_GameOver.setPosition(camera.getCenter());
        m_GameOver.move(0, camera.getSize().y * 0.3f);
      }

      // Draw
      m_window.clear(sf::Color(236, 240, 241));

      m_window.draw(map);
      m_window.draw(enemies);
      m_window.draw(bags);
      m_window.draw(bullets);
      m_window.draw(explosions);
      m_window.draw(playerHUD);
      m_window.draw(player);
      if(player.dead())
        m_window.draw(m_GameOver);
      m_window.draw(cursor);

      // Show
      m_window.display();
    }
	}
}

void Gameplay::set_up()
{
  {
    float scale{ Helpers::getVector2Min(Helpers::getProportionalScale(camera, map, 3.f)) }; //2 times of camera size
    map.setScale(scale, scale);
  }

  cursor.setTexture(AssetManager::getTexture("cursor/cursor_iddle.png"), true);
  {
    float scale{ Helpers::getVector2Min(Helpers::getProportionalScale(camera, cursor, .03f)) }; //3% of camera size

    cursor.setScale( scale, scale);
  }
  cursor.setPlayer(&player);

  //player.addState(EntityState::standing, "Stand", sf::seconds(1.f), false);
  player.addState(EntityState::dead, "Death", sf::seconds(2.f), false);
  player.addState(EntityState::moveLeft, "Left", sf::seconds(1.f), true);
  player.addState(EntityState::moveRight, "Right", sf::seconds(1.f), true);
  //player.addState(EntityState::moveUp, "Up", sf::seconds(1.f), true);
  //player.addState(EntityState::moveDown, "Down", sf::seconds(1.f), true);
  player.addState(EntityState::standing, "Iddle", sf::seconds(2.5f), true, false);
  player.addState(EntityState::spinning, "Spinning", sf::seconds(.6f), false, false);

  player.setState(EntityState::standing, true);

  {
    player.update(sf::Time::Zero);
    float scale{ Helpers::getVector2Min(Helpers::getProportionalScale(camera, player, .1f)) }; //10% of camera size
    player.setScale(scale, scale);
  }
  player.setVelocity(200.f);
  player.setOrigin(Helpers::GetSpriteCenter(player));

  do
  {
    player.setPosition(Helpers::randomMapPos(&map)/*300, 300*/);
  }while(Helpers::hasCollision(player, map, Globals::mapGround));

  player.setBullets(bullets);

  playerHUD.healt.addState(HUD::healtState::empty, "empty", sf::seconds(1.f), false);
  playerHUD.healt.addState(HUD::healtState::almost_empty, "almost_empty", sf::seconds(1.f), false);
  playerHUD.healt.addState(HUD::healtState::almost_full, "almost_full", sf::seconds(1.f), false);
  playerHUD.healt.addState(HUD::healtState::full, "full", sf::seconds(1.f), false);
  playerHUD.healt.setState(HUD::healtState::full, true);

  {
    playerHUD.healt.update(sf::Time::Zero, false);
    float scale{ Helpers::getVector2Min(Helpers::getProportionalScale(camera, playerHUD.healt, .15f)) }; //20% of camera size

    playerHUD.healt.setScale(scale, scale);
  }

  enemies.enemyTemplate.addState(EntityState::standing, "Iddle", sf::seconds(1.f), true, false);
  //enemies.enemyTemplate.addState(EntityState::moveLeft, "Left", sf::seconds(1.f), true);
  //enemies.enemyTemplate.addState(EntityState::moveRight, "Right", sf::seconds(1.f), true);
  //enemies.enemyTemplate.addState(EntityState::moveUp, "Up", sf::seconds(1.f), true);
  //enemies.enemyTemplate.addState(EntityState::moveDown, "Down", sf::seconds(1.f), true);
  enemies.enemyTemplate.addState(EntityState::attacking, "Attack", sf::seconds(1.f), true, false);

  enemies.enemyTemplate.setState(EntityState::standing, true);

  {
    enemies.enemyTemplate.update(sf::Time::Zero);
    float scale{ Helpers::getVector2Min(Helpers::getProportionalScale(camera, enemies.enemyTemplate, .1f)) }; //20% of camera size

    enemies.enemyTemplate.setScale(scale, scale);
  }
  enemies.enemyTemplate.setVelocity(200.f);
  enemies.enemyTemplate.setAttackRange(200.f);

  enemies.setEnemy(&player);
  enemies.spawnOutside();

  {
    sf::Sprite bulletSprite(bullets.getTexture());
    float scale{ Helpers::getVector2Min(Helpers::getProportionalScale(camera, bulletSprite, .03f)) }; // 4% of camera size

    bullets.setScale(sf::Vector2f(scale, scale));
  }
  bullets.setVelocity(1200.f); // big value because of the bullet's scale

  bullets.setEnemies(enemies);
  bullets.setExplosions(explosions);

  explosions.addFrames("animations/discExplosion");
  {
    explosions.update(sf::Time::Zero);
    sf::Sprite explosion(explosions.getFrame());

    sf::Vector2f explosionScale(Helpers::getProportionalScale(camera, explosion, .07f)); // 7% of camera size

    float scale { Helpers::getVector2Min(explosionScale) };
    explosions.setScale(sf::Vector2f(scale, scale));
  }

  bags.m_animation.addFrames("animations/Heal");
  {
    bags.m_animation.update(sf::Time::Zero);
    sf::Sprite sprite(bags.m_animation.getFrame());

    float scale{ Helpers::getVector2Min(Helpers::getProportionalScale(camera, sprite, .04f)) }; //20% of camera size

    bags.setScale(sf::Vector2f(scale, scale));
  }

  camera.setCenter(player.getPosition());

  {
    float scale{ Helpers::getVector2Min(Helpers::getProportionalScale(camera, m_GameOver, .45f)) }; // 45% of camera size
    m_GameOver.setScale(sf::Vector2f(scale, scale));
  }
  m_GameOver.setOrigin(Helpers::GetSpriteCenter(m_GameOver));
}
