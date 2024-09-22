# Setup
cmake_minimum_required(VERSION 3.28)
project("TaiyouUI")

# Define optional features
option(TAIYOUI_TEST_PROJECT "Additional binary target for testing TaiyouUI" OFF)


# Find required packages
find_package(fmt CONFIG REQUIRED)
find_package(SDL2 COMPONENTS SDL2-static CONFIG REQUIRED)


# Define library project
add_library(TaiyouUI STATIC
  "TaiyouUI/UIRoot.h" "TaiyouUI/UIRoot.cpp" "TaiyouUI/Control.h" "TaiyouUI/Container.h" "TaiyouUI/Container.cpp"
  "TaiyouUI/Layer.h" "TaiyouUI/Layer.cpp" "TaiyouUI/Controls/Button.h" "TaiyouUI/Controls/Button.cpp"
)

# Set C++ standard to 20
set_property(TARGET TaiyouUI PROPERTY CXX_STANDARD 20)

# Set library dependencies
target_link_libraries(TaiyouUI PRIVATE fmt::fmt)
target_link_libraries(TaiyouUI PUBLIC SDL2::SDL2-static)
target_include_directories(TaiyouUI PUBLIC ./)