/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for Port Module.
 *
 * Author: Kareem Hassaan
 ******************************************************************************/

#ifndef PORT_CFG_H
#define PORT_CFG_H

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)


/**************************************************************************************************
Name:                                    PortContainer

Description:  					Container collecting the PortPins.											
**************************************************************************************************/
/**************************************************************************************************
Name:                                    PortNumberOfPortPins

Type:                                    EcucIntegerParamDef

Description: 			The number of specified PortPins in this PortContainer.								
**************************************************************************************************/
#define PortNumberOfPortPins                (32U)
/**************************************************************************************************
Name:                                    PortGeneral

Description:  			Module wide configuration parameters of the PORT driver.											
**************************************************************************************************/
/**************************************************************************************************
Name:                                    PortDevErrorDetect

Type:                                    EcucBooleanParamDef

Description: 			Switches the Development Error Detection and Notification on or off. 
									TRUE: Enabled. FALSE: Disabled.								
**************************************************************************************************/
#define DIO_DEV_ERROR_DETECT                (STD_ON)
/**************************************************************************************************
Name:                                    PortSetPinDirectionApi

Type:                                    EcucBooleanParamDef

Description: 			Pre-processor switch to enable / disable the use of the function
						Port_SetPinDirection(). 
						TRUE: Enabled - Function Port_SetPinDirection() is available. 
						FALSE: Disabled - Function Port_SetPinDirection() is not available.								
**************************************************************************************************/
#define PORT_SET_PIN_DIRECTION_API          (STD_ON)
/**************************************************************************************************
Name:                                    PortSetPinModeApi

Type:                                    EcucBooleanParamDef

Description: 			Pre-processor switch to enable / disable the use of the function 
						Port_SetPinMode(). 
						TRUE: Enabled - Function Port_SetPinMode() is available. 
						FALSE: Disabled - Function Port_SetPinMode() is not available.								
**************************************************************************************************/
#define PORT_SET_PIN_MODE_API                (STD_ON)
/**************************************************************************************************
Name:                                    PortVersionInfoApi

Type:                                    EcucBooleanParamDef

Description: 			Pre-processor switch to enable / disable the API to read out the modules version information.
						TRUE: Version info API enabled.
						FALSE: Version info API disabled.								
**************************************************************************************************/
#define PORT_VERSION_INFO_API                (STD_ON)

/* Port Configured Pin ID's */
#define PortConf_Pin01             (Port_PinType)1  /* Pin 0 in PORTA */
#define PortConf_Pin02             (Port_PinType)2  /* Pin 1 in PORTA */
#define PortConf_Pin03             (Port_PinType)3  /* Pin 2 in PORTA */
#define PortConf_Pin04             (Port_PinType)4  /* Pin 3 in PORTA */
#define PortConf_Pin05             (Port_PinType)5  /* Pin 4 in PORTA */
#define PortConf_Pin06             (Port_PinType)6  /* Pin 5 in PORTA */
#define PortConf_Pin07             (Port_PinType)7  /* Pin 6 in PORTA */
#define PortConf_Pin08             (Port_PinType)8  /* Pin 7 in PORTA */

#define PortConf_Pin09             (Port_PinType)9  /* Pin 0 in PORTB */
#define PortConf_Pin10             (Port_PinType)10 /* Pin 1 in PORTB */
#define PortConf_Pin11             (Port_PinType)11 /* Pin 2 in PORTB */
#define PortConf_Pin12             (Port_PinType)12 /* Pin 3 in PORTB */
#define PortConf_Pin13             (Port_PinType)13 /* Pin 4 in PORTB */
#define PortConf_Pin14             (Port_PinType)14 /* Pin 5 in PORTB */
#define PortConf_Pin15             (Port_PinType)15 /* Pin 6 in PORTB */
#define PortConf_Pin16             (Port_PinType)16 /* Pin 7 in PORTB */

#define PortConf_Pin17             (Port_PinType)17 /* Pin 0 in PORTC */
#define PortConf_Pin18             (Port_PinType)18 /* Pin 1 in PORTC */
#define PortConf_Pin19             (Port_PinType)19 /* Pin 2 in PORTC */
#define PortConf_Pin20             (Port_PinType)20 /* Pin 3 in PORTC */
#define PortConf_Pin21             (Port_PinType)21 /* Pin 4 in PORTC */
#define PortConf_Pin22             (Port_PinType)22 /* Pin 5 in PORTC */
#define PortConf_Pin23             (Port_PinType)23 /* Pin 6 in PORTC */
#define PortConf_Pin24             (Port_PinType)24 /* Pin 7 in PORTC */

#define PortConf_Pin25             (Port_PinType)25 /* Pin 0 in PORTD */
#define PortConf_Pin26             (Port_PinType)26 /* Pin 1 in PORTD */
#define PortConf_Pin27             (Port_PinType)27 /* Pin 2 in PORTD */
#define PortConf_Pin28             (Port_PinType)28 /* Pin 3 in PORTD */
#define PortConf_Pin29             (Port_PinType)29 /* Pin 4 in PORTD */
#define PortConf_Pin30             (Port_PinType)30 /* Pin 5 in PORTD */
#define PortConf_Pin31             (Port_PinType)31 /* Pin 6 in PORTD */
#define PortConf_Pin32             (Port_PinType)32 /* Pin 7 in PORTD */

#endif /* PORT_CFG_H */
