include(FetchContent)
#---------------------------------------------------------------------------------------------
FetchContent_Declare(
        core
        SOURCE_DIR $ENV{CORE_FOLDER}
)
FetchContent_MakeAvailable(core)
FetchContent_GetProperties(core)
#---------------------------------------------------------------------------------------------
target_link_libraries(${PROJECT_NAME} PUBLIC core)