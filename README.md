
introduction
============

i'm cam. i wrote a shell as a refresher

it's called cash (cam's shell). it's not very complete. but that
wasn't the point

running
=======

cash uses my personal c library, libcam. for now, i just symlink it in since i 
didn't want to deal with git submodules. make sure to do that at deps/LibCam

cash should run on any linux system with modern gcc

you can run cash using the following steps:
$ mkdir build
$ cd build/
$ cmake ..
$ make
$ ./cash

you can exit cash by typing "exit"

cash doesn't support terminal emulation, so don't run anything that uses it 
(ncurses, vim, whatever)



