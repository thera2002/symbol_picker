# Symbol Picker

A Linux desktop application to browse and copy special characters, Unicode symbols, and emoji — useful for posts, documents, and everyday text editing.

Click any chip → the symbol is instantly in your clipboard.

---

## Features

- **~180 symbols** organised into 12 categories
- **Live search** by symbol name or category
- **One-click copy** — immediate visual feedback (green flash + toast notification)
- Flow layout that adapts automatically to the window width
- Respects the system colour palette (light and dark themes)

### Included categories

| Category | Examples |
|---|---|
| Bullet points | `•` `‣` `◦` `–` `—` |
| Arrows | `→` `⇒` `➤` `↳` `↩` `▶` |
| Solid shapes | `●` `■` `▲` `◆` `◉` |
| Outline shapes | `○` `□` `△` `◇` `▷` |
| Check & status | `✓` `✔` `✗` `☑` `⚠` `ℹ` |
| Stars & emphasis | `★` `✦` `✨` `❤` `◈` `※` |
| Circled numbers | `①②③` `❶❷❸` `➊➋➌` |
| Separators & lines | `│` `━` `〰` `═` `┼` |
| Quotes & text | `«»` `‹›` `""` `…` `‼` `⁉` |
| Typography | `©` `®` `™` `§` `∞` `±` `÷` |
| Hands & gestures | `👉` `👆` `👍` `✍` `🤝` |
| Coloured decorators | `🔹` `🔸` `🔺` `💠` `🟢` |

---

## Requirements

- Linux (X11 or Wayland)
- Qt 6.2 or later
- CMake 3.16 or later
- C++17 compiler (GCC 10+ or Clang 12+)

---

## Building

### Install dependencies

**Ubuntu / Debian**
```bash
sudo apt install cmake qt6-base-dev
```

**Arch Linux**
```bash
sudo pacman -S cmake qt6-base
```

**Fedora / RHEL**
```bash
sudo dnf install cmake qt6-qtbase-devel
```

### Compile

```bash
git clone <repo>
cd symbol_picker
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```

The binary is placed at `build/symbol_picker`.

### Optional install

```bash
sudo make install   # installs to /usr/local/bin/symbol_picker
```

---

## Usage

Launch the application:

```bash
./build/symbol_picker
```

- **Browse** categories by scrolling the list
- **Search** by typing in the top bar — filters by symbol name or category
- **Copy** by clicking any chip — a confirmation toast appears at the bottom
- **Paste** in your editor, browser or terminal with `Ctrl+V`

---

## Project structure

```
symbol_picker/
├── CMakeLists.txt      # build configuration
├── main.cpp            # entry point
├── mainwindow.h        # MainWindow and SymbolChip declarations
├── mainwindow.cpp      # UI, symbol data, copy logic
├── flowlayout.h        # auto-wrapping flow layout (header)
├── flowlayout.cpp      # auto-wrapping flow layout (implementation)
└── README.md           # this file
```

---

## License

MIT — free for personal and commercial use.
