kioskd
======

A graphical kiosk daemon with a JSON API

Depends on libev, SDL2, SDL_image >= 2.0.0, SDL_ttf >= 2.0.0, MathGL

How to test:
------------

Relatively standard CMake build:

    mkdir build
    cd build
    cmake ..
    make
    ./kioskd

In a new terminal:

    perl test.pl
    
If anything goes wrong, you shutdown the server with:

    sh shutdown.sh
    
    
Commandline Options
-------------------

None


Environment Variables
---------------------

PROP_PLUGIN_PATH - a PATH variable to search for prop plugins.