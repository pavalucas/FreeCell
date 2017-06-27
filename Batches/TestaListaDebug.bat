rem testa o modulo lista

cls

if exist ..\scripts\estatisticas.estat  del ..\scripts\estatisticas.estat

..\produto\TesteListaDebug.exe   /s..\scripts\TesteLista            /l..\produto\TesteLista        /a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\TesteListaDebug.exe   /s..\scripts\TesteContadorLista           /l..\produto\TesteContadorLista            /a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\TesteListaDebug.exe   /s..\scripts\TesteControleEspacoLista     /l..\produto\TesteControleEspacoLista      /a..\scripts\estatisticas
if errorlevel 4 goto sai

