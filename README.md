# Small technical task

I coded this to show my developer skills to an enterprise job application.

The requirements of this task were the following:
- Design and implement a Back/account manager in C++.
- More requirement details are not provided to disallow copy.

## Building

To configure the program, the API documentation, and the Unit Tests, follow the following steps.

### Dependencies
- [CMake](https://cmake.org/) version 3.20.
- A C++ compiler.
- In Windows, Visual Studio 14.
- [Doxygen](https://doxygen.nl/) version 1.9 or superior.
- [Graphviz](https://graphviz.org/) version 5 or superior.

Once the dependencies are solved, execute the following depending on your target OS.

### Linux
```bash
git clone https://github.com/ccostagliola/small_technical_task.git
cd small_technical_task
mkdir build
cd build
cmake ..
cmake --build .
```
Once finished, the outcome will be in the following directories:

- Program: small_technical_task/build/tech_task
- API documentation: small_technical_task/build/doc/doc_doxygen/html/index.html

### Windows
For Windows you have to indicate Visual Studio target to cmake:
```bash
git clone https://github.com/ccostagliola/small_technical_task.git
cd small_technical_task
mkdir build
cd build
cmake -G "Visual Studio 14 2015" -A Win64 ..
cmake --build .
```
## Usage

To execute the program:

```bash
cd small_technical_task/build
tech_task
```

# Testing
To run all the Unit Tests:
```bash
cd small_technical_task/build
ctest
```
## Author
Claudio Costagliola Fiedler (claudio.costagliola@gmail.com)
