# First-Year C and C++ Labs

[Русская версия](README.md)

Lab assignments and practice programs from the first year of university (2022–2023).

## C (`Labs.c`)

All the labs are in one file: each sits in its own commented-out block with its own `main`. To run one, uncomment its block.
- **Arrays:** processing through a pointer and the arithmetic mean of elements.
- **Matrices:** dynamic, with rows of different lengths; the user enters the number of rows and columns.
- **Geometry:** a triangle's height to a chosen side from its three sides.
- **Pointers:** array addresses and moving data between arrays.
- **Strings:** right-aligning a string.
- **Numbers:** a factorial and input validation.

## C++

| File | What it does |
|---|---|
| `1703.cpp` | A class with private fields, input and output of values |
| `menu.cpp` | A console menu: character registration (name, race, class, attack) saved to a file |
| `NewCharacter.cpp` | A character class reading and writing files through `fstream` |

## Quick start

```bash
gcc Labs.c -o labs && ./labs
g++ 1703.cpp -o 1703 && ./1703
```

`menu.cpp` and `NewCharacter.cpp` use `conio.h`, so they build on Windows.

Program prompts are in Russian.

## Tech stack

C, C++, Visual Studio.

## License

[MIT](../../LICENSE)
