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
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

set(CPACK_PACKAGE_INSTALL_DIRECTORY "${CPACK_PACKAGE_NAME}") # Installation directory on the target system
#set(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/logo.ico") # Need to be specified manually for each cpack generator (NSIS issues :/)
set(CPACK_PACKAGE_CHECKSUM "SHA256") # Create a checksum for the package
set(CPACK_MONOLITHIC_INSTALL OFF) # Install all components in one package, can be useful to force the installation of all components
# set(CPACK_PACKAGE_EXECUTABLES "${PROJECT_NAME}" "${PROJECT_NAME}") # No executable for saturnity

# Source package generator
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${PROJECT_VERSION}-src")
set(CPACK_SOURCE_GENERATOR "7Z;DEB;IFW;NSIS;NSIS64;NUGET;STGZ:TGZ;TXZ;WIX;ZIP")
set(CPACK_SOURCE_IGNORE_FILES ".git;build;out;dist;cmake-*")
#TODO: fix missing include directories in the source package


#
#      NSIS
#

set(CPACK_NSIS_MUI_ICON "${CMAKE_CURRENT_SOURCE_DIR}/assets\\\\logo.ico") # Installer logo
set(CPACK_NSIS_MUI_UNIICON "${CMAKE_CURRENT_SOURCE_DIR}/assets\\\\logo.ico") # Uninstaller logo
set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON) # Uninstall the previous version before installing the new one
set(CPACK_NSIS_MODIFY_PATH ON) # Add the installation directory to the PATH environment variable
set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_NAME}") # Display name in the Add/Remove Programs control panel
set(CPACK_NSIS_PACKAGE_NAME "${CPACK_PACKAGE_NAME}") # Name of the installer
set(CPACK_NSIS_INSTALLED_ICON_NAME "${CMAKE_CURRENT_SOURCE_DIR}/assets\\\\logo.ico") # A path to the executable that contains the installer icon # TODO: check more this
set(CPACK_NSIS_HELP_LINK "${PROJECT_HOMEPAGE_URL}") # Link to the project's homepage
set(CPACK_NSIS_URL_INFO_ABOUT "${PROJECT_HOMEPAGE_URL}") # Link to the project's homepage
set(CPACK_NSIS_CONTACT "${CPACK_PACKAGE_CONTACT}") # Contact information
set(CPACK_NSIS_EXECUTABLES_DIRECTORY "${CPACK_PACKAGE_INSTALL_DIRECTORY}") # Modify where the executables should be, for the Start Menu, by default=bin
#set(CPACK_NSIS_MUI_FINISHPAGE_RUN "${CPACK_PACKAGE_INSTALL_DIRECTORY}\\\\${PROJECT_NAME}.exe") # Launch the application after the installation
set(CPACK_NSIS_MENU_LINKS
        "https://alwyn974.github.io/${PROJECT_NAME}" "${PROJECT_NAME} Documentation" # Add a link to the documentation in the Start Menu
)
set(CPACK_NSIS_UNINSTALL_NAME "${CPACK_PACKAGE_NAME}-Uninstaller") # Name of the uninstaller
set(CPACK_NSIS_WELCOME_TITLE "Welcome to ${CPACK_PACKAGE_NAME} ${PROJECT_VERSION}") # Title of the welcome page
set(CPACK_NSIS_FINISH_TITLE "Thank you for installing ${CPACK_PACKAGE_NAME} ${PROJECT_VERSION}") # Title of the finish page
# TODO: fix headers and wizard images
set(CPACK_NSIS_MUI_HEADERIMAGE "${CMAKE_CURRENT_SOURCE_DIR}/assets\\\\nsis-header.bmp") # Header image
set(CPACK_NSIS_MUI_HEADERIMAGE_NOSTRETCH ON) # Don't stretch the header image
set(CPACK_NSIS_MUI_WELCOMEFINISHPAGE_BITMAP "${CMAKE_CURRENT_SOURCE_DIR}/assets\\\\nsis-wizard.bmp") # Left image
set(CPACK_NSIS_MUI_WELCOMEFINISHPAGE_BITMAP_NOSTRETCH ON) # Don't stretch the left image
set(CPACK_NSIS_BRANDING_TEXT "${CPACK_PACKAGE_NAME} ${PROJECT_VERSION}") # Text at the bottom of the install window

include(CPack)
