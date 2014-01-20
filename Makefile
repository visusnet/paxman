INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = $(INSTALL) -m 755
INSTALL_DATA = $(INSTALL) -m 644
INSTALL_SCRIPT = $(INSTALL) -m 744
INSTALL_DIRECTORY = $(INSTALL) -d

CC = gcc
CXX = g++
CXXCPP = $(CXX) -E
ECHO = echo

SDLCONFIG = -lSDL -lSDL_ttf
XMLCONFIG = -lxml2
CFLAGS = -arch x86_64 $(xml2-config --cflags)


COMPILE = $(CC)
#STATIC = -static

main: main.o map.o character.o controls.o ghost.o shell.o configuration.o gfx.o
	$(COMPILE) -L/usr/local/lib -lSDLmain -lSDL -Wl,-framework,Cocoa -arch x86_64 -o main main.o character.o map.o controls.o ghost.o shell.o configuration.o gfx.o $(SDLCONFIG) $(XMLCONFIG) $(CFLAGS)

main.o :  main.c main.h map.c map.h controls.c controls.h character.c character.h shell.c shell.h configuration.c configuration.h gfx.c gfx.h
	$(COMPILE) -arch x86_64 -c main.c $(CFLAGS) -L/usr/local/lib -lSDLmain -lSDL -Wl,-framework,Cocoa -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk/usr/include/libxml2

map.o :  map.c map.h character.h globals.h ghost.h
	$(COMPILE) -arch x86_64 -c map.c $(CFLAGS)

controls.o :  controls.c controls.h character.h globals.h
	$(COMPILE) -arch x86_64 -c controls.c $(CFLAGS)

character.o :  character.c character.h
	$(COMPILE) -arch x86_64 -c character.c $(CFLAGS)

ghost.o :  ghost.c ghost.h map.h
	$(COMPILE) -arch x86_64 -c ghost.c $(CFLAGS)

shell.o :  shell.c shell.h
	$(COMPILE) -arch x86_64 -c shell.c $(CFLAGS)

configuration.o : configuration.c configuration.h
	$(COMPILE) -arch x86_64 -c configuration.c $(CFLAGS) -L/usr/local/lib -lSDLmain -lSDL -Wl,-framework,Cocoa -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk/usr/include/libxml2

gui.o :  gfx.c gfx.h
	$(COMPILE) -arch x86_64 -c gfx.c $(CFLAGS)

install : main
	if ! [ -d /etc/paxman ] ; then mkdir /etc/paxman; fi
	if ! [ -d /etc/paxman/img ] ; then mkdir /etc/paxman/img; fi
	if ! [ -d /etc/paxman/maps ] ; then mkdir /etc/paxman/maps; fi
	if ! [ -d /etc/paxman/fonts ] ; then mkdir /etc/paxman/fonts; fi
	$(INSTALL_PROGRAM) ./main		/etc/paxman/paxman
	$(INSTALL_DATA) ./config.xml.unix	/etc/paxman/config.xml
	$(INSTALL_DATA) ./paxman.1		/usr/share/man/man1/paxman.1
	$(INSTALL_DATA) ./maps/arrow		/etc/paxman/maps/arrow
	$(INSTALL_DATA) ./maps/default	/etc/paxman/maps/default
	$(INSTALL_DATA) ./maps/visusMAPfire	/etc/paxman/maps/visusMAPfire
	$(INSTALL_DATA) ./maps/visusMAPlab	/etc/paxman/maps/visusMAPlab
	$(INSTALL_DATA) ./maps/visusMAPone	/etc/paxman/maps/visusMAPone
	$(INSTALL_DATA) ./img/coin.bmp	/etc/paxman/img/coin.bmp
	$(INSTALL_DATA) ./img/empty.bmp	/etc/paxman/img/empty.bmp
	$(INSTALL_DATA) ./img/ghost.bmp	/etc/paxman/img/ghost.bmp
	$(INSTALL_DATA) ./img/pacman.bmp	/etc/paxman/img/pacman.bmp
	$(INSTALL_DATA) ./img/pmdown.bmp	/etc/paxman/img/pmdown.bmp
	$(INSTALL_DATA) ./img/pmleft.bmp	/etc/paxman/img/pmleft.bmp
	$(INSTALL_DATA) ./img/pmright.bmp	/etc/paxman/img/pmright.bmp
	$(INSTALL_DATA) ./img/pmup.bmp	/etc/paxman/img/pmup.bmp
	$(INSTALL_DATA) ./img/wall.bmp	/etc/paxman/img/wall.bmp
	$(INSTALL_DATA) ./fonts/font.ttf	/etc/paxman/fonts/font.ttf
	ln -s /etc/paxman/paxman /usr/local/bin/paxman

clean :
	rm -f *.o main

deinstall :
	if [ -e /usr/local/bin/paxman ] ; then rm /usr/local/bin/paxman; fi
	if [ -e /usr/share/man/man1/paxman.1 ] ; then rm /usr/share/man/man1/paxman.1; fi
	if [ -d /etc/paxman ]; then rm -rf /etc/paxman; fi

reinstall : deinstall install

