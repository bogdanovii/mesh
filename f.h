const bool py_script(const std::string name){
	//запуск питон скрипта
        const std::string imy_scripta = name;
        //кем запускам скрипт
        const std::string imy_interprit = "python";

        const std::string str = imy_interprit + " " + imy_scripta;
        const char * in_to_sys = str.c_str();
        const int res = system(in_to_sys);
	if( res == 0){return true;}
	else{return false;}
}
