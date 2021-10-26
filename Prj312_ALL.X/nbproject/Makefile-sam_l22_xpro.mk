#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-sam_l22_xpro.mk)" "nbproject/Makefile-local-sam_l22_xpro.mk"
include nbproject/Makefile-local-sam_l22_xpro.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=sam_l22_xpro
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Prj312_ALL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Prj312_ALL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/config/sam_l22_xpro/git/LTC2944.c ../src/config/sam_l22_xpro/git/comm.c ../src/config/sam_l22_xpro/git/eeprom.c ../src/config/sam_l22_xpro/git/global.c ../src/config/sam_l22_xpro/git/gpio.c ../src/config/sam_l22_xpro/git/lm75.c ../src/config/sam_l22_xpro/git/mgc3130.c ../src/config/sam_l22_xpro/git/test.c ../src/config/sam_l22_xpro/git/time.c ../src/config/sam_l22_xpro/git/tm_event.c ../src/config/sam_l22_xpro/git/uart_M4.c ../src/config/sam_l22_xpro/git/g_stk8ba53.c ../src/config/sam_l22_xpro/git/PreShooting.c ../src/config/sam_l22_xpro/peripheral/adc/plib_adc.c ../src/config/sam_l22_xpro/peripheral/clock/plib_clock.c ../src/config/sam_l22_xpro/peripheral/eic/plib_eic.c ../src/config/sam_l22_xpro/peripheral/evsys/plib_evsys.c ../src/config/sam_l22_xpro/peripheral/nvic/plib_nvic.c ../src/config/sam_l22_xpro/peripheral/nvmctrl/plib_nvmctrl.c ../src/config/sam_l22_xpro/peripheral/pm/plib_pm.c ../src/config/sam_l22_xpro/peripheral/port/plib_port.c ../src/config/sam_l22_xpro/peripheral/sercom0/uart/sercom0_uart.c ../src/config/sam_l22_xpro/peripheral/sercom1/uart/sercom1_uart.c ../src/config/sam_l22_xpro/peripheral/sercom2/uart/sercom2_uart.c ../src/config/sam_l22_xpro/peripheral/sercom3/uart/sercom3_uart.c ../src/config/sam_l22_xpro/peripheral/sercom4/uart/sercom4_uart.c ../src/config/sam_l22_xpro/peripheral/sercom5/i2cm/sercom5_i2cm.c ../src/config/sam_l22_xpro/peripheral/systick/plib_systick.c ../src/config/sam_l22_xpro/stdio/xc32_monitor.c ../src/config/sam_l22_xpro/initialization.c ../src/config/sam_l22_xpro/interrupts.c ../src/config/sam_l22_xpro/exceptions.c ../src/config/sam_l22_xpro/startup_xc32.c ../src/config/sam_l22_xpro/libc_syscalls.c ../src/main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1847749054/LTC2944.o ${OBJECTDIR}/_ext/1847749054/comm.o ${OBJECTDIR}/_ext/1847749054/eeprom.o ${OBJECTDIR}/_ext/1847749054/global.o ${OBJECTDIR}/_ext/1847749054/gpio.o ${OBJECTDIR}/_ext/1847749054/lm75.o ${OBJECTDIR}/_ext/1847749054/mgc3130.o ${OBJECTDIR}/_ext/1847749054/test.o ${OBJECTDIR}/_ext/1847749054/time.o ${OBJECTDIR}/_ext/1847749054/tm_event.o ${OBJECTDIR}/_ext/1847749054/uart_M4.o ${OBJECTDIR}/_ext/1847749054/g_stk8ba53.o ${OBJECTDIR}/_ext/1847749054/PreShooting.o ${OBJECTDIR}/_ext/431015903/plib_adc.o ${OBJECTDIR}/_ext/1887322289/plib_clock.o ${OBJECTDIR}/_ext/431011904/plib_eic.o ${OBJECTDIR}/_ext/1885172803/plib_evsys.o ${OBJECTDIR}/_ext/476186239/plib_nvic.o ${OBJECTDIR}/_ext/216541841/plib_nvmctrl.o ${OBJECTDIR}/_ext/13903268/plib_pm.o ${OBJECTDIR}/_ext/476133088/plib_port.o ${OBJECTDIR}/_ext/62028211/sercom0_uart.o ${OBJECTDIR}/_ext/33399060/sercom1_uart.o ${OBJECTDIR}/_ext/4769909/sercom2_uart.o ${OBJECTDIR}/_ext/23859242/sercom3_uart.o ${OBJECTDIR}/_ext/52488393/sercom4_uart.o ${OBJECTDIR}/_ext/80714413/sercom5_i2cm.o ${OBJECTDIR}/_ext/451016939/plib_systick.o ${OBJECTDIR}/_ext/1876745589/xc32_monitor.o ${OBJECTDIR}/_ext/958067195/initialization.o ${OBJECTDIR}/_ext/958067195/interrupts.o ${OBJECTDIR}/_ext/958067195/exceptions.o ${OBJECTDIR}/_ext/958067195/startup_xc32.o ${OBJECTDIR}/_ext/958067195/libc_syscalls.o ${OBJECTDIR}/_ext/1360937237/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1847749054/LTC2944.o.d ${OBJECTDIR}/_ext/1847749054/comm.o.d ${OBJECTDIR}/_ext/1847749054/eeprom.o.d ${OBJECTDIR}/_ext/1847749054/global.o.d ${OBJECTDIR}/_ext/1847749054/gpio.o.d ${OBJECTDIR}/_ext/1847749054/lm75.o.d ${OBJECTDIR}/_ext/1847749054/mgc3130.o.d ${OBJECTDIR}/_ext/1847749054/test.o.d ${OBJECTDIR}/_ext/1847749054/time.o.d ${OBJECTDIR}/_ext/1847749054/tm_event.o.d ${OBJECTDIR}/_ext/1847749054/uart_M4.o.d ${OBJECTDIR}/_ext/1847749054/g_stk8ba53.o.d ${OBJECTDIR}/_ext/1847749054/PreShooting.o.d ${OBJECTDIR}/_ext/431015903/plib_adc.o.d ${OBJECTDIR}/_ext/1887322289/plib_clock.o.d ${OBJECTDIR}/_ext/431011904/plib_eic.o.d ${OBJECTDIR}/_ext/1885172803/plib_evsys.o.d ${OBJECTDIR}/_ext/476186239/plib_nvic.o.d ${OBJECTDIR}/_ext/216541841/plib_nvmctrl.o.d ${OBJECTDIR}/_ext/13903268/plib_pm.o.d ${OBJECTDIR}/_ext/476133088/plib_port.o.d ${OBJECTDIR}/_ext/62028211/sercom0_uart.o.d ${OBJECTDIR}/_ext/33399060/sercom1_uart.o.d ${OBJECTDIR}/_ext/4769909/sercom2_uart.o.d ${OBJECTDIR}/_ext/23859242/sercom3_uart.o.d ${OBJECTDIR}/_ext/52488393/sercom4_uart.o.d ${OBJECTDIR}/_ext/80714413/sercom5_i2cm.o.d ${OBJECTDIR}/_ext/451016939/plib_systick.o.d ${OBJECTDIR}/_ext/1876745589/xc32_monitor.o.d ${OBJECTDIR}/_ext/958067195/initialization.o.d ${OBJECTDIR}/_ext/958067195/interrupts.o.d ${OBJECTDIR}/_ext/958067195/exceptions.o.d ${OBJECTDIR}/_ext/958067195/startup_xc32.o.d ${OBJECTDIR}/_ext/958067195/libc_syscalls.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1847749054/LTC2944.o ${OBJECTDIR}/_ext/1847749054/comm.o ${OBJECTDIR}/_ext/1847749054/eeprom.o ${OBJECTDIR}/_ext/1847749054/global.o ${OBJECTDIR}/_ext/1847749054/gpio.o ${OBJECTDIR}/_ext/1847749054/lm75.o ${OBJECTDIR}/_ext/1847749054/mgc3130.o ${OBJECTDIR}/_ext/1847749054/test.o ${OBJECTDIR}/_ext/1847749054/time.o ${OBJECTDIR}/_ext/1847749054/tm_event.o ${OBJECTDIR}/_ext/1847749054/uart_M4.o ${OBJECTDIR}/_ext/1847749054/g_stk8ba53.o ${OBJECTDIR}/_ext/1847749054/PreShooting.o ${OBJECTDIR}/_ext/431015903/plib_adc.o ${OBJECTDIR}/_ext/1887322289/plib_clock.o ${OBJECTDIR}/_ext/431011904/plib_eic.o ${OBJECTDIR}/_ext/1885172803/plib_evsys.o ${OBJECTDIR}/_ext/476186239/plib_nvic.o ${OBJECTDIR}/_ext/216541841/plib_nvmctrl.o ${OBJECTDIR}/_ext/13903268/plib_pm.o ${OBJECTDIR}/_ext/476133088/plib_port.o ${OBJECTDIR}/_ext/62028211/sercom0_uart.o ${OBJECTDIR}/_ext/33399060/sercom1_uart.o ${OBJECTDIR}/_ext/4769909/sercom2_uart.o ${OBJECTDIR}/_ext/23859242/sercom3_uart.o ${OBJECTDIR}/_ext/52488393/sercom4_uart.o ${OBJECTDIR}/_ext/80714413/sercom5_i2cm.o ${OBJECTDIR}/_ext/451016939/plib_systick.o ${OBJECTDIR}/_ext/1876745589/xc32_monitor.o ${OBJECTDIR}/_ext/958067195/initialization.o ${OBJECTDIR}/_ext/958067195/interrupts.o ${OBJECTDIR}/_ext/958067195/exceptions.o ${OBJECTDIR}/_ext/958067195/startup_xc32.o ${OBJECTDIR}/_ext/958067195/libc_syscalls.o ${OBJECTDIR}/_ext/1360937237/main.o

# Source Files
SOURCEFILES=../src/config/sam_l22_xpro/git/LTC2944.c ../src/config/sam_l22_xpro/git/comm.c ../src/config/sam_l22_xpro/git/eeprom.c ../src/config/sam_l22_xpro/git/global.c ../src/config/sam_l22_xpro/git/gpio.c ../src/config/sam_l22_xpro/git/lm75.c ../src/config/sam_l22_xpro/git/mgc3130.c ../src/config/sam_l22_xpro/git/test.c ../src/config/sam_l22_xpro/git/time.c ../src/config/sam_l22_xpro/git/tm_event.c ../src/config/sam_l22_xpro/git/uart_M4.c ../src/config/sam_l22_xpro/git/g_stk8ba53.c ../src/config/sam_l22_xpro/git/PreShooting.c ../src/config/sam_l22_xpro/peripheral/adc/plib_adc.c ../src/config/sam_l22_xpro/peripheral/clock/plib_clock.c ../src/config/sam_l22_xpro/peripheral/eic/plib_eic.c ../src/config/sam_l22_xpro/peripheral/evsys/plib_evsys.c ../src/config/sam_l22_xpro/peripheral/nvic/plib_nvic.c ../src/config/sam_l22_xpro/peripheral/nvmctrl/plib_nvmctrl.c ../src/config/sam_l22_xpro/peripheral/pm/plib_pm.c ../src/config/sam_l22_xpro/peripheral/port/plib_port.c ../src/config/sam_l22_xpro/peripheral/sercom0/uart/sercom0_uart.c ../src/config/sam_l22_xpro/peripheral/sercom1/uart/sercom1_uart.c ../src/config/sam_l22_xpro/peripheral/sercom2/uart/sercom2_uart.c ../src/config/sam_l22_xpro/peripheral/sercom3/uart/sercom3_uart.c ../src/config/sam_l22_xpro/peripheral/sercom4/uart/sercom4_uart.c ../src/config/sam_l22_xpro/peripheral/sercom5/i2cm/sercom5_i2cm.c ../src/config/sam_l22_xpro/peripheral/systick/plib_systick.c ../src/config/sam_l22_xpro/stdio/xc32_monitor.c ../src/config/sam_l22_xpro/initialization.c ../src/config/sam_l22_xpro/interrupts.c ../src/config/sam_l22_xpro/exceptions.c ../src/config/sam_l22_xpro/startup_xc32.c ../src/config/sam_l22_xpro/libc_syscalls.c ../src/main.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-sam_l22_xpro.mk dist/${CND_CONF}/${IMAGE_TYPE}/Prj312_ALL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATSAML22N18A
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1847749054/LTC2944.o: ../src/config/sam_l22_xpro/git/LTC2944.c  .generated_files/flags/sam_l22_xpro/92a390217c5f7faa12471cbb7d7942858ae27de2 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1847749054" 
	@${RM} ${OBJECTDIR}/_ext/1847749054/LTC2944.o.d 
	@${RM} ${OBJECTDIR}/_ext/1847749054/LTC2944.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1847749054/LTC2944.o.d" -o ${OBJECTDIR}/_ext/1847749054/LTC2944.o ../src/config/sam_l22_xpro/git/LTC2944.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1847749054/comm.o: ../src/config/sam_l22_xpro/git/comm.c  .generated_files/flags/sam_l22_xpro/6a4c0683b5f84e84d83323e38445f831a7c7799a .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1847749054" 
	@${RM} ${OBJECTDIR}/_ext/1847749054/comm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1847749054/comm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1847749054/comm.o.d" -o ${OBJECTDIR}/_ext/1847749054/comm.o ../src/config/sam_l22_xpro/git/comm.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1847749054/eeprom.o: ../src/config/sam_l22_xpro/git/eeprom.c  .generated_files/flags/sam_l22_xpro/c0ffa60eb50c515ae8c059f9b7e78331605027d5 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1847749054" 
	@${RM} ${OBJECTDIR}/_ext/1847749054/eeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/1847749054/eeprom.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1847749054/eeprom.o.d" -o ${OBJECTDIR}/_ext/1847749054/eeprom.o ../src/config/sam_l22_xpro/git/eeprom.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1847749054/global.o: ../src/config/sam_l22_xpro/git/global.c  .generated_files/flags/sam_l22_xpro/20dc06fefb8de20cb7f045a205bc5872b1cb1f70 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1847749054" 
	@${RM} ${OBJECTDIR}/_ext/1847749054/global.o.d 
	@${RM} ${OBJECTDIR}/_ext/1847749054/global.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1847749054/global.o.d" -o ${OBJECTDIR}/_ext/1847749054/global.o ../src/config/sam_l22_xpro/git/global.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1847749054/gpio.o: ../src/config/sam_l22_xpro/git/gpio.c  .generated_files/flags/sam_l22_xpro/142ad633d3ac182e217d9e504ace606567d4afde .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1847749054" 
	@${RM} ${OBJECTDIR}/_ext/1847749054/gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1847749054/gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1847749054/gpio.o.d" -o ${OBJECTDIR}/_ext/1847749054/gpio.o ../src/config/sam_l22_xpro/git/gpio.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1847749054/lm75.o: ../src/config/sam_l22_xpro/git/lm75.c  .generated_files/flags/sam_l22_xpro/7dafe3080f6d9e8d72e83f7c720a89e8a6041a91 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1847749054" 
	@${RM} ${OBJECTDIR}/_ext/1847749054/lm75.o.d 
	@${RM} ${OBJECTDIR}/_ext/1847749054/lm75.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1847749054/lm75.o.d" -o ${OBJECTDIR}/_ext/1847749054/lm75.o ../src/config/sam_l22_xpro/git/lm75.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1847749054/mgc3130.o: ../src/config/sam_l22_xpro/git/mgc3130.c  .generated_files/flags/sam_l22_xpro/95902bcb9c90f5d73090a926eb2c005991fa61b0 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1847749054" 
	@${RM} ${OBJECTDIR}/_ext/1847749054/mgc3130.o.d 
	@${RM} ${OBJECTDIR}/_ext/1847749054/mgc3130.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1847749054/mgc3130.o.d" -o ${OBJECTDIR}/_ext/1847749054/mgc3130.o ../src/config/sam_l22_xpro/git/mgc3130.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1847749054/test.o: ../src/config/sam_l22_xpro/git/test.c  .generated_files/flags/sam_l22_xpro/ebdac16847e566999ba6c12945feb838be6944d5 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1847749054" 
	@${RM} ${OBJECTDIR}/_ext/1847749054/test.o.d 
	@${RM} ${OBJECTDIR}/_ext/1847749054/test.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1847749054/test.o.d" -o ${OBJECTDIR}/_ext/1847749054/test.o ../src/config/sam_l22_xpro/git/test.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1847749054/time.o: ../src/config/sam_l22_xpro/git/time.c  .generated_files/flags/sam_l22_xpro/1c2ec359330c18f61038298e64715564475cdf39 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1847749054" 
	@${RM} ${OBJECTDIR}/_ext/1847749054/time.o.d 
	@${RM} ${OBJECTDIR}/_ext/1847749054/time.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1847749054/time.o.d" -o ${OBJECTDIR}/_ext/1847749054/time.o ../src/config/sam_l22_xpro/git/time.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1847749054/tm_event.o: ../src/config/sam_l22_xpro/git/tm_event.c  .generated_files/flags/sam_l22_xpro/66ad63325c4c8fbcfbf67ff1c943713ea9498da7 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1847749054" 
	@${RM} ${OBJECTDIR}/_ext/1847749054/tm_event.o.d 
	@${RM} ${OBJECTDIR}/_ext/1847749054/tm_event.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1847749054/tm_event.o.d" -o ${OBJECTDIR}/_ext/1847749054/tm_event.o ../src/config/sam_l22_xpro/git/tm_event.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1847749054/uart_M4.o: ../src/config/sam_l22_xpro/git/uart_M4.c  .generated_files/flags/sam_l22_xpro/161f42f82f6e70582e53ca4c2abbd3746af218f0 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1847749054" 
	@${RM} ${OBJECTDIR}/_ext/1847749054/uart_M4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1847749054/uart_M4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1847749054/uart_M4.o.d" -o ${OBJECTDIR}/_ext/1847749054/uart_M4.o ../src/config/sam_l22_xpro/git/uart_M4.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1847749054/g_stk8ba53.o: ../src/config/sam_l22_xpro/git/g_stk8ba53.c  .generated_files/flags/sam_l22_xpro/2aa1c366e9328d4dc03e0ea377b88a9c6a0595b7 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1847749054" 
	@${RM} ${OBJECTDIR}/_ext/1847749054/g_stk8ba53.o.d 
	@${RM} ${OBJECTDIR}/_ext/1847749054/g_stk8ba53.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1847749054/g_stk8ba53.o.d" -o ${OBJECTDIR}/_ext/1847749054/g_stk8ba53.o ../src/config/sam_l22_xpro/git/g_stk8ba53.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1847749054/PreShooting.o: ../src/config/sam_l22_xpro/git/PreShooting.c  .generated_files/flags/sam_l22_xpro/67cf9760241be0224258778a9b21353381aa39b .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1847749054" 
	@${RM} ${OBJECTDIR}/_ext/1847749054/PreShooting.o.d 
	@${RM} ${OBJECTDIR}/_ext/1847749054/PreShooting.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1847749054/PreShooting.o.d" -o ${OBJECTDIR}/_ext/1847749054/PreShooting.o ../src/config/sam_l22_xpro/git/PreShooting.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/431015903/plib_adc.o: ../src/config/sam_l22_xpro/peripheral/adc/plib_adc.c  .generated_files/flags/sam_l22_xpro/ac2afaf7402911d1c00de4d5281d13d9dae6be20 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/431015903" 
	@${RM} ${OBJECTDIR}/_ext/431015903/plib_adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/431015903/plib_adc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/431015903/plib_adc.o.d" -o ${OBJECTDIR}/_ext/431015903/plib_adc.o ../src/config/sam_l22_xpro/peripheral/adc/plib_adc.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1887322289/plib_clock.o: ../src/config/sam_l22_xpro/peripheral/clock/plib_clock.c  .generated_files/flags/sam_l22_xpro/570715c01ef1765e08d9a5526bdf140b65e787f5 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1887322289" 
	@${RM} ${OBJECTDIR}/_ext/1887322289/plib_clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/1887322289/plib_clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1887322289/plib_clock.o.d" -o ${OBJECTDIR}/_ext/1887322289/plib_clock.o ../src/config/sam_l22_xpro/peripheral/clock/plib_clock.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/431011904/plib_eic.o: ../src/config/sam_l22_xpro/peripheral/eic/plib_eic.c  .generated_files/flags/sam_l22_xpro/d29f7fc52431021948e0e6bb0efd44ed4eaf98c2 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/431011904" 
	@${RM} ${OBJECTDIR}/_ext/431011904/plib_eic.o.d 
	@${RM} ${OBJECTDIR}/_ext/431011904/plib_eic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/431011904/plib_eic.o.d" -o ${OBJECTDIR}/_ext/431011904/plib_eic.o ../src/config/sam_l22_xpro/peripheral/eic/plib_eic.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1885172803/plib_evsys.o: ../src/config/sam_l22_xpro/peripheral/evsys/plib_evsys.c  .generated_files/flags/sam_l22_xpro/8908ac6688a27a0b7ef862e47a401f2beda6914e .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1885172803" 
	@${RM} ${OBJECTDIR}/_ext/1885172803/plib_evsys.o.d 
	@${RM} ${OBJECTDIR}/_ext/1885172803/plib_evsys.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1885172803/plib_evsys.o.d" -o ${OBJECTDIR}/_ext/1885172803/plib_evsys.o ../src/config/sam_l22_xpro/peripheral/evsys/plib_evsys.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/476186239/plib_nvic.o: ../src/config/sam_l22_xpro/peripheral/nvic/plib_nvic.c  .generated_files/flags/sam_l22_xpro/6261d8603aba9abea07dfe3cf87a4729b609ebb7 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/476186239" 
	@${RM} ${OBJECTDIR}/_ext/476186239/plib_nvic.o.d 
	@${RM} ${OBJECTDIR}/_ext/476186239/plib_nvic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/476186239/plib_nvic.o.d" -o ${OBJECTDIR}/_ext/476186239/plib_nvic.o ../src/config/sam_l22_xpro/peripheral/nvic/plib_nvic.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/216541841/plib_nvmctrl.o: ../src/config/sam_l22_xpro/peripheral/nvmctrl/plib_nvmctrl.c  .generated_files/flags/sam_l22_xpro/1a7c16c607846422056161323018268cb59a0b01 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/216541841" 
	@${RM} ${OBJECTDIR}/_ext/216541841/plib_nvmctrl.o.d 
	@${RM} ${OBJECTDIR}/_ext/216541841/plib_nvmctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/216541841/plib_nvmctrl.o.d" -o ${OBJECTDIR}/_ext/216541841/plib_nvmctrl.o ../src/config/sam_l22_xpro/peripheral/nvmctrl/plib_nvmctrl.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/13903268/plib_pm.o: ../src/config/sam_l22_xpro/peripheral/pm/plib_pm.c  .generated_files/flags/sam_l22_xpro/80c6d7487d744226311d280ec1f684aa251de97c .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/13903268" 
	@${RM} ${OBJECTDIR}/_ext/13903268/plib_pm.o.d 
	@${RM} ${OBJECTDIR}/_ext/13903268/plib_pm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/13903268/plib_pm.o.d" -o ${OBJECTDIR}/_ext/13903268/plib_pm.o ../src/config/sam_l22_xpro/peripheral/pm/plib_pm.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/476133088/plib_port.o: ../src/config/sam_l22_xpro/peripheral/port/plib_port.c  .generated_files/flags/sam_l22_xpro/60e390587bcba615e93e8a729f40b47107439bdd .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/476133088" 
	@${RM} ${OBJECTDIR}/_ext/476133088/plib_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/476133088/plib_port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/476133088/plib_port.o.d" -o ${OBJECTDIR}/_ext/476133088/plib_port.o ../src/config/sam_l22_xpro/peripheral/port/plib_port.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/62028211/sercom0_uart.o: ../src/config/sam_l22_xpro/peripheral/sercom0/uart/sercom0_uart.c  .generated_files/flags/sam_l22_xpro/d0a683d3a7f62775471fe23a960e1a3c94f30766 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/62028211" 
	@${RM} ${OBJECTDIR}/_ext/62028211/sercom0_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/62028211/sercom0_uart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/62028211/sercom0_uart.o.d" -o ${OBJECTDIR}/_ext/62028211/sercom0_uart.o ../src/config/sam_l22_xpro/peripheral/sercom0/uart/sercom0_uart.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/33399060/sercom1_uart.o: ../src/config/sam_l22_xpro/peripheral/sercom1/uart/sercom1_uart.c  .generated_files/flags/sam_l22_xpro/19e72021f86397d981081d983d83171659269ddb .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/33399060" 
	@${RM} ${OBJECTDIR}/_ext/33399060/sercom1_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/33399060/sercom1_uart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/33399060/sercom1_uart.o.d" -o ${OBJECTDIR}/_ext/33399060/sercom1_uart.o ../src/config/sam_l22_xpro/peripheral/sercom1/uart/sercom1_uart.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/4769909/sercom2_uart.o: ../src/config/sam_l22_xpro/peripheral/sercom2/uart/sercom2_uart.c  .generated_files/flags/sam_l22_xpro/d48cdbd5371f0c820e7f779cca16cd9d9b14d1a6 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/4769909" 
	@${RM} ${OBJECTDIR}/_ext/4769909/sercom2_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/4769909/sercom2_uart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/4769909/sercom2_uart.o.d" -o ${OBJECTDIR}/_ext/4769909/sercom2_uart.o ../src/config/sam_l22_xpro/peripheral/sercom2/uart/sercom2_uart.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/23859242/sercom3_uart.o: ../src/config/sam_l22_xpro/peripheral/sercom3/uart/sercom3_uart.c  .generated_files/flags/sam_l22_xpro/c87802f2ccc2ab1139dc5e766ec128572654b415 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/23859242" 
	@${RM} ${OBJECTDIR}/_ext/23859242/sercom3_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/23859242/sercom3_uart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/23859242/sercom3_uart.o.d" -o ${OBJECTDIR}/_ext/23859242/sercom3_uart.o ../src/config/sam_l22_xpro/peripheral/sercom3/uart/sercom3_uart.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/52488393/sercom4_uart.o: ../src/config/sam_l22_xpro/peripheral/sercom4/uart/sercom4_uart.c  .generated_files/flags/sam_l22_xpro/43c606c4e1520e3301645991f794274827ebc3d2 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/52488393" 
	@${RM} ${OBJECTDIR}/_ext/52488393/sercom4_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/52488393/sercom4_uart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/52488393/sercom4_uart.o.d" -o ${OBJECTDIR}/_ext/52488393/sercom4_uart.o ../src/config/sam_l22_xpro/peripheral/sercom4/uart/sercom4_uart.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/80714413/sercom5_i2cm.o: ../src/config/sam_l22_xpro/peripheral/sercom5/i2cm/sercom5_i2cm.c  .generated_files/flags/sam_l22_xpro/cc98168e1237d7b19a1d865ecad4a3d8d7e4b7a0 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/80714413" 
	@${RM} ${OBJECTDIR}/_ext/80714413/sercom5_i2cm.o.d 
	@${RM} ${OBJECTDIR}/_ext/80714413/sercom5_i2cm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/80714413/sercom5_i2cm.o.d" -o ${OBJECTDIR}/_ext/80714413/sercom5_i2cm.o ../src/config/sam_l22_xpro/peripheral/sercom5/i2cm/sercom5_i2cm.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/451016939/plib_systick.o: ../src/config/sam_l22_xpro/peripheral/systick/plib_systick.c  .generated_files/flags/sam_l22_xpro/5e20d36804483549c687745c4b77f92580ff91b3 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/451016939" 
	@${RM} ${OBJECTDIR}/_ext/451016939/plib_systick.o.d 
	@${RM} ${OBJECTDIR}/_ext/451016939/plib_systick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/451016939/plib_systick.o.d" -o ${OBJECTDIR}/_ext/451016939/plib_systick.o ../src/config/sam_l22_xpro/peripheral/systick/plib_systick.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1876745589/xc32_monitor.o: ../src/config/sam_l22_xpro/stdio/xc32_monitor.c  .generated_files/flags/sam_l22_xpro/2061253240439953cef19424898946e3753d5b87 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1876745589" 
	@${RM} ${OBJECTDIR}/_ext/1876745589/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1876745589/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1876745589/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/1876745589/xc32_monitor.o ../src/config/sam_l22_xpro/stdio/xc32_monitor.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/958067195/initialization.o: ../src/config/sam_l22_xpro/initialization.c  .generated_files/flags/sam_l22_xpro/d22d00a695bd68374e2af974bb61489aa37c81cf .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/958067195" 
	@${RM} ${OBJECTDIR}/_ext/958067195/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/958067195/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/958067195/initialization.o.d" -o ${OBJECTDIR}/_ext/958067195/initialization.o ../src/config/sam_l22_xpro/initialization.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/958067195/interrupts.o: ../src/config/sam_l22_xpro/interrupts.c  .generated_files/flags/sam_l22_xpro/9ca39a15dc4219cd8280b11a182ba13730cccf14 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/958067195" 
	@${RM} ${OBJECTDIR}/_ext/958067195/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/958067195/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/958067195/interrupts.o.d" -o ${OBJECTDIR}/_ext/958067195/interrupts.o ../src/config/sam_l22_xpro/interrupts.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/958067195/exceptions.o: ../src/config/sam_l22_xpro/exceptions.c  .generated_files/flags/sam_l22_xpro/25611d70518342a77fc54e98f52b20339c4407c5 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/958067195" 
	@${RM} ${OBJECTDIR}/_ext/958067195/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/958067195/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/958067195/exceptions.o.d" -o ${OBJECTDIR}/_ext/958067195/exceptions.o ../src/config/sam_l22_xpro/exceptions.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/958067195/startup_xc32.o: ../src/config/sam_l22_xpro/startup_xc32.c  .generated_files/flags/sam_l22_xpro/dae40db3b0776ec9dbf3a6b85bd123a1dd61fc2e .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/958067195" 
	@${RM} ${OBJECTDIR}/_ext/958067195/startup_xc32.o.d 
	@${RM} ${OBJECTDIR}/_ext/958067195/startup_xc32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/958067195/startup_xc32.o.d" -o ${OBJECTDIR}/_ext/958067195/startup_xc32.o ../src/config/sam_l22_xpro/startup_xc32.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/958067195/libc_syscalls.o: ../src/config/sam_l22_xpro/libc_syscalls.c  .generated_files/flags/sam_l22_xpro/96bdc5b76ced90f3d47ec0d13d93f23545ed4ae9 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/958067195" 
	@${RM} ${OBJECTDIR}/_ext/958067195/libc_syscalls.o.d 
	@${RM} ${OBJECTDIR}/_ext/958067195/libc_syscalls.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/958067195/libc_syscalls.o.d" -o ${OBJECTDIR}/_ext/958067195/libc_syscalls.o ../src/config/sam_l22_xpro/libc_syscalls.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/flags/sam_l22_xpro/d3ad3c0466f27683f75313cd9c82c0623c526383 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
else
${OBJECTDIR}/_ext/1847749054/LTC2944.o: ../src/config/sam_l22_xpro/git/LTC2944.c  .generated_files/flags/sam_l22_xpro/2a31dd2e1720a99e247d2dbffc7a0d8b29386ce4 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1847749054" 
	@${RM} ${OBJECTDIR}/_ext/1847749054/LTC2944.o.d 
	@${RM} ${OBJECTDIR}/_ext/1847749054/LTC2944.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1847749054/LTC2944.o.d" -o ${OBJECTDIR}/_ext/1847749054/LTC2944.o ../src/config/sam_l22_xpro/git/LTC2944.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1847749054/comm.o: ../src/config/sam_l22_xpro/git/comm.c  .generated_files/flags/sam_l22_xpro/9b62dd721eb24d2bc7b161008e5e4f4927de0eb1 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1847749054" 
	@${RM} ${OBJECTDIR}/_ext/1847749054/comm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1847749054/comm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1847749054/comm.o.d" -o ${OBJECTDIR}/_ext/1847749054/comm.o ../src/config/sam_l22_xpro/git/comm.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1847749054/eeprom.o: ../src/config/sam_l22_xpro/git/eeprom.c  .generated_files/flags/sam_l22_xpro/cd2ecdf34fed2d7ea7887e12144918bb736fb98d .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1847749054" 
	@${RM} ${OBJECTDIR}/_ext/1847749054/eeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/1847749054/eeprom.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1847749054/eeprom.o.d" -o ${OBJECTDIR}/_ext/1847749054/eeprom.o ../src/config/sam_l22_xpro/git/eeprom.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1847749054/global.o: ../src/config/sam_l22_xpro/git/global.c  .generated_files/flags/sam_l22_xpro/8216ee348ae99c36db06c94af5e64ac7945fecba .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1847749054" 
	@${RM} ${OBJECTDIR}/_ext/1847749054/global.o.d 
	@${RM} ${OBJECTDIR}/_ext/1847749054/global.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1847749054/global.o.d" -o ${OBJECTDIR}/_ext/1847749054/global.o ../src/config/sam_l22_xpro/git/global.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1847749054/gpio.o: ../src/config/sam_l22_xpro/git/gpio.c  .generated_files/flags/sam_l22_xpro/6de35c44cdade46bf97c315e9d61d30289504d21 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1847749054" 
	@${RM} ${OBJECTDIR}/_ext/1847749054/gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1847749054/gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1847749054/gpio.o.d" -o ${OBJECTDIR}/_ext/1847749054/gpio.o ../src/config/sam_l22_xpro/git/gpio.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1847749054/lm75.o: ../src/config/sam_l22_xpro/git/lm75.c  .generated_files/flags/sam_l22_xpro/fa24a01d5bf0ae24fd08e619b731ab0ed520f807 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1847749054" 
	@${RM} ${OBJECTDIR}/_ext/1847749054/lm75.o.d 
	@${RM} ${OBJECTDIR}/_ext/1847749054/lm75.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1847749054/lm75.o.d" -o ${OBJECTDIR}/_ext/1847749054/lm75.o ../src/config/sam_l22_xpro/git/lm75.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1847749054/mgc3130.o: ../src/config/sam_l22_xpro/git/mgc3130.c  .generated_files/flags/sam_l22_xpro/5b5ec9f1513c95aa9965c93e92a933eb999969b5 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1847749054" 
	@${RM} ${OBJECTDIR}/_ext/1847749054/mgc3130.o.d 
	@${RM} ${OBJECTDIR}/_ext/1847749054/mgc3130.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1847749054/mgc3130.o.d" -o ${OBJECTDIR}/_ext/1847749054/mgc3130.o ../src/config/sam_l22_xpro/git/mgc3130.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1847749054/test.o: ../src/config/sam_l22_xpro/git/test.c  .generated_files/flags/sam_l22_xpro/fb25d07810d8041be9d717355091d0040129959f .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1847749054" 
	@${RM} ${OBJECTDIR}/_ext/1847749054/test.o.d 
	@${RM} ${OBJECTDIR}/_ext/1847749054/test.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1847749054/test.o.d" -o ${OBJECTDIR}/_ext/1847749054/test.o ../src/config/sam_l22_xpro/git/test.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1847749054/time.o: ../src/config/sam_l22_xpro/git/time.c  .generated_files/flags/sam_l22_xpro/6189042c9d07d2d96778a409896d691a41fceb5c .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1847749054" 
	@${RM} ${OBJECTDIR}/_ext/1847749054/time.o.d 
	@${RM} ${OBJECTDIR}/_ext/1847749054/time.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1847749054/time.o.d" -o ${OBJECTDIR}/_ext/1847749054/time.o ../src/config/sam_l22_xpro/git/time.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1847749054/tm_event.o: ../src/config/sam_l22_xpro/git/tm_event.c  .generated_files/flags/sam_l22_xpro/557b5b6922ac1e126bf74325e18116b85cc004dd .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1847749054" 
	@${RM} ${OBJECTDIR}/_ext/1847749054/tm_event.o.d 
	@${RM} ${OBJECTDIR}/_ext/1847749054/tm_event.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1847749054/tm_event.o.d" -o ${OBJECTDIR}/_ext/1847749054/tm_event.o ../src/config/sam_l22_xpro/git/tm_event.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1847749054/uart_M4.o: ../src/config/sam_l22_xpro/git/uart_M4.c  .generated_files/flags/sam_l22_xpro/5461d44b7bee7e5c75394935ed3665f0b64a1cca .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1847749054" 
	@${RM} ${OBJECTDIR}/_ext/1847749054/uart_M4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1847749054/uart_M4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1847749054/uart_M4.o.d" -o ${OBJECTDIR}/_ext/1847749054/uart_M4.o ../src/config/sam_l22_xpro/git/uart_M4.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1847749054/g_stk8ba53.o: ../src/config/sam_l22_xpro/git/g_stk8ba53.c  .generated_files/flags/sam_l22_xpro/77a097c32cf8c080026db6a865b153baef11d0a8 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1847749054" 
	@${RM} ${OBJECTDIR}/_ext/1847749054/g_stk8ba53.o.d 
	@${RM} ${OBJECTDIR}/_ext/1847749054/g_stk8ba53.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1847749054/g_stk8ba53.o.d" -o ${OBJECTDIR}/_ext/1847749054/g_stk8ba53.o ../src/config/sam_l22_xpro/git/g_stk8ba53.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1847749054/PreShooting.o: ../src/config/sam_l22_xpro/git/PreShooting.c  .generated_files/flags/sam_l22_xpro/a829d01fa6684709537b1790d427806bd542893d .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1847749054" 
	@${RM} ${OBJECTDIR}/_ext/1847749054/PreShooting.o.d 
	@${RM} ${OBJECTDIR}/_ext/1847749054/PreShooting.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1847749054/PreShooting.o.d" -o ${OBJECTDIR}/_ext/1847749054/PreShooting.o ../src/config/sam_l22_xpro/git/PreShooting.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/431015903/plib_adc.o: ../src/config/sam_l22_xpro/peripheral/adc/plib_adc.c  .generated_files/flags/sam_l22_xpro/f9875e82672f88983facf6e1c47d56b977045ef4 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/431015903" 
	@${RM} ${OBJECTDIR}/_ext/431015903/plib_adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/431015903/plib_adc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/431015903/plib_adc.o.d" -o ${OBJECTDIR}/_ext/431015903/plib_adc.o ../src/config/sam_l22_xpro/peripheral/adc/plib_adc.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1887322289/plib_clock.o: ../src/config/sam_l22_xpro/peripheral/clock/plib_clock.c  .generated_files/flags/sam_l22_xpro/e575ae0fdc780cc59995a5564f0be00fcf22075f .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1887322289" 
	@${RM} ${OBJECTDIR}/_ext/1887322289/plib_clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/1887322289/plib_clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1887322289/plib_clock.o.d" -o ${OBJECTDIR}/_ext/1887322289/plib_clock.o ../src/config/sam_l22_xpro/peripheral/clock/plib_clock.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/431011904/plib_eic.o: ../src/config/sam_l22_xpro/peripheral/eic/plib_eic.c  .generated_files/flags/sam_l22_xpro/f53d70ad1d6873e7519cf3304ea5c7b16433d5d9 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/431011904" 
	@${RM} ${OBJECTDIR}/_ext/431011904/plib_eic.o.d 
	@${RM} ${OBJECTDIR}/_ext/431011904/plib_eic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/431011904/plib_eic.o.d" -o ${OBJECTDIR}/_ext/431011904/plib_eic.o ../src/config/sam_l22_xpro/peripheral/eic/plib_eic.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1885172803/plib_evsys.o: ../src/config/sam_l22_xpro/peripheral/evsys/plib_evsys.c  .generated_files/flags/sam_l22_xpro/dbf0f727191154bcb47efef78ab077fac5a8549f .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1885172803" 
	@${RM} ${OBJECTDIR}/_ext/1885172803/plib_evsys.o.d 
	@${RM} ${OBJECTDIR}/_ext/1885172803/plib_evsys.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1885172803/plib_evsys.o.d" -o ${OBJECTDIR}/_ext/1885172803/plib_evsys.o ../src/config/sam_l22_xpro/peripheral/evsys/plib_evsys.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/476186239/plib_nvic.o: ../src/config/sam_l22_xpro/peripheral/nvic/plib_nvic.c  .generated_files/flags/sam_l22_xpro/92bb97efaeb1fc9402735a78fabde242260a005b .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/476186239" 
	@${RM} ${OBJECTDIR}/_ext/476186239/plib_nvic.o.d 
	@${RM} ${OBJECTDIR}/_ext/476186239/plib_nvic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/476186239/plib_nvic.o.d" -o ${OBJECTDIR}/_ext/476186239/plib_nvic.o ../src/config/sam_l22_xpro/peripheral/nvic/plib_nvic.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/216541841/plib_nvmctrl.o: ../src/config/sam_l22_xpro/peripheral/nvmctrl/plib_nvmctrl.c  .generated_files/flags/sam_l22_xpro/2fe1ef90a60be9f7ec695c18b49cb1eaa0677d12 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/216541841" 
	@${RM} ${OBJECTDIR}/_ext/216541841/plib_nvmctrl.o.d 
	@${RM} ${OBJECTDIR}/_ext/216541841/plib_nvmctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/216541841/plib_nvmctrl.o.d" -o ${OBJECTDIR}/_ext/216541841/plib_nvmctrl.o ../src/config/sam_l22_xpro/peripheral/nvmctrl/plib_nvmctrl.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/13903268/plib_pm.o: ../src/config/sam_l22_xpro/peripheral/pm/plib_pm.c  .generated_files/flags/sam_l22_xpro/17f0a9381b098a8ffa9125f0d524e1a4d5525eb4 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/13903268" 
	@${RM} ${OBJECTDIR}/_ext/13903268/plib_pm.o.d 
	@${RM} ${OBJECTDIR}/_ext/13903268/plib_pm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/13903268/plib_pm.o.d" -o ${OBJECTDIR}/_ext/13903268/plib_pm.o ../src/config/sam_l22_xpro/peripheral/pm/plib_pm.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/476133088/plib_port.o: ../src/config/sam_l22_xpro/peripheral/port/plib_port.c  .generated_files/flags/sam_l22_xpro/1807c9a027753486b78aa9d6d7dbc03de1b353a .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/476133088" 
	@${RM} ${OBJECTDIR}/_ext/476133088/plib_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/476133088/plib_port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/476133088/plib_port.o.d" -o ${OBJECTDIR}/_ext/476133088/plib_port.o ../src/config/sam_l22_xpro/peripheral/port/plib_port.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/62028211/sercom0_uart.o: ../src/config/sam_l22_xpro/peripheral/sercom0/uart/sercom0_uart.c  .generated_files/flags/sam_l22_xpro/3b79033abef7bcabea8e6e28fbeaa6521f884667 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/62028211" 
	@${RM} ${OBJECTDIR}/_ext/62028211/sercom0_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/62028211/sercom0_uart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/62028211/sercom0_uart.o.d" -o ${OBJECTDIR}/_ext/62028211/sercom0_uart.o ../src/config/sam_l22_xpro/peripheral/sercom0/uart/sercom0_uart.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/33399060/sercom1_uart.o: ../src/config/sam_l22_xpro/peripheral/sercom1/uart/sercom1_uart.c  .generated_files/flags/sam_l22_xpro/e2102d330f09a05988d7ca05146a7bf55133ab83 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/33399060" 
	@${RM} ${OBJECTDIR}/_ext/33399060/sercom1_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/33399060/sercom1_uart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/33399060/sercom1_uart.o.d" -o ${OBJECTDIR}/_ext/33399060/sercom1_uart.o ../src/config/sam_l22_xpro/peripheral/sercom1/uart/sercom1_uart.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/4769909/sercom2_uart.o: ../src/config/sam_l22_xpro/peripheral/sercom2/uart/sercom2_uart.c  .generated_files/flags/sam_l22_xpro/b6639478b24d42644af99d51d019a50af1a171a8 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/4769909" 
	@${RM} ${OBJECTDIR}/_ext/4769909/sercom2_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/4769909/sercom2_uart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/4769909/sercom2_uart.o.d" -o ${OBJECTDIR}/_ext/4769909/sercom2_uart.o ../src/config/sam_l22_xpro/peripheral/sercom2/uart/sercom2_uart.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/23859242/sercom3_uart.o: ../src/config/sam_l22_xpro/peripheral/sercom3/uart/sercom3_uart.c  .generated_files/flags/sam_l22_xpro/c4db6e8b99816091b0a4f760a594a8ad8f9d5b2a .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/23859242" 
	@${RM} ${OBJECTDIR}/_ext/23859242/sercom3_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/23859242/sercom3_uart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/23859242/sercom3_uart.o.d" -o ${OBJECTDIR}/_ext/23859242/sercom3_uart.o ../src/config/sam_l22_xpro/peripheral/sercom3/uart/sercom3_uart.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/52488393/sercom4_uart.o: ../src/config/sam_l22_xpro/peripheral/sercom4/uart/sercom4_uart.c  .generated_files/flags/sam_l22_xpro/78c2a1561e9df680cf9339e7dade8be3834c9d9d .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/52488393" 
	@${RM} ${OBJECTDIR}/_ext/52488393/sercom4_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/52488393/sercom4_uart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/52488393/sercom4_uart.o.d" -o ${OBJECTDIR}/_ext/52488393/sercom4_uart.o ../src/config/sam_l22_xpro/peripheral/sercom4/uart/sercom4_uart.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/80714413/sercom5_i2cm.o: ../src/config/sam_l22_xpro/peripheral/sercom5/i2cm/sercom5_i2cm.c  .generated_files/flags/sam_l22_xpro/789779b2a7be1bc3d27d874a4a722011aa3ff7e0 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/80714413" 
	@${RM} ${OBJECTDIR}/_ext/80714413/sercom5_i2cm.o.d 
	@${RM} ${OBJECTDIR}/_ext/80714413/sercom5_i2cm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/80714413/sercom5_i2cm.o.d" -o ${OBJECTDIR}/_ext/80714413/sercom5_i2cm.o ../src/config/sam_l22_xpro/peripheral/sercom5/i2cm/sercom5_i2cm.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/451016939/plib_systick.o: ../src/config/sam_l22_xpro/peripheral/systick/plib_systick.c  .generated_files/flags/sam_l22_xpro/c19a5514ab35ebe5f307f0e463a347eb646b14d3 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/451016939" 
	@${RM} ${OBJECTDIR}/_ext/451016939/plib_systick.o.d 
	@${RM} ${OBJECTDIR}/_ext/451016939/plib_systick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/451016939/plib_systick.o.d" -o ${OBJECTDIR}/_ext/451016939/plib_systick.o ../src/config/sam_l22_xpro/peripheral/systick/plib_systick.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1876745589/xc32_monitor.o: ../src/config/sam_l22_xpro/stdio/xc32_monitor.c  .generated_files/flags/sam_l22_xpro/8bbe6ee42935dae8bee0191519e013610975b9f8 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1876745589" 
	@${RM} ${OBJECTDIR}/_ext/1876745589/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1876745589/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1876745589/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/1876745589/xc32_monitor.o ../src/config/sam_l22_xpro/stdio/xc32_monitor.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/958067195/initialization.o: ../src/config/sam_l22_xpro/initialization.c  .generated_files/flags/sam_l22_xpro/95e873fe11780e54e51a6e6065bd679c1cc373f7 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/958067195" 
	@${RM} ${OBJECTDIR}/_ext/958067195/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/958067195/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/958067195/initialization.o.d" -o ${OBJECTDIR}/_ext/958067195/initialization.o ../src/config/sam_l22_xpro/initialization.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/958067195/interrupts.o: ../src/config/sam_l22_xpro/interrupts.c  .generated_files/flags/sam_l22_xpro/ef1fd953f8d74a9379294d8675955885684496fe .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/958067195" 
	@${RM} ${OBJECTDIR}/_ext/958067195/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/958067195/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/958067195/interrupts.o.d" -o ${OBJECTDIR}/_ext/958067195/interrupts.o ../src/config/sam_l22_xpro/interrupts.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/958067195/exceptions.o: ../src/config/sam_l22_xpro/exceptions.c  .generated_files/flags/sam_l22_xpro/84053f050f4e62018bd018ce453013b64fc3498b .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/958067195" 
	@${RM} ${OBJECTDIR}/_ext/958067195/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/958067195/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/958067195/exceptions.o.d" -o ${OBJECTDIR}/_ext/958067195/exceptions.o ../src/config/sam_l22_xpro/exceptions.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/958067195/startup_xc32.o: ../src/config/sam_l22_xpro/startup_xc32.c  .generated_files/flags/sam_l22_xpro/70da90270fcb0fadc4a153e584b2c97b81ef7fc8 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/958067195" 
	@${RM} ${OBJECTDIR}/_ext/958067195/startup_xc32.o.d 
	@${RM} ${OBJECTDIR}/_ext/958067195/startup_xc32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/958067195/startup_xc32.o.d" -o ${OBJECTDIR}/_ext/958067195/startup_xc32.o ../src/config/sam_l22_xpro/startup_xc32.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/958067195/libc_syscalls.o: ../src/config/sam_l22_xpro/libc_syscalls.c  .generated_files/flags/sam_l22_xpro/3e8140afe8d300a314e3edcc4163d7f79835f0e8 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/958067195" 
	@${RM} ${OBJECTDIR}/_ext/958067195/libc_syscalls.o.d 
	@${RM} ${OBJECTDIR}/_ext/958067195/libc_syscalls.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/958067195/libc_syscalls.o.d" -o ${OBJECTDIR}/_ext/958067195/libc_syscalls.o ../src/config/sam_l22_xpro/libc_syscalls.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/flags/sam_l22_xpro/b4b92b2b1877ed0e4b674ab23c708119bc3192d9 .generated_files/flags/sam_l22_xpro/f50b163a5c070cc8bf98456be72a43c43dd74c5c
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/sam_l22_xpro" -I"../src/packs/ATSAML22N18A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)   ${PACK_COMMON_OPTIONS} 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Prj312_ALL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION) -mno-device-startup-code -o dist/${CND_CONF}/${IMAGE_TYPE}/Prj312_ALL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=1024,--defsym=_min_stack_size=1024,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Prj312_ALL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -mno-device-startup-code -o dist/${CND_CONF}/${IMAGE_TYPE}/Prj312_ALL.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_sam_l22_xpro=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=1024,--defsym=_min_stack_size=1024,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml 
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Prj312_ALL.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/sam_l22_xpro
	${RM} -r dist/sam_l22_xpro

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
