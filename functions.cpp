#include "functions.h"

//GLOBALIOS FUNKCIJOS
//
void menu(int& choiceMenu) {
	int choices = 10;

	do {
		cout << "\nMENIU\n";
		cout << "\n--------\n";
		cout << "Pasirinkite programos eiga\n"
			<< "\n1 - Viskas ranka,\n2 - Randomizuoti nd. pazymiai ir egz. balas,\n3 - Viskas randomizuota,"
			<< "\n4 - Baigti darba (Ir isvesti galutinius rezultatus),\n5 - Skaityti visus duomenis is failo,\n6 - Generuoti randomizuotu studentu duomenu failus,"
			<< "\n7 - Vykdyti spartos analize su std::vector (deprecated)," << "\n8 - Vykdyti spartos analize tarp skirtingu STL konteineriu,"
			<< "\n9 - Perziureti Vector klases veikima, naudojant std::vector funkciju pavyzdzius,"
			<< "\n10 - Vykdyti spartos palyginima tarp std::vector ir Vector.";
		cout << "\n--------\n";

		choiceMenu = integer_input_validation(1, choices);

		system("cls");

	} while (choiceMenu < 1 || choiceMenu > choices);
}

int integer_input_validation(int lowEnd, int highEnd, std::string optionalPrompt) { //if highEnd = -1, no highEnd used
	std::string input;

	while (true) {
		try {
			cout << optionalPrompt;
			getline(cin, input);

			if (input.empty()) {
				throw std::runtime_error("\n---KLAIDA: Ivestis tuscia---\n");
			}

			bool isNumber = true;
			for (auto i : input) {
				if (!isdigit(i)) {
					isNumber = false;
					break;
				}
			}

			if (!isNumber) {
				throw std::runtime_error("\n---KLAIDA: Iveskite realuji skaiciu---\n");
			}

			//string to int
			int choice = stoi(input);

			//if cout of range
			if (choice < lowEnd || (choice > highEnd && highEnd != -1)) {
				std::string errorMsg = "\n---KLAIDA: Iveskite realuji skaiciu";
				if (highEnd != -1) {
					errorMsg += " nuo " + std::to_string(lowEnd) + " iki " + std::to_string(highEnd) + "---\n";
				}
				else {
					errorMsg += " nuo " + std::to_string(lowEnd) + "---\n";
				}
				throw std::out_of_range(errorMsg);
			}

			//valid input
			return choice;
		}
		catch (const std::exception& e) {
			std::cerr << e.what();
		}
	}
}

std::string string_input_validation(std::string optionalPrompt) {
	std::string input;

	while (true) {
		try {
			cout << optionalPrompt;
			getline(cin, input);

			if (input.empty()) {
				throw std::runtime_error("\n---KLAIDA: Ivestis tuscia---\n");
			}

			//check if string valid
			bool isLetter = true;
			for (auto i : input) {
				if (!isalpha(i) || i == ' ') {
					isLetter = false;

					break; //if any not letter, stop checking
				}
			}

			if (isLetter == false) {
				throw std::runtime_error("\n---KLAIDA: Iveskite tik raides---\n");
			}
			//valid input
			return input;
		}
		catch (const std::exception& e) {
			std::cerr << e.what();
		}
	}
}

//Generuoti faila su randomizuotais studentu duomenimis
void student_file_generator(int nStud, int nPaz) {

	//create file name automatically
	std::string filename = "studentai";
	std::string fileend = ".txt";
	std::string nStudents = std::to_string(nStud);

	filename.append(nStudents);
	filename.append(fileend);

	std::ofstream fout(filename);

	//file header
	std::string nd = "ND";

	fout << std::setw(24) << std::left << "Vardas" << std::setw(27) << std::left << "Pavarde";

	for (int i = 0; i < nPaz; i++) {
		fout << std::setw(10) << std::left << nd.append(std::to_string(i + 1));
		nd = "ND";
	}
	fout << std::left << "Egz.\n";

	//file entries (stud data)
	int pazRnd;

	for (int i = 0; i < nStud; i++) {

		if (i != 0) fout << '\n';

		std::string studVar = "Vardas";
		std::string studPav = "Pavarde";

		//name
		fout << std::setw(24) << std::left << studVar.append(std::to_string(i + 1));
		//last name
		fout << std::setw(27) << std::left << studPav.append(std::to_string(i + 1));

		//paz
		for (int i = 0; i < nPaz; i++) {
			pazRnd = rand() % 10 + 1;
			fout << std::right << pazRnd << std::setw(10);
		}

		//egz balas
		pazRnd = rand() % 10 + 1;
		fout << std::right << pazRnd;
	}

	fout.close();
}