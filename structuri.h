/*Lăbău Cristea Andrei Liviu 314CB*/

#ifndef __STRUCTURES__
#define __STRUCTURES__

#define read                1
#define MAX_COLUMN_NAME_LEN 30
#define MAX_TABLE_NAME_LEN  30
#define MAX_DB_NAME_LEN     30
#define MAX_CMD_LEN         300
#define BUF_SIZE 			1024

//generic
typedef struct gCell {
	void* value;
	struct gCell* next;
}t_gCell, *TListGCell;

typedef struct gLine {
	t_gCell* cells;
	struct gLine* next; 
}t_gLine, *TListGLine;
// int
typedef struct intCell {
	int    value;
	struct intCell* next;
} t_intCell, *TListIntCell;

typedef struct intLine {
	t_intCell*      cells;
	struct intLine* next;
} t_intLine, *TListIntLine;

// float
typedef struct floatCell {
	float  value;
	struct floatCell* next;
} t_floatCell, *TListFloatCell;

typedef struct floatLine {
	t_floatCell*      cells;
	struct floatLine* next;
} t_floatLine, *TListFloatLine;

// string
typedef struct stringCell {
	char*  value;
	struct stringCell* next;
} t_stringCell, *TListStringCell;

typedef struct stringLine {
	t_stringCell*       cells;
	struct stringLine* next;
} t_stringLine, *TListStringLine;

// cell type
typedef enum {
	INT,
	FLOAT,
	STRING
} t_cellType;

// column
typedef struct column {
	char name[MAX_COLUMN_NAME_LEN];
	struct column* next;
} t_column, *t_columnL;

// table
typedef struct table {
	char name[MAX_TABLE_NAME_LEN];
	t_cellType    type;
	t_column*     columns;
	void*         lines;  // t_intLine* | t_floatLine* | t_stringLine*
	struct table* next;
} t_table, *TListTable;

// database
typedef struct db {
	char name[MAX_DB_NAME_LEN];
	t_table* tables;
} t_db;

// FUNCTII AUXILIARE
char* GetSpaces(char* name);
t_cellType InfoType(char* nameType);
// FUNCTII CITIRE
TListGCell ReadStringCells();
TListIntLine ReadIntLine();
TListIntCell ReadIntCells();
TListFloatCell ReadFloatCells();
// FUNCTII ALOCARE
t_stringCell* AlocStringCell(char* value);
t_intCell* AlocIntCell(int value);
t_floatCell* AlocFloatCell(float value);
t_gLine* AlocGLine();
t_stringLine* AlocStringLine();
t_intLine* AlocIntLine();
t_floatLine* AlocFloatLine();
t_column* AlocColumn(char name[MAX_COLUMN_NAME_LEN]);
t_table* AlocTable(char name[MAX_TABLE_NAME_LEN], char nameType[7]);
// FUNCTII DATA DEFINITION
t_db* INIT_DB(char* nameDB);
void DELETE_DB(t_db* dataBase);
int CREATE(t_db* db, char name[MAX_TABLE_NAME_LEN], char nameType[7]);
int DELETE(t_db* db, char name[MAX_TABLE_NAME_LEN]);
// FUNCTII DATA QUERY
void PRINT_DB(t_db db);
void PRINT(t_db db, char name[MAX_TABLE_NAME_LEN]);
void SEARCH(t_db db, char nameT[MAX_TABLE_NAME_LEN],
char nameC[MAX_COLUMN_NAME_LEN], char relation[3], char* value,
char noSpaces[MAX_COLUMN_NAME_LEN]);
// DATA MANIPULATION
int ADD(t_db* db, char nameTable[MAX_TABLE_NAME_LEN]);
void CLEAR(t_db* db, char name[MAX_TABLE_NAME_LEN]);
int DELETESELECT(t_db* db, char nameT[MAX_TABLE_NAME_LEN],
char nameC[MAX_COLUMN_NAME_LEN], char relation[3], char* value, 
char noSpaces[MAX_COLUMN_NAME_LEN]);


#endif
