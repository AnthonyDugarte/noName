# define SCENE_HPP

# include <SFML/Graphics.hpp>

class Scene
{
public:
	enum class Id { Intro, Menu, Gameplay, Paused, Quit };

	Scene(Id, sf::RenderWindow &);

	virtual ~Scene();
	virtual Id execute() = 0;
	Id getId() const;

protected:
	Id m_id;
	sf::RenderWindow & m_window;
};
