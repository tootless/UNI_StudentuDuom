#include "Studentas.h";

Studentas::Studentas(const std::string& vardas, const std::string& pavarde) {

}

double Studentas::getGalutinis(double (*calc_funk)(const std::vector<double>&)) const {
	double galutinis_rez = calc_funk(paz_);
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

double calc_vidurkis(const std::vector<double>& pazymiai) {
	return 0;
}

double calc_mediana(const std::vector<double>& pazymiai) {
	return 0.0;
}

//Perskaityti egzistuojanti studentu duomenu faila
void read_file(const std::string& filename, std::vector<Studentas>& Studentai) {
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
			Studentas temp_Studentas;
			std::istringstream iss(curr_eil);

			temp_Studentas.readStudentas(iss);

			//apskaiciuoti galutinius rezultatus, kadangi isvedami abu

			Studentai.push_back(temp_Studentas);
		}

		fin.close();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << "\n";
	}
}