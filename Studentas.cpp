#include "Studentas.h";

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

//Perskaityti egzistuojanti studentu duomenu faila (su std::vector)
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