#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#ifdef _WIN32
#include <windows.h>
#include <conio.h> // kbhit ve getch
#else
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#endif

void sleep_seconds(int seconds) {
#ifdef _WIN32
    Sleep(seconds * 1000);
#else
    sleep(seconds);
#endif
}

void beep() {
#ifdef _WIN32
    Beep(1000, 500);
#else
    printf("\a"); fflush(stdout);
#endif
}

// Linux/macOS için kbhit ve getch implementasyonu
#ifndef _WIN32
int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

int getch(void) {
    struct termios oldt, newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}
#endif

void show_progress(int total_seconds, int elapsed_seconds) {
    int width = 30;
    float ratio = (float)elapsed_seconds / total_seconds;
    int pos = ratio * width;

    printf("[");
    for (int i = 0; i < width; ++i) {
        if (i < pos) printf("=");
        else if (i == pos) printf(">");
        else printf(" ");
    }
    printf("] %d%%\r", (int)(ratio * 100));
    fflush(stdout);
}

int countdown(int minutes, const char* message) {
    int seconds = minutes * 60;
    int elapsed = 0;
    int paused = 0;

    while (seconds > 0) {
        if (kbhit()) {
            char c = tolower(getch());
            if (c == 'p') {
                paused = !paused;
                if(paused) printf("\nPaused. Press 'p' to resume.\n");
                else printf("Resumed.\n");
            } else if (c == 's') {
                printf("\nSkipped!\n");
                return 0; // skip current countdown
            }
        }

        if(!paused) {
            int m = seconds / 60;
            int s = seconds % 60;
            printf("%s: %02d:%02d ", message, m, s);
            show_progress(minutes * 60, elapsed);
            sleep_seconds(1);
            seconds--;
            elapsed++;
        } else {
            sleep_seconds(1);
        }
    }

    printf("\n%s finished!\n", message);
    beep();
    return 0;
}

int main() {
    int work_time, break_time, rounds;

    printf("Enter work time (minutes): ");
    scanf("%d", &work_time);
    printf("Enter break time (minutes): ");
    scanf("%d", &break_time);
    printf("Enter number of rounds: ");
    scanf("%d", &rounds);

    int total_work = 0;
    int total_break = 0;
    int completed_rounds = 0;

    for (int i = 1; i <= rounds; ++i) {
        printf("\n--- Pomodoro %d ---\n", i);
        countdown(work_time, "Work time");
        total_work += work_time;
        countdown(break_time, "Break time");
        total_break += break_time;
        completed_rounds++;
        printf("Statistics so far:\n");
        printf("Completed rounds: %d\n", completed_rounds);
        printf("Total work time: %d minutes\n", total_work);
        printf("Total break time: %d minutes\n", total_break);
    }

    printf("\nAll Pomodoro sessions completed!\n");
    printf("Final statistics:\n");
    printf("Total completed rounds: %d\n", completed_rounds);
    printf("Total work time: %d minutes\n", total_work);
    printf("Total break time: %d minutes\n", total_break);

    beep();
    return 0;
}
