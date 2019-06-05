enable_testing()
find_package(GTest MODULE REQUIRED)
add_executable(runBasicTests BasicTest.cpp)
target_link_libraries(runBasicTests PRIVATE GTest::GTest GTest::Main)
