@echo off
title Car Rental Management System
cls
echo ===================================================
echo   Compiling Car Rental Management System...
echo ===================================================
g++ -std=c++17 -O3 src/*.cpp -Iinclude -o CarRentalSystem.exe
if %ERRORLEVEL% EQU 0 (
    echo [SUCCESS] Compilation complete! Launching system...
    echo.
    CarRentalSystem.exe
) else (
    echo [ERROR] Compilation failed. Please ensure MinGW g++ is installed.
    pause
)
pause
