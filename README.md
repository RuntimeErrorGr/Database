// Lăbău Cristea Andrei Liviu 314CB

An interactive console was implemented to allow the user to interact with the database. This was done using two strings read from the keyboard: `command` and `command2`. Since it is guaranteed that the first user command will be `INIT_DB` followed by the name of the database, we first verify if it was entered correctly and read the name from standard input. To determine the subsequent commands, we enter a `while` loop where a sequence of `if` statements is used. The only command that breaks the loop, deletes the database, and stops program execution is `DELETE_DB`.

After entering the `INIT_DB` command and reading the database name, the `INIT_DB` function is called, which allocates memory for a `t_db` element and initializes its name field.

To insert a new table into the database, the `CREATE` command is used, followed by the new table's name, the type of data it will contain, and the column names. The functions used to simulate this command are:
- `CREATE`, which receives as parameters:
  - the address of the database into which the table is inserted
  - a string representing the new table’s name
  - a string representing the data type the table will contain

The `CREATE` function calls `AlocTable`, which uses:
- a function to convert the data type from a string into the corresponding element from the `t_cellType` enum
- the `ReadColumns` function, which allocates space for a singly linked list of column cells, with its head pointed to by the `columns` pointer in the table structure.

`ReadColumns` reads a string from stdin until newline, then splits it into substrings using `' '` and `'\n'` as delimiters. These substrings are column names. As each substring is found, the `AlocColumn` function is called with the substring as a parameter. It allocates the corresponding cell and links it into the list:
- directly to `columns` if it's the first cell,
- or at the end of the list otherwise.

The `CREATE` function is called in `main`.

To delete a table from the database, the `DELETE` command is used, followed by the name of the table to delete. The `DELETE` function first checks if the table exists in the database. If not, it prints an error message. If the table exists:
- If it’s the first in the list, the `tables` pointer of the database is updated (we change the head of the list).
- Otherwise, the table's memory is freed and list links are updated.

To print the entire database, the `PRINT_DB` command is used. When entered, the `PRINT_DB` function is called with the database as a parameter. The function traverses the list of tables; for each one:
- it traverses the column list and prints it,
- followed by a line of dashes (`-`).

Column alignment is done using space padding (`' '`) up to 30 characters. Then it traverses the list of row headers (`lines`), and for each, it traverses the cell list (`cells`) and prints each value. Alignment is again done by padding up to 30 characters.

Initially, alignment was attempted during printing for both strings and numeric values. Later, it was realized that for `int` and `float` values it was easier to include all 30 characters (value + padding) directly at allocation and input time. To achieve this, `sprintf` was used to convert the `int`/`float` into a string, making it easier to determine the character length. Then the number of spaces was calculated and added using `GetSpaces`, concatenated with the `sprintf` result.

To print a single table from the database, the `PRINT` command is used, followed by the name of the table to print. The principle is the same as in `PRINT_DB`, but now:
- instead of traversing all tables,
- we stop once the specified table name is found and begin printing.

If no table with the given name is found, an error message is returned.

To perform selective searches in the database by table, column, and a condition on the column’s values, the `SEARCH` command is used. The implementation steps are:

- Traverse the list of tables and locate the desired one. If not found, return an error.
- Traverse the list of columns and locate the desired one. If not found, return an error.
  - During this traversal, column positions are counted to determine which cell in each row to compare.
- Traverse the row headers, and for each, traverse the `cells` list up to the previously determined column index.
- Check if the value satisfies the condition.
- If it does:
  - Print the table header (column list + dashes),
  - Then print the entire row containing the match.
- Continue with the next row.

To add rows to an existing table in the database, the `ADD` command is used. Upon receiving `ADD` followed by the table name and values to insert:
- A function is called with the database address and table name as parameters.
- If the table doesn’t exist, an error is printed.
- The list of tables is traversed and stops at the desired one.

Depending on the table’s data type, one of the allocation functions is called:
- `AlocIntLine`, `AlocFloatLine`, or `AlocSTRINGLine`.

Then `ReadCells` is used to read input and allocate cells for the new row. After allocation:
- If the table is empty, the `lines` pointer will point to the new row.
- If not, we traverse to the end and append the row to the end.

To perform selective deletion based on a table, column, and condition, a different `DELETE` command is used (not the one that deletes an entire table). This one takes four parameters.

In `main`, the differentiation between the two `DELETE` commands is done by the number of arguments parsed from the command line.

To count command arguments and call the correct function:
- A buffer is read until newline.
- The buffer is split into substrings using `' '` and `'\n'`.
- These substrings are stored in order in a matrix and passed to `DELETE` or `DELETESELECT`, depending on the case.

The only matrix element altered before being passed is the column name, to which padding is added.

The principle of selective deletion is nearly identical to that of selective search, except now:
- Rows that satisfy the input condition are not printed but deleted.

Depending on the case:
- If the first row is deleted, `lines` is updated.
- If an interior row is deleted, links are updated accordingly.
- If no matching rows are found, no deletion occurs.
