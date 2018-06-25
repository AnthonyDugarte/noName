# define ASSET_MANAGER_HPP

 # define RELEASE
//# define DEBUG

# ifdef DEBUG
# include <Report.hpp>
# else
# include <Singleton.hpp>
# endif //DEBUG

# include <map>
# include <string>
# include <exception>

# include <SFML/Graphics.hpp>
# include <SFML/Audio.hpp>

class AssetManager : public Designar::Singleton<AssetManager>
{
protected:
  // it is instanciated on Designar's Singleton
  AssetManager();

public:
  ~AssetManager();

  // it gets a texture from a file on a path, second parameter sais
  //    if it has to be created a bitMask from that texture.
  static sf::Texture & getTexture(const std::string &, bool = false);

  // they are pretty simple, get the thing of that file xD
  static sf::Music & getMusic(const std::string &, bool = false);
  static sf::Uint8 * getBitMask(const std::string &);

  // it gets the bitMask of the texture it's given as argument
  static sf::Uint8 * getBitMask(const sf::Texture *);

private:
  std::map <std::string, sf::Texture> m_textures;
  std::map<const sf::Texture *, sf::Uint8 *> m_bitmasks;
  std::map <std::string, sf::Music> m_musics;

  friend class Singleton<AssetManager>;
};
