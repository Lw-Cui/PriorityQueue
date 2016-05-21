# PriorityQueue

Thread-safe Queue in C++.

## Compile and link
### Standalone
```
mkdir build && cd build
cmake ..
make && make test
```
### Submodule
When using a git submodule and CMake-buildsystem, add the following lines to your `CMakeLists.txt`:
```
ADD_SUBDIRECTORY(PriorityQueue)
```
This will produce an important CMake variable, `PRIORITYQUEUE_INCLUDE_DIRS`, which you'll use in the typical way:
```
INCLUDE_DIRECTORIES(${PRIORITYQUEUE_INCLUDE_DIRS})
```
