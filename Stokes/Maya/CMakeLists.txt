find_path(MAYA_INSTALLATION_DIR REQUIRED)
set(MAYA_INCLUDE_DIR "${MAYA_INSTALLATION_DIR}/include")
set(MAYA_LIBRARY_DIR "${MAYA_INSTALLATION_DIR}/lib")

include_directories(${MAYA_INCLUDE_DIR})
link_directories(${MAYA_LIBRARY_DIR})

add_definitions(-DSTOKES_MAYA_BUILDING)

add_definitions(-DREQUIRE_IOSTREAM)
if(MSVC)
	add_definitions(-DNT_PLUGIN)
endif()

add_library(StokesMaya SHARED API.hpp API.cpp ObjectEmitter.hpp ObjectEmitter.cpp NurbsCurveEmitter.hpp NurbsCurveEmitter.cpp NurbsSurfaceEmitter.hpp NurbsSurfaceEmitter.cpp)
target_link_libraries(StokesMaya StokesCore Foundation OpenMaya OpenMayaFX)

if(MSVC)
	set_target_properties(StokesMaya PROPERTIES IMPORT_PREFIX "lib" PREFIX "lib")
endif()
