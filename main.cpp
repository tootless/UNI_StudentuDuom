#pragma once
#include "mylib.h"
#include "functions.h"

//Visi duomenu rinkiniai su std::vector

int main()
{
	Studentas A; //Temp studentas su realiais duomenimis
	std::vector<Studentas> Studentai; //Galutiniai studentu duomenys
	int m = 0; //Studentu skaicius
	int suma = 0; //Pazymiu suma (Vidurkiui apskaiciuoti)
	double vidurkis = 0, mediana = 0;
	int choiceRez = 0; //Galutinio rez. isvedimo pasirinkimas
	int choiceEndStud = 0; //Studentu duomenu ivesties baigties pasirinkimas
	int choiceMenu = 0; //Programos eigos pasirinkimas

	srand(static_cast<unsigned int>(time(NULL)));

	do {
		//MENIU
		menu(choiceMenu);

		//RANKA
		if (choiceMenu == 1) {
			cout << "---STUDENTO DUOMENU IVEDIMAS---\n\n";

			A.varpav_input();

			cout << "---STUDENTO PAZYMIU IVEDIMAS---\n\n";

			A.egz_input();

			A.paz_input(suma);
		}

		//RND PAZYMIAI IR EGZAMINO BALAS
		else if (choiceMenu == 2) {
			cout << "---STUDENTO DUOMENU IVEDIMAS---\n\n";

			A.varpav_input();

			cout << "\n---RANDOMIZUOTAS EGZAMINO BALAS---\n\n";

			A.rand_egz();

			cout << "\n---RANDOMIZUOTI NAMU DARBU PAZYMIAI---\n\n";

			A.rand_paz(suma);
		}

		//RND VISKAS
		else if (choiceMenu == 3) {
			cout << "\n---RANDOMIZUOTAS STUDENTO VARDAS IR PAVARDE---\n";
			A.rand_varpav();

			cout << "\n---RANDOMIZUOTAS EGZAMINO BALAS---\n\n";

			A.rand_egz();

			cout << "\n---RANDOMIZUOTI NAMU DARBU PAZYMIAI---\n\n";

			A.rand_paz(suma);
		}

		//BAIGTI DARBA (Isvesti galutini rez jei yra)
		else if (choiceMenu == 4) {
			//Eiti i isvedima
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
				cout << "\nIveskite failo pavadinima, is kurio norite nuskaityti:\n";
				getline(cin, filename_input);

				Studentai = read_file(filename_input, suma);
				if (Studentai.empty()) {
					read_success = 0;
				}
				else {
					read_success = 1;
				}
			} while (read_success == 0);

			cout << "\n---STUDENTO DUOMENU ISANKSTINIS SURUSIAVIMAS/ISRIKIAVIMAS---\n\n";

			//Rūšiavimas
			choiceSort = integer_input_validation(1, 4, "\nKaip norite surusiuoti studentus? \n1 - Pagal vardus,\n2 - Pagal pavardes,\n3 - Pagal galutini (vid.),\n4- Pagal galutini (med.)\n");

			//sort here

			//Isvedimas
			do {
				integer_input_validation(choiceOutput, 1, 2, "\nKur norite isvesti studentu galutinius rezultatus? (1 - Faile, 2 - Ekrane)\n");

			} while (choiceOutput < 1 || choiceOutput > 2);

			if (choiceOutput == 1) {
				std::string answer2;
				cout << "\nIveskite failo pavadinima, i kuri norite irasyti duomenis (arba sukurti nauja, jeigu failo su tokiu pav. nera):\n";
				cin >> answer2;

				write_studentai(answer2, Studentai);
			}
			else if (choiceOutput == 2) {

				cout << "\n" << std::setw(15) << std::left << "Pavarde" << std::setw(15) << std::left << "Vardas" << std::setw(15) << std::left << "Galutinis (Vid.)   Galutinis (Med.)" << "\n";
				cout << "----------------------------------------------------\n";
				for (int i = 0; i < Studentai.size(); i++) {
					cout << std::setw(15) << std::left << Studentai[i].pav << std::setw(15) << std::left << Studentai[i].vardas << std::setw(15) << std::left << std::fixed << std::setprecision(2) << Studentai[i].galutinisVid << "   " << std::fixed << std::setprecision(2) << Studentai[i].galutinisMed << "\n";
				}
				choiceOutput = 0;
			}

			//Iseiti is while loop
			choiceEndStud = 1;
		}
		
		//Randomizuotu stud. duomenu failo generavimas
		else if (choiceMenu == 6) {
			//prompt
			int studNum;
			integer_input_validation(studNum, 0, -1, "\nIveskite su kiek randomizuotu studentu duomenu norite uzpildyti faila: \n");

			//generate file
			student_file_generator(studNum, 15);
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

			testing_v04_2(Studentai,"studentai1000.txt",suma);
			system("pause");

			testing_v04_2(Studentai, "studentai10000.txt", suma);
			system("pause");

			testing_v04_2(Studentai, "studentai100000.txt", suma);
			system("pause");

			testing_v04_2(Studentai, "studentai1000000.txt", suma);
			system("pause");

			testing_v04_2(Studentai, "studentai10000000.txt", suma);


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

		//Perkeliam vieno studento duomenis
		Studentai.push_back(A);
		if (!Studentai.empty()) {
			//Apskaiciuojame galutini rezultata kiekvienam studentui
			vidurkis = (double)suma / ((double)Studentai[m].paz.size());
			Studentai[m].galutinisVid = 0.4 * vidurkis + 0.6 * Studentai[m].egzaminas;

			for (int i = 0; i < m; i++) {
				int a = Studentai[i].paz.size();
				sort(Studentai[i].paz.begin(), Studentai[i].paz.end());
				if (a % 2 == 0) {
					int midLeftElem = a / 2 - 1;
					mediana = (Studentai[i].paz[midLeftElem] + Studentai[i].paz[a / 2]) / 2;
				}
				else
					mediana = Studentai[i].paz[a / 2];

				Studentai[i].galutinisMed = 0.4 * mediana + 0.6 * Studentai[i].egzaminas;
			}
		}

		//Testi studentu duom ivedima
		if (choiceEndStud != 1) {
			m++; //Skaiciuojame studentu skaiciu / saugome indeksa
			do {
				integer_input_validation(choiceEndStud, 0, 1, "\nAr vesite dar vieno studento duomenis? (0 - Taip, 1 - Ne, einame prie galutiniu rezultatu)\n");

			} while (choiceEndStud < 0 || choiceEndStud > 1);

			system("cls");
		}
		else Studentai.clear();

		//Reset
		if (choiceMenu == 5 || choiceMenu == 6) Studentai.clear();
		vidurkis = 0;
		suma = 0;
	} while (choiceEndStud != 1);

	///GALUTINIS REZULTATAS
	if (!Studentai.empty()) {

		do {
			integer_input_validation(choiceRez, 1, 2, "Kaip norite isvesti studentu galutinius rezultatus? (1 - Vidurkis, 2 - Mediana)\n");

		} while (choiceRez < 1 || choiceRez > 2);

		system("cls");

		//VIDURKIS
		if (choiceRez == 1) {
			//Rūšiavimas
			student_sort(Studentai);

			cout << "\n" << std::setw(15) << std::left << "Pavarde" << std::setw(15) << std::left << "Vardas" << std::setw(15) << std::left << "Galutinis (Vid.)" << "\n";
			cout << "----------------------------------------------------\n";
			for (const auto& s : Studentai) {
				cout << std::setw(15) << std::left << s.pav << std::setw(15) << std::left << s.vardas << std::setw(15) << std::left << std::fixed << std::setprecision(2) << s.galutinisVid << "   " << "\n";
			}
			choiceRez = 0;
		}
		//MEDIANA
		else if (choiceRez == 2) {
			//Rūšiavimas
			student_sort(Studentai);

			//Output
			cout << "\n" << std::setw(15) << std::left << "Pavarde" << std::setw(15) << std::left << "Vardas" << std::setw(15) << std::left << "Galutinis (Med.)" << "\n";
			cout << "------------------------------------------\n";
			for (const auto& s : Studentai) {
				cout << std::setw(15) << std::left << s.pav << std::setw(15) << std::left << s.vardas << std::setw(15) << std::left << std::fixed << std::setprecision(2) << s.galutinisMed << "   " << "\n";
			}

			choiceRez = 0;
		}

		//Restart()
	}
	else if (Studentai.empty() && (choiceMenu != 5 && choiceMenu != 6 && choiceMenu != 7)) {
		cout << "Studentu duomenu nera.\n\n";
		//Restart();
	}

	return 0;
}
