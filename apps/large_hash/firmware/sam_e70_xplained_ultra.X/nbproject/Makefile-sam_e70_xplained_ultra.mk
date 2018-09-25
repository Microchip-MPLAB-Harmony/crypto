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
ifeq "$(wildcard nbproject/Makefile-local-sam_e70_xplained_ultra.mk)" "nbproject/Makefile-local-sam_e70_xplained_ultra.mk"
include nbproject/Makefile-local-sam_e70_xplained_ultra.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=sam_e70_xplained_ultra
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/sam_e70_xplained_ultra.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/sam_e70_xplained_ultra.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../src/config/default/bsp/bsp.c ../src/config/default/peripheral/clk/plib_clk.c ../src/config/default/peripheral/nvic/plib_nvic.c ../src/config/default/peripheral/pio/plib_pio.c ../src/config/default/peripheral/tc/plib_tc1.c ../src/config/default/peripheral/usart/plib_usart1.c ../src/config/default/stdio/xc32_monitor.c ../src/config/default/system/console/src/sys_console.c ../src/config/default/system/console/src/sys_console_uart.c ../src/config/default/system/console/src/sys_debug.c ../src/config/default/system/int/src/sys_int.c ../src/config/default/system/time/src/sys_time.c ../src/config/default/initialization.c ../src/config/default/interrupts.c ../src/config/default/exceptions.c ../src/config/default/startup.c ../src/config/default/libc_syscalls.c ../src/config/default/tasks.c ../src/config/default/crypto/src/arc4.c ../src/config/default/crypto/src/asm.c ../src/config/default/crypto/src/asn.c ../src/config/default/crypto/src/async.c ../src/config/default/crypto/src/chacha.c ../src/config/default/crypto/src/chacha20_poly1305.c ../src/config/default/crypto/src/cmac.c ../src/config/default/crypto/src/coding.c ../src/config/default/crypto/src/compress.c ../src/config/default/crypto/src/crypto.c ../src/config/default/crypto/src/curve25519.c ../src/config/default/crypto/src/des3.c ../src/config/default/crypto/src/dh.c ../src/config/default/crypto/src/dsa.c ../src/config/default/crypto/src/ecc.c ../src/config/default/crypto/src/ecc_fp.c ../src/config/default/crypto/src/ed25519.c ../src/config/default/crypto/src/error.c ../src/config/default/crypto/src/fe_low_mem.c ../src/config/default/crypto/src/fe_operations.c ../src/config/default/crypto/src/ge_low_mem.c ../src/config/default/crypto/src/ge_operations.c ../src/config/default/crypto/src/hash.c ../src/config/default/crypto/src/hc128.c ../src/config/default/crypto/src/hmac.c ../src/config/default/crypto/src/idea.c ../src/config/default/crypto/src/integer.c ../src/config/default/crypto/src/logging.c ../src/config/default/crypto/src/md2.c ../src/config/default/crypto/src/md4.c ../src/config/default/crypto/src/md5.c ../src/config/default/crypto/src/memory.c ../src/config/default/crypto/src/misc.c ../src/config/default/crypto/src/pkcs12.c ../src/config/default/crypto/src/pkcs7.c ../src/config/default/crypto/src/poly1305.c ../src/config/default/crypto/src/pwdbased.c ../src/config/default/crypto/src/rabbit.c ../src/config/default/crypto/src/ripemd.c ../src/config/default/crypto/src/rsa.c ../src/config/default/crypto/src/sha3.c ../src/config/default/crypto/src/sha512.c ../src/config/default/crypto/src/signature.c ../src/config/default/crypto/src/srp.c ../src/config/default/crypto/src/tfm.c ../src/config/default/crypto/src/wc_encrypt.c ../src/config/default/crypto/src/wc_port.c ../src/config/default/crypto/src/wolfevent.c ../src/config/default/crypto/src/wolfmath.c ../src/config/default/crypto/src/aes_pic32c.c ../src/config/default/crypto/src/sha_pic32c.c ../src/config/default/crypto/src/sha256_pic32c.c ../src/config/default/crypto/src/random_pic32c.c ../src/main.c ../src/app.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1434821282/bsp.o ${OBJECTDIR}/_ext/60165520/plib_clk.o ${OBJECTDIR}/_ext/1865468468/plib_nvic.o ${OBJECTDIR}/_ext/60177924/plib_pio.o ${OBJECTDIR}/_ext/829342655/plib_tc1.o ${OBJECTDIR}/_ext/2001315827/plib_usart1.o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ${OBJECTDIR}/_ext/1832805299/sys_console.o ${OBJECTDIR}/_ext/1832805299/sys_console_uart.o ${OBJECTDIR}/_ext/1832805299/sys_debug.o ${OBJECTDIR}/_ext/1881668453/sys_int.o ${OBJECTDIR}/_ext/101884895/sys_time.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1171490990/startup.o ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o ${OBJECTDIR}/_ext/1171490990/tasks.o ${OBJECTDIR}/_ext/1645245335/arc4.o ${OBJECTDIR}/_ext/1645245335/asm.o ${OBJECTDIR}/_ext/1645245335/asn.o ${OBJECTDIR}/_ext/1645245335/async.o ${OBJECTDIR}/_ext/1645245335/chacha.o ${OBJECTDIR}/_ext/1645245335/chacha20_poly1305.o ${OBJECTDIR}/_ext/1645245335/cmac.o ${OBJECTDIR}/_ext/1645245335/coding.o ${OBJECTDIR}/_ext/1645245335/compress.o ${OBJECTDIR}/_ext/1645245335/crypto.o ${OBJECTDIR}/_ext/1645245335/curve25519.o ${OBJECTDIR}/_ext/1645245335/des3.o ${OBJECTDIR}/_ext/1645245335/dh.o ${OBJECTDIR}/_ext/1645245335/dsa.o ${OBJECTDIR}/_ext/1645245335/ecc.o ${OBJECTDIR}/_ext/1645245335/ecc_fp.o ${OBJECTDIR}/_ext/1645245335/ed25519.o ${OBJECTDIR}/_ext/1645245335/error.o ${OBJECTDIR}/_ext/1645245335/fe_low_mem.o ${OBJECTDIR}/_ext/1645245335/fe_operations.o ${OBJECTDIR}/_ext/1645245335/ge_low_mem.o ${OBJECTDIR}/_ext/1645245335/ge_operations.o ${OBJECTDIR}/_ext/1645245335/hash.o ${OBJECTDIR}/_ext/1645245335/hc128.o ${OBJECTDIR}/_ext/1645245335/hmac.o ${OBJECTDIR}/_ext/1645245335/idea.o ${OBJECTDIR}/_ext/1645245335/integer.o ${OBJECTDIR}/_ext/1645245335/logging.o ${OBJECTDIR}/_ext/1645245335/md2.o ${OBJECTDIR}/_ext/1645245335/md4.o ${OBJECTDIR}/_ext/1645245335/md5.o ${OBJECTDIR}/_ext/1645245335/memory.o ${OBJECTDIR}/_ext/1645245335/misc.o ${OBJECTDIR}/_ext/1645245335/pkcs12.o ${OBJECTDIR}/_ext/1645245335/pkcs7.o ${OBJECTDIR}/_ext/1645245335/poly1305.o ${OBJECTDIR}/_ext/1645245335/pwdbased.o ${OBJECTDIR}/_ext/1645245335/rabbit.o ${OBJECTDIR}/_ext/1645245335/ripemd.o ${OBJECTDIR}/_ext/1645245335/rsa.o ${OBJECTDIR}/_ext/1645245335/sha3.o ${OBJECTDIR}/_ext/1645245335/sha512.o ${OBJECTDIR}/_ext/1645245335/signature.o ${OBJECTDIR}/_ext/1645245335/srp.o ${OBJECTDIR}/_ext/1645245335/tfm.o ${OBJECTDIR}/_ext/1645245335/wc_encrypt.o ${OBJECTDIR}/_ext/1645245335/wc_port.o ${OBJECTDIR}/_ext/1645245335/wolfevent.o ${OBJECTDIR}/_ext/1645245335/wolfmath.o ${OBJECTDIR}/_ext/1645245335/aes_pic32c.o ${OBJECTDIR}/_ext/1645245335/sha_pic32c.o ${OBJECTDIR}/_ext/1645245335/sha256_pic32c.o ${OBJECTDIR}/_ext/1645245335/random_pic32c.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/app.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1434821282/bsp.o.d ${OBJECTDIR}/_ext/60165520/plib_clk.o.d ${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d ${OBJECTDIR}/_ext/60177924/plib_pio.o.d ${OBJECTDIR}/_ext/829342655/plib_tc1.o.d ${OBJECTDIR}/_ext/2001315827/plib_usart1.o.d ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d ${OBJECTDIR}/_ext/1832805299/sys_console.o.d ${OBJECTDIR}/_ext/1832805299/sys_console_uart.o.d ${OBJECTDIR}/_ext/1832805299/sys_debug.o.d ${OBJECTDIR}/_ext/1881668453/sys_int.o.d ${OBJECTDIR}/_ext/101884895/sys_time.o.d ${OBJECTDIR}/_ext/1171490990/initialization.o.d ${OBJECTDIR}/_ext/1171490990/interrupts.o.d ${OBJECTDIR}/_ext/1171490990/exceptions.o.d ${OBJECTDIR}/_ext/1171490990/startup.o.d ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d ${OBJECTDIR}/_ext/1171490990/tasks.o.d ${OBJECTDIR}/_ext/1645245335/arc4.o.d ${OBJECTDIR}/_ext/1645245335/asm.o.d ${OBJECTDIR}/_ext/1645245335/asn.o.d ${OBJECTDIR}/_ext/1645245335/async.o.d ${OBJECTDIR}/_ext/1645245335/chacha.o.d ${OBJECTDIR}/_ext/1645245335/chacha20_poly1305.o.d ${OBJECTDIR}/_ext/1645245335/cmac.o.d ${OBJECTDIR}/_ext/1645245335/coding.o.d ${OBJECTDIR}/_ext/1645245335/compress.o.d ${OBJECTDIR}/_ext/1645245335/crypto.o.d ${OBJECTDIR}/_ext/1645245335/curve25519.o.d ${OBJECTDIR}/_ext/1645245335/des3.o.d ${OBJECTDIR}/_ext/1645245335/dh.o.d ${OBJECTDIR}/_ext/1645245335/dsa.o.d ${OBJECTDIR}/_ext/1645245335/ecc.o.d ${OBJECTDIR}/_ext/1645245335/ecc_fp.o.d ${OBJECTDIR}/_ext/1645245335/ed25519.o.d ${OBJECTDIR}/_ext/1645245335/error.o.d ${OBJECTDIR}/_ext/1645245335/fe_low_mem.o.d ${OBJECTDIR}/_ext/1645245335/fe_operations.o.d ${OBJECTDIR}/_ext/1645245335/ge_low_mem.o.d ${OBJECTDIR}/_ext/1645245335/ge_operations.o.d ${OBJECTDIR}/_ext/1645245335/hash.o.d ${OBJECTDIR}/_ext/1645245335/hc128.o.d ${OBJECTDIR}/_ext/1645245335/hmac.o.d ${OBJECTDIR}/_ext/1645245335/idea.o.d ${OBJECTDIR}/_ext/1645245335/integer.o.d ${OBJECTDIR}/_ext/1645245335/logging.o.d ${OBJECTDIR}/_ext/1645245335/md2.o.d ${OBJECTDIR}/_ext/1645245335/md4.o.d ${OBJECTDIR}/_ext/1645245335/md5.o.d ${OBJECTDIR}/_ext/1645245335/memory.o.d ${OBJECTDIR}/_ext/1645245335/misc.o.d ${OBJECTDIR}/_ext/1645245335/pkcs12.o.d ${OBJECTDIR}/_ext/1645245335/pkcs7.o.d ${OBJECTDIR}/_ext/1645245335/poly1305.o.d ${OBJECTDIR}/_ext/1645245335/pwdbased.o.d ${OBJECTDIR}/_ext/1645245335/rabbit.o.d ${OBJECTDIR}/_ext/1645245335/ripemd.o.d ${OBJECTDIR}/_ext/1645245335/rsa.o.d ${OBJECTDIR}/_ext/1645245335/sha3.o.d ${OBJECTDIR}/_ext/1645245335/sha512.o.d ${OBJECTDIR}/_ext/1645245335/signature.o.d ${OBJECTDIR}/_ext/1645245335/srp.o.d ${OBJECTDIR}/_ext/1645245335/tfm.o.d ${OBJECTDIR}/_ext/1645245335/wc_encrypt.o.d ${OBJECTDIR}/_ext/1645245335/wc_port.o.d ${OBJECTDIR}/_ext/1645245335/wolfevent.o.d ${OBJECTDIR}/_ext/1645245335/wolfmath.o.d ${OBJECTDIR}/_ext/1645245335/aes_pic32c.o.d ${OBJECTDIR}/_ext/1645245335/sha_pic32c.o.d ${OBJECTDIR}/_ext/1645245335/sha256_pic32c.o.d ${OBJECTDIR}/_ext/1645245335/random_pic32c.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/1360937237/app.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1434821282/bsp.o ${OBJECTDIR}/_ext/60165520/plib_clk.o ${OBJECTDIR}/_ext/1865468468/plib_nvic.o ${OBJECTDIR}/_ext/60177924/plib_pio.o ${OBJECTDIR}/_ext/829342655/plib_tc1.o ${OBJECTDIR}/_ext/2001315827/plib_usart1.o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ${OBJECTDIR}/_ext/1832805299/sys_console.o ${OBJECTDIR}/_ext/1832805299/sys_console_uart.o ${OBJECTDIR}/_ext/1832805299/sys_debug.o ${OBJECTDIR}/_ext/1881668453/sys_int.o ${OBJECTDIR}/_ext/101884895/sys_time.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1171490990/startup.o ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o ${OBJECTDIR}/_ext/1171490990/tasks.o ${OBJECTDIR}/_ext/1645245335/arc4.o ${OBJECTDIR}/_ext/1645245335/asm.o ${OBJECTDIR}/_ext/1645245335/asn.o ${OBJECTDIR}/_ext/1645245335/async.o ${OBJECTDIR}/_ext/1645245335/chacha.o ${OBJECTDIR}/_ext/1645245335/chacha20_poly1305.o ${OBJECTDIR}/_ext/1645245335/cmac.o ${OBJECTDIR}/_ext/1645245335/coding.o ${OBJECTDIR}/_ext/1645245335/compress.o ${OBJECTDIR}/_ext/1645245335/crypto.o ${OBJECTDIR}/_ext/1645245335/curve25519.o ${OBJECTDIR}/_ext/1645245335/des3.o ${OBJECTDIR}/_ext/1645245335/dh.o ${OBJECTDIR}/_ext/1645245335/dsa.o ${OBJECTDIR}/_ext/1645245335/ecc.o ${OBJECTDIR}/_ext/1645245335/ecc_fp.o ${OBJECTDIR}/_ext/1645245335/ed25519.o ${OBJECTDIR}/_ext/1645245335/error.o ${OBJECTDIR}/_ext/1645245335/fe_low_mem.o ${OBJECTDIR}/_ext/1645245335/fe_operations.o ${OBJECTDIR}/_ext/1645245335/ge_low_mem.o ${OBJECTDIR}/_ext/1645245335/ge_operations.o ${OBJECTDIR}/_ext/1645245335/hash.o ${OBJECTDIR}/_ext/1645245335/hc128.o ${OBJECTDIR}/_ext/1645245335/hmac.o ${OBJECTDIR}/_ext/1645245335/idea.o ${OBJECTDIR}/_ext/1645245335/integer.o ${OBJECTDIR}/_ext/1645245335/logging.o ${OBJECTDIR}/_ext/1645245335/md2.o ${OBJECTDIR}/_ext/1645245335/md4.o ${OBJECTDIR}/_ext/1645245335/md5.o ${OBJECTDIR}/_ext/1645245335/memory.o ${OBJECTDIR}/_ext/1645245335/misc.o ${OBJECTDIR}/_ext/1645245335/pkcs12.o ${OBJECTDIR}/_ext/1645245335/pkcs7.o ${OBJECTDIR}/_ext/1645245335/poly1305.o ${OBJECTDIR}/_ext/1645245335/pwdbased.o ${OBJECTDIR}/_ext/1645245335/rabbit.o ${OBJECTDIR}/_ext/1645245335/ripemd.o ${OBJECTDIR}/_ext/1645245335/rsa.o ${OBJECTDIR}/_ext/1645245335/sha3.o ${OBJECTDIR}/_ext/1645245335/sha512.o ${OBJECTDIR}/_ext/1645245335/signature.o ${OBJECTDIR}/_ext/1645245335/srp.o ${OBJECTDIR}/_ext/1645245335/tfm.o ${OBJECTDIR}/_ext/1645245335/wc_encrypt.o ${OBJECTDIR}/_ext/1645245335/wc_port.o ${OBJECTDIR}/_ext/1645245335/wolfevent.o ${OBJECTDIR}/_ext/1645245335/wolfmath.o ${OBJECTDIR}/_ext/1645245335/aes_pic32c.o ${OBJECTDIR}/_ext/1645245335/sha_pic32c.o ${OBJECTDIR}/_ext/1645245335/sha256_pic32c.o ${OBJECTDIR}/_ext/1645245335/random_pic32c.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/app.o

# Source Files
SOURCEFILES=../src/config/default/bsp/bsp.c ../src/config/default/peripheral/clk/plib_clk.c ../src/config/default/peripheral/nvic/plib_nvic.c ../src/config/default/peripheral/pio/plib_pio.c ../src/config/default/peripheral/tc/plib_tc1.c ../src/config/default/peripheral/usart/plib_usart1.c ../src/config/default/stdio/xc32_monitor.c ../src/config/default/system/console/src/sys_console.c ../src/config/default/system/console/src/sys_console_uart.c ../src/config/default/system/console/src/sys_debug.c ../src/config/default/system/int/src/sys_int.c ../src/config/default/system/time/src/sys_time.c ../src/config/default/initialization.c ../src/config/default/interrupts.c ../src/config/default/exceptions.c ../src/config/default/startup.c ../src/config/default/libc_syscalls.c ../src/config/default/tasks.c ../src/config/default/crypto/src/arc4.c ../src/config/default/crypto/src/asm.c ../src/config/default/crypto/src/asn.c ../src/config/default/crypto/src/async.c ../src/config/default/crypto/src/chacha.c ../src/config/default/crypto/src/chacha20_poly1305.c ../src/config/default/crypto/src/cmac.c ../src/config/default/crypto/src/coding.c ../src/config/default/crypto/src/compress.c ../src/config/default/crypto/src/crypto.c ../src/config/default/crypto/src/curve25519.c ../src/config/default/crypto/src/des3.c ../src/config/default/crypto/src/dh.c ../src/config/default/crypto/src/dsa.c ../src/config/default/crypto/src/ecc.c ../src/config/default/crypto/src/ecc_fp.c ../src/config/default/crypto/src/ed25519.c ../src/config/default/crypto/src/error.c ../src/config/default/crypto/src/fe_low_mem.c ../src/config/default/crypto/src/fe_operations.c ../src/config/default/crypto/src/ge_low_mem.c ../src/config/default/crypto/src/ge_operations.c ../src/config/default/crypto/src/hash.c ../src/config/default/crypto/src/hc128.c ../src/config/default/crypto/src/hmac.c ../src/config/default/crypto/src/idea.c ../src/config/default/crypto/src/integer.c ../src/config/default/crypto/src/logging.c ../src/config/default/crypto/src/md2.c ../src/config/default/crypto/src/md4.c ../src/config/default/crypto/src/md5.c ../src/config/default/crypto/src/memory.c ../src/config/default/crypto/src/misc.c ../src/config/default/crypto/src/pkcs12.c ../src/config/default/crypto/src/pkcs7.c ../src/config/default/crypto/src/poly1305.c ../src/config/default/crypto/src/pwdbased.c ../src/config/default/crypto/src/rabbit.c ../src/config/default/crypto/src/ripemd.c ../src/config/default/crypto/src/rsa.c ../src/config/default/crypto/src/sha3.c ../src/config/default/crypto/src/sha512.c ../src/config/default/crypto/src/signature.c ../src/config/default/crypto/src/srp.c ../src/config/default/crypto/src/tfm.c ../src/config/default/crypto/src/wc_encrypt.c ../src/config/default/crypto/src/wc_port.c ../src/config/default/crypto/src/wolfevent.c ../src/config/default/crypto/src/wolfmath.c ../src/config/default/crypto/src/aes_pic32c.c ../src/config/default/crypto/src/sha_pic32c.c ../src/config/default/crypto/src/sha256_pic32c.c ../src/config/default/crypto/src/random_pic32c.c ../src/main.c ../src/app.c


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

# The following macros may be used in the pre and post step lines
Device=ATSAME70Q21B
ProjectDir="C:\microchip\harmony\h3\crypto\apps\large_hash\firmware\sam_e70_xplained_ultra.X"
ConfName=sam_e70_xplained_ultra
ImagePath="dist\sam_e70_xplained_ultra\${IMAGE_TYPE}\sam_e70_xplained_ultra.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="dist\sam_e70_xplained_ultra\${IMAGE_TYPE}"
ImageName="sam_e70_xplained_ultra.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-sam_e70_xplained_ultra.mk dist/${CND_CONF}/${IMAGE_TYPE}/sam_e70_xplained_ultra.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
	@echo "--------------------------------------"
	@echo "User defined post-build step: [${MP_CC_DIR}\xc32-objdump -S ${ImageDir}\${PROJECTNAME}.${IMAGE_TYPE}.elf > disassembly.lst]"
	@${MP_CC_DIR}\xc32-objdump -S ${ImageDir}\${PROJECTNAME}.${IMAGE_TYPE}.elf > disassembly.lst
	@echo "--------------------------------------"

MP_PROCESSOR_OPTION=ATSAME70Q21B
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
${OBJECTDIR}/_ext/1434821282/bsp.o: ../src/config/default/bsp/bsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1434821282" 
	@${RM} ${OBJECTDIR}/_ext/1434821282/bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1434821282/bsp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1434821282/bsp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1434821282/bsp.o.d" -o ${OBJECTDIR}/_ext/1434821282/bsp.o ../src/config/default/bsp/bsp.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/60165520/plib_clk.o: ../src/config/default/peripheral/clk/plib_clk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/60165520" 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/60165520/plib_clk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/60165520/plib_clk.o.d" -o ${OBJECTDIR}/_ext/60165520/plib_clk.o ../src/config/default/peripheral/clk/plib_clk.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1865468468/plib_nvic.o: ../src/config/default/peripheral/nvic/plib_nvic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1865468468" 
	@${RM} ${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865468468/plib_nvic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d" -o ${OBJECTDIR}/_ext/1865468468/plib_nvic.o ../src/config/default/peripheral/nvic/plib_nvic.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/60177924/plib_pio.o: ../src/config/default/peripheral/pio/plib_pio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/60177924" 
	@${RM} ${OBJECTDIR}/_ext/60177924/plib_pio.o.d 
	@${RM} ${OBJECTDIR}/_ext/60177924/plib_pio.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/60177924/plib_pio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/60177924/plib_pio.o.d" -o ${OBJECTDIR}/_ext/60177924/plib_pio.o ../src/config/default/peripheral/pio/plib_pio.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/829342655/plib_tc1.o: ../src/config/default/peripheral/tc/plib_tc1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/829342655" 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc1.o.d 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/829342655/plib_tc1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/829342655/plib_tc1.o.d" -o ${OBJECTDIR}/_ext/829342655/plib_tc1.o ../src/config/default/peripheral/tc/plib_tc1.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2001315827/plib_usart1.o: ../src/config/default/peripheral/usart/plib_usart1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2001315827" 
	@${RM} ${OBJECTDIR}/_ext/2001315827/plib_usart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/2001315827/plib_usart1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2001315827/plib_usart1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2001315827/plib_usart1.o.d" -o ${OBJECTDIR}/_ext/2001315827/plib_usart1.o ../src/config/default/peripheral/usart/plib_usart1.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1832805299/sys_console.o: ../src/config/default/system/console/src/sys_console.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1832805299" 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_console.o.d 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_console.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1832805299/sys_console.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1832805299/sys_console.o.d" -o ${OBJECTDIR}/_ext/1832805299/sys_console.o ../src/config/default/system/console/src/sys_console.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1832805299/sys_console_uart.o: ../src/config/default/system/console/src/sys_console_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1832805299" 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_console_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_console_uart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1832805299/sys_console_uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1832805299/sys_console_uart.o.d" -o ${OBJECTDIR}/_ext/1832805299/sys_console_uart.o ../src/config/default/system/console/src/sys_console_uart.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1832805299/sys_debug.o: ../src/config/default/system/console/src/sys_debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1832805299" 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_debug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1832805299/sys_debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1832805299/sys_debug.o.d" -o ${OBJECTDIR}/_ext/1832805299/sys_debug.o ../src/config/default/system/console/src/sys_debug.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1881668453/sys_int.o: ../src/config/default/system/int/src/sys_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1881668453" 
	@${RM} ${OBJECTDIR}/_ext/1881668453/sys_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1881668453/sys_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1881668453/sys_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1881668453/sys_int.o.d" -o ${OBJECTDIR}/_ext/1881668453/sys_int.o ../src/config/default/system/int/src/sys_int.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/101884895/sys_time.o: ../src/config/default/system/time/src/sys_time.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/101884895" 
	@${RM} ${OBJECTDIR}/_ext/101884895/sys_time.o.d 
	@${RM} ${OBJECTDIR}/_ext/101884895/sys_time.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/101884895/sys_time.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/101884895/sys_time.o.d" -o ${OBJECTDIR}/_ext/101884895/sys_time.o ../src/config/default/system/time/src/sys_time.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1171490990/initialization.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1171490990/startup.o: ../src/config/default/startup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/startup.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/startup.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1171490990/startup.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1171490990/startup.o.d" -o ${OBJECTDIR}/_ext/1171490990/startup.o ../src/config/default/startup.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1171490990/libc_syscalls.o: ../src/config/default/libc_syscalls.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d" -o ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o ../src/config/default/libc_syscalls.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1171490990/tasks.o: ../src/config/default/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1171490990/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1171490990/tasks.o.d" -o ${OBJECTDIR}/_ext/1171490990/tasks.o ../src/config/default/tasks.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/arc4.o: ../src/config/default/crypto/src/arc4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/arc4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/arc4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/arc4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/arc4.o.d" -o ${OBJECTDIR}/_ext/1645245335/arc4.o ../src/config/default/crypto/src/arc4.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/asm.o: ../src/config/default/crypto/src/asm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/asm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/asm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/asm.o.d" -o ${OBJECTDIR}/_ext/1645245335/asm.o ../src/config/default/crypto/src/asm.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/asn.o: ../src/config/default/crypto/src/asn.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/asn.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/asn.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/asn.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/asn.o.d" -o ${OBJECTDIR}/_ext/1645245335/asn.o ../src/config/default/crypto/src/asn.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/async.o: ../src/config/default/crypto/src/async.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/async.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/async.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/async.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/async.o.d" -o ${OBJECTDIR}/_ext/1645245335/async.o ../src/config/default/crypto/src/async.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/chacha.o: ../src/config/default/crypto/src/chacha.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/chacha.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/chacha.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/chacha.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/chacha.o.d" -o ${OBJECTDIR}/_ext/1645245335/chacha.o ../src/config/default/crypto/src/chacha.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/chacha20_poly1305.o: ../src/config/default/crypto/src/chacha20_poly1305.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/chacha20_poly1305.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/chacha20_poly1305.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/chacha20_poly1305.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/chacha20_poly1305.o.d" -o ${OBJECTDIR}/_ext/1645245335/chacha20_poly1305.o ../src/config/default/crypto/src/chacha20_poly1305.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/cmac.o: ../src/config/default/crypto/src/cmac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/cmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/cmac.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/cmac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/cmac.o.d" -o ${OBJECTDIR}/_ext/1645245335/cmac.o ../src/config/default/crypto/src/cmac.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/coding.o: ../src/config/default/crypto/src/coding.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/coding.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/coding.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/coding.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/coding.o.d" -o ${OBJECTDIR}/_ext/1645245335/coding.o ../src/config/default/crypto/src/coding.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/compress.o: ../src/config/default/crypto/src/compress.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/compress.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/compress.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/compress.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/compress.o.d" -o ${OBJECTDIR}/_ext/1645245335/compress.o ../src/config/default/crypto/src/compress.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/crypto.o: ../src/config/default/crypto/src/crypto.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/crypto.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/crypto.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/crypto.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/crypto.o.d" -o ${OBJECTDIR}/_ext/1645245335/crypto.o ../src/config/default/crypto/src/crypto.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/curve25519.o: ../src/config/default/crypto/src/curve25519.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/curve25519.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/curve25519.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/curve25519.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/curve25519.o.d" -o ${OBJECTDIR}/_ext/1645245335/curve25519.o ../src/config/default/crypto/src/curve25519.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/des3.o: ../src/config/default/crypto/src/des3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/des3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/des3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/des3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/des3.o.d" -o ${OBJECTDIR}/_ext/1645245335/des3.o ../src/config/default/crypto/src/des3.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/dh.o: ../src/config/default/crypto/src/dh.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/dh.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/dh.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/dh.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/dh.o.d" -o ${OBJECTDIR}/_ext/1645245335/dh.o ../src/config/default/crypto/src/dh.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/dsa.o: ../src/config/default/crypto/src/dsa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/dsa.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/dsa.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/dsa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/dsa.o.d" -o ${OBJECTDIR}/_ext/1645245335/dsa.o ../src/config/default/crypto/src/dsa.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/ecc.o: ../src/config/default/crypto/src/ecc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/ecc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/ecc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/ecc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/ecc.o.d" -o ${OBJECTDIR}/_ext/1645245335/ecc.o ../src/config/default/crypto/src/ecc.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/ecc_fp.o: ../src/config/default/crypto/src/ecc_fp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/ecc_fp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/ecc_fp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/ecc_fp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/ecc_fp.o.d" -o ${OBJECTDIR}/_ext/1645245335/ecc_fp.o ../src/config/default/crypto/src/ecc_fp.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/ed25519.o: ../src/config/default/crypto/src/ed25519.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/ed25519.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/ed25519.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/ed25519.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/ed25519.o.d" -o ${OBJECTDIR}/_ext/1645245335/ed25519.o ../src/config/default/crypto/src/ed25519.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/error.o: ../src/config/default/crypto/src/error.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/error.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/error.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/error.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/error.o.d" -o ${OBJECTDIR}/_ext/1645245335/error.o ../src/config/default/crypto/src/error.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/fe_low_mem.o: ../src/config/default/crypto/src/fe_low_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/fe_low_mem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/fe_low_mem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/fe_low_mem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/fe_low_mem.o.d" -o ${OBJECTDIR}/_ext/1645245335/fe_low_mem.o ../src/config/default/crypto/src/fe_low_mem.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/fe_operations.o: ../src/config/default/crypto/src/fe_operations.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/fe_operations.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/fe_operations.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/fe_operations.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/fe_operations.o.d" -o ${OBJECTDIR}/_ext/1645245335/fe_operations.o ../src/config/default/crypto/src/fe_operations.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/ge_low_mem.o: ../src/config/default/crypto/src/ge_low_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/ge_low_mem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/ge_low_mem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/ge_low_mem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/ge_low_mem.o.d" -o ${OBJECTDIR}/_ext/1645245335/ge_low_mem.o ../src/config/default/crypto/src/ge_low_mem.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/ge_operations.o: ../src/config/default/crypto/src/ge_operations.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/ge_operations.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/ge_operations.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/ge_operations.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/ge_operations.o.d" -o ${OBJECTDIR}/_ext/1645245335/ge_operations.o ../src/config/default/crypto/src/ge_operations.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/hash.o: ../src/config/default/crypto/src/hash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/hash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/hash.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/hash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/hash.o.d" -o ${OBJECTDIR}/_ext/1645245335/hash.o ../src/config/default/crypto/src/hash.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/hc128.o: ../src/config/default/crypto/src/hc128.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/hc128.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/hc128.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/hc128.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/hc128.o.d" -o ${OBJECTDIR}/_ext/1645245335/hc128.o ../src/config/default/crypto/src/hc128.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/hmac.o: ../src/config/default/crypto/src/hmac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/hmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/hmac.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/hmac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/hmac.o.d" -o ${OBJECTDIR}/_ext/1645245335/hmac.o ../src/config/default/crypto/src/hmac.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/idea.o: ../src/config/default/crypto/src/idea.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/idea.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/idea.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/idea.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/idea.o.d" -o ${OBJECTDIR}/_ext/1645245335/idea.o ../src/config/default/crypto/src/idea.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/integer.o: ../src/config/default/crypto/src/integer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/integer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/integer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/integer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/integer.o.d" -o ${OBJECTDIR}/_ext/1645245335/integer.o ../src/config/default/crypto/src/integer.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/logging.o: ../src/config/default/crypto/src/logging.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/logging.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/logging.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/logging.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/logging.o.d" -o ${OBJECTDIR}/_ext/1645245335/logging.o ../src/config/default/crypto/src/logging.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/md2.o: ../src/config/default/crypto/src/md2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/md2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/md2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/md2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/md2.o.d" -o ${OBJECTDIR}/_ext/1645245335/md2.o ../src/config/default/crypto/src/md2.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/md4.o: ../src/config/default/crypto/src/md4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/md4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/md4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/md4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/md4.o.d" -o ${OBJECTDIR}/_ext/1645245335/md4.o ../src/config/default/crypto/src/md4.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/md5.o: ../src/config/default/crypto/src/md5.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/md5.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/md5.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/md5.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/md5.o.d" -o ${OBJECTDIR}/_ext/1645245335/md5.o ../src/config/default/crypto/src/md5.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/memory.o: ../src/config/default/crypto/src/memory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/memory.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/memory.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/memory.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/memory.o.d" -o ${OBJECTDIR}/_ext/1645245335/memory.o ../src/config/default/crypto/src/memory.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/misc.o: ../src/config/default/crypto/src/misc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/misc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/misc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/misc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/misc.o.d" -o ${OBJECTDIR}/_ext/1645245335/misc.o ../src/config/default/crypto/src/misc.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/pkcs12.o: ../src/config/default/crypto/src/pkcs12.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/pkcs12.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/pkcs12.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/pkcs12.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/pkcs12.o.d" -o ${OBJECTDIR}/_ext/1645245335/pkcs12.o ../src/config/default/crypto/src/pkcs12.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/pkcs7.o: ../src/config/default/crypto/src/pkcs7.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/pkcs7.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/pkcs7.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/pkcs7.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/pkcs7.o.d" -o ${OBJECTDIR}/_ext/1645245335/pkcs7.o ../src/config/default/crypto/src/pkcs7.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/poly1305.o: ../src/config/default/crypto/src/poly1305.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/poly1305.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/poly1305.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/poly1305.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/poly1305.o.d" -o ${OBJECTDIR}/_ext/1645245335/poly1305.o ../src/config/default/crypto/src/poly1305.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/pwdbased.o: ../src/config/default/crypto/src/pwdbased.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/pwdbased.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/pwdbased.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/pwdbased.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/pwdbased.o.d" -o ${OBJECTDIR}/_ext/1645245335/pwdbased.o ../src/config/default/crypto/src/pwdbased.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/rabbit.o: ../src/config/default/crypto/src/rabbit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/rabbit.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/rabbit.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/rabbit.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/rabbit.o.d" -o ${OBJECTDIR}/_ext/1645245335/rabbit.o ../src/config/default/crypto/src/rabbit.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/ripemd.o: ../src/config/default/crypto/src/ripemd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/ripemd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/ripemd.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/ripemd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/ripemd.o.d" -o ${OBJECTDIR}/_ext/1645245335/ripemd.o ../src/config/default/crypto/src/ripemd.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/rsa.o: ../src/config/default/crypto/src/rsa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/rsa.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/rsa.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/rsa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/rsa.o.d" -o ${OBJECTDIR}/_ext/1645245335/rsa.o ../src/config/default/crypto/src/rsa.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/sha3.o: ../src/config/default/crypto/src/sha3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/sha3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/sha3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/sha3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/sha3.o.d" -o ${OBJECTDIR}/_ext/1645245335/sha3.o ../src/config/default/crypto/src/sha3.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/sha512.o: ../src/config/default/crypto/src/sha512.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/sha512.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/sha512.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/sha512.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/sha512.o.d" -o ${OBJECTDIR}/_ext/1645245335/sha512.o ../src/config/default/crypto/src/sha512.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/signature.o: ../src/config/default/crypto/src/signature.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/signature.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/signature.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/signature.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/signature.o.d" -o ${OBJECTDIR}/_ext/1645245335/signature.o ../src/config/default/crypto/src/signature.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/srp.o: ../src/config/default/crypto/src/srp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/srp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/srp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/srp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/srp.o.d" -o ${OBJECTDIR}/_ext/1645245335/srp.o ../src/config/default/crypto/src/srp.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/tfm.o: ../src/config/default/crypto/src/tfm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/tfm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/tfm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/tfm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/tfm.o.d" -o ${OBJECTDIR}/_ext/1645245335/tfm.o ../src/config/default/crypto/src/tfm.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/wc_encrypt.o: ../src/config/default/crypto/src/wc_encrypt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/wc_encrypt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/wc_encrypt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/wc_encrypt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/wc_encrypt.o.d" -o ${OBJECTDIR}/_ext/1645245335/wc_encrypt.o ../src/config/default/crypto/src/wc_encrypt.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/wc_port.o: ../src/config/default/crypto/src/wc_port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/wc_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/wc_port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/wc_port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/wc_port.o.d" -o ${OBJECTDIR}/_ext/1645245335/wc_port.o ../src/config/default/crypto/src/wc_port.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/wolfevent.o: ../src/config/default/crypto/src/wolfevent.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/wolfevent.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/wolfevent.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/wolfevent.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/wolfevent.o.d" -o ${OBJECTDIR}/_ext/1645245335/wolfevent.o ../src/config/default/crypto/src/wolfevent.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/wolfmath.o: ../src/config/default/crypto/src/wolfmath.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/wolfmath.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/wolfmath.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/wolfmath.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/wolfmath.o.d" -o ${OBJECTDIR}/_ext/1645245335/wolfmath.o ../src/config/default/crypto/src/wolfmath.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/aes_pic32c.o: ../src/config/default/crypto/src/aes_pic32c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/aes_pic32c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/aes_pic32c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/aes_pic32c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/aes_pic32c.o.d" -o ${OBJECTDIR}/_ext/1645245335/aes_pic32c.o ../src/config/default/crypto/src/aes_pic32c.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/sha_pic32c.o: ../src/config/default/crypto/src/sha_pic32c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/sha_pic32c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/sha_pic32c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/sha_pic32c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/sha_pic32c.o.d" -o ${OBJECTDIR}/_ext/1645245335/sha_pic32c.o ../src/config/default/crypto/src/sha_pic32c.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/sha256_pic32c.o: ../src/config/default/crypto/src/sha256_pic32c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/sha256_pic32c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/sha256_pic32c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/sha256_pic32c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/sha256_pic32c.o.d" -o ${OBJECTDIR}/_ext/1645245335/sha256_pic32c.o ../src/config/default/crypto/src/sha256_pic32c.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/random_pic32c.o: ../src/config/default/crypto/src/random_pic32c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/random_pic32c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/random_pic32c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/random_pic32c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/random_pic32c.o.d" -o ${OBJECTDIR}/_ext/1645245335/random_pic32c.o ../src/config/default/crypto/src/random_pic32c.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/1434821282/bsp.o: ../src/config/default/bsp/bsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1434821282" 
	@${RM} ${OBJECTDIR}/_ext/1434821282/bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1434821282/bsp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1434821282/bsp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1434821282/bsp.o.d" -o ${OBJECTDIR}/_ext/1434821282/bsp.o ../src/config/default/bsp/bsp.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/60165520/plib_clk.o: ../src/config/default/peripheral/clk/plib_clk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/60165520" 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/60165520/plib_clk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/60165520/plib_clk.o.d" -o ${OBJECTDIR}/_ext/60165520/plib_clk.o ../src/config/default/peripheral/clk/plib_clk.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1865468468/plib_nvic.o: ../src/config/default/peripheral/nvic/plib_nvic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1865468468" 
	@${RM} ${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865468468/plib_nvic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d" -o ${OBJECTDIR}/_ext/1865468468/plib_nvic.o ../src/config/default/peripheral/nvic/plib_nvic.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/60177924/plib_pio.o: ../src/config/default/peripheral/pio/plib_pio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/60177924" 
	@${RM} ${OBJECTDIR}/_ext/60177924/plib_pio.o.d 
	@${RM} ${OBJECTDIR}/_ext/60177924/plib_pio.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/60177924/plib_pio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/60177924/plib_pio.o.d" -o ${OBJECTDIR}/_ext/60177924/plib_pio.o ../src/config/default/peripheral/pio/plib_pio.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/829342655/plib_tc1.o: ../src/config/default/peripheral/tc/plib_tc1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/829342655" 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc1.o.d 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/829342655/plib_tc1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/829342655/plib_tc1.o.d" -o ${OBJECTDIR}/_ext/829342655/plib_tc1.o ../src/config/default/peripheral/tc/plib_tc1.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2001315827/plib_usart1.o: ../src/config/default/peripheral/usart/plib_usart1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2001315827" 
	@${RM} ${OBJECTDIR}/_ext/2001315827/plib_usart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/2001315827/plib_usart1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2001315827/plib_usart1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2001315827/plib_usart1.o.d" -o ${OBJECTDIR}/_ext/2001315827/plib_usart1.o ../src/config/default/peripheral/usart/plib_usart1.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1832805299/sys_console.o: ../src/config/default/system/console/src/sys_console.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1832805299" 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_console.o.d 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_console.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1832805299/sys_console.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1832805299/sys_console.o.d" -o ${OBJECTDIR}/_ext/1832805299/sys_console.o ../src/config/default/system/console/src/sys_console.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1832805299/sys_console_uart.o: ../src/config/default/system/console/src/sys_console_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1832805299" 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_console_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_console_uart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1832805299/sys_console_uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1832805299/sys_console_uart.o.d" -o ${OBJECTDIR}/_ext/1832805299/sys_console_uart.o ../src/config/default/system/console/src/sys_console_uart.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1832805299/sys_debug.o: ../src/config/default/system/console/src/sys_debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1832805299" 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1832805299/sys_debug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1832805299/sys_debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1832805299/sys_debug.o.d" -o ${OBJECTDIR}/_ext/1832805299/sys_debug.o ../src/config/default/system/console/src/sys_debug.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1881668453/sys_int.o: ../src/config/default/system/int/src/sys_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1881668453" 
	@${RM} ${OBJECTDIR}/_ext/1881668453/sys_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1881668453/sys_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1881668453/sys_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1881668453/sys_int.o.d" -o ${OBJECTDIR}/_ext/1881668453/sys_int.o ../src/config/default/system/int/src/sys_int.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/101884895/sys_time.o: ../src/config/default/system/time/src/sys_time.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/101884895" 
	@${RM} ${OBJECTDIR}/_ext/101884895/sys_time.o.d 
	@${RM} ${OBJECTDIR}/_ext/101884895/sys_time.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/101884895/sys_time.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/101884895/sys_time.o.d" -o ${OBJECTDIR}/_ext/101884895/sys_time.o ../src/config/default/system/time/src/sys_time.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1171490990/initialization.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1171490990/startup.o: ../src/config/default/startup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/startup.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/startup.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1171490990/startup.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1171490990/startup.o.d" -o ${OBJECTDIR}/_ext/1171490990/startup.o ../src/config/default/startup.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1171490990/libc_syscalls.o: ../src/config/default/libc_syscalls.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d" -o ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o ../src/config/default/libc_syscalls.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1171490990/tasks.o: ../src/config/default/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1171490990/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1171490990/tasks.o.d" -o ${OBJECTDIR}/_ext/1171490990/tasks.o ../src/config/default/tasks.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/arc4.o: ../src/config/default/crypto/src/arc4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/arc4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/arc4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/arc4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/arc4.o.d" -o ${OBJECTDIR}/_ext/1645245335/arc4.o ../src/config/default/crypto/src/arc4.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/asm.o: ../src/config/default/crypto/src/asm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/asm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/asm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/asm.o.d" -o ${OBJECTDIR}/_ext/1645245335/asm.o ../src/config/default/crypto/src/asm.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/asn.o: ../src/config/default/crypto/src/asn.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/asn.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/asn.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/asn.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/asn.o.d" -o ${OBJECTDIR}/_ext/1645245335/asn.o ../src/config/default/crypto/src/asn.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/async.o: ../src/config/default/crypto/src/async.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/async.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/async.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/async.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/async.o.d" -o ${OBJECTDIR}/_ext/1645245335/async.o ../src/config/default/crypto/src/async.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/chacha.o: ../src/config/default/crypto/src/chacha.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/chacha.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/chacha.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/chacha.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/chacha.o.d" -o ${OBJECTDIR}/_ext/1645245335/chacha.o ../src/config/default/crypto/src/chacha.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/chacha20_poly1305.o: ../src/config/default/crypto/src/chacha20_poly1305.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/chacha20_poly1305.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/chacha20_poly1305.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/chacha20_poly1305.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/chacha20_poly1305.o.d" -o ${OBJECTDIR}/_ext/1645245335/chacha20_poly1305.o ../src/config/default/crypto/src/chacha20_poly1305.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/cmac.o: ../src/config/default/crypto/src/cmac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/cmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/cmac.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/cmac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/cmac.o.d" -o ${OBJECTDIR}/_ext/1645245335/cmac.o ../src/config/default/crypto/src/cmac.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/coding.o: ../src/config/default/crypto/src/coding.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/coding.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/coding.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/coding.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/coding.o.d" -o ${OBJECTDIR}/_ext/1645245335/coding.o ../src/config/default/crypto/src/coding.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/compress.o: ../src/config/default/crypto/src/compress.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/compress.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/compress.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/compress.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/compress.o.d" -o ${OBJECTDIR}/_ext/1645245335/compress.o ../src/config/default/crypto/src/compress.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/crypto.o: ../src/config/default/crypto/src/crypto.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/crypto.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/crypto.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/crypto.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/crypto.o.d" -o ${OBJECTDIR}/_ext/1645245335/crypto.o ../src/config/default/crypto/src/crypto.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/curve25519.o: ../src/config/default/crypto/src/curve25519.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/curve25519.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/curve25519.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/curve25519.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/curve25519.o.d" -o ${OBJECTDIR}/_ext/1645245335/curve25519.o ../src/config/default/crypto/src/curve25519.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/des3.o: ../src/config/default/crypto/src/des3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/des3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/des3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/des3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/des3.o.d" -o ${OBJECTDIR}/_ext/1645245335/des3.o ../src/config/default/crypto/src/des3.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/dh.o: ../src/config/default/crypto/src/dh.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/dh.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/dh.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/dh.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/dh.o.d" -o ${OBJECTDIR}/_ext/1645245335/dh.o ../src/config/default/crypto/src/dh.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/dsa.o: ../src/config/default/crypto/src/dsa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/dsa.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/dsa.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/dsa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/dsa.o.d" -o ${OBJECTDIR}/_ext/1645245335/dsa.o ../src/config/default/crypto/src/dsa.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/ecc.o: ../src/config/default/crypto/src/ecc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/ecc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/ecc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/ecc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/ecc.o.d" -o ${OBJECTDIR}/_ext/1645245335/ecc.o ../src/config/default/crypto/src/ecc.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/ecc_fp.o: ../src/config/default/crypto/src/ecc_fp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/ecc_fp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/ecc_fp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/ecc_fp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/ecc_fp.o.d" -o ${OBJECTDIR}/_ext/1645245335/ecc_fp.o ../src/config/default/crypto/src/ecc_fp.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/ed25519.o: ../src/config/default/crypto/src/ed25519.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/ed25519.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/ed25519.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/ed25519.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/ed25519.o.d" -o ${OBJECTDIR}/_ext/1645245335/ed25519.o ../src/config/default/crypto/src/ed25519.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/error.o: ../src/config/default/crypto/src/error.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/error.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/error.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/error.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/error.o.d" -o ${OBJECTDIR}/_ext/1645245335/error.o ../src/config/default/crypto/src/error.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/fe_low_mem.o: ../src/config/default/crypto/src/fe_low_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/fe_low_mem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/fe_low_mem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/fe_low_mem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/fe_low_mem.o.d" -o ${OBJECTDIR}/_ext/1645245335/fe_low_mem.o ../src/config/default/crypto/src/fe_low_mem.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/fe_operations.o: ../src/config/default/crypto/src/fe_operations.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/fe_operations.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/fe_operations.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/fe_operations.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/fe_operations.o.d" -o ${OBJECTDIR}/_ext/1645245335/fe_operations.o ../src/config/default/crypto/src/fe_operations.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/ge_low_mem.o: ../src/config/default/crypto/src/ge_low_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/ge_low_mem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/ge_low_mem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/ge_low_mem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/ge_low_mem.o.d" -o ${OBJECTDIR}/_ext/1645245335/ge_low_mem.o ../src/config/default/crypto/src/ge_low_mem.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/ge_operations.o: ../src/config/default/crypto/src/ge_operations.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/ge_operations.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/ge_operations.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/ge_operations.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/ge_operations.o.d" -o ${OBJECTDIR}/_ext/1645245335/ge_operations.o ../src/config/default/crypto/src/ge_operations.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/hash.o: ../src/config/default/crypto/src/hash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/hash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/hash.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/hash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/hash.o.d" -o ${OBJECTDIR}/_ext/1645245335/hash.o ../src/config/default/crypto/src/hash.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/hc128.o: ../src/config/default/crypto/src/hc128.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/hc128.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/hc128.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/hc128.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/hc128.o.d" -o ${OBJECTDIR}/_ext/1645245335/hc128.o ../src/config/default/crypto/src/hc128.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/hmac.o: ../src/config/default/crypto/src/hmac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/hmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/hmac.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/hmac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/hmac.o.d" -o ${OBJECTDIR}/_ext/1645245335/hmac.o ../src/config/default/crypto/src/hmac.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/idea.o: ../src/config/default/crypto/src/idea.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/idea.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/idea.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/idea.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/idea.o.d" -o ${OBJECTDIR}/_ext/1645245335/idea.o ../src/config/default/crypto/src/idea.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/integer.o: ../src/config/default/crypto/src/integer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/integer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/integer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/integer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/integer.o.d" -o ${OBJECTDIR}/_ext/1645245335/integer.o ../src/config/default/crypto/src/integer.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/logging.o: ../src/config/default/crypto/src/logging.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/logging.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/logging.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/logging.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/logging.o.d" -o ${OBJECTDIR}/_ext/1645245335/logging.o ../src/config/default/crypto/src/logging.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/md2.o: ../src/config/default/crypto/src/md2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/md2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/md2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/md2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/md2.o.d" -o ${OBJECTDIR}/_ext/1645245335/md2.o ../src/config/default/crypto/src/md2.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/md4.o: ../src/config/default/crypto/src/md4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/md4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/md4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/md4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/md4.o.d" -o ${OBJECTDIR}/_ext/1645245335/md4.o ../src/config/default/crypto/src/md4.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/md5.o: ../src/config/default/crypto/src/md5.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/md5.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/md5.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/md5.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/md5.o.d" -o ${OBJECTDIR}/_ext/1645245335/md5.o ../src/config/default/crypto/src/md5.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/memory.o: ../src/config/default/crypto/src/memory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/memory.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/memory.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/memory.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/memory.o.d" -o ${OBJECTDIR}/_ext/1645245335/memory.o ../src/config/default/crypto/src/memory.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/misc.o: ../src/config/default/crypto/src/misc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/misc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/misc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/misc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/misc.o.d" -o ${OBJECTDIR}/_ext/1645245335/misc.o ../src/config/default/crypto/src/misc.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/pkcs12.o: ../src/config/default/crypto/src/pkcs12.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/pkcs12.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/pkcs12.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/pkcs12.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/pkcs12.o.d" -o ${OBJECTDIR}/_ext/1645245335/pkcs12.o ../src/config/default/crypto/src/pkcs12.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/pkcs7.o: ../src/config/default/crypto/src/pkcs7.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/pkcs7.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/pkcs7.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/pkcs7.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/pkcs7.o.d" -o ${OBJECTDIR}/_ext/1645245335/pkcs7.o ../src/config/default/crypto/src/pkcs7.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/poly1305.o: ../src/config/default/crypto/src/poly1305.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/poly1305.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/poly1305.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/poly1305.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/poly1305.o.d" -o ${OBJECTDIR}/_ext/1645245335/poly1305.o ../src/config/default/crypto/src/poly1305.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/pwdbased.o: ../src/config/default/crypto/src/pwdbased.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/pwdbased.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/pwdbased.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/pwdbased.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/pwdbased.o.d" -o ${OBJECTDIR}/_ext/1645245335/pwdbased.o ../src/config/default/crypto/src/pwdbased.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/rabbit.o: ../src/config/default/crypto/src/rabbit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/rabbit.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/rabbit.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/rabbit.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/rabbit.o.d" -o ${OBJECTDIR}/_ext/1645245335/rabbit.o ../src/config/default/crypto/src/rabbit.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/ripemd.o: ../src/config/default/crypto/src/ripemd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/ripemd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/ripemd.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/ripemd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/ripemd.o.d" -o ${OBJECTDIR}/_ext/1645245335/ripemd.o ../src/config/default/crypto/src/ripemd.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/rsa.o: ../src/config/default/crypto/src/rsa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/rsa.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/rsa.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/rsa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/rsa.o.d" -o ${OBJECTDIR}/_ext/1645245335/rsa.o ../src/config/default/crypto/src/rsa.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/sha3.o: ../src/config/default/crypto/src/sha3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/sha3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/sha3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/sha3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/sha3.o.d" -o ${OBJECTDIR}/_ext/1645245335/sha3.o ../src/config/default/crypto/src/sha3.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/sha512.o: ../src/config/default/crypto/src/sha512.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/sha512.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/sha512.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/sha512.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/sha512.o.d" -o ${OBJECTDIR}/_ext/1645245335/sha512.o ../src/config/default/crypto/src/sha512.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/signature.o: ../src/config/default/crypto/src/signature.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/signature.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/signature.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/signature.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/signature.o.d" -o ${OBJECTDIR}/_ext/1645245335/signature.o ../src/config/default/crypto/src/signature.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/srp.o: ../src/config/default/crypto/src/srp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/srp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/srp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/srp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/srp.o.d" -o ${OBJECTDIR}/_ext/1645245335/srp.o ../src/config/default/crypto/src/srp.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/tfm.o: ../src/config/default/crypto/src/tfm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/tfm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/tfm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/tfm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/tfm.o.d" -o ${OBJECTDIR}/_ext/1645245335/tfm.o ../src/config/default/crypto/src/tfm.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/wc_encrypt.o: ../src/config/default/crypto/src/wc_encrypt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/wc_encrypt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/wc_encrypt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/wc_encrypt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/wc_encrypt.o.d" -o ${OBJECTDIR}/_ext/1645245335/wc_encrypt.o ../src/config/default/crypto/src/wc_encrypt.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/wc_port.o: ../src/config/default/crypto/src/wc_port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/wc_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/wc_port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/wc_port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/wc_port.o.d" -o ${OBJECTDIR}/_ext/1645245335/wc_port.o ../src/config/default/crypto/src/wc_port.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/wolfevent.o: ../src/config/default/crypto/src/wolfevent.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/wolfevent.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/wolfevent.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/wolfevent.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/wolfevent.o.d" -o ${OBJECTDIR}/_ext/1645245335/wolfevent.o ../src/config/default/crypto/src/wolfevent.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/wolfmath.o: ../src/config/default/crypto/src/wolfmath.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/wolfmath.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/wolfmath.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/wolfmath.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/wolfmath.o.d" -o ${OBJECTDIR}/_ext/1645245335/wolfmath.o ../src/config/default/crypto/src/wolfmath.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/aes_pic32c.o: ../src/config/default/crypto/src/aes_pic32c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/aes_pic32c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/aes_pic32c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/aes_pic32c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/aes_pic32c.o.d" -o ${OBJECTDIR}/_ext/1645245335/aes_pic32c.o ../src/config/default/crypto/src/aes_pic32c.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/sha_pic32c.o: ../src/config/default/crypto/src/sha_pic32c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/sha_pic32c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/sha_pic32c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/sha_pic32c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/sha_pic32c.o.d" -o ${OBJECTDIR}/_ext/1645245335/sha_pic32c.o ../src/config/default/crypto/src/sha_pic32c.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/sha256_pic32c.o: ../src/config/default/crypto/src/sha256_pic32c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/sha256_pic32c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/sha256_pic32c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/sha256_pic32c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/sha256_pic32c.o.d" -o ${OBJECTDIR}/_ext/1645245335/sha256_pic32c.o ../src/config/default/crypto/src/sha256_pic32c.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1645245335/random_pic32c.o: ../src/config/default/crypto/src/random_pic32c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1645245335" 
	@${RM} ${OBJECTDIR}/_ext/1645245335/random_pic32c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1645245335/random_pic32c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1645245335/random_pic32c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1645245335/random_pic32c.o.d" -o ${OBJECTDIR}/_ext/1645245335/random_pic32c.o ../src/config/default/crypto/src/random_pic32c.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS" -I"../src" -I"../src/config/default" -I"../src/packs/ATSAME70Q21B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/sam_e70_xplained_ultra.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g  -D__MPLAB_DEBUGGER_ICD4=1 -mprocessor=$(MP_PROCESSOR_OPTION) -mno-device-startup-code -o dist/${CND_CONF}/${IMAGE_TYPE}/sam_e70_xplained_ultra.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_ICD4=1,--defsym=_min_heap_size=4096,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/sam_e70_xplained_ultra.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -mno-device-startup-code -o dist/${CND_CONF}/${IMAGE_TYPE}/sam_e70_xplained_ultra.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_sam_e70_xplained_ultra=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=4096,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/sam_e70_xplained_ultra.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/sam_e70_xplained_ultra
	${RM} -r dist/sam_e70_xplained_ultra

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
