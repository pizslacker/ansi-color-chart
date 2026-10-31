#include <stdio.h>

int main(void)
{
    const char *pnavn = "ansi-color-chart"; // peker til program-navn.
    const char *pversjon = "1.0";           // peker til program-versjon.

    printf("\033[1;36m%s v%s\033[0m\n", pnavn, pversjon);
    puts("=========================================================================");

    // 1. Standard & Lyse 16-fargers ANSI-koder (30-37, 90-97 / 40-47, 100-107)
    puts("\n1. KLASSISK 16-FARGERS ANSI-TABELL (Forgrunn & Bakgrunn)");
    puts("   Bruk: \\033[<FG>;<BG>mTekst\\033[0m  (f.eks. \\033[1;32;40m)\n");

    printf("   %-12s", "FG \\ BG");
    for (int bg = 40; bg <= 47; bg++) {
        printf("  %dm   ", bg);
    }
    printf("\n   %-12s", "------------");
    for (int bg = 40; bg <= 47; bg++) {
        printf("--------");
    }
    putchar('\n');

    // Gå gjennom normal (30-37) og fet/lys (1;30-1;37) samt høy-intensitet (90-97)
    for (int fg = 30; fg <= 37; fg++) {
        // Normal forgrunn
        printf("   %2dm (Normal) ", fg);
        for (int bg = 40; bg <= 47; bg++) {
            printf("\033[%d;%dm  gYw   \033[0m", fg, bg);
        }
        putchar('\n');

        // Fet / Lys (1;3Xm)
        printf(" 1;%2dm (Bold)   ", fg);
        for (int bg = 40; bg <= 47; bg++) {
            printf("\033[1;%d;%dm  gYw   \033[0m", fg, bg);
        }
        putchar('\n');
    }

    puts("\n=========================================================================");
    puts("\n2. 256-FARGERS XTERM-PALETT");
    puts("   Forgrunn: \\033[38;5;<N>m   |   Bakgrunn: \\033[48;5;<N>m\n");

    // 2A. Systemfarger (0 - 15)
    puts("   Systemfarger (0 - 15):");
    for (int i = 0; i < 16; i++) {
        if (i == 0 || i == 8) printf("   ");
        int fg_text = (i == 0 || (i >= 1 && i <= 6) || i == 8) ? 15 : 0;
        printf("\033[48;5;%dm\033[38;5;%dm %3d \033[0m ", i, fg_text, i);
        if (i == 7 || i == 15) putchar('\n');
    }

    // 2B. 6x6x6 RGB-fargekube (16 - 231)
    puts("\n   6x6x6 RGB-fargekube (16 - 231):");
    for (int row = 0; row < 6; row++) {
        printf("   ");
        for (int block = 0; block < 6; block++) {
            for (int col = 0; col < 6; col++) {
                int color = 16 + (block * 36) + (row * 6) + col;
                // Velg hvit (15) eller svart (0) tekst basert på grønn-komponenten (row)
                int fg_text = (row < 3) ? 15 : 0;
                printf("\033[48;5;%dm\033[38;5;%dm%3d\033[0m", color, fg_text, color);
            }
            putchar(' ');
        }
        putchar('\n');
    }

    // 2C. Gråskala (232 - 255)
    puts("\n   Gråskala-rampe (232 - 255):");
    for (int i = 232; i < 256; i++) {
        if (i == 232 || i == 244) printf("   ");
        int fg_text = (i < 244) ? 15 : 0;
        printf("\033[48;5;%dm\033[38;5;%dm %3d \033[0m", i, fg_text, i);
        if (i == 243 || i == 255) putchar('\n');
    }

    putchar('\n');
    return 0;
}