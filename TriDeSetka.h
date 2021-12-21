class TriDeSetka{
	private:
    //название файлоа с данными по сетке
		const std::string border_step_chyzlov_yacheek = "border_step_chyzlov_yacheek_setka";
		const std::string iskrivlenye = "iskrivlenye_setka";
		const std::string massiv_yzlov = "massiv_yzlov_setka";

		const std::vector <std::string> checkBSCY{"{", "\"xStart\" : ", "\"xFinish\" : ", "\"yStart\" : ", "\"yFinish\" : ", "\"zStart\" : ", "\"zFinish\" : ", "\"StepX\" : ", "\"StepY\" : ", "\"StepZ\" : ", "}"};

		//данные сетки
		float xStart;
		float xFinish;

		float yStart;
		float yFinish;

		float zStart;
		float zFinish;

		//зададим шаг сетки вдоль каждой из осей x и y
		float StepX;
		float StepY;
		float StepZ;

		//узлы вдоль каждой из осей
		int N_x;
		int N_y;
		int N_z;

		//число узлов
		int Number_of_nodes;
		int Number_of_cells;

		std::vector<Coord_of_Node> c_of_n;
		std::vector<Coord_of_Node> c_of_nZYX;

		void check_bscy(){//порверка файла границу, шага\, чисоа ячеек

			// Пока есть данные, которые мы можем прочитать,
			//const bool res{analiz_faula_border_step_chyzlov_yacheek("border_step_chyzlov_yacheek")}
      //
      const std::pair< bool, std::vector<std::string> > my_pair = readFile(this->border_step_chyzlov_yacheek);

      if(my_pair.first == false){
        std::cerr << "Не удалось открыть файл c границами и шагами!" << std::endl;
        std::cerr << "Для данный файл с образцовыми данными будет сгенерирован автоматически." << std::endl;
        // в будущем добавить проверку на то что файл существует в папке, но просто занят другим процессом
				generate_bscy();
			}/*if*/

      else{//my_pair.first == true
        //считаем данные и проверим их, еси неверно сообощение и испрвим
				//в готовых данных удаляем новые строки

				std::string res_of_fr;
				for(int i = 0; i < my_pair.second.size(); i++){
					if(i == 0){
						res_of_fr = my_pair.second.at(i);
					}
					else{
						res_of_fr = res_of_fr + " " + my_pair.second.at(i);
					}
				}/*for*/
				//std::cout << "Привет из елса" << std::endl;
				//std::cout << res_of_fr << std::endl;
				//делаем проверку путем поиска основных значений
				//получить значение поля из json по имени
				//std::cout<< getFieldFromJson(res_of_fr, "StepZ") << std::endl;
				//Делаем переборку, чтобы убедиться, что все поля перезаписать
				for(int i = 0; i < (checkBSCY.size() - 2); i++){
					std::string temp = checkBSCY.at(i + 1);
					temp.erase(temp.begin());//удалили первый симавола
					temp.erase((temp.length() - 4), 4);
					getFieldFromJson(res_of_fr, temp);//убрать последние 4 симавола и далить первый
				}

				//запишем в поля класса значения
				this->xStart = ::atof(getFieldFromJson(res_of_fr, "xStart").c_str());
				this->xFinish = ::atof(getFieldFromJson(res_of_fr, "xFinish").c_str());
				this->yStart = ::atof(getFieldFromJson(res_of_fr, "yStart").c_str());
				this->yFinish = ::atof(getFieldFromJson(res_of_fr, "yFinish").c_str());
				this->zStart = ::atof(getFieldFromJson(res_of_fr, "zStart").c_str());
				this->zFinish = ::atof(getFieldFromJson(res_of_fr, "zFinish").c_str());
				this->StepX = ::atof(getFieldFromJson(res_of_fr, "StepX").c_str());
				this->StepY = ::atof(getFieldFromJson(res_of_fr, "StepY").c_str());
				this->StepZ = ::atof(getFieldFromJson(res_of_fr, "StepZ").c_str());

				//количество узлов вдоль каждой из осей
        //Количество узлов вдоль каждой оси, ну если все узлы на ось
        //спроецировать
				//Следует понимать, что в это число узловв мы  вклюичли

				this->N_x = static_cast<int>(  abs(this->xStart - this->xFinish) / this->StepX ) + 1;
				this->N_y = static_cast<int>(  abs(this->yStart - this->yFinish) / this->StepY ) + 1;
				this->N_z = static_cast<int>(  abs(this->zStart - this->zFinish) / this->StepZ ) + 1;

				//Узел начала оси, поэтому общее число узлов:
				this->Number_of_nodes = (this->N_x )*(this->N_y )*(this->N_z );
				this->Number_of_cells = (this->N_x - 1)*(this->N_y - 1)*(this->N_z - 1);



      }/*else*/
		}/*check_bscy*/

		void write_bscy_to_py(){
			boost::property_tree::ptree root;
			root.put("xStart", this->xStart);
			root.put("xFinish", this->xFinish);
			root.put("yStart", this->yStart);
			root.put("yFinish", this->yFinish);
			root.put("zStart", this->zStart);
			root.put("zFinish", this->zFinish);
			root.put("StepX", this->StepX);
			root.put("StepY", this->StepY);
			root.put("StepZ", this->StepZ);
			root.put("N_x", this->N_x);
			root.put("N_y", this->N_y);
			root.put("N_z", this->N_z);
			root.put("Number_of_nodes", this->Number_of_nodes);
			root.put("Number_of_cells", this->Number_of_cells);

			const std::string result = writeJsonToString(root);

			//сделаем файлик для питона
			std::vector<std::string> pyImport;
			pyImport.push_back(result);
			const bool res = reWriteFile((border_step_chyzlov_yacheek + ".py"), pyImport);
		}

		void generate_bscy(){
			std::vector<std::string> bscy_r{checkBSCY};

			for(int i = 0; i < bscy_r.size(); i++){
				if(i == 0){
					continue;
				}/*if*/
				if((i < 7) && (i > 0)){
					bscy_r.at(i) = bscy_r.at(i) + std::to_string(50*i) + ",";
					continue;
				}/*if*/
				if((i > 6) && (i < 10)){
					bscy_r.at(i) = bscy_r.at(i) + std::to_string(5*i) + ",";
					if(i == (bscy_r.size() - 1)){
						bscy_r.at(i).pop_back();//удалили последнюю запятую
					}/*if*/
					continue;
				}/*if*/
				if(i == (bscy_r.size() - 1)){
					bscy_r.at(i).pop_back();//удалили последнюю запятую
					continue;
				}/*if*/
			}/*for*/

			//создаем файл с таким именем
			const bool isGoodRes = reWriteFile(this->border_step_chyzlov_yacheek, bscy_r);
			if(!isGoodRes){
				std::cerr << "ERROR: Failed to write" << std::endl;
			}
		}

		void make_coord(){
			//убедимся , что вектор пустой
			if(c_of_n.size() != 0){
				c_of_n.clear();
			}

			//перебор по x
			for(int x = 0; x < N_x; x++){
				//перебор по y
				for(int y = 0; y < N_y; y++){
					//перебор по z
					for(int z = 0; z < N_z; z++){
						Coord_of_Node cur(x*StepX,y*StepY,z*StepZ);
						c_of_n.push_back(cur);
					}
				}
			}

			if(c_of_nZYX.size() != 0){
				c_of_n.clear();
			}
			//перебор по z
			for(int z = 0; z < N_z; z++){
				//перебор по y
				for(int y = 0; y < N_y; y++){
					//перебор по x
					for(int x = 0; x < N_x; x++){
						Coord_of_Node cur(x*StepX,y*StepY,z*StepZ);
						c_of_nZYX.push_back(cur);
					}
				}
			}

		}

		void write_coord_to_py(){
			boost::property_tree::ptree root;
			boost::property_tree::ptree massivTochek;

			for(int i = 0; i < c_of_n.size(); i++){
				boost::property_tree::ptree subsubroot;
				subsubroot.put("x", c_of_n.at(i).getX());
				subsubroot.put("y", c_of_n.at(i).getY());
				subsubroot.put("z", c_of_n.at(i).getZ());
				massivTochek.push_back(std::make_pair("", subsubroot));
			}

			//Массив
			root.add_child("Coord_of_Nodes", massivTochek);
			//отправка корня для печати джейсона
			const std::string result = writeJsonToString(root);
			//std::cout << result << std::endl;
			//сделаем файлик для питона
			std::vector<std::string> pyImport;
			pyImport.push_back(result);
			const bool res = reWriteFile((std::string("Coord_of_Node") + ".py"), pyImport);

		}

		void read_coord_from_py(){
			/*const std::pair< bool, std::vector<std::string> > my_pair = readFile("resPySdvig");
			std::string res_of_fr;
			for(int i = 0; i < my_pair.second.size(); i++){
				if(i == 0){
					res_of_fr = my_pair.second.at(i);
				}
				else{
					res_of_fr = res_of_fr + " " + my_pair.second.at(i);
				}
			}
			//std::cout << res_of_fr << std::endl;
			std::stringstream jsonEncoded(res_of_fr);

			boost::property_tree::ptree root;
			boost::property_tree::read_json(jsonEncoded, root);
			if(root.empty()){
    		std::cerr <<"!!!!!!!!1" << std::endl;
  		}*/
			//boost::property_tree::ptree &corOF = root.get_child();//begin()->second;
			//boost::property_tree::ptree &corOF = root.get_child("Coord_of_Nodes");
			//corOF.get_value<std::vector>();
			//std::cout << *corOF << std::endl;
			//auto aaa = root.get("Coord_of_Nodes"[0]);
			//std::string res_of_rs = getFieldFromJson(res_of_fr, "Coord_of_Nodes");
			//std::cout << ret << std::endl;
			const std::pair< bool, std::vector<std::string> > my_pair = readFile("p_to_c");
			std::string res_of_fr;
			for(int i = 0; i < my_pair.second.size(); i++){
				if(i == 0){
					res_of_fr = my_pair.second.at(i);
				}
				else{
					res_of_fr = res_of_fr + " " + my_pair.second.at(i);
				}
			}
			//std::cout << res_of_fr << std::endl;
			std::stringstream ss{res_of_fr};
			float temp;
			std::vector <float> vec;
			while(ss >> temp){
				vec.push_back(temp);
			}
			//std::cerr << "ERROR" << std::endl;
			std::vector<Coord_of_Node> c_of_n1;
			for(int i = 0; i < (vec.size()); i++){
				Coord_of_Node cur(vec.at(i),vec.at(i+1),vec.at(i+2));
				i++;
				i++;
				c_of_n1.push_back(cur);
			}
			//std::cerr << "ERROR" << std::endl;
			c_of_n = c_of_n1;
			//std::vector<Coord_of_Node> c_of_nZYX;

		}
	public:
		TriDeSetka(){
			//проверяем существование и содержание наших файлов с параметрами сетки
      //все файлы в формате json
			check_bscy();
			write_bscy_to_py();
			make_coord();
			write_coord_to_py();
			//		std::cerr << "ERROR" << this->c_of_n.size() << std::endl;
			read_coord_from_py();


		}

		const int getNumber_of_Nodes(){
			return Number_of_nodes;
		}
		const std::vector<Coord_of_Node> getC_of_N(){
				return c_of_n;
		}

		const std::vector<Coord_of_Node> getC_of_NZYX(){
				return c_of_nZYX;
		}

		const int getNumber_of_Cells(){
			return Number_of_cells;
		}

		const int getN_x(){
			return N_x;
		}

		const int getN_y(){
			return N_y;
		}

		const int getN_z(){
			return N_z;
		}


};
