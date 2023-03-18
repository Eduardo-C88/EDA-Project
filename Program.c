/*****************************************************************//**
 * \file   Program.c
 * \brief  Fun��o main para correr o codigo
 * 
 * \author Eduardo
 * \date   March 2023
 *********************************************************************/

#include "Globals.h"

int main() {
	Customer* cHeader = LoadCustomersBin("Customers.bin");
	if (cHeader == NULL)LoadCustomers("Customers.txt");

	Manager* mHeader = LoadManagersBin("Managers.bin");
	if (mHeader == NULL)LoadManagers("Managers.txt");

	Vehicle* vHeader = LoadVehiclesBin("Vehicles.bin");
	if (vHeader == NULL)LoadVehicles("Vehicles.txt");

	Customer c1 = { 1, "Carlos", "267543512", "Rua dos Robalos", 100654.57 };
	Manager m1 = { 1, "Rodrigo", "rodrisantos@gmail.pt", "yessir123" };
	Vehicle v1 = { 1, "Bicycle", 3.56, 26.48 };
	
	cHeader = NULL;
	mHeader = NULL;
	vHeader = NULL;

	cHeader = AddCustomer(cHeader, &c1);
	mHeader = AddManager(mHeader, &m1);
	vHeader = AddVehicle(vHeader, &v1);

	ShowCustomerList(cHeader);
}
