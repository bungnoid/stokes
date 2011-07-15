include_directories(${CXXTEST_INCLUDE_DIR})

CXXTEST_ADD_TEST(UnitTestLinearArray UnitTestLinearArray.cpp "${CMAKE_CURRENT_SOURCE_DIR}/UnitTestLinearArray.hpp")
target_link_libraries(UnitTestLinearArray StokesCore)

CXXTEST_ADD_TEST(UnitTestMappedArray UnitTestMappedArray.cpp "${CMAKE_CURRENT_SOURCE_DIR}/UnitTestMappedArray.hpp")
target_link_libraries(UnitTestMappedArray StokesCore ${Boost_FILESYSTEM_LIBRARY})
