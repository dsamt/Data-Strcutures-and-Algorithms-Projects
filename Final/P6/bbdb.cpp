#include "bbdb.hpp"

//default constructor that reads in the default csv file (db.csv) and parses each line of data from the csv file
//does so by grabbing each line and extracting the data in between commas
//whenever data is needed for the structure that represents a players statistics that we are looking for it stores that line into the structs category that is relates to
//if the data is not wanted it is just stored in the plain string line that will keep getting written over and once all the data for a given playter on a certain day is stored in the struct it is pushed 
//back to the vector container that holds the struct statistics that represents a players stats
//if the file cannot be read for any reason it throws a runtime error
BBDB::BBDB() {
	std::ifstream file("db.csv");
	std::string line;

	if (!file.good()) {
		throw std::runtime_error("Error opening file");
	}
	else {
		//std::getline(file, line);
		while (std::getline(file, line)) {
			//std::cout << line << std::endl;

			std::getline(file, stat.gmDate, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, stat.playDisplayNm, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			stat.playPTS = std::stoi(line);
			std::getline(file, line, ',');
			stat.playAST = std::stoi(line);
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			stat.playSTL = std::stoi(line);
			std::getline(file, line, ',');
			stat.playBLK = std::stoi(line);
			statVect.push_back(stat);

		}
	}
}

//paramterized constructor that takes in a user defined file as the paramter and parses that file
//does so by grabbing each line and extracting the data in between commas
//whenever data is needed for the structure that represents a players statistics that we are looking for it stores that line into the structs category that it relates to
//if the data is not wanted it is just stored in the plain string line that will keep getting written over and once all the data for a given playter on a certain day is stored in the struct it is pushed 
//back to the vector container that holds the struct statistics that represents a players stats
//if the file cannot be read for any reason it throws a runtime error
BBDB::BBDB(std::string filename) {
	std::ifstream file(filename);
	std::string line;

	if (!file.good()) {
		throw std::runtime_error("Error opening file");
	}
	else {
		//std::getline(file, line);
		while (std::getline(file, line)) {
			//std::cout << line << std::endl;

			std::getline(file, stat.gmDate, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, stat.playDisplayNm, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			std::getline(file, line, ',');
			stat.playPTS = std::stoi(line);
			std::getline(file, line, ','); 
				stat.playAST = std::stoi(line);
			std::getline(file, line, ',');
			std::getline(file, line, ',');
				stat.playSTL = std::stoi(line);
			std::getline(file, line, ',');
				stat.playBLK = std::stoi(line);
			statVect.push_back(stat);

		}
	}
}


//main function that queries over all the data from the file to extract the data requested by the user which is passed into the function as a string parameter
//uses the vector container created from the constructors to go thorugh all the data and find the relevant fields that the user is searching for
std::vector<std::string> BBDB::select(std::string query) const {
	std::vector<std::string> s; //defines a string that will represent each word from the query string
	std::string out; //represents the data that is needed to be outputted and is set later
	int com1, com2, com3, com4; //used for the number comparisons from the query string
	std::vector<std::string> output; //represents all the final data that is stored from the search and stores all the strings out is set to

	//reads the query word by word and stores the words in the s vector
	std::istringstream iss(query);
	std::string word;
	while (iss >> word) {
		s.push_back(word);
	}

	//std::cout << query.length() << std::endl;

	//for a query searching over one category the category is found from the query and the number comparison is stored to be searched for through the vector that stores all the data
	//if the data found in the vector it is put in the string out and then pushed into the output container
	//for more than one category the basic idea for searching is the same so all comments applied in this section aplly through just for more than one category
	if (query.length() == 13 || query.length() == 12) {	//if the query is a certain length it will correspond to a search over a certain amount of categories
		if (((s[0] == "playPTS") || (s[0] == "playAST") || (s[0] == "playSTL") || (s[0] == "playBLK")) && s[1] == ">=") { //if a word is a certain category and the symbol is correct then continue
			com1 = std::stoi(s[2]); //set the number comparison for the category searching for
			if (s[0] == "playPTS") { // if a word is catgeory then compare that category to the number given in the query
				for (int i = 0; i < statVect.size(); i++) { //for a certain category go thorugh the vector and find all times that the comparison is true and return it in the output vector
					if (statVect[i].playPTS >= com1) {
						out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playPTS);
						output.push_back(out);
						//std::cout << statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playPTS) + "," + std::to_string(statVect[i].playAST) + "," + std::to_string(statVect[i].playBLK) + "," + std::to_string(statVect[i].playSTL) << std::endl;
					}
				}
			}
			else if (s[0] == "playAST") {
				for (int i = 0; i < statVect.size(); i++) {
					if (statVect[i].playAST >= com1) {
						out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playAST);
						output.push_back(out);
						//std::cout << statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playAST) << std::endl;
					}
				}
			}
			else if (s[0] == "playBLK") {
				for (int i = 0; i < statVect.size(); i++) {
					if (statVect[i].playBLK >= com1) {
						out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playBLK);
						output.push_back(out);
						//std::cout << statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playBLK) << std::endl;
					}
				}
			}
			else if (s[0] == "playSTL") {
				for (int i = 0; i < statVect.size(); i++) {
					if (statVect[i].playSTL >= com1) {
						out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playSTL);
						output.push_back(out);
						//std::cout << statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playSTL) << std::endl;
					}
				}
			}
		}
	}
		//for a query searching over two categories the category is found from the query and the number comparisons are stored to be searched for through the vector that stores all the data
		//if the data found in the vector it is put in the string out and then pushed into the output container	else 
	if (query.length() == 31 || query.length() == 30 || query.length() == 29) {
		if (s[0] == "playPTS" && s[4] == "playAST" && s[1] == ">=" && s[3] == "AND" && s[5] == ">=") { // for more than one category more than one word is compared to find what is being searched for
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playPTS >= com1 && statVect[i].playAST >= com2) { // search through the vector container for all instances of the comparison asked for
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playPTS) + "," + s[4] + "," + std::to_string(statVect[i].playAST);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playPTS" && s[4] == "playSTL" && s[1] == ">=" && s[3] == "AND" && s[5] == ">=") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playPTS >= com2 && statVect[i].playSTL >= com1) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playPTS) + "," + s[4] + "," + std::to_string(statVect[i].playSTL);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playPTS" && s[4] == "playBLK" && s[1] == ">=" && s[3] == "AND" && s[5] == ">=") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playPTS >= com1 && statVect[i].playBLK >= com2) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playPTS) + "," + s[4] + "," + std::to_string(statVect[i].playBLK);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playAST" && s[4] == "playPTS" && s[1] == ">=" && s[3] == "AND" && s[5] == ">=") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playPTS >= com2 && statVect[i].playAST >= com1) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playAST) + "," + s[4] + "," + std::to_string(statVect[i].playPTS);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playAST" && s[4] == "playSTL" && s[1] == ">=" && s[3] == "AND" && s[5] == ">=") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playAST >= com1 && statVect[i].playSTL >= com2) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playAST) + "," + s[4] + "," + std::to_string(statVect[i].playSTL);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playAST" && s[4] == "playBLK" && s[1] == ">=" && s[3] == "AND" && s[5] == ">=") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playAST >= com1 && statVect[i].playBLK >= com2) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playAST) + "," + s[4] + "," + std::to_string(statVect[i].playBLK);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playSTL" && s[4] == "playPTS" && s[1] == ">=" && s[3] == "AND" && s[5] == ">=") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playSTL >= com1 && statVect[i].playPTS >= com2) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playSTL) + "," + s[4] + "," + std::to_string(statVect[i].playPTS);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playSTL" && s[4] == "playAST" && s[1] == ">=" && s[3] == "AND" && s[5] == ">=") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playSTL >= com1 && statVect[i].playAST >= com2) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playSTL) + "," + s[4] + "," + std::to_string(statVect[i].playAST);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playSTL" && s[4] == "playBLK" && s[1] == ">=" && s[3] == "AND" && s[5] == ">=") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playSTL >= com1 && statVect[i].playBLK >= com2) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playSTL) + "," + s[4] + "," + std::to_string(statVect[i].playBLK);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playBLK" && s[4] == "playPTS" && s[1] == ">=" && s[3] == "AND" && s[5] == ">=") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playBLK >= com1 && statVect[i].playPTS >= com2) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playBLK) + "," + s[4] + "," + std::to_string(statVect[i].playPTS);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playBLK" && s[4] == "playAST" && s[1] == ">=" && s[3] == "AND" && s[5] == ">=") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playBLK >= com1 && statVect[i].playAST >= com2) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playBLK) + "," + s[4] + "," + std::to_string(statVect[i].playAST);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playBLK" && s[4] == "playSTL" && s[1] == ">=" && s[3] == "AND" && s[5] == ">=") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playBLK >= com1 && statVect[i].playSTL >= com2) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playBLK) + "," + s[4] + "," + std::to_string(statVect[i].playSTL);
					output.push_back(out);
				}
			}
		}
	}
	//for a query searching over three categories the category is found from the query and the number comparisons are stored to be searched for through the vector that stores all the data
		//if the data found in the vector it is put in the string out and then pushed into the output container	else
	else if (query.length() == 49 || query.length() == 48 || query.length() == 47 || query.length() == 46) {
		if (s[0] == "playPTS" && s[4] == "playAST" && s[8] == "playSTL" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[3] == "AND" && s[7] == "AND") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);
			com3 = std::stoi(s[10]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playPTS >= com1 && statVect[i].playAST >= com2 && statVect[i].playSTL >= com3) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playPTS) + "," + s[4] + ","
						+ std::to_string(statVect[i].playAST) + "," + s[8] + "," + std::to_string(statVect[i].playSTL);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playPTS" && s[4] == "playAST" && s[8] == "playBLK" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[3] == "AND" && s[7] == "AND") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);
			com3 = std::stoi(s[10]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playPTS >= com1 && statVect[i].playAST >= com2 && statVect[i].playBLK >= com3) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playPTS) + "," + s[4] + ","
						+ std::to_string(statVect[i].playAST) + "," + s[8] + "," + std::to_string(statVect[i].playBLK);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playPTS" && s[4] == "playSTL" && s[8] == "playAST" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[3] == "AND" && s[7] == "AND") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);
			com3 = std::stoi(s[10]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playPTS >= com1 && statVect[i].playSTL >= com2 && statVect[i].playAST >= com3) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playPTS) + "," + s[4] + ","
						+ std::to_string(statVect[i].playSTL) + "," + s[8] + "," + std::to_string(statVect[i].playAST);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playPTS" && s[4] == "playSTL" && s[8] == "playBLK" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[3] == "AND" && s[7] == "AND") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);
			com3 = std::stoi(s[10]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playPTS >= com1 && statVect[i].playSTL >= com2 && statVect[i].playBLK >= com3) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playPTS) + "," + s[4] + ","
						+ std::to_string(statVect[i].playSTL) + "," + s[8] + "," + std::to_string(statVect[i].playBLK);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playPTS" && s[4] == "playBLK" && s[8] == "playAST" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[3] == "AND" && s[7] == "AND") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);
			com3 = std::stoi(s[10]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playPTS >= com1 && statVect[i].playBLK >= com2 && statVect[i].playAST >= com3) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playPTS) + "," + s[4] + ","
						+ std::to_string(statVect[i].playBLK) + "," + s[8] + "," + std::to_string(statVect[i].playAST);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playPTS" && s[4] == "playBLK" && s[8] == "playSTL" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[3] == "AND" && s[7] == "AND") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);
			com3 = std::stoi(s[10]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playPTS >= com1 && statVect[i].playBLK >= com2 && statVect[i].playSTL >= com3) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playPTS) + "," + s[4] + ","
						+ std::to_string(statVect[i].playBLK) + "," + s[8] + "," + std::to_string(statVect[i].playSTL);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playAST" && s[4] == "playPTS" && s[8] == "playSTL" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[3] == "AND" && s[7] == "AND") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);
			com3 = std::stoi(s[10]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playAST >= com1 && statVect[i].playPTS >= com2 && statVect[i].playSTL >= com3) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playAST) + "," + s[4] + ","
						+ std::to_string(statVect[i].playPTS) + "," + s[8] + "," + std::to_string(statVect[i].playSTL);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playAST" && s[4] == "playPTS" && s[8] == "playBLK" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[3] == "AND" && s[7] == "AND") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);
			com3 = std::stoi(s[10]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playAST >= com1 && statVect[i].playPTS >= com2 && statVect[i].playBLK >= com3) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playAST) + "," + s[4] + ","
						+ std::to_string(statVect[i].playPTS) + "," + s[8] + "," + std::to_string(statVect[i].playBLK);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playAST" && s[4] == "playSTL" && s[8] == "playPTS" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[3] == "AND" && s[7] == "AND") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);
			com3 = std::stoi(s[10]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playAST >= com1 && statVect[i].playSTL >= com2 && statVect[i].playPTS >= com3) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playAST) + "," + s[4] + ","
						+ std::to_string(statVect[i].playSTL) + "," + s[8] + "," + std::to_string(statVect[i].playPTS);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playAST" && s[4] == "playSTL" && s[8] == "playBLK" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[3] == "AND" && s[7] == "AND") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);
			com3 = std::stoi(s[10]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playAST >= com1 && statVect[i].playSTL >= com2 && statVect[i].playBLK >= com3) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playAST) + "," + s[4] + ","
						+ std::to_string(statVect[i].playSTL) + "," + s[8] + "," + std::to_string(statVect[i].playBLK);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playAST" && s[4] == "playBLK" && s[8] == "playPTS" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[3] == "AND" && s[7] == "AND") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);
			com3 = std::stoi(s[10]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playAST >= com1 && statVect[i].playBLK >= com2 && statVect[i].playPTS >= com3) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playAST) + "," + s[4] + ","
						+ std::to_string(statVect[i].playBLK) + "," + s[8] + "," + std::to_string(statVect[i].playPTS);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playAST" && s[4] == "playBLK" && s[8] == "playSTL" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[3] == "AND" && s[7] == "AND") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);
			com3 = std::stoi(s[10]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playAST >= com1 && statVect[i].playBLK >= com2 && statVect[i].playSTL >= com3) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playAST) + "," + s[4] + ","
						+ std::to_string(statVect[i].playBLK) + "," + s[8] + "," + std::to_string(statVect[i].playSTL);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playBLK" && s[4] == "playPTS" && s[8] == "playAST" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[3] == "AND" && s[7] == "AND") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);
			com3 = std::stoi(s[10]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playBLK >= com1 && statVect[i].playPTS >= com2 && statVect[i].playAST >= com3) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playBLK) + "," + s[4] + ","
						+ std::to_string(statVect[i].playPTS) + "," + s[8] + "," + std::to_string(statVect[i].playAST);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playBLK" && s[4] == "playPTS" && s[8] == "playSTL" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[3] == "AND" && s[7] == "AND") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);
			com3 = std::stoi(s[10]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playBLK >= com1 && statVect[i].playPTS >= com2 && statVect[i].playSTL >= com3) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playBLK) + "," + s[4] + ","
						+ std::to_string(statVect[i].playPTS) + "," + s[8] + "," + std::to_string(statVect[i].playSTL);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playBLK" && s[4] == "playAST" && s[8] == "playPTS" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[3] == "AND" && s[7] == "AND") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);
			com3 = std::stoi(s[10]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playBLK >= com1 && statVect[i].playAST >= com2 && statVect[i].playPTS >= com3) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playBLK) + "," + s[4] + ","
						+ std::to_string(statVect[i].playAST) + "," + s[8] + "," + std::to_string(statVect[i].playPTS);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playBLK" && s[4] == "playAST" && s[8] == "playSTL" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[3] == "AND" && s[7] == "AND") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);
			com3 = std::stoi(s[10]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playBLK >= com1 && statVect[i].playAST >= com2 && statVect[i].playSTL >= com3) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playBLK) + "," + s[4] + ","
						+ std::to_string(statVect[i].playAST) + "," + s[8] + "," + std::to_string(statVect[i].playSTL);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playBLK" && s[4] == "playSTL" && s[8] == "playPTS" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[3] == "AND" && s[7] == "AND") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);
			com3 = std::stoi(s[10]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playBLK >= com1 && statVect[i].playSTL >= com2 && statVect[i].playPTS >= com3) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playBLK) + "," + s[4] + ","
						+ std::to_string(statVect[i].playSTL) + "," + s[8] + "," + std::to_string(statVect[i].playPTS);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playBLK" && s[4] == "playSTL" && s[8] == "playAST" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[3] == "AND" && s[7] == "AND") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);
			com3 = std::stoi(s[10]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playBLK >= com1 && statVect[i].playSTL >= com2 && statVect[i].playAST >= com3) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playBLK) + "," + s[4] + ","
						+ std::to_string(statVect[i].playSTL) + "," + s[8] + "," + std::to_string(statVect[i].playAST);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playSTL" && s[4] == "playPTS" && s[8] == "playAST" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[3] == "AND" && s[7] == "AND") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);
			com3 = std::stoi(s[10]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playSTL >= com1 && statVect[i].playPTS >= com2 && statVect[i].playAST >= com3) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playSTL) + "," + s[4] + ","
						+ std::to_string(statVect[i].playPTS) + "," + s[8] + "," + std::to_string(statVect[i].playAST);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playSTL" && s[4] == "playPTS" && s[8] == "playBLK" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[3] == "AND" && s[7] == "AND") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);
			com3 = std::stoi(s[10]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playSTL >= com1 && statVect[i].playPTS >= com2 && statVect[i].playBLK >= com3) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playSTL) + "," + s[4] + ","
						+ std::to_string(statVect[i].playPTS) + "," + s[8] + "," + std::to_string(statVect[i].playBLK);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playSTL" && s[4] == "playAST" && s[8] == "playPTS" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[3] == "AND" && s[7] == "AND") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);
			com3 = std::stoi(s[10]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playSTL >= com1 && statVect[i].playAST >= com2 && statVect[i].playPTS >= com3) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playSTL) + "," + s[4] + ","
						+ std::to_string(statVect[i].playAST) + "," + s[8] + "," + std::to_string(statVect[i].playPTS);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playSTL" && s[4] == "playAST" && s[8] == "playBLK" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[3] == "AND" && s[7] == "AND") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);
			com3 = std::stoi(s[10]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playSTL >= com1 && statVect[i].playAST >= com2 && statVect[i].playBLK >= com3) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playSTL) + "," + s[4] + ","
						+ std::to_string(statVect[i].playAST) + "," + s[8] + "," + std::to_string(statVect[i].playBLK);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playSTL" && s[4] == "playBLK" && s[8] == "playPTS" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[3] == "AND" && s[7] == "AND") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);
			com3 = std::stoi(s[10]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playSTL >= com1 && statVect[i].playBLK >= com2 && statVect[i].playPTS >= com3) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playSTL) + "," + s[4] + ","
						+ std::to_string(statVect[i].playBLK) + "," + s[8] + "," + std::to_string(statVect[i].playPTS);
					output.push_back(out);
				}
			}
		}
		else if (s[0] == "playSTL" && s[4] == "playBLK" && s[8] == "playAST" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[3] == "AND" && s[7] == "AND") {
			com1 = std::stoi(s[2]);
			com2 = std::stoi(s[6]);
			com3 = std::stoi(s[10]);

			for (int i = 0; i < statVect.size(); i++) {
				if (statVect[i].playSTL >= com1 && statVect[i].playBLK >= com2 && statVect[i].playAST >= com3) {
					out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playSTL) + "," + s[4] + ","
						+ std::to_string(statVect[i].playBLK) + "," + s[8] + "," + std::to_string(statVect[i].playAST);
					output.push_back(out);
				}
			}
		}
	}
	//for a query searching over four categories the category is found from the query and the number comparisons are stored to be searched for through the vector that stores all the data
		//if the data found in the vector it is put in the string out and then pushed into the output container	else
	else if (query.length() == 67 || query.length() == 66 || query.length() == 65 || query.length() == 64 || query.length() == 63) {
	if (s[0] == "playPTS" && s[4] == "playAST" && s[8] == "playSTL" && s[12] == "playBLK" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[13] == ">=" && s[3] == "AND" && s[7] == "AND" && s[11] == "AND") {
		com1 = std::stoi(s[2]);
		com2 = std::stoi(s[6]);
		com3 = std::stoi(s[10]);
		com4 = std::stoi(s[14]);

		for (int i = 0; i < statVect.size(); i++) {
			if (statVect[i].playPTS >= com1 && statVect[i].playAST >= com2 && statVect[i].playSTL >= com3 && statVect[i].playBLK >= com4) {
				out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playPTS) + "," + s[4] + ","
					+ std::to_string(statVect[i].playAST) + "," + s[8] + "," + std::to_string(statVect[i].playSTL) + "," + s[12] + "," + std::to_string(statVect[i].playBLK);
				output.push_back(out);
			}
		}
	}
	else if (s[0] == "playPTS" && s[4] == "playAST" && s[8] == "playBLK" && s[12] == "playSTL" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[13] == ">=" && s[3] == "AND" && s[7] == "AND" && s[11] == "AND") {
		com1 = std::stoi(s[2]);
		com2 = std::stoi(s[6]);
		com3 = std::stoi(s[10]);
		com4 = std::stoi(s[14]);

		for (int i = 0; i < statVect.size(); i++) {
			if (statVect[i].playPTS >= com1 && statVect[i].playAST >= com2 && statVect[i].playBLK >= com3 && statVect[i].playSTL >= com4) {
				out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playPTS) + "," + s[4] + ","
					+ std::to_string(statVect[i].playAST) + "," + s[8] + "," + std::to_string(statVect[i].playBLK) + "," + s[12] + "," + std::to_string(statVect[i].playSTL);
				output.push_back(out);
			}
		}
	}
	else if (s[0] == "playPTS" && s[4] == "playSTL" && s[8] == "playAST" && s[12] == "playBLK" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[13] == ">=" && s[3] == "AND" && s[7] == "AND" && s[11] == "AND") {
		com1 = std::stoi(s[2]);
		com2 = std::stoi(s[6]);
		com3 = std::stoi(s[10]);
		com4 = std::stoi(s[14]);

		for (int i = 0; i < statVect.size(); i++) {
			if (statVect[i].playPTS >= com1 && statVect[i].playSTL >= com2 && statVect[i].playAST >= com3 && statVect[i].playBLK >= com4) {
				out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playPTS) + "," + s[4] + ","
					+ std::to_string(statVect[i].playSTL) + "," + s[8] + "," + std::to_string(statVect[i].playAST) + "," + s[12] + "," + std::to_string(statVect[i].playBLK);
				output.push_back(out);
			}
		}
	}
	else if (s[0] == "playPTS" && s[4] == "playSTL" && s[8] == "playBLK" && s[12] == "playAST" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[13] == ">=" && s[3] == "AND" && s[7] == "AND" && s[11] == "AND") {
		com1 = std::stoi(s[2]);
		com2 = std::stoi(s[6]);
		com3 = std::stoi(s[10]);
		com4 = std::stoi(s[14]);

		for (int i = 0; i < statVect.size(); i++) {
			if (statVect[i].playPTS >= com1 && statVect[i].playSTL >= com2 && statVect[i].playBLK >= com3 && statVect[i].playAST >= com4) {
				out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playPTS) + "," + s[4] + ","
					+ std::to_string(statVect[i].playSTL) + "," + s[8] + "," + std::to_string(statVect[i].playBLK) + "," + s[12] + "," + std::to_string(statVect[i].playAST);
				output.push_back(out);
			}
		}
	}
	else if (s[0] == "playPTS" && s[4] == "playBLK" && s[8] == "playAST" && s[12] == "playSTL" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[13] == ">=" && s[3] == "AND" && s[7] == "AND" && s[11] == "AND") {
		com1 = std::stoi(s[2]);
		com2 = std::stoi(s[6]);
		com3 = std::stoi(s[10]);
		com4 = std::stoi(s[14]);

		for (int i = 0; i < statVect.size(); i++) {
			if (statVect[i].playPTS >= com1 && statVect[i].playBLK >= com2 && statVect[i].playAST >= com3 && statVect[i].playSTL >= com4) {
				out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playPTS) + "," + s[4] + ","
					+ std::to_string(statVect[i].playBLK) + "," + s[8] + "," + std::to_string(statVect[i].playAST) + "," + s[12] + "," + std::to_string(statVect[i].playSTL);
				output.push_back(out);
			}
		}
	}
	else if (s[0] == "playPTS" && s[4] == "playBLK" && s[8] == "playSTL" && s[12] == "playAST" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[13] == ">=" && s[3] == "AND" && s[7] == "AND" && s[11] == "AND") {
		com1 = std::stoi(s[2]);
		com2 = std::stoi(s[6]);
		com3 = std::stoi(s[10]);
		com4 = std::stoi(s[14]);

		for (int i = 0; i < statVect.size(); i++) {
			if (statVect[i].playPTS >= com1 && statVect[i].playBLK >= com2 && statVect[i].playSTL >= com3 && statVect[i].playAST >= com4) {
				out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playPTS) + "," + s[4] + ","
					+ std::to_string(statVect[i].playBLK) + "," + s[8] + "," + std::to_string(statVect[i].playSTL) + "," + s[12] + "," + std::to_string(statVect[i].playAST);
				output.push_back(out);
			}
		}
	}
	else if (s[0] == "playAST" && s[4] == "playPTS" && s[8] == "playSTL" && s[12] == "playBLK" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[13] == ">=" && s[3] == "AND" && s[7] == "AND" && s[11] == "AND") {
		com1 = std::stoi(s[2]);
		com2 = std::stoi(s[6]);
		com3 = std::stoi(s[10]);
		com4 = std::stoi(s[14]);

		for (int i = 0; i < statVect.size(); i++) {
			if (statVect[i].playAST >= com1 && statVect[i].playPTS >= com2 && statVect[i].playSTL >= com3 && statVect[i].playBLK >= com4) {
				out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playAST) + "," + s[4] + ","
					+ std::to_string(statVect[i].playPTS) + "," + s[8] + "," + std::to_string(statVect[i].playSTL) + "," + s[12] + "," + std::to_string(statVect[i].playBLK);
				output.push_back(out);
			}
		}
	}
	else if (s[0] == "playAST" && s[4] == "playPTS" && s[8] == "playBLK" && s[12] == "playSTL" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[13] == ">=" && s[3] == "AND" && s[7] == "AND" && s[11] == "AND") {
		com1 = std::stoi(s[2]);
		com2 = std::stoi(s[6]);
		com3 = std::stoi(s[10]);
		com4 = std::stoi(s[14]);

		for (int i = 0; i < statVect.size(); i++) {
			if (statVect[i].playAST >= com1 && statVect[i].playPTS >= com2 && statVect[i].playBLK >= com3 && statVect[i].playSTL >= com4) {
				out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playAST) + "," + s[4] + ","
					+ std::to_string(statVect[i].playPTS) + "," + s[8] + "," + std::to_string(statVect[i].playBLK) + "," + s[12] + "," + std::to_string(statVect[i].playSTL);
				output.push_back(out);
			}
		}
	}
	else if (s[0] == "playAST" && s[4] == "playSTL" && s[8] == "playPTS" && s[12] == "playBLK" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[13] == ">=" && s[3] == "AND" && s[7] == "AND" && s[11] == "AND") {
	com1 = std::stoi(s[2]);
	com2 = std::stoi(s[6]);
	com3 = std::stoi(s[10]);
	com4 = std::stoi(s[14]);

	for (int i = 0; i < statVect.size(); i++) {
		if (statVect[i].playAST >= com1 && statVect[i].playSTL >= com2 && statVect[i].playPTS >= com3 && statVect[i].playBLK >= com4) {
			out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playAST) + "," + s[4] + ","
				+ std::to_string(statVect[i].playSTL) + "," + s[8] + "," + std::to_string(statVect[i].playPTS) + "," + s[12] + "," + std::to_string(statVect[i].playBLK);
			output.push_back(out);
		}
	}
	}
	else if (s[0] == "playAST" && s[4] == "playSTL" && s[8] == "playBLK" && s[12] == "playPTS" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[13] == ">=" && s[3] == "AND" && s[7] == "AND" && s[11] == "AND") {
	com1 = std::stoi(s[2]);
	com2 = std::stoi(s[6]);
	com3 = std::stoi(s[10]);
	com4 = std::stoi(s[14]);

	for (int i = 0; i < statVect.size(); i++) {
		if (statVect[i].playAST >= com1 && statVect[i].playSTL >= com2 && statVect[i].playBLK >= com3 && statVect[i].playPTS >= com4) {
			out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playAST) + "," + s[4] + ","
				+ std::to_string(statVect[i].playSTL) + "," + s[8] + "," + std::to_string(statVect[i].playBLK) + "," + s[12] + "," + std::to_string(statVect[i].playPTS);
			output.push_back(out);
		}
	}
	}
	else if (s[0] == "playAST" && s[4] == "playBLK" && s[8] == "playPTS" && s[12] == "playSTL" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[13] == ">=" && s[3] == "AND" && s[7] == "AND" && s[11] == "AND") {
	com1 = std::stoi(s[2]);
	com2 = std::stoi(s[6]);
	com3 = std::stoi(s[10]);
	com4 = std::stoi(s[14]);

	for (int i = 0; i < statVect.size(); i++) {
		if (statVect[i].playAST >= com1 && statVect[i].playBLK >= com2 && statVect[i].playPTS >= com3 && statVect[i].playSTL >= com4) {
			out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playAST) + "," + s[4] + ","
				+ std::to_string(statVect[i].playBLK) + "," + s[8] + "," + std::to_string(statVect[i].playPTS) + "," + s[12] + "," + std::to_string(statVect[i].playSTL);
			output.push_back(out);
		}
	}
	}
	else if (s[0] == "playAST" && s[4] == "playBLK" && s[8] == "playSTL" && s[12] == "playPTS" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[13] == ">=" && s[3] == "AND" && s[7] == "AND" && s[11] == "AND") {
	com1 = std::stoi(s[2]);
	com2 = std::stoi(s[6]);
	com3 = std::stoi(s[10]);
	com4 = std::stoi(s[14]);

	for (int i = 0; i < statVect.size(); i++) {
		if (statVect[i].playAST >= com1 && statVect[i].playBLK >= com2 && statVect[i].playSTL >= com3 && statVect[i].playPTS >= com4) {
			out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playAST) + "," + s[4] + ","
				+ std::to_string(statVect[i].playBLK) + "," + s[8] + "," + std::to_string(statVect[i].playSTL) + "," + s[12] + "," + std::to_string(statVect[i].playPTS);
			output.push_back(out);
		}
	}
	}
	else if (s[0] == "playSTL" && s[4] == "playPTS" && s[8] == "playAST" && s[12] == "playBLK" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[13] == ">=" && s[3] == "AND" && s[7] == "AND" && s[11] == "AND") {
	com1 = std::stoi(s[2]);
	com2 = std::stoi(s[6]);
	com3 = std::stoi(s[10]);
	com4 = std::stoi(s[14]);

	for (int i = 0; i < statVect.size(); i++) {
		if (statVect[i].playSTL >= com1 && statVect[i].playPTS >= com2 && statVect[i].playAST >= com3 && statVect[i].playBLK >= com4) {
			out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playSTL) + "," + s[4] + ","
				+ std::to_string(statVect[i].playPTS) + "," + s[8] + "," + std::to_string(statVect[i].playAST) + "," + s[12] + "," + std::to_string(statVect[i].playBLK);
			output.push_back(out);
		}
	}
	}
	else if (s[0] == "playSTL" && s[4] == "playPTS" && s[8] == "playBLK" && s[12] == "playAST" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[13] == ">=" && s[3] == "AND" && s[7] == "AND" && s[11] == "AND") {
	com1 = std::stoi(s[2]);
	com2 = std::stoi(s[6]);
	com3 = std::stoi(s[10]);
	com4 = std::stoi(s[14]);

	for (int i = 0; i < statVect.size(); i++) {
		if (statVect[i].playSTL >= com1 && statVect[i].playPTS >= com2 && statVect[i].playBLK >= com3 && statVect[i].playAST >= com4) {
			out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playSTL) + "," + s[4] + ","
				+ std::to_string(statVect[i].playPTS) + "," + s[8] + "," + std::to_string(statVect[i].playBLK) + "," + s[12] + "," + std::to_string(statVect[i].playAST);
			output.push_back(out);
		}
	}
	}
	else if (s[0] == "playSTL" && s[4] == "playAST" && s[8] == "playPTS" && s[12] == "playBLK" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[13] == ">=" && s[3] == "AND" && s[7] == "AND" && s[11] == "AND") {
	com1 = std::stoi(s[2]);
	com2 = std::stoi(s[6]);
	com3 = std::stoi(s[10]);
	com4 = std::stoi(s[14]);

	for (int i = 0; i < statVect.size(); i++) {
		if (statVect[i].playSTL >= com1 && statVect[i].playAST >= com2 && statVect[i].playPTS >= com3 && statVect[i].playBLK >= com4) {
			out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playSTL) + "," + s[4] + ","
				+ std::to_string(statVect[i].playAST) + "," + s[8] + "," + std::to_string(statVect[i].playPTS) + "," + s[12] + "," + std::to_string(statVect[i].playBLK);
			output.push_back(out);
		}
	}
	}
	else if (s[0] == "playSTL" && s[4] == "playAST" && s[8] == "playBLK" && s[12] == "playPTS" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[13] == ">=" && s[3] == "AND" && s[7] == "AND" && s[11] == "AND") {
	com1 = std::stoi(s[2]);
	com2 = std::stoi(s[6]);
	com3 = std::stoi(s[10]);
	com4 = std::stoi(s[14]);

	for (int i = 0; i < statVect.size(); i++) {
		if (statVect[i].playSTL >= com1 && statVect[i].playAST >= com2 && statVect[i].playBLK >= com3 && statVect[i].playPTS >= com4) {
			out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playSTL) + "," + s[4] + ","
				+ std::to_string(statVect[i].playAST) + "," + s[8] + "," + std::to_string(statVect[i].playBLK) + "," + s[12] + "," + std::to_string(statVect[i].playPTS);
			output.push_back(out);
		}
	}
	}
	else if (s[0] == "playSTL" && s[4] == "playBLK" && s[8] == "playPTS" && s[12] == "playAST" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[13] == ">=" && s[3] == "AND" && s[7] == "AND" && s[11] == "AND") {
	com1 = std::stoi(s[2]);
	com2 = std::stoi(s[6]);
	com3 = std::stoi(s[10]);
	com4 = std::stoi(s[14]);

	for (int i = 0; i < statVect.size(); i++) {
		if (statVect[i].playSTL >= com1 && statVect[i].playBLK >= com2 && statVect[i].playPTS >= com3 && statVect[i].playAST >= com4) {
			out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playSTL) + "," + s[4] + ","
				+ std::to_string(statVect[i].playBLK) + "," + s[8] + "," + std::to_string(statVect[i].playPTS) + "," + s[12] + "," + std::to_string(statVect[i].playAST);
			output.push_back(out);
		}
	}
	}
	else if (s[0] == "playSTL" && s[4] == "playBLK" && s[8] == "playAST" && s[12] == "playPTS" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[13] == ">=" && s[3] == "AND" && s[7] == "AND" && s[11] == "AND") {
	com1 = std::stoi(s[2]);
	com2 = std::stoi(s[6]);
	com3 = std::stoi(s[10]);
	com4 = std::stoi(s[14]);

	for (int i = 0; i < statVect.size(); i++) {
		if (statVect[i].playSTL >= com1 && statVect[i].playBLK >= com2 && statVect[i].playAST >= com3 && statVect[i].playPTS >= com4) {
			out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playSTL) + "," + s[4] + ","
				+ std::to_string(statVect[i].playBLK) + "," + s[8] + "," + std::to_string(statVect[i].playAST) + "," + s[12] + "," + std::to_string(statVect[i].playPTS);
			output.push_back(out);
		}
	}
	}
	else if (s[0] == "playBLK" && s[4] == "playPTS" && s[8] == "playAST" && s[12] == "playSTL" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[13] == ">=" && s[3] == "AND" && s[7] == "AND" && s[11] == "AND") {
	com1 = std::stoi(s[2]);
	com2 = std::stoi(s[6]);
	com3 = std::stoi(s[10]);
	com4 = std::stoi(s[14]);

	for (int i = 0; i < statVect.size(); i++) {
		if (statVect[i].playBLK >= com1 && statVect[i].playPTS >= com2 && statVect[i].playAST >= com3 && statVect[i].playSTL >= com4) {
			out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playBLK) + "," + s[4] + ","
				+ std::to_string(statVect[i].playPTS) + "," + s[8] + "," + std::to_string(statVect[i].playAST) + "," + s[12] + "," + std::to_string(statVect[i].playSTL);
			output.push_back(out);
		}
	}
	}
	else if (s[0] == "playBLK" && s[4] == "playPTS" && s[8] == "playSTL" && s[12] == "playAST" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[13] == ">=" && s[3] == "AND" && s[7] == "AND" && s[11] == "AND") {
	com1 = std::stoi(s[2]);
	com2 = std::stoi(s[6]);
	com3 = std::stoi(s[10]);
	com4 = std::stoi(s[14]);

	for (int i = 0; i < statVect.size(); i++) {
		if (statVect[i].playBLK >= com1 && statVect[i].playPTS >= com2 && statVect[i].playSTL >= com3 && statVect[i].playAST >= com4) {
			out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playBLK) + "," + s[4] + ","
				+ std::to_string(statVect[i].playPTS) + "," + s[8] + "," + std::to_string(statVect[i].playSTL) + "," + s[12] + "," + std::to_string(statVect[i].playAST);
			output.push_back(out);
		}
	}
	}
	else if (s[0] == "playBLK" && s[4] == "playAST" && s[8] == "playPTS" && s[12] == "playSTL" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[13] == ">=" && s[3] == "AND" && s[7] == "AND" && s[11] == "AND") {
	com1 = std::stoi(s[2]);
	com2 = std::stoi(s[6]);
	com3 = std::stoi(s[10]);
	com4 = std::stoi(s[14]);

	for (int i = 0; i < statVect.size(); i++) {
		if (statVect[i].playBLK >= com1 && statVect[i].playAST >= com2 && statVect[i].playPTS >= com3 && statVect[i].playSTL >= com4) {
			out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playBLK) + "," + s[4] + ","
				+ std::to_string(statVect[i].playAST) + "," + s[8] + "," + std::to_string(statVect[i].playPTS) + "," + s[12] + "," + std::to_string(statVect[i].playSTL);
			output.push_back(out);
		}
	}
	}
	else if (s[0] == "playBLK" && s[4] == "playAST" && s[8] == "playSTL" && s[12] == "playPTS" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[13] == ">=" && s[3] == "AND" && s[7] == "AND" && s[11] == "AND") {
	com1 = std::stoi(s[2]);
	com2 = std::stoi(s[6]);
	com3 = std::stoi(s[10]);
	com4 = std::stoi(s[14]);

	for (int i = 0; i < statVect.size(); i++) {
		if (statVect[i].playBLK >= com1 && statVect[i].playAST >= com2 && statVect[i].playSTL >= com3 && statVect[i].playPTS >= com4) {
			out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playBLK) + "," + s[4] + ","
				+ std::to_string(statVect[i].playAST) + "," + s[8] + "," + std::to_string(statVect[i].playSTL) + "," + s[12] + "," + std::to_string(statVect[i].playPTS);
			output.push_back(out);
		}
	}
	}
	else if (s[0] == "playBLK" && s[4] == "playSTL" && s[8] == "playPTS" && s[12] == "playAST" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[13] == ">=" && s[3] == "AND" && s[7] == "AND" && s[11] == "AND") {
	com1 = std::stoi(s[2]);
	com2 = std::stoi(s[6]);
	com3 = std::stoi(s[10]);
	com4 = std::stoi(s[14]);

	for (int i = 0; i < statVect.size(); i++) {
		if (statVect[i].playBLK >= com1 && statVect[i].playSTL >= com2 && statVect[i].playPTS >= com3 && statVect[i].playAST >= com4) {
			out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playBLK) + "," + s[4] + ","
				+ std::to_string(statVect[i].playSTL) + "," + s[8] + "," + std::to_string(statVect[i].playPTS) + "," + s[12] + "," + std::to_string(statVect[i].playAST);
			output.push_back(out);
		}
	}
	}
	else if (s[0] == "playBLK" && s[4] == "playSTL" && s[8] == "playAST" && s[12] == "playPTS" && s[1] == ">=" && s[5] == ">=" && s[9] == ">=" && s[13] == ">=" && s[3] == "AND" && s[7] == "AND" && s[11] == "AND") {
	com1 = std::stoi(s[2]);
	com2 = std::stoi(s[6]);
	com3 = std::stoi(s[10]);
	com4 = std::stoi(s[14]);

	for (int i = 0; i < statVect.size(); i++) {
		if (statVect[i].playBLK >= com1 && statVect[i].playSTL >= com2 && statVect[i].playAST >= com3 && statVect[i].playPTS >= com4) {
			out = statVect[i].gmDate + "," + statVect[i].playDisplayNm + "," + s[0] + "," + std::to_string(statVect[i].playBLK) + "," + s[4] + ","
				+ std::to_string(statVect[i].playSTL) + "," + s[8] + "," + std::to_string(statVect[i].playAST) + "," + s[12] + "," + std::to_string(statVect[i].playPTS);
			output.push_back(out);
		}
	}
	}
}


	return output;

}

	



