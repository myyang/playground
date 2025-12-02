# Unit Testing Example

CMake project demonstrating C++ unit testing structure.

## Structure

```
├── src/           # Source files
│   ├── formula.cpp
│   ├── formula.h
│   └── main.cpp
└── tst/           # Test files
    ├── formula.cpp
    └── main.cpp
```

## Build & Run

```bash
mkdir build && cd build
cmake ..
make
./tst/tests
```
