# include <AssetManager.hpp>

AssetManager::AssetManager()
  : m_textures()
{
  # ifdef DEBUG
  Report::report_id(Report::report::assetManager_created);
  # endif // DEBUG
}
AssetManager::~AssetManager()
{
  # ifdef DEBUG
  Report::report_id(Report::report::assetManager_killed);
  # endif // DEBUG

  while(not m_bitmasks.empty())
  {
    delete [] m_bitmasks.begin()->second;
    m_bitmasks.erase(m_bitmasks.begin());
  }
}

sf::Texture & AssetManager::getTexture(const std::string & name, bool create_BitMask)
{
  # ifdef DEBUG
  Report::report_id(Report::report::texture_call, name);
  # endif // DEBUG

  //Manager instance
  auto && instance { get_instance() };

  auto && search{ instance.m_textures.find(name) };
  if (search != instance.m_textures.end())
    return search->second;

    std::string prefix{ "assets/" };

  sf::Texture new_texture;
  if (not new_texture.loadFromFile(prefix + name))
    throw std::invalid_argument("texture could not be loaded: " + prefix + name);

  new_texture.setSmooth(true);

  instance.m_textures[name] = std::move(new_texture);

  if(create_BitMask)
    getBitMask(&instance.m_textures[name]);

  # ifdef DEBUG
  Report::report_id(Report::report::texture_created, name);
  # endif // DEBUG

  return *&instance.m_textures[name];
}

sf::Music & AssetManager::getMusic(const std::string & name_music, bool looping)
{
  # ifdef DEBUG
  Report::report_id(Report::report::music_call, name_music);
  # endif // DEBUG

  //Manager instance
  auto && instance { get_instance() };

  auto && search{ instance.m_musics.find(name_music) };
  if (search != instance.m_musics.end())
    return search->second;

  auto && new_music{ &instance.m_musics[name_music] };
  std::string prefix{ "music/" };

   if (new_music->openFromFile(prefix + name_music) == false)
    throw std::invalid_argument("music could not be loaded" + prefix + name_music);

  # ifdef DEBUG
  Report::report_id(Report::report::music_created, name_music);
  # endif // DEBUG

  if(looping)
    new_music->setLoop(true);

  return *&*new_music;
}

const std::pair<const sf::Texture *, sf::Uint8 *> getMask(const sf::Texture *);

sf::Uint8 * AssetManager::getBitMask(const std::string & name)
{
  # ifdef DEBUG
  Report::report_id(Report::report::bitMask_call, name);
  # endif // DEBUG

  //Manager instance
  auto && instance { get_instance() };

  sf::Texture * bitMaskTexture;

  //we charge our texture on the Manager so we have just one instance of bitMask per Texture
  try
  {
    bitMaskTexture = &getTexture(name);
  }
  catch(...)
  {
    throw std::invalid_argument("bitMask could not be loaded, file wasn't found: " + name);
  }

  auto && search{ instance.m_bitmasks.find(&*bitMaskTexture) };
  if(search != instance.m_bitmasks.end())
    return search->second;

  auto && new_mask{ getMask(&*bitMaskTexture) };

  instance.m_bitmasks.insert(std::move(new_mask));

  # ifdef DEBUG
  Report::report_id(Report::report::bitMask_created, name);
  # endif // DEBUG

  return *&new_mask.second;
}

sf::Uint8 * AssetManager::getBitMask(const sf::Texture * bitMaskTexture)
{
  # ifdef DEBUG
  Report::report_id(Report::report::bitMask_call, "from texture");
  # endif // DEBUG

  //Manager instance
  auto && instance { get_instance() };

  auto && search{ instance.m_bitmasks.find(&*bitMaskTexture) };
  if(search != instance.m_bitmasks.end())
    return &*search->second;

  auto && new_mask{ getMask(&*bitMaskTexture) };

  instance.m_bitmasks.insert(std::move(new_mask));

  # ifdef DEBUG
  Report::report_id(Report::report::bitMask_created, "from texture");
  # endif // DEBUG

  return &*new_mask.second;
}

const std::pair<const sf::Texture *, sf::Uint8 *> getMask(const sf::Texture * texture)
{
  sf::Image img{ texture->copyToImage() };
  sf::Uint8 * new_mask{ new sf::Uint8[texture->getSize().y * texture->getSize().x] };

  for(size_t y{ 0 }; y < texture->getSize().y ; ++y)
    for(size_t x{ 0 }; x < texture->getSize().x; ++x)
      new_mask[x + y * texture->getSize().x] = img.getPixel(x, y).a;

  return std::pair<const sf::Texture *, sf::Uint8 *>(&*texture, std::move(&*new_mask));
}
