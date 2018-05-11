# Wa-Tor 4th Year Concurrency Project

This project is an implementation of the Wa-Tor simulation which is a population dynamics simulation using sharkes and fish. More can be read about Wa-Tor here: https://en.wikipedia.org/wiki/Wa-Tor

## Authors

[Eamonn Gaynor](https://github.com/eamonngaynor) & [Peter Cronin](https://github.com/peadarcronin)

## Getting Started

### Prerequisites

C++ Compiler(See [here](https://www.tutorialspoint.com/cplusplus/cpp_environment_setup.htm) for instructions for your machine.)

### Running The Program

Clone the repository to a folder of your choosing using ```git clone https://github.com/eamonngaynor/CDDProject.git``` in your terminal. Navigate to the Concurrent Implementation folder and then enter ```make``` to run the Makefile and compile the program. Finally, enter ```./main``` and the simulation will run.

## Things to Note

When the simulation is run, the number of moves and the average frames per second are displayed. The sharks are denoted as Xs and the fish are Os. The frames per second per move and total time taken is written to a text file stored in the folder. This is done for benchmarking purposes. The first section of this project can be found in the folder Concurrent Implementation and the second within the Optimization folder within that.

## Screenshots

![alt tag](https://i.imgur.com/pv1nqzi.png "Wa-Tor")
![alt tag](https://i.imgur.com/RKOkc88.png "Wa-Tor Benchmarking")

## License:

MIT License
Copyright (c) 2017 Eamonn Gaynor Peter Cronin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
