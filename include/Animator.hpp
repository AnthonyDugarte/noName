# define ANIMATOR_HPP

# ifndef ANIMATION_HPP
# include <Animation.hpp>
# endif

# include <list>

// it's name is pretty clear, it animates, how? It stores a bunch of animations by
// their name(T), it stores a pointer to the actual animation being used so when updating
// it's frame with dt, it just calls the update method of that single animation
template <class T>
class Animator
{
public:
  Animator();
  Animator(const Animator<T> &);

  ~Animator();

  // @Parama 1: Animation Name.
  // @Param 2: Animation duration.
  // @Param 3: Loop condition
  void createAnimation(const T &, const sf::Time &, bool = false);

  // @Param 1: Animation name to switch to, if it fails for any reason, it returns false
  // @Param 2: Enforce resetment of an animation
  bool switchAnimation(const T &, bool = false);

  // @Param: Name of the Animation to look for
  Animation* findAnimation(const T &);
  // @Param: Current animation name
  T getCurrentAnimationName() const;

  // @Method: it returns the texture of the current frame of the animation being,
  //    my bad, animated.
  sf::Texture & getFrame() const;

  // @Description: It takes an animation name; if is hasn't been added, it just do nothing;
  //    and stores the frames of a path stored on -> assets/animations/
  //    using the method from Animation class that has the same name.
  void addFrames(const T &, const std::string &,
    const std::string & = ".png", bool = false);
  void addFrames(const T &, const std::string &,
    bool = false);

  virtual void update(const sf::Time &);

private:
  void switchAnimation(Animation *, const T &, bool);

  Animation * m_current;
  T m_currentName;

  std::map<T, Animation *> m_animations;
}; // Animator


template <class T>
Animator<T>::Animator()
  : m_current(nullptr),
    m_currentName(),
    m_animations()
{
  //empty
}
template <class T>
Animator<T>::Animator(const Animator<T> & copy)
  : m_current(nullptr),
  m_currentName()
{
  for(auto && animation : copy.m_animations)
    m_animations[animation.first] = new Animation(*animation.second);

  switchAnimation(copy.getCurrentAnimationName(), true);
}


template <class T>
Animator<T>::~Animator()
{
  for(auto && it : m_animations)
    delete it.second;
}

template <class T>
void Animator<T>::createAnimation(const T & name,
  const sf::Time & duration, bool loop)
{
  if(m_animations.find(name) == m_animations.end())
    m_animations[name] = new Animation(duration, loop);

  if(m_current == nullptr)
    switchAnimation(&*m_animations[name], name, true);
}

template <class T>
bool Animator<T>::switchAnimation(const T & name, bool reset)
{
  auto && animation{ findAnimation(name) };

  if(animation != nullptr)
  {
    switchAnimation(&*animation, name, reset);
    return true;
  }

  return false;
}

template <class T>
Animation * Animator<T>::findAnimation(const T & name)
{
  auto && animation{ m_animations.find(name) };

  if(animation != m_animations.end())
    return &*animation->second;

  return nullptr;
}

template <class T>
T Animator<T>::getCurrentAnimationName() const
{
    return m_currentName;
}

template<class T>
sf::Texture & Animator<T>::getFrame() const
{
  return m_current->getFrame();
}

template <class T>
void Animator<T>::addFrames(const T & name, const std::string & path,
  const std::string & sufix, bool reverseAnimation)
{
  auto && animation{ m_animations.find(name) };

  if(animation == m_animations.end())
    return;

  std::string prefix{ "animations/" };

  animation->second->addFrames(prefix + path, sufix, reverseAnimation);
}

template <class T>
void Animator<T>::addFrames(const T & name, const std::string & path,
  bool reverseAnimation)
{
    addFrames(name, path, ".png" , reverseAnimation);
}

template <class T>
void Animator<T>::update(const sf::Time & dt)
{
  if(m_current == nullptr)
    return;

  m_current->update(dt);
}

template <class T>
void Animator<T>::switchAnimation(Animation* animation, const T & animationName,
    bool resetAnimation)
{
  m_current = &*animation;
  if(resetAnimation and animationName != m_currentName)
    m_current->reset();
  m_currentName = animationName;
}
