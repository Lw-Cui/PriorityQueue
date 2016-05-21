# PriorityQueue

Thread-safe Queue in C++.

## Compile and link
### Submodule
When using a git submodule and CMake-buildsystem, add this repository as a submodule of your root repository:
```
git submodule add git@github.com:Lw-Cui/PriorityQueue.git
git submodule update --init --recursive
```
and then add the following lines to your `CMakeLists.txt`:
```
ADD_SUBDIRECTORY(PriorityQueue)
```
This will produce an important CMake variable, `PRIORITYQUEUE_INCLUDE_DIRS`, which you'll use in the typical way:
```
INCLUDE_DIRECTORIES(${PRIORITYQUEUE_INCLUDE_DIRS})
```
