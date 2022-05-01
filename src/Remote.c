#include "common.h"
#include "Remote.h"
#include <string.h>


void Remote_askAction(){
    printf("You want to:\r\n");
    printf("1 - Add new pwd entry\r\n");
    printf("2 - Delete an entry\r\n");
    printf("3 - Show entries\r\n");
}

void Remote_onActionResponse(char response){
    switch (response) {
        case '1':
        Remote_addEntry();
        break;
        case '2':
        Remote_delEntry();
    }
}

void Remote_addEntry(){
    FILE *file;
    file = fopen(REMOTE_FILE_PATH, "a");
    if (file)
    {
    Entry new_entry = Remote_getEntry();
    fprintf(file, "%s,%s,%s;\r\n", new_entry.id, new_entry.login, new_entry.pwd);
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
    char *seek = Remote_getDomain();
    LineInfo line = Remote_findEntry(seek);
    if (line.line == NULL)
    {
        printf("No matching entry found\r\n");
    }
    else
    {
        printf("The entry was deleted successfully\r\n");
        Remote_delLine(line.line_index);
    }
}

char Remote_getDomain(){
    char domain [ID_MAX_LENGTH];
    printf("Enter a domain to delete the entry of:\r\n");
    scanf("%s", domain);
    return *domain;
}

LineInfo Remote_findEntry(char *id){
    FILE *file;
    LineInfo line;
    file = fopen(REMOTE_FILE_PATH, "r");
    int lines = Remote_getNbLines();
    char l_line[MAX_ENTRY_LENGTH];
    int index = 0;
    if (file)
    {
        bool found = false;
        for (int i = 0; i < lines && !found; i++){
            fscanf(file, "%s\r\n", l_line);
            found = strcmp(l_line, id) == strlen(id); // boubou_est_gentil, boubou --> 6
            line.line_index = i;
        }
    }
    else {
        printf("Unable to open entry file\r\n");
    }  
    strcpy(line.line, l_line);
    fclose(file);
    return line;
}

int Remote_getNbLines(){
    // count the number of lines in the file called filename                                    
    FILE *file = fopen(REMOTE_FILE_PATH, "r");
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
    file = fopen(REMOTE_FILE_PATH, "w");
    char content[MAX_ENTRY_LENGTH * (MAX_ENTRIES-1)];
    int ch=0;
    int lines=0;


    while ((ch = fgetc(file)) != EOF)
        {
        if (lines != i)
        {
            strcat(content, ch);
        }
        if (ch == '\n'){
            lines++;
        }
    }
    fclose(file);
}