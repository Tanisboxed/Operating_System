#include <stdio.h>
#include <conio.h>

int ssize, fsize, frame[10], rstring[30];

int main() {
    int i, cs = 0, pf = 0, y, k, z = 0;

    int found(int x);
    void display();

    printf("\n\t\tFIFO PAGE REPLACEMENT ALGORITHM\n");
    printf("\t\t-------------------------------\n");
    printf("\n\tEnter the size of the frame: ");
    scanf("%d", &fsize);
    printf("\n\tEnter the number of reference strings: ");
    scanf("%d", &ssize);
    printf("\n\tEnter the strings: ");
    for (i = 0; i < ssize; i++)
        scanf("%d", &rstring[i]);

    for (k = 0; k < fsize; k++)
        frame[k] = -1;

    for (i = 0; i < ssize; i++) {
        y = found(rstring[i]);
        if (y == 0) {
            pf++;
            frame[z] = rstring[i];
            z = (z + 1) % fsize;
            display();
        }
    }

    printf("\n\n\tPage faults: %d", pf);
    getch();
    return 0;
}

int found(int x) {
    int i, val = 0;
    for (i = 0; i < fsize; i++) {
        if (x == frame[i]) {
            val = 1;
            break;
        }
    }
    return val;
}

void display() {
    int i;
    printf("\n");
    for (i = 0; i < fsize; i++) {
        if (frame[i] == -1)
            printf("\t");
        else
            printf("%d\t", frame[i]);
    }
}
