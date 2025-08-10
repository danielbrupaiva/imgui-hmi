include(FetchContent)
#---------------------
FetchContent_Declare(Catch2                                     # name of the content
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git   # the repository
        GIT_TAG v3.4.0                                   # the tag
)
FetchContent_MakeAvailable(Catch2)
FetchContent_GetProperties(Catch2)
#---------------------
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME})
#---------------------
target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2WithMain)