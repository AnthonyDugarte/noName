# define CURSOR_HPP

# ifndef PLAYER_HPP
# include <Player.hpp>
# endif

class Cursor : public sf::Sprite
{
public:
  Cursor();
  ~Cursor();

  void setPlayer(Player * ); // for shooting stuff

  void handleEvent(const sf::Event &);
  void update(const sf::RenderWindow &);

private:
  Player * m_player;

  #ifdef RELEASE
	sf::Music * shoot_music;
  #endif
};
