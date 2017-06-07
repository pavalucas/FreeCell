rem testa o modulo celula base

cls

if exist ..\scripts\estatisticas.estat  del ..\scripts\estatisticas.estat

..\produto\testecb.exe  /s..\scripts\TesteCelulaBase      /a..\scripts\estatisticas
