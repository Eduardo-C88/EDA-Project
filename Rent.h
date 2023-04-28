/*****************************************************************//**
 * \file   Rent.h
 * \brief  
 * 
 * \author Utilizador
 * \date   April 2023
 *********************************************************************/
#pragma once

#include "Globals.h"

enum Month {
	Jan = 1,
	Feb,
	Mar,
	Abr,
	Mai,
	Jun,
	Jul,
	Ago,
	Set,
	Out,
	Nov,
	Dec
};

typedef struct Date {
	int day;
	enum Month month;
	int year;
}Date;

typedef struct Rent {
	Customer customer;
	Manager manager;
	Vehicle vehicle;
	Date date;
}Rent;
