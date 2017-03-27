################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LED.c 

CMD_SRCS += \
../Hawk_link.cmd 

OBJS += \
./LED.obj 

C_DEPS += \
./LED.pp 

OBJS__QTD += \
".\LED.obj" 

C_DEPS__QTD += \
".\LED.pp" 

C_SRCS_QUOTED += \
"../LED.c" 


# Each subdirectory must supply rules for building sources it contributes
LED.obj: ../LED.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/tms470/bin/cl470" -mv5e -g --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/tms470/include" --diag_warning=225 -me --code_state=32 --preproc_with_compile --preproc_dependency="LED.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


