SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/forms)

ADD_LIBRARY(bbtCalculatorGui STATIC)

TARGET_SOURCES(bbtCalculatorGui
  PRIVATE
    mainwindow.cpp

    ${CMAKE_SOURCE_DIR}/src/include/gui/mainwindow.hpp
)

TARGET_INCLUDE_DIRECTORIES(bbtCalculatorGui
  PRIVATE
    ${CMAKE_SOURCE_DIR}/src/include/gui/
  PUBLIC
    ${CMAKE_SOURCE_DIR}/src/include/
)

TARGET_LINK_LIBRARIES(bbtCalculatorGui
  PUBLIC
    Qt5::Widgets
)

TARGET_COMPILE_FEATURES(bbtCalculatorGui
  PUBLIC
    cxx_std_17
)