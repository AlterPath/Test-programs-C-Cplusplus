# POSIX Threads in C: Real-Time Systems Practice

[Русская версия](README.md)

Practice tasks for the "Real-Time Computing Systems" course (November–December 2024): multithreaded C programs with pthreads on Linux.

| Practice | Files | Contents |
|---|---|---|
| 13 | `1_v1.c`, `1_v2.c` | Two threads print messages. In the second version, two mutexes set the order in which they alternate. Ctrl+C is caught by a SIGINT handler |
| 13 | `2_v1.c`, `2_v2.c` | A simulation: five cats eat from a shared bowl, and the owner refills it once a "day" (7 s). The shared resource is protected by mutexes |
| 14 | `1.c`, `2.c` | Dining philosophers. In the first version the last philosopher picks up the forks in reverse order to avoid deadlock. In the second, a philosopher tries to take both forks: if the second one is busy, they release the first and wait on a condition variable |
| 15 | `main.c` | A production line on semaphores: parts A, B and C are made in parallel and assembled into a module and a product |
| 16 | `main.c` | A bounded message queue (a ring buffer) on semaphores: producers and consumers |

Program output and comments are in Russian.

## Quick start

```bash
gcc -pthread practice-14/2.c -o philosophers
./philosophers
```

## Tech stack

C, POSIX threads (mutex, condition variable, semaphore), signals, Linux.

## License

[MIT](../../LICENSE)
