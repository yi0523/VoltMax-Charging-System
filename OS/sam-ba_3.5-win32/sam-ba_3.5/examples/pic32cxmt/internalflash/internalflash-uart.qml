import SAMBA 3.5
import SAMBA.Connection.Serial 3.5
import SAMBA.Device.PIC32CXMT 3.5

SerialConnection {
	//port: "ttyUSB0"
	//port: "COM85"

	device: PIC32CXMT {
	}

	onConnectionOpened: {
		// initialize internal flash applet
		initializeApplet("internalflash")

		// erase all memory
		applet.erase(0, applet.memorySize)

		// write files
		applet.write(0x00000, "program.bin")

		// Set GPNVM[8:5] to 0011b
		applet.setGPNVM(GPNVM.SBS_STANDARD_BOOT, GPNVM.SBS_MASK)
	}
}