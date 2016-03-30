/*
Daniel Church
CSCI_113_01
C++ IO Assignment
 */

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>
#include<iomanip>

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
	std::cout << "\tJan\tFeb\tMar\tApr\tMay\tJun\tJul\tAug\tSep\tOct\tNov\tDec\tTotals" << std::endl;
	
	int total = 0;
	for (int i = 0; i < rows; i++) {
		std::cout << "Dep " << i + 1 << "\t";
		int colTotal = 0;
		for (int j = 0; j < columns; j++) {
			colTotal += stoi(data[i][j]);
			std::cout << data[i][j] << "\t";
		}
		total += colTotal;
		std::cout << colTotal << std::endl;
	}

	std::cout << "Total" << "\t";
	for (int j = 0; j < columns; j++) {
		int rowTotal = 0;
		for (int i = 0; i < rows; i++) 
			rowTotal += stoi(data[i][j]);
		std::cout << rowTotal << "\t";
	}

	std::cout << total << std::endl;
}

void writeLog(int col, int row, int value) {
	std::fstream logFile;
	logFile.open("io_change.txt", std::ios::out|std::ios::app);
	if (!logFile.fail()) {
		time_t t = time(0);
		struct tm now;
		localtime_s(&now, &t);
		logFile << "Column " << col << ", Row " << row << " was changed to " << value << " at " << now.tm_hour << ":" << now.tm_min << ":" << now.tm_sec << " on " << now.tm_mon+1 << "/" << now.tm_mday << "/" << now.tm_year + 1900 <<  std::endl;
		logFile.close();
	}
}

void writeLog(std::string message) {
	std::fstream logFile;
	logFile.open("io_change.txt", std::ios::out | std::ios::app);
	if (!logFile.fail()) {
		logFile << message << std::endl;
		logFile.close();
	}
}

void editData() {
	int col = 0;
	int row = 0;
	int value = 0;
	std::cout << "Enter the column of the cell to edit" << std::endl;
	std::cin >> col;
	if (col >= columns) {
		std::cout << "That column doesn't exist, please enter a valid column." << std::endl;
		return;
	}
	std::cout << "Enter the row of the cell to edit" << std::endl;
	std::cin >> row;
	if (row >= rows) {
		std::cout << "That row doesn't exist, please enter a valid row." << std::endl;
		return;
	}
	std::cout << "Enter the new value for the cell" << std::endl;
	std::cin >> value;
	data[row][col] = std::to_string(value);
	writeLog(col, row, value);
}

void writeFormattedText(std::fstream &file, std::string fileName) {
	file.open(fileName.c_str(), std::ios::out);
	if (!file.fail()) {
		file << std::fixed;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++)
				file << std::setw(8) << data[i][j];
			file << std::endl;
		}
		file.close();
	}
	writeLog("Saved as txt.");
}

void writeCSV(std::fstream &file, std::string fileName) {
	file.open(fileName.c_str(), std::ios::out);
	if (!file.fail()) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++)
				file << data[i][j] << ",";
			file << "\n";
		}
		file.close();
	}
	writeLog("Saved as CSV.");
}

void showLog(std::fstream& file) {
	file.open("io_change.txt", std::ios::in);
	std::string buffer = "";
	if (!file.fail()) {
		for (std::string line; std::getline(file, line); )
			std::cout << line << std::endl;
		file.close();
	}
}

void menu(std::fstream& file) {
	int choice = 0;
	while (true) {
		std::cout << "Enter:\n1. View the CSV\n2. Edit the CSV\n3. Save Formatted Text\n4. Save CSV\n5. View Log\n6. Quit" << std::endl;
		std::cin >> choice;
		switch (choice) {
			case 1: printData(); break;
			case 2: editData(); break;
			case 3: writeFormattedText(file, "out.txt"); break;
			case 4: writeCSV(file, "out_csv.csv"); break;
			case 5: showLog(file); break;
			case 6: return;
		}
	}
}

int main() {
	system("color 0c");
	std::fstream file;
	if (openFile(file, "iobudget.csv")) {
		getContents(file);
		file.close();
	}
	menu(file);
	return 0;
}