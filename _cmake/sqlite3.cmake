include(FetchContent)
#---------------------
FetchContent_Declare(
        sqlite3                                               # name of the content
        GIT_REPOSITORY https://github.com/sqlite/sqlite.git   # the repository
        GIT_TAG version-3.47.0                                # the tag
)
FetchContent_MakeAvailable(sqlite3)
#---------------------
target_link_libraries(${PROJECT_NAME} PRIVATE sqlite3)
target_include_directories(${PROJECT_NAME} PRIVATE ${sqlite3_SOURCE_DIR})