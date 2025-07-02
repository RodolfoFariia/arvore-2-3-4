# 🌳 Trabalho 02: Árvores 2-3-4 & Rubro-Negra

![CMake](https://img.shields.io/badge/CMake-3.10%2B-blue) ![Language](https://img.shields.io/badge/Linguagem-C-brightgreen)

> Implementação e estudo de Árvore 2-3-4, Árvore Rubro-Negra e conversão entre elas, além de benchmarks de desempenho.

---

## 📂 Estrutura do Projeto

```
TRABALHO02/
│
├── arv234/             # Implementação da Árvore 2-3-4
│   ├── arv234.c        # Código-fonte
│   ├── arv234.h        # Cabeçalhos de funções e structs
│   └── CMakeLists.txt  # Configuração CMake
│
├── arvrb/              # Implementação da Árvore Rubro-Negra
│   ├── arvrb.c
│   ├── arvrb.h
│   └── CMakeLists.txt
│
├── conversao/          # Conversão 2-3-4 → Rubro-Negra
│   ├── conversao.c
│   ├── conversao.h
│   └── CMakeLists.txt
│
├── benchmark/          # Testes de desempenho (benchmark)
│   ├── experimentos.c
│   ├── experimentos.h
│   └── CMakeLists.txt
│
├── main.c              # Programa principal (menu, interface)
├── testes.c            # Casos de teste automatizados
├── CMakeLists.txt      # CMake principal
└── .gitignore          # Arquivos/pastas ignorados pelo Git
```

---

## 🛠️ Pré-requisitos

* CMake ≥ 3.10
* Compilador C (GCC, Clang, MSVC)
* Sistema operacional: Linux, macOS ou Windows

---

## 🚀 Como Compilar

```bash
# 1. Criar pasta de build e entrar nela
e:
mkdir build && cd build

# 2. Gerar arquivos de projeto via CMake
e:
cmake ..

# 3. Compilar tudo
e:
make
```

> Todos os módulos serão compilados como bibliotecas estáticas e ligados ao executável principal.

---

## 🎯 Como Executar

Após `make`, você terá os executáveis:

| Executável   | Descrição                                  |
| ------------ | ------------------------------------------ |
| `trabalho02` | Interface principal com menu de operações  |
| `testes`     | Rotinas automatizadas de teste e validação |

```bash
# Exemplo de execução:
./trabalho02

# Para rodar testes:
./testes
```

---

## 📊 Benchmarks

O módulo `benchmark` mede tempo de inserção e remoção em diferentes cenários.
Ele grava resultados em arquivos CSV para posterior análise.

```bash
# Exemplo de uso:
./trabalho02 --benchmark
```

---

## 📝 Documentação das APIs

### Árvores 2-3-4 (`arv234.h`)

```c
// Estrutura principal
typedef struct arvore234 arv234;

// Cria e inicializa a árvore
arv234 *alocaArvore();

// Insere uma chave
void inserir(arv234 *arv, int chave);

// Remove uma chave
void removeChave(arv234 *arv, int chave);

// Percorre em pré-ordem\ void percorrePreOrdem(no *n, int nivel);
// ... e outras funções de consulta (getAltura, getQtdSplits, etc.)
```

### Árvore Rubro-Negra (`arvrb.h`)

```c
// Cria e inicializa a árvore
arvRb *rb_alocaArvore();

// Insere e remove nó
void rb_insereNo(arvRb *arv, noRB *novoNo);
int rb_removeNo(arvRb *arv, int chave);

// Percorre e obtém raiz
void rb_percorrePreOrdem(arvRb *arv, noRB *n);
noRB *rb_getRaiz(arvRb *arv);
```

### Conversão (`conversao.h`)

```c
// Converte árvore 2-3-4 inteira para RB
arvRb *converte234ParaRB(arv234 *arv234Orig);

// Converte nó a nó
noRB *converteNo(arvRb *arvoreRB, no *no234);
```

---

## 📝 .gitignore

Este projeto já inclui um `.gitignore` para ignorar:

* Diretório de build (`/build/`)
* Artefatos CMake (`CMakeFiles/`, `CMakeCache.txt`, etc.)
* Binários e objetos (`*.o`, `*.exe`, etc.)
* Configurações do VSCode (`.vscode/`)

---

## 🤝 Contribuições

1. Fork deste repositório
2. Crie uma feature branch: `git checkout -b feature/nova-funcionalidade`
3. Faça commits claros: `git commit -m "Adiciona ..."`
4. Abra pull request

---

## 📄 License

[MIT License](./LICENSE)

---

<p align="center">Feito por Rodolfo Henrique Faria e Rafael S. P. B. Leite</p>
