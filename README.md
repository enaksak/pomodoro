# Console Pomodoro Timer (C Language)

A simple **cross-platform console-based Pomodoro timer** written in **C**.  
Supports work/break cycles, progress bars, pause/resume, skip, and statistics.

---

## Features

- Set **custom work time**, **break time**, and **number of rounds**.
- **Progress bar** and countdown timer displayed in the console.
- **Pause/resume** (`p` key) and **skip current countdown** (`s` key).
- **Sound alert** when work or break ends (works on Windows/Linux/macOS).
- **Real-time statistics**: completed rounds, total work time, total break time.

---

## Usage
1. Clone the repository:

```bash
git clone https://github.com/yourusername/console-pomodoro-c.git
cd console-pomodoro-c

Run the program:
Windows (with MinGW or MSVC)
gcc -o pomodoro pomodoro.c


Linux/macOS
gcc -o pomodoro pomodoro.c

Follow prompts:

Enter work time (minutes)

Enter break time (minutes)

Enter number of rounds

Control during countdown:

Press p to pause/resume

Press s to skip the current countdown


Works on Windows, Linux, and macOS.

Uses platform-specific Sleep and Beep for timing and sound.

Non-blocking keyboard input implemented for cross-platform pause/skip support.

License

This project is licensed under the MIT License.



./pomodoro   # Linux/macOS
pomodoro.exe # Windows
