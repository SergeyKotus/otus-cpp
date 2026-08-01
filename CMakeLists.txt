cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VESRION})

option(WITH_BOOST_TEST "Whether to build Boost test" ON)

add_executable(ip_filter main.cpp)

set_target_properties(ip_filter PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

#message("cmake: - before boost test including")

message("cmake: - WITH_BOOST_TEST = " ${WITH_BOOST_TEST})
set(Boost_DEBUG ON)
if(WITH_BOOST_TEST)    
    #message("cmake: - with boost test")
    #cmake_policy(SET CMP0074 NEW)
    #cmake_policy(SET CMP0167 NEW)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    add_executable(test_md5sum test_md5sum.cpp)

    set_target_properties(test_md5sum PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
    )

#[[
    set_target_properties(test_version PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    )
]]

    set_target_properties(test_md5sum PROPERTIES
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    )

    target_link_libraries(test_md5sum
        ${Boost_LIBRARIES}        
    )

#    add_custom_command(
#        TARGET test_md5sum
#        POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy
#            "${CMAKE_CURRENT_SOURCE_DIR}/ip_filter.tsv"
#            "$<TARGET_FILE_DIR:test_md5sum>/ip_filter.tsv"
#    COMMENT "Deploying test data file..."
#   )
endif()

if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    
    if(WITH_BOOST_TEST)
        target_compile_options(test_md5sum PRIVATE
            /W4
        )
    endif()
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    
    if(WITH_BOOST_TEST)
        target_compile_options(test_md5sum PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT KondrS@bk.ru)
include(CPack)

if(WITH_BOOST_TEST)
    enable_testing()
    add_test(NAME test_md5sum COMMAND test_md5sum)
endif()
