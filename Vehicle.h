/*****************************************************************//**
 * \file   Vehicle.h
 * \brief  
 * 
 * \author Eduardo
 * \date   March 2023
 *********************************************************************/
#pragma once
#pragma warning(disable : 4996)

#ifndef VEHICLE
#define VEHICLE

#include "Globals.h"

#define TYPE_SIZE 15
#define CODE_SIZE 20

typedef struct Vehicle{
	int id;
	char type[TYPE_SIZE];
	float battery;
	float price;
	char geoCode[CODE_SIZE];
	struct Vehicle* next;
}Vehicle;

Vehicle* LoadVehicles(char f[]);
/**
 * .
 */
Vehicle* LoadVehiclesBin(char f[]);
/**
 * .
 */
bool SaveVehicle(Vehicle* h, char f[]);
/**
 * .
 */
bool SaveVehicleBin(Vehicle* h, char f[]);
/**
 * .
 */
Vehicle* AddVehicle(Vehicle* h, Vehicle* v);
/**
 * .
 */
Vehicle* RemoveVehicle(Vehicle* h, int id);
/**
 * .
 */
bool EditVehicle(Vehicle* h, Vehicle* v);
/**
 * 
 * .
 */
void ShowVehicleList(Vehicle* h);
/**
 * .
 */
bool ClearVehicleList(Vehicle* h);
/**
 * .
 */
Vehicle* SearchVehicle(Vehicle* h, char t[]);


#endif


