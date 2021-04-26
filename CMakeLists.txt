cmake_minimum_required(VERSION 3.9)
project(RG88-3d-boxing  
	VERSION 1.0
)   

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

set(SOURCES 
"${CMAKE_CURRENT_SOURCE_DIR}/image.c" 
"${CMAKE_CURRENT_SOURCE_DIR}/image.h" 
"${CMAKE_CURRENT_SOURCE_DIR}/main.c" 
"${CMAKE_CURRENT_SOURCE_DIR}/objekti.c" 
"${CMAKE_CURRENT_SOURCE_DIR}/objekti.h")


add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(${PROJECT_NAME} PUBLIC ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} m) 
