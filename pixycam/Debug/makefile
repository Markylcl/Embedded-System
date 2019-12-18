################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := E:/ccs.9.1.0/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./Sensor_queue.obj" \
"./cJson.obj" \
"./client.obj" \
"./client_cbs.obj" \
"./syscfg/ti_drivers_net_wifi_config.obj" \
"./syscfg/Board.obj" \
"./debug.obj" \
"./main_freertos.obj" \
"./mqtt_client_app.obj" \
"./network_if.obj" \
"./pixy.obj" \
"./pixy_queue.obj" \
"./timer_queue.obj" \
"./timerthree.obj" \
"./timertwo.obj" \
"./uart_term.obj" \
"../CC3220SF_LAUNCHXL_FREERTOS.cmd" \
$(GEN_CMDS__FLAG) \
-l"ccs/m4/mqtt_release.a" \
-l"ccs/m4/slnetsock_release.a" \
-l"ccs/Release/slnetifwifi.a" \
-l"ti/display/lib/display.aem4" \
-l"ti/grlib/lib/ccs/m4/grlib.a" \
-l"third_party/spiffs/lib/ccs/m4/spiffs.a" \
-l"ti/drivers/lib/drivers_cc32xx.aem4" \
-l"third_party/fatfs/lib/ccs/m4/fatfs.a" \
-l"ccs/rtos/simplelink.a" \
-lfreertos_builds_CC3220SF_LAUNCHXL_release_ccs.lib \
-l"ti/devices/cc32xx/driverlib/ccs/Release/driverlib.a" \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
Milestone3.out \

EXE_OUTPUTS__QUOTED += \
"Milestone3.out" \

BIN_OUTPUTS += \
Milestone3.bin \

BIN_OUTPUTS__QUOTED += \
"Milestone3.bin" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "Milestone3.out"

dependents:
	-cd E:/embedded/m3workspace/Milestone3Team6/freertos_builds_CC3220SF_LAUNCHXL_release_ccs/Debug && $(MAKE) all

# Tool invocations
Milestone3.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS) E:/embedded/m3workspace/Milestone3Team6/freertos_builds_CC3220SF_LAUNCHXL_release_ccs/Debug/freertos_builds_CC3220SF_LAUNCHXL_release_ccs.lib
	@echo 'Building target: "$@"'
	@echo 'Invoking: ARM Linker'
	"E:/ccs.9.1.0/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on -z -m"Milestone3.map" -i"C:/ti/simplelink_cc32xx_sdk_3_20_00_06/source/ti/net/mqtt/lib" -i"C:/ti/simplelink_cc32xx_sdk_3_20_00_06/source/ti/net/lib" -i"C:/ti/simplelink_cc32xx_sdk_3_20_00_06/source/ti/drivers/net/wifi/slnetif" -i"C:/ti/simplelink_cc32xx_sdk_3_20_00_06/source" -i"C:/ti/simplelink_cc32xx_sdk_3_20_00_06/source/ti/drivers/net/wifi" -i"E:/embedded/m3workspace/Milestone3Team6/freertos_builds_CC3220SF_LAUNCHXL_release_ccs/Debug" -i"E:/ccs.9.1.0/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/lib" --diag_suppress=10063 --diag_wrap=off --display_error_number --warn_sections --xml_link_info="Milestone3_linkInfo.xml" --rom_model -o "Milestone3.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

Milestone3.bin: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: ARM Hex Utility'
	"E:/ccs.9.1.0/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/bin/armhex"  -o "Milestone3.bin" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(GEN_MISC_FILES__QUOTED)$(BIN_OUTPUTS__QUOTED)$(GEN_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "Sensor_queue.obj" "cJson.obj" "client.obj" "client_cbs.obj" "syscfg\ti_drivers_net_wifi_config.obj" "syscfg\Board.obj" "debug.obj" "main_freertos.obj" "mqtt_client_app.obj" "network_if.obj" "pixy.obj" "pixy_queue.obj" "timer_queue.obj" "timerthree.obj" "timertwo.obj" "uart_term.obj" 
	-$(RM) "Sensor_queue.d" "cJson.d" "client.d" "client_cbs.d" "syscfg\ti_drivers_net_wifi_config.d" "syscfg\Board.d" "debug.d" "main_freertos.d" "mqtt_client_app.d" "network_if.d" "pixy.d" "pixy_queue.d" "timer_queue.d" "timerthree.d" "timertwo.d" "uart_term.d" 
	-$(RMDIR) $(GEN_MISC_DIRS__QUOTED)
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-E:/ccs.9.1.0/ccs/utils/tiobj2bin/tiobj2bin Milestone3.out Milestone3.bin E:/ccs.9.1.0/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/bin/armofd E:/ccs.9.1.0/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/bin/armhex E:/ccs.9.1.0/ccs/utils/tiobj2bin/mkhex4bin
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
E:/embedded/m3workspace/Milestone3Team6/freertos_builds_CC3220SF_LAUNCHXL_release_ccs/Debug/freertos_builds_CC3220SF_LAUNCHXL_release_ccs.lib:

-include ../makefile.targets

