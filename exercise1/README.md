# Qt QWidget C++ Exercise Collection

This project contains exercises for learning Qt QWidget development in C++.

## Project Structure

```
exercise1/
├── CMakeLists.txt          # CMake build configuration
├── main.cpp               # Application entry point
├── exercise1window.h      # Exercise 1 window class header
├── exercise1window.cpp    # Exercise 1 window class implementation
└── README.md             # This file
```

## Exercise 1.1: Basic Window

**Requirements:**
- Create a simple application that displays an empty window
- Window title: "My First Qt Window"
- Fixed size: 400x300 pixels
- Window should appear in the center of the screen

**Implementation:**
- `Exercise1Window` class inherits from `QWidget`
- Uses `setWindowTitle()` to set the window title
- Uses `setFixedSize()` to set the window dimensions
- Implements `centerWindow()` method to position window in screen center

## Build Instructions

### Prerequisites
- Qt6 development libraries
- CMake 3.16 or higher
- C++17 compatible compiler

### Ubuntu/Debian
```bash
sudo apt install qt6-base-dev cmake build-essential
```

### Building
```bash
mkdir build
cd build
cmake ..
make
```

### Running
```bash
./exercise1
```

## Key Qt Concepts Demonstrated

1. **QApplication**: Main application object that manages GUI application control flow
2. **QWidget**: Base class for all user interface objects
3. **QScreen**: Access to screen properties for window positioning
4. **Window properties**: Setting title, size, and position
5. **CMake integration**: Using Qt6 with CMake build system

## Next Steps

This foundation exercise demonstrates the basics of creating a Qt application window. Future exercises will build upon this by adding:
- Layouts and widgets
- Event handling
- Signals and slots
- Custom painting
- And more Qt features