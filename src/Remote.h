#ifndef REMOTE_H
#define REMOTE_H

#define REMOTE_FILE_PATH ("remote.entries")
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

typedef struct {
    int line_index;
    char line[MAX_ENTRY_LENGTH];
} LineInfo;

void Remote_askAction();

void Remote_onActionResponse(char);

void Remote_addEntry();

Entry Remote_getEntry();

void Remote_delEntry();

char Remote_getDomain(); 

LineInfo Remote_findEntry(char *id);

int Remote_getNbLines();

void Remote_delLine(int);

#endif // REMOTE_H