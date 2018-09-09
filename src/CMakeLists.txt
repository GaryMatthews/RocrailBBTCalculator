CMAKE_MINIMUM_REQUIRED(VERSION 3.12)
PROJECT(rocrailBBTCalculator
  LANGUAGES CXX
  VERSION 0.1.0
)

FIND_PACKAGE(Qt5 COMPONENTS Widgets Xml REQUIRED)

ADD_SUBDIRECTORY(core)
ADD_SUBDIRECTORY(gui)

ADD_EXECUTABLE(rocrailBBTCalculator)

TARGET_SOURCES(rocrailBBTCalculator
  PRIVATE
    main.cpp
)

TARGET_LINK_LIBRARIES(rocrailBBTCalculator
  PRIVATE
    Qt5::Widgets

    bbtCalculatorCore
)

INSTALL(TARGETS rocrailBBTCalculator
  RUNTIME DESTINATION bin
)

IF (WIN32)
  INCLUDE(${CMAKE_SOURCE_DIR}/cmake/windeployqt.cmake)

  WINDEPLOYQT(rocrailBBTCalculator)

  INSTALL(
    FILES
      $<TARGET_FILE_DIR:rocrailBBTCalculator>/Qt5Core.dll
      $<TARGET_FILE_DIR:rocrailBBTCalculator>/Qt5Gui.dll
      $<TARGET_FILE_DIR:rocrailBBTCalculator>/Qt5Svg.dll
      $<TARGET_FILE_DIR:rocrailBBTCalculator>/Qt5Widgets.dll
      $<TARGET_FILE_DIR:rocrailBBTCalculator>/Qt5Xml.dll
    DESTINATION bin
  )
  INSTALL(
    FILES
      $<TARGET_FILE_DIR:rocrailBBTCalculator>/iconengines/qsvgicon.dll
    DESTINATION bin/iconengines
  )
  INSTALL(
    FILES
      $<TARGET_FILE_DIR:rocrailBBTCalculator>/imageformats/qgif.dll
      $<TARGET_FILE_DIR:rocrailBBTCalculator>/imageformats/qicns.dll
      $<TARGET_FILE_DIR:rocrailBBTCalculator>/imageformats/qico.dll
      $<TARGET_FILE_DIR:rocrailBBTCalculator>/imageformats/qjpeg.dll
      $<TARGET_FILE_DIR:rocrailBBTCalculator>/imageformats/qsvg.dll
      $<TARGET_FILE_DIR:rocrailBBTCalculator>/imageformats/qtga.dll
      $<TARGET_FILE_DIR:rocrailBBTCalculator>/imageformats/qtiff.dll
      $<TARGET_FILE_DIR:rocrailBBTCalculator>/imageformats/qwbmp.dll
      $<TARGET_FILE_DIR:rocrailBBTCalculator>/imageformats/qwebp.dll
    DESTINATION bin/imageformats
  )
  INSTALL(
    FILES
      $<TARGET_FILE_DIR:rocrailBBTCalculator>/platforms/qwindows.dll
    DESTINATION bin/platforms
  )
  INSTALL(
    FILES
      $<TARGET_FILE_DIR:rocrailBBTCalculator>/styles/qwindowsvistastyle.dll
    DESTINATION bin/styles
  )
  INSTALL(
    FILES
      $<TARGET_FILE_DIR:rocrailBBTCalculator>/translations/qt_de.qm
      $<TARGET_FILE_DIR:rocrailBBTCalculator>/translations/qt_en.qm
    DESTINATION bin/translations
  )
ENDIF (WIN32)

SET(CPACK_PACKAGE_NAME "rocrailBBTCalculator")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "rocrailBBTCalculator")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Calculates BBT values for RocRail Locomotives")
SET(CPACK_PACKAGE_VENDOR "Markus Reitboeck")
SET(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/LICENSE)

SET(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
SET(CPACK_NSIS_DISPLAY_NAME "Rocrail BBT Calculator")
SET(CPACK_NSIS_PACKAGE_NAME "Rocrail BBT Calculator")
SET(CPACK_NSIS_MODIFY_PATH ON)

SET(CPACK_GENERATOR NSIS)

INCLUDE(CPack)
