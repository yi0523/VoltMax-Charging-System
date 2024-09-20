These SAM9xx5 Applets were built from the Atmel Software Package:

Repository: https://github.com/atmelcorp/atmel-software-package
Commit: b62c87ca480561b67a1d8c5cd5c566afe2b3d0b8

To get the sources and rebuild an applet (using GCC):

1. get the software package source git checkout:
        git clone https://github.com/atmelcorp/atmel-software-package
        git checkout b62c87ca480561b67a1d8c5cd5c566afe2b3d0b8

2. build the applet (for example: serialflash):
        cd samba_applets/serialflash
        make TARGET=sam9x25-generic VARIANT=ddram RELEASE=1

3. copy the applet binary to SAM-BA directory
        cp build/applet-serialflash_sam9x25-generic_ddram.bin $SAMBADIR/qml/SAMBA/Device/SAM9xx5/applets

