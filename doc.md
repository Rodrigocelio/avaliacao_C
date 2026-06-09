# Lista de Funções do Projeto LibC

De acordo com o documento, as funções são divididas em três partes principais:

## 1. Funções da Libc (Reimplementações)

Essas funções devem ter o prefixo `sc_` e seguir o comportamento original da biblioteca C padrão:

### Classificação e Conversão

- `sc_isalpha`
- `sc_isdigit`
- `sc_isalnum`
- `sc_isascii`
- `sc_isprint`
- `sc_toupper`
- `sc_tolower`
- `sc_atoi`

### Manipulação de Memória

- `sc_memset`
- `sc_bzero`
- `sc_memcpy`
- `sc_memmove`
- `sc_memchr`
- `sc_memcmp`

### Manipulação de Strings

- `sc_strlen`
- `sc_strlcpy`
- `sc_strlcat`
- `sc_strchr`
- `sc_strrchr`
- `sc_strncmp`
- `sc_strnstr`
- `sc_strdup`

### Alocação Dinâmica

- `sc_calloc`

## 2. Funções Adicionais

Funções que não estão na libc ou possuem formatos diferentes:

- `sc_substr` — Cria uma substring de uma string original.
- `sc_strjoin` — Concatena duas strings em uma nova.
- `sc_strtrim` — Remove caracteres específicos do início e fim de uma string.
- `sc_split` — Divide uma string em um array de strings usando um delimitador.
- `sc_itoa` — Converte um número inteiro em uma string.
- `sc_strmapi` e `sc_striteri` — Aplicam funções a cada caractere de uma string.
- `sc_putchar_fd`, `sc_putstr_fd`, `sc_putendl_fd`, `sc_putnbr_fd` — Saída de dados em descritores de arquivo.

## 3. Funções de Lista Ligada (Bônus — não obrigatório)

Funções para manipular a estrutura de lista encadeada (`t_list`):

- `sc_lstnew`
- `sc_lstadd_front`
- `sc_lstsize`
- `sc_lstlast`
- `sc_lstadd_back`
- `sc_lstdelone`
- `sc_lstclear`
- `sc_lstiter`
- `sc_lstmap`

---

# Atividade Prática: Guia de Documentação Técnica

**Objetivo:** Demonstrar compreensão profunda de cada função antes da implementação de código.

### Instruções para os alunos

Crie um documento (em formato planilha ou texto simples) contendo um descritivo técnico para cada uma das funções listadas acima. Para cada função, você deve preencher o seguinte modelo:

1. **Protótipo:** (ex: `int sc_strlen(const char *s)`)
2. **Parâmetros:** Explique o que cada argumento recebido representa.
3. **Valor de Retorno:** O que a função retorna em caso de sucesso e o que retorna em caso de erro/falha (ex: `NULL`, `0`).
4. **Descrição Detalhada:** Explique em suas próprias palavras o que a função faz, passo a passo.
5. **Casos de Borda:** O que acontece se um ponteiro for `NULL`? E se o tamanho (`size_t`) for `0`?

Após o desenvolvimento do documento, implemente as funções acima na linguagem de sua preferência (que seja mais fácil para você). Esses arquivos devem ser enviados junto.
