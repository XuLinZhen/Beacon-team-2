################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/Control.cpp \
../source/Electric.cpp 

C_SRCS += \
../source/Cpu0_Main.c \
../source/Cpu1_Main.c \
../source/SmartCar_Isr.c \
../source/image.c \
../source/menu.c \
../source/my_math.c 

OBJS += \
./source/Control.o \
./source/Cpu0_Main.o \
./source/Cpu1_Main.o \
./source/Electric.o \
./source/SmartCar_Isr.o \
./source/image.o \
./source/menu.o \
./source/my_math.o 

COMPILED_SRCS += \
./source/Control.src \
./source/Cpu0_Main.src \
./source/Cpu1_Main.src \
./source/Electric.src \
./source/SmartCar_Isr.src \
./source/image.src \
./source/menu.src \
./source/my_math.src 

CPP_DEPS += \
./source/Control.d \
./source/Electric.d 

C_DEPS += \
./source/Cpu0_Main.d \
./source/Cpu1_Main.d \
./source/SmartCar_Isr.d \
./source/image.d \
./source/menu.d \
./source/my_math.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.src: ../source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Infra/Platform/Tricore/Compilers" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Multican/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Infra/Platform" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Cif/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Hssl/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Cpu/Trap" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/If/Ccu6If" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dsadc/Dsadc" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Port" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Stm/Timer" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dts/Dts" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Eth" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Flash" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Vadc" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Msc" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Qspi/SpiMaster" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Scu/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/SysSe/Comm" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/SysSe/Math" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Infra/Platform/Tricore" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Trig" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Tim" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Ccu6/TimerWithTrigger" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Emem" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Mtu" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Infra" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Fft" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/I2c/I2c" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Asclin/Asc" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/SysSe" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Flash/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/If" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Psi5" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Cpu" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Fce/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Stm/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Msc/Msc" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Vadc/Adc" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Asclin" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Tom/Pwm" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Atom" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Port/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Psi5/Psi5" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Eray" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Qspi/SpiSlave" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Ccu6/Icu" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Cpu/CStart" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Hssl" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Cif" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Eth/Phy_Pef7071" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Hssl/Hssl" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Iom/Driver" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Multican/Can" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Psi5s/Psi5s" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Fft/Fft" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Ccu6/PwmHl" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Iom/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/_Lib" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Tom/Timer" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Sent" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Eray/Eray" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gpt12/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dma" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Fce/Crc" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Qspi" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Infra/Sfr" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Infra/Sfr/TC26B" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/SysSe/Bsp" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/SysSe/General" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Cpu/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dts" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Src" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dma/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Cif/Cam" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Src/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Asclin/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/I2c/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Configurations" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/_Lib/DataHandling" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Sent/Sent" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Ccu6/Timer" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Psi5/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Psi5s" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Emem/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Ccu6/PwmBc" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Iom" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Ccu6/TPwm" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Multican" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Mtu/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Infra/Sfr/TC26B/_Reg" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Tom/PwmHl" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dma/Dma" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Atom/Timer" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Ccu6/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/SysSe/Time" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dsadc/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Cpu/Irq" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Ccu6" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gpt12/IncrEnc" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Psi5s/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Scu" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/_Lib/InternalMux" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Stm" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dsadc/Rdc" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Vadc/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dts/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Service" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Eth/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Smu" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/_PinMap" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Asclin/Lin" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/StdIf" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dsadc" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Fce" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Atom/PwmHl" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Qspi/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Tom" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Tim/In" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Msc/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Configurations/Debug" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Fft/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Atom/Pwm" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/_Utilities" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Smu/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/I2c" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/source" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Asclin/Spi" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Eray/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Port/Io" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/_Impl" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Sent/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/SmartCar" --iso=99 --c++14 --language=+volatile --anachronisms --fp-model=3 --fp-model=c --fp-model=f --fp-model=l --fp-model=n --fp-model=r --fp-model=z -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file=$(@:.src=.d) --misrac-version=2012 -N0 -Z0 -Y0 2>&1; sed -i -e '/ctc\\include/d' -e '/Libraries\\iLLD/d' -e '/Libraries\\Infra/d' -e 's/\(.*\)".*\\HITSIC_TC264DA_ADS\(\\.*\)"/\1\.\.\2/g' -e 's/\\/\//g' $(@:.src=.d) && \
	echo $(@:.src=.d) generated
	@echo 'Finished building: $<'
	@echo ' '

source/%.o: ./source/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '

source/%.src: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Infra/Platform/Tricore/Compilers" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Multican/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Infra/Platform" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Cif/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Hssl/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Cpu/Trap" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/If/Ccu6If" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dsadc/Dsadc" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Port" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Stm/Timer" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dts/Dts" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Eth" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Flash" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Vadc" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Msc" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Qspi/SpiMaster" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Scu/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/SysSe/Comm" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/SysSe/Math" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Infra/Platform/Tricore" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Trig" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Tim" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Ccu6/TimerWithTrigger" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Emem" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Mtu" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Infra" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Fft" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/I2c/I2c" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Asclin/Asc" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/SysSe" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Flash/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/If" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Psi5" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Cpu" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Fce/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Stm/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Msc/Msc" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Vadc/Adc" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Asclin" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Tom/Pwm" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Atom" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Port/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Psi5/Psi5" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Eray" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Qspi/SpiSlave" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Ccu6/Icu" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Cpu/CStart" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Hssl" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Cif" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Eth/Phy_Pef7071" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Hssl/Hssl" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Iom/Driver" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Multican/Can" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Psi5s/Psi5s" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Fft/Fft" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Ccu6/PwmHl" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Iom/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/_Lib" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Tom/Timer" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Sent" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Eray/Eray" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gpt12/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dma" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Fce/Crc" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Qspi" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Infra/Sfr" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Infra/Sfr/TC26B" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/SysSe/Bsp" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/SysSe/General" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Cpu/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dts" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Src" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dma/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Cif/Cam" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Src/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Asclin/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/I2c/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Configurations" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/_Lib/DataHandling" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Sent/Sent" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Ccu6/Timer" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Psi5/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Psi5s" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Emem/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Ccu6/PwmBc" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Iom" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Ccu6/TPwm" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Multican" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Mtu/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Infra/Sfr/TC26B/_Reg" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Tom/PwmHl" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dma/Dma" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Atom/Timer" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Ccu6/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/SysSe/Time" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dsadc/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Cpu/Irq" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Ccu6" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gpt12/IncrEnc" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Psi5s/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Scu" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/_Lib/InternalMux" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Stm" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dsadc/Rdc" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Vadc/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dts/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Service" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Eth/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Smu" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/_PinMap" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Asclin/Lin" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/StdIf" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Dsadc" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Fce" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Atom/PwmHl" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Qspi/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Tom" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Tim/In" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Msc/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Configurations/Debug" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Fft/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Atom/Pwm" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/Service/CpuGeneric/_Utilities" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Gtm/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Smu/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/I2c" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/source" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Asclin/Spi" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Eray/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Port/Io" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/_Impl" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/Libraries/iLLD/TC26B/Tricore/Sent/Std" -I"E:/SmartCar/Beacons-2/HITSIC_TC264DA_ADS/SmartCar" --iso=99 --c++14 --language=+volatile --anachronisms --fp-model=3 --fp-model=c --fp-model=f --fp-model=l --fp-model=n --fp-model=r --fp-model=z -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file=$(@:.src=.d) --misrac-version=2012 -N0 -Z0 -Y0 2>&1; sed -i -e '/ctc\\include/d' -e '/Libraries\\iLLD/d' -e '/Libraries\\Infra/d' -e 's/\(.*\)".*\\HITSIC_TC264DA_ADS\(\\.*\)"/\1\.\.\2/g' -e 's/\\/\//g' $(@:.src=.d) && \
	echo $(@:.src=.d) generated
	@echo 'Finished building: $<'
	@echo ' '


