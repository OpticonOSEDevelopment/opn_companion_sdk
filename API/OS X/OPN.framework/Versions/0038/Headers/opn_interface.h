/*
 *  opn_interface.h
 *	opn_driver
 *
 *  Created by Scott McGhee on 9/26/07.
 *	Updated by Scott McGhee on 7/20/10.
 *	Updated by Yumi Kimura on 6/14/10.
 *  Copyright 2011 Opticon Inc. All rights reserved.
 *
 */

/*!
    @header opn_interface
	@abstract		Header file containing the API for the libopn_driver library.
	@discussion		This API controls the OPN 2001/2003 driver, a driver in the form of 
		a dynamically linked library.  Note that this library must be loaded at load time, 
		meaning it is a dependent library of any client code that uses it.  <b>You must add the OPN.framework to your 
		projects, to use the framework.  The library's install location is "\@executable_path/../
		Frameworks" (although, the path may be changed with install_name_tool).</b>
 
		The OPN framework utilizes the Carbon Event Manager to signal client code of 
		three possible events: 1) the OPN has been removed, 2) the OPN has been inserted, or 3) 
		the OPN has data.  The particulars of each event (its class and kind, which together, 
		compose its type) can be accessed via API functions defined in this file.  However, it 
		is the responsibility of any client code utilizing this library to implement event 
		handler functions, install these functions, and run the application event loop.  
		Examples of how to do this are illustrated in the project "opn_test."  More information 
		about the Carbon Event Manager, and how to use it, can be found in the Apple Developer 
		documentation.  See the 
		<a href="http://developer.apple.com/documentation/Carbon/Conceptual/Carbon_Event_Manager/Intro/chapter_1_section_1.html">
		Carbon Event Manager Programming Guide</a> for details.  
 
		Note that this library is dependent upon the Carbon, CoreFoundation, and IOKit 
		frameworks.  These are part of any normal OS X installation, and though it's probably 
		impossible for OS X to run without them, it's noted here for completeness.  This 
		library should run on both x86 and PPC flavors of OS X.
 
		This driver should only be used with OPN firmware version RBBV0120 and later.
	@copyright 2011 Opticon Inc.
	@updated 7-21-2011
	@version EGFS0038 (0.0.3.8)
*/


/***********************************************************************************************
*	INCLUDES
***********************************************************************************************/
#include <CoreFoundation/CoreFoundation.h>

/***********************************************************************************************
*	DEFINES
***********************************************************************************************/

//return status codes
/*!
	@group Function Status Codes
 */
/*!
	@defined STATUS_OK
	@abstract Return value of a function that executes with no errors.
*/
#define STATUS_OK					0
/*!
	@defined COMMUNICATIONS_ERROR
	@abstract Return value of a function that indicates there was a communication error.
 */
#define COMMUNICATIONS_ERROR		-1
/*!
	@defined BAD_PARAM
	@abstract Return value of a function that indicates there was a bad parameter to the 
		function.
 */
#define BAD_PARAM					-2
/*!
	@defined SETUP_ERROR
	@abstract Return value of a function that indicates the driver instance was in a state 
		that didn't permit it to carry out the function.
 */
#define SETUP_ERROR					-3
/*!
	@defined INVALID_COMMAND_NUMBER
	@abstract Return value of a function that indicates that the command sent to the driver 
		was not defined.
 */
#define INVALID_COMMAND_NUMBER		-4
/*!
	@defined COMMAND_LRC_ERROR
	@abstract Return value of a function that indicates that the CRC check on written or 
		read data failed.
 */
#define COMMAND_LRC_ERROR			-7
/*!
	@defined RECEIVED_CHARACTER_ERROR
	@abstract Return value of a function that indicates that the function encountered a value 
		it did not expect.
 */
#define RECEIVED_CHARACTER_ERROR	-8
/*!
	@defined GENERAL_ERROR
	@abstract Return value of a function that indicates that some error occurred.
 */
#define GENERAL_ERROR				-9
/*!
	@group Buffer Sizes
 */

//sizes for argument buffers
/*!
	@defined TIME_BUFFER_SIZE
	@abstract Expected size of the buffer holding time data for getTimeCmd() and setTimeCmd().
 */
#define TIME_BUFFER_SIZE			6
/*!
	@defined DEVICE_ID_SIZE
	@abstract Expected size of the buffer holding the Device ID, including the trailing null
		character.
 */
#define DEVICE_ID_SIZE				9
/*!
	@defined SOFTWARE_VERSION_SIZE
	@abstract Expected size of the buffer holding the Software Version, including the trailing 
		null character.
 */
#define SOFTWARE_VERSION_SIZE		9
/*!
	@defined LIBRARY_VERSION_SIZE
	@abstract Expected size of the buffer holding the driver version, including the trailing 
		null character.
 */
#define LIBRARY_VERSION_SIZE		9
/*!
 @defined COMPOSITE_CLASS
 @abstract Return value of a function that indicates composite device is connected.
 */
#define COMPOSITE_CLASS			20
/*!
 @defined COMMUNICATION_CLASS
 @abstract Return value of a function that indicates communication device(CDC) is connected.
 */
#define COMMUNICATION_CLASS		21
/*!
 @defined OPN_2001
 @abstract Return value of a function that indicates OPN2001 is connected.
 */
#define OPN_2001				2001
/*!
 @defined OPN_2003
 @abstract Return value of a function that indicates OPN2003 is connected.
 */
#define OPN_2003				2003

//these functions are exported
#pragma GCC visibility push(default)


/***********************************************************************************************
*	API
***********************************************************************************************/

//creation and destruction
typedef struct DriverHandler* OPNInterface;


/*!
	@group Functions
 */
/*!
	@functiongroup Creation / Destruction Functions
 */
/*!
	@function CreateOPNInterface
	@abstract Instantiates and initializes the libopn_driver library.
	@result An opaque pointer of type OPNInterface, needed to call other functions.
	@discussion This function must be called before all others, except for getEventClass, 
		getEventKindInsert, getEventKindRemove, and getEventKindDataAvailable.
 */
extern "C"		OPNInterface		CreateOPNInterface();
/*!
	@function DestroyOPNInterface
	@abstract Cleans up and destroys the instance of the libopn_driver library.
	@param interface The OPNInterface opaque pointer returned by CreateOPNInterface().
	@discussion This function should be called when the interface to the device is no longer 
		necessary.  For example, in a client application's cleanup code.
 */
extern "C"		void				DestroyOPNInterface(OPNInterface interface);

//commands
/*!
@functiongroup OPN Command Functions
 */
/*!
	@function getTimeCmd
	@abstract Gets the RTC (real-time clock) timestamp from the device.
 	@param interface The OPNInterface opaque pointer returned by CreateOPNInterface().
	@param TimeBuffer	A pointer to a byte buffer to hold the timestamp.  The buffer 
		should be of size TIME_BUFFER_SIZE.
	@param BufferLength	Input: a pointer to a variable holding the size of TimeBuffer.  
		Output: the pointer is updated to hold the number of bytes read into TimeBuffer.
	@result A status code.  See the status code defines for the possible returned codes.
	@discussion TimeBuffer should be passed to the timeStamp2String function in order 
		to convert the TimeBuffer into a human-readable date and time string.
 */
extern "C"		SInt32	getTimeCmd(OPNInterface interface, UInt8* TimeBuffer, UInt32* BufferLength);
/*!
	@function setTimeCmd
	@abstract Sets the RTC (real-time clock) time of the device.
 	@param interface The OPNInterface opaque pointer returned by CreateOPNInterface().
	@param TimeBuffer	A pointer to a byte buffer to holding the timestamp to set.  
		The buffer should be of size TIME_BUFFER_SIZE.
	@param BufferLength	The size of TimeBuffer.
	@result A status code.  See the status code defines for the possible returned codes.
 */
extern "C"		SInt32	setTimeCmd(OPNInterface interface, UInt8* TimeBuffer, UInt32 BufferLength);
/*!
	@function interrogateCmd
	@abstract Queries the device for its Device ID, Software Version, Protocol Version, 
		and System Status.
 	@param interface The OPNInterface opaque pointer returned by CreateOPNInterface().
	@result A status code.  See the status code defines for the possible returned codes.
	@discussion After this function has been called, the getDeviceID function, the 
		getSoftwareVersion function, the getProtocolVersion function, and the 
		getSystemStatus function will return appropriate values in their passed-in 
		buffers.
 */
extern "C"		SInt32	interrogateCmd(OPNInterface interface);
/*!
	@function powerDownCmd
	@abstract Shuts down the device.
 	@param interface The OPNInterface opaque pointer returned by CreateOPNInterface().
	@result A status code.  See the status code defines for the possible returned codes.
	@discussion The usefulness or relevance of this function is dubious.
 */
extern "C"		SInt32	powerDownCmd(OPNInterface interface);
/*!
	@function clearDataCmd
	@abstract Erases stored barcodes from the device.
 	@param interface The OPNInterface opaque pointer returned by CreateOPNInterface().
	@result A status code.  See the status code defines for the possible returned codes.
	@discussion If you read the barcodes stored in the device, and don't call this function 
		to clear them, then on the next read, the previously read barcodes will be read 
		again, because they haven't been erased.
 */
extern "C"		SInt32	clearDataCmd(OPNInterface interface);
/*!
	@function setDefaultsCmd
	@abstract Restores the device to a default state.
 	@param interface The OPNInterface opaque pointer returned by CreateOPNInterface().
	@result A status code.  See the status code defines for the possible returned codes.
	@discussion This function will reset any parameters that have been changed via 
		setParamCmd.
 */
extern "C"		SInt32	setDefaultsCmd(OPNInterface interface);
/*!
	@function getParamCmd
	@abstract Retrieves the associated value of a parameter.
 	@param interface The OPNInterface opaque pointer returned by CreateOPNInterface().
	@param Param	A value signifying the parameter to obtain the associated value for.
	@param ParamValue	A pointer to a buffer that will, on return, hold the associated 
		value of the parameter.
	@param ParamValueLength	Input: a pointer to a variable holding the size of 
		ParamValue.  Output: the pointer is updated to hold the number of bytes read 
		into ParamValue.
	@result A status code.  See the status code defines for the possible returned codes.
 */
extern "C"		SInt32	getParamCmd(OPNInterface interface, UInt8 Param, char* ParamValue, UInt32* ParamValueLength);
/*!
	@function setParamCmd
	@abstract Sets the associated value of a parameter.
 	@param interface The OPNInterface opaque pointer returned by CreateOPNInterface().
	@param Param	A value signifying the parameter to set the associated value for.
	@param ParamValue	A pointer to a buffer that holds the new associated value of the 
		parameter.
	@param ParamValueLength	The size of ParamValue.
	@result A status code.  See the status code defines for the possible returned codes.
 */
extern "C"		SInt32	setParamCmd(OPNInterface interface, UInt8 Param, char* ParamValue, UInt32 ParamValueLength);

//barcode data I/O
/*!
@functiongroup Barcode Functions
 */
/*!
	@function isDataAvailable
	@abstract Indicates whether or not the device has barcode data.
 	@param interface The OPNInterface opaque pointer returned by CreateOPNInterface().
	@param DataAvailable	A pointer to a boolean that will, on return, be true if there 
		is barcode data to be read, and false if there is not.
	@result A status code.  See the status code defines for the possible returned codes.
 */
extern "C"		SInt32	isDataAvailable(OPNInterface interface, bool* DataAvailable);
/*!
	@function readData
	@abstract Reads barcodes from the device.
 	@param interface The OPNInterface opaque pointer returned by CreateOPNInterface().
	@param NumberOfCodes	A pointer to a value that will, on return, contain the number of 
		barcodes that have been read from the device.
	@result A status code.  See the status code defines for the possible returned codes.
	@discussion This function must be called to read barcodes from the device.  However, 
		the barcodes are only returned to client code via getBarcode.
 
		Note that the driver's internal storage of read barcodes is erased on every 
		successful call to this function.  The barcodes are only erased from the device, 
		however, when clearDataCmd is called.
 */
extern "C"		SInt32	readData(OPNInterface interface, UInt32* NumberOfCodes);
/*!
	@function getBarcode
	@abstract Retrieves a read barcode.
 	@param interface The OPNInterface opaque pointer returned by CreateOPNInterface().
	@param BarcodeData	A pointer to a buffer that will contain the data of the read barcode.
	@param BarcodeNumber	A number, within the domain of 0 <= n <= N (where N is the 
		total number of read barcodes, got by readData), signifying the barcode to be 
		returned in BarcodeData.
	@param BarcodeDataLength	Input: a pointer to a variable holding the size of BarcodeData.  
		Output: the pointer is updated to hold the number of bytes read into BarcodeData.
	@result A status code.  See the status code defines for the possible returned codes.
	@discussion Probably best used in a loop designed to retrieve every read barcode.
 
		Note that calling this function does not erase the retrieved barcode from the driver's 
		internal storage of read barcodes.
 
		The first byte of the returned barcode data is the barcode's length (the length doesn't 
		include the first byte).  The second byte is the barcode symbology, which can be passed 
		to getCodeType to retrieve the symbology name.  The last four bytes, if the RTC 
		timestamp is set to be appended to each barcode the device reads, is the timestamp of 
		when the barcode was read (which can be passed to timeStamp2String to return a 
		formatted date/time string).  All of the bytes between the barcode symbology byte, and 
		(potentially) the RTC timestamp bytes, compose the actual barcode data.
 */
extern "C"		SInt32	getBarcode(OPNInterface interface, char* BarcodeData, UInt32 BarcodeNumber, UInt32* BarcodeDataLength);

//getters and setters for private fields
/*!
@functiongroup Getter / Setter Functions
 */
/*!
	@function getProtocolVersion
	@abstract Retrieves the protocol version of the device.
 	@param interface The OPNInterface opaque pointer returned by CreateOPNInterface().
	@param PV	A pointer to an integer variable that will contain, on return, the protocol 
		version.
	@result BAD_PARAM if PV is NULL, or STATUS_OK on success.
	@discussion One of the command functions must be called before this function returns any 
		meaningful data.
 */
extern "C"		SInt32	getProtocolVersion(OPNInterface interface, UInt32* PV);
/*!
	@function getDeviceID
	@abstract Retrieves the device ID of the device.
 	@param interface The OPNInterface opaque pointer returned by CreateOPNInterface().
	@param DevID	A pointer to a buffer that will contain the data composing the device ID.
	@param DevIDLength	The size of the DevID buffer.
	@result BAD_PARAM if DevID is NULL or DevIDLength is less than DEVICE_ID_SIZE; STATUS_OK on 
		success.
	@discussion One of the command functions must be called before this function returns any 
		meaningful data.
 */
extern "C"		SInt32	getDeviceID(OPNInterface interface, char* DevID, UInt32 DevIDLength);
/*!
	@function getSystemStatus
	@abstract Retrieves the system status of the device.
 	@param interface The OPNInterface opaque pointer returned by CreateOPNInterface().
	@param SysStat	A pointer to an integer variable that will contain, on return, the system 
		status.
	@result BAD_PARAM if SysStat is NULL, or STATUS_OK on success.
	@discussion One of the command functions must be called before this function returns any 
		meaningful data.
 */
extern "C"		SInt32	getSystemStatus(OPNInterface interface, UInt32* SysStat);
/*!
	@function getSoftwareVersion
	@abstract Retrieves the software version of the device.
 	@param interface The OPNInterface opaque pointer returned by CreateOPNInterface().
	@param SV	A pointer to a buffer that will contain the data composing the software version.
	@param SVLength	The size of the SV buffer.
	@result BAD_PARAM if SV is NULL or SVLength is less than SOFTWARE_VERSION_SIZE; STATUS_OK on 
		success.
	@discussion One of the command functions must be called before this function returns any 
		meaningful data.
 */
extern "C"		SInt32	getSoftwareVersion(OPNInterface interface, char* SV, UInt32 SVLength);
/*!
	@function getRetryCount
	@abstract Retrieves the retry count for the interrogate command.
 	@param interface The OPNInterface opaque pointer returned by CreateOPNInterface().
	@param Retries	A pointer to an integer variable that will contain, on return, the retry 
		count.
	@result BAD_PARAM if Retries is NULL, or STATUS_OK on success.
	@discussion The interrogate command will attempt to execute up to the number of times 
		returned in Retries if it doesn't execute successfully before then.
 */
extern "C"		SInt32	getRetryCount(OPNInterface interface, UInt32* Retries);
/*!
	@function setRetryCount
	@abstract Sets the retry count for the interrogate command.
 	@param interface The OPNInterface opaque pointer returned by CreateOPNInterface().
	@param Retries	The new value for the retry count.
	@result BAD_PARAM if Retries is less than 0 or greater than 9, or STATUS_OK on success.
	@discussion The interrogate command will attempt to execute up to the number of times 
		specified in Retries if it doesn't execute successfully before then.
 */
extern "C"		SInt32	setRetryCount(OPNInterface interface, UInt32 Retries);
/*!
	@function getCodeType
	@abstract Looks up and retrieves a symbology name from a symbology ID.
 	@param interface The OPNInterface opaque pointer returned by CreateOPNInterface().
	@param CodeName	A pointer to a buffer that will contain the symbology name.
	@param CodeNameLength	The size of the CodeName buffer.
	@param CodeID	The symbology ID used to look up the symbology name.
	@result BAD_PARAM if CodeName is NULL; GENERAL_ERROR on an error; or STATUS_OK on success.
	@discussion The driver must be loaded and CreateOPNInterface called before this function 
		can be called.
 */
extern "C"		SInt32	getCodeType(OPNInterface interface, char* CodeName, UInt32 CodeNameLength, UInt8 CodeID);
/*!
	@function getASCIIMode
	@abstract Retrieves the data encoding of the barcodes read by the device.
 	@param interface The OPNInterface opaque pointer returned by CreateOPNInterface().
	@param AM	A pointer to a boolean variable that will contain, on return, true if 
		the data encoding is ASCII, and false if it's binary.
	@result BAD_PARAM if AM is NULL, or STATUS_OK on success.
	@discussion readData must be called before this function returns any meaningful data.
 */
extern "C"		SInt32	getASCIIMode(OPNInterface interface, bool* AM);
/*!
	@function getRTCMode
	@abstract Retrieves a value indicating whether the barcodes read by the device have a 
		timestamp appended to them, indicating when they were read.
 	@param interface The OPNInterface opaque pointer returned by CreateOPNInterface().
	@param RTC	A pointer to a boolean variable that will contain, on return, true if the 
		timestamp data is appended, and false if not.
	@result BAD_PARAM if RTC is NULL, or STATUS_OK on success.
	@discussion readData must be called before this function returns any meaningful data.
 */
extern "C"		SInt32	getRTCMode(OPNInterface interface, bool* RTC);
/*!
	@function getLibraryVersion
	@abstract Retrieves the version of this library.
 	@param interface The OPNInterface opaque pointer returned by CreateOPNInterface().
	@param VersionString	A pointer to a buffer that will contain the driver version string.
	@param VersionStringLength	The size of the VersionString buffer.
	@result BAD_PARAM if VersionString is NULL or VersionStringLength is less than 
		LIBRARY_VERSION_SIZE; STATUS_OK on success.
	@discussion The driver version string is 8 characters (e.g. RABS0030).
 */
extern "C"		SInt32	getLibraryVersion(OPNInterface interface, char* VersionString, UInt32 VersionStringLength);
/*!
 @function getConnectedDeviceClass
 @abstract Retrieves the connected device classs.
 @param interface The OPNInterface opaque pointer returned by CreateOPNInterface().
 @result COMPOSITE_CLASS if composite device is connected;
 COMMUNICATION_CLASS if communication device is connected; COMMUNICATION_ERROR if no device is connected.
 @discussion OPN2001 connect composite class always. 
 OPN2003 enable to connect composite class or communication class.
 */
extern "C"		SInt32	getConnectedDeviceClass(OPNInterface interface);
/*!
 @function getConnectedDeviceName
 @abstract Retrieves the connected device name.
 @param interface The OPNInterface opaque pointer returned by CreateOPNInterface().
 @result OPN_2001 if OPN 2001 is connected;
 OPN_2003 if OPN 2003 device is connected; COMMUNICATION_ERROR if no device is connected.
 */
extern "C"		SInt32	getConnectedDeviceName(OPNInterface interface);
//getters for event type data
/*!
	@function getUSBEventClass
	@abstract Retrieves a value used to signify the class of events generated by the library.
	@result An integer value signifying the event class for library-generated events.
	@discussion This function may be called before CreateOPNInterface.
 
		An event type is made up of an event class and an event kind.  Event types are 
		essentially how events get matched to event handlers.  The event class returned by 
		this function is defined by the library, meaning that this function must be utilized 
		when installing and/or handling the insertion, removal, or device-has-data events.
 */
extern "C"		UInt32	getUSBEventClass();
/*!
	@function getUSBEventKindInsert
	@abstract Retrieves a value used to specify what kind of event, within a class of events, 
		a particular event is.  In this case, a library-generated device-insertion event.
	@result An integer value signifying the event kind for a library-generated insertion event.
	@discussion This function may be called before CreateOPNInterface.
 
		An event type is made up of an event class and an event kind.  Event types are 
		essentially how events get matched to event handlers.  The event kind returned by 
		this function is defined by the library, meaning that this function must be utilized 
		when installing and/or handling the insertion event.
 */
extern "C"		UInt32	getUSBEventKindInsert();
/*!
	@function getUSBEventKindRemove
	@abstract Retrieves a value used to specify what kind of event, within a class of events, 
		a particular event is.  In this case, a library-generated device-removal event.
	@result An integer value signifying the event kind for a library-generated removal event.
	@discussion This function may be called before CreateOPNInterface.
 
		An event type is made up of an event class and an event kind.  Event types are 
		essentially how events get matched to event handlers.  The event kind returned by 
		this function is defined by the library, meaning that this function must be utilized 
		when installing and/or handling the removal event.
 */
extern "C"		UInt32	getUSBEventKindRemove();
/*!
	@function getUSBEventKindDataAvailable
	@abstract Retrieves a value used to specify what kind of event, within a class of events, 
		a particular event is.  In this case, a library-generated device-has-data event.
	@result An integer value signifying the event kind for a library-generated device-has-data 
		event.
	@discussion This function may be called before CreateOPNInterface.
 
		An event type is made up of an event class and an event kind.  Event types are 
		essentially how events get matched to event handlers.  The event kind returned by 
		this function is defined by the library, meaning that this function must be utilized 
		when installing and/or handling the device-has-data event.
 */
extern "C"		UInt32	getUSBEventKindDataAvailable();
//getters for event type data
/*!
 @function getCDCEventClass
 @abstract Retrieves a value used to signify the class of events generated by the library.
 @result An integer value signifying the event class for library-generated events.
 @discussion This function may be called before CreateOPNInterface.
 
 An event type is made up of an event class and an event kind.  Event types are 
 essentially how events get matched to event handlers.  The event class returned by 
 this function is defined by the library, meaning that this function must be utilized 
 when installing and/or handling the insertion, removal, or device-has-data events.
 */
extern "C"		UInt32	getCDCEventClass();
/*!
 @function getCDCEventKindInsert
 @abstract Retrieves a value used to specify what kind of event, within a class of events, 
 a particular event is.  In this case, a library-generated device-insertion event.
 @result An integer value signifying the event kind for a library-generated insertion event.
 @discussion This function may be called before CreateOPNInterface.
 
 An event type is made up of an event class and an event kind.  Event types are 
 essentially how events get matched to event handlers.  The event kind returned by 
 this function is defined by the library, meaning that this function must be utilized 
 when installing and/or handling the insertion event.
 */
extern "C"		UInt32	getCDCEventKindInsert();
/*!
 @function getCDCEventKindRemove
 @abstract Retrieves a value used to specify what kind of event, within a class of events, 
 a particular event is.  In this case, a library-generated device-removal event.
 @result An integer value signifying the event kind for a library-generated removal event.
 @discussion This function may be called before CreateOPNInterface.
 
 An event type is made up of an event class and an event kind.  Event types are 
 essentially how events get matched to event handlers.  The event kind returned by 
 this function is defined by the library, meaning that this function must be utilized 
 when installing and/or handling the removal event.
 */
extern "C"		UInt32	getCDCEventKindRemove();
/*!
 @function getCDCEventKindDataAvailable
 @abstract Retrieves a value used to specify what kind of event, within a class of events, 
 a particular event is.  In this case, a library-generated device-has-data event.
 @result An integer value signifying the event kind for a library-generated device-has-data 
 event.
 @discussion This function may be called before CreateOPNInterface.
 
 An event type is made up of an event class and an event kind.  Event types are 
 essentially how events get matched to event handlers.  The event kind returned by 
 this function is defined by the library, meaning that this function must be utilized 
 when installing and/or handling the device-has-data event.
 */
extern "C"		UInt32	getCDCEventKindDataAvailable();
//polling functions
/*!
 @functiongroup Polling Functions
 */
/*!
	@function enablePolling
	@abstract Enable the generation of the device-has-data event when data is available in the 
		device.
	@param interface The OPNInterface opaque pointer returned by CreateOPNInterface().
	@result GENERAL_ERROR on error, or STATUS_OK on success.
	@discussion Calling this function will poll the device intermittently for whether or not
		it has data.  If it does, it will generate the device-has-data event, which must be
		handled by client code.
 */
extern "C"		SInt32	enablePolling(OPNInterface interface);
/*!
	@function disablePolling
	@abstract Disable the generation of the device-has-data event when data is available in the 
		device.
	@param interface The OPNInterface opaque pointer returned by CreateOPNInterface().
	@result GENERAL_ERROR on error, or STATUS_OK on success.
	@discussion Calling this function stop the generation of the device-has-data event.
 */
extern "C"		SInt32	disablePolling(OPNInterface interface);

//miscellaneous
/*!
@functiongroup Miscellaneous Functions
 */
/*!
	@function timeStamp2String
	@abstract Converts a 4-byte timestamp buffer into a formatted date/time string.
 	@param interface The OPNInterface opaque pointer returned by CreateOPNInterface().
	@param TimeString	A pointer to a buffer to hold the formatted date/time string.
	@param TimeStringLength	The size of the TimeString buffer.
	@param TimeStamp	A 4-byte buffer containing an RTC timestamp, such as the one returned 
		via getTimeCmd.
	@result A status code.  See the status code defines for the possible returned codes.
	@discussion Make sure the size of the TimeString buffer is big enough to fit any formatted 
		date/time string.  A size of 31 (NUL terminator included) ought to do.
 */
extern "C"		SInt32	timeStamp2String(OPNInterface interface, char* TimeString, UInt32 TimeStringLength, UInt8* TimeStamp);




#pragma GCC visibility pop

