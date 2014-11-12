cmake_minimum_required( VERSION 2.6 )

project( kioskd )
set( kioskd_VERSION_MAJOR 0 )
set( kioskd_VERSION_MINOR 2 )
set(CMAKE_INSTALL_PREFIX /opt/kioskd)
set(CMAKE_INSTALL_RPATH "/opt/kioskd/lib;/opt/vc/lib")

include_directories( ${CMAKE_SOURCE_DIR}/include )
include_directories( /usr/include/libev )
include_directories( /opt/vc/include /opt/vc/include/interface/vcos/pthreads ) # wtf rpi?
link_directories( /opt/vc/lib /usr/local/lib )

#set( CMAKE_C_FLAGS "-std=c99" )
#set( CMAKE_C_FLAGS_DEBUG "-g -Wall" )

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
# ev doesn't use pkg-config

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})


add_library(kiosk SHARED src/kioskd.c src/cJSON.c src/jsonrpc-c.c src/graphics.c src/propmanager.c)
TARGET_LINK_LIBRARIES(kiosk ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ev m)

add_executable(kioskd src/main.c)
target_link_libraries(kioskd kiosk)



## Props
add_library(prop_text SHARED props/text.c)
add_library(prop_generic SHARED props/generic.c)
add_library(prop_image SHARED props/image.c)
target_link_libraries(prop_text kiosk)
target_link_libraries(prop_generic kiosk)
target_link_libraries(prop_image kiosk ${SDL2IMAGE_LIBRARIES})


## Installation instructions
install(TARGETS kioskd kiosk prop_generic prop_text prop_image
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib 
    ARCHIVE DESTINATION lib
)
