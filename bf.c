#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int main(int argc, char *argv[])
{
    FILE *f = fopen(argv[1], "r");
    fseek(f, 0, SEEK_END);
    size_t fsize = ftell(f);
    rewind(f);
    char *ip = malloc(fsize + 1);
    fread(ip, fsize, 1, f);
    fclose(f);
    ip[fsize] = 0;
    
    uint8_t *dp = calloc(65536, 1);

    while (*ip) {
        switch(*ip) {
        case '>': 
            dp++; break;
        case '<': 
            dp--; break;
        case '+': 
            ++*dp; break;
        case '-': 
            --*dp; break;
        case '.': 
            putchar(*dp); break;
        case ',': 
            *dp = getchar(); break;
        case '[': 
            if (!*dp) {
                int depth = 0;
                while (*ip != ']' || depth != 1) {
                    if (*ip == '[')
                        depth++;
                    else if (*ip == ']')
                        depth--;
                    ip++;
                }
            }
            break;
        case ']': 
            if (*dp) {
                int depth = 0;
                while (*ip != '[' || depth != 1) {
                    if (*ip == ']')
                        depth++;
                    else if (*ip == '[')
                        depth--;
                    ip--;
                }
            }
            break;
        }
        ip++;
    }
            
    return 0;
}
