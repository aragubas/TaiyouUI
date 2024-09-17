# TaiyouUI
Simplistic and quick SDL2 C++ GUI Framework for real time projects, with low overhead

This project is currently a W.I.P

# Build Instructions
This project has been setup to be used as a git submodule, and to be statically linked to another SDL2 application. The test project doesn't exist yet, so there are no build instructions

# How to use TaiyouUI in your project
**This section is a WIP.**

There are probably other ways of doing this, but this is the way I have set up in another project and it works

### For projects with a root level CMake file and children projects
First, Add the project to your root level CMake file with ``add_subdirectory``
```CMake
add_subdirectory ("TaiyouUI")
```

Then, in the child project which will use TaiyouUI, you can link and include TaiyouUI as follows
```CMake
target_link_libraries(<Project Name> PUBLIC TaiyouUI)
target_include_directories(<Project Name> PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/TaiyouUI)
```