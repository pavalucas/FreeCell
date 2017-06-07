rem testa o modulo celulas extras

cls

if exist ..\scripts\estatisticas.estat  del ..\scripts\estatisticas.estat

..\produto\testece.exe  /s..\scripts\TesteCelulaExtra     /a..\scripts\estatisticas
