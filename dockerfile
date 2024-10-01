# Use the GCC base image
FROM gcc:latest

# Install CMake, gdb, and dos2unix
RUN apt-get update && \
    apt-get install -y cmake gdb dos2unix

# Set the working directory inside the container
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . .

# Convert all text files in the maps directory
RUN dos2unix res/maps/*

# Create a build directory
RUN mkdir -p build

# Change to the build directory
WORKDIR /app/build

# Run CMake to configure the project
RUN cmake ..

# Build the project
RUN make

# Default command to run the MapDriver executable
CMD ["./MapDriver"]
