################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/iLLD/TC26B/Tricore/Port/Io/IfxPort_Io.c 

OBJS += \
./Libraries/iLLD/TC26B/Tricore/Port/Io/IfxPort_Io.o 

COMPILED_SRCS += \
./Libraries/iLLD/TC26B/Tricore/Port/Io/IfxPort_Io.src 

C_DEPS += \
./Libraries/iLLD/TC26B/Tricore/Port/Io/IfxPort_Io.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/iLLD/TC26B/Tricore/Port/Io/%.src: ../Libraries/iLLD/TC26B/Tricore/Port/Io/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/Infra/Platform/Tricore/Compilers" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Multican/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/Infra/Platform" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Cif/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Hssl/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Cpu/Trap" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/If/Ccu6If" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dsadc/Dsadc" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Port" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Stm/Timer" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dts/Dts" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Eth" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Flash" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Vadc" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Msc" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Qspi/SpiMaster" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Scu/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/SysSe/Comm" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/SysSe/Math" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/Infra/Platform/Tricore" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Trig" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Tim" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Ccu6/TimerWithTrigger" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Emem" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Mtu" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/Infra" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Fft" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/I2c/I2c" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Asclin/Asc" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/SysSe" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Flash/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/If" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Psi5" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Cpu" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Fce/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Stm/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Msc/Msc" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Vadc/Adc" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Asclin" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Tom/Pwm" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Atom" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Port/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Psi5/Psi5" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Eray" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Qspi/SpiSlave" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Ccu6/Icu" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Cpu/CStart" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Hssl" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Cif" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Eth/Phy_Pef7071" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Hssl/Hssl" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Iom/Driver" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Multican/Can" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Psi5s/Psi5s" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Fft/Fft" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Ccu6/PwmHl" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Iom/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/_Lib" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Tom/Timer" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Sent" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Eray/Eray" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gpt12/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dma" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Fce/Crc" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Qspi" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/Infra/Sfr" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/Infra/Sfr/TC26B" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/SysSe/Bsp" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/SysSe/General" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Cpu/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dts" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Src" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dma/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Cif/Cam" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Src/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Asclin/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/I2c/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Configurations" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/_Lib/DataHandling" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Sent/Sent" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Ccu6/Timer" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Psi5/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Psi5s" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Emem/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Ccu6/PwmBc" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Iom" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Ccu6/TPwm" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Multican" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Mtu/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/Infra/Sfr/TC26B/_Reg" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Tom/PwmHl" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dma/Dma" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Atom/Timer" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Ccu6/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/SysSe/Time" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dsadc/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Cpu/Irq" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Ccu6" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gpt12/IncrEnc" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Psi5s/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Scu" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/_Lib/InternalMux" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Stm" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dsadc/Rdc" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Vadc/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dts/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/Service" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Eth/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Smu" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/_PinMap" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Asclin/Lin" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/StdIf" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dsadc" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Fce" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Atom/PwmHl" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Qspi/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Tom" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Tim/In" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Msc/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Configurations/Debug" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Fft/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Atom/Pwm" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/_Utilities" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Smu/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/I2c" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/source" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Asclin/Spi" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Eray/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Port/Io" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/_Impl" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Sent/Std" -I"D:/HIT_smartcar/MA_two/HITSIC_TC264DA_ADS/SmartCar" --iso=99 --c++14 --language=+volatile --anachronisms --fp-model=3 --fp-model=c --fp-model=f --fp-model=l --fp-model=n --fp-model=r --fp-model=z -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file=$(@:.src=.d) --misrac-version=2012 -N0 -Z0 -Y0 2>&1; sed -i -e '/ctc\\include/d' -e '/Libraries\\iLLD/d' -e '/Libraries\\Infra/d' -e 's/\(.*\)".*\\HITSIC_TC264DA_ADS\(\\.*\)"/\1\.\.\2/g' -e 's/\\/\//g' $(@:.src=.d) && \
	echo $(@:.src=.d) generated
	@echo 'Finished building: $<'
	@echo ' '

Libraries/iLLD/TC26B/Tricore/Port/Io/%.o: ./Libraries/iLLD/TC26B/Tricore/Port/Io/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


