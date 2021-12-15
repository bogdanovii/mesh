#include "readFile.h"
#include "reWriteFile.h"
#include "getFieldFromJson.h"

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

//записать в конец файла с новой строки
const bool writeFile(const std::string filename, const std::vector<std::string> zapis){
                        // Класс ofstream используется для записи данных в файл.
                        // Создаем файл SofilenameText.txt
                        std::ofstream outf(filename, std::ios::app);

                        // Если мы не можем открыть этот файл для записи данных,
                        if (!outf)
                        {
                                // то выводим сообщение об ошибке и выполняем функцию exit()
                                std::cerr << "Uh oh, SomeText.txt could not be opened for writing!" << std::endl;
                                return false;
                        }

                        // Записываем в файл следующие две строки
                        for(int i = 0; i < zapis.size(); i++){
                                outf << zapis.at(i) << std::endl;
                        }

                        outf.close();

                        return true;
}
