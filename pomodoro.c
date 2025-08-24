#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>  // Sleep ve Beep
#else
#include <unistd.h>   // sleep
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
    printf("\a"); // terminal beep
#endif
}

void show_progress(int total_seconds, int elapsed_seconds) {
    int width = 30; // progress bar width
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

void countdown(int minutes, const char* message) {
    int seconds = minutes * 60;
    int elapsed = 0;
    while (seconds > 0) {
        int m = seconds / 60;
        int s = seconds % 60;
        printf("%s: %02d:%02d ", message, m, s);
        show_progress(minutes * 60, elapsed);
        sleep_seconds(1);
        seconds--;
        elapsed++;
    }
    printf("\n%s finished!\n", message);
    beep();
}

int main() {
    int work_time, break_time, rounds;

    printf("Enter work time (minutes): ");
    scanf("%d", &work_time);
    printf("Enter break time (minutes): ");
    scanf("%d", &break_time);
    printf("Enter number of rounds: ");
    scanf("%d", &rounds);

    for (int i = 1; i <= rounds; ++i) {
        printf("\n--- Pomodoro %d ---\n", i);
        countdown(work_time, "Work time");
        countdown(break_time, "Break time");
    }

    printf("\nAll Pomodoro sessions completed!\n");
    beep();
    return 0;
}
