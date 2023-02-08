##
## NSIS
##

set(CPACK_NSIS_MUI_ICON "${CMAKE_CURRENT_SOURCE_DIR}/assets\\\\logo.ico") # Installer logo
set(CPACK_NSIS_MUI_UNIICON "${CMAKE_CURRENT_SOURCE_DIR}/assets\\\\logo.ico") # Uninstaller logo
set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON) # Uninstall the previous version before installing the new one
set(CPACK_NSIS_MODIFY_PATH ON) # Add the installation directory to the PATH environment variable
set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_NAME}") # Display name in the Add/Remove Programs control panel
set(CPACK_NSIS_PACKAGE_NAME "${CPACK_PACKAGE_NAME}") # Name of the installer
set(CPACK_NSIS_HELP_LINK "${PROJECT_HOMEPAGE_URL}") # Link to the project's homepage
set(CPACK_NSIS_URL_INFO_ABOUT "${PROJECT_HOMEPAGE_URL}") # Link to the project's homepage
set(CPACK_NSIS_CONTACT "${CPACK_PACKAGE_CONTACT}") # Contact information
set(CPACK_NSIS_EXECUTABLES_DIRECTORY "bin") # Modify where the executables should be, for the Start Menu, by default=bin
if (${${PROJECT_NAME}_IS_EXECUTABLE})
    set(CPACK_NSIS_MUI_FINISHPAGE_RUN "${PROJECT_NAME}.exe") # Launch the application after the installation
    set(CPACK_NSIS_MUI_FINISHPAGE_RUN_NOTCHECKED ON) # Launch checkbox
    set(CPACK_NSIS_MUI_FINISHPAGE_RUN_PARAMETERS "") # Launch parameters
endif ()
set(CPACK_NSIS_MENU_LINKS
        "https://alwyn974.github.io/${PROJECT_NAME}" "${PROJECT_NAME} Documentation" # Add a link to the documentation in the Start Menu
)
set(CPACK_NSIS_UNINSTALL_NAME "${CPACK_PACKAGE_NAME}-Uninstaller") # Name of the uninstaller
set(CPACK_NSIS_WELCOME_TITLE "Welcome to ${CPACK_PACKAGE_NAME} ${PROJECT_VERSION}") # Title of the welcome page
set(CPACK_NSIS_FINISH_TITLE "Thank you for installing ${CPACK_PACKAGE_NAME} ${PROJECT_VERSION}") # Title of the finish page

set(CPACK_NSIS_MUI_HEADERIMAGE "${CMAKE_CURRENT_SOURCE_DIR}/assets\\\\nsis-header.bmp") # Header image
set(CPACK_NSIS_MUI_HEADERIMAGE_NOSTRETCH ON) # Don't stretch the header image
set(CPACK_NSIS_MUI_WELCOMEFINISHPAGE_BITMAP "${CMAKE_CURRENT_SOURCE_DIR}/assets\\\\nsis-wizard.bmp") # Left image
set(CPACK_NSIS_MUI_WELCOMEFINISHPAGE_BITMAP_NOSTRETCH ON) # Don't stretch the left image
set(CPACK_NSIS_BRANDING_TEXT "${CPACK_PACKAGE_NAME} ${PROJECT_VERSION}") # Text at the bottom of the install window
set(CPACK_NSIS_IGNORE_LICENSE_PAGE OFF) # Disable the license page
