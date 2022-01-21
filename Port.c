/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for Port Module.
 *
 * Author: Kareem Hassaan
 ******************************************************************************/

#include "Port.h"
#include "Dio_Regs.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

STATIC PortPin * PortPinInitCpy = NULL_PTR;
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;

/************************************************************************************
* Service Name: Port_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): ConfigPtr - Pointer to configuration set.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the Port Driver module.
************************************************************************************/
void Port_Init(const Port_ConfigType* ConfigPtr)
{
	uint8 * Port_Ptr_Dir = NULL_PTR;
	uint8 * Port_Ptr_Lev = NULL_PTR;
	uint8 PortPinsConfigurationIndex;
	uint8 PortNum;
	uint8 PinNum;
	uint8 PinMode;
	
	
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	if(NULL_PTR == ConfigPtr)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,PORT_E_PARAM_CONFIG);
	}
	else
#endif
	{
		PortPinInitCpy = ConfigPtr -> Pins;
		
		for(PortPinsConfigurationIndex=0;PortPinsConfigurationIndex<PortNumberOfPortPins;PortPinsConfigurationIndex++)
		{
			PortNum = ((PortPinInitCpy[PortPinsConfigurationIndex].PortPinId)-1)/(8);
			PinNum  = ((PortPinInitCpy[PortPinsConfigurationIndex].PortPinId)-1);
			PinMode = (PortPinInitCpy[PortPinsConfigurationIndex].PortPinInitialMode);
				
				switch(PortNum)
				{
					/* Point to the correct DDR & PORT register according to the PortPinId member  */
					case 0:	Port_Ptr_Dir = &DDRA_REG;
							Port_Ptr_Lev = &PORTA_REG;
						break;
					case 1:	Port_Ptr_Dir = &DDRB_REG;
							Port_Ptr_Lev = &PORTB_REG;
							PinNum = PinNum - (8);
						break;
					case 2:	Port_Ptr_Dir = &DDRC_REG;
							Port_Ptr_Lev = &PORTC_REG;
							PinNum = PinNum - (16);
						break;
					case 3:	Port_Ptr_Dir = &DDRD_REG;
							Port_Ptr_Lev = &PORTD_REG;
							PinNum = PinNum - (24);
						break;
				}
				
				/* Point to the correct Mode according to the PortPinInitialMode member */
				switch(PinMode)
				{
					case PORT_PIN_MODE_DIO:	
							
							/*Setting the Pin Direction according to the PortPinDirection member*/
							if(PORT_PIN_OUT == PortPinInitCpy[PortPinsConfigurationIndex].PortPinDirection)
							{
								SET_BIT(*Port_Ptr_Dir,PinNum);
							}
							else if(PORT_PIN_IN == PortPinInitCpy[PortPinsConfigurationIndex].PortPinDirection)
							{
								CLEAR_BIT(*Port_Ptr_Dir,PinNum);
							}
							
				            /*Setting the Pin Level Value according to the PortPinLevelValue member*/
							if (PORT_PIN_LEVEL_HIGH == PortPinInitCpy[PortPinsConfigurationIndex].PortPinLevelValue)
							{
								SET_BIT(*Port_Ptr_Lev,PinNum);
							}
							else if(PORT_PIN_LEVEL_LOW == PortPinInitCpy[PortPinsConfigurationIndex].PortPinLevelValue)
							{
								CLEAR_BIT(*Port_Ptr_Lev,PinNum);
							}
								break;
					case PORT_PIN_MODE_ADC:	
								break;
					case PORT_PIN_MODE_CAN:	
								break;
					case PORT_PIN_MODE_DIO_GPT:	
								break;
					case PORT_PIN_MODE_DIO_WDG:	
								break;
					case PORT_PIN_MODE_FLEXRAY:	
								break;
					case PORT_PIN_MODE_ICU:	
								break;
					case PORT_PIN_MODE_LIN:	
								break;
					case PORT_PIN_MODE_MEM:	
								break;
					case PORT_PIN_MODE_PWM:	
								break;
					case PORT_PIN_MODE_SPI:	
								break;
				}
				
				if(TRUE == PortPinInitCpy[PortPinsConfigurationIndex].ActivationOfInternalPull_Up)
				{
						CLEAR_BIT(*Port_Ptr_Dir,PinNum);
						SET_BIT(*Port_Ptr_Lev,PinNum);
				}
				else
				{
					
				}
			
		}	
		
		Port_Status = PORT_INITIALIZED;
		
	}		


	
}
/************************************************************************************
* Service Name: Port_SetPinDirection
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin - Port Pin ID number.
				   Direction - Port Pin Direction.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction.
************************************************************************************/
#if(PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{
	uint8 * Port_Ptr_Dir = NULL_PTR;
	uint8 PortDirection;
	uint8 PortNum;
	uint8 PinNum;

	PortDirection = Direction;
	PortNum = (Pin-1)/8;
	PinNum  = (Pin-1);
	
#if(PORT_DEV_ERROR_DETECT == STD_ON)
	if(Port_Status == PORT_NOT_INITIALIZED)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID,PORT_E_UNINIT);
	}
	else
	{
		/*MISRA*/
	}
	
	if(PinNum > PortNumberOfPortPins)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID,PORT_E_PARAM_PIN);
	}	
	else
	{
		/*MISRA*/
	}
	
	if(PortPinInitCpy[PinNum].PortPinDirectionChangeable == FALSE)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID,PORT_E_DIRECTION_UNCHANGEABLE);
	}
	else	
#endif	
	{		
		switch(PortNum)
			
		{
			/* Point to the correct DDR & PORT register according to the PortPinId member  */
			case 0:	Port_Ptr_Dir = &DDRA_REG;
				break;
			case 1:	Port_Ptr_Dir = &DDRB_REG;
					PinNum = PinNum - (8);
				break;
			case 2:	Port_Ptr_Dir = &DDRC_REG;
					PinNum = PinNum - (16);
				break;
			case 3:	Port_Ptr_Dir = &DDRD_REG;
					PinNum = PinNum - (24);
				break;
			}
				
		/*Setting the Pin Direction according to the PortPinDirection member*/
		if(PORT_PIN_OUT == PortDirection)
		{
			SET_BIT(*Port_Ptr_Dir,PinNum);
		}
		else if(PORT_PIN_IN == PortDirection)
		{
			CLEAR_BIT(*Port_Ptr_Dir,PinNum);
		}
	}
}
#endif

/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction.
************************************************************************************/
void Port_RefreshPortDirection(void)
{
	uint8 * Port_Ptr_Dir = NULL_PTR;
	uint8 PortPinsRefreshIndex;
	uint8 PortNum;
	uint8 PinNum;
	
	if(Port_Status == PORT_INITIALIZED)
	{
		for(PortPinsRefreshIndex=0;PortPinsRefreshIndex<PortNumberOfPortPins;PortPinsRefreshIndex++)
		{
			PortNum = ((PortPinInitCpy[PortPinsRefreshIndex].PortPinId)-1)/(8);
			PinNum  = ((PortPinInitCpy[PortPinsRefreshIndex].PortPinId)-1);
		
			if(PortPinInitCpy[PortPinsRefreshIndex].PortPinDirectionChangeable == FALSE)
			{
				switch(PortNum)
					{
						/* Point to the correct DDR & PORT register according to the PortPinId member  */
						case 0:	Port_Ptr_Dir = &DDRA_REG;
							break;
						case 1:	Port_Ptr_Dir = &DDRB_REG;
								PinNum = PinNum - (8);
							break;
						case 2:	Port_Ptr_Dir = &DDRC_REG;
								PinNum = PinNum - (16);
							break;
						case 3:	Port_Ptr_Dir = &DDRD_REG;
								PinNum = PinNum - (24);
							break;
					}
				/*Setting the Pin Direction according to the PortPinDirection member*/
				if(PORT_PIN_OUT == PortPinInitCpy[PortPinsRefreshIndex].PortPinDirection)
				{
					SET_BIT(*Port_Ptr_Dir,PinNum);
				}
				else if(PORT_PIN_IN == PortPinInitCpy[PortPinsRefreshIndex].PortPinDirection)
				{
					CLEAR_BIT(*Port_Ptr_Dir,PinNum);
				}	
			
			}
			else
			{
				/*MISRA*/
			}
		}
	}	
#if(PORT_DEV_ERROR_DETECT == STD_ON)	
	else
	{
		/*Port_Status = PORT_NOT_INITIALIZED*/
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIRECTION_SID,PORT_E_UNINIT);
	}
#endif	
}

/************************************************************************************
* Service Name: Port_GetVersionInfo
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): ConfigPtr - Pointer to configuration set..
* Parameters (inout): None
* Parameters (out): versioninfo - Pointer to where to store the version information of this module.
* Return value: None
* Description: Returns the version information of this module.
************************************************************************************/
#if(PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	
	if(Port_Status == PORT_NOT_INITIALIZED)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID,PORT_E_UNINIT);
	}
	else
	{
		/*MISRA*/
	}
	
	if(NULL_PTR == versioninfo)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID,PORT_E_PARAM_POINTER);
	}
	else
		
#endif
	{
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16)PORT_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
	}
}
#endif

/************************************************************************************
* Service Name: Port_SetPinMode
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin - Port Pin ID number.
				   Mode - New Port Pin mode to be set on port pin.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode.
************************************************************************************/
#if(PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{
	uint8 * Port_Ptr_Mode = NULL_PTR;
	uint8 PortNum;
	uint8 PinMode;
	uint8 PinNum;
	
	PortNum = (Pin-1)/8;
	PinMode = Mode;
	PinNum =  (Pin-1);
	
#if(PORT_DEV_ERROR_DETECT == STD_ON)	
	if(Port_Status == PORT_NOT_INITIALIZED)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,PORT_E_UNINIT);
	}
	else
	{
		/*MISRA*/
	}
	
	if(PinNum > PortNumberOfPortPins)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN);
	}
	else
	{
		/*MISRA*/
	}
	
	if(PortPinInitCpy[PinNum].PortPinModeChangeable == FALSE)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,PORT_E_MODE_UNCHANGEABLE);
	}	
	else	
#endif
	{
		switch(PortNum)
		{
			
			case 0:Port_Ptr_Mode = &PORTA_REG;
				break;
			case 1:	Port_Ptr_Mode = &PORTB_REG;
					PinNum = PinNum - (8);
				break;
			case 2:	Port_Ptr_Mode = &PORTC_REG;
					PinNum = PinNum - (16);
				break;
			case 3:	Port_Ptr_Mode = &PORTD_REG;
					PinNum = PinNum - (24);
				break;
		}
				
				switch(PinMode)
				{
					case PORT_PIN_MODE_DIO:	
								break;
					case PORT_PIN_MODE_ADC:	
								break;
					case PORT_PIN_MODE_CAN:	
								break;
					case PORT_PIN_MODE_DIO_GPT:	
								break;
					case PORT_PIN_MODE_DIO_WDG:	
								break;
					case PORT_PIN_MODE_FLEXRAY:	
								break;
					case PORT_PIN_MODE_ICU:	
								break;
					case PORT_PIN_MODE_LIN:	
								break;
					case PORT_PIN_MODE_MEM:	
								break;
					case PORT_PIN_MODE_PWM:	
								break;
					case PORT_PIN_MODE_SPI:	
								break;
#if(PORT_DEV_ERROR_DETECT == STD_ON)						
					default: Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,PORT_E_PARAM_INVALID_MODE);	
								break;
#endif				
				}
	}				
}
#endif
