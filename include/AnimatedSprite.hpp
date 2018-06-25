# define ANIMATEDSPRITE_HPP

# ifndef ANIMATOR_HPP
# include <Animator.hpp>
# endif

/* Class that takes care of the sprite's animation
 *
 * Constructor takes as parameter the folder on-> assets/animations
 *  that has stored the animations it's going to need
 *
 *  It's main reason is to work as a wrapper for animation selection between
 *  states
*/

template<class T>
class AnimatedSprite : public sf::Sprite
{
public:
  AnimatedSprite(const std::string &);// animations folder on -> assets/animations
  AnimatedSprite(const AnimatedSprite<T> &);
  AnimatedSprite() = delete;

  // returns actual state
  T getState() const;

  // sets state to animate previously added via addState
  // if state isn't setted, because it hasn't been stored of something else, it returns false
  // @param 2 dictates if state should start from begining of keep
  // its previous course
  bool setState(const T &, bool);

  // @Param 1: State to add, if state is added already, it anin't touched
  // it takes the state to add, the name of its on -> assets/animations/folder/
  // the time it's goint to take the reach de last frame
  // and if it is is a loop or not
  void addState(const T & state, const std::string & folderName,
    const sf::Time & duration, bool looping = false, bool reverseAnimation = false);

  void update(const sf::Time &, bool = true);

private:
  Animator<T> m_animator;

  std::string m_folder;
}; // AnimatedSprite


template <class T>
AnimatedSprite<T>::AnimatedSprite(const std::string & folder)
  : m_animator(),
    m_folder(std::move(folder))
{
  //empty
}

template <class T>
AnimatedSprite<T>::AnimatedSprite(const AnimatedSprite<T> & copy)
  : m_animator(copy.m_animator),
    m_folder(copy.m_folder)
{
  // empty
}

template <class T>
T AnimatedSprite<T>::getState() const
{
  return m_animator.getCurrentAnimationName();
}

template <class T>
bool AnimatedSprite<T>::setState(const T & state, bool reset)
{
  return m_animator.switchAnimation(state, reset);

  m_animator.update(sf::seconds(0.f));
  setTexture(m_animator.getFrame(), true);
}

template <class T>
void AnimatedSprite<T>::addState(const T & state, const std::string & folderName,
  const sf::Time & duration, bool looping, bool reverseAnimation)
{
  m_animator.createAnimation(state, duration, looping);

  std::string prefix{ m_folder + "/" };

  m_animator.addFrames(state, prefix + folderName, reverseAnimation);
}

template <class T>
void AnimatedSprite<T>::update(const sf::Time & dt, bool updatedOrigin)
{
  m_animator.update(dt);
  setTexture(m_animator.getFrame(), true);

  if(updatedOrigin)
    setOrigin(Helpers::getSpriteLocalCenter(*this));
  setScale(getScale());
}
