#include <iostream>
#include <fstream>
#include <string>

bool openFile(std::fstream &file, std::string name) {
	file.open(name.c_str(), std::ios::in);
	return !file.fail();
}

void showContents(std::fstream &file) {
	std::string line;
	while (file >> line)
		std::cout << line << std::endl;
}

std::string getContents(std::fstream &file) {
	const int rows = 1;
	const int columns = 1;

	std::string data[rows][columns];


	int rowCntr, colCntr;
	std::string temp;
	if(file)
		while (!file.eof) {
			std::getline(file, temp, ',');
			
			data[rowCntr][colCntr] = temp;

			colCntr++;

			if (colCntr == 4) {
				rowCntr++;
				colCntr = 0;
			}
		}
	return "";
}

int main() {
	system("color 0c");
	std::fstream file;
	if (openFile(file, "H:\\iobudget.csv")) {
		showContents(file);
		file.close();
	}

	system("pause");

	return 0;
}