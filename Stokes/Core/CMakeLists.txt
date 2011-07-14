file(GLOB STOKES_CORE_HEADER_FILES "*.hpp")
file(GLOB STOKES_CORE_SOURCE_FILES "*.cpp")

add_definitions(-DSTOKES_BUILDING)

add_library(StokesCore SHARED ${STOKES_CORE_HEADER_FILES} ${STOKES_CORE_SOURCE_FILES})

if(MSVC)
	set_target_properties(StokesCore PROPERTIES IMPORT_PREFIX "lib" PREFIX "lib")
endif()
