# Tetris Game in C with WebAssembly

This project is an implementation of the classic Tetris game written in C, compiled to WebAssembly (Wasm) to run in a web browser. 
The goal of this project is to provide a Tetris game engine that can be easily integrated into a React application using the generated JavaScript module.

## Tetris Game Features

- Classic Tetris gameplay with falling blocks.
- Keyboard controls for movement and rotation.
- Game over detection.

## Building the WebAssembly Module

To build the WebAssembly module from the C source code, follow these steps:

1. Clone this repository:

   ```bash
   git clone https://github.com/yourusername/tetris-c-wasm.git
   ```

2. Navigate to the project directory:

   ```bash
   cd tetris-game/src
   ```

3. Compile the C code to WebAssembly using Emscripten (ensure you have Emscripten installed):

   ```bash
   emcc tetris.c -o tetris.js
   ```

   This command will generate `tetris.js` and `tetris.wasm` files.

## Future Improvements:
  Integrating into a React Application
In the future, the project will be upgraded by enhancing the Tetris game's features, adding high scores, or implementing multiplayer functionality. 
