#include "Studentas.h";

Studentas::Studentas(std::istream& is) {
	readStudentas(is);
}

double Studentas::getGalutinis(double(*calc_funk)(const std::vector<double>&)) const {
	double galutinis_rez = 0.4 * calc_funk(paz_) + 0.6 * egzaminas_;
	return galutinis_rez;
}

std::istream& Studentas::readStudentas(std::istream& input) {
	input >> vardas_ >> pavarde_;

	double temp_paz;

	while (input >> temp_paz) {
		paz_.push_back(temp_paz);
	}
	egzaminas_ = paz_.back();
	paz_.pop_back();

	return input;
}

void Studentas::setRandVardas()
{
	switch (rand() % 14) {
	case 0: vardas_ = "Irma"; break;
	case 1: vardas_ = "Alma"; break;
	case 2: vardas_ = "Irena"; break;
	case 3: vardas_ = "Egle"; break;
	case 4: vardas_ = "Jolanta"; break;
	case 5: vardas_ = "Petras"; break;
	case 6: vardas_ = "Jonas"; break;
	case 7: vardas_ = "Ignas"; break;
	case 8: vardas_ = "Darius"; break;
	case 9: vardas_ = "Simas"; break;
	case 10: vardas_ = "Aistis"; break;
	case 11: vardas_ = "Aurimas"; break;
	case 12: vardas_ = "Kotryna"; break;
	case 13: vardas_ = "Bertolomiejus"; break;
	case 14: vardas_ = "Augustinas"; break;
	}
}

void Studentas::setRandPavarde(std::string& vardas)
{
	vardas = getVardas();
	switch (*vardas.rbegin()) {
	case 's': //M
		switch (rand() % 14) {
		case 0: pavarde_ = "Kazlauskas"; break;
		case 1: pavarde_ = "Stankevicius"; break;
		case 2: pavarde_ = "Petrauskas"; break;
		case 3: pavarde_ = "Zukauskas"; break;
		case 4: pavarde_ = "Jankauskas"; break;
		case 5: pavarde_ = "Butkus"; break;
		case 6: pavarde_ = "Kirkliauskas"; break;
		case 7: pavarde_ = "Vasiliauskas"; break;
		case 8: pavarde_ = "Lukosius"; break;
		case 9: pavarde_ = "Vilkas"; break;
		case 10: pavarde_ = "Markevicius"; break;
		case 11: pavarde_ = "Maciulis"; break;
		case 13: pavarde_ = "Adomavicius"; break;
		case 14: pavarde_ = "Mickius"; break;
		}
		break;
	default: //F
		switch (rand() % 10) {
		case 0: pavarde_ = "Andziuliene"; break;
		case 1: pavarde_ = "Gaidyte"; break;
		case 2: pavarde_ = "Dirse"; break;
		case 3: pavarde_ = "Ciurlionaite"; break;
		case 4: pavarde_ = "Dunauskaite"; break;
		case 5: pavarde_ = "Dvarionaite"; break;
		case 6: pavarde_ = "Klumpaite"; break;
		case 7: pavarde_ = "Salnaite"; break;
		case 8: pavarde_ = "Vaitkute"; break;
		case 9: pavarde_ = "Mickeviciute"; break;
		case 10: pavarde_ = "Urbe"; break;
		}
		break;
	};
}

void Studentas::setRandEgzaminas()
{
	int randEgz = rand() % 10 + 1;
	setEgzaminas(randEgz);
}

void Studentas::setRandPazymiai()
{
	int pazKiekis;
	do {
		integer_input_validation(pazKiekis, 1, -1, "Iveskite norima namu darbu pazymiu skaiciu:\n");

	} while (pazKiekis < 1);

	for (int i = 0; i < pazKiekis; i++) {
		int randPaz = rand() % 10 + 1;
		addPazymys(randPaz);
	}
}

double calc_vidurkis(const std::vector<double>& pazymiai) {
	double suma = 0;
	for (auto& p : pazymiai) suma += p;

	return suma / (double)pazymiai.size();
}

double calc_mediana(const std::vector<double>& pazymiai) {
	sort(pazymiai.begin(), pazymiai.end());
	if (pazymiai.size() % 2 == 0) {
		int midLeftElem = pazymiai.size() / 2 - 1;
		double mediana = (pazymiai[midLeftElem] + pazymiai[pazymiai.size() / 2]) / 2;
	}
	else
		double mediana = pazymiai[pazymiai.size() / 2];
}

void Studentas::vardas_input() {
	string_input_validation(vardas_, "Iveskite studento varda:\n");
}

void Studentas::pavarde_input(){
	string_input_validation(pavarde_, "Iveskite studento pavarde:\n");
}

void Studentas::paz_input(){
	int tempPaz;
	int choiceEndPaz = 0;

	do {
		tempPaz = integer_input_validation(1, 10, "Pazymys:\n");

		addPazymys(tempPaz);

		choiceEndPaz = integer_input_validation(0, 1, "\nAr vesite dar viena pazymi? (0 - Taip, 1 - Ne, eikime prie kito studento):\n");
	} while (choiceEndPaz != 1);
}

void Studentas::egz_input()
{
	int egz = egzaminas_;
	egz = integer_input_validation(1, 10, "Iveskite studento egzamino bala:\n");
	egzaminas_ = egz;
}

//Perskaityti egzistuojanti studentu duomenu faila
template<typename StudentaiContainer>
void read_file(const std::string& filename, StudentaiContainer& studentai) {
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

		//Read file
		std::string curr_eil;

		fin.ignore(INT32_MAX, '\n');

		while (std::getline(fin, curr_eil)) {
			Studentas temp_studentas;
			std::istringstream iss(curr_eil);

			temp_studentas.readStudentas(iss);

			//apskaiciuoti galutinius rezultatus, kadangi isvedami abu

			calc_mediana(temp_studentas.getPazymiai());
			calc_vidurkis(temp_studentas.getPazymiai());

			studentai.push_back(temp_studentas);
		}

		fin.close();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << "\n";
	}
}

//Studentu vektoriaus rusiavimas pagal pasirinkima
void choice_sort(std::vector<Studentas>& studentai, int choice) {
	choice = integer_input_validation(1, 4, "\nKaip norite surusiuoti studentus? \n1 - Pagal vardus,\n2 - Pagal pavardes,\n3 - Pagal galutini (vid.),\n4- Pagal galutini (med.)\n");

	sort(studentai.begin(), studentai.end(),
		[choice](const Studentas& a, const Studentas& b) -> bool {
			if (choice == 1) {
				if (a.getVardas() != b.getVardas()) return a.getVardas() < b.getVardas();
			}
			else if (choice == 2) {
				if (a.getPavarde() != b.getPavarde()) return a.getPavarde() < b.getPavarde();
			}
			else if (choice == 3) {
				return a.getGalutinis(calc_vidurkis) > b.getGalutinis(calc_vidurkis);
			}
			else {
				return a.getGalutinis() > b.getGalutinis();
			}
		});
}