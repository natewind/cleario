// Windows

#include <conio.h>

getch()

// Unix-like

#include <stdio.h>
#include <termios.h> // termios, TCSANOW, ECHO, ICANON
#include <unistd.h>  // STDIN_FILENO

static struct termios oldt, newt;

// tcgetattr gets the parameters of the current terminal
// STDIN_FILENO will tell tcgetattr that it should write the settings
// of stdin to oldt
tcgetattr(STDIN_FILENO, &oldt);

// Now the settings will be copied
newt = oldt;

// ICANON normally takes care that one line at a time will be processed
// that means it will return if it sees a "\n" or an EOF or an EOL
// If you want to disassociate the input from the output,
// you also have to turn of the ECHO flag.
newt.c_lflag &= ~(ICANON | ECHO);

// Those new settings will be set to STDIN
// TCSANOW tells tcsetattr to change attributes immediately.
tcsetattr(STDIN_FILENO, TCSANOW, &newt);

char c = getchar();

// Restore the old settings
tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
