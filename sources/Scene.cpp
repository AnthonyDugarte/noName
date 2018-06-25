# include <Scene.hpp>

Scene::Scene(Id _id, sf::RenderWindow & _win)
: m_id(_id),
	m_window(_win)
{
	# ifdef DEBUG
  Report::report_id(Report::report::extra, "Scene created");
  # endif // DEBUG
}

Scene::~Scene()
{
	# ifdef DEBUG
  Report::report_id(Report::report::extra, "Scene destroyed");
  # endif // DEBUG
}

Scene::Id Scene::getId() const
{
	return m_id;
}
