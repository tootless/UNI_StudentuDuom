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

class Studentas {

	std::string vardas_;
	std::string pavarde_;
	std::vector<double> paz_; //nd pazymiai
	double egzaminas_ = 0;
	double galutinis_ = 0;

public:
	Studentas() = default;
	Studentas(const std::string& vardas, const std::string& pavarde);

	inline std::string getVardas() const { return vardas_; }
	inline std::string getPavarde() const { return pavarde_; }
	double getGalutinis(const double (*) (const std::vector<double>&) = mediana) const;
	std::istream& readStudentas(std::istream&);
	


};

const double vidurkis(const std::vector<double>&); //Calculate vidurkis
const double mediana(const std::vector<double>&); //Calculate mediana

void read_file(std::string& filename, std::vector<Studentas>& Studentai);