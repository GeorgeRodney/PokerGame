cmake_minimum_required( VERSION 3.14 )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

project( project2 )

set (TARGET play)

set( SOURCES 
        ${CMAKE_SOURCE_DIR}/src/Person.cpp
        ${CMAKE_SOURCE_DIR}/src/Player.cpp
        ${CMAKE_SOURCE_DIR}/src/Card.cpp
        ${CMAKE_SOURCE_DIR}/src/Dealer.cpp
        ${CMAKE_SOURCE_DIR}/src/Deck.cpp
        ${CMAKE_SOURCE_DIR}/src/DeckUtils.cpp
        ${CMAKE_SOURCE_DIR}/src/Gui.cpp
        ${CMAKE_SOURCE_DIR}/src/Button.cpp
        ${CMAKE_SOURCE_DIR}/src/Banner.cpp
     )

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable( ${TARGET} main.cpp ${SOURCES} )

target_link_libraries(${TARGET} sfml-graphics sfml-window sfml-system)

target_include_directories( ${TARGET} PUBLIC Inc )