//перезаписать файл
const bool reWriteFile(const std::string filename, const std::vector<std::string> zapis){
	// Класс ofstream используется для записи данных в файл.
	// Создаем файл SofilenameText.txt
  // Открываем файл для записи.
  // Если файл с указанным именем не существует, то программа создает его
	std::ofstream outf(filename, std::ios::out);

	// Если мы не можем открыть этот файл для записи данных,
	if (!outf){
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
