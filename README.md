# Symbol Picker

Applicazione desktop per Linux che permette di sfogliare e copiare negli appunti caratteri speciali, simboli Unicode ed emoji utili per post, documenti e testi.

Un clic sul chip → il simbolo è già negli appunti.

---

## Funzionalità

- **~180 simboli** organizzati in 12 categorie
- **Ricerca live** per nome simbolo o categoria
- **Copia con un clic** — feedback visivo immediato (flash verde + toast)
- Adatta automaticamente il layout alla larghezza della finestra
- Rispetta la palette del sistema (tema chiaro e scuro)

### Categorie incluse

| Categoria | Esempi |
|---|---|
| Elenchi puntati | `•` `‣` `◦` `–` `—` |
| Frecce | `→` `⇒` `➤` `↳` `↩` `▶` |
| Geometrici pieni | `●` `■` `▲` `◆` `◉` |
| Geometrici vuoti | `○` `□` `△` `◇` `▷` |
| Check e stato | `✓` `✔` `✗` `☑` `⚠` `ℹ` |
| Stelle e enfasi | `★` `✦` `✨` `❤` `◈` `※` |
| Numerici cerchiati | `①②③` `❶❷❸` `➊➋➌` |
| Separatori e linee | `│` `━` `〰` `═` `┼` |
| Citazioni e testo | `«»` `‹›` `""` `…` `‼` `⁉` |
| Simboli tipografici | `©` `®` `™` `§` `∞` `±` `÷` |
| Mani e gesti | `👉` `👆` `👍` `✍` `🤝` |
| Decorativi colorati | `🔹` `🔸` `🔺` `💠` `🟢` |

---

## Requisiti

- Linux (X11 o Wayland)
- Qt 6.2 o superiore
- CMake 3.16 o superiore
- Compilatore C++17 (GCC 10+ o Clang 12+)

---

## Compilazione

### Ubuntu / Debian

```bash
sudo apt install cmake qt6-base-dev
```

### Arch Linux

```bash
sudo pacman -S cmake qt6-base
```

### Fedora / RHEL

```bash
sudo dnf install cmake qt6-qtbase-devel
```

### Build

```bash
git clone <repo>
cd symbol_picker
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```

Il binario si trova in `build/symbol_picker`.

### Installazione opzionale

```bash
sudo make install   # installa in /usr/local/bin/symbol_picker
```

---

## Utilizzo

Avvia l'applicazione:

```bash
./build/symbol_picker
```

- **Sfoglia** le categorie scorrendo la lista
- **Cerca** digitando nella barra in alto — filtra per nome simbolo o categoria
- **Copia** cliccando su qualsiasi chip — appare un toast di conferma in basso
- **Incolla** nel tuo editor, browser o terminale con `Ctrl+V`

---

## Struttura del progetto

```
symbol_picker/
├── CMakeLists.txt      # configurazione build
├── main.cpp            # entry point
├── mainwindow.h        # dichiarazione finestra principale e SymbolChip
├── mainwindow.cpp      # implementazione UI, dati simboli, logica copia
├── flowlayout.h        # layout a flusso automatico (header)
├── flowlayout.cpp      # layout a flusso automatico (implementazione)
└── README.md           # questo file
```

---

## Licenza

MIT — libero per uso personale e commerciale.
