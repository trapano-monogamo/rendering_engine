add_executable(demo src/main.cpp src/scenes.cpp)

target_link_libraries(demo PRIVATE rendering_engine)
target_include_directories(demo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../engine/include)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../engine/assets
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
