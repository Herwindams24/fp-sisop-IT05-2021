
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ptrsize=sizeof(char*);


typedef struct database_Element{
  int ID;
  int field_Size;
  char* field_Name;
  char* field_Value;


}db_Element;

typedef struct Database{
  char* db_Name;
  db_Element* elements;
  int row_Size;
  int num_Of_Rows;
  int num_Of_Columns;
  int ID;

}db;

void newDb(db* dataBase, char* buffer){

  char cmd[1024];
  sprintf(cmd, "%s", buffer + 15);
  
  char *token;
  token =strtok(cmd, " ");
  
  char name[1024];
  sprintf(name, "%s", token);
  
  char *ob = strchr(buffer, '(');
	char *cb = strchr(buffer, ')');
	
	char cols_and_types[1024];
	sprintf(cols_and_types, "%.*s", cb - ob - 1, ob + 1);
	
	token = strtok(cols_and_types, ", ");

  db_Element *elem=(db_Element*)malloc(sizeof(db_Element)*20);
  dataBase->elements=elem;
	
	int num = 0;
	while (token != NULL) {
		elem[num].field_Name=token;
		token = strtok(NULL, ", ");
		
		elem[num].field_Size=50;
    elem[num].ID=1;
		token = strtok(NULL, ", ");
		++num;
	}

  dataBase->num_Of_Rows=0;
  FILE* fp;
  int i,x;
  int id=1,field_size;
  char* field_name;
  dataBase->db_Name=name;

  x=strlen(name);
  name[x]='.';
  name[x+1]='d';
  name[x+2]='b';
  name[x+3]='\0';
  fp=fopen(name,"wb");
  int format=16711935,rows=0;
  fwrite(&format,4,1,fp);
  fwrite(name,24,1,fp);
  fwrite(&num,4,1,fp);
  fwrite(&rows,4,1,fp);
  fwrite(&id,4,1,fp);
  for(i=0;i<num;i++){
      char a[21];
      int b;
      char c='\0';
      memmove(a,elem[i].field_Name,21);
      b=elem[i].field_Size;
      fwrite(&id,4,1,fp);
      fwrite(a,21,1,fp);
      fwrite(&b,4,1,fp);
      fwrite(&c,1,elem[i].field_Size,fp);

  }
  fclose(fp);
  free(elem);
}

FILE* readDbHeader(db* dataBase,char fileName[]){
    FILE* fp=fopen(fileName,"rb");
    char name[24];
    int format,num_of_columns,num_of_rows,id;
    fread(&format,4,1,fp);

    fread(name,24,1,fp);
    // printf("Database name: %s\n",name);
    fread(&num_of_columns,4,1,fp);
    // printf("Number of columns: %d\n",num_of_columns);
    fread(&num_of_rows,4,1,fp);
    // printf("Number of rows: %d\n\n",num_of_rows);
    fread(&id,4,1,fp);
    dataBase->num_Of_Rows=num_of_rows;
    dataBase->num_Of_Columns=num_of_columns;
    dataBase->ID=id;

    return fp;

}

void readRow(db* dataBase,char fileName[]){
    dataBase->row_Size=0;
    char *a;
    int b,id;
    char *c;
    FILE* fp=readDbHeader(dataBase,fileName);
    int i,r=dataBase->num_Of_Columns;
    db_Element* elem=(db_Element*)malloc(r*sizeof(db_Element));
    dataBase->elements=elem;
    for(i=0;i<r;i++){
        a=(char*)malloc(21);
      fread(&id,4,1,fp);
      fread(a,21,1,fp);
      fread(&b,4,1,fp);
      c=(char*)malloc(b);
      fread(c,b,1,fp);
      elem[i].field_Name=a;
      elem[i].field_Size=b;
      elem[i].field_Value=c;
      dataBase->row_Size+=(b+29);

    }
    fclose(fp);
}

void printTitle(db* dataBase){
    char name[25];
    int r=dataBase->num_Of_Columns,j,k;
       for(j=0;j<(9+22*r);j++){
            printf("-");
       }
       printf("\n");
       printf("| ID    |");
       for(j=0;j<r;j++){
            memmove(name,dataBase->elements[j].field_Name,21);
            printf(" %s",name);

            int n=strlen(name);
            //printf("   %d   ",n);
            for(k=0;k<(20-n);k++){
                printf(" ");
            }
            printf("|");
       }
       printf("\n");
       for(j=0;j<(9+22*r);j++){
            printf("-");
            }

       printf("\n");
       for(j=0;j<(9+22*r);j++){
            printf("-");
       }
       printf("\n");
}

void printValues(db* dataBase,char fileName[]){
    if(dataBase->num_Of_Rows==0)
        return;
    int id,b,r=dataBase->num_Of_Columns,i,j,it=0;
    char value[256];
    FILE* fp=fopen(fileName,"rb");
    fseek(fp, 40+dataBase->row_Size, SEEK_CUR);
    while(1){
        fread(&id,4,1,fp);
        fseek(fp,-4,SEEK_CUR);
        int len=0,x=id;
        while(x){
            x/=10;
            len++;
        }
        printf("| %d ",id);
        for(i=0;i<(5-len);i++){
            printf(" ");
        }
        for(i=0;i<(dataBase->num_Of_Columns);i++){
        //fread(&id,4,1,fp);
        fseek(fp,4,SEEK_CUR);
        fseek(fp,21,SEEK_CUR);
        fread(&b,4,1,fp);
        fread(value,b,1,fp);
        printf("| %s ",value);
        for(j=0;j<(19-strlen(value));j++){
            printf(" ");
        }

        }
        printf("|");
        printf("\n");
        it++;
        if(it==dataBase->num_Of_Rows)
            break;
    }
}

void addRow(db* dataBase,char fileName[], char* buffer){
  int i;
  dataBase->num_Of_Rows++;
  int row=dataBase->num_Of_Rows,id;
  FILE* fp=fopen(fileName,"a+b");

  char cmd[1024];
	sprintf(cmd, "%s", buffer + 11);
  
  char *token;
  token =strtok(cmd, " ");

  char name[1024];
  sprintf(name, "%s", token);
  
  char *ob = strchr(buffer, '(');
	char *cb = strchr(buffer, ')');
	
	char cols_and_types[1024];
	sprintf(cols_and_types, "%.*s", cb - ob - 1, ob + 1);
	
	token = strtok(cols_and_types, ", ");

  for(i=0;i<dataBase->num_Of_Columns;i++){
      char a[21];
      int b;
      id=dataBase->ID;
      char *c;
      memmove(a,dataBase->elements[i].field_Name,21);
      b=dataBase->elements[i].field_Size;
      fwrite(&id,4,1,fp);
      fwrite(a,21,1,fp);
      fwrite(&b,4,1,fp);
      c=(char*)malloc(b);
      token = strtok(NULL, ", ");
      c = token;
      token = strtok(NULL, ", ");
      fwrite(c,b,1,fp);


  }
  id++;
  dataBase->ID++;
  fclose(fp);
  fp=fopen(fileName,"r+b");
  fseek(fp,32,SEEK_CUR);
  fwrite(&row,4,1,fp);
  fwrite(&id,4,1,fp);
  fclose(fp);

}

struct InputBuffer_t {
  char* buffer;
  size_t buffer_length;
  ssize_t input_length;
};
typedef struct InputBuffer_t InputBuffer;

enum MetaCommandResult_t {
  META_COMMAND_SUCCESS,
  META_COMMAND_UNRECOGNIZED_COMMAND
};
typedef enum MetaCommandResult_t MetaCommandResult;

enum PrepareResult_t { PREPARE_SUCCESS, PREPARE_UNRECOGNIZED_STATEMENT };
typedef enum PrepareResult_t PrepareResult;

enum StatementType_t { STATEMENT_CREATE, STATEMENT_INSERT, STATEMENT_SELECT };
typedef enum StatementType_t StatementType;

struct Statement_t {
  StatementType type;
};
typedef struct Statement_t Statement;

InputBuffer* new_input_buffer() {
  InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
  input_buffer->buffer = NULL;
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;

  return input_buffer;
}

void print_prompt() { printf("db > "); }

void read_input(InputBuffer* input_buffer) {
  ssize_t bytes_read =
      getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

  if (bytes_read <= 0) {
    printf("Error reading input\n");
    exit(EXIT_FAILURE);
  }

  input_buffer->input_length = bytes_read - 1;
  input_buffer->buffer[bytes_read - 1] = 0;
}

MetaCommandResult do_meta_command(InputBuffer* input_buffer) {
  if (strcmp(input_buffer->buffer, ".exit") == 0) {
    exit(EXIT_SUCCESS);
  } else {
    return META_COMMAND_UNRECOGNIZED_COMMAND;
  }
}

PrepareResult prepare_statement(InputBuffer* input_buffer,
                                Statement* statement) {
  db* dataBase=(db*)malloc(sizeof(db));
  if (strncmp(input_buffer->buffer, "CREATE DATABASE", 15) == 0) {
    statement->type = STATEMENT_CREATE;

    newDb(dataBase, input_buffer->buffer);

    return PREPARE_SUCCESS;
  }
  if (strncmp(input_buffer->buffer, "INSERT INTO", 11) == 0) {
    statement->type = STATEMENT_INSERT;

    char cmd[1024];
    sprintf(cmd, "%s", input_buffer->buffer + 11);
    
    char *token;
    token =strtok(cmd, " ;\n\0");
    
    char db[1024];
    sprintf(db, "%s", token);

    char fileName[1024];
    sprintf(fileName, "%s.db", db);

    addRow(dataBase,fileName, input_buffer->buffer);

    return PREPARE_SUCCESS;
  }
  if (strncmp(input_buffer->buffer, "SELECT * FROM", 13) == 0) {
    statement->type = STATEMENT_SELECT;

    char cmd[1024];
    sprintf(cmd, "%s", input_buffer->buffer + 13);
    
    char *token;
    token =strtok(cmd, " ;\n\0");
    
    char db[1024];
    sprintf(db, "%s", token);

    char fileName[1024];
    sprintf(fileName, "%s.db", db);

    readRow(dataBase,fileName);
    printTitle(dataBase);
    printValues(dataBase,fileName);
    return PREPARE_SUCCESS;
  }

  return PREPARE_UNRECOGNIZED_STATEMENT;
}

int main(int argc, char* argv[]) {
    InputBuffer* input_buffer = new_input_buffer();
    while (true) {
    print_prompt();
    read_input(input_buffer);

    if (input_buffer->buffer[0] == '.') {
      switch (do_meta_command(input_buffer)) {
        case (META_COMMAND_SUCCESS):
          continue;
        case (META_COMMAND_UNRECOGNIZED_COMMAND):
          printf("Unrecognized command '%s'\n", input_buffer->buffer);
          continue;
      }
    }

    Statement statement;
    switch (prepare_statement(input_buffer, &statement)) {
      case (PREPARE_SUCCESS):
        break;
      case (PREPARE_UNRECOGNIZED_STATEMENT):
        printf("Unrecognized keyword at start of '%s'.\n",
               input_buffer->buffer);
        continue;
    }
  }
}