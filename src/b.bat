@echo off

IF NOT EXIST ..\build mkdir ..\build

SET compilerFlags= -Zi /EHsc
SET winLibs= kernel32.lib user32.lib gdi32.lib winmm.lib Dwmapi.lib
SET DXLibs= d3d11.lib d3dcompiler.lib 

pushd ..\build

cl %compilerFlags% ..\src\CJDX_02.cpp %winLibs% %DXLibs% 

popd

copy /Y shader.fx ..\build

del *.bat~ *.un~ *.cpp~ *.h~ *.h~~ *.fx~
