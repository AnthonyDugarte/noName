# include <Report.hpp>

Report::Report()
  : output(),
  enemy_counter(0L),
  player_counter(0L),
  bullet_counter(0L),
  animation_counter(0L),
  texture_counter(0L),
  texture_calls(0L),
  bitMask_counter(0L),
  bitMask_calls(0L),
  music_counter(0L),
  music_calls(0L),
  assetManager_counter(0L),
  assetManager_calls(0L)
{
  output << "Report init" << std::endl;
}

Report::~Report()
{
  report_id(report::extra, "Report ended");


  std::ofstream outputFile("log.info", std::ios_base::trunc);

  if(not outputFile.is_open())
    std::cerr << "something went wrong with the report file";
  outputFile << output.str();
  outputFile.close();
}

void Report::report_id(report report_id, const std::string & message)
{
  auto && reporter{ get_instance() };

  switch (report_id)
  {
      case report::assetManager_created:
        reporter.output << message << ".... assetManager created. New Value: " << ++reporter.assetManager_counter << std::endl;
      break;
      case report::assetManager_killed:
        reporter.output << message << ".... assetManager killed. New Value: " << --reporter.assetManager_counter << std::endl;
      break;
      case report::texture_created:
        reporter.output << message << ".... texture created. New Value: " << ++reporter.texture_counter << std::endl;
      break;
      case report::texture_call:
        reporter.output << message << ".... texture call. New Value: " << ++reporter.texture_calls << std::endl;
      break;
      case report::bitMask_created:
        reporter.output << message << ".... bitMask created. New Value: " << ++reporter.bitMask_counter << std::endl;
      break;
      case report::bitMask_call:
        reporter.output << message << ".... bitMask call. New Value: " << ++reporter.bitMask_calls << std::endl;
      break;
      case report::music_created:
        reporter.output << message << ".... music created. New Value: " << ++reporter.music_counter << std::endl;
      break;
      case report::music_call:
        reporter.output << message << ".... music call. New Value: " << ++reporter.music_calls << std::endl;
      break;
      case report::player_killed:
        reporter.output << message << ".... player killed. New Value: " << --reporter.player_counter << std::endl;
      break;
      case report::player_created:
        reporter.output << message << ".... player created. New Value: " << ++reporter.player_counter << std::endl;
      break;
      case report::animation_killed:
        reporter.output << message << ".... animation killed. New Value: " << --reporter.animation_counter << std::endl;
      break;
      case report::animation_created:
        reporter.output << message << ".... animation created. New Value: " << ++reporter.animation_counter << std::endl;
      break;
      case report::bullet_killed:
        reporter.output << message << ".... bullet killed. New Value: " << --reporter.bullet_counter << std::endl;
      break;
      case report::bullet_created:
        reporter.output << message << ".... bullet created. New Value: " << ++reporter.bullet_counter << std::endl;
      break;
      case report::enemy_killed:
        reporter.output << message << ".... enemy killed. New Value: " << --reporter.enemy_counter << std::endl;
      break;
      case report::enemy_created:
        reporter.output << message << ".... enemy created. New Value: " << ++reporter.enemy_counter << std::endl;
      break;
      case report::entity_created:
        reporter.output << message << ".... Entity created. New Value: " << ++reporter.entity_counter << std::endl;
      break;
      case report::entity_killed:
        reporter.output << message << ".... Entity killed. New Value: " << --reporter.entity_counter << std::endl;
      break;
      case report::extra:
        reporter.output << message << std::endl;
      break;

  }
}
