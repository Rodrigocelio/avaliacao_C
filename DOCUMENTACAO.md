# Documentação Técnica — Projeto LibC

## 1. Funções da Libc (Reimplementações)

Todas as funções possuem o prefixo `sc_` e seguem o comportamento original da biblioteca C padrão.

---

### Classificação e Conversão

---

#### `sc_isalpha`

- **Protótipo:** `int sc_isalpha(int c)`
- **Parâmetros:** `c` — valor inteiro representando um caractere (geralmente `unsigned char` ou `EOF`).
- **Valor de Retorno:** Retorna um valor diferente de zero (true) se `c` é uma letra maiúscula (`A`–`Z`) ou minúscula (`a`–`z`). Retorna `0` (false) caso contrário.
- **Descrição:** Verifica se o caractere passado é alfabético. A função testa se `c` está no intervalo `'A'`–`'Z'` ou `'a'`–`'z'` conforme a tabela ASCII.
- **Casos de Borda:** Se `c` for `EOF` ou um valor negativo diferente de `unsigned char`, o comportamento é indefinido (deve ser tratado com cast para `unsigned char`).

---

#### `sc_isdigit`

- **Protótipo:** `int sc_isdigit(int c)`
- **Parâmetros:** `c` — valor inteiro representando um caractere.
- **Valor de Retorno:** Retorna um valor diferente de zero se `c` é um dígito decimal (`'0'`–`'9'`). Retorna `0` caso contrário.
- **Descrição:** Verifica se o caractere é um dígito numérico de `0` a `9`.
- **Casos de Borda:** Qualquer valor fora do intervalo `'0'`–`'9'` retorna `0`.

---

#### `sc_isalnum`

- **Protótipo:** `int sc_isalnum(int c)`
- **Parâmetros:** `c` — valor inteiro representando um caractere.
- **Valor de Retorno:** Retorna um valor diferente de zero se `c` é alfanumérico (letra ou dígito). Retorna `0` caso contrário.
- **Descrição:** Combina `sc_isalpha` e `sc_isdigit`: retorna true se o caractere é uma letra ou um dígito.
- **Casos de Borda:** Equivale a `sc_isalpha(c) || sc_isdigit(c)`.

---

#### `sc_isascii`

- **Protótipo:** `int sc_isascii(int c)`
- **Parâmetros:** `c` — valor inteiro representando um caractere.
- **Valor de Retorno:** Retorna um valor diferente de zero se `c` está no intervalo `0`–`127` (tabela ASCII). Retorna `0` caso contrário.
- **Descrição:** Verifica se o valor está dentro do conjunto de caracteres ASCII de 7 bits.
- **Casos de Borda:** Valores negativos retornam `0`. O valor `127` (DEL) também é considerado ASCII.

---

#### `sc_isprint`

- **Protótipo:** `int sc_isprint(int c)`
- **Parâmetros:** `c` — valor inteiro representando um caractere.
- **Valor de Retorno:** Retorna um valor diferente de zero se `c` é um caractere imprimível (`32`–`126`). Retorna `0` caso contrário.
- **Descrição:** Verifica se o caractere é imprimível (incluindo espaço).
- **Casos de Borda:** O espaço (`' '`, valor 32) é considerado imprimível. Caracteres de controle (`0`–`31`) e DEL (`127`) não são.

---

#### `sc_toupper`

- **Protótipo:** `int sc_toupper(int c)`
- **Parâmetros:** `c` — valor inteiro representando um caractere.
- **Valor de Retorno:** Retorna o caractere convertido para maiúsculo, se aplicável. Caso contrário, retorna o caractere original.
- **Descrição:** Se `c` é uma letra minúscula (`'a'`–`'z'`), converte para maiúscula subtraindo 32 da tabela ASCII.
- **Casos de Borda:** Caracteres não alfabéticos ou já maiúsculos são retornados inalterados.

---

#### `sc_tolower`

- **Protótipo:** `int sc_tolower(int c)`
- **Parâmetros:** `c` — valor inteiro representando um caractere.
- **Valor de Retorno:** Retorna o caractere convertido para minúsculo, se aplicável. Caso contrário, retorna o caractere original.
- **Descrição:** Se `c` é uma letra maiúscula (`'A'`–`'Z'`), converte para minúscula somando 32 na tabela ASCII.
- **Casos de Borda:** Caracteres não alfabéticos ou já minúsculos são retornados inalterados.

---

#### `sc_atoi`

- **Protótipo:** `int sc_atoi(const char *nptr)`
- **Parâmetros:** `nptr` — ponteiro para a string a ser convertida.
- **Valor de Retorno:** Retorna o valor inteiro convertido. Se a string não contiver dígitos, retorna `0`.
- **Descrição:** Converte o início da string `nptr` para um inteiro. Ignora espaços em branco iniciais, aceita um sinal opcional (`+`/`-`) e lê dígitos consecutivos até encontrar um caractere não numérico.
- **Casos de Borda:** Se `nptr` for `NULL`, o comportamento é indefinido. Se a string for vazia ou não iniciar com dígito/sinal, retorna `0`. Não trata overflow (comportamento indefinido da libc original).

---

### Manipulação de Memória

---

#### `sc_memset`

- **Protótipo:** `void *sc_memset(void *s, int c, size_t n)`
- **Parâmetros:** `s` — ponteiro para o bloco de memória; `c` — valor a ser escrito (convertido para `unsigned char`); `n` — número de bytes a serem preenchidos.
- **Valor de Retorno:** Retorna o ponteiro `s` original.
- **Descrição:** Preenche os primeiros `n` bytes da área de memória apontada por `s` com o valor `c` convertido para `unsigned char`.
- **Casos de Borda:** Se `n` for `0`, a função não faz nada. Se `s` for `NULL`, o comportamento é indefinido.

---

#### `sc_bzero`

- **Protótipo:** `void sc_bzero(void *s, size_t n)`
- **Parâmetros:** `s` — ponteiro para o bloco de memória; `n` — número de bytes a serem zerados.
- **Valor de Retorno:** Nada (`void`).
- **Descrição:** Equivalente a `sc_memset(s, 0, n)`. Preenche com zeros os primeiros `n` bytes da memória apontada por `s`.
- **Casos de Borda:** Se `n` for `0`, não faz nada. Se `s` for `NULL`, comportamento indefinido.

---

#### `sc_memcpy`

- **Protótipo:** `void *sc_memcpy(void *dest, const void *src, size_t n)`
- **Parâmetros:** `dest` — ponteiro de destino; `src` — ponteiro de origem; `n` — número de bytes a copiar.
- **Valor de Retorno:** Retorna o ponteiro `dest` original.
- **Descrição:** Copia `n` bytes da área de memória `src` para `dest`. As áreas **não devem** se sobrepor (use `sc_memmove` para sobreposição).
- **Casos de Borda:** Se `n` for `0`, não faz nada. Se `src` ou `dest` forem `NULL`, comportamento indefinido. Comportamento incorreto se `src` e `dest` se sobrepuserem.

---

#### `sc_memmove`

- **Protótipo:** `void *sc_memmove(void *dest, const void *src, size_t n)`
- **Parâmetros:** `dest` — ponteiro de destino; `src` — ponteiro de origem; `n` — número de bytes a copiar.
- **Valor de Retorno:** Retorna o ponteiro `dest` original.
- **Descrição:** Copia `n` bytes de `src` para `dest`. Diferente de `memcpy`, suporta áreas sobrepostas: se `dest` < `src`, copia do início para o fim; caso contrário, copia do fim para o início.
- **Casos de Borda:** Se `n` for `0`, não faz nada. Se `dest == src`, não há efeito. Se `src` ou `dest` forem `NULL`, comportamento indefinido.

---

#### `sc_memchr`

- **Protótipo:** `void *sc_memchr(const void *s, int c, size_t n)`
- **Parâmetros:** `s` — ponteiro para o bloco de memória; `c` — valor a ser localizado (convertido para `unsigned char`); `n` — número inicial de bytes a serem pesquisados.
- **Valor de Retorno:** Retorna um ponteiro para a primeira ocorrência de `c` em `s`, ou `NULL` se não encontrado.
- **Descrição:** Escaneia os primeiros `n` bytes de `s` em busca do valor `c`.
- **Casos de Borda:** Se `n` for `0`, retorna `NULL` imediatamente. Se `s` for `NULL`, comportamento indefinido.

---

#### `sc_memcmp`

- **Protótipo:** `int sc_memcmp(const void *s1, const void *s2, size_t n)`
- **Parâmetros:** `s1` — primeiro bloco de memória; `s2` — segundo bloco de memória; `n` — número de bytes a comparar.
- **Valor de Retorno:** Retorna `0` se os blocos forem iguais. Retorna um valor negativo se `s1` < `s2`, ou positivo se `s1` > `s2` (comparação byte a byte como `unsigned char`).
- **Descrição:** Compara os primeiros `n` bytes de `s1` e `s2`.
- **Casos de Borda:** Se `n` for `0`, retorna `0`. Se `s1` ou `s2` forem `NULL`, comportamento indefinido.

---

### Manipulação de Strings

---

#### `sc_strlen`

- **Protótipo:** `size_t sc_strlen(const char *s)`
- **Parâmetros:** `s` — ponteiro para a string terminada em caractere nulo (`'\0'`).
- **Valor de Retorno:** Retorna o número de caracteres na string, excluindo o terminador nulo.
- **Descrição:** Percorre a string contando caracteres até encontrar `'\0'`.
- **Casos de Borda:** Se `s` for `NULL`, comportamento indefinido. Se `s` for uma string vazia (`""`), retorna `0`.

---

#### `sc_strlcpy`

- **Protótipo:** `size_t sc_strlcpy(char *dst, const char *src, size_t size)`
- **Parâmetros:** `dst` — buffer de destino; `src` — string de origem; `size` — tamanho do buffer de destino.
- **Valor de Retorno:** Retorna o comprimento total de `src` (o comprimento que `dst` teria se `size` fosse ilimitado). Isso permite detectar truncamento.
- **Descrição:** Copia até `size - 1` caracteres de `src` para `dst` e adiciona o terminador nulo. Se `size` for 0, não escreve nada.
- **Casos de Borda:** Se `size` for 0, retorna `strlen(src)` sem escrever nada. Se `size` > 0, garante terminação nula. Se `src` for NULL, comportamento indefinido.

---

#### `sc_strlcat`

- **Protótipo:** `size_t sc_strlcat(char *dst, const char *src, size_t size)`
- **Parâmetros:** `dst` — buffer de destino contendo string; `src` — string a ser concatenada; `size` — tamanho total do buffer.
- **Valor de Retorno:** Retorna o comprimento total que a string tentou criar (soma do comprimento inicial de `dst` e `src`).
- **Descrição:** Concatena `src` ao final de `dst` com segurança, garantindo terminação nula. Usa `strlen` para encontrar o final de `dst` e copia no máximo `size - dst_len - 1` caracteres.
- **Casos de Borda:** Se `size` for 0 ou `dst` não tiver terminador nulo dentro dos primeiros `size` bytes, retorna `size + strlen(src)`.

---

#### `sc_strchr`

- **Protótipo:** `char *sc_strchr(const char *s, int c)`
- **Parâmetros:** `s` — string a ser pesquisada; `c` — caractere a localizar (convertido para `char`).
- **Valor de Retorno:** Retorna um ponteiro para a primeira ocorrência de `c` em `s`, ou `NULL` se não encontrado.
- **Descrição:** Percorre a string `s` até encontrar o caractere `c` ou o terminador nulo. O terminador nulo é considerado parte da string, então `sc_strchr(s, '\0')` retorna um ponteiro para o final da string.
- **Casos de Borda:** Se `c` for `'\0'`, retorna ponteiro para o terminador nulo. Se `s` for `NULL`, comportamento indefinido.

---

#### `sc_strrchr`

- **Protótipo:** `char *sc_strrchr(const char *s, int c)`
- **Parâmetros:** `s` — string a ser pesquisada; `c` — caractere a localizar.
- **Valor de Retorno:** Retorna um ponteiro para a **última** ocorrência de `c` em `s`, ou `NULL` se não encontrado.
- **Descrição:** Percorre a string do início ao fim, atualizando um ponteiro a cada ocorrência de `c`. O terminador nulo é incluído na busca.
- **Casos de Borda:** Se `c` for `'\0'`, retorna ponteiro para o terminador nulo. Se `s` for `NULL`, comportamento indefinido.

---

#### `sc_strncmp`

- **Protótipo:** `int sc_strncmp(const char *s1, const char *s2, size_t n)`
- **Parâmetros:** `s1` — primeira string; `s2` — segunda string; `n` — número máximo de caracteres a comparar.
- **Valor de Retorno:** Retorna `0` se as strings forem iguais (até `n` caracteres). Retorna negativo se `s1` < `s2`, positivo se `s1` > `s2`.
- **Descrição:** Compara no máximo `n` caracteres de `s1` e `s2`. A comparação é feita caractere por caractere como `unsigned char`. A comparação para ao encontrar diferença ou terminador nulo.
- **Casos de Borda:** Se `n` for `0`, retorna `0`. Se uma string for prefixo da outra, a diferença é determinada pelo terminador nulo (valor 0).

---

#### `sc_strnstr`

- **Protótipo:** `char *sc_strnstr(const char *big, const char *little, size_t len)`
- **Parâmetros:** `big` — string a ser percorrida; `little` — substring a localizar; `len` — número máximo de caracteres a examinar em `big`.
- **Valor de Retorno:** Retorna um ponteiro para o início de `little` em `big`, ou `NULL` se não encontrado. Se `little` for vazia, retorna `big`.
- **Descrição:** Localiza a primeira ocorrência da substring `little` (excluindo o terminador nulo) na string `big`, examinando no máximo `len` caracteres.
- **Casos de Borda:** Se `little` for vazia (`""`), retorna `big`. Se `big` ou `little` forem `NULL`, comportamento indefinido.

---

#### `sc_strdup`

- **Protótipo:** `char *sc_strdup(const char *s)`
- **Parâmetros:** `s` — string a ser duplicada.
- **Valor de Retorno:** Retorna um ponteiro para a nova string duplicada, ou `NULL` se a alocação falhar.
- **Descrição:** Aloca memória suficiente (via `malloc`) para copiar a string `s`, copia o conteúdo e retorna o ponteiro.
- **Casos de Borda:** Se `s` for `NULL`, retorna `NULL`. Se `malloc` falhar, retorna `NULL`.

---

### Alocação Dinâmica

---

#### `sc_calloc`

- **Protótipo:** `void *sc_calloc(size_t nmemb, size_t size)`
- **Parâmetros:** `nmemb` — número de elementos; `size` — tamanho de cada elemento em bytes.
- **Valor de Retorno:** Retorna um ponteiro para a memória alocada e zerada, ou `NULL` se a alocação falhar.
- **Descrição:** Aloca memória suficiente para um array de `nmemb` elementos de `size` bytes cada. A memória é inicializada com zero. Internamente usa `malloc` e `sc_bzero`/`sc_memset`.
- **Casos de Borda:** Se `nmemb` ou `size` for `0`, pode retornar `NULL` ou um ponteiro único (comportamento definido pela implementação). Se a multiplicação `nmemb * size` causar overflow, retorna `NULL`.

---

## 2. Funções Adicionais

---

#### `sc_substr`

- **Protótipo:** `char *sc_substr(char const *s, unsigned int start, size_t len)`
- **Parâmetros:** `s` — string original; `start` — índice inicial (base 0); `len` — comprimento máximo da substring.
- **Valor de Retorno:** Retorna a substring alocada, ou `NULL` se a alocação falhar.
- **Descrição:** Aloca e retorna uma substring da string `s`. A substring começa no índice `start` e tem no máximo `len` caracteres. Se `start` for maior que o comprimento de `s`, retorna uma string vazia.
- **Casos de Borda:** Se `s` for `NULL`, retorna `NULL`. Se `start >= strlen(s)`, retorna string vazia alocada. Se `len` exceder o restante da string, copia até o final.

---

#### `sc_strjoin`

- **Protótipo:** `char *sc_strjoin(char const *s1, char const *s2)`
- **Parâmetros:** `s1` — primeira string; `s2` — segunda string.
- **Valor de Retorno:** Retorna a nova string concatenada, ou `NULL` se a alocação falhar.
- **Descrição:** Aloca e retorna uma nova string resultante da concatenação de `s1` e `s2`.
- **Casos de Borda:** Se `s1` ou `s2` for `NULL`, comportamento indefinido (ou retorna `NULL` — a depender da implementação).

---

#### `sc_strtrim`

- **Protótipo:** `char *sc_strtrim(char const *s, char const *set)`
- **Parâmetros:** `s` — string a ser aparada; `set` — conjunto de caracteres a remover.
- **Valor de Retorno:** Retorna a nova string aparada, ou `NULL` se a alocação falhar.
- **Descrição:** Remove todos os caracteres presentes em `set` do início e do fim de `s`. Os caracteres do meio não são alterados. Aloca uma nova string com o resultado.
- **Casos de Borda:** Se `s` ou `set` for `NULL`, retorna `NULL`. Se todos os caracteres forem removidos, retorna uma string vazia alocada.

---

#### `sc_split`

- **Protótipo:** `char **sc_split(char const *s, char c)`
- **Parâmetros:** `s` — string a ser dividida; `c` — caractere delimitador.
- **Valor de Retorno:** Retorna um array de strings (terminado por `NULL`) alocado, ou `NULL` se a alocação falhar.
- **Descrição:** Divide a string `s` em substrings usando o caractere `c` como delimitador. O array resultante termina com um ponteiro `NULL`. Delimitadores consecutivos geram strings vazias.
- **Casos de Borda:** Se `s` for `NULL`, retorna `NULL`. Se `s` for vazia, retorna array com um elemento `""` e terminador `NULL`.

---

#### `sc_itoa`

- **Protótipo:** `char *sc_itoa(int n)`
- **Parâmetros:** `n` — número inteiro a ser convertido.
- **Valor de Retorno:** Retorna a string representando o número, ou `NULL` se a alocação falhar.
- **Descrição:** Converte um inteiro `n` para sua representação em string (base 10). Lida com números negativos. O inteiro mínimo `INT_MIN` é tratado corretamente.
- **Casos de Borda:** `0` retorna a string `"0"`. `INT_MIN` requer cuidado com inversão de sinal (usar `long` ou tratar como unsigned).

---

#### `sc_strmapi`

- **Protótipo:** `char *sc_strmapi(char const *s, char (*f)(unsigned int, char))`
- **Parâmetros:** `s` — string de entrada; `f` — função a ser aplicada a cada caractere, recebendo o índice e o caractere.
- **Valor de Retorno:** Retorna a nova string com as modificações, ou `NULL` se a alocação falhar.
- **Descrição:** Aplica a função `f` a cada caractere de `s`, passando o índice do caractere e o próprio caractere. Gera uma nova string com os resultados.
- **Casos de Borda:** Se `s` for `NULL`, retorna `NULL`. Se `f` for `NULL`, comportamento indefinido.

---

#### `sc_striteri`

- **Protótipo:** `void sc_striteri(char *s, void (*f)(unsigned int, char *))`
- **Parâmetros:** `s` — string a ser modificada; `f` — função a ser aplicada a cada caractere, recebendo o índice e um ponteiro para o caractere.
- **Valor de Retorno:** Nada (`void`).
- **Descrição:** Aplica a função `f` a cada caractere de `s`, permitindo modificar o caractere in-place através do ponteiro.
- **Casos de Borda:** Se `s` ou `f` for `NULL`, a função não faz nada.

---

#### `sc_putchar_fd`

- **Protótipo:** `void sc_putchar_fd(char c, int fd)`
- **Parâmetros:** `c` — caractere a ser escrito; `fd` — descritor de arquivo (ex: `1` para stdout, `2` para stderr).
- **Valor de Retorno:** Nada (`void`).
- **Descrição:** Escreve o caractere `c` no descritor de arquivo `fd` usando a chamada `write`.
- **Casos de Borda:** Se `fd` for inválido, `write` pode retornar erro (ignorado pela função).

---

#### `sc_putstr_fd`

- **Protótipo:** `void sc_putstr_fd(char *s, int fd)`
- **Parâmetros:** `s` — string a ser escrita; `fd` — descritor de arquivo.
- **Valor de Retorno:** Nada (`void`).
- **Descrição:** Escreve a string `s` no descritor `fd`.
- **Casos de Borda:** Se `s` for `NULL`, a função não faz nada.

---

#### `sc_putendl_fd`

- **Protótipo:** `void sc_putendl_fd(char *s, int fd)`
- **Parâmetros:** `s` — string a ser escrita; `fd` — descritor de arquivo.
- **Valor de Retorno:** Nada (`void`).
- **Descrição:** Escreve a string `s` no descritor `fd` seguida por uma quebra de linha (`'\n'`).
- **Casos de Borda:** Se `s` for `NULL`, escreve apenas `'\n'`.

---

#### `sc_putnbr_fd`

- **Protótipo:** `void sc_putnbr_fd(int n, int fd)`
- **Parâmetros:** `n` — número inteiro a ser escrito; `fd` — descritor de arquivo.
- **Valor de Retorno:** Nada (`void`).
- **Descrição:** Escreve o número inteiro `n` como string no descritor `fd`. Lida com números negativos e `INT_MIN`.
- **Casos de Borda:** O valor `INT_MIN` é tratado corretamente usando unsigned para evitar overflow na inversão.

---

## 3. Funções de Lista Ligada (Bônus)

Estrutura utilizada:

```c
typedef struct s_list
{
    void          *content;
    struct s_list *next;
} t_list;
```

---

#### `sc_lstnew`

- **Protótipo:** `t_list *sc_lstnew(void *content)`
- **Parâmetros:** `content` — ponteiro para o conteúdo do novo nó.
- **Valor de Retorno:** Retorna o novo nó, ou `NULL` se a alocação falhar.
- **Descrição:** Aloca e retorna um novo nó da lista. O campo `content` é inicializado com o valor recebido e `next` com `NULL`.
- **Casos de Borda:** `content` pode ser `NULL`.

---

#### `sc_lstadd_front`

- **Protótipo:** `void sc_lstadd_front(t_list **lst, t_list *new)`
- **Parâmetros:** `lst` — ponteiro duplo para o início da lista; `new` — nó a ser adicionado.
- **Valor de Retorno:** Nada (`void`).
- **Descrição:** Adiciona o nó `new` no início da lista. O `next` de `new` aponta para o antigo primeiro elemento, e `*lst` passa a apontar para `new`.
- **Casos de Borda:** Se `lst` ou `new` forem `NULL`, a função não faz nada.

---

#### `sc_lstsize`

- **Protótipo:** `int sc_lstsize(t_list *lst)`
- **Parâmetros:** `lst` — início da lista.
- **Valor de Retorno:** Retorna o número de nós na lista.
- **Descrição:** Percorre a lista contando os nós até encontrar `NULL`.
- **Casos de Borda:** Se `lst` for `NULL`, retorna `0`.

---

#### `sc_lstlast`

- **Protótipo:** `t_list *sc_lstlast(t_list *lst)`
- **Parâmetros:** `lst` — início da lista.
- **Valor de Retorno:** Retorna o último nó da lista, ou `NULL` se a lista estiver vazia.
- **Descrição:** Percorre a lista até o último nó (onde `next` é `NULL`).
- **Casos de Borda:** Se `lst` for `NULL`, retorna `NULL`.

---

#### `sc_lstadd_back`

- **Protótipo:** `void sc_lstadd_back(t_list **lst, t_list *new)`
- **Parâmetros:** `lst` — ponteiro duplo para o início da lista; `new` — nó a ser adicionado.
- **Valor de Retorno:** Nada (`void`).
- **Descrição:** Adiciona o nó `new` ao final da lista. Se a lista estiver vazia, `*lst` passa a apontar para `new`.
- **Casos de Borda:** Se `lst` ou `new` forem `NULL`, não faz nada.

---

#### `sc_lstdelone`

- **Protótipo:** `void sc_lstdelone(t_list *lst, void (*del)(void *))`
- **Parâmetros:** `lst` — nó a ser deletado; `del` — função para liberar o conteúdo.
- **Valor de Retorno:** Nada (`void`).
- **Descrição:** Libera a memória do conteúdo do nó usando a função `del` e depois libera o próprio nó com `free`. O ponteiro `next` não é alterado.
- **Casos de Borda:** Se `del` for `NULL`, não libera o conteúdo (apenas o nó). Se `lst` for `NULL`, não faz nada.

---

#### `sc_lstclear`

- **Protótipo:** `void sc_lstclear(t_list **lst, void (*del)(void *))`
- **Parâmetros:** `lst` — ponteiro duplo para o início da lista; `del` — função para liberar o conteúdo.
- **Valor de Retorno:** Nada (`void`).
- **Descrição:** Deleta e libera todos os nós da lista sequencialmente. `*lst` é definido como `NULL` ao final.
- **Casos de Borda:** Se `lst` ou `del` forem `NULL`, não faz nada.

---

#### `sc_lstiter`

- **Protótipo:** `void sc_lstiter(t_list *lst, void (*f)(void *))`
- **Parâmetros:** `lst` — início da lista; `f` — função a ser aplicada ao conteúdo de cada nó.
- **Valor de Retorno:** Nada (`void`).
- **Descrição:** Percorre a lista e aplica a função `f` ao `content` de cada nó.
- **Casos de Borda:** Se `lst` ou `f` forem `NULL`, não faz nada.

---

#### `sc_lstmap`

- **Protótipo:** `t_list *sc_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))`
- **Parâmetros:** `lst` — início da lista; `f` — função a ser aplicada a cada conteúdo; `del` — função para deletar nós em caso de erro.
- **Valor de Retorno:** Retorna a nova lista, ou `NULL` se a alocação falhar.
- **Descrição:** Cria uma nova lista aplicando a função `f` ao `content` de cada nó de `lst`. Se a alocação de um novo nó falhar, toda a nova lista é liberada usando `del`.
- **Casos de Borda:** Se `lst` ou `f` forem `NULL`, retorna `NULL`. Se `del` for `NULL` e ocorrer erro, pode haver vazamento de memória.
