@echo off
title Ps1 Game Engine Setup
goto help

:help
cls
echo This tool will setup environment for Ps1-Game-Engine
echo.
echo Things you need :
echo -Installed PSYQ SDK
echo -The Data folder on this directory
echo.
echo.
echo Press any key to Start The Process..
pause > nul
goto start

:start
cls
if exist C:\psyq\bin\PSYQ.INI goto :check
echo You havent installed PSYQ SDK !!
echo   Read Setup PSYQ from Docs.
pause > nul
exit

:check
cls
if exist Data\PSYQ.INI goto :setup
goto :bad
pause
exit

:setup
cls
del C:\psyq\bin\PSYQ.INI
copy Data\PSYQ.INI C:\psyq\bin
cls
echo Succesfully setuped environment !!
echo  Visit http://github.com/SAK-007/
echo  Visit http://PSXDEV.NET
pause > nul
exit

:bad
echo Couldn't find folder called Data !!
echo      Download the file again.
pause > nul
exit