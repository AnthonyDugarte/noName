# include <Animation.hpp>

Animation::Animation(const sf::Time & duration, bool looping)
  : m_frames(),
    m_duration(duration),
    m_looping(looping),
    m_elapsed(),
    m_pos(0u)
{
  # ifdef DEBUG
  Report::report_id(Report::report::animation_created);
  # endif // DEBUG
}

Animation::Animation(const Animation & copy)
  : m_elapsed(),
    m_pos(0u)
{
  # ifdef DEBUG
  Report::report_id(Report::report::animation_created, "copy constructor");
  # endif // DEBUG

  for(auto && texture : copy.m_frames)
    m_frames.push_back(&*texture);

  m_duration = copy.m_duration;
  m_looping = copy.m_looping;
}

Animation::~Animation()
{
  # ifdef DEBUG
  Report::report_id(Report::report::animation_killed);
  # endif // DEBUG

  while(not m_frames.empty())
  {
    m_frames.back() = nullptr;
    m_frames.pop_back();
  }
}

void Animation::reset()
{
  m_pos = 0;
  m_elapsed = sf::Time::Zero;
}

void Animation::setDuraton(const sf::Time & duration)
{
  m_duration = duration;
}

void Animation::setLooping(bool looping)
{
  m_looping = looping;
}

sf::Texture & Animation::getFrame() const
{
  return *m_frames[m_pos];
}

const sf::Time & Animation::getDuration() const
{
  return m_duration;
}

const sf::Time & Animation::getElapsed() const
{
  return m_elapsed;
}

bool Animation::getLooping() const
{
  return m_looping;
}

size_t Animation::size() const
{
  return m_frames.size();
}

void Animation::addFrame(const std::string & path)
{
  m_frames.push_back(&AssetManager::getTexture(path));
}

void Animation::addFrames(const std::string & path,
  const std::string & sufix, bool reverse_animation)
{
  std::string prefix{ "/frame" };
  size_t i { 0u };

  while(true)
  {
    try
    {
      addFrame(path + prefix + std::to_string(i++) + sufix);
    }
    catch(...)
    {
      i -= 2;
      break;
    }
  }

  //if the animation is looping we are adding the counter part animations to the end
  // of the vector so we can have a simpler implementation on the update() method
  if(m_looping and reverse_animation)
    for(size_t it{ m_frames.size() - 1 }; i > 0; --i, --it)
      m_frames.push_back(&*m_frames[it]);
}
void Animation::addFrames(const std::string & path, bool reverse_animation)
{
  addFrames(path, ".png", reverse_animation);
}

void Animation::update(const sf::Time & dt)
{
  m_elapsed += dt;

  float scaledTime { m_elapsed.asSeconds() / m_duration.asSeconds() };
  size_t numFrames { m_frames.size() };

  m_pos = scaledTime * numFrames;

  if(m_looping)
    m_pos %= numFrames;
  else if(m_pos >= numFrames) // if the current frame is greater than the number of frames
    m_pos = numFrames - 1; //show the last one
}
