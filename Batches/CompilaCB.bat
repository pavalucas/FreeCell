ECHO compila o modulo celula base
REM Requer o ambiente (environment) inicializado para compilar com o VisualStudio Microsoft
cls

del ..\produto\*.err
del ..\objetos\*.obj

REM compila para producao
pushd .
nmake /F..\composicao\testecb.make 
popd

copy ..\produto\*.err ..\produto\tudo.err

notepad ..\produto\tudo.err

