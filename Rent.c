/*****************************************************************//**
 * \file   Rent.c
 * \brief  
 * 
 * \author Eduardo
 * \date   April 2023
 *********************************************************************/

#include "Globals.h"
//
//int countLeapYears(Date d) {
//	int years = d.year;
//	int res;
//
//	if (d.month <= 2)years--;
//
//	res = years / 4 - years / 100 + years / 400;
//
//	return res;
//}
//
//int getDifference(Date dt1, Date dt2) {
//	//Contar dias totais da primeira data 
//	long int n1 = dt1.year * 365 + dt1.day;
//
//	for (int i = 0; i < dt1.month - 1; i++) {
//		n1 += monthDays[i];
//	}
//
//	n1 += countLeapYears(dt1);
//	//Contar dias totais da segunda data
//	long int n2 = dt2.year * 365 + dt2.day;
//
//	for (int i = 0; i < dt2.month - 1; i++) {
//		n2 += monthDays[i];
//	}
//
//	n2 += countLeapYears(dt2);
//
//	return (n2 - n1);
//}
//
//
//float CostCalc(Vehicle* v, Date start, Date end) {
//	Vehicle* aux = v;
//	float res = 0;
//	float days = getDifference(start, end);
//
//	res = (days/7) * v->price;
//
//	return res;
//}
//
//
//Rent* CreateRent(Customer* customer, Vehicle* vehicle, Date start, Date end){
//	Rent* new = (Rent*)malloc(sizeof(Rent));
//	if (new == NULL)return NULL;
//
//	new->customer = *customer;
//	new->vehicle = *vehicle;
//	new->dateStart = start;
//	new->dateEnd = end;
//	new->cost = CostCalc(vehicle, start, end);
//
//	return new;
//}
//
//
//RentList* AddRent(RentList* h, Rent* new) {
//	if (new == NULL)return h;
//
//	if (h == NULL) {
//		h = new;
//		return h;
//	}
//	else {
//		RentList* aux = h;
//		RentList* prev = aux;
//
//		while (aux != NULL && new->customer.id < aux->rent.customer.id) {
//			prev = aux;
//			aux = aux->next;
//		}
//		if (aux = h) {
//			new->next = h;
//			h = new;
//		}
//		else {
//			new->next = aux;
//			prev->next = new;
//		}
//	}
//	return h;
//}
//
//RentList* AddRentType(RentList* h, char* type) {
//	if (h == NULL)return NULL;
//
//	RentList* aux = h;
//	RentList* final = NULL;
//
//	while (aux != NULL) {
//		if (strcmp(aux->rent.vehicle.type, type) == 0) {
//			final = AddRent(final, &aux->rent);
//		}
//		aux = aux->next;
//	}
//	return final;
//}
//
//bool SaveRentsBin(RentList* h, char fileName[]) {
//	if (h == NULL)return false;
//	RentList* aux = h;
//
//	FILE* fp;
//	fp = fopen(fileName, "wb");
//	if (fp == NULL)return false;
//
//	while (aux != NULL) {
//		aux->next = NULL;
//		fwrite(aux, 1, sizeof(aux->rent), fp);
//		aux = aux->next;
//	}
//	fclose(fp);
//	return true;
//}
