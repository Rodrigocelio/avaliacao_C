#!/bin/sh
# Script de compilacao do Projeto LibC
# Uso: ./build.sh [run|clean]

SRC="main.c src/sc_type.c src/sc_math.c src/sc_mem.c src/sc_str.c src/sc_str2.c src/sc_calloc.c src/sc_put.c src/sc_lst.c"
OUT="libc_demo"
CFLAGS="-Wall -Wextra -Werror -Iinclude"
CC=""

# Find a C compiler
for c in gcc cc clang; do
    if command -v "$c" >/dev/null 2>&1; then
        CC="$c"
        break
    fi
done

if [ -z "$CC" ]; then
    echo "Erro: Nenhum compilador C encontrado (gcc, cc, clang)."
    echo "Instale o gcc com: sudo apt install gcc"
    exit 1
fi

case "${1:-}" in
    clean)
        rm -f *.o src/*.o "$OUT"
        echo "Limpo."
        ;;
    run)
        if [ ! -f "$OUT" ]; then
            $CC $CFLAGS $SRC -o "$OUT" || exit 1
        fi
        ./"$OUT"
        ;;
    *)
        $CC $CFLAGS $SRC -o "$OUT" || exit 1
        echo "Compilado: ./$OUT"
        ;;
esac
