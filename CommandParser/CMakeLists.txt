file(GLOB SRC_FILES "*.c")

#add_subdirectory(ut)
#add_subdirectory(gluethread)

add_library(CommandParser  ${SRC_FILES})
find_library(LIBRT rt)
if(LIBRT)
    target_link_libraries(CommandParser ${LIBRT})
endif()