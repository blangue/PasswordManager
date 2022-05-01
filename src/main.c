#include "common.h"
#include "Remote.h"

int main(int argc, char const *argv[])
{
    Remote_askAction();
    char action = 0;
    system("stty cbreak");
    system("stty -echo");
    scanf("%c", &action);
    system("stty -cbreak");
    system("stty echo");
    Remote_onActionResponse(action);
    return 0;
}
