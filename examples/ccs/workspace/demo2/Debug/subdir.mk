################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CFG_SRCS += \
../mutex.cfg 

C_SRCS += \
../mutex.c 

GEN_SRCS += \
./configPkg/compiler.opt \
./configPkg/linker.cmd 

GEN_CMDS += \
./configPkg/linker.cmd 

OBJS += \
./mutex.obj 

C_DEPS += \
./mutex.pp 

GEN_MISC_DIRS += \
./configPkg/ 

GEN_OPTS += \
./configPkg/compiler.opt 

OBJS__QTD += \
".\mutex.obj" 

GEN_SRCS__QTD += \
".\configPkg\compiler.opt" \
".\configPkg\linker.cmd" 

C_DEPS__QTD += \
".\mutex.pp" 

GEN_MISC_DIRS__QTD += \
".\configPkg\" 

C_SRCS_QUOTED += \
"../mutex.c" 

CFG_SRCS_QUOTED += \
"../mutex.cfg" 

GEN_OPTS_QUOTED += \
--cmd_file="./configPkg/compiler.opt" 

GEN_CMDS_QUOTED += \
-l"./configPkg/linker.cmd" 


# Each subdirectory must supply rules for building sources it contributes
mutex.obj: ../mutex.c $(GEN_OPTS) $(GEN_SRCS) $(CFG_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/tms470/bin/cl470" -mv5e -g --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/tms470/include" --diag_warning=225 -me --abi=eabi --code_state=32 --preproc_with_compile --preproc_dependency="mutex.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

configPkg/compiler.opt: ../mutex.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"C:/Program Files/Texas Instruments/xdctools_3_20_03_63/xs" --xdcpath="C:/Program Files/Texas Instruments/bios_6_30_02_42/packages;C:/Program Files/Texas Instruments/ipc_1_21_02_23/packages;" xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.Arm9 -p xdc.platform.generic -r whole_program -c "C:/Program Files/Texas Instruments/ccsv4/tools/compiler/tms470" "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/linker.cmd: configPkg/compiler.opt
configPkg/: configPkg/compiler.opt


