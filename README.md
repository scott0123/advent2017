# advent2017
These are my solutions to the "Advent of Code 2017" event. Feel free to look at them.

## Important
You must have my custom input/output library "IO" installed or it wont compile.

you can find this [here](https://github.com/scott0123/IO)

The file structure should look like:

* IO
    * stuff in the IO folder
* advent2017
    * main.cpp
    * Makefile
    * other stuff in advent2017 folder

## Compiling
1. Put the desired day's function in the `main()` function in main.cpp
    ```
    int main(){

        day1();
        return 0;
    }
    ```
2. Run the `make` command
    If this fails, try `make clean` and then `make`
3. Run `./advent`
