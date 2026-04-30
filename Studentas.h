#pragma once
#include "mylib.h"
#include "functions.h"

class Studentas {

	std::string vardas_;
	std::string pavarde_;
	std::vector<double> paz_; // nd pazymiai
	double egzaminas_ = 0;
	double galutinis_ = 0;

public:

	Studentas() = default;
	Studentas(std::istream& is);

	inline std::string getVardas() const { return vardas_; }
	inline std::string getPavarde() const { return pavarde_; }
	std::vector<double> getPazymiai() const { return paz_; };
	double getGalutinis(double (*)(const std::vector<double>&) = calc_mediana) const;
	std::istream& readStudentas(std::istream& input);

	void setVardas(const std::string& vardas) { vardas_ = vardas; };
	void setPavarde(const std::string& pavarde) { pavarde_ = pavarde; };
	void addPazymys(const double& pazymys) { paz_.push_back(pazymys); };
	void setEgzaminas(const double& egzaminas) { egzaminas_ = egzaminas;};

	void setRandVardas();
	void setRandPavarde(std::string& vardas);
	void setRandEgzaminas();
	void setRandPazymiai();

};

double calc_vidurkis(const std::vector<double>&); //Calculate vidurkis
double calc_mediana(const std::vector<double>&); //Calculate mediana

//Input funkcijos

void paz_input();


void read_file(std::string&, std::vector<Studentas>&);

//Irasyti studentu duomenis i faila / sukurti nauja faila su duomenimis
template<typename StudentaiContainer>
void write_studentai(const std::string filename, StudentaiContainer& studentai) {
	//write to file
	std::ofstream fout(filename);

	fout << "\n" << std::setw(15) << std::left << "Pavarde" << std::setw(15) << std::left << "Vardas" << std::setw(15) << std::left << "Galutinis (Vid.)   Galutinis (Med.)" << "\n";
	fout << "----------------------------------------------------\n";
	for (const auto& s : studentai) {
		fout << std::setw(15) << std::left << s.getPavarde() << std::setw(15) << std::left << s.getVardas()<< std::setw(15) << std::left << std::fixed << std::setprecision(2) << s.getGalutinis(calc_vidurkis) << "   " << std::fixed << std::setprecision(2) << s.getGalutinis() << "\n";
	}

	fout.close();
}

void choice_sort(std::vector<Studentas>&);



