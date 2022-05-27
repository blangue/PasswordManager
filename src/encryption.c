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
    char modulos[strlen(p_password)];
    i = 0;
    while (i < strlen(p_password))
    {
        encryptedPassword[i] = 33 + (offset * p_password[i]) % 93;
        modulos[i] = p_password[i]/93;
        i++;
    }
    char separator = '\128';
    memset(p_result, 0, 2 * i + 1);
    strcat(p_result, encryptedPassword);
    p_result[strlen(p_result)+1] = '\0';
    p_result[strlen(p_result)] = separator;
    strcat(p_result, modulos);
    printf("Encoded: %s\r\n", p_result);
}

void decode(char * p_password, char * p_key, char * p_result){
    int offset = 3;
    size_t i = 0;
    while ( p_key[i] != NULL)
    {
        offset += p_key[i];
        i++;
    }
    offset *= i;
    for (size_t i = 0; i < sizeof(p_password); i++)
    {
        p_password[i] /= offset;
    }
}
