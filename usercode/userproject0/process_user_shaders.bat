rmdir /S /Q .\usercode\runtime\shaders
mkdir .\usercode\runtime\shaders\vertex\
mkdir .\usercode\runtime\shaders\fragment\

for /r %%V in (shaders\vertex\*.*) do .build\win64_vs2017\bin\shadercDebug.exe --verbose -i .\src --varyingdef .\shaders\varying.def.sc --platform windows --profile "vs_5_0" --type vertex -O 0 -f "%%V" -o "..\runtime\shaders\vertex\%%~nV.bin"

for /r %%V in (shaders\fragment\*.*) do .build\win64_vs2017\bin\shadercDebug.exe --verbose -i .\src --varyingdef .\shaders\varying.def.sc --platform windows --profile "ps_5_0" --type fragment -O 0 -f "%%V" -o "..\runtime\shaders\fragment\%%~nV.bin"

pause