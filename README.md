# DSA Project: Maze Solver using Dijkstra's Algorithm

This repository contains a command-line interface (CLI) based maze solver implemented in C++. The solver uses Dijkstra's algorithm to find the shortest path from a start point to a goal point in a grid-based maze. This project is part of a data structures and algorithms (DSA) course and showcases the practical application of graph algorithms.

## Features

- Generates a grid-based maze with walls, a start point, and a goal point.
- Uses Dijkstra's algorithm to find the shortest path from the start to the goal.
- Visualizes the maze and the path found by the algorithm in the console.

## Technologies Used

- C++
- Standard Template Library (STL)

## How It Works

1. **Grid Representation:** The maze is represented as a 2D grid where `0` represents open paths, `1` represents walls, `2` represents the start point, and `3` represents the goal point.
2. **Dijkstra's Algorithm:** The algorithm is used to explore the shortest path from the start to the goal by calculating the minimum distance to each point.
3. **Path Visualization:** After finding the shortest path, the maze and the path are printed to the console, where the path is marked with `*`.

## Getting Started

### Prerequisites

- C++ compiler (e.g., GCC)
- Standard C++ library

### Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/yourusername/DSA-Project.git
   cd DSA-Project
