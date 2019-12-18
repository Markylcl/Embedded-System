################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"E:/ccs.9.1.0/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="E:/embedded/m3workspace/Milestone3Team6/Milestone3" --include_path="E:/embedded/m3workspace/Milestone3Team6/Milestone3/Debug" --include_path="C:/ti/simplelink_cc32xx_sdk_3_20_00_06/source" --include_path="C:/ti/simplelink_cc32xx_sdk_3_20_00_06/source/ti/posix/ccs" --include_path="E:/embedded/FreeRTOSv10.2.1/FreeRTOS/Source/include" --include_path="E:/embedded/FreeRTOSv10.2.1/FreeRTOS/Source/portable/CCS/ARM_CM3" --include_path="E:/embedded/m3workspace/Milestone3Team6/freertos_builds_CC3220SF_LAUNCHXL_release_ccs" --include_path="E:/ccs.9.1.0/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/include" -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="E:/embedded/m3workspace/Milestone3Team6/Milestone3/Debug/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-120502561:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-120502561-inproc

build-120502561-inproc: ../common.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"E:/ccs.9.1.0/ccs/utils/sysconfig/sysconfig_cli.bat" -s "C:/ti/simplelink_cc32xx_sdk_3_20_00_06/.metadata/product.json" -o "syscfg" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_drivers_net_wifi_config.c: build-120502561 ../common.syscfg
syscfg/Board.c: build-120502561
syscfg/Board.h: build-120502561
syscfg/: build-120502561

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"E:/ccs.9.1.0/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="E:/embedded/m3workspace/Milestone3Team6/Milestone3" --include_path="E:/embedded/m3workspace/Milestone3Team6/Milestone3/Debug" --include_path="C:/ti/simplelink_cc32xx_sdk_3_20_00_06/source" --include_path="C:/ti/simplelink_cc32xx_sdk_3_20_00_06/source/ti/posix/ccs" --include_path="E:/embedded/FreeRTOSv10.2.1/FreeRTOS/Source/include" --include_path="E:/embedded/FreeRTOSv10.2.1/FreeRTOS/Source/portable/CCS/ARM_CM3" --include_path="E:/embedded/m3workspace/Milestone3Team6/freertos_builds_CC3220SF_LAUNCHXL_release_ccs" --include_path="E:/ccs.9.1.0/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/include" -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="E:/embedded/m3workspace/Milestone3Team6/Milestone3/Debug/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


