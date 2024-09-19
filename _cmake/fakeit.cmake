FetchContent_Declare(
        FakeIt
        GIT_REPOSITORY https://github.com/eranpeer/FakeIt.git
)
FetchContent_MakeAvailable(FakeIt)
target_include_directories(${PROJECT_NAME} PRIVATE "${fakeit_SOURCE_DIR}/single_header/catch")
# Fix reference to header that was renamed in Catch2 v3.x
add_custom_target(
        fix_fakeit_catch_header
        COMMAND sed -i 's,catch2/catch\.hpp,catch2/catch_all.hpp,' "${fakeit_SOURCE_DIR}/single_header/catch/fakeit.hpp"
)
add_dependencies(${PROJECT_NAME} fix_fakeit_catch_header)