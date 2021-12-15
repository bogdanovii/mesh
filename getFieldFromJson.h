const std::string getFieldFromJson(const std::string jsonST, const std::string field){

  //преобразуем строку в поток
  std::stringstream jsonEncoded(jsonST);

  boost::property_tree::ptree root;
  boost::property_tree::read_json(jsonEncoded, root);
  //если запрос пустой, то вернутьпустую строку
  if(root.empty()){
    return "";
  }/*if*/
  else{//потом проверить,Ю что такое поле существует, кстати , в будущем добавить
    const std::string ret{root.get<std::string>(field)};
    return ret;
  }/*else*/
}
