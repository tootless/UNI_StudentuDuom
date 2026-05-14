#include "mylib.h"
#include "Studentas.h"
#include "functions.h"

Studentas::Studentas(std::istream& in) {
	read(in);
}

Studentas::Studentas(const Studentas& other) {
	vardas_ = other.vardas_;
	pavarde_ = other.pavarde_;
	paz_ = other.paz_;
	egzaminas_ = other.egzaminas_;
	galutinis_ = other.galutinis_;
}

Studentas::Studentas(Studentas&& other) noexcept {
	vardas_ = std::move(other.vardas_);
	pavarde_ = std::move(other.pavarde_);
	paz_ = std::move(other.paz_);
	egzaminas_ = std::move(other.egzaminas_);
	galutinis_ = std::move(other.galutinis_);
}

Studentas& Studentas::operator=(const Studentas& other) {
	if (this == &other) return *this;

	vardas_ = other.vardas_;
	pavarde_ = other.pavarde_;
	paz_ = other.paz_;
	egzaminas_ = other.egzaminas_;
	galutinis_ = other.galutinis_;

	return *this;
}

Studentas& Studentas::operator=(Studentas&& other) noexcept {
	if (this == &other) return *this;

	vardas_ = std::move(other.vardas_);
	pavarde_ = std::move(other.pavarde_);
	paz_ = std::move(other.paz_);
	egzaminas_ = other.egzaminas_;
	galutinis_ = other.galutinis_;

	return *this;
}

std::istream& operator>>(std::istream& in, Studentas& studentas) {
	studentas.read(in);
	return in;
}

//Outputs all data
std::ostream& operator<<(std::ostream& out, const Studentas& studentas) {
	out << std::setw(15) << std::left << studentas.getVardas()
		<< std::setw(15) << std::left << studentas.getPavarde()
		<< std::setw(15) << std::left << std::fixed << std::setprecision(2) << studentas.getGalutinis(calc_vidurkis)
		<< std::fixed << std::setprecision(2) << studentas.getGalutinis();

	return out;
}

double Studentas::getGalutinis(double(*calc_funk)(const std::vector<double>&)) const {
	double galutinis_rez = 0.4 * calc_funk(paz_) + 0.6 * egzaminas_;
	return galutinis_rez;
}

std::istream& Studentas::read(std::istream& input) {
	input >> vardas_ >> pavarde_;

	double temp_paz;

	std::vector<double> temp_vec;

	while (input >> temp_paz)
	{
		temp_vec.push_back(temp_paz);
	}

	if (!temp_vec.empty())
	{
		egzaminas_ = temp_vec.back();
		temp_vec.pop_back();
		paz_ = temp_vec;
	}

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
	pazKiekis = integer_input_validation(1, -1, "Iveskite norima namu darbu pazymiu skaiciu:\n");

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
	std::vector<double> sortedPaz = pazymiai;
	sort(sortedPaz.begin(), sortedPaz.end());
	if (sortedPaz.size() % 2 == 0) {
		int midLeftElem = sortedPaz.size() / 2 - 1;
		return (sortedPaz[midLeftElem] + sortedPaz[sortedPaz.size() / 2]) / 2.0;
	}
	else
		return sortedPaz[sortedPaz.size() / 2];
}

void Zmogus::vardas_input() {
	vardas_ = string_input_validation("Iveskite studento varda:\n");
}

void Zmogus::pavarde_input() {
	pavarde_ = string_input_validation("Iveskite studento pavarde:\n");
}

void Studentas::paz_input() {
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

void split_file_generator(const std::string& filename, std::vector<Studentas>& studentai) {
	std::ofstream fout(filename);
	int max_pazSize = studentai[0].getPazymiaiSize(); //didziausias pazymiu skaicius, header'iui, !!siuo metu toks pats visiems studentams

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

		if (!firstEil) fout << '\n'; //po paskutinio entry netureti buti dar vieno \n
		firstEil = false;

		//varpav output
		fout << std::setw(24) << std::left << s.getVardas();
		fout << std::setw(27) << std::left << s.getPavarde();

		//paz output
		for (const auto& p : s.getPazymiai()) {
			fout << std::right << p << std::setw(10);
		}
		fout << std::right << s.getEgzaminas() << std::setw(10);
	}

	fout.close();
}

void student_split(std::string filename, std::vector<Studentas>& studentai) {
	//filename input prompt + filename validation;

	//sorting prompt
	int choiceSort = integer_input_validation(1, 4, "\nKaip norite surusiuoti studentus? \n1 - Pagal vardus,\n2 - Pagal pavardes,\n3 - Pagal galutini (vid.),\n4- Pagal galutini (med.)\n");

	//sort by choice
	choice_sort(studentai, choiceSort);

	//move students to new vectors
	std::vector<Studentas> studGeri, studBlogi;

	for (auto& s : studentai) {
		if (s.getGalutinis(calc_vidurkis) < 5.0) {
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

//Sort vector
void vidurkis_sort(std::vector<Studentas>& studentai) { //didejimo tvarka
	sort(studentai.begin(), studentai.end(),
		[](const Studentas& a, const Studentas& b) -> bool {
			return a.getGalutinis(calc_vidurkis) < b.getGalutinis(calc_vidurkis);
		});
}

//Sort deque
void vidurkis_sort(std::deque<Studentas>& studentai) { //didejimo tvarka
	sort(studentai.begin(), studentai.end(),
		[](const Studentas& a, const Studentas& b) -> bool {
			return a.getGalutinis(calc_vidurkis) < b.getGalutinis(calc_vidurkis);
		});
}

//Sort list
void vidurkis_sort(std::list<Studentas>& studentai) {
	studentai.sort([](const Studentas& a, const Studentas& b) {
		return a.getGalutinis(calc_vidurkis) < b.getGalutinis(calc_vidurkis); //didejimo tvarka
		});
}

//Testavimas: nauju failu sukurimas ir ofstream uzdarymas
void testing_v04_1(int nStud) {
	Timer timer;
	student_file_generator(nStud, 15);
	double time = timer.elapsed();

	cout << "Faila is " << nStud << " studentu ivesciu sukurti uztruko : " << time << "s.\n\n";
}

//Testavimas: egzistuojanciu failu skaitymas ir pavertimas i du atskirus failus
void testing_v04_2(std::string filename) {
	//read file
	Timer timer_full;
	Timer timer;
	std::vector<Studentas> studentai;

	read_file(filename, studentai);

	cout << "Faila '" << filename << "' perskaityti uztruko : " << timer.elapsed() << "s.\n";

	//split file into two new ones

	//sort file by galutinisVid decreasing
	sort(studentai.begin(), studentai.end(),
		[](Studentas& a, Studentas& b)-> bool {
			return a.getGalutinis(calc_vidurkis) > b.getGalutinis(calc_vidurkis);
		});

	//move students to new vectors
	std::vector<Studentas> studGeri, studBlogi;

	Timer timer1;
	for (auto& s : studentai) {
		if (s.getGalutinis(calc_vidurkis) < 5.0) {
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

//Testavimas: rule of five + I/O operatoriu overloads
void testROF() {
	Studentas s1;
	s1.setVardas("Algis");
	s1.setPavarde("Dovydaitis");

	cout << "Original data: " << s1 << '\n';

	//input output

	std::istringstream in("Algis Dovydaitis");

	Studentas sin;
	in >> sin;

	cout << "Input operator: " << sin << '\n';

	std::ostringstream out;
	out << s1;
	std::string res = out.str();

	cout << "Output operator, from original data: " << res << '\n';

	//copy
	Studentas s2(s1);

	cout << "Copy constructor: " << s2 << '\n';

	//move
	Studentas s3(std::move(s2));

	cout << "Move constructor: " << s3 << '\n';

	//assign copy
	Studentas s4;
	s4 = s1;

	cout << "Copy assignment: " << s4 << '\n';

	//assign move
	Studentas s5;
	s5 = std::move(s4);

	cout << "Move assignment: " << s5 << '\n';
}