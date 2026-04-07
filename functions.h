//function declarations file

#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <filesystem>
#include <list>
#include "timer.h";

namespace fs = std::filesystem;

using std::cout;
using std::cin;

struct Studentas {
	std::string vardas, pav;
	std::vector<int> paz;
	int egzaminas = 0;
	double galutinisVid = 0;
	double galutinisMed = 0;

	void varpav_input();
	void paz_input(int& suma);
	void egz_input();
	void rand_paz(int& suma);
	void rand_egz();
	void rand_varpav();
};

std::vector<Studentas> read_file(std::string& filename, int& suma);

//Perskaityti egzistuojanti studentu duomenu faila
template<typename StudentaiContainer>
StudentaiContainer read_file_testing(std::string& filename, int& suma) {

	StudentaiContainer tempStudentai;

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

//Irasyti studentu duomenis i faila / sukurti nauja faila su duomenimis
template<typename StudentaiContainer>
void write_studentai(const std::string filename, StudentaiContainer& studentai) {
	//sorting
	//int choiceOutput;



	//write to file
	std::ofstream fout(filename);

	fout << "\n" << std::setw(15) << std::left << "Pavarde" << std::setw(15) << std::left << "Vardas" << std::setw(15) << std::left << "Galutinis (Vid.)   Galutinis (Med.)" << "\n";
	fout << "----------------------------------------------------\n";
	for (const auto& s : studentai) {
		fout << std::setw(15) << std::left << s.pav << std::setw(15) << std::left << s.vardas << std::setw(15) << std::left << std::fixed << std::setprecision(2) << s.galutinisVid << "   " << std::fixed << std::setprecision(2) << s.galutinisMed << "\n";
	}

	fout.close();
}

void student_file_generator(int nStud, int nPaz);

void split_file_generator(std::string& filename, std::vector<Studentas>& studentai);

void student_split(std::string filename, std::vector<Studentas>& studentai);

template <typename StudentaiContainer>
void student_split_strategyold(StudentaiContainer& studentai) {
	std::vector<Studentas> studGeri, studBlogi;
	for (auto& s : studentai) {
		if (s.galutinisVid < 5.0)
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
		if (s.galutinisVid < 5.0)
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
		if (it->galutinisVid < 5.0) {
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
		[](const Studentas& s) { return s.galutinisVid >= 5.0; }
	);
	//move
	StudentaiContainer studBlogi;
	for (auto it = partition_point; it != studentai.end(); ++it) {
		studBlogi.push_back(std::move(*it));
	}
}

void menu(int& choiceMenu);

void number_input_validation(int& choice, int lowEnd, int highEnd, std::string optionalPrompt = "");

void string_input_validation(std::string& input, std::string optionalPrompt = "");

void student_sort(std::vector<Studentas>& studentai);

//Studentu rusiavimas didejimo tvarka pagal galutiniVid
template<typename StudentaiContainer>
void student_sort_testing(StudentaiContainer& studentai) {
	sort(studentai.begin(), studentai.end(),
		[](const Studentas& a, const Studentas& b) -> bool {
			return a.galutinisVid < b.galutinisVid;
		});
}

//Studentu rusiavimas su std::list didejimo tvarka pagal galutiniVid
template<>
static void student_sort_testing<std::list<Studentas>>(std::list<Studentas>& studentai);

void calculate_galutinis();

//void test1_files
void testing_v04_1(int nStud);

//void test2_files
void testing_v04_2(std::vector<Studentas>& studentai, const std::string filename, int& suma);

//void run_test_files

//Initial test of containers: reading, sorting + splitting students, writing
template<typename StudentaiContainer>
void test1_containers(int nStud) {
	std::string filename = "studentai" + std::to_string(nStud) + ".txt";
	int suma = 0;

	cout << "\n----TESTAVIMAS SU " << nStud << " STUDENTU IVESCIU----\n\n";

	//reading
	Timer t;
	StudentaiContainer studentai = read_file_testing<StudentaiContainer>(filename, suma);
	double read_t = t.elapsed();
	cout << "Duomenu nuskaitymas is failo " << filename << " uztruko: " << read_t << " s\n\n";
	system("pause");
	//sort by galutinisVid
	Timer t1;
	student_sort_testing(studentai);
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

	int suma = 0;
	//read
	StudentaiContainer studentai_original = read_file_testing<StudentaiContainer>(filename, suma);

	cout << "\n----STRATEGIJA 0 (PIRMINE)----\n\n";
	
	//copy and sort
	StudentaiContainer studentai0 = studentai_original;
	student_sort_testing(studentai0);

	//split students and time
	Timer t;
	student_split_strategyold(studentai0);
	double split_t = t.elapsed();
	cout << "\nStudentu paskirstymas i 'gerus' ir 'blogus' " << filename << " uztruko: " << split_t << " s\n\n";
	system("pause");

	cout << "\n----STRATEGIJA 1----\n\n";

	//copy and sort
	StudentaiContainer studentai1 = studentai_original;
	student_sort_testing(studentai1);

	//split students and time
	Timer t1;
	student_split_strategy1(studentai1);
	double split_t1 = t1.elapsed();
	cout << "\nStudentu paskirstymas i 'gerus' ir 'blogus' " << filename << " uztruko: " << split_t1 << " s\n\n";
	system("pause");

	cout << "\n----STRATEGIJA 2----\n\n";

	//copy and sort
	StudentaiContainer studentai2 = studentai_original;
	student_sort_testing(studentai2);

	//split students and time
	Timer t2;
	student_split_strategy2(studentai2);
	double split_t2 = t2.elapsed();
	cout << "\nStudentu paskirstymas i 'gerus' ir 'blogus' " << filename << " uztruko: " << split_t2 << " s\n\n";
	system("pause");

	cout << "\n----STRATEGIJA 3----\n\n";

	//copy and sort
	StudentaiContainer studentai3 = studentai_original;
	student_sort_testing(studentai3);

	//split students and time
	Timer t3;
	student_split_strategy3(studentai);
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