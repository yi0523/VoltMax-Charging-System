These SAMA5D2 Applets were built from the Atmel Software Package:

Repository: https://github.com/atmelcorp/atmel-software-package
Commit: b62c87ca480561b67a1d8c5cd5c566afe2b3d0b8

To get the sources and rebuild an applet (using GCC):

1. get the software package source git checkout:
        git clone https://github.com/atmelcorp/atmel-software-package
        git checkout b62c87ca480561b67a1d8c5cd5c566afe2b3d0b8

2. build the applet (for example: qspiflash):
        cd samba_applets/qspiflash
        make TARGET=sama5d2-generic RELEASE=1

3. copy the applet binary to SAM-BA directory
        cp build/applet-qspiflash_sama5d2-generic_sram.bin $SAMBADIR/qml/SAMBA/Device/SAMA5D2/applets

