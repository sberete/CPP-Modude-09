# CPP-Module-09

This project is part of the 42 school C++ curriculum. It is the final module, combining STL containers, parsing, and algorithmic complexity constraints.

## Exercises

- **ex00** — Implements `BitcoinExchange`, a program that parses a CSV database of historical Bitcoin prices and evaluates a list of date/value pairs from an input file, handling invalid dates, values, and formatting errors.
- **ex01** — Implements an `RPN` (Reverse Polish Notation) calculator that evaluates arithmetic expressions given in postfix notation using a stack-based approach.
- **ex02** — Implements `PmergeMe`, a program that sorts a sequence of positive integers using the merge-insertion sort (Ford-Johnson) algorithm, comparing performance between two different STL containers.

- ## Build

- Each exercise has its own Makefile:
- ```
  cd ex00 && make   # builds the ex00 executable
  ```
  Repeat inside `ex01` and `ex02` as needed. Use `make clean`, `make fclean`, or `make re` to clean/rebuild.

  ## Constraints

  - Follows the 42 Norm
  - Compiles without errors or warnings (`-Wall -Wextra -Werror`)
  - Written in C++98
