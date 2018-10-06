
FIND_PACKAGE(Qt5 COMPONENTS Core Widgets PrintSupport REQUIRED)

SET(CMAKE_AUTOMOC  ON)

ADD_LIBRARY(qcustomplot STATIC
  qcustomplot.cpp
)

TARGET_LINK_LIBRARIES(qcustomplot
  PUBLIC
    Qt5::Core
    Qt5::PrintSupport
    Qt5::Widgets
)

ADD_EXECUTABLE(IconGenerator
  main.cpp)

TARGET_LINK_LIBRARIES(IconGenerator
  PRIVATE
    qcustomplot
)