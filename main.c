/*Lăbău Cristea Andrei Liviu 314CB*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structuri.h"

int main() {
	char comanda[MAX_CMD_LEN];			
	scanf("%s", comanda);					// citire prima comanda
	char nameDB[MAX_DB_NAME_LEN];
	if(strcmp(comanda, "INIT_DB") == 0) {
		scanf("%s", nameDB);				// citire nume baza de date
	}
	t_db* dataBase = INIT_DB(nameDB);		// initializare baza de date
	if(dataBase == NULL) {
		printf("Cannot initialize data base\n");
	}

	while (read) { 							
		char comanda2[MAX_CMD_LEN];			// comanda CMD
		char nameTable[MAX_TABLE_NAME_LEN];	// nume tabel
		char nameType[7];					// tipul de date
		scanf("%s", comanda2);
		if(strcmp(comanda2, "CREATE") == 0) {
			scanf("%s", nameTable);			// citire nume tabel
			scanf("%s", nameType);			// citire tip de date
			CREATE(dataBase, nameTable, nameType); 	// creare tabel nou
		}
		if(strcmp(comanda2, "DELETE_DB") == 0) {	// stergere baza de date 
			free(dataBase->tables);					
			dataBase = NULL;
			break;									// opreste executie program
		}
		if(strcmp(comanda2, "PRINT_DB") == 0) {
			PRINT_DB(*dataBase);					// afisarea bazei de date
		}
		if(strcmp(comanda2, "PRINT") == 0) {
			scanf("%s", nameTable);					// citire nume tabel
			PRINT(*dataBase, nameTable);			// afisare tabel
		}
		if(strcmp(comanda2, "ADD") == 0) {
			scanf("%s", nameTable);					// citire nume tabel
			ADD(dataBase, nameTable);				// adaugare tabel in baza
		}
		if(strcmp(comanda2, "CLEAR") == 0) {
			scanf("%s", nameTable);					// citire nume tabel
			CLEAR(dataBase, nameTable);				// stergere linii tabel
		}
		if(strcmp(comanda2, "DELETE") == 0) {
			char comenzi[4][BUF_SIZE];				
			char buffer[BUF_SIZE];
			int nrArgs = 0;							// numara argumentele date
			while(!fgets(buffer, BUF_SIZE, stdin));	// citire buffer comenzi
			char* p;
			p = strtok(buffer, " \n");			// impart bufferul in tokens
			while(p) { 							// cat timp am un token
				strcpy(comenzi[nrArgs], p);		// copiez token intr-un vector
				nrArgs++;						// incrementez nr. de comenzi
				p = strtok(NULL, " \n");		// trec la urmatorul token
			}
			if(nrArgs == 1) {					// daca functia are 1 argument
				DELETE(dataBase, comenzi[0]);	// apel stergere tabel
			}
			else {								// daca functia are 4 argumente
				char* auxS = malloc(BUF_SIZE * sizeof(char)); 	// string aux.
				if(auxS == NULL) {							 	
					break;										
				}
				memcpy(auxS, comenzi[1], BUF_SIZE); 
				char* spaces = malloc(MAX_COLUMN_NAME_LEN * sizeof(char));
				if(spaces == NULL) {
					break;
				}
				strcat(spaces, GetSpaces(auxS)); 	// string de padding ' '
				strcat(auxS, spaces);				// adaug padding la string
				DELETESELECT(dataBase, comenzi[0], auxS, comenzi[2],
				comenzi[3], comenzi[1]);			// apel stergere selectiva
				free(auxS);
				free(spaces);
			}
		}
		if(strcmp(comanda2, "SEARCH") == 0) {
			char comenzi[4][BUF_SIZE];
			char buffer[BUF_SIZE];
			int nrArgs = 0;							// numara argumentele date
			while(!fgets(buffer, BUF_SIZE, stdin)); // citire buffer comenzi
			char* p;
			p = strtok(buffer, " \n");			// impart bufferul in tokens
			while(p) {							// cat timp am un token
				strcpy(comenzi[nrArgs], p); 	// copiez token intr-un vector
				nrArgs++;						// incrementez nr. de comenzi
				p = strtok(NULL, " \n");		// trec la urmatorul token
			}
			char* auxS = malloc(BUF_SIZE * sizeof(char));	// string aux.
			if(auxS == NULL) {
				break;
			}
			memcpy(auxS, comenzi[1], BUF_SIZE);
			char* spaces = malloc(MAX_COLUMN_NAME_LEN * sizeof(char));
			if(spaces == NULL) {
				break;
			}
			strcat(spaces, GetSpaces(auxS));		// string de padding ' '
			strcat(auxS, spaces);					// adaug padding la string
			SEARCH(*dataBase, comenzi[0], auxS,		// apel cautare selectiva
			comenzi[2], comenzi[3], comenzi[1]);
			free(spaces);
			free(auxS);
		}
	}
	return 0;
}
