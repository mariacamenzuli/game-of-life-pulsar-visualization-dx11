# A Pulsar Pattern in a Game of Life Simulation Rendered Using DirectX 11

An implementation of a simple 3D scene rendered using DirectX 11 visualizing a pulsar pattern in a Game of Life simulation.

## Project Design Goals

-  Create an API that will allow a scene to be defined with the ease of creating one in something like Unity. This ultimately boils down to the ability to define a 3D scene structured in a scene graph with as little effort as possible. It should only take a line or two to create a new scene object and attach it to the graph. Once a scene is defined, it should be able to be transformed with the same level of ease.
- The simulation code should be decoupled from the rendering code. A class that creates and manipulates a scene graph in order to run a simulation should not be concerned with rendering it. Additionally, the rendering frame rate should not impact the simulation, and you should even be able to start and stop rendering at any time during the run of the simulation without impacting it.
- Rendering configurations that may vary from one execution of the simulation to another, such as whether full screen mode should be used, or whether VSync should be on or off, should be modifiable without requiring project recompilation.
- All memory should be managed by smart pointers, to reduce the risk of mismanagement of memory resources. Apart from the standard smart pointers that are available in C++, [`Microsoft::WRL::ComPtr`](https://github.com/Microsoft/DirectXTK/wiki/ComPtr) was used as a smart pointer for COM objects.
- Models should be loaded from a standard file format.

## Configuration

The program that runs the simulation loads up some configurations from `config.yml`, a file that should be located in the directory of the executable, along with the `Resources` folder. The following options can be configured.

- `fullscreen_enabled`: This should be `true` or `false`, depending on whether fullscreen mode should be used or not. If fullscreen mode is not used, an 800x600 window will be used instead.
- `vsync_enabled`: This should be true or false, depending on whether VSync should be used or not.
- `screen_depth` and `screen_near`: These float values are used when creating the perspective projection matrix to render the scene.
- `shadowmap_size`: This should be an integer value that will determine the resolution of the shadow map. Note that the shadow map is a cube texture and this value specifies the length of the cube’s side.

## Controls

While viewing the scene, the following controls are available.

- **W**, **A**, **S**, and **D** keys move the camera forward, to the left, backwards, and to the right, respectively.
- Mouse movement yaws and pitches the camera in the direction of the mouse movement.
- **Q** and **E** provide an alternative way to yaw the camera left and right respectively.
- **Z** and **C** provide an alternative way to pitch the camera up and down respectively.
- **Escape** terminates the program.
- **Spacebar** will cause the current state of the shadow map to be written to file for inspection. The file will be saved in the scene’s working directory and will be named shadow-map.dds.
- **R** will cause the program to stop rendering new frames, without stopping the simulation.
- **T** will cause the program to continue rendering new frames