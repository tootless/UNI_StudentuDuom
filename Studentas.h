#pragma once
#include "mylib.h"

double calc_vidurkis(const std::vector<double>&); //Calculate vidurkis
double calc_mediana(const std::vector<double>&); //Calculate mediana

class Studentas {

	std::string vardas_;
	std::string pavarde_;
	std::vector<double> paz_; // nd pazymiai
	double egzaminas_ = 0;
	double galutinis_ = 0;

public:

	Studentas() = default;
	Studentas(std::istream& is);
	~Studentas() = default;

	inline std::string getVardas() const { return vardas_; }
	inline std::string getPavarde() const { return pavarde_; }
	std::vector<double> getPazymiai() const { return paz_; };
	int getPazymiaiSize() const { return paz_.size(); };
	double getEgzaminas() const { return egzaminas_; };
	double getGalutinis(double (*)(const std::vector<double>&) = calc_mediana) const; //returns apdorotas galutinis
	std::istream& readStudentas(std::istream& input);

	void setVardas(const std::string& vardas) { vardas_ = vardas; };
	void setPavarde(const std::string& pavarde) { pavarde_ = pavarde; };
	void addPazymys(const double& pazymys) { paz_.push_back(pazymys); };
	void setEgzaminas(const double& egzaminas) { egzaminas_ = egzaminas; };

	void setRandVardas();
	void setRandPavarde(std::string& vardas);
	void setRandEgzaminas();
	void setRandPazymiai();

	//Input funkcijos
	void paz_input();
	void egz_input();
	void vardas_input();
	void pavarde_input();

};

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
			std::istringstream iss(curr_eil);

			Studentas temp_studentas(iss(curr_eil);

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

//Irasyti studentu duomenis i faila / sukurti nauja faila su duomenimis
template<typename StudentaiContainer>
void write_studentai(const std::string filename, StudentaiContainer& studentai) {
	//write to file
	std::ofstream fout(filename);

	fout << "\n" << std::setw(15) << std::left << "Pavarde" << std::setw(15) << std::left << "Vardas" << std::setw(15) << std::left << "Galutinis (Vid.)   Galutinis (Med.)" << "\n";
	fout << "----------------------------------------------------\n";
	for (const auto& s : studentai) {
		fout << std::setw(15) << std::left << s.getPavarde() << std::setw(15) << std::left << s.getVardas() << std::setw(15) << std::left << std::fixed << std::setprecision(2) << s.getGalutinis(calc_vidurkis) << "   " << std::fixed << std::setprecision(2) << s.getGalutinis() << "\n";
	}

	fout.close();
}

template<typename StudentaiContainer>
void choice_sort(StudentaiContainer& studentai, int choice) {
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

//Sort vector
void vidurkis_sort(std::vector<Studentas>& studentai);

//Sort deque
void vidurkis_sort(std::deque<Studentas>& studentai);

//Sort list
void vidurkis_sort(std::list<Studentas>& studentai);

void split_file_generator(std::string& filename, std::vector<Studentas>& studentai);

void student_split(std::string filename, std::vector<Studentas>& studentai);

/// Testavimo funkcijos

void testing_v04_1(int nStud);

void testing_v04_2(std::string filename);


/// Konteineriu testavimo funkcijos

template <typename StudentaiContainer>
void student_split_strategyold(StudentaiContainer& studentai) {
	std::vector<Studentas> studGeri, studBlogi;
	for (auto& s : studentai) {
		if (s.getGalutinis(calc_vidurkis) < 5.0)
			studBlogi.push_back(std::move(s));
		else
			studGeri.push_back(std::move(s));
	}
	studentai.clear();
}

template <typename StudentaiContainer>
void student_split_strategy1(StudentaiContainer& studentai) {
	StudentaiContainer studBlogi, studGeri;
	for (const auto& s : studentai) {
		if (s.getGalutinis(calc_vidurkis) < 5.0)
			studBlogi.push_back(s);
		else
			studGeri.push_back(s);
	}
}

template <typename StudentaiContainer>
void student_split_strategy2(StudentaiContainer& studentai) {
	StudentaiContainer studBlogi;

	auto it = studentai.begin();
	while (it != studentai.end()) {
		if (it->getGalutinis(calc_vidurkis) < 5.0) {
			studBlogi.push_back(std::move(*it));
			//push iterator and remove studBlogi from studentai
			it = studentai.erase(it);
		}
		else {
			++it;
		}
	}
}

template <typename StudentaiContainer>
void student_split_strategy3(StudentaiContainer& studentai) {
	//reorder - good first, bad after
	auto partition_point = std::stable_partition(
		studentai.begin(), studentai.end(),
		[](const Studentas& s) { return s.getGalutinis(calc_vidurkis) >= 5.0; }
	);
	//move
	StudentaiContainer studBlogi;
	for (auto it = partition_point; it != studentai.end(); ++it) {
		studBlogi.push_back(std::move(*it));
	}
}


//Initial test of containers: reading, sorting + splitting students, writing
template<typename StudentaiContainer>
void test1_containers(int nStud) {
	std::string filename = "studentai" + std::to_string(nStud) + ".txt";

	cout << "\n----TESTAVIMAS SU " << nStud << " STUDENTU IVESCIU----\n\n";

	//reading
	Timer t;
	StudentaiContainer studentai;

	read_file<StudentaiContainer>(filename, studentai);

	double read_t = t.elapsed();
	cout << "Duomenu nuskaitymas is failo " << filename << " uztruko: " << read_t << " s\n\n";
	system("pause");

	//sort by galutinisVid
	Timer t1;
	vidurkis_sort(studentai);
	double sort_t = t1.elapsed();
	cout << "\nStudentu sort() " << filename << " uztruko: " << sort_t << " s\n\n";
	system("pause");

	//split students
	Timer t2;
	student_split_strategyold(studentai);
	double split_t = t2.elapsed();
	cout << "\nStudentu paskirstymas i 'gerus' ir 'blogus' " << filename << " uztruko: " << split_t << " s\n\n";
	system("pause");

	//all results for nStud

	cout << "\n\n---REZULTATAI SU " << nStud << " STUDENTU IVESCIU---\n\n";
	cout << "Nuskaitymas:   " << read_t << " s\n";
	cout << "Rusiavimas (sort):    " << sort_t << " s\n";
	cout << "Skirstymas:    " << split_t << " s\n";
	cout << "Viskas:       " << (read_t + sort_t + split_t) << " s\n";

}

//Test every num of students with one type of container
template <typename StudentaiContainer>
void run_test_containers() {
	test1_containers<StudentaiContainer>(1000);
	test1_containers<StudentaiContainer>(10000);
	test1_containers<StudentaiContainer>(100000);
	test1_containers<StudentaiContainer>(1000000);
	test1_containers<StudentaiContainer>(10000000);
}

//Test every num of students with one type of container
template <typename StudentaiContainer>
void test1_splitting(int nStud) {
	std::string filename = "studentai" + std::to_string(nStud) + ".txt";

	//read
	StudentaiContainer studentai_original;
	read_file<StudentaiContainer>(filename, studentai_original);

	cout << "\n----STRATEGIJA 0 (PIRMINE)----\n\n";

	//copy and sort
	StudentaiContainer studentai0 = studentai_original;
	vidurkis_sort(studentai0);

	//split students and time
	Timer t;
	student_split_strategyold(studentai0);
	double split_t = t.elapsed();
	cout << "\nStudentu paskirstymas i 'gerus' ir 'blogus' " << filename << " uztruko: " << split_t << " s\n\n";
	system("pause");

	cout << "\n----STRATEGIJA 1----\n\n";

	//copy and sort
	StudentaiContainer studentai1 = studentai_original;
	vidurkis_sort(studentai1);

	//split students and time
	Timer t1;
	student_split_strategy1(studentai1);
	double split_t1 = t1.elapsed();
	cout << "\nStudentu paskirstymas i 'gerus' ir 'blogus' " << filename << " uztruko: " << split_t1 << " s\n\n";
	system("pause");

	cout << "\n----STRATEGIJA 2----\n\n";

	//copy and sort
	StudentaiContainer studentai2 = studentai_original;
	vidurkis_sort(studentai2);

	//split students and time
	Timer t2;
	student_split_strategy2(studentai2);
	double split_t2 = t2.elapsed();
	cout << "\nStudentu paskirstymas i 'gerus' ir 'blogus' " << filename << " uztruko: " << split_t2 << " s\n\n";
	system("pause");

	cout << "\n----STRATEGIJA 3----\n\n";

	//copy and sort
	StudentaiContainer studentai3 = studentai_original;
	vidurkis_sort(studentai3);

	//split students and time
	Timer t3;
	student_split_strategy3(studentai3);
	double split_t3 = t3.elapsed();
	cout << "\nStudentu paskirstymas i 'gerus' ir 'blogus' " << filename << " uztruko: " << split_t3 << " s\n\n";
	system("pause");
	system("cls");
}

template <typename StudentaiContainer>
void run_test_splitting() {
	test1_splitting<StudentaiContainer>(1000);
	test1_splitting<StudentaiContainer>(10000);
	test1_splitting<StudentaiContainer>(100000);
	test1_splitting<StudentaiContainer>(1000000);
	test1_splitting<StudentaiContainer>(10000000);
}