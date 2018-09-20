################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/test/Material_test.cpp \
../src/test/test_element.cpp \
../src/test/test_factorial.cpp \
../src/test/test_mesh.cpp \
../src/test/test_node.cpp \
../src/test/test_nodesets.cpp 

OBJS += \
./src/test/Material_test.o \
./src/test/test_element.o \
./src/test/test_factorial.o \
./src/test/test_mesh.o \
./src/test/test_node.o \
./src/test/test_nodesets.o 

CPP_DEPS += \
./src/test/Material_test.d \
./src/test/test_element.d \
./src/test/test_factorial.d \
./src/test/test_mesh.d \
./src/test/test_node.d \
./src/test/test_nodesets.d 


# Each subdirectory must supply rules for building sources it contributes
src/test/%.o: ../src/test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/home/saman/Dropbox/FSDE/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


