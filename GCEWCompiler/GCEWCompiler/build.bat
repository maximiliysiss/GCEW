if exist $(%1)configuration.xml del /f $(%1)masmCompile.bat

if exist $(%1)masmCompile.bat del /f $(%1)masmCompile.bat

copy masmCompile.bat %1
copy configuration.xml %1