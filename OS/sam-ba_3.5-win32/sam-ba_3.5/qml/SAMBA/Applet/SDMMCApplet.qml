/*
 * Copyright (c) 2015-2017, Atmel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 */

import QtQuick 2.3
import SAMBA 3.5

/*! \internal */
Applet {
	name: "sdmmc"
	description: "SD/MMC"
	commands: [
		AppletCommand { name:"initialize"; code:0 },
		AppletCommand { name:"readPages"; code:0x32 },
		AppletCommand { name:"writePages"; code:0x33 },
		AppletCommand { name:"enableBootPartition"; code:0x37 }
	]

	/*! \internal */
	function buildInitArgs() {
		var config = device.config.sdmmc

		if (typeof config.instance === "undefined")
			throw new Error("Incomplete SD/MMC configuration, missing value for 'instance' property")

		if (typeof config.ioset === "undefined")
			throw new Error("Incomplete SD/MMC configuration, missing value for 'ioset' property")

		if (typeof config.partition === "undefined")
			throw new Error("Incomplete SD/MMC configuration, missing value for 'partition' property")

		if (typeof config.busWidth === "undefined")
			throw new Error("Incomplete SD/MMC configuration, missing value for 'busWidth' property")

		if (typeof config.voltages === "undefined")
			throw new Error("Incomplete SD/MMC configuration, missing value for 'voltages' property")

		var args = defaultInitArgs()
		args.push(config.instance)
		args.push(config.ioset)
		args.push(config.partition)
		args.push(config.busWidth)
		args.push(config.voltages)
		return args
	}

	/* -------- Command Line Handling -------- */

	/*! \internal */
	function commandLineParse(args)	{
		if (args.length > 5)
			return "Invalid number of arguments."

		var config = device.config.sdmmc

		if (args.length >= 5) {
			if (args[4].length > 0) {
				config.voltages = Utils.parseInteger(args[4]);
				if (isNaN(config.voltages))
					return "Invalid SD/MMC voltages (not a number)."
			}
		}

		if (args.length >= 4) {
			if (args[3].length > 0) {
				config.busWidth = Utils.parseInteger(args[3]);
				if (isNaN(config.busWidth))
					return "Invalid SD/MMC bus width (not a number)."
			}
		}

		if (args.length >= 3) {
			if (args[2].length > 0) {
				config.partition = Utils.parseInteger(args[2]);
				if (isNaN(config.partition))
					return "Invalid SD/MMC partition (not a number)."
			}
		}

		if (args.length >= 2) {
			if (args[1].length > 0) {
				config.ioset = Utils.parseInteger(args[1]);
				if (isNaN(config.ioset))
					return "Invalid SD/MMC ioset (not a number)."
			}
		}

		if (args.length >= 1) {
			if (args[0].length > 0) {
				config.instance = Utils.parseInteger(args[0]);
				if (isNaN(config.instance))
					return "Invalid SD/MMC instance (not a number)."
			}
		}

		return true;
	}

	/*! \internal */
	function commandLineHelp() {
		return ["Syntax: sdmmc:[<instance>]:[<ioset>]:[<partition>]:[<bus_width>]:[<voltages>]",
		        "Parameters:",
		        "    instance   SDMMC controller number",
		        "    ioset      SDMMC I/O set",
		        "    partition  Partition number (0=user partition, x>0=boot partition x)",
		        "    bus_width  Data bus width (0=controller max, 1=1-bit, 4=4-bit, 8=8-bit)",
		        "    voltages   Supported voltages (bitfield: 1=1.8V, 2=3.0V, 4=3.3V)",
		        "Examples:",
		        "    sdmmc           use default board settings",
		        "    sdmmc:0:1:1:8:5 use fully custom settings (SDMMC0, IOSET1, first boot partition, 8-bit, 1.8V/3.3V)",
		        "    sdmmc:0::1      use default board settings but force use of SDMMC0, first boot partition"]
	}

	/*! \internal */
	function commandLineCommands() {
		 var commands = defaultCommandLineCommands()
		 commands.push("enablebootpartition")
		 return commands
	}

	/*! \internal */
	function commandLineCommandHelp(command) {
		 if (command === "enablebootpartition") {
			return ["* enablebootpartition - enable/disable eMMC boot partition",
				"Syntax:",
				"    enablebootpartition:[<partition>]",
				"Examples:",
				"    enablebootpartition    disable boot partitions",
				"    enablebootpartition:1  enable boot partition 1",
				"    enablebootpartition:2  enable boot partition 2"]
		 }
		 else {
			return defaultCommandLineCommandHelp(command)
		 }
	}

	/*!
		\qmlmethod void SDMMCApplet::enableBootPartition(int boot_partition)
		\brief Enable/disable e.MMC boot partitions

		Enable/disable partition \a boot_partition.

		Throws an \a Error if an error occured during the applet command.
	*/
	function enableBootPartition(boot_partition) {
		var cmd, status

		if (typeof boot_partition === "undefined")
			boot_partition = 0

		cmd = command("enableBootPartition")
		if (cmd) {
			status = connection.appletExecute(cmd, [boot_partition])
			if (status === 0)
				memoryPages = connection.appletMailboxRead(0)
			else
				return "Enable Boot Partition command failed (status=" + status + ")"
		} else {
			return "Applet does not support 'Enable Boot Partition' command"
		}
	}

	/*! \internal */
	function commandLineCommandEnableBootPartition(args) {
		var boot_partition

		switch(args.length) {
		case 1:
			if (args[0].length > 0) {
				boot_partition = Utils.parseInteger(args[0])
				if (isNaN(boot_partition) || boot_partition < 0 || boot_partition > 2)
					return "Invalid boot partition (expected 0, 1 or 2)."
			}
			// fall-through
		case 0:
			break
		default:
			return "Invalid number of arguments (expected 0 or 1)."
		}

		enableBootPartition(boot_partition)
	}

	/*! \internal */
	function commandLineCommand(command, args) {
		if (command === "enablebootpartition") {
			return commandLineCommandEnableBootPartition(args)
		}
		else {
			return defaultCommandLineCommand(command, args)
		}
	}
}
