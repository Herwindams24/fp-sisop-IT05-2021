# FP SISOP IT05 2021
Penyelesaian Final Project Sistem Operasi 2021\
Kelompok IT05
  * Herwinda Marwaa Salsabila (05311840000009)
  * Stefanus Lionel Carlo Nugroho (05311940000027)
  * I Gde Ardha Semaranatha Gunasatwika (05311940000034)

---

## Table of Contents

* [Server](#server)
* [Client](#client)
* [Program Database](#database)
* [Kendala](#kendala)

---

## Server




## Client



## Database

Pertama, penulis menulis library-library yang akan digunakan pada program database ini. Berikut merupakan library-library yang penulis gunakan:

```c
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
```

Lalu buat sebuah struct bernama `database_Element` dengan member `ID`, `field_size`, `field_name`, `field_value`. Selain itu, *create* sebuah variabel dengan nama `db_Element`.

```c
typedef struct database_Element{
  int ID;
  int field_Size;
  char* field_Name;
  char* field_Value;
}db_Element;
```
Buat struct ke-2 dengan nama `Database` dengan member `db_Name`, `elements`, `row_Size`, `num_Of_Rows`, `num_Of_Columns`, dan `ID`. Selain itu, *create* sebuah variabel dengan nama `db`.
```c
typedef struct Database{
  char* db_Name;
  db_Element* elements;
  int row_Size;
  int num_Of_Rows;
  int num_Of_Columns;
  int ID;
}db;
```

## Kendala
- .
- .
