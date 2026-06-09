# LibSC — Biblioteca de funções C reimplementadas

Projeto acadêmico que reimplementa funções padrão da libc com o prefixo `sc_`.

## Pré-requisitos

```bash
sudo apt update
sudo apt install build-essential 

ou 

sudo apt install build-essential valgrind
```

## Compilação

```bash
make        # compila a biblioteca libsc.a
make clean  # remove arquivos objeto
make fclean # remove objetos e a biblioteca
make re     # recompila tudo do zero
```

## Como testar no Ubuntu

Crie um arquivo de teste (ex.: `tests/meu_teste.c`):

```c
#include "libsc.h"
#include <stdio.h>

int main(void)
{
    printf("strlen: %zu\n", sc_strlen("Hello"));
    printf("isalpha('A'): %d\n", sc_isalpha('A'));
    printf("atoi: %d\n", sc_atoi("  -42"));
    return (0);
}
```

Compile e execute:

```bash
gcc -Wall -Wextra -Werror -Iinclude tests/meu_teste.c src/*.c -o meu_teste
./meu_teste
```

Ou linke com a biblioteca estática:

```bash
make
gcc -Wall -Wextra -Werror -Iinclude tests/meu_teste.c -L. -lsc -o meu_teste
./meu_teste
```

## Verificação de vazamentos com Valgrind

```bash
gcc -Wall -Wextra -Werror -Iinclude tests/meu_teste.c src/*.c -o meu_teste
valgrind --leak-check=full ./meu_teste
```

## Estrutura do projeto

```
├── include/    # cabeçalhos (.h)
├── src/        # implementações (.c)
├── tests/      # arquivos de teste
├── obj/        # objetos compilados (gerado pelo make)
├── Makefile    # sistema de build
└── build.bat   # build para Windows (MSVC)
```
