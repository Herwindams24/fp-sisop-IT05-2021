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

Berikut merupakan library-library yang penulis gunakan:
``` c
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h> 
#include <termios.h> 
```
Di mana library-library tersebut memiliki fungsi sebagai berikut:
* `<sys/stat.h>` - Library untuk memanggil fungsi pembuatan sebuah direktori baru (e.g. `mkdir()`)
* `<stdio.h>` - Library untuk fungsi input-output (e.g. `printf(), sprintf()`)
* `<sys/socket.h>` - Library untuk memanggil fungsi pemanfaatan socket
* `<stdlib.h>` - Library untuk fungsi umum (e.g. `exit()`, `atoi()`)
* `<netinet/in.h>` - Library untuk memanggil fungsi pemanfaatan internet
* `<unistd.h>` - Library untuk mendapatkan lokasi current working direktory (e.g. `getcwd()`)
* `<string.h>` - Libraryy untuk manipulasi string
* `<pthread.h>` - Library untuk operasi thread (e.g. `pthread_create()`, `ptrhead_exit()` )
* `<arpa/inet.h>` - Library untuk memanggil fungsi pemanfaatan serta manipulasi fungsi host menggunakan internet
* `<termios.h>` - Library untuk menjalankan fungsi dalam terminal

Selain itu, penulis juga mendeklarasikan port yang akan digunakan oleh `Client` adalah port 8080:
```c
#define PORT 8080
```
Dalam fungsi main, pertama-tama dilakukan inisialisasi socket dan juga struct socket untuk menginisialisasi socket yang akan digunakan untuk menjalankan program.
```c
 int sock;
    struct sockaddr_in address;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        exit(EXIT_FAILURE);
    }
```
Selanjutnya buat fungsi memset untuk mengisi blok memory dengan nilai `0`.
```c
memset(&address, '0', sizeof(address));
```
Selanjutnya menggunakan struktur field .sin_family yang mengandung address family. Di mana AF_INET saat TCP atau User Datagram Protocol (UDP) digunakan. Adapun .sin_port yang mengandung nilai port dan akan disimpan pada variabel htons(PORT).
```c
address.sin_family = AF_INET;
address.sin_port = htons(PORT);
```
Lalu buat statement if yang berisikan parameter fungsi `inet_pton`. Fungsi ini mengubah string karakter src menjadi jaringan struktur alamat dalam keluarga alamat AF.
```c
   if(inet_pton(AF_INET, "127.0.0.1", &address.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        exit(EXIT_FAILURE);
    }
  
```
## Database

Pertama, penulis menulis library-library yang akan digunakan pada program database ini. Berikut merupakan library-library yang penulis gunakan:

```c
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
```
Di mana library-library tersebut memiliki fungsi sebagai berikut:
* `<stdio.h>` - Library untuk fungsi input-output (e.g. `printf(), sprintf()`)
* `<stdlib.h>` - Library untuk fungsi umum (e.g. `exit()`, `atoi()`)
* `<string.h>` - Library untuk manipulasi string
* `<stdlib.h>` - Library untuk operasi pembanding dan konversi (e.g. `atoi()`)

Selanjutnya, penulis membuat sebuah struct bernama `database_Element` dengan member `ID`, `field_size`, `field_name`, `field_value`. Selain itu, *create* sebuah variabel dengan nama `db_Element`.

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
