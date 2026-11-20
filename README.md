# ⚔️ Nodefall

Jogo de ação top-down em **C** com **raylib**, estilo masmorra pixel art. Projeto em grupo da disciplina de PIF.

## 🎥 Vídeo de demonstração

👉 **[Assista ao vídeo do jogo](https://drive.google.com/file/d/1eC1WYIaYBjqbdPrzRrtVAtCWvHjk8su5/view?usp=drivesdk)**

## 🎮 Sobre o jogo

Você é um cavaleiro que atravessa 4 salas até chegar ao tesouro:

1. **Arsenal:** escolha a Espada (mais dano e vida) ou o Arco (à distância e mais rápido, mas com 1 coração a menos).
2. **Ondas:** derrote 3 ondas de inimigos (Servo, Corredor e Brutamontes).
3. **Chefe:** enfrente o Demônio, que fica mais forte quando chega à metade da vida.
4. **Tesouro:** chegue ao baú para vencer.

## ⌨️ Controles

| Tecla | Ação |
|---|---|
| `WASD` / setas | Mover |
| `ESPAÇO` | Atacar |
| `E` | Pegar arma |
| `P` | Pausar / continuar |
| `ENTER` | Confirmar / jogar de novo |
| `ESC` | Sair |

## 🏆 Pontuação

100 pontos por abate (o chefe vale 1000) + 50 por coração restante ao vencer. O top 5 é salvo em `placar.txt`.

## 🛠️ Como executar

> ⚠️ Execute sempre **na raiz do projeto**, senão os sprites não carregam.

### Windows

Requisitos: GCC e Make (MinGW-w64). A raylib já vem no repositório.

```bash
git clone https://github.com/gugar333/Nodefall.git
cd Nodefall
make run
```

### Linux

```bash
# 1. Dependências
sudo apt update
sudo apt install build-essential git cmake libasound2-dev libx11-dev \
  libxrandr-dev libxi-dev libgl1-mesa-dev libxcursor-dev libxinerama-dev

# 2. Instalar a raylib
git clone --depth 1 https://github.com/raysan5/raylib.git
cd raylib/src
make PLATFORM=PLATFORM_DESKTOP
sudo make install
cd ../..

# 3. Compilar e rodar o jogo
git clone https://github.com/gugar333/Nodefall.git
cd Nodefall
make run
```

No Linux, o `Makefile` precisa usar as bibliotecas do sistema. Troque a linha `LDFLAGS` por:

```make
ifeq ($(OS),Windows_NT)
    LDFLAGS = -Llib -lraylib -lgdi32 -lwinmm
else
    LDFLAGS = -lraylib -lm -lpthread -ldl -lrt -lX11
endif
```

### Problemas comuns

| Problema | Solução |
|---|---|
| `cannot find -lgdi32` | O `Makefile` ainda está na versão Windows. Aplique o ajuste acima. |
| `cannot find -lraylib` | Instale a raylib (passo 2 do Linux). |
| Build parando por *warning* | Remova `-Werror` do `CFLAGS`. |
| Janela sem texturas | Rode o jogo na raiz do projeto. |

## 🧩 Conceitos de C usados

| Conceito | Onde está |
|---|---|
| Structs | `Jogo`, `Jogador`, `Inimigo`, `Flecha`, `Boss`, `Registro` |
| Ponteiros | Funções recebem ponteiros (`Jogo *j`); ponteiro para ponteiro na remoção das listas |
| Alocação dinâmica | `malloc`/`free` de inimigos, flechas e registros do placar |
| Listas encadeadas | Inimigos (`inimigo.c`), flechas (`flecha.c`) e placar ordenado (`placar.c`) |
| Matrizes | Mapa das salas `salas[4][12][21]` (`sala.c`), composição das ondas (`jogo.c`) |
| Arquivos | Leitura e escrita do ranking em `placar.txt` (`placar.c`) |

## 🙏 Créditos

- Sprites: [0x72 — DungeonTileset II](https://0x72.itch.io/dungeontileset-ii) (CC0)
- Biblioteca: [raylib](https://www.raylib.com) (licença zlib)

## 👥 Integrantes

- Davi da Fonte
- Gustavo Soares
- Pedro José
