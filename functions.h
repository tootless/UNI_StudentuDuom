#pragma once
#include "mylib.h"

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

int integer_input_validation(int lowEnd, int highEnd, std::string optionalPrompt = ""); //if highEnd = -1, no highEnd used

string string_input_validation(input, std::string optionalPrompt = "");

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