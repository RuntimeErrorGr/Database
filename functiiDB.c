/*Lăbău Cristea Andrei Liviu 314CB*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structuri.h"

/* Adauga padding de ' ' unui string pana la valoarea MAX_COLUMN_NAME_LEN.
 * Primeste ca parametru un string.
 * Returneaza un string cu padding sau NULL.
*/
char* GetSpaces(char* name) {
	char* spaces = malloc(MAX_COLUMN_NAME_LEN * sizeof(char));
	if(spaces == NULL) {
		return NULL;
	}
	int lenName = strlen(name);	
	int nrSpaces = MAX_COLUMN_NAME_LEN + 1 - lenName; 	// determin nr. necesar
	int i = 0;
	while (i < nrSpaces) {								
		strcat(spaces, " ");						 	// formez string de ' '
		i++;
	}
	return spaces;	
}
/* Aloca o celula de tip generic.
 * Returneaza adresa celulei create sau NULL.
*/
TListGCell AlocGCells(void* value) {
	TListGCell aux = (TListGCell)malloc(sizeof(t_gCell));
	if(!aux) {
		return NULL;
	}
	aux -> value = value;
	aux -> next = NULL;
	return aux;
}
/* Aloca o celula cu info de tip string.
 * Returneaza adresa celulei create sau NULL.
*/
t_stringCell* AlocStringCell(char* value) {
	size_t size = strlen(value) + 1;
	t_stringCell* aux = malloc(sizeof(t_stringCell) + size);
	if(!aux) {
		return NULL;	
	}
	memcpy(aux -> value, value, size);
	aux -> next = NULL;
	return aux;
}
/* Aloca o celula cu info de tip int.
 * Returneaza adresa celulei create sau NULL.
*/
t_intCell* AlocIntCell(int value) {
	t_intCell* aux = (t_intCell*)malloc(sizeof(t_intCell));
	if(!aux) {
		return NULL;	
	}
	aux -> value = value;
	aux -> next = NULL;
	return aux;
}
/* Aloca o celula cu info de tip float.
 * Returneaza adresa celulei create sau NULL.
*/
t_floatCell* AlocFloatCell(float value) {
	t_floatCell* aux = (t_floatCell*)malloc(sizeof(t_floatCell));
	if(!aux) {
		return NULL;	
	}
	aux -> value = value;
	aux -> next = NULL;
	return aux;
}
/* Aloca o celula de tip linie string.
 * Returneaza adresa liniei create sau NULL.
*/
t_stringLine* AlocStringLine() {
	t_stringLine* auxL = (t_stringLine*)malloc(sizeof(t_stringLine));
	if(!auxL) {
		return NULL;
	}
	auxL -> cells = NULL;
	auxL -> next = NULL;
	return auxL;
}
/* Aloca o celula de tip linie int.
 * Returneaza adresa celulei create sau NULL.
*/
t_intLine* AlocIntLine() {
	t_intLine* auxL = (t_intLine*)malloc(sizeof(t_intLine));
	if(!auxL) {
		return NULL;
	}
	auxL -> cells = NULL;
	auxL -> next = NULL;
	return auxL;
}
/* Aloca o celula de tip linie float.
 * Returneaza adresa liniei create sau NULL.
*/
t_floatLine* AlocFloatLine() {
	t_floatLine* auxL = (t_floatLine*)malloc(sizeof(t_floatLine));
	if(!auxL) {
		return NULL;
	}
	auxL -> cells = NULL;
	auxL -> next = NULL;
	return auxL;
}
/* Aloca o celula de tip coloana.
 * Returneaza adresa coloanei sau NULL.
*/
t_columnL AlocColumnL(char name[MAX_COLUMN_NAME_LEN]) {
	t_columnL auxC = (t_columnL)malloc(sizeof(t_column));
	if(!auxC) {
		return NULL;
	}
	strcpy(auxC -> name, name);
	auxC -> next = NULL;
	return auxC;
}
/* Construieste o lista de celule coloana cu nume citite de la stdin.
*/
t_columnL ReadColumnsL() {
  t_columnL L = NULL, u, aux;
  char buffer[BUF_SIZE];
  while(!fgets(buffer, BUF_SIZE, stdin));	// citire buffer nume coloane
  char *p;
  p = strtok(buffer, " \n");				// impart bufferul in tokens
  while(p) {								// cat timp am un token
  	char* auxS = malloc(BUF_SIZE * sizeof(char));	// string auxiliar
  	if(auxS == NULL) {								// alocare esuata
  		return L;							// returnez adresa listei
  	}
  	memcpy(auxS, p, BUF_SIZE);
  	char* spaces = malloc(MAX_COLUMN_NAME_LEN * sizeof(char));
  	if(spaces == NULL) {
  		return L;
  	}
  	strcat(spaces, GetSpaces(auxS));		// string de padding ' '
  	strcat(auxS, spaces);					// adaug padding la string
    aux = AlocColumnL(auxS);        		// aloc celula auxiliara
    if(!aux) {									// alocare esuata
    	return L;            	 				// returnez adresa listei
    }
    free(spaces);
    free(auxS);
    if(L == NULL) {							// daca lista e vida
    	L = aux;							// aux devine capul de lista
    }
    else {									// altfel
    	u -> next = aux;					// inserez aux la finalul listei
    } 
    u = aux;								// actualizez finalul listei
    p = strtok(NULL, " \n");				// trec la urmatorul token
  }
  return L;                     			// returnez lista rezultat 
}
/* Construieste o lista de celule int citite de la stdin.
 * Returneaza adresa celulei.
*/
TListIntCell ReadIntCells() {
	TListIntCell L = NULL, u, aux;
	int x;
	for(;scanf("%d", &x) == 1;) {	// cat timp se citesc valori
		aux = AlocIntCell(x);		// aloc celula auxiliara
		if(!aux) {						// alocare esuata
			return L;					// returnez adresa listei
		}
		if(L == NULL) {				// daca lista e goala
			L = aux;				// aux devine capul de lista
		}
		else {						// altfel
			u -> next = aux;		// inserez aux la finalul lista
		}
		u = aux;					// actualizez finalul de lista
	}
	return L;						// returnez lista rezultat
}
/* Construieste o lista de celule float citite de la stdin.
*/
TListFloatCell ReadFloatCells() {
	TListFloatCell L = NULL, u, aux;
	float x;
	for(;scanf("%f", &x) == 1;) {	// cat timp se citesc valori
		aux = AlocFloatCell(x);		// aloc celula auxiliara
		if(!aux) {						// alocare esuata
			return L;					// returnez adresa listei
		}
		if(L == NULL) {				// daca lista e goala
			L = aux;				// aux devine capul de lista
		}		
		else {						// altfel	
			u -> next = aux;		// inserez aux la finalul lista
		}
		u = aux;					// actualizez finalul de lista
	}
	return L;						// returnez lista rezultat
}
/* Construieste o lista de celule string citite de la stdin.
*/
TListGCell ReadStringCells() {
  TListGCell L = NULL, u, aux;
  char buffer[BUF_SIZE];
  while(!fgets(buffer, BUF_SIZE, stdin));	// citire buffer nume coloane
  char* p;
  p = strtok(buffer, " \n");				// impart bufferul in tokens
  while(p) {								// cat timp am un token
    aux = AlocGCells(p);        			// aloc celula auxiliara
    if(!aux) {									// alocare esuata
    	return L;            	 				// returnez adresa listei
    }
    if(L == NULL) {							// daca lista e vida
    	L = aux;							// aux devine capul de lista
    }
    else {									// altfel
    	u -> next = aux;					// inserez aux la finalul listei
    } 	
    u = aux;								// actualizez finalul listei
    p = strtok(NULL, " \n");				// trec la urmatorul token
  }
  return L;                     			// returnez lista rezultat 
}
/* Construieste o lista de celule linie int.
*/
TListIntLine ReadIntLine() {
	TListIntLine L = NULL, u = NULL, aux;
	aux = AlocIntLine();					// aloc linie auxiliara
	aux -> cells = ReadIntCells();			// aloc + citesc lista celule
	if(!aux) {									// alocare esuata
		return L;								// returnez adresa listei
	}
	if(L == NULL) {							// daca lista e vida
		L = aux;							// aux devine capul de lista
	}
	else {									// altfel
		u -> next = aux;					// inserez aux la finalul listei
	}
	u = aux;								// actualizez finalul listei
	return L;								// returnez lista rezultat 
}
/* Determina tipul datelor pe care le va contine un tabel:
 * nameType INT/FLOAT/STRING
*/
t_cellType InfoType(char* nameType) {
	t_cellType type;
	if(strcmp(nameType, "INT") == 0) {
		type = INT;
	}
	else if(strcmp(nameType, "FLOAT") == 0) {
		type = FLOAT;
	}
	else if(strcmp(nameType, "STRING") == 0) {
		type = STRING;
	}
	else {
		type = -1;
		printf("Unknown data type: \"%s\".\n", nameType);
	}
	return type;
}
/* Aloca un tabel cu:
 * numele name,
 * tipul de date nameType.
 * Returneaza adresa tabelului sau NULL.
*/
t_table* AlocTable(char name[MAX_TABLE_NAME_LEN], char nameType[7]) {
	t_table* auxT = (t_table*)malloc(sizeof(t_table));
	if(!auxT) {   					                                    
		return NULL;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
	}
	strcpy(auxT -> name, name);				// actualizez numele 
	auxT -> type = InfoType(nameType);		// actualizez tipul de informatie
	auxT -> columns = ReadColumnsL(); 		// actualizez lista de coloane
	if(auxT -> type == INT) {
		auxT -> lines = NULL;				// actualizez pointerul lines 
	}
	if(auxT -> type == FLOAT) {
		auxT -> lines = NULL;				// actualizez pointerul lines
	}
	if(auxT -> type == STRING) {
		auxT -> lines = NULL;				// actualizez pointerul lines
	}
	auxT -> next = NULL;					// actualizez pointerul next
	return auxT;
}
/* Aloca baza de date cu:
 * numele nameDB.
 * Returneaza adresa bazei de date sau NULL.
*/
t_db* INIT_DB(char* nameDB) {
	t_db* dataBase = (t_db*)calloc(sizeof(t_db), 1);
	if(!dataBase) {
		printf("Eroare alocare baza de date\n");
		return NULL;
	}
	strcpy(dataBase->name, nameDB);
	dataBase -> tables = NULL;
	return dataBase;
}
/* Creeaza un tabel cu: 
 * numele name,
 * tipul de date nameType.
 * Returneaza 1 succes / 0 nu s-a putut insera.
*/
int CREATE(t_db* db, char name[MAX_TABLE_NAME_LEN], char nameType[7]) {
	t_table* table = AlocTable(name, nameType);		// aloc tabel
	if(!table) {
		return 0;
	}
	if(db -> tables == NULL) { 						// daca baza este goala
		db -> tables = table;						// inserez primul tabel
	}
	else {											// altfel
		t_table* p = db -> tables;
		if(strcmp(p -> name, name) == 0) {			// tabelul exista deja
				printf("Table \"%s\" already exists\n", name);
				return 0;
			}
		for( ; p->next != NULL; p = p -> next ) {		// verific fiecare tabel
			if(strcmp(p -> next -> name, name) == 0) { 	// tabelul exista deja
				printf("Table \"%s\" already exists\n", name);
				return 0;
			}
		}
		p -> next = table;								// inserez tabel
	}
	return 1;
}
/* Sterge un tabel cu:
 * numele name, 
 * din baza de date db.
 * Returneaza 1 succes / 0 nu s-a putut sterge.
*/
int DELETE(t_db* db, char name[MAX_TABLE_NAME_LEN]) {
	if(db -> tables == NULL) {					// baza este vida			
		printf("Table \"%s\" not found in database.\n", name);
		return 0;
	}
	else {
		t_table* p = db -> tables; 				// retin capul de lista
		t_table* ant;							// retin tabelul anterior
		if(p -> next == NULL) {  				// baza contine un singur tabel
			if(strcmp(p -> name, name) == 0) { 	// numele este cel cautat
				free(p -> columns);
				free(p -> lines);
				free(p);
				db -> tables = NULL;
				return 1;
			}
			else {								// tabelul nu exista in baza
				printf("Table \"%s\" not found in database.\n", name);
				return 0;
			}
		}
		else { 									// baza contine mai multe tabele			
			for(ant = NULL ; p != NULL; ant = p, p = p -> next) { 
				if(strcmp(p -> name, name) == 0) {	// numele este cel cautat
					if(ant == NULL) {				// primul tabel
						db -> tables = p -> next;	// refac leg. cu baza
						free(p -> columns);
						free(p -> lines);
						free(p);
					}
					else {							// tabel diferit de primul
						ant -> next = p -> next;	// refac legatura cu baza
						free(p -> columns);
						free(p -> lines);
						free(p);
					}
					return 1;
				}
				if(p -> next == NULL) {				// tabelul nu exista in baza
					printf("Table \"%s\" not found in database.\n", name);
				return 0;
				}
			}
			return 0; 
		}
	}
}
/* Afiseaza baza de date db.
*/
void PRINT_DB(t_db db) {
	printf("DATABASE: %s\n", db.name);		// afisez numele bazei de date
	printf("\n");
	t_table* aux = db.tables;
	for(; aux != NULL; aux = aux->next) {	// iterez lista de tabele
		int nrCols = 0;						// retin cate coloane are fiecare
		printf("TABLE: %s\n", aux->name);	// afisez numele tabelului curent
		t_column* auxC = aux->columns;
		for(; auxC !=NULL; auxC  = auxC ->next) {	// iterez lista de coloane
			nrCols++;								// incrementez nr. coloane
			printf("%s", auxC -> name);				// afisez nume coloane
		}
		printf("\n");
		int k = 0;							// folosesc un contor pt " "
		while(k < nrCols) {					// cat timp mai am coloane
			int q = 0;						// folosesc alt contor pt "-"
			while(q < MAX_COLUMN_NAME_LEN) { 	// cat timp mai am caractere
				printf("-");					// afisez "-"
				q++;							// incrementez contor
			}
			printf(" ");						// afisez " "
			k++;								// incrementez contor
		}
		printf("\n");
		if(aux -> type == INT) {				// daca tipul de date este INT
			if(aux -> lines != NULL) {			// daca am linii in tabel
				t_intLine* auxL =  aux -> lines;
				for(; auxL != NULL; auxL = auxL -> next) { 	// iterez liniile
					t_intCell* auxCell = auxL -> cells;		// iterez celulele
					for(; auxCell != NULL; auxCell = auxCell -> next) {
						printf("%d", auxCell -> value); 	// afiseaza celula
						char string[BUF_SIZE];
						sprintf(string, "%d", auxCell -> value);
						char* spaces = GetSpaces(string);
						printf("%s", spaces);				// adaugare padding
					}
					printf("\n");		
				}
				printf("\n");
			}
			else {								// daca nu am linii in tabel
				printf("\n");					// afiseaza new line
			}
		}
		if(aux->type == FLOAT) {				// daca tipul de date este FLOAT		
			if(aux -> lines != NULL) {			// daca am linii in tabel
				t_floatLine* auxL =  aux -> lines;
				for(; auxL != NULL; auxL = auxL -> next) { 	// iterez liniile
					t_floatCell* auxCell = auxL -> cells;	// iterez celulele
					for(; auxCell != NULL; auxCell = auxCell -> next) {
						printf("%f",auxCell -> value); 		// afiseaza celula
						char string[BUF_SIZE];
						sprintf(string, "%f", auxCell -> value);
						char* spaces = GetSpaces(string);
						printf("%s", spaces);				// adaugare padding
					}
					printf("\n");
				}
				printf("\n");
			}
			else {							// daca nu am linii in tabel
				printf("\n");				// afiseaza new line
			}
		}	
		if(aux->type == STRING) {			// daca tipul de date este STRING
			t_stringLine* auxL = (t_stringLine*)aux -> lines;
			for(; auxL != NULL; auxL = auxL -> next) { 		// iterez liniile
				t_stringCell* p;
  				for(p = auxL -> cells; p != NULL; p = p -> next) {
    				printf("%s",p -> value);            	// iterez celulele
    				printf("%s",GetSpaces(p -> value));		// adaugare padding
				}
				printf("\n");
			}
			printf("\n");
		}
	}	
}
/* Afiseaza tabelul cu:
 * numele name,
 * din baza de date db.
*/
void PRINT(t_db db, char name[MAX_TABLE_NAME_LEN]) {
	t_table* aux = db.tables;
	for(; aux != NULL; aux = aux->next)			// iterez lista de tabele 
		if(strcmp(aux->name, name) == 0) 		// tabelul are numele cautat
			break;								// opresc iterarea
	if(aux == NULL) {							// nu a fost gasit niciun tabel
		printf("Table \"%s\" not found in database.\n", name);
	}
	else {
		int nrCols = 0;							// nr. de coloane din tabel
		printf("TABLE: %s\n", aux->name);		// afisez numele tabelului
		t_column* auxC = aux->columns;
		for(; auxC !=NULL; auxC  = auxC -> next) {	// iterez coloanele
			nrCols++;								// incrementez nr. coloane
			printf("%s", auxC -> name);				// afisez nume coloane
		}	
		printf("\n");
		int k = 0;							// folosesc un contor pt " "
		while(k < nrCols) {					// cat timp mai am coloane
			int q = 0;						// folosesc alt contor pt "-"
			while(q < MAX_COLUMN_NAME_LEN) {	// cat timp mai am caractere
				printf("-");					// afisez "-"
				q++;							// incrementez contor
			}
			printf(" ");						// afisez " "
			k++;								// incrementez contor
		}
		printf("\n");
		if(aux -> type == INT) {				
			if(aux -> lines != NULL) {			// daca am linii in tabel
				t_intLine* auxL =  aux -> lines;
				for(; auxL != NULL; auxL = auxL ->next) { 	// iterez liniile
					t_intCell* auxCell = auxL -> cells;		// iterez celulele
					for(; auxCell != NULL; auxCell = auxCell -> next) {
						printf("%d", auxCell -> value); 	// afisez celula
						char string[BUF_SIZE];
						sprintf(string, "%d", auxCell -> value);
						char* spaces = GetSpaces(string);	
						printf("%s", spaces);				// adaugare padding
					}
					printf("\n");		
				}
				printf("\n");
			}
			else {								// daca nu am linii in tabel
				printf("\n");					// afisare new line
			}
		}
		if(aux->type == FLOAT) {				
			if(aux -> lines != NULL) {				// daca am linii in tabel
				t_floatLine* auxL =  aux -> lines;
				for(; auxL != NULL; auxL = auxL ->next) { 	// iterez liniile
					t_floatCell* auxCell = auxL -> cells;	// iterez celulele
					for(; auxCell != NULL; auxCell = auxCell -> next) {
						printf("%f",auxCell -> value); 		// afisez celula
						char string[BUF_SIZE];
						sprintf(string, "%f", auxCell -> value);
						char* spaces = GetSpaces(string);
						printf("%s", spaces);				// adaugare padding
					}
					printf("\n");
				}
				printf("\n");
			}
			else {									// daca nu am linii in tabel
				printf("\n");						// afisare new line
			}
		}	
		if(aux->type == STRING) {				
			t_stringLine* auxL = (t_stringLine*)aux -> lines;
			for(; auxL != NULL; auxL = auxL -> next) { 		// iterez liniile
				t_stringCell* p;							// iterez celulele  
  				for(p = auxL -> cells; p != NULL; p = p -> next) {  
    				printf("%s",p -> value);            	// afiseaza celula
    				char* spaces = GetSpaces(p->value);
    				printf("%s",spaces); 					// adaugare padding
				}
				printf("\n");
			}
			printf("\n");
		}
	}	
}
/* Adauga o noua linie in tabelul cu:
 * numele nameTable,
 * din baza de date db.
*/
int ADD(t_db* db, char nameTable[MAX_TABLE_NAME_LEN]) {
	t_table* aux = db -> tables;
	for(; aux != NULL; aux = aux -> next) 			// iterez lista de tabele
		if(strcmp(aux -> name, nameTable) == 0) 	// am gasit tabelul cautat
			break;
	if(aux == NULL) {								// nu am gasit niciun tabel
		printf("Table \"%s\" not found in database.\n", nameTable);
		return 0;
	}
	else {					
		if(aux -> type == INT) {
			if(aux -> lines == NULL) {					// tabelul este gol
				t_intLine* aux2 = AlocIntLine();		// aloc celula tip linie
				if(aux2 == NULL) {
					return 0;
				}
				t_intCell* auxCell = ReadIntCells();	// aloc si citesc celule
				if(auxCell == NULL) {
					return 0;
				}
				aux2 -> cells = auxCell;				
				aux -> lines = aux2;					
			}
			else {										// tabelul contine linii
				t_intLine* aux2 = (t_intLine*)aux -> lines; 
				for(; aux2 ->next != NULL; aux2 = aux2 -> next);
				t_intLine* aux3 = AlocIntLine();		// aloc celula tip linie
				if(aux3 == NULL) {
					return 0;
				}
				aux2 -> next = aux3;
				aux3 -> cells = ReadIntCells();			// aloc si citesc celule
				return 1;
			}
		}
		else if(aux -> type == FLOAT) {
			if(aux -> lines == NULL) {					// tabelul este gol
				t_floatLine* aux2 = AlocFloatLine();	// aloc celula tip linie
				if(aux2 == NULL) {
					return 0;
				}
				t_floatCell* auxCell = ReadFloatCells();// aloc si citesc celule
				if(auxCell == NULL) {
					return 0;
				}
				aux2 -> cells = auxCell;
				aux -> lines = aux2;
			}
			else {										// tabelul contine linii
				t_floatLine* aux2 = (t_floatLine*)aux -> lines;
				for(; aux2 ->next != NULL; aux2 = aux2 -> next);
				t_floatLine* aux3 = AlocFloatLine();	// aloc celula tip linie
				if(aux3 == NULL) {
					return 0;
				}
				aux2 -> next = aux3;
				aux3 -> cells = ReadFloatCells();		// aloc si citesc celule
				return 1;
			}
		}
		else if(aux -> type == STRING) {
			t_stringLine* aux2 = AlocStringLine();		// aloc celula tip linie
			if(aux -> lines == NULL) {					// tabelul este gol
				aux -> lines = aux2;
				TListGCell u;
				char buffer[BUF_SIZE];
				while(!fgets(buffer, BUF_SIZE, stdin));	// citire buffer info
				char* p;
				p = strtok(buffer, " \n");				// impart bufferul	
				while(p) {								// cat timp am un token
					char* auxP = malloc(BUF_SIZE * sizeof(char));
					if(auxP == NULL) {
						return 0;
					}
					memcpy(auxP, p, BUF_SIZE);
					char* spaces = malloc(MAX_COLUMN_NAME_LEN * sizeof(char));
					if(spaces == NULL) {
						return 0;
					}
					strcat(spaces, GetSpaces(auxP));	// string de padding ' '
					strcat(auxP, spaces);				// adaug padding
					t_gCell* auxCell = AlocGCells(auxP);// aloc o noua celula
					if(!auxCell) {
    					return 0;            	 
    				}
    				if(aux2 -> cells == NULL) {			// daca linia e goala
    					aux2 -> cells = (t_stringCell*)auxCell;
    					u = auxCell;					// inserez prima celula
    				}
    				else {								// altfel
    					u -> next = auxCell;			// inserez la final
    					u = auxCell;					// actualizez ultim. cel.
    				} 
    					p = strtok(NULL, " \n");		// urmatorul token
  					}
  					return 1;
  				}	 
			else {										// tabelul nu este gol
				t_stringLine* auxL = (t_stringLine*)aux -> lines;
				for(; auxL -> next != NULL; auxL = auxL -> next); 
				t_stringLine* aux3 = AlocStringLine();	// aloc o noua linie
				if(aux3 == NULL) {
					return 0;
				}
				auxL -> next = aux3;					// actualizez lista lines
				TListGCell u;
				char buffer[BUF_SIZE];
				while(!fgets(buffer, BUF_SIZE, stdin));	// citire buffer info
				char* p;
				p = strtok(buffer, " \n");				// impart buffer
				while(p) {								// cat timp am un token
					char* auxP = malloc(BUF_SIZE * sizeof(char));
					if(auxP == NULL) {
						return 0;
					}
					memcpy(auxP, p, BUF_SIZE);
					char* spaces = malloc(MAX_COLUMN_NAME_LEN * sizeof(char));
					if(spaces == NULL) {
						return 0;
					}
					strcat(spaces, GetSpaces(auxP));	// string de padding ' '
					strcat(auxP, spaces);				// adaug padding
					t_gCell* auxCell = AlocGCells(auxP);// aloc o noua celula
					if(!auxCell) {
    					return 0;            	 
    				}
    				if(aux3 -> cells == NULL) {			// daca linia este goala
    					aux3 -> cells = (t_stringCell*)auxCell; // inserez
    					u = auxCell;					// actualizez ultima cel.
    				}
    				else {								// linia nu este goala
    					u -> next = auxCell;			// inserez
    					u = auxCell;					// actualizez ultima cel.
    				} 
    				p = strtok(NULL, " \n");			// urmatorul token
    			}
    			return 1;
			}
		}
	}
	return 0;
}
/* Elimina toate liniile din tabelul cu:
 * numele name,
 * din baza de date db.
*/
void CLEAR(t_db* db, char name[MAX_TABLE_NAME_LEN]) {
	t_table* aux = db -> tables;
	for(; aux != NULL; aux = aux -> next) 			// iterez lista de tabele
		if(strcmp(aux->name, name) == 0) 			// am gasit un tabel
			break;									// stop
	if(aux == NULL) {								// nu am gasit niciun tabel
		printf("Table \"%s\" not found in database.\n", name);
	}
	if(aux -> type == INT) {
		t_intLine* auxL = aux -> lines;				
		while(auxL != NULL) {						// cat timp mai am linii
			t_intLine* aux2 = auxL;
			auxL = auxL -> next;
			free(aux2 -> cells);					// eliberez celulele
			aux2 -> cells = NULL;					// rup legatura cu linia
			free(aux2);
		}
		free(auxL);									// eliberez celulele
		aux -> lines = NULL;						// rup legatura cu tabelul
	}												
	if(aux -> type == FLOAT) {
		t_floatLine* auxL = aux->lines;
		while(auxL != NULL) {						// cat timp mai am linii
			t_floatLine* aux2 = auxL;
			auxL = auxL -> next;
			free(aux2 -> cells);					// eliberez celulele
			aux2 -> cells = NULL;					// rup legatura cu linia
			free(aux2);
		}
		free(auxL);									// eliberez celulele
		aux -> lines = NULL;						// rup legatura cu tabelul	
	}
	if(aux -> type == STRING) {
		t_stringLine* auxL = aux->lines;
		while(auxL != NULL) {						// cat timp mai am linii
			t_stringLine* aux2 = auxL;
			auxL = auxL -> next;
			free(aux2 -> cells);					// eliberez celulele
			aux2 -> cells = NULL;					// rup legatura cu linia
			free(aux2);
		}
		free(auxL);									// eliberez celulele
		aux -> lines = NULL;						// rup legatura cu tabelul
	}
}
/* Elimina toate liniile din tabelul nameT
 * pentru care valoarea value de pe coloana nameC
 * respecta conditia relation.
*/
int DELETESELECT(t_db* db, char nameT[MAX_TABLE_NAME_LEN],
char nameC[MAX_COLUMN_NAME_LEN], char relation[3], char* value, 
char noSpaces[MAX_COLUMN_NAME_LEN]) {
	t_table* aux = db -> tables;
	for(; aux != NULL; aux = aux -> next) 		// iterez lista de tabele
		if(strcmp(aux -> name, nameT) == 0) 	// am gasit tabelul
			break;								// stop
	if(aux == NULL) {							// nu am gasit niciun tabel
		printf("Table \"%s\" not found in database.\n", nameT);
		return 0;
	}
	t_column* auxCol = aux -> columns;
	int nrCol = 1;								// pozitia coloanei cautate
	for(; auxCol != NULL; auxCol = auxCol -> next) {	// iterez coloanele
		if(strcmp(auxCol -> name, nameC) == 0) {		// am gasit coloana
			break;
		}
		nrCol++;								// actualizez pozitia
	}
	if(auxCol == NULL) {						// nu am gasit nicio coloana
		printf("Table \"%s\" does not contain column \"%s\".\n", nameT, noSpaces);
		return 0;
	}
	if(aux -> type == INT) {
		t_intLine* auxL = (t_intLine*)aux -> lines;
		t_intLine* ant = NULL;
		t_intLine* p;
		for(; auxL != NULL; ) {				// iterez liniile tabelului
			t_intCell* auxCell;	
			if(auxL != NULL) 			
				auxCell = auxL -> cells;		
			else return 0; 					// tabelul nu contine nicio linie
			int i;
			for(i = 1; i < nrCol; i++) {	// iterez pana la pozitia coresp.
				auxCell = auxCell -> next;
			}
			if(strcmp(relation, "<") == 0) {	
				if(auxCell == NULL) {			// daca celula este vida
					return 0;					// stop
				}
				else if(auxCell -> value < atoi(value)) { 	
					p = auxL;
					auxL = auxL -> next;	// trec la urmatoarea linie
					if(ant != NULL) {		// daca nu am sters prima linie
						ant -> next = auxL; // refac leg. cu celula anterioara
					} 
					else {					// daca am sters prima linie
						aux -> lines = auxL;// actualizez pointerul lines
					}
					free(p);
				}
				else {						// daca conditia nu este respectata
					ant = auxL;				// linia ant devine linia curenta
					auxL = auxL -> next;	// trec la linia urmatoare
				}
			}
			if(strcmp(relation, "<=") == 0) {	
				if(auxCell == NULL) {			// daca celula este vida
					return 0;					// stop
				}
				else if(auxCell -> value <= atoi(value)) { 
					p = auxL;
					auxL = auxL -> next;	// trec la urmatoarea linie
					if(ant != NULL) {		// daca nu am sters prima linie
						ant -> next = auxL;	// refac leg. cu celula anterioara
					} 	
					else {					// daca am sters prima linie
						aux -> lines = auxL;// actualizez pointerul lines
					}
					free(p);
				}
				else {						// daca conditia nu este respectata
					ant = auxL;				// linia ant devine linia curenta
					auxL = auxL -> next;	// trec la linia urmatoare
				}
			}
			if(strcmp(relation, "==") == 0) {	
				if(auxCell == NULL) {			// daca celula este vida
					return 0;					// stop
				}
				else if(auxCell -> value == atoi(value)) {	
					p = auxL;
					auxL = auxL -> next;	// trec la urmatoarea linie
					if(ant != NULL) {		// daca nu am sters prima linie
						ant -> next = auxL;	// refac leg. cu celula anterioara
					} 
					else {
						aux -> lines = auxL;// actualizez pointerul lines
					}
					free(p);
				}
				else {						// daca conditia nu este respectata
					ant = auxL;				// linia ant devine linia curenta
					auxL = auxL -> next;	// trec la linia urmatoare
				}
			}
			if(strcmp(relation, "!=") == 0) {	
				if(auxCell == NULL) {			// daca celula este vida
					return 0;					// stop
				}
				else if(auxCell -> value != atoi(value)) {	
					p = auxL;
					auxL = auxL -> next;	// trec la urmatoarea linie
					if(ant != NULL) {		// daca nu am sters prima linie
						ant -> next = auxL;	// refac leg. cu celula anterioara
					} 
					else {
						aux -> lines = auxL;// actualizez pointerul lines
					}
					free(p);
				}
				else {						// daca conditia nu este respectata
					ant = auxL;				// linia ant devine linia curenta
					auxL = auxL -> next;	// trec la linia urmatoare
				}
			}
			if(strcmp(relation, ">=") == 0) {	
				if(auxCell == NULL) {			// daca celula este vida
					return 0;					// stop
				}
				else if(auxCell -> value >= atoi(value)) {
					p = auxL;
					auxL = auxL -> next;	// trec la urmatoarea linie
					if(ant != NULL) {		// daca nu am sters prima linie
						ant -> next = auxL;	// refac leg. cu celula anterioara
					} 
					else {
						aux -> lines = auxL;// actualizez pointerul lines
					}
					free(p);
				}
				else {						// daca conditia nu este respectata
					ant = auxL;				// linia ant devine linia curenta
					auxL = auxL -> next;	// trec la linia urmatoare
				}
			}
			if(strcmp(relation, ">") == 0) {	
				if(auxCell == NULL) {			// daca celula este vida
					return 0;					// stop
				}
				else if(auxCell -> value > atoi(value)) {	
					p = auxL;
					auxL = auxL -> next;	// trec la urmatoarea linie
					if(ant != NULL) {		// daca nu am sters prima linie
						ant -> next = auxL;	// refac leg. cu celula anterioara
					} 
					else {
						aux -> lines = auxL;// actualizez pointerul lines
					}
					free(p);
				}
				else {						// daca conditia nu este respectata
					ant = auxL;				// linia ant devine linia curenta
					auxL = auxL -> next;	// trec la linia urmatoare	
				}
			}
		}
	}
	if(aux -> type == FLOAT) {
		t_floatLine* auxL = (t_floatLine*)aux -> lines;
		t_floatLine* ant = NULL;
		t_floatLine* p = NULL;
		for(; auxL != NULL; ) {					// iterez liniile tabelului
			t_floatCell* auxCell;
			if(auxL != NULL) 
				auxCell = auxL -> cells;
			else return 0; 						// tabelul nu contine nicio linie
			int i;
			for(i = 1; i < nrCol; i++) {		// iterez pana la pozitia coresp.
				auxCell = auxCell -> next;
			}
			if(strcmp(relation, "<") == 0) {	// verific relatia de la stdin
				if(auxCell == NULL) {			// daca celula este vida
					return 0;					// stop
				}
				else if(auxCell -> value < atof(value)) {
					p = auxL;
					auxL = auxL -> next;	// trec la urmatoarea linie
					if(ant != NULL) {		// daca nu am sters prima linie
						ant -> next = auxL;	// refac leg. cu celula anterioara
					} 
					else {
						aux -> lines = auxL;// actualizez pointerul lines
					}
					free(p);
				}
				else {						// daca conditia nu este respectata
					ant = auxL;				// linia ant devine linia curenta
					auxL = auxL -> next;	// trec la linia urmatoare
				}
			}
			if(strcmp(relation, "<=") == 0) {	
				if(auxCell == NULL) {			// daca celula este vida
					return 0;					// stop
				}
				else if(auxCell -> value <= atof(value)) {
					p = auxL;
					auxL = auxL -> next;	// trec la urmatoarea linie				
					if(ant != NULL) {		// daca nu am sters prima linie
						ant -> next = auxL;	// refac leg. cu celula anterioara
					} 
					else {
						aux -> lines = auxL;// actualizez pointerul lines
					}
					free(p);
				}
				else {						// daca conditia nu este respectata
					ant = auxL;				// linia ant devine linia curenta
					auxL = auxL -> next;	// trec la linia urmatoare
				}
			}
			if(strcmp(relation, "==") == 0) {	
				if(auxCell == NULL) {			// daca celula este vida
					return 0;					// stop	
				}
				else if(auxCell -> value == atof(value)) {
					p = auxL;
					auxL = auxL -> next;	// trec la urmatoarea linie		
					if(ant != NULL) {		// daca nu am sters prima linie
						ant -> next = auxL;	// refac leg. cu celula anterioara
					} 
					else {
						aux -> lines = auxL;// actualizez pointerul lines	
					}
					free(p);
				}
				else {						// daca conditia nu este respectata
					ant = auxL;				// linia ant devine linia curenta
					auxL = auxL -> next;	// trec la linia urmatoare
				}
			}
			if(strcmp(relation, "!=") == 0) {	
				if(auxCell == NULL) {			// daca celula este vida
					return 0;					// stop	
				}
				else if(auxCell -> value != atof(value)) {
					p = auxL;
					auxL = auxL -> next;	// trec la urmatoarea linie
					if(ant != NULL) {		// daca nu am sters prima linie
						ant -> next = auxL;	// refac leg. cu celula anterioara
					} 
					else {
						aux -> lines = auxL;// actualizez pointerul lines	
					}
					free(p);
				}
				else {						// daca conditia nu este respectata
					ant = auxL;				// linia ant devine linia curenta
					auxL = auxL -> next;	// trec la linia urmatoare	
				}
			}
			if(strcmp(relation, ">=") == 0) {	
				if(auxCell == NULL) {			// daca celula este vida
					return 0;					// stop		
				}
				else if(auxCell -> value >= atof(value)) {
					p = auxL;
					auxL = auxL -> next;	// trec la urmatoarea linie
					if(ant != NULL) {		// daca nu am sters prima linie
						ant -> next = auxL;	// refac leg. cu celula anterioara
					} 
					else {
						aux -> lines = auxL;// actualizez pointerul lines	
					}
					free(p);
				}
				else {						// daca conditia nu este respectata
					ant = auxL;				// linia ant devine linia curenta
					auxL = auxL -> next;	// trec la linia urmatoare	
				}
			}
			if(strcmp(relation, ">") == 0) {	
				if(auxCell == NULL) {			// daca celula este vida
					return 0;					// stop	
				}
				else if(auxCell -> value > atof(value)) {
					p = auxL;
					auxL = auxL -> next;	// trec la urmatoarea linie
					if(ant != NULL) {		// daca nu am sters prima linie
						ant -> next = auxL;	// refac leg. cu celula anterioara
					} 
					else {
						aux -> lines = auxL;// actualizez pointerul lines
					}
					free(p);
				}	
				else {						// daca conditia nu este respectata
					ant = auxL;				// linia ant devine linia curenta
					auxL = auxL -> next;	// trec la linia urmatoare		
				}	
			}
		}
	}
	if(aux -> type == STRING) {
		t_stringLine* auxL = (t_stringLine*)aux -> lines;
		t_stringLine* ant = NULL;
		t_stringLine* p = NULL;
		for(; auxL != NULL; ) {				// iterez liniile tabelului
			t_stringCell* auxCell;
			if(auxL != NULL) 
				auxCell = auxL -> cells;
			else return 0; 					// tabelul nu contine nicio linie
			int i;
			for(i = 1; i < nrCol; i++) {	// iterez pana la pozitia coresp.
				auxCell = auxCell -> next; 	
			}
			if(strcmp(relation, "<") == 0) {
				char* padValue = malloc(BUF_SIZE * sizeof(char));
				if(padValue == NULL) {
					return 0;
				}
				memcpy(padValue, value, BUF_SIZE);
				char* spaces = malloc(MAX_COLUMN_NAME_LEN * sizeof(char));
				if(spaces == NULL) {
					return 0;
				}
				strcat(spaces, GetSpaces(padValue));	// formez padding
				strcat(padValue, spaces);				// adaug padding
				if(strcmp(auxCell -> value, padValue) < 0) {
					if(auxCell == NULL) {
						return 0;
					}
					p = auxL;						
					auxL = auxL -> next;	// trec la urmatoarea linie
					if(ant != NULL) {		// daca nu am sters prima linie
						ant -> next = auxL;	// refac leg. cu celula anterioara	
					} 
					else {
						aux -> lines = auxL;// actualizez pointerul lines
					}
					free(p);
				}
				else {						// daca conditia nu este respectata
					ant = auxL;				// linia ant devine linia curenta
					auxL = auxL -> next;	// trec la linia urmatoare	
				}
			}
			if(strcmp(relation, "<=") == 0) {
				char* padValue = malloc(BUF_SIZE * sizeof(char));
				if(padValue == NULL) {
					return 0;
				}
				memcpy(padValue, value, BUF_SIZE);
				char* spaces = malloc(MAX_COLUMN_NAME_LEN * sizeof(char));
				if(spaces == NULL) {
					return 0;
				}
				strcat(spaces, GetSpaces(padValue));	// formez padding
				strcat(padValue, spaces);				// adaug padding
				if(strcmp(auxCell -> value, padValue) <= 0) {
					if(auxCell == NULL) {
						return 0;
					}
					p = auxL;
					auxL = auxL -> next;	// trec la urmatoarea linie
					if(ant != NULL) {		// daca nu am sters prima linie
						ant -> next = auxL;	// refac leg. cu celula anterioara	
					} 
					else {
						aux -> lines = auxL;// actualizez pointerul lines	
					}
					free(p);
				}
				else {						// daca conditia nu este respectata
					ant = auxL;				// linia ant devine linia curenta
					auxL = auxL -> next;	// trec la linia urmatoare		
				}
			}
			if(strcmp(relation, "==") == 0) {
				char* padValue = malloc(BUF_SIZE * sizeof(char));
				if(padValue == NULL) {
					return 0;
				}
				memcpy(padValue, value, BUF_SIZE);
				char* spaces = malloc(MAX_COLUMN_NAME_LEN * sizeof(char));
				if(spaces == NULL) {
					return 0;
				}
				strcat(spaces, GetSpaces(padValue));	// formez padding
				strcat(padValue, spaces);				// adaug padding
				if(strcmp(auxCell -> value, padValue) == 0) {
					if(auxCell == NULL) {
						return 0;
					}
					p = auxL;
					auxL = auxL -> next;	// trec la urmatoarea linie
					if(ant != NULL) {		// daca nu am sters prima linie
						ant -> next = auxL;	// refac leg. cu celula anterioara
					} 
					else {
						aux -> lines = auxL;// actualizez pointerul lines	
					}
					free(p);
				}
				else {						// daca conditia nu este respectata
					ant = auxL;				// linia ant devine linia curenta
					auxL = auxL -> next;	// trec la linia urmatoare
				}
			}
			if(strcmp(relation, "!=") == 0) {
				char* padValue = malloc(BUF_SIZE * sizeof(char));
				if(padValue == NULL) {
					return 0;
				}
				memcpy(padValue, value, BUF_SIZE);
				char* spaces = malloc(MAX_COLUMN_NAME_LEN * sizeof(char));
				if(spaces == NULL) {
					return 0;
				}
				strcat(spaces, GetSpaces(padValue));	// formez padding
				strcat(padValue, spaces);				// adaug padding
				if(strcmp(auxCell -> value, padValue) != 0) {
					if(auxCell == NULL) {
						return 0;
					}
					p = auxL;
					auxL = auxL -> next;	// trec la urmatoarea linie	
					if(ant != NULL) {		// daca nu am sters prima linie
						ant -> next = auxL;	// refac leg. cu celula anterioara
					} 
					else {
						aux -> lines = auxL;// actualizez pointerul lines
					}
					free(p);
				}
				else {						// daca conditia nu este respectata
					ant = auxL;				// linia ant devine linia curenta
					auxL = auxL -> next;	// trec la linia urmatoare	
				}
			}
			if(strcmp(relation, ">=") == 0) {
				char* padValue = malloc(BUF_SIZE * sizeof(char));
				if(padValue == NULL) {
					return 0;
				}
				memcpy(padValue, value, BUF_SIZE);
				char* spaces = malloc(MAX_COLUMN_NAME_LEN * sizeof(char));
				if(spaces == NULL) {
					return 0;
				}
				strcat(spaces, GetSpaces(padValue));	// formez padding
				strcat(padValue, spaces);				// adaug padding
				if(strcmp(auxCell -> value, padValue) >= 0) {
					if(auxCell == NULL) {
						return 0;
					}
					p = auxL;
					auxL = auxL -> next;	// trec la urmatoarea linie	
					if(ant != NULL) {		// daca nu am sters prima linie
						ant -> next = auxL;	// refac leg. cu celula anterioara
					} 
					else {
						aux -> lines = auxL;// actualizez pointerul lines
					}
					free(p);
				}
				else {						// daca conditia nu este respectata
					ant = auxL;				// linia ant devine linia curenta
					auxL = auxL -> next;	// trec la linia urmatoare	
				}
			}
			if(strcmp(relation, ">") == 0) {
				char* padValue = malloc(BUF_SIZE * sizeof(char));
				if(padValue == NULL) {
					return 0;
				}
				memcpy(padValue, value, BUF_SIZE);
				char* spaces = malloc(MAX_COLUMN_NAME_LEN * sizeof(char));
				if(spaces == NULL) {
					return 0;
				}
				strcat(spaces, GetSpaces(padValue));	// formez padding
				strcat(padValue, spaces);				// adaug padding
				if(strcmp(auxCell -> value, padValue) > 0) {
					if(auxCell == NULL) {
						return 0;
					}
					p = auxL;
					auxL = auxL -> next;	// trec la urmatoarea linie	
					if(ant != NULL) {		// daca nu am sters prima linie
						ant -> next = auxL;	// refac leg. cu celula anterioara
					} 
					else {
						aux -> lines = auxL;// actualizez pointerul lines
					}
					free(p);
				}
				else {						// daca conditia nu este respectata
					ant = auxL;				// linia ant devine linia curenta
					auxL = auxL -> next;	// trec la linia urmatoare		
				}
			}
		}
	}
	return 1; 								// eliminarea a reusit
}
/* Afiseaza toate liniile din tabelul nameT
 * pentru care valoarea value de pe coloana nameC 
 * respecta conditia relation.
*/
void SEARCH(t_db db, char nameT[MAX_TABLE_NAME_LEN],
char nameC[MAX_COLUMN_NAME_LEN], char relation[3], char* value, 
char noSpaces[MAX_COLUMN_NAME_LEN]) {
	t_table* aux = db.tables;
	for(; aux != NULL; aux = aux->next) 	// iterez lista de tabele
		if(strcmp(aux->name, nameT) == 0) 	// am gasit tabelul
			break;							// stop
	if(aux == NULL) {						// nu am gasit niciun tabel
		printf("Table \"%s\" not found in database.\n", nameT);
	}
	else {
	t_column* auxCol = aux -> columns;
	int nrCol = 1;									// pozitia coloanei cautate
	for(; auxCol != NULL; auxCol = auxCol -> next) {// iterez coloanele
		if(strcmp(auxCol->name, nameC) == 0) {		// am gasit coloana
			break;
		}
		nrCol++;									// actualizez pozitia
	}
	if(auxCol == NULL) {							// nu am gasit nicio coloana
		printf("Table \"%s\" does not contain column \"%s\".\n", nameT, noSpaces);
	}
	else {
		int nrCols = 0;								// nr coloane din tabel
		printf("TABLE: %s\n", aux->name);			// afisez nume tabel
		t_column* auxC = aux->columns;
		for(; auxC !=NULL; auxC  = auxC ->next) {	// iterez coloanele
			nrCols++;								// incrementez nr. coloane
			printf("%s", auxC -> name);				// afisez nume coloana
		}
		printf("\n");
		int k = 0;								// folosesc un contor pt " "
		while(k < nrCols) {						// cat timp mai am coloane
			int q = 0;							// folosesc alt contor pt "-"
			while(q < MAX_COLUMN_NAME_LEN) {	// cat timp mai am caractere
				printf("-");					// afisez "-"
				q++;							// incrementez contor
			}
			printf(" ");						// afisez " "
			k++;								// incrementez contor
		}
		printf("\n");
		if(aux->type == INT) {					
			t_intLine* auxL = (t_intLine*)aux -> lines;
			for(; auxL != NULL; auxL = auxL -> next) {	// iterez liniile
				t_intCell* auxCell;
				auxCell = auxL -> cells;
				int i;
				for(i = 1; i < nrCol; i++) {	// iterez pana la pozitia coresp.
					auxCell = auxCell -> next; 
				}
				if(strcmp(relation, "<") == 0) {
					if(auxCell == NULL) {		// daca celula este vida
						break;					// stop
					}
					if(auxCell -> value < atoi(value)) {
						t_intCell* p = auxL -> cells;
						for(; p != NULL; p = p -> next) {	// iterez celule
							printf("%d", p -> value); 		// afiseaza celula
							char string[BUF_SIZE];
							sprintf(string, "%d", p -> value);
							char* spaces = GetSpaces(string); // formez padding
							printf("%s", spaces);			  // adaug padding
						}
						printf("\n");
					}
				}
				if(strcmp(relation, "<=") == 0) {
					if(auxCell == NULL) {		// daca celula este vida
						break;					// stop
					}
					if(auxCell -> value <= atoi(value)) {
						t_intCell* p = auxL -> cells;
						for(; p != NULL; p = p -> next) {	// iterez celule
							printf("%d", p -> value);		// afiseaza celula
							char string[BUF_SIZE];
							sprintf(string, "%d", p -> value);
							char* spaces = GetSpaces(string); // formez padding
							printf("%s", spaces);			  // adaug padding
						}
						printf("\n");
					}
				}
				if(strcmp(relation, "==") == 0) {
					if(auxCell == NULL) {		// daca celula este vida
						break;					// stop
					}
					if(auxCell -> value == atoi(value)) {
						t_intCell* p = auxL -> cells;
						for(; p != NULL; p = p -> next) {	// iterez celule
							printf("%d", p -> value); 		// afiseaza celula
							char string[BUF_SIZE];
							sprintf(string, "%d", p -> value);
							char* spaces = GetSpaces(string); // formez padding
							printf("%s", spaces);			  // adaug padding	
						}
						printf("\n");
					}
				}
				if(strcmp(relation, ">") == 0) {
					if(auxCell == NULL) {		// daca celula este vida
						break;					// stop
					}
					if(auxCell -> value > atoi(value)) {
						t_intCell* p = auxL -> cells;
						for(; p != NULL; p = p -> next) {	// iterez celule
							printf("%d", p -> value); 		// afiseaza celula
							char string[BUF_SIZE];
							sprintf(string, "%d", p -> value);
							char* spaces = GetSpaces(string);// formez padding	
							printf("%s", spaces);			 // adaug padding	
						}
						printf("\n");
					}
				}
				if(strcmp(relation, ">=") == 0) {
					if(auxCell == NULL) {		// daca celula este vida
						break;					// stop
					}	
					if(auxCell -> value >= atoi(value)) {
						t_intCell* p = auxL -> cells;
						for(; p != NULL; p = p -> next) {	// iterez celule
							printf("%d", p -> value); 		// afiseaza celula
							char string[BUF_SIZE];
							sprintf(string, "%d", p -> value);
							char* spaces = GetSpaces(string);// formez padding
							printf("%s", spaces);			 // adaug padding	
						}
						printf("\n");
					}
				}
				if(strcmp(relation, "!=") == 0) {
					if(auxCell == NULL) {		// daca celula este vida
						break;					// stop
					}
					if(auxCell -> value != atoi(value)) {
						t_intCell* p = auxL -> cells;
						for(; p != NULL; p = p -> next) {	// iterez celule
							printf("%d", p -> value); 		// afiseaza celula
							char string[BUF_SIZE];
							sprintf(string, "%d", p -> value);// formez padding
							char* spaces = GetSpaces(string); // adaug padding
							printf("%s", spaces);
						}
						printf("\n");
					}
				}
			}
		}
		if(aux->type == FLOAT) {
			t_floatLine* auxL = (t_floatLine*)aux -> lines;	
			for(; auxL != NULL; auxL = auxL -> next) {		// iterez liniile
				t_floatCell* auxCell;
				auxCell = auxL -> cells;
				int i;
				for(i = 1; i < nrCol; i++) {	// iterez pana la pozitia coresp.	
					auxCell = auxCell -> next; 
				}
				if(strcmp(relation, "<") == 0) {
					if(auxCell == NULL) {		// daca celula este vida
						break;					// stop
					}
					if(auxCell -> value < atof(value)) {
						t_floatCell* p = auxL -> cells;
						for(; p != NULL; p = p -> next) {	// iterez celule
							printf("%f", p -> value); 		// afiseaza celula
							char string[BUF_SIZE];
							sprintf(string, "%f", p -> value);// formez padding
							char* spaces = GetSpaces(string); // adaug padding
							printf("%s", spaces);
						}
						printf("\n");
					}
				}
				if(strcmp(relation, "<=") == 0) {
					if(auxCell == NULL) {		// daca celula este vida
						break;					// stop
					}
					if(auxCell -> value <= atof(value)) {
						t_floatCell* p = auxL -> cells;
						for(; p != NULL; p = p -> next) {	// iterez celule
							printf("%f", p -> value);		// afiseaza celula
							char string[BUF_SIZE];
							sprintf(string, "%f", p -> value);// formez padding
							char* spaces = GetSpaces(string); // adaug padding
							printf("%s", spaces);
						}
						printf("\n");
					}
				}
				if(strcmp(relation, "==") == 0) {
					if(auxCell == NULL) {		// daca celula este vida
						break;					// stop
					}
					if(auxCell -> value == atof(value)) {
						t_floatCell* p = auxL -> cells;
						for(; p != NULL; p = p -> next) {	// iterez celule
							printf("%f", p -> value); 		//afiseaza celula
							char string[BUF_SIZE];
							sprintf(string, "%f", p -> value);// formez padding
							char* spaces = GetSpaces(string); // adaug padding
							printf("%s", spaces);
						}
						printf("\n");
					}
				}
				if(strcmp(relation, ">") == 0) {
					if(auxCell == NULL) {		// daca celula este vida
						break;					// stop
					}
					if(auxCell -> value > atof(value)) {
						t_floatCell* p = auxL -> cells;
						for(; p != NULL; p = p -> next) {	// iterez celule
							printf("%f", p -> value); 		// afiseaza celula
							char string[BUF_SIZE];
							sprintf(string, "%f", p -> value);// formez padding
							char* spaces = GetSpaces(string); // adaug padding
							printf("%s", spaces);
						}
						printf("\n");
					}
				}
				if(strcmp(relation, ">=") == 0) {
					if(auxCell == NULL) {		// daca celula este vida
						break;					// stop	
					}	
					if(auxCell -> value >= atof(value)) {
						t_floatCell* p = auxL -> cells;	
						for(; p != NULL; p = p -> next) {	// iterez celule
							printf("%f", p -> value); 		// afiseaza celula
							char string[BUF_SIZE];
							sprintf(string, "%f", p -> value);
							char* spaces = GetSpaces(string); // formez padding
							printf("%s", spaces);			  // adaug padding
						}
						printf("\n");
					}
				}
				if(strcmp(relation, "!=") == 0) {
					if(auxCell == NULL) {		// daca celula este vida
						break;					// stop	
					}
					if(auxCell -> value != atof(value)) {
						t_floatCell* p = auxL -> cells;
						for(; p != NULL; p = p -> next) {	// iterez celule
							printf("%f", p -> value); 		// afiseaza celula
							char string[BUF_SIZE];
							sprintf(string, "%f", p -> value);
							char* spaces = GetSpaces(string);// formez padding
							printf("%s", spaces);			 // adaug padding
						}
						printf("\n");
					}
				}
			}
		}
		if(aux->type == STRING) {
			t_stringLine* auxL = (t_stringLine*)aux -> lines;
			for(; auxL != NULL; auxL = auxL -> next) {		// iterez liniile
				t_stringCell* auxCell;
				auxCell = auxL -> cells;
				int i;
				for(i = 1; i < nrCol; i++) {	// iterez pana la pozitia coresp.
					auxCell = auxCell -> next; 
				}
				if(strcmp(relation, "<") == 0) {
					if(auxCell == NULL) {		// daca celula este vida
						break;					// stop	
					}
					char* padValue = malloc(BUF_SIZE * sizeof(char));
					if(padValue == NULL) {
						break;
					}
					memcpy(padValue, value, BUF_SIZE);
					char* spaces = malloc(MAX_COLUMN_NAME_LEN * sizeof(char));
					if(spaces == NULL) {
						break;
					}
					strcat(spaces, GetSpaces(padValue));	// formez padding
					strcat(padValue, spaces);				// adaug padding
					if(strcmp(auxCell -> value, padValue) < 0) {
						t_stringCell* p = auxL -> cells;
						for(; p != NULL; p = p -> next) {	// iterez celule
							printf("%s", p -> value); 		// afiseaza celula
						}
						printf("\n");
					}
				}
				if(strcmp(relation, "<=") == 0) {	// daca celula este vida
					if(auxCell == NULL) {			// stop	
						break;
					}
					char* padValue = malloc(BUF_SIZE * sizeof(char));
					if(padValue == NULL) {
						break;
					}
					memcpy(padValue, value, BUF_SIZE);
					char* spaces = malloc(MAX_COLUMN_NAME_LEN * sizeof(char));
					if(spaces == NULL) {
						break;
					}
					strcat(spaces, GetSpaces(padValue));	// formez padding
					strcat(padValue, spaces);				// adaug padding
					if(strcmp(auxCell -> value, padValue) <= 0) {
						t_stringCell* p = auxL -> cells;
						for(; p != NULL; p = p -> next) {	// iterez celule
							printf("%s", p -> value); 		// afiseaza celula
						}
						printf("\n");
					}
				}
				if(strcmp(relation, "==") == 0) {	
					if(auxCell == NULL) {			// daca celula este vida
						break;						// stop	
					}
					char* padValue = malloc(BUF_SIZE * sizeof(char));
					if(padValue == NULL) {
						break;
					}
					memcpy(padValue, value, BUF_SIZE);
					char* spaces = malloc(MAX_COLUMN_NAME_LEN * sizeof(char));
					if(spaces == NULL) {
						break;
					}
					strcat(spaces, GetSpaces(padValue));	// formez padding
					strcat(padValue, spaces);				// adaug padding
					if(strcmp(auxCell -> value, padValue) == 0) {
						t_stringCell* p = auxL -> cells;
						for(; p != NULL; p = p -> next) {	// iterez celule
							printf("%s", p -> value); 		// afiseaza celula
						}
						printf("\n");
					}
				}
				if(strcmp(relation, ">") == 0) {
					if(auxCell == NULL) {		// daca celula este vida
						break;					// stop	
					}
					char* padValue = malloc(BUF_SIZE * sizeof(char));
					if(padValue == NULL) {
						break;
					}
					memcpy(padValue, value, BUF_SIZE);
					char* spaces = malloc(MAX_COLUMN_NAME_LEN * sizeof(char));
					if(spaces == NULL) {
						break;
					}
					strcat(spaces, GetSpaces(padValue));	// formez padding
					strcat(padValue, spaces);				// adaug padding
					if(strcmp(auxCell -> value, padValue) > 0) {
						t_stringCell* p = auxL -> cells;
						for(; p != NULL; p = p -> next) {	// iterez celule
							printf("%s", p -> value); 		// afiseaza celula
						}
						printf("\n");
					}
				}
				if(strcmp(relation, ">=") == 0) {
					if(auxCell == NULL) {		// daca celula este vida
						break;					// stop	
					}
					char* padValue = malloc(BUF_SIZE * sizeof(char));
					if(padValue == NULL) {
						break;
					}
					memcpy(padValue, value, BUF_SIZE);
					char* spaces = malloc(MAX_COLUMN_NAME_LEN * sizeof(char));
					if(spaces == NULL) {
						break;
					}
					strcat(spaces, GetSpaces(padValue));	// formez padding
					strcat(padValue, spaces);				// adaug padding
					if(strcmp(auxCell -> value, padValue) >= 0) {
						t_stringCell* p = auxL -> cells;
						for(; p != NULL; p = p -> next) {	// iterez celule
							printf("%s", p -> value); 		// afiseaza celula
						}
						printf("\n");
					}
				}
				if(strcmp(relation, "!=") == 0) {
					if(auxCell == NULL) {		// daca celula este vida
						break;					// stop	
					}
					char* padValue = malloc(BUF_SIZE * sizeof(char));
					if(padValue == NULL) {
						break;
					}
					memcpy(padValue, value, BUF_SIZE);
					char* spaces = malloc(MAX_COLUMN_NAME_LEN * sizeof(char));
					if(spaces == NULL) {
						break;
					}
					strcat(spaces, GetSpaces(padValue));	// formez padding	
					strcat(padValue, spaces);				// adaug padding
					if(strcmp(auxCell -> value, padValue) != 0) {
						t_stringCell* p = auxL -> cells;
						for(; p != NULL; p = p -> next) {	// iterez celule
							printf("%s", p -> value); 		// afiseaza celula
						}
						printf("\n");
					}
				}
			}
		}
		printf("\n");
		}
	}
}
