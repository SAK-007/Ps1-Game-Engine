@echo off
cd cdimage
del game.iso
cd..
cls
psymake
pause
.\mkpsxiso\mkpsxiso.exe -o cdimage\game.iso -y .\cuesheet.xml
C:/epsxe/epsxe.exe -loadbin C:/psyq/Projects/demoproject/cdimage/game.iso -nogui
exit
