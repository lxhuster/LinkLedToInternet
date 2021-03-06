/**
  @page ride7 RIDE7 Project Template
  
  @verbatim
 ******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
 * @file      readme.txt
 * @author    MCD Application Team
 * @version   V3.0.0
 * @date      04/06/2009
 * @brief     This sub-directory contains all the user-modifiable files 
 *            needed to create a new project linked with the STM32F10x  
 *            Standard Peripheral Library and working with RIDE7 software 
 *            toolchain (RIDE7 IDE:7.16.0000, RKitARM for RIDE7:1.16.0930)
 ********************************************************************************
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
 * AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
 * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
 * CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
 * INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *******************************************************************************
 @endverbatim
 
 @par Directory contents
 
 - project .rprj/.rapp: A pre-configured project file with the provided library 
                        structure that produces an executable image with RIDE7.
                
 - stm32f10x_flash_extsram.ld: This file is the RAISONANCE linker script used to 
                               place program code (readonly) in internal FLASH 
                               and data (readwrite, Stack and Heap)in external 
                               SRAM. 
                               You can customize this file to your need.
                           
 @par How to use it ?
 
 - Open the Project.rprj project.
 - In the configuration toolbar(Project->properties) select the project config:
     - STM3210B-EVAL: to configure the project for STM32 Medium-density devices
     - STM3210E-EVAL: to configure the project for STM32 High-density devices
 - Rebuild all files: Project->build project
 - Load project image: Debug->start(ctrl+D)
 - Run program: Debug->Run(ctrl+F9)  

@note
 - Low-density devices are STM32F101xx and STM32F103xx microcontrollers where
   the Flash memory density ranges between 16 and 32 Kbytes.
 - Medium-density devices are STM32F101xx and STM32F103xx microcontrollers where
   the Flash memory density ranges between 32 and 128 Kbytes.
 - High-density devices are STM32F101xx and STM32F103xx microcontrollers where
   the Flash memory density ranges between 256 and 512 Kbytes. 

 * <h3><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h3>
 */