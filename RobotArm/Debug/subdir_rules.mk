################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/Users/Mark6/Desktop/Embedded/Arm/RobotArm" --include_path="C:/Users/Mark6/Desktop/Embedded/Arm/RobotArm/Debug" --include_path="C:/ti/simplelink_cc32xx_sdk_3_20_00_06/source" --include_path="C:/ti/simplelink_cc32xx_sdk_3_20_00_06/source/ti/posix/ccs" --include_path="C:/freertos-code-r2717-trunk/FreeRTOS/Source/include" --include_path="C:/freertos-code-r2717-trunk/FreeRTOS/Source/portable/CCS/ARM_CM3" --include_path="C:/Users/Mark6/Desktop/Embedded/Arm/freertos_builds_CC3220SF_LAUNCHXL_release_ccs" --include_path="C:/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/include" -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/Mark6/Desktop/Embedded/Arm/RobotArm/Debug/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1379846735:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-1379846735-inproc

build-1379846735-inproc: ../pwmled2.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs910/ccs/utils/sysconfig/sysconfig_cli.bat" -s "C:/ti/simplelink_cc32xx_sdk_3_20_00_06/.metadata/product.json" -o "syscfg" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_drivers_net_wifi_config.c: build-1379846735 ../pwmled2.syscfg
syscfg/Board.c: build-1379846735
syscfg/Board.h: build-1379846735
syscfg/: build-1379846735

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/Users/Mark6/Desktop/Embedded/Arm/RobotArm" --include_path="C:/Users/Mark6/Desktop/Embedded/Arm/RobotArm/Debug" --include_path="C:/ti/simplelink_cc32xx_sdk_3_20_00_06/source" --include_path="C:/ti/simplelink_cc32xx_sdk_3_20_00_06/source/ti/posix/ccs" --include_path="C:/freertos-code-r2717-trunk/FreeRTOS/Source/include" --include_path="C:/freertos-code-r2717-trunk/FreeRTOS/Source/portable/CCS/ARM_CM3" --include_path="C:/Users/Mark6/Desktop/Embedded/Arm/freertos_builds_CC3220SF_LAUNCHXL_release_ccs" --include_path="C:/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/include" -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/Mark6/Desktop/Embedded/Arm/RobotArm/Debug/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


