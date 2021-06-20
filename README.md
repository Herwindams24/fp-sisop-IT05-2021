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
Selanjutnya dilakukan inisialisasi koneksi dari client side dengan server side dan dilakukan deklarasi if condition jika connection gagal dilakukan sebagai berikut:
```c
if (connect(sock, (struct sockaddr *)&address, sizeof(address)) < 0) {
        printf("\nConnection Failed \n");
        exit(EXIT_FAILURE);
    }
```
Ketika koneksi sudah terbentuk maka dilakukan penampilan screen 1 yang menampilkan pilihan untuk melakukan login atau register, kemudian mengirimkan input respon yang dikirimkan user kepada server side, sebagai berikut:
```c
screen1:;
    int mode = -1;
    while (mode == -1) {
        char input[20];
        printf("1. Login\n2. Register\nChoices: ");
        scanf("%s", input);
        if (strcmp(input, "login") == 0) {
            mode = 0;
            break;
        } else if (strcmp(input, "register") == 0) {
            mode = 1;
            break;
        }
        printf("\nInvalid input.\n");
    }
```
Selanjutnya, terdapat inisialiasi variabel username dan password yang nantinya akan digunakan untuk menjalankan fungsi login dan juga register, sebagai berikut:
```c
    char username[210], password[200];
    memset(username, 0, sizeof(username));
    memset(password, 0, sizeof(password));
    username[0] = mode + '0';
    username[1] = '\t';
    password[0] = '\t';
    printf("Username: ");
    getchar();
    scanf("%[^\n]", username+2);
    getchar();
    printf("Password: ");
    scanf("%[^\n]", password+1);
    strcat(username, password);
    send(sock, username, strlen(username), 0);
```
Berikutnya terdapat respond yang diberikan ketika berhasil melakukan login yang akan menampilkan “login success” ataupun gagal yang akan menampilkan pesan “login failed”.
```c
if (mode == 0) {// LOGIN
        int resp;
        read(sock, &resp, sizeof(resp));
        if (resp) printf("login success\n");
        else {
            printf("login failed\n");
            goto screen1;
}
```
Sementara dalam menjalankan register maka dari client side akan menampilkan respond “register succesfull” ketika berhasil mendaftarkan user ke dalam server. Adapun fungsi yang digunakan sebagai berikut:
```c
else if (mode == 1) { // REGISTER
        printf("register success\n");
    }
```
Saat sudah berhasil melakukan login, dari client side akan menampilkan pilihan fitur-fitur yang dapat dilakukan dalam program yang terdiri dari fitur: add, download, delete, see, find, serta logout. Adapun fungsi yang digunakan dalam menampilkan fitur adalah sebagai berikut:
```c
screen2:;
    mode = -1;
    while (mode == -1) {
        printf("1. add\n2. download\n3. delete\n4. see\n5. find\n6. logout\nChoices: ");
        char input[20];
        scanf("%s", input);
        if (strcmp(input, "add") == 0) {
            mode = 0;
            break;
        } else if (strcmp(input, "download") == 0) {
            mode = 1;
            break;
        } else if (strcmp(input, "delete") == 0) {
            mode = 2;
            break;
        } else if (strcmp(input, "see") == 0) {
            mode = 3;
            break;
        } else if (strcmp(input, "find") == 0) {
            mode = 4;
            break;
        } else if (strcmp(input, "logout") == 0) {
            mode = 5;
            break;
        }
        printf("\nInvalid input.\n");
    }
```
Jika user memilih opsi logout, maka client akan kembali menampilkan tampilan awal yang menampilkan opsi login atau register dengan menggunakan perintah berikut:
```c
else if (mode == 5) { // LOGOUT
        goto screen1;
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
