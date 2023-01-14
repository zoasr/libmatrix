Project(matrixlib)
cmake_minimum_required(VERSION 3.0)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)


file(GLOB_RECURSE matrixlib_cpp "src/*.cpp")
file(GLOB_RECURSE matrixlib_h "include/*.h")

file(GLOB_RECURSE EXAMPLE_SOURCES "examples/*.cpp")


add_library(matrixlib
	${matrixlib_cpp}
	${matrixlib_h}
)

install(TARGETS matrixlib ARCHIVE DESTINATION lib )
install(FILES ${matrixlib_h} DESTINATION include )

# Compile all the Examples in the "examples" folder
foreach( example_source ${EXAMPLE_SOURCES} )
	get_filename_component( examplename ${example_source} NAME_WE)
	add_executable( ${examplename}
		${example_source}
	)
	target_link_libraries( ${examplename} matrixlib )
endforeach( example_source ${EXAMPLE_SOURCES} )



