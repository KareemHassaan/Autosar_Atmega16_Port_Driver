 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for Port Module.
 *
 * Author: Kareem Hassaan
 ******************************************************************************/
#ifndef PORT_H
#define PORT_H

/* Id for the company in the AUTOSAR */
#define PORT_VENDOR_ID    (1000U)

/* Dio Module Id */
#define PORT_MODULE_ID    (124U)

/* Dio Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR  version checking between Std types and port modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((Port_CFG_AR_RELEASE_MAJOR_VERSION != Port_AR_RELEASE_MAJOR_VERSION)\
 ||  (Port_CFG_AR_RELEASE_MINOR_VERSION != Port_AR_RELEASE_MINOR_VERSION)\
 ||  (Port_CFG_AR_RELEASE_PATCH_VERSION != Port_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((Port_CFG_SW_MAJOR_VERSION != Port_SW_MAJOR_VERSION)\
 ||  (Port_CFG_SW_MINOR_VERSION != Port_SW_MINOR_VERSION)\
 ||  (Port_CFG_SW_PATCH_VERSION != Port_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
******************************************************************************/
/* Service ID for Port Init */
#define PORT_INIT_SID                  							(uint8)0x00

/* Service ID for Port Set Pin Direction */
#define PORT_SET_PIN_DIRECTION_SID      			 			(uint8)0x01

/* Service ID for Port Refresh Port Direction */
#define PORT_REFRESH_PORT_DIRECTION_SID      					(uint8)0x02

/* Service ID for Port Get Version Info */
#define PORT_GET_VERSION_INFO_SID                  				(uint8)0x03

/*Service ID for Port Set Pin Mode */
#define PORT_SET_PIN_MODE_SID                          			(uint8)0x04

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
 /*DET code to report Invalid Port Pin ID requested */
 #define PORT_E_PARAM_PIN  										(uint8)0x0A
 
 /*DET code to report Port Pin not configured as changeable */
 #define PORT_E_DIRECTION_UNCHANGEABLE  						(uint8)0x0B
 
 /*DET code to report API Port_Init service called with wrong parameter */
 #define PORT_E_PARAM_CONFIG  									(uint8)0x0C
 
 /*DET code to report API Port_SetPinMode service called when mode is unchangeable */
 #define PORT_E_PARAM_INVALID_MODE  							(uint8)0x0D
 
 /*DET code to report API Port_SetPinMode service called when mode is unchangeable */
 #define PORT_E_MODE_UNCHANGEABLE   							(uint8)0x0E
 
 /*DET code to report API service called without module initialization */
 #define PORT_E_UNINIT  										(uint8)0x0F
 
 /*DET code to report APIs called with a Null Pointer */
 #define PORT_E_PARAM_POINTER									(uint8)0x10
 
/*******************************************************************************
*                              Module Data Types                              *
*******************************************************************************/
/* Type definition for Port_PinType used by the Port APIs */
typedef uint8 Port_PinType;

/* Type definition for Port_PinType used by the Port APIs */
typedef uint8 Port_PinModeType;

typedef enum 
{	
	/* Sets port pin as input */
	PORT_PIN_IN,
	/* Sets port pin as output */
	PORT_PIN_OUT
	
}Port_PinDirectionType;

typedef enum 
{	
	/* Port Pin level is High */
	PORT_PIN_LEVEL_HIGH,
	/* Port Pin level is LOW */
	PORT_PIN_LEVEL_LOW
	
}Port_PinLevelType;

typedef enum 
{	/*Port Pin used by ADC*/
	PORT_PIN_MODE_ADC,
	/*Port Pin used for CAN*/
	PORT_PIN_MODE_CAN,
	/*Port Pin configured for DIO. It shall be used under control of the DIO driver.*/
	PORT_PIN_MODE_DIO,
	/*Port Pin configured for DIO. It shall be used under control of the general purpose timer driver.*/
	PORT_PIN_MODE_DIO_GPT,
	/*Port Pin configured for DIO. It shall be used under control of the watchdog driver.*/
	PORT_PIN_MODE_DIO_WDG,
	/*Port Pin used for FlexRay*/
	PORT_PIN_MODE_FLEXRAY,
	/*Port Pin used by ICU*/
	PORT_PIN_MODE_ICU,
	/*Port Pin used for LIN*/
	PORT_PIN_MODE_LIN,
	/*Port Pin used for external memory under control of a memory driver.*/
	PORT_PIN_MODE_MEM,
	/*Port Pin used by PWM*/
	PORT_PIN_MODE_PWM,
	/*Port Pin used by SPI*/
	PORT_PIN_MODE_SPI
}Mode;

typedef struct
{
	Port_PinType 			PortPinId;
	Port_PinModeType 		PortPinInitialMode;
	Port_PinModeType  	    PortPinMode;
	Port_PinDirectionType   PortPinDirection;
	Port_PinLevelType 		PortPinLevelValue;
	boolean 				PortPinDirectionChangeable;
	boolean					PortPinModeChangeable;
	boolean					ActivationOfInternalPull_Up;
	
}PortPin;

typedef struct
{
	PortPin Pins[PortNumberOfPortPins];
	
} Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
 
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
void Port_Init(const Port_ConfigType* ConfigPtr);
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
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);
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
void Port_RefreshPortDirection(void);
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
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo);
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
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);
#endif
 
 /*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Dio and other modules */
extern const Port_ConfigType Port_PinsConfiguration;

#endif /* PORT_H */
 
 














 
 
 
 
 
 
