find_path(MAYA_INSTALLATION_DIR REQUIRED)
set(MAYA_INCLUDE_DIR "${MAYA_INSTALLATION_DIR}/include")
set(MAYA_LIBRARY_DIR "${MAYA_INSTALLATION_DIR}/lib")

include_directories(${MAYA_INCLUDE_DIR})
link_directories(${MAYA_LIBRARY_DIR})

add_definitions(-DREQUIRE_IOSTREAM)
if(MSVC)
	add_definitions(-DNT_PLUGIN)
endif()

add_executable(MtoS MtoS.cpp)
target_link_libraries(MtoS StokesCore StokesMaya)