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
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/FreeRTOS_Port_Test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/FreeRTOS_Port_Test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=FreeRTOS-Kernel/croutine.c FreeRTOS-Kernel/event_groups.c FreeRTOS-Kernel/list.c FreeRTOS-Kernel/queue.c FreeRTOS-Kernel/stream_buffer.c FreeRTOS-Kernel/tasks.c FreeRTOS-Kernel/timers.c newmain.c E:/New/FreeRTOS/Git/FreeRTOS_Practice/Codes/PIC18F_Port_test/FreeRTOS_Port_Test.X/FreeRTOS-Kernel/portable/MPLAB/PIC18F/port.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/FreeRTOS-Kernel/croutine.p1 ${OBJECTDIR}/FreeRTOS-Kernel/event_groups.p1 ${OBJECTDIR}/FreeRTOS-Kernel/list.p1 ${OBJECTDIR}/FreeRTOS-Kernel/queue.p1 ${OBJECTDIR}/FreeRTOS-Kernel/stream_buffer.p1 ${OBJECTDIR}/FreeRTOS-Kernel/tasks.p1 ${OBJECTDIR}/FreeRTOS-Kernel/timers.p1 ${OBJECTDIR}/newmain.p1 ${OBJECTDIR}/_ext/769785779/port.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/FreeRTOS-Kernel/croutine.p1.d ${OBJECTDIR}/FreeRTOS-Kernel/event_groups.p1.d ${OBJECTDIR}/FreeRTOS-Kernel/list.p1.d ${OBJECTDIR}/FreeRTOS-Kernel/queue.p1.d ${OBJECTDIR}/FreeRTOS-Kernel/stream_buffer.p1.d ${OBJECTDIR}/FreeRTOS-Kernel/tasks.p1.d ${OBJECTDIR}/FreeRTOS-Kernel/timers.p1.d ${OBJECTDIR}/newmain.p1.d ${OBJECTDIR}/_ext/769785779/port.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/FreeRTOS-Kernel/croutine.p1 ${OBJECTDIR}/FreeRTOS-Kernel/event_groups.p1 ${OBJECTDIR}/FreeRTOS-Kernel/list.p1 ${OBJECTDIR}/FreeRTOS-Kernel/queue.p1 ${OBJECTDIR}/FreeRTOS-Kernel/stream_buffer.p1 ${OBJECTDIR}/FreeRTOS-Kernel/tasks.p1 ${OBJECTDIR}/FreeRTOS-Kernel/timers.p1 ${OBJECTDIR}/newmain.p1 ${OBJECTDIR}/_ext/769785779/port.p1

# Source Files
SOURCEFILES=FreeRTOS-Kernel/croutine.c FreeRTOS-Kernel/event_groups.c FreeRTOS-Kernel/list.c FreeRTOS-Kernel/queue.c FreeRTOS-Kernel/stream_buffer.c FreeRTOS-Kernel/tasks.c FreeRTOS-Kernel/timers.c newmain.c E:/New/FreeRTOS/Git/FreeRTOS_Practice/Codes/PIC18F_Port_test/FreeRTOS_Port_Test.X/FreeRTOS-Kernel/portable/MPLAB/PIC18F/port.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/FreeRTOS_Port_Test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F45K20
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/FreeRTOS-Kernel/croutine.p1: FreeRTOS-Kernel/croutine.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/FreeRTOS-Kernel" 
	@${RM} ${OBJECTDIR}/FreeRTOS-Kernel/croutine.p1.d 
	@${RM} ${OBJECTDIR}/FreeRTOS-Kernel/croutine.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -D_SERIES=18 -DQUICKCALL=1 -xassembler-with-cpp -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/MPLAB/PIC18F" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/FreeRTOS-Kernel/croutine.p1 FreeRTOS-Kernel/croutine.c 
	@-${MV} ${OBJECTDIR}/FreeRTOS-Kernel/croutine.d ${OBJECTDIR}/FreeRTOS-Kernel/croutine.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/FreeRTOS-Kernel/croutine.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/FreeRTOS-Kernel/event_groups.p1: FreeRTOS-Kernel/event_groups.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/FreeRTOS-Kernel" 
	@${RM} ${OBJECTDIR}/FreeRTOS-Kernel/event_groups.p1.d 
	@${RM} ${OBJECTDIR}/FreeRTOS-Kernel/event_groups.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -D_SERIES=18 -DQUICKCALL=1 -xassembler-with-cpp -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/MPLAB/PIC18F" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/FreeRTOS-Kernel/event_groups.p1 FreeRTOS-Kernel/event_groups.c 
	@-${MV} ${OBJECTDIR}/FreeRTOS-Kernel/event_groups.d ${OBJECTDIR}/FreeRTOS-Kernel/event_groups.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/FreeRTOS-Kernel/event_groups.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/FreeRTOS-Kernel/list.p1: FreeRTOS-Kernel/list.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/FreeRTOS-Kernel" 
	@${RM} ${OBJECTDIR}/FreeRTOS-Kernel/list.p1.d 
	@${RM} ${OBJECTDIR}/FreeRTOS-Kernel/list.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -D_SERIES=18 -DQUICKCALL=1 -xassembler-with-cpp -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/MPLAB/PIC18F" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/FreeRTOS-Kernel/list.p1 FreeRTOS-Kernel/list.c 
	@-${MV} ${OBJECTDIR}/FreeRTOS-Kernel/list.d ${OBJECTDIR}/FreeRTOS-Kernel/list.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/FreeRTOS-Kernel/list.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/FreeRTOS-Kernel/queue.p1: FreeRTOS-Kernel/queue.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/FreeRTOS-Kernel" 
	@${RM} ${OBJECTDIR}/FreeRTOS-Kernel/queue.p1.d 
	@${RM} ${OBJECTDIR}/FreeRTOS-Kernel/queue.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -D_SERIES=18 -DQUICKCALL=1 -xassembler-with-cpp -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/MPLAB/PIC18F" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/FreeRTOS-Kernel/queue.p1 FreeRTOS-Kernel/queue.c 
	@-${MV} ${OBJECTDIR}/FreeRTOS-Kernel/queue.d ${OBJECTDIR}/FreeRTOS-Kernel/queue.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/FreeRTOS-Kernel/queue.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/FreeRTOS-Kernel/stream_buffer.p1: FreeRTOS-Kernel/stream_buffer.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/FreeRTOS-Kernel" 
	@${RM} ${OBJECTDIR}/FreeRTOS-Kernel/stream_buffer.p1.d 
	@${RM} ${OBJECTDIR}/FreeRTOS-Kernel/stream_buffer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -D_SERIES=18 -DQUICKCALL=1 -xassembler-with-cpp -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/MPLAB/PIC18F" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/FreeRTOS-Kernel/stream_buffer.p1 FreeRTOS-Kernel/stream_buffer.c 
	@-${MV} ${OBJECTDIR}/FreeRTOS-Kernel/stream_buffer.d ${OBJECTDIR}/FreeRTOS-Kernel/stream_buffer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/FreeRTOS-Kernel/stream_buffer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/FreeRTOS-Kernel/tasks.p1: FreeRTOS-Kernel/tasks.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/FreeRTOS-Kernel" 
	@${RM} ${OBJECTDIR}/FreeRTOS-Kernel/tasks.p1.d 
	@${RM} ${OBJECTDIR}/FreeRTOS-Kernel/tasks.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -D_SERIES=18 -DQUICKCALL=1 -xassembler-with-cpp -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/MPLAB/PIC18F" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/FreeRTOS-Kernel/tasks.p1 FreeRTOS-Kernel/tasks.c 
	@-${MV} ${OBJECTDIR}/FreeRTOS-Kernel/tasks.d ${OBJECTDIR}/FreeRTOS-Kernel/tasks.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/FreeRTOS-Kernel/tasks.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/FreeRTOS-Kernel/timers.p1: FreeRTOS-Kernel/timers.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/FreeRTOS-Kernel" 
	@${RM} ${OBJECTDIR}/FreeRTOS-Kernel/timers.p1.d 
	@${RM} ${OBJECTDIR}/FreeRTOS-Kernel/timers.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -D_SERIES=18 -DQUICKCALL=1 -xassembler-with-cpp -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/MPLAB/PIC18F" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/FreeRTOS-Kernel/timers.p1 FreeRTOS-Kernel/timers.c 
	@-${MV} ${OBJECTDIR}/FreeRTOS-Kernel/timers.d ${OBJECTDIR}/FreeRTOS-Kernel/timers.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/FreeRTOS-Kernel/timers.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/newmain.p1: newmain.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/newmain.p1.d 
	@${RM} ${OBJECTDIR}/newmain.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -D_SERIES=18 -DQUICKCALL=1 -xassembler-with-cpp -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/MPLAB/PIC18F" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/newmain.p1 newmain.c 
	@-${MV} ${OBJECTDIR}/newmain.d ${OBJECTDIR}/newmain.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/newmain.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/769785779/port.p1: E:/New/FreeRTOS/Git/FreeRTOS_Practice/Codes/PIC18F_Port_test/FreeRTOS_Port_Test.X/FreeRTOS-Kernel/portable/MPLAB/PIC18F/port.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/769785779" 
	@${RM} ${OBJECTDIR}/_ext/769785779/port.p1.d 
	@${RM} ${OBJECTDIR}/_ext/769785779/port.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -D_SERIES=18 -DQUICKCALL=1 -xassembler-with-cpp -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/MPLAB/PIC18F" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/769785779/port.p1 E:/New/FreeRTOS/Git/FreeRTOS_Practice/Codes/PIC18F_Port_test/FreeRTOS_Port_Test.X/FreeRTOS-Kernel/portable/MPLAB/PIC18F/port.c 
	@-${MV} ${OBJECTDIR}/_ext/769785779/port.d ${OBJECTDIR}/_ext/769785779/port.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/769785779/port.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/FreeRTOS-Kernel/croutine.p1: FreeRTOS-Kernel/croutine.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/FreeRTOS-Kernel" 
	@${RM} ${OBJECTDIR}/FreeRTOS-Kernel/croutine.p1.d 
	@${RM} ${OBJECTDIR}/FreeRTOS-Kernel/croutine.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -D_SERIES=18 -DQUICKCALL=1 -xassembler-with-cpp -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/MPLAB/PIC18F" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/FreeRTOS-Kernel/croutine.p1 FreeRTOS-Kernel/croutine.c 
	@-${MV} ${OBJECTDIR}/FreeRTOS-Kernel/croutine.d ${OBJECTDIR}/FreeRTOS-Kernel/croutine.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/FreeRTOS-Kernel/croutine.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/FreeRTOS-Kernel/event_groups.p1: FreeRTOS-Kernel/event_groups.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/FreeRTOS-Kernel" 
	@${RM} ${OBJECTDIR}/FreeRTOS-Kernel/event_groups.p1.d 
	@${RM} ${OBJECTDIR}/FreeRTOS-Kernel/event_groups.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -D_SERIES=18 -DQUICKCALL=1 -xassembler-with-cpp -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/MPLAB/PIC18F" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/FreeRTOS-Kernel/event_groups.p1 FreeRTOS-Kernel/event_groups.c 
	@-${MV} ${OBJECTDIR}/FreeRTOS-Kernel/event_groups.d ${OBJECTDIR}/FreeRTOS-Kernel/event_groups.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/FreeRTOS-Kernel/event_groups.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/FreeRTOS-Kernel/list.p1: FreeRTOS-Kernel/list.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/FreeRTOS-Kernel" 
	@${RM} ${OBJECTDIR}/FreeRTOS-Kernel/list.p1.d 
	@${RM} ${OBJECTDIR}/FreeRTOS-Kernel/list.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -D_SERIES=18 -DQUICKCALL=1 -xassembler-with-cpp -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/MPLAB/PIC18F" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/FreeRTOS-Kernel/list.p1 FreeRTOS-Kernel/list.c 
	@-${MV} ${OBJECTDIR}/FreeRTOS-Kernel/list.d ${OBJECTDIR}/FreeRTOS-Kernel/list.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/FreeRTOS-Kernel/list.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/FreeRTOS-Kernel/queue.p1: FreeRTOS-Kernel/queue.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/FreeRTOS-Kernel" 
	@${RM} ${OBJECTDIR}/FreeRTOS-Kernel/queue.p1.d 
	@${RM} ${OBJECTDIR}/FreeRTOS-Kernel/queue.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -D_SERIES=18 -DQUICKCALL=1 -xassembler-with-cpp -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/MPLAB/PIC18F" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/FreeRTOS-Kernel/queue.p1 FreeRTOS-Kernel/queue.c 
	@-${MV} ${OBJECTDIR}/FreeRTOS-Kernel/queue.d ${OBJECTDIR}/FreeRTOS-Kernel/queue.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/FreeRTOS-Kernel/queue.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/FreeRTOS-Kernel/stream_buffer.p1: FreeRTOS-Kernel/stream_buffer.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/FreeRTOS-Kernel" 
	@${RM} ${OBJECTDIR}/FreeRTOS-Kernel/stream_buffer.p1.d 
	@${RM} ${OBJECTDIR}/FreeRTOS-Kernel/stream_buffer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -D_SERIES=18 -DQUICKCALL=1 -xassembler-with-cpp -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/MPLAB/PIC18F" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/FreeRTOS-Kernel/stream_buffer.p1 FreeRTOS-Kernel/stream_buffer.c 
	@-${MV} ${OBJECTDIR}/FreeRTOS-Kernel/stream_buffer.d ${OBJECTDIR}/FreeRTOS-Kernel/stream_buffer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/FreeRTOS-Kernel/stream_buffer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/FreeRTOS-Kernel/tasks.p1: FreeRTOS-Kernel/tasks.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/FreeRTOS-Kernel" 
	@${RM} ${OBJECTDIR}/FreeRTOS-Kernel/tasks.p1.d 
	@${RM} ${OBJECTDIR}/FreeRTOS-Kernel/tasks.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -D_SERIES=18 -DQUICKCALL=1 -xassembler-with-cpp -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/MPLAB/PIC18F" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/FreeRTOS-Kernel/tasks.p1 FreeRTOS-Kernel/tasks.c 
	@-${MV} ${OBJECTDIR}/FreeRTOS-Kernel/tasks.d ${OBJECTDIR}/FreeRTOS-Kernel/tasks.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/FreeRTOS-Kernel/tasks.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/FreeRTOS-Kernel/timers.p1: FreeRTOS-Kernel/timers.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/FreeRTOS-Kernel" 
	@${RM} ${OBJECTDIR}/FreeRTOS-Kernel/timers.p1.d 
	@${RM} ${OBJECTDIR}/FreeRTOS-Kernel/timers.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -D_SERIES=18 -DQUICKCALL=1 -xassembler-with-cpp -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/MPLAB/PIC18F" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/FreeRTOS-Kernel/timers.p1 FreeRTOS-Kernel/timers.c 
	@-${MV} ${OBJECTDIR}/FreeRTOS-Kernel/timers.d ${OBJECTDIR}/FreeRTOS-Kernel/timers.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/FreeRTOS-Kernel/timers.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/newmain.p1: newmain.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/newmain.p1.d 
	@${RM} ${OBJECTDIR}/newmain.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -D_SERIES=18 -DQUICKCALL=1 -xassembler-with-cpp -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/MPLAB/PIC18F" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/newmain.p1 newmain.c 
	@-${MV} ${OBJECTDIR}/newmain.d ${OBJECTDIR}/newmain.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/newmain.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/769785779/port.p1: E:/New/FreeRTOS/Git/FreeRTOS_Practice/Codes/PIC18F_Port_test/FreeRTOS_Port_Test.X/FreeRTOS-Kernel/portable/MPLAB/PIC18F/port.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/769785779" 
	@${RM} ${OBJECTDIR}/_ext/769785779/port.p1.d 
	@${RM} ${OBJECTDIR}/_ext/769785779/port.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -D_SERIES=18 -DQUICKCALL=1 -xassembler-with-cpp -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/MPLAB/PIC18F" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/769785779/port.p1 E:/New/FreeRTOS/Git/FreeRTOS_Practice/Codes/PIC18F_Port_test/FreeRTOS_Port_Test.X/FreeRTOS-Kernel/portable/MPLAB/PIC18F/port.c 
	@-${MV} ${OBJECTDIR}/_ext/769785779/port.d ${OBJECTDIR}/_ext/769785779/port.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/769785779/port.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

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
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/FreeRTOS_Port_Test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/FreeRTOS_Port_Test.X.${IMAGE_TYPE}.map  -D__DEBUG=1  -mdebugger=none  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -D_SERIES=18 -DQUICKCALL=1 -xassembler-with-cpp -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/MPLAB/PIC18F" -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto        $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/FreeRTOS_Port_Test.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} ${DISTDIR}/FreeRTOS_Port_Test.X.${IMAGE_TYPE}.hex 
	
	
else
${DISTDIR}/FreeRTOS_Port_Test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/FreeRTOS_Port_Test.X.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -D_SERIES=18 -DQUICKCALL=1 -xassembler-with-cpp -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/MPLAB/PIC18F" -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/FreeRTOS_Port_Test.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
