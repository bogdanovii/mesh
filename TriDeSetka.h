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

		void check_bscy(){//порверка файла границу, шага\, чисоа ячеек

			// Пока есть данные, которые мы можем прочитать,
			//const bool res{analiz_faula_border_step_chyzlov_yacheek("border_step_chyzlov_yacheek")}
      //
      const std::pair< bool, std::vector<std::string> > my_pair = readFile(this->border_step_chyzlov_yacheek);
      if(my_pair.first == false){
        std::cerr << "Не удалось открыть файл c границами и шагами!" << std::endl;
        std::cerr << "Для данный файл с образцовыми данными будет сгенерирован автоматически." << std::endl;
        // в будущем добавить проверку на то что файл существует в папке, но просто занят другим процессом

        //наш файл в формате json будет выглядеть:
        /*
        {
          "xStart": 25.4,
          "xFinich": 35.4
        }
        */

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
						bscy_r.at(i) = bscy_r.at(i) + std::to_string(10*i) + ",";
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

				//сделаем файлик для питона
				std::vector<std::string> pyImport;
				pyImport.push_back("xStart = " + std::to_string(this->xStart));
				const bool res = reWriteFile((border_step_chyzlov_yacheek + ".py"), pyImport);
				boost::property_tree::ptree root;
				// Once our ptree was constructed, we can generate JSON on standard output
				//boost::property_tree::write_json(std::cout, root);
				root.put<int>("xStart", 10);
				//https://stackoverflow.com/questions/2855741/why-does-boost-property-tree-write-json-save-everything-as-string-is-it-possibl
				std::ostringstream oss;
				boost::property_tree::write_json(oss, root);
				std::cout << oss.str() << std::endl;

      }/*else*/


			//const bool res{analiz_faula_border_step_chyzlov_yacheek("ttt")};


		}/*check_bscy*/


	public:
		TriDeSetka(){
			//проверяем существование и содержание наших файлов с параметрами сетки
      //все файлы в формате json
			check_bscy();




		}


};
