# https://developer.pebble.com/guides/tools-and-resources/pebble-tool/
all:
	pebble build

clean:
	pebble clean

emu1:
	pebble install -v --emulator basalt

run:
	pebble install -v build/mymario.pbw

install:
	pebble install
