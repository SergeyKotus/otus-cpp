cmake_minimum_required(VERSION 3.5)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(custom_allocator VERSION ${PROJECT_VESRION})

add_executable(custom_allocator main.cpp MyList.h)
set_target_properties(custom_allocator PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

if (MSVC)
    target_compile_options(custom_allocator PRIVATE
        /W4
    )
else ()
    target_compile_options(custom_allocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS custom_allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT KondrS@bk.ru)
include(CPack)

