#pragma once
#include <iostream>
#include <iomanip>

#include <fstream>
#include <sstream>

#include <Windows.h>
#include <conio.h>

#include <vector>
#include <string>

#include <algorithm>
#include <cmath>

using namespace std;

class OneDimInteraction
{

public:

	float getFuncValue(float x); // xe^(-(x^2)/2))

	void ScanMethod();
	void ScanMethodVar();
	void DichotomyMethod();
	void GoldenRatioMethod();

};

void printQuit();