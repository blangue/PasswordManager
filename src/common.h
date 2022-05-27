#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

//Boolean type
#define true (1)
#define false (0)
typedef int bool;

//Printing color codes
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define DEFAUT  "\033[39m"

/**
 * @def TRACE
 *
 * Fonction utilisée pour afficher des messages de débug
 *
 * @param fmt Texte à afficher
 */
#define TRACE(fmt, ...) do {\
                                fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__);\
                                fflush (stderr);\
                            } while(0);
