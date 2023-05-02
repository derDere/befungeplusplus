#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

using namespace std;

// A config class that loads and saves static config values from a config-ini file loacated in the users home directory names .bpprc
class Config {
  private:
    Config() {}
    ~Config() {}

    static void SetDefaults();

  public:
    static void Reload();
    static void Save();

    static string ClipBoardGetTextCmd;
    static string ClipBoardSetTextCmd;
};

#endif
