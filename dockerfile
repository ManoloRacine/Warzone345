# Use the GCC base image
FROM gcc:latest

# Install CMake
RUN apt-get update && apt-get install -y cmake
RUN apt-get -y install gdb

# Set the working directory inside the container
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . .

RUN apt-get update && apt-get install -y cmake gdb dos2unix

# Convert all text files in the maps directory
RUN dos2unix res/maps/*

# Create a build directory
RUN mkdir build

# Change to the build directory
WORKDIR /app/build

# Run CMake to configure the project
RUN cmake ..

# Build the project
RUN make

# Compile the test files ( examples )
# RUN g++ test1.cpp -o test1
# RUN g++ test2.cpp -o test2

# Default command to run the compiled binary
CMD ["./Warzone345"]

# Intialize Docker image using: 
# path> docker build -t warzone345 .

# Example to run specific test: 
# path> docker run --rm warzone345 ./test1