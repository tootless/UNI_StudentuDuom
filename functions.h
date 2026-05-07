#pragma once
#include "mylib.h"

void menu(int& choiceMenu);

int integer_input_validation(int lowEnd, int highEnd, std::string optionalPrompt = ""); //if highEnd = -1, no highEnd used

std::string string_input_validation(std::string optionalPrompt = "");

void student_file_generator(int nStud, int nPaz);