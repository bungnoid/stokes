include_directories(${CXXTEST_INCLUDE_DIR})

CXXTEST_ADD_TEST(UnitTestDataType UnitTestDataType.cpp "${CMAKE_CURRENT_SOURCE_DIR}/UnitTestDataType.hpp")
target_link_libraries(UnitTestDataType StokesCore)

CXXTEST_ADD_TEST(UnitTestDenseMappedField UnitTestDenseMappedField.cpp "${CMAKE_CURRENT_SOURCE_DIR}/UnitTestDenseMappedField.hpp")
target_link_libraries(UnitTestDenseMappedField StokesCore)

CXXTEST_ADD_TEST(UnitTestMatrix UnitTestMatrix.cpp "${CMAKE_CURRENT_SOURCE_DIR}/UnitTestMatrix.hpp")
target_link_libraries(UnitTestMatrix StokesCore)

CXXTEST_ADD_TEST(UnitTestSimpleField UnitTestSimpleField.cpp "${CMAKE_CURRENT_SOURCE_DIR}/UnitTestSimpleField.hpp")
target_link_libraries(UnitTestSimpleField StokesCore)

CXXTEST_ADD_TEST(UnitTestSparseMappedField UnitTestSparseMappedField.cpp "${CMAKE_CURRENT_SOURCE_DIR}/UnitTestSparseMappedField.hpp")
target_link_libraries(UnitTestSparseMappedField StokesCore)
