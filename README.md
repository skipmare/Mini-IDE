# Mini-IDE 💻
*A C++ project for automata, regex to ENFA/DFA conversion, and state machine simulation.*

## 📖 Overview
**Mini-IDE** is a C++ implementation of core concepts from **automata theory**.  
It provides functionality to parse **regular expressions**, convert them into **ε-NFA (ENFA)**, transform them into **DFA**, and manage states and transitions.  
The project also supports configuration via `.ini` files and includes an HTML converter for output visualization.

---

## Features
- Convert **regular expressions** into ENFA  
- Transform **ENFA → DFA**  
- Manage states, groups, and transition tables  
- Configurable with `.ini` files  
- Export results to HTML  

---

## Getting Started

### 1. Prerequisites
- C++17 or later  
- [CMake](https://cmake.org/) (>= 3.10)  

### 2. Build
```bash
git clone https://github.com/skipmare/TATOG7.git
cd TATOG7-main
mkdir build && cd build
cmake ..
make
