# Swag Lords
![Game Menu](assets/screenshots/main_menu.png)


![In Game](assets/screenshots/in_game.png)
# Setup Project
Clone or
Download repo **[Space War](https://github.com/b1oss/SwagLords)**\
Unzip repository \
Go to project folder\
Type the following in terminal (Make sure you have Cmake)
### MinGW
```bash
mkdir build
cd build/
cmake -G "MinGW Makefiles" ..
mingw32-make.exe
./SpaceWar.exe
```
### MSVC
```bash
cmake -S . -B build -G "Visual Studio 18 2026" -A x64
```
Debug
```sh
cmake --build build --config Debug
./build/Debug/SpaceWar.exe
```
or Release
```sh
cmake --build build --config Release
./build/Release/SpaceWar.exe
```