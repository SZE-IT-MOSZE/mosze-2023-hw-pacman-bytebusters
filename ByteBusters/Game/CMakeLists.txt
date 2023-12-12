cmake_minimum_required(VERSION 3.10)
project(Game)

#set(SDL2_DIR ${CMAKE_SOURCE_DIR}/Dependencies/SDL2-2.28.4/cmake)
#set(SDL2_image_DIR ${CMAKE_SOURCE_DIR}/Dependencies/SDL2_image-2.6.3/cmake)

#find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)

include_directories("${CMAKE_SOURCE_DIR}/Game/Header Files")
include_directories("${CMAKE_SOURCE_DIR}/MazeGenerator/Header Files")
include_directories("${CMAKE_SOURCE_DIR}/Dependencies/SDL2-2.28.4/include")
include_directories("${CMAKE_SOURCE_DIR}/Dependencies/SDL2_image-2.6.3/include")


file(GLOB_RECURSE SOURCES 
	"${CMAKE_SOURCE_DIR}/Game/Source Files/*.cpp"
	"${CMAKE_SOURCE_DIR}/MazeGenerator/Source Files/*.cpp"
	)

add_executable(DeerGame ${SOURCES})

target_link_libraries(DeerGame PRIVATE "${CMAKE_SOURCE_DIR}/Dependencies/SDL2-2.28.4/lib/x64/SDL2.lib")
target_link_libraries(DeerGame PRIVATE "${CMAKE_SOURCE_DIR}/Dependencies/SDL2-2.28.4/lib/x64/SDL2main.lib")
target_link_libraries(DeerGame PRIVATE "${CMAKE_SOURCE_DIR}/Dependencies/SDL2_image-2.6.3/lib/x64/SDL2_image.lib")

#target_link_libraries(DeerGame PRIVATE SDL2 SDL2_image)

target_include_directories(DeerGame PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

target_compile_features(DeerGame PRIVATE cxx_std_20)

add_custom_command(TARGET DeerGame POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                       "${CMAKE_SOURCE_DIR}/Dependencies/SDL2-2.28.4/lib/x64/SDL2.dll"
                       $<TARGET_FILE_DIR:DeerGame>)

add_custom_command(TARGET DeerGame POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                       "${CMAKE_SOURCE_DIR}/Dependencies/SDL2_image-2.6.3/lib/x64/SDL2_image.dll"
                       $<TARGET_FILE_DIR:DeerGame>)

add_custom_command(TARGET DeerGame POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       "${CMAKE_SOURCE_DIR}/Assets"
                       $<TARGET_FILE_DIR:DeerGame>/Assets)
