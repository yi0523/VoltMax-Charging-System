These PIC32CXMT Applets were built from the Atmel Software Package:

Repository: https://github.com/atmelcorp/atmel-software-package
Commit: a18936acf75f1de8c85fb0d20d5ad8e1ea3eeeba

To get the sources and rebuild an applet (using GCC):

1. get the software package source git checkout:
        git clone https://github.com/atmelcorp/atmel-software-package
        git checkout a18936acf75f1de8c85fb0d20d5ad8e1ea3eeeba

2. build the applet (for example: internalflash):
        cd samba_applets/internalflash
        make TARGET=pic32cxmt-generic VARIANT=sram RELEASE=1

3. copy the applet binary to SAM-BA directory
        cp build/applet-internalflash_pic32cxmt-generic_sram.bin $SAMBADIR/qml/SAMBA/Device/PIC32CXMT/applets
