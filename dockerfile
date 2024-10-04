# Use the GCC base image
FROM gcc:latest

# Install CMake
RUN apt-get update && apt-get install -y cmake
RUN apt-get -y install gdb dos2unix

# Set the working directory inside the container
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . .

# Convert all text files in the maps directory to Unix format
RUN dos2unix res/maps/*

# Create a build directory and switch to it
RUN mkdir build
WORKDIR /app/build

# Run CMake to configure the project
RUN cmake ..

# Build the project using Make
RUN make

# Default command to run the compiled binary (assuming binary is named Warzone345)
CMD ["./Warzone345"]

# Instructions:
# Build the Docker image using:
# docker build -t warzone345 .
#
# Example to run a specific test:
# docker run --rm warzone345 ./test1
