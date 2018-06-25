# define HUD_HPP

# ifndef ANIMATEDSPRITE_HPP
# include <AnimatedSprite.hpp>
# endif

# ifndef ATTRIBUTES_HPP
# include <Attributes.hpp>
# endif

class HUD : public sf::Drawable
 {
 public:
   enum class healtState
   {
     empty = 0, almost_empty = 1, almost_full = 2, full = 3
   };

   HUD(const Attributes &, const std::string & = "attributes");

   void update(const sf::Time &, sf::RenderWindow &);

   AnimatedSprite<healtState> healt;

private:
  void draw(sf::RenderTarget &, sf::RenderStates) const;

  const Attributes & m_attributes;
};
