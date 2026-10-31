# ansi-color-chart 1.1

Prints a complete, formatted ANSI color reference chart directly in your terminal. __It covers standard 16-color foreground/background codes, and the full 256-color Xterm palette (system colors, the 6×6×6 RGB color cube, and the 24-step grayscale ramp) with automatic text contrast so every number remains readable.__


Here is the expanded `ansi-color-chart.c` (updated to `v1.1`), which adds **Section 3: 24-bit TrueColor** (`16,777,216` colors) right below the 16-color and 256-color tables.

Modern terminals (including `gnome-terminal` and `xfce4-terminal` on Linux Mint) support 24-bit RGB escape sequences, allowing you to pass exact `0–255` Red, Green, and Blue values directly to the terminal.
