################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Edge.cpp \
../src/Element.cpp \
../src/FSDE.cpp \
../src/Material.cpp \
../src/Mesh.cpp \
../src/Node.cpp \
../src/Nodesets.cpp \
../src/ShapeFunction.cpp \
../src/SolidElement.cpp \
../src/factorial.cpp 

OBJS += \
./src/Edge.o \
./src/Element.o \
./src/FSDE.o \
./src/Material.o \
./src/Mesh.o \
./src/Node.o \
./src/Nodesets.o \
./src/ShapeFunction.o \
./src/SolidElement.o \
./src/factorial.o 

CPP_DEPS += \
./src/Edge.d \
./src/Element.d \
./src/FSDE.d \
./src/Material.d \
./src/Mesh.d \
./src/Node.d \
./src/Nodesets.d \
./src/ShapeFunction.d \
./src/SolidElement.d \
./src/factorial.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/home/saman/Dropbox/FSDE/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


