/*
 * Copyright (c) 2015-2016, Atmel Corporation.
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

/*!
	\qmltype Device
	\inqmlmodule SAMBA
	\brief Defines all required data for a given Device
*/
Item {
	/*!
		\qmlproperty Connection Device::connection
		\brief The parent connection object
	*/
	property var connection

	/*!
		\qmlproperty string Device::family
		\brief The device family
	*/
	property var family

	/*!
		\qmlproperty string Device::name
		\brief The device name
	*/
	property var name

	/*!
		\qmlproperty string Device::description
		\brief The device description
	*/
	property var description

	/*!
		\qmlproperty list<string> Device::aliases
		\brief The connection aliases (alternate names that can be used
		on the command-line)
	*/
	property var aliases

	/*!
		\qmlproperty bool Device::usb_zlp_quirk
		\brief Work-around for devices that don't sent zero-length
		packets
	*/
	property bool usb_zlp_quirk: false

	/*!
		\qmlproperty string Device::applets
		\brief A list of all supported applets for the device
	*/
	property list<Applet> applets

	/*!
		\qmlproperty bool Device::hasMultipleROMVersions
		\brief If true, read the ROM code version to select the relevant
		files before executing secure applets or any of the WSMD, WCKY,
		WRHA or WFCK secure monitor commands
	*/
	property bool hasMultipleROMVersions: false

	/*! \internal */
	property int activeROMVersion: -1

	/*! \internal */
	function setActiveROMVersion(version) {
		activeROMVersion = 0
	}

	/*! \internal */
	function translateSecureAppletUrl(codeUrl) {
		return codeUrl
	}

	/*! \internal */
	function translateInputFileName(filename) {
		return filename
	}

	/*!
		\qmlmethod list<string> Device::appletNames()
		Returns a list of the names of all the applets.
	*/
	function appletNames() {
		var names = []
		for (var i = 0; i < applets.length; i++)
			names.push(applets[i].name)
		return names
	}

	/*!
		\qmlmethod list<string> Device::securedAppletNames()
		Return a list of the names of all the secured applets.
	*/
	function securedAppletNames() {
		var names = []
		for (var i = 0; i < applets.length; i++)
			if (applets[i].connectionType === applets[i].connectionTypeAll ||
			    applets[i].connectionType === applets[i].connectionTypeSecureOnly)
				names.push(applets[i].name)
		return names
	}

	/*!
		\qmlmethod list<string> Device::nonSecuredAppletNames()
		Return a list of the names of all the non-secured applets.
	*/
	function nonSecuredAppletNames() {
		var names = []
		for (var i = 0; i < applets.length; i++)
			if (applets[i].connectionType === applets[i].connectionTypeAll ||
			    applets[i].connectionType === applets[i].connectionTypeNonSecureOnly)
				names.push(applets[i].name)
		return names
	}

	/*!
		\qmlmethod Applet Device::applet(string name)
		Returns the applet with name \a name or \a undefined if not found.
	*/
	function applet(name) {
		for (var i = 0; i < applets.length; i++)
			if (applets[i].name === name &&
			    ((applets[i].connectionType === applets[i].connectionTypeAll) ||
			     (applets[i].connectionType === applets[i].connectionTypeNonSecureOnly && !connection.toSecureMonitor()) ||
			     (applets[i].connectionType === applets[i].connectionTypeSecureOnly && connection.toSecureMonitor())))
				return applets[i]
		return
	}

	/*!
		\qmlmethod void Device::initialize()
		Initialize the device using configured connection.
	*/
	function initialize() {
		// do nothing
	}

	/*! \internal */
	onConnectionChanged: {
		for (var i = 0; i < applets.length; i++)
			applets[i].connection = connection
	}

	/*! \internal */
	Component.onCompleted: {
		for (var i = 0; i < applets.length; i++)
			applets[i].device = this
	}

	/* -------- Command Line Handling -------- */

	/*! \internal */
	function commandLineParse(args)	{
		if (args.length > 2)
			return "Invalid number of arguments."

		if (args.length >= 2) {
			if (args[1].length > 0) {
				config.serial.ioset = Utils.parseInteger(args[1]);
				if (isNaN(config.serial.ioset))
					return "Invalid serial console ioset (not a number)."
			}
		}

		if (args.length >= 1) {
			if (args[0].length > 0) {
				config.serial.instance = Utils.parseInteger(args[0]);
				if (isNaN(config.serial.instance))
					return "Invalid serial console instance (not a number)."
			}
		}

		return true;
	}

	/*! \internal */
	function commandLineHelp() {
		return ["Syntax: " + name + ":[<instance>]:[<ioset>]",
		        "Parameters:",
		        "    instance   Serial console peripheral number",
		        "    ioset      Serial console I/O set",
		        "Examples:",
		        "    " + name + "       use default device/board settings",
		        "    " + name + ":1:2   use fully custom settings (peripheral number 1, I/O set 2)",
		        "    " + name + "::2    use default device/board settings but force use of I/O set 2",
		        "Note:",
		        "    Peripheral numbers and I/O sets are device specific. Please see device documentation in 'doc' directory."]
	}

	/*! \internal */
	function commandLineSecureCommands() {
		return []
	}

	/*! \internal */
	function commandLineSecureCommandHelp(command) {
		// do nothing
	}

	/*! \internal */
	function commandLineSecureCommand(command, args) {
		// do nothing
	}

	/*! \internal */
	function hasSecureCommand(command) {
		var commands = commandLineSecureCommands()

		return commands.indexOf(command) !== -1
	}

	/*! \internal */
	function strerror(code) {
		// do nothing
	}
}
