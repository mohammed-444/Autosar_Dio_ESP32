 /******************************************************************************
 *
 * Module: Dio
 *
 * File Name: Dio.c
 *
 * Description: Source file for esp32 Microcontroller - Dio Driver
 *
 * Author: Mohammed Alaa
 ******************************************************************************/

#include "Dio.h"
#include "Dio_MemMap.h"

#if (DIO_DEV_ERROR_DETECT == STD_ON)

#include "../../utilities/Det.h"
/* AUTOSAR Version checking between Det and Dio Modules */
#if ((DET_AR_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

STATIC const Dio_ConfigChannel * Dio_PortChannels = NULL_PTR;
STATIC uint8 Dio_Status = DIO_NOT_INITIALIZED;

/************************************************************************************
* Service Name: Dio_Init
* Service ID[hex]: 0x10
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Dio module.
************************************************************************************/
void Dio_Init(const Dio_ConfigType * ConfigPtr)
{
#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR == ConfigPtr)
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_INIT_SID,
		     DIO_E_PARAM_CONFIG);
	}
	else
#endif
	{
		/*
		 * Set the module state to initialized and point to the PB configuration structure using a global pointer.
		 * This global pointer is global to be used by other functions to read the PB configuration structures
		 */
		Dio_Status       = DIO_INITIALIZED;
		Dio_PortChannels = ConfigPtr->Channels; /* address of the first Channels structure --> Channels[0] */
	}
}

/************************************************************************************
* Service Name: Dio_WriteChannel
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - ID of DIO channel.
*                  Level - Value to be written.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set a level of a channel.
************************************************************************************/
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{

	boolean error = FALSE;

#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (DIO_NOT_INITIALIZED == Dio_Status)
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
				DIO_WRITE_CHANNEL_SID, DIO_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
	/* Check if the used channel is within the valid range */
	if (DIO_CONFIGURED_CHANNLES <= ChannelId)
	{

		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
				DIO_WRITE_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
#endif

	/* In-case there are no errors */
	if(FALSE == error)
	{

		if(Level == STD_HIGH)
		{
			/************************************************************************************
			* Parameters (reg): the register as type uint32 (GPIO_OUT_REG)
			* Parameters (start_position): the bit number to write in pin number.
			* Return value: None
			* Description: set the bit selected to 1.
			************************************************************************************/

			if(Dio_PortChannels[ChannelId].Pin_Num<REG_SIZE)
			{
				SET_BIT(REG(GPIO_OUT_REG),(Dio_PortChannels[ChannelId].Pin_Num));
			}
			else if((Dio_PortChannels[ChannelId].Pin_Num)<DIO_PINS_MAX_NUM)
			{
				SET_BIT(REG(GPIO_OUT1_REG),(Dio_PortChannels[ChannelId].Pin_Num)-REG_SIZE);
			}
			else
			{
				/*Do nothing*/
			}
		}
		else if(Level == STD_LOW)
		{
			/************************************************************************************
			* Parameters (reg): the register as type uint32 (GPIO_OUT_REG)
			* Parameters (start_position): the bit number to write in pin number.
			* Return value: None
			* Description: set the bit selected to 0.
			************************************************************************************/

			if(Dio_PortChannels[ChannelId].Pin_Num<REG_SIZE)
			{
				CLEAR_BIT(REG(GPIO_OUT_REG),(Dio_PortChannels[ChannelId].Pin_Num));
			}
			else if((Dio_PortChannels[ChannelId].Pin_Num)<DIO_PINS_MAX_NUM)
			{
				CLEAR_BIT(REG(GPIO_OUT1_REG),(Dio_PortChannels[ChannelId].Pin_Num)-REG_SIZE);
			}
			else
			{
				/*Do nothing*/
			}
		}
	}
	else
	{
		/* No Action Required */
	}

}

/************************************************************************************
* Service Name: Dio_ReadChannel
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - ID of DIO channel.
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_LevelType
* Description: Function to return the value of the specified DIO channel.
************************************************************************************/
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
	Dio_LevelType output = STD_LOW;
	boolean error = FALSE;

#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (DIO_NOT_INITIALIZED == Dio_Status)
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
				DIO_READ_CHANNEL_SID, DIO_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
	/* Check if the used channel is within the valid range */
	if (DIO_CONFIGURED_CHANNLES <= ChannelId)
	{

		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
				DIO_READ_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
#endif

	/* In-case there are no errors */
	if(FALSE == error)
	{

		if(Dio_PortChannels[ChannelId].Pin_Num<REG_SIZE)
		{
			output = READ_BIT(REG(GPIO_IN_REG),(Dio_PortChannels[ChannelId].Pin_Num));
		}
		else if((Dio_PortChannels[ChannelId].Pin_Num)<DIO_PINS_MAX_NUM)
		{
			output = READ_BIT(REG(GPIO_IN1_REG),(Dio_PortChannels[ChannelId].Pin_Num)-REG_SIZE);
		}
		else
		{
			/*Do nothing*/
		}

	}
	else
	{
		/* No Action Required */
	}
        return output;
}

/************************************************************************************
* Service Name: Dio_GetVersionInfo
* Service ID[hex]: 0x12
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): VersionInfo - Pointer to where to store the version information of this module.
* Return value: None
* Description: Function to get the version information of this module.
************************************************************************************/
#if (DIO_VERSION_INFO_API == STD_ON)
void Dio_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if(NULL_PTR == versioninfo)
	{
		/* Report to DET  */
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
				DIO_GET_VERSION_INFO_SID, DIO_E_PARAM_POINTER);
	}
	else
#endif /* (DIO_DEV_ERROR_DETECT == STD_ON) */
	{
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)DIO_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16)DIO_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)DIO_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)DIO_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)DIO_SW_PATCH_VERSION;
	}
}
#endif

/************************************************************************************
* Service Name: Dio_FlipChannel
* Service ID[hex]: 0x11
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - ID of DIO channel.
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_LevelType
* Description: Function to flip the level of a channel and return the level of the channel after flip.
************************************************************************************/
#if (DIO_FLIP_CHANNEL_API == STD_ON)
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
	Dio_LevelType output = STD_LOW;
	boolean error = FALSE;

#if (DIO_DEV_ERROR_DETECT == STD_ON)
/* Check if the Driver is initialized before using this function */
if (DIO_NOT_INITIALIZED == Dio_Status)
{
	Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
			DIO_WRITE_CHANNEL_SID, DIO_E_UNINIT);
	error = TRUE;
}
else
{
	/* No Action Required */
}
/* Check if the used channel is within the valid range */
if (DIO_CONFIGURED_CHANNLES <= ChannelId)
{

	Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
			DIO_WRITE_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
	error = TRUE;
}
else
{
	/* No Action Required */
}
#endif

/* In-case there are no errors */
if(FALSE == error)
{

	if(BIT_IS_CLEAR(REG(GPIO_OUT_REG),Dio_PortChannels[ChannelId].Pin_Num))
	{
		/************************************************************************************
		* Parameters (reg): the register as type uint32 (GPIO_OUT_REG)
		* Parameters (start_position): the bit number to write in pin number.
		* Return value: None
		* Description: set the bit selected to 1.
		************************************************************************************/

		if(Dio_PortChannels[ChannelId].Pin_Num<REG_SIZE)
		{
			SET_BIT(REG(GPIO_OUT_REG),(Dio_PortChannels[ChannelId].Pin_Num));
			output = STD_HIGH;
		}
		else if((Dio_PortChannels[ChannelId].Pin_Num)<DIO_PINS_MAX_NUM)
		{
			SET_BIT(REG(GPIO_OUT1_REG),(Dio_PortChannels[ChannelId].Pin_Num)-REG_SIZE);
			output = STD_HIGH;
		}
		else
		{
			/*Do nothing*/
		}
	}
	else if(BIT_IS_SET(REG(GPIO_OUT_REG),Dio_PortChannels[ChannelId].Pin_Num))
	{
		/************************************************************************************
		* Parameters (reg): the register as type uint32 (GPIO_OUT_REG)
		* Parameters (start_position): the bit number to write in pin number.
		* Return value: None
		* Description: set the bit selected to 0.
		************************************************************************************/

		if(Dio_PortChannels[ChannelId].Pin_Num<REG_SIZE)
		{
			CLEAR_BIT(REG(GPIO_OUT_REG),(Dio_PortChannels[ChannelId].Pin_Num));
			output = STD_LOW;

		}
		else if((Dio_PortChannels[ChannelId].Pin_Num)<DIO_PINS_MAX_NUM)
		{
			CLEAR_BIT(REG(GPIO_OUT1_REG),(Dio_PortChannels[ChannelId].Pin_Num)-REG_SIZE);
			output = STD_LOW;
		}
		else
		{
			/*Do nothing*/
		}
	}
}
else
{
	/* No Action Required */
}
	return output;
}
#endif

