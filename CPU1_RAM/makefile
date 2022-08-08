################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./device/device.obj" \
"./device/f28002x_codestartbranch.obj" \
"../28002x_generic_ram_lnk.cmd" \
"C:/ti/C2000Ware_4_01_00_00/driverlib/f28002x/driverlib/ccs/Debug/driverlib.lib" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include device/subdir_vars.mk
-include subdir_rules.mk
-include device/subdir_rules.mk
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
FSM_GSM.out \

EXE_OUTPUTS__QUOTED += \
"FSM_GSM.out" \

BIN_OUTPUTS += \
FSM_GSM.hex \

BIN_OUTPUTS__QUOTED += \
"FSM_GSM.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "FSM_GSM.out"

# Tool invocations
FSM_GSM.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --idiv_support=idiv0 --tmu_support=tmu0 -Ooff --define=DEBUG --define=RAM --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi -z -m"FSM_GSM.map" --heap_size=0x100 --stack_size=0x200 --warn_sections -i"C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/lib" -i"C:/ti/C2000Ware_4_01_00_00" -i"C:/Users/noelp/workspace_v11/FSM_GSM/CPU1_RAM/syscfg" -i"C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" --reread_libs --diag_wrap=off --display_error_number --xml_link_info="FSM_GSM_linkInfo.xml" --entry_point=code_start --rom_model -o "FSM_GSM.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

FSM_GSM.hex: $(EXE_OUTPUTS)
	@echo 'Building secondary target: "$@"'
	@echo 'Invoking: C2000 Hex Utility'
	"C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/hex2000" --diag_wrap=off -o "FSM_GSM.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building secondary target: "$@"'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "device\device.obj" "device\f28002x_codestartbranch.obj" 
	-$(RM) "main.d" "device\device.d" 
	-$(RM) "device\f28002x_codestartbranch.d" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-if 0 == 1  mkdir "C:/Users/noelp/workspace_v11/FSM_GSM/CPU1_RAM/simulation"
	-if 0 == 1  C:/TDM-GCC-64/bin/g++  -c -DCLB_SIM -IC:/ti/C2000Ware_4_01_00_00/utilities/clb_tool/clb_syscfg/systemc-2.3.3/src -IC:/ti/C2000Ware_4_01_00_00/utilities/clb_tool/clb_syscfg/systemc/include/type3 -IC:/Users/noelp/workspace_v11/FSM_GSM -IC:/TDM-GCC-64/bin/include -Og -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MFC:/Users/noelp/workspace_v11/FSM_GSM/CPU1_RAM/simulation/clb_sim.d -MTC:/Users/noelp/workspace_v11/FSM_GSM/CPU1_RAM/simulation/clb_sim.o -IC:/Users/noelp/workspace_v11/FSM_GSM/CPU1_RAM/syscfg   -fno-threadsafe-statics  -oC:/Users/noelp/workspace_v11/FSM_GSM/CPU1_RAM/simulation/clb_sim.o C:/Users/noelp/workspace_v11/FSM_GSM/CPU1_RAM/syscfg/clb_sim.cpp
	-if 0 == 1  C:/TDM-GCC-64/bin/g++ -DCLB_SIM -Og -g -gdwarf-3 -gstrict-dwarf -Wall -Wl,-Map,C:/Users/noelp/workspace_v11/FSM_GSM/CPU1_RAM/simulation/simulation_output.map -LC:/ti/C2000Ware_4_01_00_00/utilities/clb_tool/clb_syscfg/systemc-2.3.3/build/src -oC:/Users/noelp/workspace_v11/FSM_GSM/CPU1_RAM/simulation/simulation_output.exe C:/Users/noelp/workspace_v11/FSM_GSM/CPU1_RAM/simulation/clb_sim.o C:/ti/C2000Ware_4_01_00_00/utilities/clb_tool/clb_syscfg/systemc/src/type3/CLB_FSM_SC_model.o C:/ti/C2000Ware_4_01_00_00/utilities/clb_tool/clb_syscfg/systemc/src/type3/CLB_HLC_SC_model.o C:/ti/C2000Ware_4_01_00_00/utilities/clb_tool/clb_syscfg/systemc/src/type3/CLB_LUT4_SC_model.o C:/ti/C2000Ware_4_01_00_00/utilities/clb_tool/clb_syscfg/systemc/src/type3/CLB_OutputLUT_SC_model.o C:/ti/C2000Ware_4_01_00_00/utilities/clb_tool/clb_syscfg/systemc/src/type3/CLB_counter_SC_model.o C:/ti/C2000Ware_4_01_00_00/utilities/clb_tool/clb_syscfg/systemc/src/type3/CLB_counter_top_SC_model.o C:/ti/C2000Ware_4_01_00_00/utilities/clb_tool/clb_syscfg/systemc/src/type3/CLB_FSM_top_SC_model.o C:/ti/C2000Ware_4_01_00_00/utilities/clb_tool/clb_syscfg/systemc/src/type3/CLB_LUT4_top_SC_model.o C:/ti/C2000Ware_4_01_00_00/utilities/clb_tool/clb_syscfg/systemc/src/type3/CLB_OutputLUT_top_SC_model.o  -Wl,--start-group -lsystemc -Wl,--end-group
	-if 0 == 1  "./simulation/simulation_output.exe"
	-if 0 == 1  C:/ti/ccs1110/ccs/tools/node/node.exe "C:/ti/C2000Ware_4_01_00_00/utilities/clb_tool/clb_syscfg/dot_file_libraries/clbDotUtility.js"  "C:/ti/C2000Ware_4_01_00_00/utilities/clb_tool/clb_syscfg/" "C:/Users/noelp/workspace_v11/FSM_GSM/CPU1_RAM/syscfg" "C:/Users/noelp/workspace_v11/FSM_GSM/CPU1_RAM/syscfg/clb.dot"
	-if 0 == 1  mkdir "C:/Users/noelp/workspace_v11/FSM_GSM/CPU1_RAM/diagrams"
	-if 0 == 1  C:/ti/ccs1110/ccs/tools/node/node.exe "C:/ti/C2000Ware_4_01_00_00/driverlib/.meta/generate_diagrams.js" "C:/ti/C2000Ware_4_01_00_00" "C:/Users/noelp/workspace_v11/FSM_GSM/CPU1_RAM/diagrams" "C:/Users/noelp/workspace_v11/FSM_GSM/CPU1_RAM/syscfg"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

