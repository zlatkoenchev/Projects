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
ifeq "$(wildcard nbproject/Makefile-local-Debug.mk)" "nbproject/Makefile-local-Debug.mk"
include nbproject/Makefile-local-Debug.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=Debug
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MRF89XA_Switch.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MRF89XA_Switch.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=--mafrlcsj
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
SOURCEFILES_QUOTED_IF_SPACED=../main.c ../drv_eep.c ../drv_spi.c ../svc_nvm_blocks.c ../../LIBC/MRF89_Drv/MRF89XA.c ../svc_comm.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/main.p1 ${OBJECTDIR}/_ext/1472/drv_eep.p1 ${OBJECTDIR}/_ext/1472/drv_spi.p1 ${OBJECTDIR}/_ext/1472/svc_nvm_blocks.p1 ${OBJECTDIR}/_ext/950037222/MRF89XA.p1 ${OBJECTDIR}/_ext/1472/svc_comm.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/main.p1.d ${OBJECTDIR}/_ext/1472/drv_eep.p1.d ${OBJECTDIR}/_ext/1472/drv_spi.p1.d ${OBJECTDIR}/_ext/1472/svc_nvm_blocks.p1.d ${OBJECTDIR}/_ext/950037222/MRF89XA.p1.d ${OBJECTDIR}/_ext/1472/svc_comm.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/main.p1 ${OBJECTDIR}/_ext/1472/drv_eep.p1 ${OBJECTDIR}/_ext/1472/drv_spi.p1 ${OBJECTDIR}/_ext/1472/svc_nvm_blocks.p1 ${OBJECTDIR}/_ext/950037222/MRF89XA.p1 ${OBJECTDIR}/_ext/1472/svc_comm.p1

# Source Files
SOURCEFILES=../main.c ../drv_eep.c ../drv_spi.c ../svc_nvm_blocks.c ../../LIBC/MRF89_Drv/MRF89XA.c ../svc_comm.c


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
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/${CND_CONF}/${IMAGE_TYPE}/MRF89XA_Switch.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=16LF18323
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/main.p1: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --rom=0-7FF --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -DDEBUG -P -N255 -I"../" -I"../../LIBC/MRF89_Drv" -I"../../LIBC/NVM" --warn=-3 -DXPRJ_Debug=$(CND_CONF)  --summary=default,+psect,-class,-mem,-hex,-file --fill=0@0x480:0x1FFF --codeoffset=0 --output=default,-inhx032 --runtime=default,-clear,-init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto -Q "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/main.p1  ../main.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/main.d ${OBJECTDIR}/_ext/1472/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/drv_eep.p1: ../drv_eep.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/drv_eep.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/drv_eep.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --rom=0-7FF --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -DDEBUG -P -N255 -I"../" -I"../../LIBC/MRF89_Drv" -I"../../LIBC/NVM" --warn=-3 -DXPRJ_Debug=$(CND_CONF)  --summary=default,+psect,-class,-mem,-hex,-file --fill=0@0x480:0x1FFF --codeoffset=0 --output=default,-inhx032 --runtime=default,-clear,-init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto -Q "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/drv_eep.p1  ../drv_eep.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/drv_eep.d ${OBJECTDIR}/_ext/1472/drv_eep.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/drv_eep.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/drv_spi.p1: ../drv_spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/drv_spi.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/drv_spi.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --rom=0-7FF --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -DDEBUG -P -N255 -I"../" -I"../../LIBC/MRF89_Drv" -I"../../LIBC/NVM" --warn=-3 -DXPRJ_Debug=$(CND_CONF)  --summary=default,+psect,-class,-mem,-hex,-file --fill=0@0x480:0x1FFF --codeoffset=0 --output=default,-inhx032 --runtime=default,-clear,-init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto -Q "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/drv_spi.p1  ../drv_spi.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/drv_spi.d ${OBJECTDIR}/_ext/1472/drv_spi.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/drv_spi.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/svc_nvm_blocks.p1: ../svc_nvm_blocks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/svc_nvm_blocks.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/svc_nvm_blocks.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --rom=0-7FF --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -DDEBUG -P -N255 -I"../" -I"../../LIBC/MRF89_Drv" -I"../../LIBC/NVM" --warn=-3 -DXPRJ_Debug=$(CND_CONF)  --summary=default,+psect,-class,-mem,-hex,-file --fill=0@0x480:0x1FFF --codeoffset=0 --output=default,-inhx032 --runtime=default,-clear,-init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto -Q "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/svc_nvm_blocks.p1  ../svc_nvm_blocks.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/svc_nvm_blocks.d ${OBJECTDIR}/_ext/1472/svc_nvm_blocks.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/svc_nvm_blocks.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/950037222/MRF89XA.p1: ../../LIBC/MRF89_Drv/MRF89XA.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/950037222" 
	@${RM} ${OBJECTDIR}/_ext/950037222/MRF89XA.p1.d 
	@${RM} ${OBJECTDIR}/_ext/950037222/MRF89XA.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --rom=0-7FF --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -DDEBUG -P -N255 -I"../" -I"../../LIBC/MRF89_Drv" -I"../../LIBC/NVM" --warn=-3 -DXPRJ_Debug=$(CND_CONF)  --summary=default,+psect,-class,-mem,-hex,-file --fill=0@0x480:0x1FFF --codeoffset=0 --output=default,-inhx032 --runtime=default,-clear,-init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto -Q "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/950037222/MRF89XA.p1  ../../LIBC/MRF89_Drv/MRF89XA.c 
	@-${MV} ${OBJECTDIR}/_ext/950037222/MRF89XA.d ${OBJECTDIR}/_ext/950037222/MRF89XA.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/950037222/MRF89XA.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/svc_comm.p1: ../svc_comm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/svc_comm.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/svc_comm.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --rom=0-7FF --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -DDEBUG -P -N255 -I"../" -I"../../LIBC/MRF89_Drv" -I"../../LIBC/NVM" --warn=-3 -DXPRJ_Debug=$(CND_CONF)  --summary=default,+psect,-class,-mem,-hex,-file --fill=0@0x480:0x1FFF --codeoffset=0 --output=default,-inhx032 --runtime=default,-clear,-init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto -Q "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/svc_comm.p1  ../svc_comm.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/svc_comm.d ${OBJECTDIR}/_ext/1472/svc_comm.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/svc_comm.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/1472/main.p1: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --rom=0-7FF --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -DDEBUG -P -N255 -I"../" -I"../../LIBC/MRF89_Drv" -I"../../LIBC/NVM" --warn=-3 -DXPRJ_Debug=$(CND_CONF)  --summary=default,+psect,-class,-mem,-hex,-file --fill=0@0x480:0x1FFF --codeoffset=0 --output=default,-inhx032 --runtime=default,-clear,-init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto -Q "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/main.p1  ../main.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/main.d ${OBJECTDIR}/_ext/1472/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/drv_eep.p1: ../drv_eep.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/drv_eep.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/drv_eep.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --rom=0-7FF --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -DDEBUG -P -N255 -I"../" -I"../../LIBC/MRF89_Drv" -I"../../LIBC/NVM" --warn=-3 -DXPRJ_Debug=$(CND_CONF)  --summary=default,+psect,-class,-mem,-hex,-file --fill=0@0x480:0x1FFF --codeoffset=0 --output=default,-inhx032 --runtime=default,-clear,-init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto -Q "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/drv_eep.p1  ../drv_eep.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/drv_eep.d ${OBJECTDIR}/_ext/1472/drv_eep.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/drv_eep.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/drv_spi.p1: ../drv_spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/drv_spi.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/drv_spi.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --rom=0-7FF --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -DDEBUG -P -N255 -I"../" -I"../../LIBC/MRF89_Drv" -I"../../LIBC/NVM" --warn=-3 -DXPRJ_Debug=$(CND_CONF)  --summary=default,+psect,-class,-mem,-hex,-file --fill=0@0x480:0x1FFF --codeoffset=0 --output=default,-inhx032 --runtime=default,-clear,-init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto -Q "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/drv_spi.p1  ../drv_spi.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/drv_spi.d ${OBJECTDIR}/_ext/1472/drv_spi.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/drv_spi.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/svc_nvm_blocks.p1: ../svc_nvm_blocks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/svc_nvm_blocks.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/svc_nvm_blocks.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --rom=0-7FF --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -DDEBUG -P -N255 -I"../" -I"../../LIBC/MRF89_Drv" -I"../../LIBC/NVM" --warn=-3 -DXPRJ_Debug=$(CND_CONF)  --summary=default,+psect,-class,-mem,-hex,-file --fill=0@0x480:0x1FFF --codeoffset=0 --output=default,-inhx032 --runtime=default,-clear,-init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto -Q "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/svc_nvm_blocks.p1  ../svc_nvm_blocks.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/svc_nvm_blocks.d ${OBJECTDIR}/_ext/1472/svc_nvm_blocks.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/svc_nvm_blocks.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/950037222/MRF89XA.p1: ../../LIBC/MRF89_Drv/MRF89XA.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/950037222" 
	@${RM} ${OBJECTDIR}/_ext/950037222/MRF89XA.p1.d 
	@${RM} ${OBJECTDIR}/_ext/950037222/MRF89XA.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --rom=0-7FF --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -DDEBUG -P -N255 -I"../" -I"../../LIBC/MRF89_Drv" -I"../../LIBC/NVM" --warn=-3 -DXPRJ_Debug=$(CND_CONF)  --summary=default,+psect,-class,-mem,-hex,-file --fill=0@0x480:0x1FFF --codeoffset=0 --output=default,-inhx032 --runtime=default,-clear,-init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto -Q "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/950037222/MRF89XA.p1  ../../LIBC/MRF89_Drv/MRF89XA.c 
	@-${MV} ${OBJECTDIR}/_ext/950037222/MRF89XA.d ${OBJECTDIR}/_ext/950037222/MRF89XA.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/950037222/MRF89XA.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/svc_comm.p1: ../svc_comm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/svc_comm.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/svc_comm.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --rom=0-7FF --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -DDEBUG -P -N255 -I"../" -I"../../LIBC/MRF89_Drv" -I"../../LIBC/NVM" --warn=-3 -DXPRJ_Debug=$(CND_CONF)  --summary=default,+psect,-class,-mem,-hex,-file --fill=0@0x480:0x1FFF --codeoffset=0 --output=default,-inhx032 --runtime=default,-clear,-init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto -Q "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/svc_comm.p1  ../svc_comm.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/svc_comm.d ${OBJECTDIR}/_ext/1472/svc_comm.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/svc_comm.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/MRF89XA_Switch.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/MRF89XA_Switch.X.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --rom=0-7FF --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -DDEBUG -P -N255 -I"../" -I"../../LIBC/MRF89_Drv" -I"../../LIBC/NVM" --warn=-3 -DXPRJ_Debug=$(CND_CONF)  --summary=default,+psect,-class,-mem,-hex,-file --fill=0@0x480:0x1FFF --codeoffset=0 --output=default,-inhx032 --runtime=default,-clear,-init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto -Q "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"        $(COMPARISON_BUILD) --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/MRF89XA_Switch.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/MRF89XA_Switch.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/MRF89XA_Switch.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/MRF89XA_Switch.X.${IMAGE_TYPE}.map  --double=24 --float=24 --rom=0-7FF --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -DDEBUG -P -N255 -I"../" -I"../../LIBC/MRF89_Drv" -I"../../LIBC/NVM" --warn=-3 -DXPRJ_Debug=$(CND_CONF)  --summary=default,+psect,-class,-mem,-hex,-file --fill=0@0x480:0x1FFF --codeoffset=0 --output=default,-inhx032 --runtime=default,-clear,-init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto -Q "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     $(COMPARISON_BUILD) --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/MRF89XA_Switch.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} -r dist/Debug

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
