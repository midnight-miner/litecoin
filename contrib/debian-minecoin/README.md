
Debian
====================
This directory contains files used to package minecoind/minecoin-qt
for Debian-based Linux systems. If you compile minecoind/minecoin-qt yourself, there are some useful files here.

## minecoin: URI support ##


minecoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install minecoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your minecoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/bitcoin128.png` to `/usr/share/pixmaps`

minecoin-qt.protocol (KDE)

