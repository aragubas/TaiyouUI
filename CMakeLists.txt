# Find required packages
find_package(fmt CONFIG REQUIRED)
find_package(SDL2 COMPONENTS SDL2-static CONFIG REQUIRED)

add_library(TaiyouUI STATIC 
  "TaiyouUI/UIRoot.h" "TaiyouUI/UIRoot.cpp" "TaiyouUI/Control.h" "TaiyouUI/Container.h" "TaiyouUI/Container.cpp"
  "TaiyouUI/Layer.h" "TaiyouUI/Layer.cpp" "TaiyouUI/Controls/Button.h" "TaiyouUI/Controls/Button.cpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET TaiyouUI PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(TaiyouUI PRIVATE fmt::fmt)
target_link_libraries(TaiyouUI PRIVATE SDL2::SDL2-static)