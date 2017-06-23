##################################################
###
### Diretivas de MAKE para o construto: TestePartida
### Gerado a partir de: TestePartida.comp
###
### ----- Arquivo gerado, NÃO EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = TestePartida


### Nomes de paths

Pdef                 = ..\Tabelas
Ph                   = ..\Fontes
Pobj                 = ..\Objetos
Perr                 = ..\Produto
PDEFAULT             = ..\Fontes
Pc                   = ..\Fontes

### Nomes de diretórios para geração

Fdef                 = ..\Tabelas
Fh                   = ..\Fontes
Fobj                 = ..\Objetos
Ferr                 = ..\Produto
FDEFAULT             = ..\Fontes
Fc                   = ..\Fontes

### Macros da plataforma


O       = /D_CRT_SECURE_NO_DEPRECATE
OD      = /Zi /Od /D_CRT_SECURE_NO_DEPRECATE
L       =
LD      = /DEBUG /DEBUGTYPE:CV

!IFDEF PRD
O       = /Ox /D_CRT_SECURE_NO_DEPRECATE
!ENDIF

OPT     = /c /J /W4 /nologo
INCLUDE = $(INCLUDE);$(PDEFAULT)


### Regras de geração

all : limpa \
   $(Fobj)\CelulaBase.obj   $(Fobj)\CelulaExtra.obj   $(Fobj)\ColunaVisivel.obj \
   $(Fobj)\Partida.obj \
   Construto

### Limpar arquivos

limpa :
   if exist $(Ferr)\$(NOME).err  del $(Ferr)\$(NOME).err


### Dependências de módulos objeto a compilar

$(Fobj)\CelulaBase.obj :  {$(Pc)}\CelulaBase.c \
    {$(Ph)}BARALHO.h            {$(Ph)}CELULABASE.h         {$(PDEFAULT)}LISTA.H             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\CelulaExtra.obj :  {$(Pc)}\CelulaExtra.c \
    {$(Ph)}BARALHO.h            {$(Ph)}CELULAEXTRA.h        {$(PDEFAULT)}LISTA.H             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\ColunaVisivel.obj :  {$(Pc)}\ColunaVisivel.c \
    {$(Ph)}BARALHO.h            {$(PDEFAULT)}COLUNAVISIVEL.H      {$(PDEFAULT)}LISTA.H             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\Partida.obj :  {$(Pc)}\Partida.c \
    {$(Ph)}BARALHO.h            {$(Ph)}CELULABASE.h         {$(Ph)}CELULAEXTRA.h        \
    {$(Ph)}COLUNAVISIVEL.h      {$(PDEFAULT)}LISTA.H             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err


### Terminação

Construto : \
   $(Fobj)\CelulaBase.obj   $(Fobj)\CelulaExtra.obj   $(Fobj)\ColunaVisivel.obj \
   $(Fobj)\Partida.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: TestePartida
###
##################################################

