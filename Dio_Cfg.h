 /******************************************************************************
 *
 * Module: Dio
 *
 * File Name: Dio_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for esp32 Microcontroller - Dio Driver
 *
 * Author: Mohammed Alaa
 ******************************************************************************/

#ifndef DIO_CFG_H
#define DIO_CFG_H

/*
 * Module Version 1.0.0
 */
#define DIO_CFG_SW_MAJOR_VERSION              (1U)
#define DIO_CFG_SW_MINOR_VERSION              (0U)
#define DIO_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define DIO_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define DIO_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define DIO_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define DIO_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define DIO_VERSION_INFO_API                (STD_ON)

/* Pre-compile option for presence of Dio_FlipChannel API */
#define DIO_FLIP_CHANNEL_API                (STD_ON)

#define DIO_PINS_MAX_NUM                     (40U)
/* Number of the configured Dio Channels */
#define DIO_CONFIGURED_CHANNLES              (2U)

/* Channel Index in the array of structures in Dio_PBcfg.c */
#define DioConf_LED1_CHANNEL_ID_INDEX        (uint8)0x00
#define DioConf_SW1_CHANNEL_ID_INDEX         (uint8)0x01

/*Pin number*/
#define DioConf_LD1_PIN_NUM                        2U
#define DioConf_SW1_PIN_NUM                        39U
#endif /* DIO_CFG_H */
