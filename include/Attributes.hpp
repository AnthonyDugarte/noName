# define ATTRIBUTES_HPP

class Attributes
{
public:
  Attributes(short unsigned health = 3);

  const short unsigned & get_health() const;
  void healted();

  void attacked();
  void restoreAttackable();
  void inmortal();
  bool attackable() const;
  bool recentlyAttacked();

  bool dead() const;

private:
  short unsigned m_health;

  bool m_attacked = false;
  bool m_attackable = true;
};
