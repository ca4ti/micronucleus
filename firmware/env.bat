@echo off 
where /q make.exe
if errorlevel 1 (
  SET PATH=%PATH%;C:\WinAVR\bin
)
