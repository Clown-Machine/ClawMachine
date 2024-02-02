################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
BlueTooth/BluetoothLib/%.obj: ../BlueTooth/BluetoothLib/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/CCS/ccs/tools/compiler/ti-cgt-arm_20.2.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/HUAWEI/Desktop/msp432Library/source" --include_path="C:/CCS/ccs/ccs_base/arm/include" --include_path="C:/CCS/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/HUAWEI/Desktop/bluetooth/Project1" --include_path="C:/CCS/ccs/tools/compiler/ti-cgt-arm_20.2.0.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="BlueTooth/BluetoothLib/$(basename $(<F)).d_raw" --obj_directory="BlueTooth/BluetoothLib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


