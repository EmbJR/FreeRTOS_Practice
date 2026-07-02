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
FINAL_IMAGE=${DISTDIR}/AVR_FreeRTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/AVR_FreeRTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/GPIO/gpiom2560.c E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/portable/ATmega/port.c E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/portable/MemMang/heap_4.c E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/croutine.c E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/event_groups.c E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/list.c E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/queue.c E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/stream_buffer.c E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/tasks.c E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/timers.c E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/newmain.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/686616193/gpiom2560.o ${OBJECTDIR}/_ext/508962574/port.o ${OBJECTDIR}/_ext/346853003/heap_4.o ${OBJECTDIR}/_ext/739144360/croutine.o ${OBJECTDIR}/_ext/739144360/event_groups.o ${OBJECTDIR}/_ext/739144360/list.o ${OBJECTDIR}/_ext/739144360/queue.o ${OBJECTDIR}/_ext/739144360/stream_buffer.o ${OBJECTDIR}/_ext/739144360/tasks.o ${OBJECTDIR}/_ext/739144360/timers.o ${OBJECTDIR}/_ext/1987829343/newmain.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/686616193/gpiom2560.o.d ${OBJECTDIR}/_ext/508962574/port.o.d ${OBJECTDIR}/_ext/346853003/heap_4.o.d ${OBJECTDIR}/_ext/739144360/croutine.o.d ${OBJECTDIR}/_ext/739144360/event_groups.o.d ${OBJECTDIR}/_ext/739144360/list.o.d ${OBJECTDIR}/_ext/739144360/queue.o.d ${OBJECTDIR}/_ext/739144360/stream_buffer.o.d ${OBJECTDIR}/_ext/739144360/tasks.o.d ${OBJECTDIR}/_ext/739144360/timers.o.d ${OBJECTDIR}/_ext/1987829343/newmain.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/686616193/gpiom2560.o ${OBJECTDIR}/_ext/508962574/port.o ${OBJECTDIR}/_ext/346853003/heap_4.o ${OBJECTDIR}/_ext/739144360/croutine.o ${OBJECTDIR}/_ext/739144360/event_groups.o ${OBJECTDIR}/_ext/739144360/list.o ${OBJECTDIR}/_ext/739144360/queue.o ${OBJECTDIR}/_ext/739144360/stream_buffer.o ${OBJECTDIR}/_ext/739144360/tasks.o ${OBJECTDIR}/_ext/739144360/timers.o ${OBJECTDIR}/_ext/1987829343/newmain.o

# Source Files
SOURCEFILES=E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/GPIO/gpiom2560.c E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/portable/ATmega/port.c E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/portable/MemMang/heap_4.c E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/croutine.c E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/event_groups.c E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/list.c E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/queue.c E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/stream_buffer.c E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/tasks.c E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/timers.c E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/newmain.c

# Pack Options 
PACK_COMPILER_OPTIONS=-I "${DFP_DIR}/include"
PACK_COMMON_OPTIONS=-B "${DFP_DIR}/gcc/dev/atmega2560"



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/AVR_FreeRTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATmega2560
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
${OBJECTDIR}/_ext/686616193/gpiom2560.o: E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/GPIO/gpiom2560.c  .generated_files/flags/default/834356f8661e1a18ae5af808649e9c96a95d5755 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/686616193" 
	@${RM} ${OBJECTDIR}/_ext/686616193/gpiom2560.o.d 
	@${RM} ${OBJECTDIR}/_ext/686616193/gpiom2560.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega2560 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/ATmega" -I"GPIO" -I"Timers" -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/_ext/686616193/gpiom2560.o.d" -MT "${OBJECTDIR}/_ext/686616193/gpiom2560.o.d" -MT ${OBJECTDIR}/_ext/686616193/gpiom2560.o  -o ${OBJECTDIR}/_ext/686616193/gpiom2560.o E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/GPIO/gpiom2560.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/508962574/port.o: E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/portable/ATmega/port.c  .generated_files/flags/default/8b0f128d62ea8ccc8a466552bbac2341ca89545f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/508962574" 
	@${RM} ${OBJECTDIR}/_ext/508962574/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/508962574/port.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega2560 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/ATmega" -I"GPIO" -I"Timers" -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/_ext/508962574/port.o.d" -MT "${OBJECTDIR}/_ext/508962574/port.o.d" -MT ${OBJECTDIR}/_ext/508962574/port.o  -o ${OBJECTDIR}/_ext/508962574/port.o E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/portable/ATmega/port.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/346853003/heap_4.o: E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/portable/MemMang/heap_4.c  .generated_files/flags/default/dfe03b4f71427e8b9cad4a1f86fdb09aa7b0332e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/346853003" 
	@${RM} ${OBJECTDIR}/_ext/346853003/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/346853003/heap_4.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega2560 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/ATmega" -I"GPIO" -I"Timers" -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/_ext/346853003/heap_4.o.d" -MT "${OBJECTDIR}/_ext/346853003/heap_4.o.d" -MT ${OBJECTDIR}/_ext/346853003/heap_4.o  -o ${OBJECTDIR}/_ext/346853003/heap_4.o E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/portable/MemMang/heap_4.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/739144360/croutine.o: E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/croutine.c  .generated_files/flags/default/d8f7447b2a3e4265bbfd70e1bc6ef9dcc027854 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/739144360" 
	@${RM} ${OBJECTDIR}/_ext/739144360/croutine.o.d 
	@${RM} ${OBJECTDIR}/_ext/739144360/croutine.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega2560 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/ATmega" -I"GPIO" -I"Timers" -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/_ext/739144360/croutine.o.d" -MT "${OBJECTDIR}/_ext/739144360/croutine.o.d" -MT ${OBJECTDIR}/_ext/739144360/croutine.o  -o ${OBJECTDIR}/_ext/739144360/croutine.o E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/croutine.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/739144360/event_groups.o: E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/event_groups.c  .generated_files/flags/default/cf8f8ec2a1cf51f9ae300f53fffc0b9c77627a4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/739144360" 
	@${RM} ${OBJECTDIR}/_ext/739144360/event_groups.o.d 
	@${RM} ${OBJECTDIR}/_ext/739144360/event_groups.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega2560 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/ATmega" -I"GPIO" -I"Timers" -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/_ext/739144360/event_groups.o.d" -MT "${OBJECTDIR}/_ext/739144360/event_groups.o.d" -MT ${OBJECTDIR}/_ext/739144360/event_groups.o  -o ${OBJECTDIR}/_ext/739144360/event_groups.o E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/event_groups.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/739144360/list.o: E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/list.c  .generated_files/flags/default/87699d1ce498443aa94413dfd757501cab3d962 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/739144360" 
	@${RM} ${OBJECTDIR}/_ext/739144360/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/739144360/list.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega2560 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/ATmega" -I"GPIO" -I"Timers" -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/_ext/739144360/list.o.d" -MT "${OBJECTDIR}/_ext/739144360/list.o.d" -MT ${OBJECTDIR}/_ext/739144360/list.o  -o ${OBJECTDIR}/_ext/739144360/list.o E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/list.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/739144360/queue.o: E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/queue.c  .generated_files/flags/default/b4d78a2feed496330c2bff3512eb0bf6d4aa43ff .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/739144360" 
	@${RM} ${OBJECTDIR}/_ext/739144360/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/739144360/queue.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega2560 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/ATmega" -I"GPIO" -I"Timers" -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/_ext/739144360/queue.o.d" -MT "${OBJECTDIR}/_ext/739144360/queue.o.d" -MT ${OBJECTDIR}/_ext/739144360/queue.o  -o ${OBJECTDIR}/_ext/739144360/queue.o E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/queue.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/739144360/stream_buffer.o: E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/stream_buffer.c  .generated_files/flags/default/b0112860b6e39c46a14cd701bc2f99a9486c1edc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/739144360" 
	@${RM} ${OBJECTDIR}/_ext/739144360/stream_buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/739144360/stream_buffer.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega2560 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/ATmega" -I"GPIO" -I"Timers" -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/_ext/739144360/stream_buffer.o.d" -MT "${OBJECTDIR}/_ext/739144360/stream_buffer.o.d" -MT ${OBJECTDIR}/_ext/739144360/stream_buffer.o  -o ${OBJECTDIR}/_ext/739144360/stream_buffer.o E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/stream_buffer.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/739144360/tasks.o: E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/tasks.c  .generated_files/flags/default/5bcb535dca70fa60ec5e8a604c7429a32431c990 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/739144360" 
	@${RM} ${OBJECTDIR}/_ext/739144360/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/739144360/tasks.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega2560 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/ATmega" -I"GPIO" -I"Timers" -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/_ext/739144360/tasks.o.d" -MT "${OBJECTDIR}/_ext/739144360/tasks.o.d" -MT ${OBJECTDIR}/_ext/739144360/tasks.o  -o ${OBJECTDIR}/_ext/739144360/tasks.o E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/tasks.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/739144360/timers.o: E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/timers.c  .generated_files/flags/default/25a7ba9eb33b1f88bfaf8b573b0abf78779c9ea2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/739144360" 
	@${RM} ${OBJECTDIR}/_ext/739144360/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/739144360/timers.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega2560 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/ATmega" -I"GPIO" -I"Timers" -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/_ext/739144360/timers.o.d" -MT "${OBJECTDIR}/_ext/739144360/timers.o.d" -MT ${OBJECTDIR}/_ext/739144360/timers.o  -o ${OBJECTDIR}/_ext/739144360/timers.o E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/timers.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1987829343/newmain.o: E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/newmain.c  .generated_files/flags/default/6c387b1a3dac0c9ab4153cb214e8002ff3c67ad .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1987829343" 
	@${RM} ${OBJECTDIR}/_ext/1987829343/newmain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1987829343/newmain.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega2560 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/ATmega" -I"GPIO" -I"Timers" -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1987829343/newmain.o.d" -MT "${OBJECTDIR}/_ext/1987829343/newmain.o.d" -MT ${OBJECTDIR}/_ext/1987829343/newmain.o  -o ${OBJECTDIR}/_ext/1987829343/newmain.o E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/newmain.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/686616193/gpiom2560.o: E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/GPIO/gpiom2560.c  .generated_files/flags/default/cba8dd32eac2e3d9d0e7897a98c8181a0eced825 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/686616193" 
	@${RM} ${OBJECTDIR}/_ext/686616193/gpiom2560.o.d 
	@${RM} ${OBJECTDIR}/_ext/686616193/gpiom2560.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega2560 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/ATmega" -I"GPIO" -I"Timers" -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/_ext/686616193/gpiom2560.o.d" -MT "${OBJECTDIR}/_ext/686616193/gpiom2560.o.d" -MT ${OBJECTDIR}/_ext/686616193/gpiom2560.o  -o ${OBJECTDIR}/_ext/686616193/gpiom2560.o E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/GPIO/gpiom2560.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/508962574/port.o: E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/portable/ATmega/port.c  .generated_files/flags/default/d451473cd3129fb6574bcc89b7bcd89f658e0dc7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/508962574" 
	@${RM} ${OBJECTDIR}/_ext/508962574/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/508962574/port.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega2560 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/ATmega" -I"GPIO" -I"Timers" -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/_ext/508962574/port.o.d" -MT "${OBJECTDIR}/_ext/508962574/port.o.d" -MT ${OBJECTDIR}/_ext/508962574/port.o  -o ${OBJECTDIR}/_ext/508962574/port.o E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/portable/ATmega/port.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/346853003/heap_4.o: E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/portable/MemMang/heap_4.c  .generated_files/flags/default/25d3eafeeec4f7b38959cfe9eebb55a3e7cef481 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/346853003" 
	@${RM} ${OBJECTDIR}/_ext/346853003/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/346853003/heap_4.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega2560 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/ATmega" -I"GPIO" -I"Timers" -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/_ext/346853003/heap_4.o.d" -MT "${OBJECTDIR}/_ext/346853003/heap_4.o.d" -MT ${OBJECTDIR}/_ext/346853003/heap_4.o  -o ${OBJECTDIR}/_ext/346853003/heap_4.o E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/portable/MemMang/heap_4.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/739144360/croutine.o: E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/croutine.c  .generated_files/flags/default/1b31d8ae8d7f82b740028b9788e9bd92514af6b0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/739144360" 
	@${RM} ${OBJECTDIR}/_ext/739144360/croutine.o.d 
	@${RM} ${OBJECTDIR}/_ext/739144360/croutine.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega2560 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/ATmega" -I"GPIO" -I"Timers" -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/_ext/739144360/croutine.o.d" -MT "${OBJECTDIR}/_ext/739144360/croutine.o.d" -MT ${OBJECTDIR}/_ext/739144360/croutine.o  -o ${OBJECTDIR}/_ext/739144360/croutine.o E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/croutine.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/739144360/event_groups.o: E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/event_groups.c  .generated_files/flags/default/3681313e9facb4de5c797626ef78c275e81c5259 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/739144360" 
	@${RM} ${OBJECTDIR}/_ext/739144360/event_groups.o.d 
	@${RM} ${OBJECTDIR}/_ext/739144360/event_groups.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega2560 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/ATmega" -I"GPIO" -I"Timers" -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/_ext/739144360/event_groups.o.d" -MT "${OBJECTDIR}/_ext/739144360/event_groups.o.d" -MT ${OBJECTDIR}/_ext/739144360/event_groups.o  -o ${OBJECTDIR}/_ext/739144360/event_groups.o E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/event_groups.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/739144360/list.o: E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/list.c  .generated_files/flags/default/52bd304c07e20810ec271a85cb8031e48ed3bf4a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/739144360" 
	@${RM} ${OBJECTDIR}/_ext/739144360/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/739144360/list.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega2560 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/ATmega" -I"GPIO" -I"Timers" -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/_ext/739144360/list.o.d" -MT "${OBJECTDIR}/_ext/739144360/list.o.d" -MT ${OBJECTDIR}/_ext/739144360/list.o  -o ${OBJECTDIR}/_ext/739144360/list.o E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/list.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/739144360/queue.o: E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/queue.c  .generated_files/flags/default/e860243756f9277758da55acbd64eae6221a5b2d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/739144360" 
	@${RM} ${OBJECTDIR}/_ext/739144360/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/739144360/queue.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega2560 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/ATmega" -I"GPIO" -I"Timers" -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/_ext/739144360/queue.o.d" -MT "${OBJECTDIR}/_ext/739144360/queue.o.d" -MT ${OBJECTDIR}/_ext/739144360/queue.o  -o ${OBJECTDIR}/_ext/739144360/queue.o E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/queue.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/739144360/stream_buffer.o: E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/stream_buffer.c  .generated_files/flags/default/54bdef35b41414225604bd735e76571edbfb613f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/739144360" 
	@${RM} ${OBJECTDIR}/_ext/739144360/stream_buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/739144360/stream_buffer.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega2560 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/ATmega" -I"GPIO" -I"Timers" -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/_ext/739144360/stream_buffer.o.d" -MT "${OBJECTDIR}/_ext/739144360/stream_buffer.o.d" -MT ${OBJECTDIR}/_ext/739144360/stream_buffer.o  -o ${OBJECTDIR}/_ext/739144360/stream_buffer.o E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/stream_buffer.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/739144360/tasks.o: E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/tasks.c  .generated_files/flags/default/fc600e8e12d9511d5a36366019c1431277ff8b7f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/739144360" 
	@${RM} ${OBJECTDIR}/_ext/739144360/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/739144360/tasks.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega2560 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/ATmega" -I"GPIO" -I"Timers" -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/_ext/739144360/tasks.o.d" -MT "${OBJECTDIR}/_ext/739144360/tasks.o.d" -MT ${OBJECTDIR}/_ext/739144360/tasks.o  -o ${OBJECTDIR}/_ext/739144360/tasks.o E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/tasks.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/739144360/timers.o: E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/timers.c  .generated_files/flags/default/806becc59c08cd2e741ead6be79fb78e4e9fd6cf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/739144360" 
	@${RM} ${OBJECTDIR}/_ext/739144360/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/739144360/timers.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega2560 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/ATmega" -I"GPIO" -I"Timers" -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/_ext/739144360/timers.o.d" -MT "${OBJECTDIR}/_ext/739144360/timers.o.d" -MT ${OBJECTDIR}/_ext/739144360/timers.o  -o ${OBJECTDIR}/_ext/739144360/timers.o E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/FreeRTOS-Kernel/timers.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1987829343/newmain.o: E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/newmain.c  .generated_files/flags/default/31c53aedce4cacb7c7aa6c1701367a53fdb7f486 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1987829343" 
	@${RM} ${OBJECTDIR}/_ext/1987829343/newmain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1987829343/newmain.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega2560 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"FreeRTOS-Kernel/include" -I"FreeRTOS-Kernel/portable/ATmega" -I"GPIO" -I"Timers" -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1987829343/newmain.o.d" -MT "${OBJECTDIR}/_ext/1987829343/newmain.o.d" -MT ${OBJECTDIR}/_ext/1987829343/newmain.o  -o ${OBJECTDIR}/_ext/1987829343/newmain.o E:/New/Microcontrollers/AVR/Git/AVR_Practice/FreeRTOS_Port/AVR_FreeRTOS.X/newmain.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/AVR_FreeRTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=atmega2560 ${PACK_COMMON_OPTIONS}   -gdwarf-2 -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="${DISTDIR}\AVR_FreeRTOS.X.${IMAGE_TYPE}.map"    -o ${DISTDIR}/AVR_FreeRTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1 -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	
	
	
	
	
	
else
${DISTDIR}/AVR_FreeRTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=atmega2560 ${PACK_COMMON_OPTIONS}  -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="${DISTDIR}\AVR_FreeRTOS.X.${IMAGE_TYPE}.map"    -o ${DISTDIR}/AVR_FreeRTOS.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION) -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}\\avr-objcopy -O ihex "${DISTDIR}/AVR_FreeRTOS.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "${DISTDIR}/AVR_FreeRTOS.X.${IMAGE_TYPE}.hex"
	
	
	
	
	
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
