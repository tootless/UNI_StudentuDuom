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
#include "timer.h"
//#include "functions.h"

namespace fs = std::filesystem;

double calc_vidurkis(const std::vector<double>&); //Calculate vidurkis
double calc_mediana(const std::vector<double>&); //Calculate mediana

class Studentas {

	std::string vardas_;
	std::string pavarde_;
	std::vector<double> paz_; // nd pazymiai
	double egzaminas_ = 0;
	double galutinis_ = 0;

public:
	// Member funkcijos

	Studentas() = default;
	Studentas(const std::string& vardas, const std::string& pavarde);

	inline std::string getVardas() const { return vardas_; }
	inline std::string getPavarde() const { return pavarde_; }
	double getGalutinis(double (*)(const std::vector<double>&) = calc_mediana) const;
	std::istream& readStudentas(std::istream& input);

};

void read_file(std::string&, std::vector<Studentas>&);