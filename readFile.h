//функция читает файл и каждую его строку пишет в массив
//возвращает тру или фалс успеха считки в первом значении и массив во втором значении
const std::pair< bool, std::vector<std::string> > readFile(const std::string filename){
	// ifstream используется для чтения содержимого файла.
	// Попытаемся прочитать содержимое файла SomeText.txt
	std::ifstream inf(filename);

	// Пока есть данные, которые мы можем прочитать,
	std::vector<std::string> bscy_s;

	// Если мы не можем открыть этот файл для чтения его содержимого,например, файла нет, или он занят
	if (!bool(inf)){
		// то выводим следующее сообщение об ошибке и выполняем функцию exit()
    inf.close();
		std::cerr << "Не получается открыть файл на чтение!" << std::endl;
	  const std::vector<std::string> ret{bscy_s};

	  return std::pair<bool, std::vector<std::string> >(false,ret);
	}


	while (inf){
		// то перемещаем эти данные в строку, которую затем выводим на экран
		std::string strInput;
		inf >> strInput;
		bscy_s.push_back(strInput);
	}

	inf.close();

	const std::vector<std::string> ret{bscy_s};
	return std::pair<bool, std::vector<std::string> >(true,ret);
}
