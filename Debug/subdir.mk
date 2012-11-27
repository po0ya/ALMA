################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Amatrix.cpp \
../example.cpp \
../mex_ex.cpp 

OBJS += \
./Amatrix.o \
./example.o \
./mex_ex.o 

CPP_DEPS += \
./Amatrix.d \
./example.d \
./mex_ex.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/pooya/MATLAB/extern/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


