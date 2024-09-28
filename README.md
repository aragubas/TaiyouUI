# TaiyouUI
Simplistic and quick SDL2 C++ GUI Framework for real time projects, with low overhead

This project is currently a W.I.P

# Build Instructions
This project has been setup to be used as a git submodule, and to be statically linked to another SDL2 application. The test project doesn't exist yet, so there are no build instructions

### For projects with a root level CMake file and children projects
First, Add the project to your root level CMake file with ``add_subdirectory``
```CMake
add_subdirectory ("TaiyouUI")
```

Then, in the child project which will use TaiyouUI, you can link and include TaiyouUI as follows
```CMake
target_link_libraries(<Project Name> <PUBLIC|PRIVATE> TaiyouUI)
```

# License
This project is licensed under the AGPL 3.0 license

Check [License](./LICENSE) for more details

(C) 2022 - 2024 by Aragubas - part of Taiyou Software Suite
