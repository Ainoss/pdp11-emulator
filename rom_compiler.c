
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


u_int16_t scan_word(char* str)
{
    u_int16_t word = 0;
    int i;
    for (i = 15; i >= 0; i--){
        word += (*(str++) - '0') << i;
    }
    return word;
}

int main()
{
    FILE *fin, *fout;
    char str[1024], sect_name[32] = "";
    unsigned sect_offset = 0, count = 0;
    u_int16_t word, rom[16*1024];
    memset(rom, 0, sizeof(rom));

    fin = fopen("rom.text", "r");
    if (!fin){
        perror("input file");
        return 1;
    }
    fout = fopen("rom.raw", "w");
    if (!fout){
        perror("output file");
        return 1;
    }

    while (1){
        errno = 0;
        if (!fgets(str, sizeof(str), fin)){
            if (errno){
                perror("fgets");
                return 1;
            }
            break;
        }
        if (str[0] == '.'){
            if (sect_name[0] != 0)
                printf("written %u words\n", count);
            count = 0;
            sscanf(str, ".%s %u", sect_name, &sect_offset);
            printf("Section %s: offset=%u\n", sect_name, sect_offset);
            sect_offset /= 2; // convert to word count
        }
        else if (str[0] == '0' || str[0] == '1'){
            word = scan_word(str);
            rom[sect_offset++] = word;
            count++;
        }
        else
            continue;
    }

    fwrite(&rom, sizeof(rom), 1, fout);
    printf("written %u words\n", count);
    printf("Done!\n");

    fclose(fin);
    fclose(fout);
    return 0;
}

