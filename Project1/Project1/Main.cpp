#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

const int rows = 10;
const int columns = 12;
std::string data[rows][columns];

bool openFile(std::fstream &file, std::string name) {
	file.open(name.c_str(), std::ios::in);
	return !file.fail();
}

void showContents(std::fstream &file) {
	std::string line;
	while (file >> line)
		std::cout << line << std::endl;
}

void getContents(std::fstream &file) {
	int rowCntr = 0, colCntr = 0;
	std::string temp;
	if (file)
		while (!file.eof()) {
			std::getline(file, temp, ',');
			temp.erase(std::remove(temp.begin(), temp.end(), '\n'), temp.end());
			data[rowCntr][colCntr] = temp;

			if (colCntr++ == columns-1) {
				rowCntr++;
				colCntr = 0;
			}
		}
}

void printData() {
	std::cout << "\tJan\tFeb\tMar\tApr\tMay\tJun\tJul\tAug\tSep\tOct\tNov\tDec\tDept Totals" << std::endl;
	int rowTotal = 0;
	int colTotal = 0;
	for (int i = 0; i < rows; i++) {
		std::cout << "Dep " << i + 1 << "\t";
		for (int j = 0; j < columns; j++) {
			std::cout << data[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}

int main() {
	system("color 0c");
	std::fstream file;
	if (openFile(file, "C:\\Users\\Daniel\\Desktop\\iobudget.csv")) {
		getContents(file);
		file.close();
	}
	printData();
	system("pause");

	return 0;
}