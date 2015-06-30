# Script that sets up the installation of targets..
# To add targets/headers, call macro
# bdsim_install_targets(TARGET_LIST)
# bdsim_install_headers(TARGET_LIST)
# Create installation targets. Note that we put each kind of file
# into a different component via COMPONENT. These components will 
# be used to create the installation components.
macro(bdsim_install_targets)
    install(TARGETS ${ARGN}
      BUNDLE
      DESTINATION .
      COMPONENT Runtime
      ARCHIVE
      DESTINATION lib
      LIBRARY
      DESTINATION lib
      COMPONENT Libraries
      RUNTIME
      DESTINATION bin
      COMPONENT Runtime
      )
endmacro()
macro(bdsim_install_headers)
    install(FILES ${ARGN}
      DESTINATION include/bdsim
      COMPONENT Headers)
endmacro()
macro(bdsim_install_doc)
    install(FILES ${ARGN}
        DESTINATION share/${PROJECT_NAME}/doc/${DOC_POSTFIX}
        COMPONENT Documentation)
endmacro()
macro(bdsim_install_scripts)
    install(FILES ${ARGN}
        DESTINATION ${SCRIPT_DEST}
        COMPONENT Scripts)
endmacro()
macro(bdsim_install_vis)
    install(FILES ${ARGN}
        DESTINATION share/${PROJECT_NAME}/vis/
        COMPONENT Visualisation)
endmacro()

# This macro fixes the MACOSX_BUNDLES
# since we do not make a "traditional app"
macro(bdsim_install_bundle)
  if(APPLE)
    foreach(bundle_name ${ARGN})
    set(APPS "\${CMAKE_INSTALL_PREFIX}/${bundle_name}")
    set(DIRS "")
    install(CODE "
      set(BU_CHMOD_BUNDLE_ITEMS 1)
      include(BundleUtilities)
      fixup_bundle(\"${APPS}.app\"   \"\"   \"${DIRS}\")
      execute_process(COMMAND mv \"${APPS}.app/Contents\" \"${APPS}\"  )
      execute_process(COMMAND rm -rf \"${APPS}.app\" )
      " COMPONENT Runtime)
    endforeach()
  endif()
endmacro()

# add rpath to the binaries/libraries when installing
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# CPack boilerplate for this project
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VENDOR "RHUL")
set(CPACK_PACKAGE_CONTACT "Jochem Snuverink")
set(CPACK_BUNDLE_NAME "${CPACK_PACKAGE_NAME}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "BDSIM - Beam Physics Simulation Tool")
set(CPACK_PACKAGE_VERSION ${BDSIM_VERSION})
set(CPACK_PACKAGE_VERSION_MAJOR ${BDSIM_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${BDSIM_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${BDSIM_VERSION_PATCH})
