#ifndef CONFIG_CPP
#define CONFIG_CPP

#include "config.hpp"

using namespace std;

string Config::ClipBoardGetTextCmd = "";
string Config::ClipBoardSetTextCmd = "";

void Config::SetDefaults() {
  ClipBoardGetTextCmd = "xsel -p";
  ClipBoardSetTextCmd = "xsel -i -p";
}

void Config::Reload() {
  // properly get the home directory
  string home = getenv("HOME");
  // full path to the config file
  string config_file = home + "/.bpprc";

  // check if the config file exists
  ifstream f(config_file.c_str());
  if (!f.good()) {
    // save the default config
    Config::SetDefaults();
    Config::Save();
  }

  // create a property tree
  boost::property_tree::ptree pt;
  // read the config file
  boost::property_tree::ini_parser::read_ini(config_file, pt);

  // set the config values
  ClipBoardGetTextCmd = pt.get<string>("clipboard.get_text_cmd");
  ClipBoardSetTextCmd = pt.get<string>("clipboard.set_text_cmd");
}

void Config::Save() {
  // create a property tree
  boost::property_tree::ptree pt;
  // properly get the home directory
  string home = getenv("HOME");
  // full path to the config file
  string config_file = home + "/.bpprc";

  // set the config values and example values
  pt.put("clipboard.# This command is used to get text from the clipboard\t", ">");
  pt.put("clipboard.#   If you use X11 you could use \"xsel -p\"\t", ">");
  pt.put("clipboard.#   Without an X11 you can use \"cat /tmp/clipboard 2>/dev/null\"\t", ">");
  pt.put("clipboard.get_text_cmd", ClipBoardGetTextCmd);

  //pt.add_child("", boost::property_tree::ptree{""});

  pt.put("clipboard.# This command is used to set text to the clipboard\t", ">");
  pt.put("clipboard.#   If you use X11 you could use \"xsel -i -p\"\t", ">");
  pt.put("clipboard.#   Without an X11 you can use \"cat >/tmp/clipboard 2>/dev/null\"\t", ">");
  pt.put("clipboard.set_text_cmd", ClipBoardSetTextCmd);

  // write the config file
  boost::property_tree::ini_parser::write_ini(config_file, pt);
}

#endif
