#ifndef MAIN_H
#define MAIN_H
#include "linewidget.h"
#include <QApplication>
#include <iostream>
#include <string>
#include <QtGlobal>

//solver libraries
#include <stdint.h>
#include <string.h>
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<cmath>
#include<time.h>
using namespace std;

void trivialMatrix(char* filename, double tolerance, bool infinite, double max);

int EasyPlotting();

#endif
