# NCMatrix - `see the code` in style

NCMatrix is a [clone/revamp/cheap imitation] of the novelty terminal program [CMatrix](https://github.com/abishekvashok/cmatrix), leveraging the [notcurses](https://github.com/dankamongmen/notcurses) library to provide a better-looking, and (in the future) more configurable raining code experience.

This program is currently under development, and has not seen widespread testing (which is very welcome).

![ncmatrix-demo](/home/william/Programming/C++/NCMatrix/ncmatrix-demo.gif)

## Requirements:

- (Build) CMake >= 3.14.0
- (Runtime) notcurses >= 1.3.0

## Installation:

1. Clone or download this repository.
2. Create a folder in the downloaded directory, typically `build`.
3. Enter the directory and run `cmake ..`.
4. Run`make`.
5. Run `make install`, or `sudo make install`, depending on file permissions.

Then run `ncmatrix`, and watch the code rain!

Running `make uninstall` in the `build` directory will uninstall the program.

## Special Thanks:

- Nick Black, for creating notcurses, without which this project would be impossible.
- Chris Allegretta, Abishek V. Ashok, and all the contributors to CMatrix, for creating the inspiration for this project.

