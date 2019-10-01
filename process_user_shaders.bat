rmdir /S /Q .\usercode\runtime\shaders
mkdir .\usercode\runtime\shaders\vertex\
mkdir .\usercode\runtime\shaders\fragment\

for /r %%V in (usercode\userproject0\shaders\vertex\*.*) do .build\win64_vs2017\bin\shadercDebug.exe --verbose -i .\src --varyingdef .\src\varying.def.sc --platform windows --profile "vs_5_0" --type vertex -O 0 -f "%%V" -o "usercode\runtime\shaders\vertex\%%~nV.bin"

for /r %%V in (usercode\userproject0\shaders\fragment\*.*) do .build\win64_vs2017\bin\shadercDebug.exe --verbose -i .\src --varyingdef .\src\varying.def.sc --platform windows --profile "ps_5_0" --type fragment -O 0 -f "%%V" -o "usercode\runtime\shaders\fragment\%%~nV.bin"

pause