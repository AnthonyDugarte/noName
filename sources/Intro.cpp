# include <Intro.hpp>

Intro::Intro(sf::RenderWindow & _win)
  : Scene(Id::Intro, _win)
{
  # ifdef DEBUG
  Report::report_id(Report::report::extra, "Intro logo");
  # endif // DEBUG
}

Intro::~Intro()
{
	# ifdef DEBUG
  Report::report_id(Report::report::extra, "Intro logo destroyed");
  # endif // DEBUG
}

Scene::Id Intro::execute()
{
  auto && introTexture{ AssetManager::getTexture("menu/logo.png") };
  sf::Sprite introSprite(introTexture);

  introSprite.setOrigin(introTexture.getSize().x * .5f, introTexture.getSize().y * .5f);
  introSprite.setPosition(m_window.getSize().x * .5f, m_window.getSize().y * .5f);

  auto min = [](float a, float b) ->float{ return a < b ? a : b; };

  float scale(min((0.8f * m_window.getSize().x) / introTexture.getSize().x,
                                (0.8f * m_window.getSize().y) / introTexture.getSize().y));

  introSprite.setScale(scale, scale);
  sf::Color introColor(255, 255, 255, 0);

  float elapsed{ 0.f };
  float deadLine{ 3.f };
  sf::Clock gameClock;

  while(elapsed <= deadLine)
  {
    elapsed += gameClock.restart().asSeconds();

    introColor.a = (elapsed / deadLine) * 255;
    introSprite.setColor(introColor);

    m_window.clear(sf::Color::White);
    m_window.draw(introSprite);
    m_window.display();
  }

  return Scene::Id::Menu;
}
