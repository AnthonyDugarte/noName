# include <Attributes.hpp>

Attributes::Attributes(short unsigned health)
: m_health(health)
{
  // empty
}

const short unsigned & Attributes::get_health() const
{
  return m_health;
}

void Attributes::healted()
{
  if(m_health < 3)
    ++m_health;
}

void Attributes::attacked()
{
  if(m_health > 0)
    --m_health;

  m_attackable = false;
  m_attacked = true;
}

bool Attributes::recentlyAttacked()
{
  if(m_attacked)
  {
    m_attacked = false; // restore it's condition
    return true;
  }

  return false;
}

void Attributes::restoreAttackable()
{
  m_attackable = true;
}

void Attributes::inmortal()
{
  m_attackable = false;
}

bool Attributes::attackable() const
{
  return m_attackable;
}

bool Attributes::dead() const
{
  return m_health == 0;
}
