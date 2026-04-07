//function implementations file

#include "functions.h"

//GLOBALIOS FUNKCIJOS
//
void menu(int& choiceMenu) {
	int choices = 8;

	do {
		cout << "\nMENIU\n";
		cout << "\n--------\n";
		cout << "Pasirinkite programos eiga\n"
			<< "\n1 - Viskas ranka,\n2 - Randomizuoti nd. pazymiai ir egz. balas,\n3 - Viskas randomizuota,"
			<< "\n4 - Baigti darba (Ir isvesti galutinius rezultatus),\n5 - Skaityti visus duomenis is failo,\n6 - Generuoti randomizuotu studentu duomenu failus,"
			<< "\n7 - Vykdyti spartos analize su std::vector." << "\n8 - Vykdyti spartos analize tarp skirtingu STL konteineriu";
		cout << "\n--------\n";

		number_input_validation(choiceMenu, 1, choices);

		system("cls");

	} while (choiceMenu < 1 || choiceMenu > choices);
}

void number_input_validation(int& choice, int lowEnd, int highEnd, std::string optionalPrompt) { //if highEnd = -1, no highEnd used
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
			choice = stoi(input);

			//check range
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
			break;
		}
		catch (const std::exception& e) {
			std::cerr << e.what();
		}
	}
}

void string_input_validation(std::string& input, std::string optionalPrompt) {
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
			break;
		}
		catch (const std::exception& e) {
			std::cerr << e.what();
		}
	}
}

//Studentu vektoriaus rusiavimas pagal pasirinkima
void student_sort(std::vector<Studentas>& studentai) {
	int choiceSort;
	do {
		number_input_validation(choiceSort, 1, 4, "\nKaip norite surusiuoti studentus? \n1 - Pagal vardus,\n2 - Pagal pavardes,\n3 - Pagal galutini (vid.),\n4- Pagal galutini (med.)\n");

	} while (choiceSort < 1 || choiceSort > 4);

	sort(studentai.begin(), studentai.end(),
		[choiceSort](const Studentas& a, const Studentas& b) -> bool {
			if (choiceSort == 1) {
				if (a.vardas != b.vardas) return a.vardas < b.vardas;
			}
			else if (choiceSort == 2) {
				if (a.pav != b.pav) return a.pav < b.pav;
			}
			else if (choiceSort == 3) {
				return a.galutinisVid > b.galutinisVid;
			}
			else {
				return a.galutinisMed > b.galutinisMed;
			}
		});
}

void calculate_galutinis() {
	return;
}

//DARBAS SU EKRANU
// 
//Vardo, pavardes ivestis
void Studentas::varpav_input()
{
	string_input_validation(vardas, "Iveskite studento varda:\nVardas: ");

	string_input_validation(pav, "Iveskite studento pavarde:\nPavarde: ");
	cout << "\n";
}

//Nd pazymiu ivestis
void Studentas::paz_input(int& suma)
{
	cout << "Iveskite studento pazymius:\n";

	int tempPaz;
	int choiceEndPaz = 0;

	do {
		number_input_validation(tempPaz, 1, 10, "Pazymys:\n");

		suma += tempPaz;
		paz.push_back(tempPaz);

		do {
			number_input_validation(choiceEndPaz, 0, 1, "\nAr vesite dar viena pazymi? (0 - Taip, 1 - Ne, eikime prie kito studento):\n");

		} while (choiceEndPaz < 0 || choiceEndPaz > 1);
	} while (choiceEndPaz != 1);
}

//Egzamino balo ivestis
void Studentas::egz_input()
{

	number_input_validation(egzaminas, 1, 10, "Iveskite studento egzamino bala:\n");
}

//Randomizuoti nd pazymiai
void Studentas::rand_paz(int& suma)
{
	int pazSk;
	do {
		number_input_validation(pazSk, 1, -1, "Iveskite norima namu darbu pazymiu skaiciu:\n");

	} while (pazSk < 1);

	for (int i = 0; i < pazSk; i++) {
		int tempPazRnd = rand() % 10 + 1;
		paz.push_back(tempPazRnd);

		suma += tempPazRnd;
	}

	cout << "Ivesti pazymiai:\n{ ";
	for (int i = 0; i < pazSk; i++) {
		cout << paz[i] << " ";
	}
	cout << "}";
}

//Randomizuotas egzamino balas
void Studentas::rand_egz()
{
	int tempEgzPazRnd = rand() % 10 + 1;
	egzaminas = tempEgzPazRnd;
	cout << "Ivestas egzamino balas:\n";
	cout << "{ " << tempEgzPazRnd << " }\n";
}

//Randomizuotas vardas ir pavarde
void Studentas::rand_varpav()
{
	switch (rand() % 14) {
	case 0: vardas = "Irma"; break;
	case 1: vardas = "Alma"; break;
	case 2: vardas = "Irena"; break;
	case 3: vardas = "Egle"; break;
	case 4: vardas = "Jolanta"; break;
	case 5: vardas = "Petras"; break;
	case 6: vardas = "Jonas"; break;
	case 7: vardas = "Ignas"; break;
	case 8: vardas = "Darius"; break;
	case 9: vardas = "Simas"; break;
	case 10: vardas = "Aistis"; break;
	case 11: vardas = "Aurimas"; break;
	case 12: vardas = "Kotryna"; break;
	case 13: vardas = "Bertolomiejus"; break;
	case 14: vardas = "Augustinas"; break;
	}
	switch (*vardas.rbegin()) {
	case 's': //M
		switch (rand() % 14) {
		case 0: pav = "Kazlauskas"; break;
		case 1: pav = "Stankevicius"; break;
		case 2: pav = "Petrauskas"; break;
		case 3: pav = "Zukauskas"; break;
		case 4: pav = "Jankauskas"; break;
		case 5: pav = "Butkus"; break;
		case 6: pav = "Kirkliauskas"; break;
		case 7: pav = "Vasiliauskas"; break;
		case 8: pav = "Lukosius"; break;
		case 9: pav = "Vilkas"; break;
		case 10: pav = "Markevicius"; break;
		case 11: pav = "Maciulis"; break;
		case 13: pav = "Adomavicius"; break;
		case 14: pav = "Mickius"; break;
		}
		break;
	default: //F
		switch (rand() % 10) {
		case 0: pav = "Andziuliene"; break;
		case 1: pav = "Gaidyte"; break;
		case 2: pav = "Dirse"; break;
		case 3: pav = "Ciurlionaite"; break;
		case 4: pav = "Dunauskaite"; break;
		case 5: pav = "Dvarionaite"; break;
		case 6: pav = "Klumpaite"; break;
		case 7: pav = "Salnaite"; break;
		case 8: pav = "Vaitkute"; break;
		case 9: pav = "Mickeviciute"; break;
		case 10: pav = "Urbe"; break;
		}
		break;
	};

	cout << "\n\nCia yra vardas: " << vardas << ", o cia pavarde: " << pav << "\n\n\n";
}

//DARBAS SU FAILAIS
//

//Perskaityti egzistuojanti studentu duomenu faila (su std::vector)
std::vector<Studentas> read_file(std::string& filename, int& suma) {

	std::vector<Studentas> tempStudentai;

	fs::path filePath = filename;

	try {
		//CHECK IMPORTANT EXCEPTIONS

		if (filePath.extension() != ".txt") {
			throw std::runtime_error("\n---KLAIDA: Failas " + filename + " turi baigtis '.txt'---\n");
		}

		if (!fs::exists(filename)) {
			throw std::runtime_error("\n---KLAIDA: Failas " + filename + " neegzistuoja---\n");
		}

		//Open file
		std::fstream fin(filename, std::ios::in);

		if (!fin.is_open()) {
			throw std::runtime_error("\n---KLAIDA: Failo " + filename + " nepavyko atidaryti---\n");
		}

		if (fs::file_size(filename) == 0) {
			throw std::runtime_error("\n---KLAIDA: Failas " + filename + " yra tuscias---\n");
		}

		//Read file
		std::string curr_eil; //current eilute

		fin.ignore(INT32_MAX, '\n');

		while (std::getline(fin, curr_eil)) {
			Studentas A; //temp Studentas
			int tempPaz;

			std::istringstream iss(curr_eil);
			iss >> A.vardas >> A.pav;

			//read visus pazymius
			while (iss >> tempPaz) {
				A.paz.push_back(tempPaz);
				suma += tempPaz;
			}
			//paskutinis pazymys paz vector yra egzamino balas
			A.egzaminas = A.paz.back();
			A.paz.pop_back();
			suma -= A.egzaminas;

			//apskaiciuoti galutinius rezultatus, kadangi isvedami abu
			double vidurkis = (double)suma / (double)A.paz.size();
			A.galutinisVid = 0.4 * vidurkis + 0.6 * A.egzaminas;

			int a = A.paz.size();
			double mediana;
			sort(A.paz.begin(), A.paz.end());
			if (a % 2 == 0) {
				int midLeftElem = a / 2 - 1;
				mediana = (A.paz[midLeftElem] + A.paz[a / 2]) / 2;
			}
			else
				mediana = A.paz[a / 2];

			A.galutinisMed = 0.4 * mediana + 0.6 * A.egzaminas;



			tempStudentai.push_back(A);

			suma = 0;
		}

		fin.close();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << "\n";

		return tempStudentai; //Empty
	}

	return tempStudentai;
}

//Generuoti faila su randomizuotais studentu duomenimis
void student_file_generator(int nStud, int nPaz) {

	//try catch if file exists

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

		if (i != 0) fout << "\n";

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

//Generuoti split files
void split_file_generator(std::string& filename, std::vector<Studentas>& studentai) {
	std::ofstream fout(filename);
	int max_pazSize = studentai[0].paz.size(); //didziausias pazymiu skaicius, header'iui

	//file header

	fout << std::setw(24) << std::left << "Vardas" << std::setw(27) << std::left << "Pavarde";

	for (int i = 0; i < max_pazSize; i++) {
		std::string nd = "ND";
		fout << std::setw(10) << std::left << nd.append(std::to_string(i + 1));
	}

	fout << std::left << "Egz.\n";

	//write to file
	bool firstEil = true;
	for (const auto& s : studentai) {

		if (!firstEil) fout << "\n"; //po paskutinio entry netureti buti dar vieno \n
		firstEil = false;

		//varpav output
		fout << std::setw(24) << std::left << s.vardas;
		fout << std::setw(27) << std::left << s.pav;

		//paz output
		for (const auto& p : s.paz) {
			fout << std::right << p << std::setw(10);
		}
		fout << std::right << s.egzaminas << std::setw(10);
	}

	fout.close();
}

//Isrusiuoti studentus i "gerus" ir "blogus" pagal galutiniVid
void student_split(std::string filename, std::vector<Studentas>& studentai) {
	//filename input prompt + filename validation;

	//sort by choice
	student_sort(studentai);

	//move students to new vectors
	std::vector<Studentas> studGeri, studBlogi;

	for (auto& s : studentai) {
		if (s.galutinisVid < 5.0) {
			studBlogi.push_back(std::move(s));
		}
		else
			studGeri.push_back(std::move(s));
	}
	studentai.clear();

	//create files

	//construct two new filenames
	std::string fileGeri = "geri", fileBlogi = "blogi"; //geri: galutinisVid >= 5.0; blogi: galutinisVid < 5.0

	fileGeri.append(filename); fileBlogi.append(filename);

	split_file_generator(fileGeri, studGeri);
	split_file_generator(fileBlogi, studBlogi);
}

//TESTAVIMAS
// 
//Testavimas: nauju failu sukurimas ir ofstream uzdarymas
void testing_v04_1(int nStud) {
	Timer timer;
	student_file_generator(nStud, 15);
	double time = timer.elapsed();

	cout << "Faila is " << nStud << " studentu ivesciu sukurti uztruko : " << time << "s.\n\n";
}

//Testavimas: egzistuojanciu failu skaitymas ir pavertimas i du atskirus failus
void testing_v04_2(std::vector<Studentas>& studentai, std::string filename, int& suma) {
	//read file
	Timer timer_full;
	Timer timer;
	studentai = read_file(filename, suma);

	cout << "Faila '" << filename << "' perskaityti uztruko : " << timer.elapsed() << "s.\n";

	//split file into two new ones

	//sort file by galutinisVid decreasing
	sort(studentai.begin(), studentai.end(),
		[](Studentas& a, Studentas& b)-> bool {
			return a.galutinisVid > b.galutinisVid;
		});

	//move students to new vectors
	std::vector<Studentas> studGeri, studBlogi;

	Timer timer1;
	for (auto& s : studentai) {
		if (s.galutinisVid < 5.0) {
			studBlogi.push_back(std::move(s));
		}
		else
			studGeri.push_back(std::move(s));
	}
	studentai.clear();

	cout << "Failo '" << filename << "' studentu duomenis isrusiuoti i 'gerus' ir 'blogus' uztruko : " << timer1.elapsed() << "s.\n";

	//create files

	//construct two new filenames
	std::string fileGeri = "geri", fileBlogi = "blogi"; //geri: galutinisVid >= 5.0; blogi: galutinisVid < 5.0

	fileGeri.append(filename); fileBlogi.append(filename);

	Timer timer2;
	split_file_generator(fileGeri, studGeri);
	split_file_generator(fileBlogi, studBlogi);

	cout << "Is failo '" << filename << "' sukurti du failus is isrusiuotu duomenu uztruko : " << timer2.elapsed() << "s.\n";

	//final timer
	cout << "Failo '" << filename << "' testavimas uztruko : " << timer_full.elapsed() << "s.\n\n";
}

template<>
void student_sort_testing<std::list<Studentas>>(std::list<Studentas>& studentai){
	studentai.sort([](const Studentas& a, const Studentas& b) {
		return a.galutinisVid < b.galutinisVid;
		});
}