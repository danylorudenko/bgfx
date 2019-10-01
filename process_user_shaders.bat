for /r %%v in (usercode\userproject0\shaders\vertex\*.*) do .build\win64_vs2017\bin\shadercDebug.exe --verbose -i .\src --varyingdef .\src\varying.def.sc --platform windows --profile "s_5" --type vertex -O 0 -f "%%v" -o "%%v.bin"

for /r %%v in (usercode\userproject0\shaders\fragment\*.*) do .build\win64_vs2017\bin\shadercDebug.exe --verbose -i .\src --varyingdef .\src\varying.def.sc --platform windows --profile "s_5" --type fragment -O 0 -f "%%v" -o "%%v.bin"
pause