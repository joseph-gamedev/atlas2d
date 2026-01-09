@echo off
setlocal

set "CONFIG=Debug"
if not "%~1"=="" set "CONFIG=%~1"

set "BUILD_DIR=build"

cmake -S . -B "%BUILD_DIR%"
if errorlevel 1 exit /b %errorlevel%

cmake --build "%BUILD_DIR%" --config "%CONFIG%" --parallel
if errorlevel 1 exit /b %errorlevel%
