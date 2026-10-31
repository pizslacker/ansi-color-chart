#include <stdio.h>

// Hjelpefunksjon som regner ut en jevn regnbue-verdi (R, G, B) fra 0.0 til 1.0
static void rainbow_rgb(double ratio, int *r, int *g, int *b)
{
    double h = ratio * 6.0;
    int region = (int)h;
    double f = h - region;
    int p = 0;
    int q = (int)(255.0 * (1.0 - f));
    int t = (int)(255.0 * f);

    switch (region % 6) {
        case 0: *r = 255; *g = t;   *b = p;   break;
        case 1: *r = q;   *g = 255; *b = p;   break;
        case 2: *r = p;   *g = 255; *b = t;   break;
        case 3: *r = p;   *g = q;   *b = 255; break;
        case 4: *r = t;   *g = p;   *b = 255; break;
        default:*r = 255; *g = p;   *b = q;   break;
    }
}

int main(void)
{
    const char *pnavn = "ansi-color-chart"; // peker til program-navn.
    const char *pversjon = "1.1";           // peker til program-versjon.

    printf("\033[1;36m%s v%s\033[0m\n", pnavn, pversjon);
    puts("=========================================================================");

    // 1. Standard & Lyse 16-fargers ANSI-koder (30-37 / 40-47)
    puts("\n1. CLASSIC 16-COLOR ANSI-TABLE (Foreground & Background)");
    puts("   Use: \\033[<FG>;<BG>mText\\033[0m  (f.ex. \\033[1;32;40m)\n");

    printf("   %-12s", "FG \\ BG");
    for (int bg = 40; bg <= 47; bg++) {
        printf("  %dm   ", bg);
    }
    printf("\n   %-12s", "------------");
    for (int bg = 40; bg <= 47; bg++) {
        printf("--------");
    }
    putchar('\n');

    for (int fg = 30; fg <= 37; fg++) {
        printf("   %2dm (Normal) ", fg);
        for (int bg = 40; bg <= 47; bg++) {
            printf("\033[%d;%dm  gYw   \033[0m", fg, bg);
        }
        putchar('\n');

        printf(" 1;%2dm (Bold)   ", fg);
        for (int bg = 40; bg <= 47; bg++) {
            printf("\033[1;%d;%dm  gYw   \033[0m", fg, bg);
        }
        putchar('\n');
    }

    puts("\n=========================================================================");
    puts("\n2. 256-FARGERS XTERM-PALETT");
    puts("   Foreground: \\033[38;5;<N>m   |   Background: \\033[48;5;<N>m\n");

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

    puts("\n=========================================================================");
    puts("\n3. 24-BIT TRUECOLOR (16 777 216 FARGER - RGB 0-255)");
    puts("   Foreground: \\033[38;2;<R>;<G>;<B>m   |   Background: \\033[48;2;<R>;<G>;<B>m\n");

    const int bar_width = 64;

    // Rød gradient (0 -> 255)
    printf("   Red   (R: 0-255): ");
    for (int i = 0; i < bar_width; i++) {
        int r = (i * 255) / (bar_width - 1);
        printf("\033[48;2;%d;0;0m ", r);
    }
    puts("\033[0m");

    // Grønn gradient (0 -> 255)
    printf("   Green (G: 0-255): ");
    for (int i = 0; i < bar_width; i++) {
        int g = (i * 255) / (bar_width - 1);
        printf("\033[48;2;0;%d;0m ", g);
    }
    puts("\033[0m");

    // Blå gradient (0 -> 255)
    printf("   Blue   (B: 0-255): ");
    for (int i = 0; i < bar_width; i++) {
        int b = (i * 255) / (bar_width - 1);
        printf("\033[48;2;0;0;%dm ", b);
    }
    puts("\033[0m");

    // Full 24-bit regnbue-gradient
    printf("   24-bit Spectrum : ");
    for (int i = 0; i < bar_width; i++) {
        int r, g, b;
        rainbow_rgb((double)i / (double)bar_width, &r, &g, &b);
        printf("\033[48;2;%d;%d;%dm ", r, g, b);
    }
    puts("\033[0m\n");

    // Eksempel med bestemte RGB- og Hex-verdier (f.eks. Linux Mint & Slackware-farger)
    puts("   Examples for exact RGB-colors in C:");
    printf("   \033[48;2;135;207;62m\033[38;2;0;0;0m  Linux Mint Green  \033[0m -> \\033[48;2;135;207;62m  (Hex: #87CF3E)\n");
    printf("   \033[48;2;19;87;180m\033[38;2;255;255;255m  Slackware Blue     \033[0m -> \\033[48;2;19;87;180m   (Hex: #1357B4)\n");
    printf("   \033[48;2;215;10;83m\033[38;2;255;255;255m  Debian Red        \033[0m -> \\033[48;2;215;10;83m   (Hex: #D70A53)\n\n");

    return 0;
}