
ADD_LIBRARY(bbtCalculatorCore STATIC)

TARGET_SOURCES(bbtCalculatorCore
  PRIVATE
    core.cpp
)

TARGET_INCLUDE_DIRECTORIES(bbtCalculatorCore
  PRIVATE
    ${CMAKE_SOURCE_DIR}/src/include/core
  PUBLIC
    ${CMAKE_SOURCE_DIR}/src/include/
)

TARGET_LINK_LIBRARIES(bbtCalculatorCore
  PRIVATE
    bbtCalculatorGui
)