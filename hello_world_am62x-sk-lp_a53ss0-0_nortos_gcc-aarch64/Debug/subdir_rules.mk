################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-2098605103: ../example.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/sysconfig_1.20.0/sysconfig_cli.bat" --script "C:/Users/bakra/Desktop/AM625/hello_world_am62x-sk-lp_a53ss0-0_nortos_gcc-aarch64/example.syscfg" -o "syscfg" -s "C:/ti/mcu_plus_sdk_am62x_10_01_00_33/.metadata/product.json" --context "a53ss0-0" --part Default --package AMC --compiler gcc
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_dpl_config.c: build-2098605103 ../example.syscfg
syscfg/ti_dpl_config.h: build-2098605103
syscfg/ti_drivers_config.c: build-2098605103
syscfg/ti_drivers_config.h: build-2098605103
syscfg/ti_drivers_open_close.c: build-2098605103
syscfg/ti_drivers_open_close.h: build-2098605103
syscfg/ti_pinmux_config.c: build-2098605103
syscfg/ti_power_clock_config.c: build-2098605103
syscfg/ti_board_config.c: build-2098605103
syscfg/ti_board_config.h: build-2098605103
syscfg/ti_board_open_close.c: build-2098605103
syscfg/ti_board_open_close.h: build-2098605103
syscfg/ti_enet_config.c: build-2098605103
syscfg/ti_enet_config.h: build-2098605103
syscfg/ti_enet_open_close.c: build-2098605103
syscfg/ti_enet_open_close.h: build-2098605103
syscfg/ti_enet_soc.c: build-2098605103
syscfg/ti_enet_lwipif.c: build-2098605103
syscfg/ti_enet_lwipif.h: build-2098605103
syscfg: build-2098605103

syscfg/%.o: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/gcc-arm-9.2-2019.12-mingw-w64-i686-aarch64-none-elf/bin/aarch64-none-elf-gcc-9.2.1.exe" -c -mcpu=cortex-a53+fp+simd -DSOC_AM62X -DAMP_A53 -D_DEBUG_=1 -I"C:/Users/bakra/Desktop/AM625/hello_world_am62x-sk-lp_a53ss0-0_nortos_gcc-aarch64" -I"C:/ti/mcu_plus_sdk_am62x_10_01_00_33/source" -I"C:/ti/gcc-arm-9.2-2019.12-mingw-w64-i686-aarch64-none-elf/aarch64-none-elf/include" -Og -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -Werror -mabi=lp64 -mcmodel=large -mstrict-align -mfix-cortex-a53-835769 -mfix-cortex-a53-843419 -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast -Wno-unused-but-set-variable -MMD -MP -MF"syscfg/$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/bakra/Desktop/AM625/hello_world_am62x-sk-lp_a53ss0-0_nortos_gcc-aarch64/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/gcc-arm-9.2-2019.12-mingw-w64-i686-aarch64-none-elf/bin/aarch64-none-elf-gcc-9.2.1.exe" -c -mcpu=cortex-a53+fp+simd -DSOC_AM62X -DAMP_A53 -D_DEBUG_=1 -I"C:/Users/bakra/Desktop/AM625/hello_world_am62x-sk-lp_a53ss0-0_nortos_gcc-aarch64" -I"C:/ti/mcu_plus_sdk_am62x_10_01_00_33/source" -I"C:/ti/gcc-arm-9.2-2019.12-mingw-w64-i686-aarch64-none-elf/aarch64-none-elf/include" -Og -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -Werror -mabi=lp64 -mcmodel=large -mstrict-align -mfix-cortex-a53-835769 -mfix-cortex-a53-843419 -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast -Wno-unused-but-set-variable -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/bakra/Desktop/AM625/hello_world_am62x-sk-lp_a53ss0-0_nortos_gcc-aarch64/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


