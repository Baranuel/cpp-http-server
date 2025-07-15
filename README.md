# Minimal C++ HTTP Server

A beginner-friendly implementation of a basic HTTP server in C++. This project is designed for learning purposes and includes extensive comments explaining every part of the code.

## What This Server Does

This server:
- Listens on port 8080
- Accepts HTTP requests from web browsers
- Responds with a simple HTML page
- Handles one client at a time (single-threaded)
- Demonstrates basic socket programming concepts

## Files in This Project

- `main.cpp` - The main server implementation with detailed comments
- `CMakeLists.txt` - Build configuration for CMake
- `Makefile` - Alternative build configuration for Make
- `README.md` - This documentation file

## Prerequisites

To build and run this server, you need:
- A C++ compiler (g++ recommended)
- Linux/Unix environment (uses POSIX sockets)
- Either CMake or Make build system

### Installing Prerequisites on Ubuntu/Debian
```bash
sudo apt update
sudo apt install build-essential cmake
```

### Installing Prerequisites on CentOS/RHEL
```bash
sudo yum install gcc-c++ cmake make
```

## Building the Server

You can build the server using either CMake or Make:

### Option 1: Using CMake (Recommended)
```bash
# Create a build directory
mkdir build
cd build

# Generate build files
cmake ..

# Build the project
make

# The executable will be named 'server'
```

### Option 2: Using Make
```bash
# Build using the Makefile
make

# The executable will be named 'server'
```

### Option 3: Direct Compilation
```bash
# Compile directly with g++
g++ -Wall -Wextra -std=c++17 -g -O2 main.cpp -o server
```

## Running the Server

After building, run the server:
```bash
./server
```

You should see output like:
```
Starting minimal C++ HTTP server...
Socket created successfully
Socket bound to port 8080
Server listening on port 8080
Server is ready! Visit http://localhost:8080 in your browser
```

## Testing the Server

1. **Using a Web Browser:**
   - Open your browser
   - Navigate to `http://localhost:8080`
   - You should see a simple HTML page

2. **Using curl:**
   ```bash
   curl http://localhost:8080
   ```

3. **Using wget:**
   ```bash
   wget -O - http://localhost:8080
   ```

## Understanding the Code

### Key Concepts Demonstrated

1. **Socket Creation:** Using `socket()` to create a network endpoint
2. **Binding:** Using `bind()` to associate the socket with an address and port
3. **Listening:** Using `listen()` to wait for incoming connections
4. **Accepting:** Using `accept()` to handle client connections
5. **HTTP Protocol:** Basic HTTP request/response format
6. **Resource Management:** Properly closing sockets and cleaning up

### Code Structure

The code is organized into several functions:

- `createSocket()` - Creates a TCP socket
- `bindSocket()` - Binds the socket to port 8080
- `startListening()` - Starts listening for connections
- `handleClient()` - Processes client requests and sends responses
- `main()` - Coordinates the server startup and main loop

### Important Notes for Beginners

1. **Error Handling:** The code includes basic error checking for all socket operations
2. **Comments:** Every line is explained to help you understand what's happening
3. **Simplicity:** This is intentionally minimal - real servers are much more complex
4. **Learning Focus:** Emphasis on understanding rather than performance or features

## Common Issues and Solutions

### Port Already in Use
If you get "Address already in use" error:
```bash
# Find what's using port 8080
sudo lsof -i :8080

# Kill the process (replace PID with actual process ID)
kill -9 PID
```

### Permission Denied
If you get permission errors:
- Make sure you're not trying to use ports below 1024 (requires root)
- Check that your user has permission to create sockets

### Compilation Errors
- Make sure you have a C++ compiler installed
- Ensure you're using C++17 or later standard
- Check that all header files are available

## Next Steps for Learning

After understanding this basic server, you can explore:

1. **Multi-threading:** Handle multiple clients simultaneously
2. **HTTP Parsing:** Properly parse HTTP requests
3. **Routing:** Handle different URLs differently
4. **Static Files:** Serve files from the filesystem
5. **HTTPS:** Add SSL/TLS encryption
6. **Modern C++:** Use libraries like Boost.Beast or cpp-httplib

## Stopping the Server

To stop the server:
- Press `Ctrl+C` in the terminal where it's running
- Or send a SIGTERM signal: `kill PID`

## Cleaning Up

To remove build files:
```bash
# If using CMake
rm -rf build/

# If using Make
make clean
```

## Additional Resources

- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)
- [HTTP/1.1 Specification](https://tools.ietf.org/html/rfc2616)
- [Socket Programming in C++](https://www.geeksforgeeks.org/socket-programming-cc/)

---

**Happy Learning!** 🚀

This server is intentionally simple and designed for educational purposes. For production use, consider established frameworks and libraries that handle security, performance, and protocol compliance properly.
