# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (SimpleFramework)

find_package(OpenGL REQUIRED)


if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()




#SET (ALL_AT_FRAMEWORK_SRC "" CACHE INTERNAL " ")
# Compile external dependencies 
add_subdirectory (External)
add_subdirectory (Common)

# On Visual 2005 and above, this module can set the debug working directory
cmake_policy(SET CMP0026 OLD)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-fe2273")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

#if(INCLUDE_DISTRIB)
#	add_subdirectory(distrib)
#endif(INCLUDE_DISTRIB)



include_directories(
	External/AntTweakBar-1.16/include/
	External/glfw-3.1.2/include/GLFW/
	External/glm-0.9.7.1/
	External/glew-1.13.0/include/
	External/assimp-3.0.1270/include/
	#external/bullet-2.81-rev2613/src/	
	External/
	${ALL_AT_INCLUDE_DIRS}
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_1130
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)
MESSAGE( " ALL FILES : " ${CORE_SRCS})

SOURCE_GROUP(CORE FILES ${CORE_SRCS})
SOURCE_GROUP(GEOMETRY FILES ${GEOMETRY_SRCS} )
SOURCE_GROUP(LOADERS FILES ${LOADERS_SRCS} )
SOURCE_GROUP(RENDERERS FILES ${RENDERERS_SRCS} )
SOURCE_GROUP(UTILITIES FILES ${UTILITIES_SRCS} )
SOURCE_GROUP(UI FILES ${UI_SRCS} )
SOURCE_GROUP(WINDOWMGT FILES ${WINDOWMGT_SRCS} )

add_executable(SliceBasedVolumeRendering
	SliceBasedVolumeRendering/Source/Source.cpp
	${ALL_AT_FRAMEWORK_SRC}
)
target_link_libraries(SliceBasedVolumeRendering
	${ALL_LIBS}
	assimp
	ANTTWEAKBAR_116_OGLCORE_GLFW
)

add_custom_command(TARGET SliceBasedVolumeRendering POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${PROJECT_SOURCE_DIR}/Common/StandardShapes ${PROJECT_BINARY_DIR}/Common/StandardShapes
					   COMMENT "Copying standard shapes"
					   )


