const std::string writeJsonToString(boost::property_tree::ptree root){
  std::ostringstream oss;
  boost::property_tree::write_json(oss, root);
  std::regex reg("\\\"([0-9]+\\.{0,1}[0-9]*)\\\"");
  const std::string result{std::regex_replace(oss.str(), reg, "$1")};
  return result;
}
