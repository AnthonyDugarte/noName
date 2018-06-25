# define ANIMATION_HPP

# ifndef HELPERS_HPP
# include <Helpers.hpp>
# endif

# include <vector>

//Animation has the animation's frames, it's duration and it's loop conditional.
// if the animation is looping, it means that the animation is going to repite itself
// in the pass of time but, if it is not looping, it is going to show it last frame after the
// total duration has been reached
class Animation
{
public:
  // constructor takes as parameters the total time to get to the last frame
  // and if it is going to loop
  Animation(const sf::Time &, bool = false);
  Animation(const Animation &);
  ~Animation();

  //sets animation time elapsed to zero
  void reset();

  // methods identifiers are pretty clear I believe
  void setDuraton(const sf::Time &);
  void setLooping(bool);

  sf::Texture & getFrame() const;
  const sf::Time & getDuration() const;
  const sf::Time & getElapsed() const;
  bool getLooping() const;
  size_t size() const;

  // it's mean to work as a manual setter of frames getting as parameter
  // the complete path of it's texture on assets folder
  void addFrame(const std::string &);

  // parameter 1 is the path to a folder of animation,
  //    for simplicity, our animations using this method are going to have a name
  //    "frame" and what our function does is to take all frames starting from 1.
  //    it takes all frames placed on the prefix path
  // parameter 2 is the postfx of the frame,s by default they are ".png"
  void addFrames(const std::string &,
                                    const std::string & = ".png", bool = false);
  void addFrames(const std::string &, bool);

  // @note: This method is setted virtual so we can define different types of interactions
  // from derived classes, with aims of class Enemies having a global Animator.
  virtual void update(const sf::Time &);

private:
  std::vector<sf::Texture *> m_frames;
  sf::Time m_duration;
  bool m_looping;

  sf::Time m_elapsed;
  uint m_pos;
};
