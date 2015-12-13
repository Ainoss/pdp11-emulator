
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "emulator.h"

unsigned init()
{
    u_int16_t rom[16*1024];
    FILE *fin = fopen("rom.raw", "r");
    if (!fin){
        perror("opening rom file");
        return 1;
    }

    if (!fread(rom, sizeof(rom), 1, fin)){
        perror("reading rom file");
        return 1;
    }

    pdp11_init(&rom);

    fclose(fin);
    return 0;
}


int main()
{
    char str[1024];
    char last = 0;
    int stop = 0;

    init();

    while (!stop){
        printf("\n> ");
        errno = 0;
        if (!fgets(str, sizeof(str), stdin)){
            if (errno){
                perror("fgets");
                return 1;
            }
            break;
        }
        if (str[0] == '\n')
            str[0] = last;
        switch (str[0]) {
            case 's': 
                if (pdp11_step())
                    printf("Error while stepping\n");;
                last = str[0];
                break;
            case 'd':
                pdp11_debug();
                last = str[0];
                break;
            case 'q':
                stop = 1;
                last = str[0];
                break;
            default:
                printf("Invalid command\n");
        }
    }

    return 0;
}

