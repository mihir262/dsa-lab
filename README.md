# DSA Lab

C programs from the COEP semester 3 data structures lab.

Each folder is one assignment. Types and function declarations live in a `.h` file. The matching `.c` file holds the definitions, and `main` when the program is a single file.

| Folder | What it does | Build |
| --- | --- | --- |
| `01-remove-duplicates` | Drop duplicate values from an array of doubles | `gcc duplicates.c -o duplicates` |
| `02-bigint` | Store and print an arbitrarily long integer | `gcc bigint.c -o bigint` |
| `03-sorting` | Bubble sort and selection sort, with a timing plot | `gcc sorting.c -o sorting` |
| `04-sparse-matrix` | Sparse matrices: create, transpose, add, multiply, update, delete | `gcc sparsematrix.c -o sparsematrix` |
| `05-record-file-sort` | Sort whitespace-separated records in a file by a chosen field | `gcc filesort.c -o filesort` |
| `06-circular-linked-list` | Insert, delete, search, and display on a circular list | `gcc circular.c -o circular` |
| `07-singly-linked-list` | Build a list from an MIS number and delete largest, smallest, first, and last | `gcc list.c -o list` |
| `08-linked-list-operations` | Menu-driven list: delete, count, search, reverse traversal | `gcc list.c -o list` |
| `09-polynomial` | Add, subtract, and multiply polynomials stored as linked lists | `gcc polynomial.c -o polynomial` |
| `10-stack` | Array stack, linked-list stack, infix to postfix, postfix evaluation | `make` |
| `structs` | Complex-number arithmetic and 2D point geometry | `make` |

Run those commands from inside the folder. `10-stack` and `structs` link more than one `.c` file, so use `make`.

`07-singly-linked-list/graphics/` is a raylib visualizer (`make` in that folder; needs raylib). `03-sorting/datagen.c` rewrites `input.txt`. `05-record-file-sort/input.txt` is a small sample record file.
