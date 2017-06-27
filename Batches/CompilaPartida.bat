ECHO compila o modulo partida e dependencias
REM Requer o ambiente (environment) inicializado para compilar com o VisualStudio Microsoft

cls

del ..\produto\*.err
del ..\objetos\*.obj

REM compila para producao sem otimizacoes
pushd .
nmake /F..\composicao\TestePartida.make 
popd


copy ..\produto\*.err ..\produto\tudo.err

notepad ..\produto\tudo.err