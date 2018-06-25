# define REPORT_HPP

# include <fstream>
# include <sstream>
# include <iostream>

# include <Singleton.hpp>

class Report : public Designar::Singleton<Report>
{
public:
  enum class report
  {
    assetManager_created, assetManager_killed,
    texture_created, texture_call,
    bitMask_created, bitMask_call,
    music_created, music_call,
    player_killed, player_created,
    animation_killed, animation_created,
    bullet_killed, bullet_created,
    enemy_killed, enemy_created,
    entity_killed, entity_created,
    extra
  };
  ~Report();

  static void report_id(report, const std::string & = std::string(""));
protected:
  Report();

private:
  long enemy_counter,
  player_counter,
  bullet_counter,
  animation_counter,
  texture_counter, texture_calls,
  bitMask_counter, bitMask_calls,
  music_counter, music_calls,
  assetManager_counter, assetManager_calls,
  entity_counter
  ;

  std::basic_ostringstream<char> output;

  friend class Singleton<Report>;
};
