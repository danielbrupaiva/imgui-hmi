include(FetchContent)
#---------------------
FetchContent_Declare(
        bcrypt
        SOURCE_DIR $ENV{VENDOR_FOLDER}/bcrypt
#        GIT_REPOSITORY https://github.com/danielbrupaiva/bcrypt.git
        GIT_TAG        master  # Or use a specific commit hash or tag
)
FetchContent_MakeAvailable(bcrypt)
#FetchContent_GetProperties(bcrypt)
#---------------------
target_link_libraries(${PROJECT_NAME} PUBLIC bcrypt)