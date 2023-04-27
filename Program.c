/*****************************************************************//**
 * \file   Program.c
 * \brief  Função main para correr o codigo
 * 
 * \author Eduardo
 * \date   March 2023
 *********************************************************************/

#include "Globals.h"

int main() {
	Customer* cHeader = LoadCustomers("Customers.txt");
	Manager* mHeader = LoadManagers("Managers.txt");
	Vehicle* vHeader = LoadVehicles("Vehicles.txt");

	Customer c1 = { 1, "Carlos", "267543512", "Rua dos Robalos", 100654.57 };
	Manager m1 = { 1, "Rodrigo", "rodrisantos@gmail.pt", "yessir123" };
	Vehicle v1 = { 1, "Bicycle", 3.56, 26.48 };
	
	//cHeader = NULL;
	//mHeader = NULL;
	//vHeader = NULL;

	cHeader = AddCustomer(cHeader, &c1);
	mHeader = AddManager(mHeader, &m1);
	vHeader = AddVehicle(vHeader, &v1);

	ShowCustomerList(cHeader);
}
