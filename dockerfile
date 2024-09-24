# Use the GCC base image
FROM gcc:latest

# Set the working directory inside the container
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . .

# Compile the main program
RUN g++ main.cpp -o main

# Compile the test files ( examples )
# RUN g++ test1.cpp -o test1
# RUN g++ test2.cpp -o test2

# Set the default command to run the main program
CMD ["./main"]


# Intialize Docker image using: 
# path> docker build -t warzone345 .

# Example to run specific test: 
# path> docker run --rm warzone345 ./test1
