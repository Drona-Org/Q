/*********************************************************************************

Copyright (c) Microsoft Corporation

File Name:

    SmfPublic.h

Abstract:
    This header file contains declarations of all the public functions which can be 
	used inside driver code.

Environment:

    Kernel mode only.		

***********************************************************************************/
#pragma once

#include "SmfPublicTypes.h"

/*********************************************************************************

		Macro Functions For Enqueue

*********************************************************************************/

//
// Macro to enqueue an Event with Payload
//
#define SMF_ENQUEUEEVENT_WITH_PAYLOAD(Machine, EventIndex, Payload, UseWorkItem) SmfEnqueueEvent(Machine, EventIndex, Payload, UseWorkItem)

//
//Macro to enqueue an Event without Payload
//
#define SMF_ENQUEUEEVENT(Machine, EventIndex, UseWorkItem) SmfEnqueueEvent(Machine, EventIndex, 0, UseWorkItem)


/*********************************************************************************

		Functions - Machine Creation

*********************************************************************************/
//
// Create the attributes object, returns pointer to the allocated attribute structure
// Attribute structure created by the driver should be freed by the driver itself
//
PSMF_MACHINE_ATTRIBUTES 
SmfCreateAttributes( 
__in PSMF_DRIVERDECL			Driver,
__in SMF_MACHINEDECL_INDEX		InstanceOf
);

#ifdef KERNEL_MODE
//
// Initializes StateMachine attributes used for creating a machine of type InstanceOf
//
VOID 
SmfInitAttributes(
__inout PSMF_MACHINE_ATTRIBUTES Attributes, 
__in PDEVICE_OBJECT				PDeviceObj, 
__in PSMF_DRIVERDECL			Driver,
__in SMF_MACHINEDECL_INDEX		InstanceOf,
__in PVOID						PFrgnMem
);
#else
VOID 
SmfInitAttributes(
__inout PSMF_MACHINE_ATTRIBUTES Attributes, 
__in PSMF_DRIVERDECL			Driver,
__in SMF_MACHINEDECL_INDEX		InstanceOf,
__in PVOID						PFrgnMem
);
#endif
//
//Creates a new State Machine of using Machine_Attributes and initializes PSmHandle to new Machine handle
//
NTSTATUS 
SmfCreate(
__in PSMF_MACHINE_ATTRIBUTES	InitAttributes, 
__out PSMF_MACHINE_HANDLE		PSmHandle
);

//
// To initialize the local variables of statemachines, done by initializing Machine_Attributes which is 
// used while creating the statemachine
//
VOID SmfInitVar(
__in PSMF_DRIVERDECL			Driver,
__inout PSMF_MACHINE_ATTRIBUTES	InitAttributes, 
__in SMF_VARDECL_INDEX			VarIndex, 
__in ULONG_PTR					Value
);


/*********************************************************************************

		Functions - Life Time Management of the State-Machine (Reference Counting)

*********************************************************************************/
//
// To Acquire Reference on a state machine (Reference count is incremented by 1)
//
VOID 
SmfReference(
__in SMF_MACHINE_HANDLE			Machine
);

//
// To Release Reference on a state machine (remove statemachine if reference count is 0)
//
VOID SmfDereference(
__in SMF_MACHINE_HANDLE			Machine
);


/*********************************************************************************

		Functions - Machine Interaction

*********************************************************************************/
//
// Enqueue Event on to the State Machine
//

VOID 
SmfEnqueueEvent(
__in SMF_MACHINE_HANDLE			Machine, 
__in SMF_EVENTDECL_INDEX		EventIndex, 
__in PSMF_PACKED_VALUE			Arg,
__in BOOLEAN					UseWorkItem
); 

//
// Get Foreign Memory Context for the State Machine
//
PSMF_EXCONTEXT
SmfGetForeignContext(
__in SMF_MACHINE_HANDLE SmHandle
);