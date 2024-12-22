cmake_minimum_required(VERSION 3.22)

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME})
file(GLOB SOURCEFILES *.cpp)

foreach(FILE ${SOURCEFILES})
    get_filename_component(FILE_NAME ${FILE} NAME_WE)
    set(TARGET_NAME "${FILE_NAME}")
    message(${TARGET_NAME})
    add_executable(${TARGET_NAME} ${COMMON_SRC} ${FILE})
    configure_file(${CMAKE_SOURCE_DIR}/unix/${TARGET_NAME}.cpp ${CMAKE_BINARY_DIR}/${TARGET_NAME}.cpp COPYONLY)
endforeach()
