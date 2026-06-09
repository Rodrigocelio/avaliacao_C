# Projeto LibC

Reimplementação de funções da biblioteca C padrão, com funções adicionais e manipulação de listas ligadas.

## Estrutura do Projeto

```
C/
├── include/
│   └── libc.h          # Header com protótipos e struct t_list
├── src/
│   ├── sc_type.c       # Classificação e conversão
│   ├── sc_math.c       # sc_atoi, sc_itoa
│   ├── sc_mem.c        # Manipulação de memória
│   ├── sc_str.c        # Manipulação de strings (parte 1)
│   ├── sc_str2.c       # Funções adicionais de string
│   ├── sc_calloc.c     # Alocação dinâmica
│   ├── sc_put.c        # Saída em file descriptors
│   └── sc_lst.c        # Lista ligada (bônus)
├── main.c              # Programa de demonstração
├── Makefile             # Build system
├── DOCUMENTACAO.md      # Documentação técnica detalhada
├── doc.md              # Lista resumida das funções
└── README.md           # Este arquivo
```

## Requisitos

- Compilador C (gcc, cc, clang)
- Make

## Compilação

```bash
make          # Compila o projeto
make clean    # Remove arquivos objeto (.o)
make fclean   # Remove objetos e binário
make re       # Limpa e recompila
```

## Execução

```bash
make run      # Compila (se necessário) e executa a demonstração
# ou
./libc_demo   # Executa o binário diretamente
```

## Funções Implementadas

### Libc (prefixo `sc_`)

| Categoria               | Funções                                                                 |
|-------------------------|-------------------------------------------------------------------------|
| Classificação/Conversão | `sc_isalpha`, `sc_isdigit`, `sc_isalnum`, `sc_isascii`, `sc_isprint`, `sc_toupper`, `sc_tolower`, `sc_atoi` |
| Memória                 | `sc_memset`, `sc_bzero`, `sc_memcpy`, `sc_memmove`, `sc_memchr`, `sc_memcmp` |
| Strings                 | `sc_strlen`, `sc_strlcpy`, `sc_strlcat`, `sc_strchr`, `sc_strrchr`, `sc_strncmp`, `sc_strnstr`, `sc_strdup` |
| Alocação                | `sc_calloc`                                                             |

### Adicionais

`sc_substr`, `sc_strjoin`, `sc_strtrim`, `sc_split`, `sc_itoa`, `sc_strmapi`, `sc_striteri`, `sc_putchar_fd`, `sc_putstr_fd`, `sc_putendl_fd`, `sc_putnbr_fd`

### Bônus (Lista Ligada)

`sc_lstnew`, `sc_lstadd_front`, `sc_lstsize`, `sc_lstlast`, `sc_lstadd_back`, `sc_lstdelone`, `sc_lstclear`, `sc_lstiter`, `sc_lstmap`

## Documentação

Consulte o arquivo [`DOCUMENTACAO.md`](DOCUMENTACAO.md) para a descrição detalhada de cada função, incluindo protótipo, parâmetros, valor de retorno, descrição passo a passo e casos de borda.
