import SAMBA 3.5
import SAMBA.Connection.Serial 3.5
import SAMBA.Device.SAMA7G5 3.5

SerialConnection {
	device: SAMA7G5-EK {
	}

	onConnectionOpened: {
		// initialize SDMMC applet
		initializeApplet("sdmmc")

		// write files
		applet.write(0x00000, "sdcard.img")
	}
}
