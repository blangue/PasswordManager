#include "encryption.h"

void encode(char * p_password, char * p_key, char * p_result){
    // Check password length
    if (sizeof(p_password) > MAX_PWD_SIZE)
    {
        TRACE("Password to encode is too long, aborting...");
        exit(1);
    }
    
    int offset = 3;
    size_t i = 0;
    while ( i < strlen(p_key))
    {
        offset += p_key[i];
        i++;
    }
    offset *= i;
    char encryptedPassword[strlen(p_password)];
    char modulos[2 * strlen(p_password)];
    i = 0;
    while (i < strlen(p_password))
    {
        encryptedPassword[i] = 33 + (offset * p_password[i]) % 93;
        u_int16_t mod1 = (offset * p_password[i]) / 93;
        u_int16_t mod2 = mod1 / CHAR_MAX;
        mod1 %= CHAR_MAX;
        modulos[i*2] = (mod1 == 0) ? -1 : mod1; //The rest
        modulos[i*2 + 1] = (mod2 == 0) ? -1 : mod2; // The quotient
        i++;
    }
    memset(p_result, 0, 2 * i + 1);
    strcat(p_result, encryptedPassword);
    p_result[strlen(p_result)+1] = '\0';
    p_result[strlen(p_result)] = '\171';
    strcat(p_result, modulos);
    TRACE("Encoded: %s\r\n", p_result);
}

void decode(char * p_password, char * p_key, char * p_result){
    // Check password length
    if (sizeof(p_password) > MAX_PWD_SIZE)
    {
        TRACE("Password to encode is too long, aborting...");
        exit(1);
    }   

    char *incomingStr = malloc(MAX_PWD_SIZE * 2);
    memset(incomingStr, 0, MAX_PWD_SIZE);
    strcpy(incomingStr, strtok(p_password, "\171"));
    char incomingModulos[MAX_PWD_SIZE];
    memset(incomingModulos, 0, MAX_PWD_SIZE);
    strcpy(incomingModulos, strtok(NULL, "\171"));
    

    int offset = 3;
    size_t i = 0;
    while ( i < strlen(p_key))
    {
        offset += p_key[i];
        i++;
    }
    offset *= i;

    for (size_t i = 0; i < strlen(incomingStr); i++)
    {
        u_int32_t temp, rest, quotient;
        temp = incomingStr[i] - 33;
        rest = (incomingModulos[i * 2] == -1) ? 0 : incomingModulos[i * 2];
        quotient = ((incomingModulos[i * 2 + 1] == -1) ? 0 : incomingModulos[i * 2 + 1]);
        temp += 93 * (rest + quotient * CHAR_MAX);
        temp /= offset;
        assert(temp <= UCHAR_MAX);
        p_result[i] = temp;
    }

}
