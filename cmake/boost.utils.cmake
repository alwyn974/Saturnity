cmake_minimum_required(VERSION 3.17)

function(create_boost_dependency name)
    message(STATUS "Creating boost dependency for ${name}")
    get_target_property(linked_targets ${name} INTERFACE_LINK_LIBRARIES) # Get the linked libraries of the target

    if (NOT linked_targets)
        message(STATUS "No linked targets for ${name}")
        return()
    endif ()

    if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/cmake/boost")
        message(STATUS "Creating directory ${CMAKE_CURRENT_SOURCE_DIR}/cmake/boost")
        file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/cmake/boost")
    endif ()

    list(FIND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/boost" index)
    if (index EQUAL -1)
        message(STATUS "Adding Boost CMake module path")
        list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/boost")
    endif ()

    # Creating a list of all the boost library required by the component
    foreach (required_lib ${linked_targets})
        string(REGEX REPLACE "Boost::" "boost_" required_lib ${required_lib})
        list(FIND ${name}_boost_libraries_required "${required_lib}" index)
        if (index EQUAL -1)
            list(APPEND ${name}_boost_libraries_required "${required_lib}")
        endif ()
    endforeach ()

    message(STATUS "Boost::${name} require: ${${name}_boost_libraries_required}")

    foreach (library ${${name}_boost_libraries_required})
        if (TARGET ${library})
            message(STATUS "Target ${library} already exists")
            continue()
        endif ()

        set(boost_sublibrary "${CMAKE_CURRENT_SOURCE_DIR}/cmake/boost/Find${library}.cmake")
        if (NOT EXISTS ${boost_sublibrary})
            message(STATUS "Creating ${boost_sublibrary}")
            configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/boost.template.in" ${boost_sublibrary} @ONLY)
        endif ()
        message(STATUS "Adding library ${library}")
        find_package(${library} REQUIRED)
    endforeach ()
endfunction()

