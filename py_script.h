//в данную функцию посылается имя питн скрипта и она его запускает
//возвращает ПРАВДУ если норм вызвалась и непрадву, если проблема
//потом добавить конкретизацию по кодам ошибок
const bool py_script(const std::string name){
	//запуск питон скрипта
        const std::string imy_scripta = name;
        //кем запускам скрипт
        const std::string imy_interprit = "python3";//если че убрать цифру три и будет работать

        const std::string str = imy_interprit + " " + imy_scripta;
        const char * in_to_sys = str.c_str();
        const int res = system(in_to_sys);
	if( res == 0){return true;}
	else{return false;}
}
