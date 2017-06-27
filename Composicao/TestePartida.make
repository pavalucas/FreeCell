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


O       =
OD      = /Zi /Od
L       =
LD      = /DEBUG /DEBUGTYPE:CV

!IFDEF PRD
O       = /Ox
!ENDIF

OPT     = /c /J /W4 /nologo
INCLUDE = $(INCLUDE);$(PDEFAULT)


### Regras de geração

all : limpa \
   $(Fobj)\lista.obj   $(Fobj)\baralho.obj   $(Fobj)\celulabase.obj \
   $(Fobj)\celulaextra.obj   $(Fobj)\colunavisivel.obj   $(Fobj)\partida.obj \
   Construto

### Limpar arquivos

limpa :
   if exist $(Ferr)\$(NOME).err  del $(Ferr)\$(NOME).err


### Dependências de módulos objeto a compilar

$(Fobj)\lista.obj :  {$(Pc)}\lista.c \
    ..\\tabelas\\idtiposespaco.def {$(Ph)}cespdin.h            {$(Ph)}conta.h              \
    {$(Ph)}lista.h              {$(Pdef)}tiposespacoslista.def
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\baralho.obj :  {$(Pc)}\baralho.c \
    {$(Ph)}baralho.h            {$(Ph)}lista.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\celulabase.obj :  {$(Pc)}\celulabase.c \
    {$(Ph)}baralho.h            {$(Ph)}celulabase.h         {$(Ph)}lista.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\celulaextra.obj :  {$(Pc)}\celulaextra.c \
    {$(Ph)}baralho.h            {$(Ph)}celulaextra.h        {$(Ph)}lista.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\colunavisivel.obj :  {$(Pc)}\colunavisivel.c \
    {$(Ph)}baralho.h            {$(Ph)}colunavisivel.h      {$(Ph)}lista.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\partida.obj :  {$(Pc)}\partida.c \
    {$(Ph)}baralho.h            {$(Ph)}celulabase.h         {$(Ph)}celulaextra.h        \
    {$(Ph)}colunavisivel.h      {$(Ph)}lista.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err


### Terminação

Construto : \
   $(Fobj)\lista.obj   $(Fobj)\baralho.obj   $(Fobj)\celulabase.obj \
   $(Fobj)\celulaextra.obj   $(Fobj)\colunavisivel.obj   $(Fobj)\partida.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: TestePartida
###
##################################################

