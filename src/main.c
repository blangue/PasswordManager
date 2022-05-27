#include "common.h"
#include "Remote.h"
#include "encryption.h"
#include <assert.h>

int main(int argc, char const *argv[])
{
    bool l_continue = true;
    char action = 0;
    while(l_continue){
        Remote_askAction();
        system("stty cbreak");
        system("stty -echo");
        scanf(" %c", &action);
        system("stty -cbreak");
        system("stty echo");
        l_continue = Remote_onActionResponse(action);
    } 
    return 0;
}
