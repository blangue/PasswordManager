#include "common.h"
#include "Remote.h"
#include "encryption.h"
#include <assert.h>

int main(int argc, char const *argv[])
{
    // bool l_continue = true;
    // char action = 0;
    // while(l_continue){
    //     Remote_askAction();
    //     system("stty cbreak");
    //     system("stty -echo");
    //     scanf(" %c", &action);
    //     system("stty -cbreak");
    //     system("stty echo");
    //     l_continue = Remote_onActionResponse(action);
    // } 
    // ** Init **
    char test[] = "coucou";
    assert(strlen(test) < MAX_PWD_SIZE);

    char encodedTest[MAX_PWD_SIZE * 2 + 1];
    memset(encodedTest, 0, sizeof(encodedTest));

    char decodedTest[MAX_PWD_SIZE * 2 + 1];
    memset(decodedTest, 0, sizeof(decodedTest));
    char key[MAX_PWD_SIZE];

    // ** Testing **
    printf("Enter key: \r\n");
    scanf("%30s", key);
    TRACE("Encoding: %s\r\n", test);
    encode(test, key, encodedTest);
    TRACE("Decoding: %s\r\n", encodedTest);
    decode(test, key, decodedTest);
    TRACE("Decoded: %s\r\n", decodedTest);
    return 0;
}
