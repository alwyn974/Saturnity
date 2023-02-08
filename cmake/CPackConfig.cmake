# https://cmake.org/cmake/help/latest/module/CPack.html
include(InstallRequiredSystemLibraries) # include any runtime libraries that are needed by the project for the current platform

# Set some basic information about the project
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_CONTACT "Alwyn974")
set(CPACK_PACKAGE_VENDOR "Alwyn974")
set(CPACK_PACKAGE_DESCRIPTION "Saturnity is a library in C++ to handle network easily, using tcp & udp packets. It is cross-platform and can be used on Windows, Linux, Mac OS X. It's a library that is easy to use and that can be used in any project.")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Saturnity is a library to handle networking")
set(CPACK_PACKAGE_HOMEPAGE_URL "${PROJECT_HOMEPAGE_URL}")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${PROJECT_VERSION}-${CMAKE_SYSTEM_NAME}") # Default

# Set the version information
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

# Set some resource files
set(CPACK_RESOURCE_FILE_WELCOME "${CMAKE_CURRENT_SOURCE_DIR}/README.md") # TODO: change this later
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

set(CPACK_PACKAGE_INSTALL_DIRECTORY "${CPACK_PACKAGE_NAME}") # Installation directory on the target system
set(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/assets/logo.ico") # Location of an icon to display during the installation process
set(CPACK_PACKAGE_CHECKSUM "SHA256") # Create a checksum for the package
set(CPACK_MONOLITHIC_INSTALL OFF) # Install all components in one package, can be useful to force the installation of all components
get_target_property(TARGET_TYPE ${PROJECT_NAME} TYPE)
if (TARGET_TYPE STREQUAL "EXECUTABLE")
    set(CPACK_PACKAGE_EXECUTABLES "${PROJECT_NAME}" "${PROJECT_NAME}") # Set the executable name
    set(${PROJECT_NAME}_IS_EXECUTABLE ON)
endif ()

# Components
# TODO: create component for library (shared/static) and headers
# TODO: create component for only the dll/so
#[[include(CPackComponent)
cpack_add_component(headers
        DISPLAY_NAME "Headers"
        DESCRIPTION "C++ Header files"
        GROUP "Development"
        REQUIRED
)
cpack_add_component(archive
        DISPLAY_NAME "Archive"
        DESCRIPTION "Static library"
        GROUP "Development"
        REQUIRED
)
cpack_add_component(library
        DISPLAY_NAME "Library"
        DESCRIPTION "Shared library"
        GROUP "Runtime"
        REQUIRED
)
cpack_add_component_group(Development
        EXPANDED
        DESCRIPTION
        "All of the tools you'll ever need to develop software"
)]]

# Source package generator
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${PROJECT_VERSION}-src")
set(CPACK_SOURCE_GENERATOR "7Z;DEB;IFW;NSIS;NSIS64;NUGET;STGZ:TGZ;TXZ;ZIP")
set(CPACK_SOURCE_IGNORE_FILES ".git;build;out;dist;cmake-*")

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/cpack/CPackDEB.cmake) # DEB
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/cpack/CPackNSIS.cmake) # NSIS
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/cpack/CPackRPM.cmake) # RPM

include(CPack)
