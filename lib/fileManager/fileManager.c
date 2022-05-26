#include "fileManager.h"

char *Remote_getWorkingDir(int8_t buff_size){
    char *buf;
    buf=(char *)malloc(buff_size*sizeof(char));
    getcwd(buf,buff_size);
    return buf;
}