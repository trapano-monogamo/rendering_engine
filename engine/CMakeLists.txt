file(GLOB_RECURSE SRC src/**/*.cpp src/glad.c)

add_library(rendering_engine ${SRC})

target_link_directories(rendering_engine PUBLIC lib/)
target_link_libraries(rendering_engine -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl)

target_include_directories(rendering_engine PUBLIC include)
