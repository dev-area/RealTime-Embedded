################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CFG_SRCS += \
../message_dsp.cfg 

C_SRCS += \
../message_dsp.c 

GEN_SRCS += \
./configPkg/compiler.opt \
./configPkg/linker.cmd 

GEN_CMDS += \
./configPkg/linker.cmd 

OBJS += \
./message_dsp.obj 

C_DEPS += \
./message_dsp.pp 

GEN_MISC_DIRS += \
./configPkg/ 

GEN_OPTS += \
./configPkg/compiler.opt 

OBJS__QTD += \
".\message_dsp.obj" 

GEN_SRCS__QTD += \
".\configPkg\compiler.opt" \
".\configPkg\linker.cmd" 

C_DEPS__QTD += \
".\message_dsp.pp" 

GEN_MISC_DIRS__QTD += \
".\configPkg\" 

C_SRCS_QUOTED += \
"../message_dsp.c" 

CFG_SRCS_QUOTED += \
"../message_dsp.cfg" 

GEN_OPTS_QUOTED += \
--cmd_file="./configPkg/compiler.opt" 

GEN_CMDS_QUOTED += \
-l"./configPkg/linker.cmd" 


# Each subdirectory must supply rules for building sources it contributes
message_dsp.obj: ../message_dsp.c $(GEN_OPTS) $(GEN_SRCS) $(CFG_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c6000/bin/cl6x" -mv6740 -g --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c6000/include" --diag_warning=225 --preproc_with_compile --preproc_dependency="message_dsp.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

configPkg/compiler.opt: ../message_dsp.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"C:/Program Files/Texas Instruments/xdctools_3_20_03_63/xs" --xdcpath="C:/Program Files/Texas Instruments/ipc_1_21_02_23/packages;C:/Program Files/Texas Instruments/bios_6_30_02_42/packages;" xdc.tools.configuro -o configPkg -t ti.targets.C674 -p ti.sdo.ipc.examples.platforms.evmOMAPL138.dsp -r whole_program -c "C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c6000" "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/linker.cmd: configPkg/compiler.opt
configPkg/: configPkg/compiler.opt


