rem testa o modulo lista

cls

if exist ..\scripts\estatisticas.estat  del ..\scripts\estatisticas.estat

..\produto\testelista.exe   /s..\scripts\TesteLista            /l..\produto\testelista        /a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\testelista.exe    /s..\scripts\TesteContadorLista          /l..\produto\testecontador            /a..\scripts\estatisticas
if errorlevel 4 goto sai