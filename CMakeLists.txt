# Setup
cmake_minimum_required(VERSION 3.28)
project("TaiyouUI")


# Define optional features
# TODO: Add optional test project feature
option(TAIYOUI_TEST_PROJECT "Additional binary target for testing TaiyouUI" OFF)


# Find required packages
find_package(fmt CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)


# Define library project
add_library(TaiyouUI STATIC
  "TaiyouUI/UIRoot.h" "TaiyouUI/UIRoot.cpp" "TaiyouUI/Control.h" "TaiyouUI/Control.cpp" "TaiyouUI/Container.h" "TaiyouUI/Container.cpp"
  "TaiyouUI/Layer.h" "TaiyouUI/Layer.cpp" "TaiyouUI/Controls/Button.h" "TaiyouUI/Controls/Button.cpp" "TaiyouUI/UIRootContext.h"
  "TaiyouUI/Turk/Turk.h" "TaiyouUI/Turk/Turk.cpp" "TaiyouUI/Turk/FontDescriptor.h" "TaiyouUI/Turk/FontDescriptor.cpp"  "TaiyouUI/Turk/FontDescriptorHasher.h"
  "TaiyouUI/Animation/Interpolator.cpp" "TaiyouUI/Animation/Interpolator.h" "TaiyouUI/Animation/InterpolatorEasingFunction.h"
  "TaiyouUI/Animation/ColorInterpolator.cpp" "TaiyouUI/Animation/ColorInterpolator.h"
 )

# Set C++ standard to 20
set_property(TARGET TaiyouUI PROPERTY CXX_STANDARD 20)
# Treat warnings as errors
set_property(TARGET TaiyouUI PROPERTY COMPILE_WARNING_AS_ERROR ON)


# Set target dependencies
target_link_libraries(TaiyouUI PRIVATE fmt::fmt)
target_link_libraries(TaiyouUI PUBLIC SDL3::SDL3)
# idk how the $<IF: part works, vcpkg told me this would work so I trust it :)
target_link_libraries(TaiyouUI PRIVATE $<IF:$<TARGET_EXISTS:SDL3_ttf::SDL3_ttf>,SDL3_ttf::SDL3_ttf,SDL3_ttf::SDL3_ttf-static>)
target_include_directories(TaiyouUI PUBLIC ./)