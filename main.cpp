#pragma once
#include "mylib.h"
#include "functions.h"
#include "Studentas.h"

//Visi duomenu rinkiniai su std::vector

int main()
{
	std::vector<Studentas> Studentai; //Galutiniai studentu duomenys
	int choiceEndStud = 0; //Studentu duomenu ivesties baigties pasirinkimas
	int choiceMenu = 0; //Programos eigos pasirinkimas

	srand(static_cast<unsigned int>(time(NULL)));

	do {
		//MENIU
		menu(choiceMenu);

		//RANKA
		if (choiceMenu == 1) {
			Studentas A;

			cout << "---STUDENTO DUOMENU IVEDIMAS---\n\n";
			A.vardas_input();
			A.pavarde_input();

			cout << "---STUDENTO PAZYMIU IVEDIMAS---\n\n";
			A.egz_input();
			A.paz_input();

			Studentai.push_back(A);
		}

		//RND PAZYMIAI IR EGZAMINO BALAS
		else if (choiceMenu == 2) {
			Studentas A;

			cout << "---STUDENTO DUOMENU IVEDIMAS---\n\n";
			A.vardas_input();
			A.pavarde_input();

			cout << "\n---RANDOMIZUOTAS EGZAMINO BALAS---\n\n";
			A.setRandEgzaminas();

			cout << "\n---RANDOMIZUOTI NAMU DARBU PAZYMIAI---\n\n";
			A.setRandPazymiai();

			Studentai.push_back(A);
		}

		//RND VISKAS
		else if (choiceMenu == 3) {
			Studentas A;

			cout << "\n---RANDOMIZUOTAS STUDENTO VARDAS IR PAVARDE---\n";
			A.setRandVardas();

			std::string vardas = A.getVardas();
			A.setRandPavarde(vardas);

			cout << "\n---RANDOMIZUOTAS EGZAMINO BALAS---\n\n";
			A.setRandEgzaminas();

			cout << "\n---RANDOMIZUOTI NAMU DARBU PAZYMIAI---\n\n";
			A.setRandPazymiai();

			Studentai.push_back(A);
		}

		//BAIGTI DARBA (Isvesti galutini rez jei yra)
		else if (choiceMenu == 4) {
			choiceEndStud = 1;
		}

		//SKAITYTI IS FAILO
		else if (choiceMenu == 5) {
			std::string filename_input;
			int choiceOutput, choiceSort;

			cout << "\n---STUDENTO DUOMENU NUSKAITYMAS IS FAILO---\n\n";

			//Skaitymas
			bool read_success = true;
			do {
				//perhaps filename_input() someday
				cout << "\nIveskite failo pavadinima, is kurio norite nuskaityti:\n";
				getline(cin, filename_input);

				read_file(filename_input, Studentai);
				if (Studentai.empty()) {
					read_success = 0;
					cout << "Nepavyko nuskaityti failo. Bandykite dar karta.\n";
				}
				else {
					read_success = 1;
				}
			} while (read_success == 0);

			cout << "\n---STUDENTU DUOMENU ISANKSTINIS SURUSIAVIMAS/ISRIKIAVIMAS---\n\n";

			//Rūšiavimas
			choiceSort = integer_input_validation(1, 4, "\nKaip norite surusiuoti studentus? \n1 - Pagal vardus,\n2 - Pagal pavardes,\n3 - Pagal galutini (vid.),\n4- Pagal galutini (med.)\n");
			
			choice_sort(Studentai, choiceSort);

			//Isvedimas
			choiceOutput = integer_input_validation(1, 2, "\nKur norite isvesti studentu galutinius rezultatus? (1 - Faile, 2 - Ekrane)\n");

			if (choiceOutput == 1) {
				std::string answer2;
				cout << "\nIveskite failo pavadinima, i kuri norite irasyti duomenis (arba sukurti nauja, jeigu failo su tokiu pav. nera):\n";
				getline(cin, answer2);

				write_studentai(answer2, Studentai);
			}
			else if (choiceOutput == 2) {
				cout << "\n" << std::setw(15) << std::left << "Pavarde"
					<< std::setw(15) << std::left << "Vardas"
					<< std::setw(15) << std::left << "Galutinis (Vid.)"
					<< std::setw(15) << std::left << "Galutinis (Med.)" << "\n";
				cout << "--------------------------------------------------------------\n";

				for (const auto& studentas : Studentai) {
					cout << std::setw(15) << std::left << studentas.getPavarde()
						<< std::setw(15) << std::left << studentas.getVardas()
						<< std::setw(15) << std::left << std::fixed << std::setprecision(2)
						<< studentas.getGalutinis(calc_vidurkis)
						<< std::setw(15) << std::left << std::fixed << std::setprecision(2)
						<< studentas.getGalutinis() << "\n";
				}
			}

			choiceEndStud = 1;
		}

		//Randomizuotu stud. duomenu failo generavimas
		else if (choiceMenu == 6) {
			//prompt
			int studNum;
			studNum = integer_input_validation(0, -1, "\nIveskite su kiek randomizuotu studentu duomenu norite uzpildyti faila: \n");

			student_file_generator(studNum, 15);
			cout << "Sugeneruotas failas su " << studNum << " studentu duomenimis.\n";
		}

		//Spartos analize
		else if (choiceMenu == 7) {
			cout << "\n---PROGRAMOS SPARTOS ANALIZE---\n";
			cout << "\n---FAILU SUKURIMO SPARTOS ANALIZE---\n\n";

			testing_v04_1(1000);
			system("pause");

			testing_v04_1(10000);
			system("pause");

			testing_v04_1(100000);
			system("pause");

			testing_v04_1(1000000);
			system("pause");

			testing_v04_1(10000000);

			cout << "\n---EGZISTUOJANCIU FAILU SKAITYMO SPARTOS ANALIZE---\n\n";

			testing_v04_2("studentai1000.txt");
			system("pause");

			testing_v04_2("studentai10000.txt");
			system("pause");

			testing_v04_2("studentai100000.txt");
			system("pause");

			testing_v04_2("studentai1000000.txt");
			system("pause");

			testing_v04_2("studentai10000000.txt");

			choiceEndStud = 1;
		}

		//Spartos analize 2
		else if (choiceMenu == 8) {

			cout << "\n---STD::VECTOR---\n\n";
			run_test_containers<std::vector<Studentas>>();
			cout << "Pabaiga std::vector testavimo\n";
			system("pause");
			system("cls");

			cout << "\n---STD::LIST---\n\n";
			run_test_containers<std::list<Studentas>>();
			cout << "Pabaiga std::list testavimo\n";
			system("pause");
			system("cls");

			cout << "\n---STD::DEQUE---\n\n";
			run_test_containers<std::deque<Studentas>>();
			cout << "Pabaiga std::deque testavimo\n";
			system("pause");
			system("cls");

			cout << "\n---STD::VECTOR---\n\n";
			run_test_splitting<std::vector<Studentas>>();
			cout << "Pabaiga std::vector testavimo\n";
			system("pause");
			system("cls");

			cout << "\n---STD::LIST---\n\n";
			run_test_splitting<std::list<Studentas>>();
			cout << "Pabaiga std::list testavimo\n";
			system("pause");
			system("cls");

			cout << "\n---STD::DEQUE---\n\n";
			run_test_splitting<std::deque<Studentas>>();
			cout << "Pabaiga std::deque testavimo\n";
			system("pause");
			system("cls");


		}

		if (choiceMenu >= 1 && choiceMenu <= 3) {
			choiceEndStud = integer_input_validation(0, 1, "\nAr vesite dar vieno studento duomenis? (0 - Taip, 1 - Ne, einame prie galutiniu rezultatu)\n");
			system("cls");
		}

		//Reset
		if (choiceMenu >= 5 && choiceMenu <= 8) {
			Studentai.clear();
			choiceEndStud = 0;
		}

	} while (choiceEndStud != 1);

	///GALUTINIS REZULTATAS
	if (!Studentai.empty()) {
		int choiceRez = integer_input_validation(1, 2, "Kaip norite isvesti studentu galutinius rezultatus? (1 - Vidurkis, 2 - Mediana)\n");
		system("cls");
		int choiceSort = integer_input_validation(1, 4, "\nKaip norite surusiuoti studentus? \n1 - Pagal vardus,\n2 - Pagal pavardes,\n3 - Pagal galutini (vid.),\n4- Pagal galutini (med.)\n");
		system("cls");

		choice_sort(Studentai, choiceSort);

		//VIDURKIS
		if (choiceRez == 1) {

			cout << "\n" << std::setw(15) << std::left << "Pavarde"
				<< std::setw(15) << std::left << "Vardas"
				<< std::setw(15) << std::left << "Galutinis (Vid.)" << "\n";
			cout << "------------------------------------------\n";

			for (const auto& s : Studentai) {
				cout << std::setw(15) << std::left << s.getPavarde()
					<< std::setw(15) << std::left << s.getVardas()
					<< std::setw(15) << std::left << std::fixed << std::setprecision(2)
					<< s.getGalutinis(calc_vidurkis) << "\n";
			}
		}
		//MEDIANA
		else if (choiceRez == 2) {
			cout << "\n" << std::setw(15) << std::left << "Pavarde"
				<< std::setw(15) << std::left << "Vardas"
				<< std::setw(15) << std::left << "Galutinis (Med.)" << "\n";
			cout << "------------------------------------------\n";

			for (const auto& s : Studentai) {
				cout << std::setw(15) << std::left << s.getPavarde()
					<< std::setw(15) << std::left << s.getVardas()
					<< std::setw(15) << std::left << std::fixed << std::setprecision(2)
					<< s.getGalutinis() << "\n";
			}
		}
	}
	else if (Studentai.empty() && (choiceMenu != 5 && choiceMenu != 6 && choiceMenu != 7 && choiceMenu != 8)) {
		cout << "Studentu duomenu nera.\n\n";
	}

	return 0;
}
