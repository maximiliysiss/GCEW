set execPath=%~dp1
set fileName=%~n1

cd %execPath%

/masm32/bin/ml /c /coff "%1"
/masm32/bin/link /SUBSYSTEM:CONSOLE %fileName%.obj