# mkenv

A simple script for managing `.env` files.  If you have a `.env.development` and a `.env.staging` and so on, `mkenv` provides `set` and `show` commands for moving the contents of these files back and forth to the `.env` file used by many tools these days, so you don't have to copy and paste.  It's fairly trivial, and C is obviously overkill for the implementation, but for my own betterment I'm trying to discipline myself to use C more often when I want something, rather than using a higher level scripting langugage.


## Installation

Requirements:

- `gcc` (I have version 9.3)
- `make` (I have version 4.2)

Building:

- `make`

Installation:

- Copy `./build/mkenv` to wherever you want to install the program


## Usage

Output of `mkenv --help`:

```
Usage:
        mkenv [cmd] [args...]

        show            display currently active environment
        set [env]       set .env file to [env]
        --help          display usage information
```
