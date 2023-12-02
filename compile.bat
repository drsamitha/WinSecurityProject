@echo off
setlocal enabledelayedexpansion
REM Define the C++ compiler to use
set CXX=g++

REM Define any compile-time flags
set CXXFLAGS=-Wall

REM Loop over each .cpp file in the current directory
for %%f in (*.cpp) do (
    REM Get the base name of the file
    for %%n in (%%~nf) do (
        REM Define the executable file 
        set MAIN=%%n.exe

        REM Print out a message about what the script is doing
        echo Compiling %%f into !MAIN!...

        REM Call the C++ compiler to compile the source file and link it into an executable
        %CXX% %CXXFLAGS% %%f -o !MAIN!
    )
)

REM Pause the script at the end
pause
endlocal
