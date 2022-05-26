#ifndef REMOTE_H
#define REMOTE_H

#define REMOTE_FILE_NAME ("remote.entries")
#define FILE_SEPARATOR ("/")
#define ID_MAX_LENGTH (30)
#define LOGIN_MAX_LENGTH (40)
#define PWD_MAX_LENGTH (25)
#define MAX_ENTRIES (500)
#define MAX_ENTRY_LENGTH (ID_MAX_LENGTH+LOGIN_MAX_LENGTH+PWD_MAX_LENGTH+3)

typedef struct {
    char id[ID_MAX_LENGTH];
    char login[LOGIN_MAX_LENGTH];
    char pwd[PWD_MAX_LENGTH];
} Entry;

void Remote_askAction();

bool Remote_onActionResponse(char);

void Remote_addEntry();

Entry Remote_getEntry();

void Remote_delEntry();

void Remote_getDomain(char []); 

int Remote_findEntry(char*);

int Remote_getNbLines();

void Remote_delLine(int);

char *Remote_getEntryFilePath();

#endif // REMOTE_H