rem testa o modulo lista

cls

if exist ..\scripts\estatisticas.estat  del ..\scripts\estatisticas.estat

..\produto\testelista.exe         /s..\scripts\TesteLista           /a..\scripts\estatisticas
