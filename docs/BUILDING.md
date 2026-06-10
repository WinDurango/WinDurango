# Building

You must have a 64-bit machine for building and running the project. Always
run your system updater before building and make sure you have the latest
drivers.

## Setup

* Windows 10 or later
* [Visual Studio 2026](https://www.visualstudio.com/downloads/)
* Windows 11 SDK version 10.0.28000.0 or later

### Building

1. Open up `Developer PowerShell for VS`
2. Clone the repository
   ```sh
   git clone https://github.com/WinDurango/WinDurango
   ```
3. Install vcpkg packages
   ```sh
   vcpkg install
   ```
4. Prepare CMake
   ```sh
    mkdir build && cd build
    cmake ..
   ```
5. Build WinDurango
   ```sh
   cmake --build .
   ```