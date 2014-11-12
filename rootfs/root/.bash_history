/debootstrap/debootstrap --second-stage
ls
exit
env
exit
ls
cd /root
ls
cd kioskd-libs/
ls
cd SDL2-2.0.3/
ls
less README-SDL.txt 
less README-linux.txt 
apt-get install make cmake autoconf automake libtool libasound2-dev libpulse-dev libaudio-dev libx11-dev libxext-dev libxrandr-dev libxcursor-dev libxi-dev libxinerama-dev libxxf86vm-dev libxss-dev libgl1-mesa-dev libesd0-dev libdbus-1-dev libudev-dev
exit
apt-get install make cmake autoconf automake libtool libasound2-dev libpulse-dev libaudio-dev libx11-dev libxext-dev libxrandr-dev libxcursor-dev libxi-dev libxinerama-dev libxxf86vm-dev libxss-dev libgl1-mesa-dev libesd0-dev libdbus-1-dev libudev-dev
nano /root/.bashrc
exit
nano /root/.bashrc 
exit
apt-get install make cmake autoconf automake libtool libasound2-dev libpulse-dev libaudio-dev libx11-dev libxext-dev libxrandr-dev libxcursor-dev libxi-dev libxinerama-dev libxxf86vm-dev libxss-dev libgl1-mesa-dev libesd0-dev libdbus-1-dev libudev-dev
exit
cd ~
ls
cd kioskd-libs/
ls
wget http://prdownloads.sourceforge.net/libpng/libpng-1.6.13.tar.gz?download
mv libpng-1.6.13.tar.gz\?download libpng-1.6.13.tar.gz
tar -xf libpng-1.6.13.tar.gz 
mv libpng-1.6.13.tar.gz tars/
cd libpng-1.6.13/
ls
mkdir build
les README 
less
less README 
less INSTALL 
echo $CPPFLAGS
echo $CFLAGS
exit
echo $CFLAGS
ls
cd /root/kioskd-libs
ls
cd libpng-1.6.13/
less README
less INSTALL 
exit
cd /root/
cd kioskd-libs/libpng-1.6.13/
cd ..
wget http://zlib.net/zlib-1.2.8.tar.gz
ls /opt
tar -xf zlib-1.2.8.tar.gz 
mv zlib-1.2.8.tar.gz tars
cd zlib-1.2.8/
ls
less README
mkdir build
../configure
cd build
../configure --help
cd ..
rmdir build
./configure --prefix=/opt/kioskd
make
uname -a
make install
ls /opt/vc
ls /opt/kioskd/
ls /opt/kioskd/lib
ls /opt/kioskd/lib/pkgconfig/
exit
cd /
ls
cd ~
ls
cd kioskd-libs/
ls
mkdir done
mv libpng-1.6.13/ done/
mv done/libpng-1.6.13/ .
mv zlib-1.2.8/ done/
ls
cd libpng-1.6.13/
ls
./configure --help
pkg-config z
pkg-config z --libs
pkg-config zlib --libs
./configure --enable-shared --prefix=/opt/kioskd
make -j5
make install
ls /opt/kioskd/lib
ls /opt/kioskd/lib/pkgconfig/
cd ..
ls
mv libpng-1.6.13/ done
ls
wget http://ijg.org/files/jpegsrc.v9.tar.gz
tar -xf jpegsrc.v9.tar.gz 
mv jpegsrc.v9.tar.gz tars/
ls
cd jpeg-9/
ls
./configure --help
less README
./configure --help
./configure --enable-shared --prefix=/opt/kioskd
make -j5
make install
echo $LD_LIBRARY_RUN
exit
cd /root/kioskd-libs/
ls
ls /opt/kioskd/lib
ls /opt/kioskd/lib/pkgconfig/
ls
cd jpeg-9/
ls
make install
cd ..
mv jpeg-9/ done/
ls
wget http://download.savannah.gnu.org/releases/freetype/freetype-2.5.3.tar.gz.sig
tar -xf freetype-2.5.3.tar.gz.sig 
rm freetype-2.5.3.tar.gz.sig 
wget http://download.savannah.gnu.org/releases/freetype/freetype-2.5.3.tar.gz
ls
tar -xf freetype-2.5.3.tar.gz 
mv freetype-2.5.3.tar.gz tars
ls
cd freetype-2.5.3/
ls
less README
./configure --help
./configure --enable-shared --prefix=/opt/kioskd
make -j4
make install
ls /opt/kioskd/lib
ls /opt/kioskd/include/
ls /opt/kioskd/include/libpng16/
ls
ls /opt/kioskd/lib/pkgconfig/
cd ..
mv freetype-2.5.3/ done/
ls
wget http://dist.schmorp.de/libev/libev-4.19.tar.gz
ls
tar -xf libev-4.19.tar.gz 
mv libev-4.19.tar.gz tars
cd libev-4.19/
ls
less README
./configure --help
./configure --prefix=/opt/kioskd
make -j5
make install
ls
ls /opt/kioskd/lib
ls /opt/kioskd/lib/pkgconfig/
ls /opt/kioskd/include/
cd ..
mv libev-4.19/ done
ls
cd SDL2-2.0.3/
ls
cmake -DCMAKE_INSTALL_PREFIX:PATH=/opt/kioskd
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX:PATH=/opt/kioskd ..
ls
cmake .. -DCMAKE_INSTALL_PREFIX:PATH=/opt/kioskd
cd ..
ls
rmdir build
cd ..
mkdir SDL2-2.0.3-build
cd SDL2-2.0.3-build/
cmake ../SDL2-2.0.3 -DCMAKE_INSTALL_PREFIX:PATH=/opt/kioskd
man cmake
cmake -DCMAKE_INSTALL_PREFIX:PATH=/opt/kioskd  ../SDL2-2.0.3
cmake -DCMAKE_INSTALL_PREFIX:PATH=/opt/kioskd  ../SDL2-2.0.3/CMakeLists.txt 
ls
/host-rootfs/bin/cmake -DCMAKE_INSTALL_PREFIX:PATH=/opt/kioskd  ../SDL2-2.0.3/CMakeLists.txt 
cd ..
ls
rm SDL2* -r
tar -xf tars/SDL2-2.0.3.tar.gz 
ls
cd SDL2-2.0.3/
ls
mkdir BUILD
cmake ..
mkdir BUILD
cd BUILD
cmake ..
cmake .. -DCMAKE_INSTALL_PREFIX:PATH=/opt/kioskd
exit
cd /root/kioskd-libs/SDL2-2.0.3/BUILD/
ls
rm CMakeFiles/ -r
cmake -DCMAKE_INSTALL_PREFIX:PATH=/opt/kioskd  ../SDL2-2.0.3/CMakeLists.txt 
cmake -DCMAKE_INSTALL_PREFIX:PATH=/opt/kioskd
cmake -DCMAKE_INSTALL_PREFIX:PATH=/opt/kioskd ..
/host-rootfs/bin/cmake -DCMAKE_INSTALL_PREFIX:PATH=/opt/kioskd ..
ls /opt/vc/include/EGL/
ls /opt/vc/lib/
cd ..
ls
less README-cmake.txt 
less README-SDL.txt 
less README.txt 
less README-raspberrypi.txt 
sudo rm -rf /opt/vc
rm -r /opt/vc
apt-get install libraspberrypi0 libraspberrypi-bin libraspberrypi-de
apt-get install sudo
nano /etc/apt/sources.list
apt-get update
apt-get install libraspberrypi0 libraspberrypi-bin libraspberrypi-de
apt-cache search raspberrypi
nano /etc/apt/sources.list
apt-get update
apt-get install libraspberrypi0 libraspberrypi-bin libraspberrypi-de
nano /etc/apt/sources.list
apt-get update
apt-get install libraspberrypi0 libraspberrypi-bin libraspberrypi-de
apt-get install libraspberrypi0 libraspberrypi-bin libraspberrypi-dev
ls /opt/vc
ls /opt/vc/bin
ls /opt/vc/lib
ls /opt/vc/include/
ls
nano README-raspberrypi.txt 
cd BUILD
ls
rm ./ -r
rm ./* -rf
cd ..
ls
nano README-raspberrypi.txt 
cd BUILD
--disable-esd
ls
../configure --prefix=/opt/kioskd --disable-pulse --disable-esd
../configure --help
../configure --prefix=/opt/kioskd --disable-pulse --disable-esd --enable-video-opengles 
../configure --help | grep pulse
../configure --prefix=/opt/kioskd --disable-pulse --disable-esd --enable-video-opengles --disable-pulseaudio --disable-pulseaudio-shared 
../configure --prefix=/opt/kioskd --disable-esd --enable-video-opengles --disable-pulseaudio --disable-pulseaudio-shared 
make -j4 
make install
ls /opt/kioskd/lib
ls /opt/kioskd/lib/pkgconfig/
ls /opt/kioskd/include/
ls /opt/kioskd/
cd ..
ls
mv SDL2-2.0.3/ done
wget http://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.0.tar.gz
ls
tar -xf SDL2_image-2.0.0.tar.gz 
ls
mv SDL2_image-2.0.0.tar.gz tars
cd SDL2_image-2.0.0/
ls
./configure --help
./configure --enable-png-shared --enable-jpeg-shared --prefix=/opt/kioskd --enable-shared 
./configure --enable-png-shared --enable-jpg-shared --prefix=/opt/kioskd --enable-shared 
make 
ls /usr/lib
ls /usr/lib/X11/
cd ..
cd done/SDL2-2.0.3/
ls
less README
lee README.txt 
nano README.txt 
nan README-linux.txt 
nano README-linux.txt 
apt-get install libx11 libxext libxrandr libxcursor libxi libxinerama libxxf86vm libxss
apt-cache search libx11
apt-cache search libxext
apt-get install libx11-6 libext6
apt-cache search libxrandr
apt-get install libx11-6 libext6 libxrandr2 
apt-cache search libxinerama
apt-get install libx11-6 libext6 libxrandr2 libxinerama1
apt-cache search libxxf86vm
apt-get install libx11-6 libext6 libxrandr2 libxinerama1 libxxf86vm1
apt-cache search libxss
apt-get install libx11-6 libext6 libxrandr2 libxinerama1 libxxf86vm1 libxss1
apt-get install libx11-6 libxext6 libxrandr2 libxinerama1 libxxf86vm1 libxss1
apt-get install libx11-6 libxext6 libxrandr2 libxinerama1 libxxf86vm1 libxss1 --reinstall
ls /usr/lib
ls /lib
ls /usr/lib/X11/
make -j5
cd ..
ls
cd SDL2_image-2.0.0/
make -j5
whereis Xss
whereis Xss.so
whereis X11.so
ls /usr/bin/X11
ls /usr/bin/X11/X11/
ls /usr/bin
/usr/bin/arm-linux-gnueabihf-gcc
/usr/bin/arm-linux-gnueabihf-gcc --help
/usr/bin/arm-linux-gnueabihf-gcc --version
/opt/xgcc/bin/arm-linux-gnueabihf-gcc --version
find / -iname X11.so
find /usr -iname X11.so
ls /lib
ls /opt
dpkg --help
dpkg -L libx11-6
exit
cd /root/kioskd-libs/
cd SDL2_image-2.0.0/
ls
./configure --enable-png-shared --enable-jpg-shared --prefix=/opt/kioskd --enable-shared 
make -j5
make install
ls /opt/kioskd/lib
ls /opt/kioskd/lib/pkgconfig/
cd ..
mv SDL2_image-2.0.0/ done/
wget http://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.12.tar.gz
ls
tar -xf SDL2_ttf-2.0.12.tar.gz 
mv SDL2_ttf-2.0.12.tar.gz tars/
ls done
ls
cd SDL2_ttf-2.0.12/
LS
ls
nano README.txt 
./configure --help
ls
./configure --prefix=/opt/kioskd
./configure --prefix=/opt/kioskd --with-freetype=/opt/kioskd --with-sdl=/opt/kioskd
./configure --prefix=/opt/kioskd --with-freetype-prefix=/opt/kioskd --with-sdl-prefix=/opt/kioskd
make -j4
make install
ls /opt/kioskd/lib
ls /opt/kioskd/lib/pkgconfig/
cd ..
ls
mv SDL2_ttf-2.0.12/ done/
cd ..
mkdir kioskd-build
ls
cd kioskd-build/
ls
mkdir build
cd build
/host-rootfs/bin/cmake --help | less
/host-rootfs/bin/cmake -DCMAKE_INSTALL_PATH:PATH=/opt/kioskd ..
/host-rootfs/bin/cmake -DCMAKE_INSTALL_PREFIX:PATH=/opt/kioskd ..
rm ./* -r
/host-rootfs/bin/cmake -DCMAKE_INSTALL_PREFIX:PATH=/opt/kioskd ..
ls
make
make install
rm ./* -r
/host-rootfs/bin/cmake -DCMAKE_INSTALL_PREFIX:PATH=/opt/kioskd -DCMAKE_SKIP_INSTALL_RPATH=ON  ..
make
make install
/opt/kioskd/bin/kioskd 
/host-rootfs/bin/cmake -DCMAKE_INSTALL_PREFIX:PATH=/opt/kioskd -DCMAKE_INSTALL_RPATH="/opt/kioskd/lib;/opt/vc/lib"
nano /etc/ld.so.conf
nano /etc/ld.so.conf.d/arm-linux-gnueabihf.conf 
ls
/host-rootfs/bin/cmake -DCMAKE_INSTALL_PREFIX:PATH=/opt/kioskd -DCMAKE_INSTALL_RPATH="/opt/kioskd/lib;/opt/vc/lib" ..
make -j5
make install
rm ./* -r
/host-rootfs/bin/cmake -DCMAKE_INSTALL_PREFIX:PATH=/opt/kioskd -DCMAKE_INSTALL_RPATH="/opt/kioskd/lib;/opt/vc/lib" ..
make
make install
/opt/kioskd/bin/kioskd 
ls /opt/kioskd/include/
cd ..
ls
less CMakeLists.txt 
cd build/
rm ./*
rm ./* -r
cmake ..
/host-rootfs/bin/cmake ..
/host-rootfs/bin/make 
make install
/opt/kioskd/bin/kioskd 
ls
cd ..
tar -cf kioskd.tar /opt/kioskd
ls -lh
ls
cd /opt/kioskd/
ls
mkdir fonts
ls /root/kioskd-build/fonts/
cp /root/kioskd-build/fonts/quartzregulardb.ttf 
cp /root/kioskd-build/fonts/quartzregulardb.ttf .
cp /host-rootfs/home/rikki/Documents/din1451alt.ttf .
ls
mv quartzregulardb.ttf din1451alt.ttf fonts/
cd share/
ls
mkdir kioskd
cd kioskd/
cp /host-rootfs/home/rikki/Pictures/test.png .
ls
cd ~
ls
/opt/kioskd/bin/kioskd 
cd /opt/kioskd/bin/
ls
cp /host-rootfs/home/rikki/Projects/kioskd/testpi.pl test-kioskd.pl
ls -la
ls -lah
chmod +x test-kioskd.pl 
./kioskd 
cd ~
ls
rm kioskd.tar 
tar -cf kioskd.tar /opt/kioskd/
cp kioskd.tar /host-rootfs/scratch/
rm kioskd.tar
ls
cd kioskd-libs
ls
mv done/SDL2-2.0.3/ .
sd SDL2-2.0.3/
cd SDL2-2.0.3/
ls
cd build
cd BUILD
ls
nano config.log
../configure --prefix=/opt/kioskd --disable-esd --enable-video-opengles --disable-pulseaudio --disable-pulseaudio-shared --enable-egl
../configure --help
cd ..
mv SDL2-2.0.3/ done
cd ..
ls
cd kioskd-build/
ls
cd build/
cmake ..
make
make install
rsync /opt/kioskd/ pi@$PI_ADDR:/opt/kioskd
/host-rootfs/bin/rsync /opt/kioskd/ pi@$PI_ADDR:/opt/kioskd
PATH="/host-roofs/usr/bin:$PATH" /host-rootfs/bin/rsync /opt/kioskd/ pi@$PI_ADDR:/opt/kioskd
ssh
exit
cd /root
tar -cf kioskd.tar /opt/kioskd
tar -ls
cp kioskd.tar /host-rootfs/scratch/
nano /opt/kioskd/bin/run-kioskd.sh
chmod +x /opt/kioskd/bin/run-kioskd.sh 
exit
nano /opt/kioskd/bin/run-kioskd.sh 
/opt/kioskd/bin/run-kioskd.sh 
exit
cd ~/kioskd-build/
ls
cd build
cmake ..
make
make install
exit
nano /opt/kioskd/bin/run-kioskd.sh 
cd ~
ls
rm kioskd.tar
tar -cf kioskd.tar /opt/kioskd/
cp kioskd.tar /host-rootfs/scratch/
cd kioskd-libs/
mv done/SDL2-2.0.3/ .
cd SDL2-2.0.3/
ls
cd BUILD
../configure --help | grep egl
../configure --help | grep gl
../configure --help
nano config.log 
less config.log
cat config.log | grep egl
../configure --prefix=/opt/kioskd --disable-esd --enable-video-opengles --disable-pulseaudio --disable-pulseaudio-shared
less config.log 
less config.log | grep EGL
cat config.log | grep EGL
kwrite
nano config.log
cd /opt/vc/include/interface/
ln -s vchiq_arm/ vchiq
ls vcos/pthreads/
pwd
cd
s
ls
cd
ls
exit
cd /root
cd kioskd-libs/
ls
cd SDL2-2.0.3/
cd BUILD
nano config.log 
../configure --prefix=/opt/kioskd --disable-esd --enable-video-opengles --disable-pulseaudio --disable-pulseaudio-shared
nano config.log 
echo $CC
echo $CFLAGS
exit
cd /root/kioskd-libs/SDL2-2.0.3/BUILD/
../configure --help
../configure --prefix=/opt/kioskd --disable-esd --enable-video-opengles --disable-pulseaudio --disable-pulseaudio-shared --without-x --disable-video-opengl --disable-video-x11
make -j5
make install
cd ..
cd kioskd-build/
cd build/
cmake ..
rm ./* -r
cmake ..
make -j4
make install
exit
cd /root/kioskd-build/
ls
cd build/
ls
cd ..
less src/main.c 
cd build
rm ./* -r
cmake ..
make 
make install
exit
cd /root/kioskd-build/
cd build
rm ./* -r
cmake ..
make 
make install
/opt/kioskd/bin/kioskd 
cd ../..
cd kioskd-libs/
cd SDL2-2.0.3/
ls
cd BUILD
nano config.log
../configure --prefix=/opt/kioskd --disable-esd --enable-video-opengles --disable-pulseaudio --disable-pulseaudio-shared  --disable-video-opengl --disable-video-x11
make 
make -j5
../configure --prefix=/opt/kioskd --disable-esd --enable-video-opengles --disable-pulseaudio --disable-pulseaudio-shared  --disable-video-opengl --disable-video-x11
ls
rm ./* -r
../configure --prefix=/opt/kioskd --disable-esd --enable-video-opengles --disable-pulseaudio --disable-pulseaudio-shared  --disable-video-opengl --disable-video-x11
make -j5
make install
/opt/kioskd/bin/kioskd 
../configure --prefix=/opt/kioskd --disable-esd --enable-video-opengles --disable-pulseaudio --disable-pulseaudio-shared 
make -j5
make install
../configure --prefix=/opt/kioskd --disable-esd --enable-video-opengles --disable-pulseaudio --disable-pulseaudio-shared --disable-video-opengl
cat config.log | grep rpi
cd ..
hg clone http://hg.libsdl.org/SDL
/host-rootfs/bin/hg
wget http://libsdl.org/tmp/SDL-2.0.4-9134.tar.gz
tar -xf SDL-2.0.4-9134.tar.gz 
mv SDL-2.0.4-9134.tar.gz tars
cd SDL-2.0.4-9134/
ls
mkdir build
cd build
../configure --help
../configure --prefix=/opt/kioskd --disable-esd --enable-video-opengles --disable-pulseaudio --disable-pulseaudio-shared --disable-video-opengl
cat config.log | grep pi
cat config.log | grep rpi
cat config.log | grep RPi
cat config.log | grep -i rpi
cat config.log | grep -i rPi
cat config.log | grep -i raspberry
less config.
less config.log
nano config.log
cd ..
ls
cd ..
cd SDL2-2.0.3/
ls
nano README-raspberrypi.txt 
sudo apt-get install libudev-dev libasound2-dev libdbus-1-dev
nano README-raspberrypi.txt 
exit
cd /root/kioskd-libs/
cd SDL2-2.0.3/
cd BUILD
ls
rm ./* -r
../configure --prefix=/opt/kioskd --disable-esd --enable-video-opengles --disable-pulseaudio --disable-pulseaudio-shared --disable-video-opengl
ls
ls include/
nano include/SDL_config.h 
nano sdl2-config
whereis libbcm_host
whereis libbcm_host.so
find / -iname *bcm_host*
ls
nano Makefile.rules 
make -j5
cat ../configure | grep -i rpi
nano ../configure
uname
uname --all
nano ../configure
echo $host
nano ../configure
../configure --prefix=/opt/kioskd --disable-esd --enable-video-opengles --disable-pulseaudio --disable-pulseaudio-shared --disable-video-opengl --host=arm-raspberry-linux-gnueabihf
ls
cat include/SDL_config.h | grep RPI
make -j5
make install
ls /opt/vc
ls /opt/vc/lib
ls /usr/lib/
cd ..
cd kioskd-build/
cd BUILD
cd build
rm ./*
rm ./* -r
cmake .
cmake ..
make
make install
cmake ..
make -j5
make install
rm ./* -r
cmake ..
/host-rootfs/bin/cmake ..
make -j2
make install
nano /opt/kioskd/bin/run-kioskd.sh 
/opt/kioskd/bin/run-kioskd.sh 
/opt/kioskd/bin/kioskd 
cd ../..
cd kioskd-libs/
cd SDL2-2.0.3/
cd BUILD
nano config.log
less config.log
../configure --prefix=/opt/kioskd --disable-esd --enable-video-opengles --disable-pulseaudio --disable-pulseaudio-shared --disable-video-opengl --host=arm-raspberry-linux-gnueabihf --without-x
make -j5
make install
cd ..
ls
rm -r SDL-2.0.4-9134/
mv SDL2-2.0.3/ done
cd ..
ls
rm kioskd.tar
tar -cf kioskd.tar /opt/kioskd
nano /opt/kioskd/bin/run-kioskd.sh 
exit
cd /root
apt-get update
apt-cache search boehm
apt-get install libgc-dev
cd /opt
ls
cd vc
ls
cd include/
ls
cd interface/
ls
cd vmcs_host/
ls
cd linux/
ls
exit
