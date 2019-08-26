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
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/USB_HF_FBL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/USB_HF_FBL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
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
SOURCEFILES_QUOTED_IF_SPACED="../Microchip/USB/CDC Device Driver/usb_function_cdc.c" ../Microchip/USB/usb_device.c "../CDC - Serial Emulator/usb_descriptors.c" "../CDC - Serial Emulator/main.c" "../CDC - Serial Emulator/LEDs_control.c" ../../MRF89_Drv/MRF89XA.c "../CDC - Serial Emulator/MSPI.c" "../CDC - Serial Emulator/bootloader.c"

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/131024517/usb_function_cdc.o ${OBJECTDIR}/_ext/343710134/usb_device.o ${OBJECTDIR}/_ext/616994271/usb_descriptors.o ${OBJECTDIR}/_ext/616994271/main.o ${OBJECTDIR}/_ext/616994271/LEDs_control.o ${OBJECTDIR}/_ext/979234859/MRF89XA.o ${OBJECTDIR}/_ext/616994271/MSPI.o ${OBJECTDIR}/_ext/616994271/bootloader.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/131024517/usb_function_cdc.o.d ${OBJECTDIR}/_ext/343710134/usb_device.o.d ${OBJECTDIR}/_ext/616994271/usb_descriptors.o.d ${OBJECTDIR}/_ext/616994271/main.o.d ${OBJECTDIR}/_ext/616994271/LEDs_control.o.d ${OBJECTDIR}/_ext/979234859/MRF89XA.o.d ${OBJECTDIR}/_ext/616994271/MSPI.o.d ${OBJECTDIR}/_ext/616994271/bootloader.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/131024517/usb_function_cdc.o ${OBJECTDIR}/_ext/343710134/usb_device.o ${OBJECTDIR}/_ext/616994271/usb_descriptors.o ${OBJECTDIR}/_ext/616994271/main.o ${OBJECTDIR}/_ext/616994271/LEDs_control.o ${OBJECTDIR}/_ext/979234859/MRF89XA.o ${OBJECTDIR}/_ext/616994271/MSPI.o ${OBJECTDIR}/_ext/616994271/bootloader.o

# Source Files
SOURCEFILES=../Microchip/USB/CDC Device Driver/usb_function_cdc.c ../Microchip/USB/usb_device.c ../CDC - Serial Emulator/usb_descriptors.c ../CDC - Serial Emulator/main.c ../CDC - Serial Emulator/LEDs_control.c ../../MRF89_Drv/MRF89XA.c ../CDC - Serial Emulator/MSPI.c ../CDC - Serial Emulator/bootloader.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/USB_HF_FBL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F26J50
MP_PROCESSOR_OPTION_LD=18f26j50
MP_LINKER_DEBUG_OPTION=  -u_DEBUGSTACK
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/131024517/usb_function_cdc.o: ../Microchip/USB/CDC\ Device\ Driver/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/131024517" 
	@${RM} ${OBJECTDIR}/_ext/131024517/usb_function_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/131024517/usb_function_cdc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"../CDC - Serial Emulator" -I"../CDC - Serial Emulator/tests" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../microchip/include" -I"E:/Sasho/COMPILERS/mcc18/h" -I"." -I"../../MRF89_Drv" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/131024517/usb_function_cdc.o   "../Microchip/USB/CDC Device Driver/usb_function_cdc.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/131024517/usb_function_cdc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/131024517/usb_function_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/343710134/usb_device.o: ../Microchip/USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/343710134" 
	@${RM} ${OBJECTDIR}/_ext/343710134/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/343710134/usb_device.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"../CDC - Serial Emulator" -I"../CDC - Serial Emulator/tests" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../microchip/include" -I"E:/Sasho/COMPILERS/mcc18/h" -I"." -I"../../MRF89_Drv" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/343710134/usb_device.o   ../Microchip/USB/usb_device.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/343710134/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/343710134/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/616994271/usb_descriptors.o: ../CDC\ -\ Serial\ Emulator/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/616994271" 
	@${RM} ${OBJECTDIR}/_ext/616994271/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/_ext/616994271/usb_descriptors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"../CDC - Serial Emulator" -I"../CDC - Serial Emulator/tests" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../microchip/include" -I"E:/Sasho/COMPILERS/mcc18/h" -I"." -I"../../MRF89_Drv" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/616994271/usb_descriptors.o   "../CDC - Serial Emulator/usb_descriptors.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/616994271/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/616994271/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/616994271/main.o: ../CDC\ -\ Serial\ Emulator/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/616994271" 
	@${RM} ${OBJECTDIR}/_ext/616994271/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/616994271/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"../CDC - Serial Emulator" -I"../CDC - Serial Emulator/tests" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../microchip/include" -I"E:/Sasho/COMPILERS/mcc18/h" -I"." -I"../../MRF89_Drv" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/616994271/main.o   "../CDC - Serial Emulator/main.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/616994271/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/616994271/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/616994271/LEDs_control.o: ../CDC\ -\ Serial\ Emulator/LEDs_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/616994271" 
	@${RM} ${OBJECTDIR}/_ext/616994271/LEDs_control.o.d 
	@${RM} ${OBJECTDIR}/_ext/616994271/LEDs_control.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"../CDC - Serial Emulator" -I"../CDC - Serial Emulator/tests" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../microchip/include" -I"E:/Sasho/COMPILERS/mcc18/h" -I"." -I"../../MRF89_Drv" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/616994271/LEDs_control.o   "../CDC - Serial Emulator/LEDs_control.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/616994271/LEDs_control.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/616994271/LEDs_control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/979234859/MRF89XA.o: ../../MRF89_Drv/MRF89XA.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/979234859" 
	@${RM} ${OBJECTDIR}/_ext/979234859/MRF89XA.o.d 
	@${RM} ${OBJECTDIR}/_ext/979234859/MRF89XA.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"../CDC - Serial Emulator" -I"../CDC - Serial Emulator/tests" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../microchip/include" -I"E:/Sasho/COMPILERS/mcc18/h" -I"." -I"../../MRF89_Drv" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/979234859/MRF89XA.o   ../../MRF89_Drv/MRF89XA.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/979234859/MRF89XA.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/979234859/MRF89XA.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/616994271/MSPI.o: ../CDC\ -\ Serial\ Emulator/MSPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/616994271" 
	@${RM} ${OBJECTDIR}/_ext/616994271/MSPI.o.d 
	@${RM} ${OBJECTDIR}/_ext/616994271/MSPI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"../CDC - Serial Emulator" -I"../CDC - Serial Emulator/tests" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../microchip/include" -I"E:/Sasho/COMPILERS/mcc18/h" -I"." -I"../../MRF89_Drv" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/616994271/MSPI.o   "../CDC - Serial Emulator/MSPI.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/616994271/MSPI.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/616994271/MSPI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/616994271/bootloader.o: ../CDC\ -\ Serial\ Emulator/bootloader.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/616994271" 
	@${RM} ${OBJECTDIR}/_ext/616994271/bootloader.o.d 
	@${RM} ${OBJECTDIR}/_ext/616994271/bootloader.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"../CDC - Serial Emulator" -I"../CDC - Serial Emulator/tests" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../microchip/include" -I"E:/Sasho/COMPILERS/mcc18/h" -I"." -I"../../MRF89_Drv" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/616994271/bootloader.o   "../CDC - Serial Emulator/bootloader.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/616994271/bootloader.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/616994271/bootloader.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/_ext/131024517/usb_function_cdc.o: ../Microchip/USB/CDC\ Device\ Driver/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/131024517" 
	@${RM} ${OBJECTDIR}/_ext/131024517/usb_function_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/131024517/usb_function_cdc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"../CDC - Serial Emulator" -I"../CDC - Serial Emulator/tests" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../microchip/include" -I"E:/Sasho/COMPILERS/mcc18/h" -I"." -I"../../MRF89_Drv" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/131024517/usb_function_cdc.o   "../Microchip/USB/CDC Device Driver/usb_function_cdc.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/131024517/usb_function_cdc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/131024517/usb_function_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/343710134/usb_device.o: ../Microchip/USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/343710134" 
	@${RM} ${OBJECTDIR}/_ext/343710134/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/343710134/usb_device.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"../CDC - Serial Emulator" -I"../CDC - Serial Emulator/tests" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../microchip/include" -I"E:/Sasho/COMPILERS/mcc18/h" -I"." -I"../../MRF89_Drv" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/343710134/usb_device.o   ../Microchip/USB/usb_device.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/343710134/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/343710134/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/616994271/usb_descriptors.o: ../CDC\ -\ Serial\ Emulator/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/616994271" 
	@${RM} ${OBJECTDIR}/_ext/616994271/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/_ext/616994271/usb_descriptors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"../CDC - Serial Emulator" -I"../CDC - Serial Emulator/tests" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../microchip/include" -I"E:/Sasho/COMPILERS/mcc18/h" -I"." -I"../../MRF89_Drv" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/616994271/usb_descriptors.o   "../CDC - Serial Emulator/usb_descriptors.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/616994271/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/616994271/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/616994271/main.o: ../CDC\ -\ Serial\ Emulator/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/616994271" 
	@${RM} ${OBJECTDIR}/_ext/616994271/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/616994271/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"../CDC - Serial Emulator" -I"../CDC - Serial Emulator/tests" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../microchip/include" -I"E:/Sasho/COMPILERS/mcc18/h" -I"." -I"../../MRF89_Drv" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/616994271/main.o   "../CDC - Serial Emulator/main.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/616994271/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/616994271/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/616994271/LEDs_control.o: ../CDC\ -\ Serial\ Emulator/LEDs_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/616994271" 
	@${RM} ${OBJECTDIR}/_ext/616994271/LEDs_control.o.d 
	@${RM} ${OBJECTDIR}/_ext/616994271/LEDs_control.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"../CDC - Serial Emulator" -I"../CDC - Serial Emulator/tests" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../microchip/include" -I"E:/Sasho/COMPILERS/mcc18/h" -I"." -I"../../MRF89_Drv" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/616994271/LEDs_control.o   "../CDC - Serial Emulator/LEDs_control.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/616994271/LEDs_control.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/616994271/LEDs_control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/979234859/MRF89XA.o: ../../MRF89_Drv/MRF89XA.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/979234859" 
	@${RM} ${OBJECTDIR}/_ext/979234859/MRF89XA.o.d 
	@${RM} ${OBJECTDIR}/_ext/979234859/MRF89XA.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"../CDC - Serial Emulator" -I"../CDC - Serial Emulator/tests" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../microchip/include" -I"E:/Sasho/COMPILERS/mcc18/h" -I"." -I"../../MRF89_Drv" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/979234859/MRF89XA.o   ../../MRF89_Drv/MRF89XA.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/979234859/MRF89XA.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/979234859/MRF89XA.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/616994271/MSPI.o: ../CDC\ -\ Serial\ Emulator/MSPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/616994271" 
	@${RM} ${OBJECTDIR}/_ext/616994271/MSPI.o.d 
	@${RM} ${OBJECTDIR}/_ext/616994271/MSPI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"../CDC - Serial Emulator" -I"../CDC - Serial Emulator/tests" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../microchip/include" -I"E:/Sasho/COMPILERS/mcc18/h" -I"." -I"../../MRF89_Drv" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/616994271/MSPI.o   "../CDC - Serial Emulator/MSPI.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/616994271/MSPI.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/616994271/MSPI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/616994271/bootloader.o: ../CDC\ -\ Serial\ Emulator/bootloader.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/616994271" 
	@${RM} ${OBJECTDIR}/_ext/616994271/bootloader.o.d 
	@${RM} ${OBJECTDIR}/_ext/616994271/bootloader.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"../CDC - Serial Emulator" -I"../CDC - Serial Emulator/tests" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../microchip/include" -I"E:/Sasho/COMPILERS/mcc18/h" -I"." -I"../../MRF89_Drv" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/616994271/bootloader.o   "../CDC - Serial Emulator/bootloader.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/616994271/bootloader.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/616994271/bootloader.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/USB_HF_FBL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -m"$(BINDIR_)$(TARGETBASE).map" -w -l"E:/Sasho/COMPILERS/mcc18/lib" -l"."  -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_PK3=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/USB_HF_FBL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/USB_HF_FBL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w  -m"$(BINDIR_)$(TARGETBASE).map" -w -l"E:/Sasho/COMPILERS/mcc18/lib" -l"."  -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/USB_HF_FBL.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
