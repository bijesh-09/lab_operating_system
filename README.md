# Operating System Lab (C Programs)

A collection of C programs for the Operating System lab, covering processes, threads, synchronization, CPU scheduling, memory management, page replacement, disk scheduling, file and directory handling, and a menu-driven OS simulator that ties many of them together.

> **Please read the sections "Important: Running Q28" and "Use Linux" below before running anything.**

---

## Table of Contents

1. [What is covered](#what-is-covered)
2. [Code quality: what to expect](#code-quality-what-to-expect)
3. [How to clone, compile and run](#how-to-clone-compile-and-run)
4. [Important: Running Q28](#important-running-q28)
5. [Use Linux](#use-linux)
6. [Known limitations of the lecturer-provided programs](#known-limitations-of-the-lecturer-provided-programs)
7. [Folder structure](#folder-structure)
8. [A note on how this was made](#a-note-on-how-this-was-made)

---

## What is covered

| Lab | File(s) | Topic | Origin |
|---|---|---|---|
| 1 | `q1.c` | `getpid()` and `getppid()` system calls | Written by me |
| 2 | `q2.c` | Creating a child process with `fork()` | Written by me |
| 3 | `q3.c` | Multiple child processes and their PIDs | Written by me |
| 4 | `q4.c` | `wait()` for process synchronization | Written by me |
| 5 | `q5.c` | IPC using `pipe()` | Written by me |
| 6 | `q6.c` | FCFS CPU scheduling | Written by me |
| 7 | `q7a.c`, `q7b.c` | SJF and SRTF CPU scheduling | Written by me |
| 8 | `q8.c` | Priority scheduling | Written by me |
| 9 | `q9.c` | Round Robin scheduling | Written by me |
| 10 | `q10.c` | Multiple threads using POSIX `pthread` | Written by me |
| 11 | `q11.c` | Producer-Consumer problem | Written by me |
| 12 | `q12.c` | Reader-Writer problem using semaphores | Written by me |
| 13 | `q13.c` | Dining Philosophers problem | Written by me |
| 14 | `q14.c` | Banker's Algorithm (deadlock avoidance) | Written by me |
| 15 | `q15.c` | First Fit, Best Fit, Worst Fit memory allocation | Written by me |
| 16 | `q16.c` | FIFO page replacement | **Lecturer's code** |
| 17, 18 | `q17and18.c` | LRU and Optimal page replacement (one menu-driven program) | **Lecturer's code** |
| - | `second_chance.c` | Second Chance page replacement (extra) | **Lecturer's code** |
| 19 | `q19.c` | FCFS disk scheduling | **Lecturer's code** |
| 20 | `q20.c` | SSTF disk scheduling | **Lecturer's code** |
| 21 | `q21.c` | SCAN disk scheduling | **Lecturer's code** |
| 22 | `q22.c` | C-SCAN disk scheduling | **Lecturer's code** |
| 23 | `q23.c` | LOOK disk scheduling | **Lecturer's code** |
| 24 | `q24.c` | C-LOOK disk scheduling | **Lecturer's code** |
| 25 | `q25.c` | File operations (create, read, write, append, copy) | Written by me |
| 26 | `q26.c` | Directory operations and listing with `dirent.h` | Written by me |
| 27 | `q27.c` | Display and modify file permissions with `chmod()` | Written by me |
| 28 | `q28.c` | Menu-driven OS simulator (launches CPU scheduling, memory allocation, page replacement and disk scheduling programs) | Written by me |

Case study theory (DOS/Windows, UNIX, Linux) is part of the lab report and not included as code.

---

## Code quality: what to expect

The programs fall into two groups, and the quality differs between them.

### Programs written by me (Labs 1-15, 25-28)

These are the programs I wrote and worked through myself, debugging them step by step (with AI assistance for finding and understanding bugs). For these programs:

- I traced the logic by hand and fixed the bugs I ran into, rather than just accepting the first version that compiled.
- They were checked against different inputs and edge cases (for example, processes that fit in no memory block, missing files, invalid menu input, failed system calls).
- They have **comments explaining what each part does**, so you can read them and understand the reasoning, not just copy the output.
- Errors are reported with clear messages (for example, `perror()` in the file, directory and permission programs).

If you want to learn from this repo, **these are the files to read.**

### Programs copied from the lecturer's code (Labs 16-24 and `second_chance.c`)

The **page replacement** and **disk scheduling** programs were copied from the lecturer's code and are **not** written or reviewed to the same standard:

- I did not rewrite them, so they do not have the same detailed comments.
- They do not handle every case. Some inputs can give wrong results or undefined behavior (see [Known limitations](#known-limitations-of-the-lecturer-provided-programs)).
- Use them to see the algorithms run on normal inputs, not as a model of careful coding.

---

## How to clone, compile and run

```bash
git clone https://github.com/bijesh-09/lab_operating_system.git
cd lab_operating_system
mkdir -p bin
```

Compile and run any single program (example: Lab 15):

```bash
gcc q15.c -o ./bin/q15 && ./bin/q15
```

Note that you run `./bin/q15`, **not** `q15.c`. The `.c` file is the source, and the executable is inside `bin/`.

---

## Important: Running Q28

`q28.c` is an OS simulator that **launches the other programs** in this repo (`q6`, `q7a`, `q7b`, `q8`, `q9`, `q15`, `q16`, `q17and18`, `second_chance`, and `q19` to `q24`). It does not contain their code. Instead, it compiles and runs the matching `.c` file when you choose it from the menu.

Because of this, **Q28 works only if the repo is cloned and left exactly as it is.** Otherwise it will fail. Specifically:

- **Do not rename or delete** any `qN.c` file or `second_chance.c`. Q28 looks for these exact names.
- **Do not move files into subfolders.** All `.c` files must stay together in the same folder as `q28.c`.
- **Run it from the repo's root folder** (the folder that contains all the `.c` files). Q28 uses relative paths like `q6.c` and `bin/`, so running it from another directory will make it fail to find the files.
- **`gcc` must be installed** and available in your `PATH`, since Q28 compiles the programs when you select them.
- The `bin/` folder is created automatically if it is missing.

Run it like this:

```bash
cd lab_operating_system
gcc q28.c -o ./bin/q28 && ./bin/q28
```

If you change file names or the folder layout, you must also edit the file names listed in the arrays inside `q28.c`.

---

## Use Linux

**Please run these programs on Linux** (Ubuntu, Debian, Fedora, etc.). Many of them depend on Linux/UNIX-specific features and will not compile or will not behave as intended elsewhere:

- `fork()`, `wait()`, `pipe()`, `getpid()` and `getppid()` (Labs 1-5) do not exist on native Windows.
- POSIX threads and semaphores (Labs 10-13) work reliably on Linux. Some parts (for example unnamed semaphores) are not supported on macOS.
- `dirent.h`, `chmod()`, `mkdir()`, `unistd.h` (Labs 25-27) are UNIX APIs.
- Q28 relies on a UNIX shell (`system()` running `gcc ... && ./bin/...`).

**If you are on Windows**, use **WSL (Windows Subsystem for Linux)**, a Linux virtual machine, or a Linux live USB. Running these files with Windows compilers (such as MinGW or MSVC) will fail or give incorrect output for many labs.

---

## Known limitations of the lecturer-provided programs

These come from the lecturer's original code, which I have not modified. If you use them, be aware of the following:

| Program | Limitation |
|---|---|
| `q16.c` (FIFO) | While frames are still filling up, a page hit before the frames are full can make the code write to the wrong index, and it can go out of bounds. It works correctly when the first hit happens after the frames are full. Fix: use `temp[pageFaults - 1]` when adding a page. |
| `q17and18.c` (Optimal / LRU) | Choose **option 1 (enter data) first** before running an algorithm. In Optimal, a page that is never used again looks the same as an empty frame, so the frames display can look odd. The page fault count is still correct. |
| `q20.c` (SSTF) | Uses 1000 as the "already served" marker, so every request must be **less than 1000**. |
| `q21.c` to `q24.c` (SCAN, C-SCAN, LOOK, C-LOOK) | If **all requests are on one side of the head**, an internal index is never set and the result is unpredictable. Also avoid a request equal to the initial head position. |
| `q22.c` (C-SCAN) | The value `199` is hardcoded, so it is only correct for a disk size of **200**. It also does **not count the return jump**, while some textbooks do, so check which convention your course expects. |
| `q24.c` (C-LOOK) | Does not count the return jump either, for the same reason. |

For Q19 to Q24, the standard test input is: requests `98 183 37 122 14 124 65 67`, initial head `53`, disk size `200`.

---

## Folder structure

```
lab_operating_system/
├── bin/                 # compiled executables (created when you compile)
├── q1.c ... q5.c        # processes and IPC
├── q6.c, q7a.c, q7b.c, q8.c, q9.c     # CPU scheduling
├── q10.c ... q14.c      # threads, synchronization, deadlock
├── q15.c                # memory allocation
├── q16.c, q17and18.c, second_chance.c # page replacement
├── q19.c ... q24.c      # disk scheduling
├── q25.c ... q27.c      # file, directory, permissions
├── q28.c                # menu-driven OS simulator
└── README.md
```

---

## A note on how this was made

The programs I wrote (Labs 1-15 and 25-28) were built with AI assistance for debugging and explanation. I went through the bugs and the logic myself to understand them. The page replacement and disk scheduling programs (Labs 16-24 and `second_chance.c`) are the lecturer's code, copied as-is.

This repo is for learning and lab submission. If you spot a mistake, feel free to open an issue.