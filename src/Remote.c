#include "common.h"
#include "Remote.h"
#include <string.h>
#include <assert.h>


void Remote_askAction(){
    printf("You want to:\r\n");
    printf("1 - Add new pwd entry\r\n");
    printf("2 - Delete an entry\r\n");
    printf("3 - Show entries\r\n");
    printf("q - Quit\r\n");
}

bool Remote_onActionResponse(char response){
    bool l_continue = true; 
    switch (response) {
        case '1':
        Remote_addEntry();
        break;
        case '2':
        Remote_delEntry();
        break;
        case 'q':
        l_continue = false;
        break;
    }
    return l_continue;
}

void Remote_addEntry(){
    FILE *file;
    file = fopen(REMOTE_FILE_NAME, "a");
    if (file)
    {
    Entry new_entry = Remote_getEntry();
    fprintf(file, "%s %s %s;\r\n", new_entry.id, new_entry.login, new_entry.pwd);
    fclose(file);
    } 
    else {
        printf("Unable to open entry file\r\n");
    }    
}


Entry Remote_getEntry(){
    Entry new_entry;
    calloc(1, sizeof(Entry)+1);
    printf("Enter the id of the entry (domain name for instance):\r\n");
    scanf("%s", new_entry.id);
    printf("Enter the login of the entry:\r\n");
    scanf("%s", new_entry.login);
    printf("Enter the password of the entry:\r\n");
    system("stty -echo");
    scanf("%s", new_entry.pwd);
    system("stty echo");

    return new_entry;
}

void Remote_delEntry(){
    char seek [ID_MAX_LENGTH];
    Remote_getDomain(seek);
    int index = Remote_findEntry(seek);
    if (index == -1)
    {
        printf(RED);
        printf("No existing matching entry was found\r\n\n");
        printf(DEFAUT);        
    }
    else
    {
        Remote_delLine(index);
        printf(GREEN);
        printf("The entry was deleted successfully\r\n\n");
        printf(DEFAUT);
    }
}

void Remote_getDomain(char domain []){
    printf("Enter a domain to delete the entry of:\r\n");
    scanf("%s", domain);
}

int Remote_findEntry(char * id){
    int line_index = -1;
    FILE *file = fopen(REMOTE_FILE_NAME, "r+");
    int lines = Remote_getNbLines();
    char domain[15];
    if (file)
    {
        bool found = false;
        for (int i = 0; i < lines && !found; i++){
            fscanf(file, "%s %*s %*s", domain);
            found = strcmp(domain, id) == 0; // Compare domain with the wanted one
            printf("Comparing: %s and %s --> %s\r\n", domain, id, found ? "Found!" : "Fail");
            line_index = found? i : line_index;
        }
    }
    else {
        printf("Unable to open entry file\r\n");
    }  
    fclose(file);
    return line_index;
}

int Remote_getNbLines(){
    // count the number of lines in the file called filename                                    
    FILE *file = fopen(REMOTE_FILE_NAME, "r");
    int ch=0;
    int lines=1;

    if (file == NULL){
        return 0;
    }
    while ((ch = fgetc(file)) != EOF)
        {
        if (ch == '\n')
        lines++;
        }
    fclose(file);
    return lines;
}

void Remote_delLine(int i){
    FILE *file;
    file = fopen(REMOTE_FILE_NAME, "r");
    //Getting the file length
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = (char *) calloc(size, sizeof(char)); //Length of the file
    int ascii=0;
    int current_line=0;
    char ch = 0; 
    int cursor = 0;


    while ((ascii = fgetc(file)) != EOF)
    {
        ch = ascii;
        if (current_line != i)
        {
            content[cursor] = ascii;
            cursor++;
        }
        if (ch == '\n'){
            current_line++;
        }
    }
    fclose(file);
    // Rewrite file without the new content
    file = fopen(REMOTE_FILE_NAME, "w");
    if (file){
        fprintf(file, content);
        fclose(file);
    }
}
