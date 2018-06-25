# include <Cursor.hpp>

Cursor::Cursor()
  : m_player(nullptr)
{
  # ifdef RELEASE
  shoot_music = &AssetManager::getMusic("shoot.wav");
  # endif // RELEASE

  # ifdef DEBUG
  Report::report_id(Report::report::extra, "Cursor created");
  # endif // DEBUG
}

Cursor::~Cursor()
{
  # ifdef RELEASE
  shoot_music = nullptr;
  # endif // RELEASE

  # ifdef DEBUG
  Report::report_id(Report::report::extra, "Cursor destroyed");
  # endif // DEBUG

  m_player = nullptr;
}

void Cursor::setPlayer(Player * player)
{
  m_player = &*player;
}

void Cursor::handleEvent(const sf::Event & event)
{
  switch (event.type)
  {
    case sf::Event::MouseButtonPressed:
      switch(event.mouseButton.button)
      {
        case sf::Mouse::Button::Left:
        if(m_player != nullptr and not m_player->dead())
        {
          m_player->shoot(getPosition());

          # ifdef RELEASE
          shoot_music->play();
          # endif // RELEASE
        }
        break;

        case sf::Mouse::Button::Right:
        if(m_player != nullptr)
          m_player->spin();

        default: break;
      }
    break; //MouseButtonPressed

    default: break;
  } // event type
}

void Cursor::update(const sf::RenderWindow & window)
{
  setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
}
