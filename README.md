<img width="512" height="336" alt="xfileselect" src="https://github.com/user-attachments/assets/c3eb81ad-0348-4e0a-8eb4-d4169ac4b6cf" />

# xfileselect

A tiny, single-file X11 file/directory chooser for C programs.

- Standalone or embeddable via `#include "xfileselect.c"`
- File or directory selection mode
- Comma-separated extension filters (e.g. `.mid,.midi,.cmf`)
- Configurable appearance via `#define`s (sizes, font, colors, header/footer text)
- Text drawn with a font built into the program ([xbmfont](https://github.com/realgraybox/xbmfont), bundled): the same look on every X server, UTF-8 file names, long names shortened with "…"
- Grows for large screens: `x11_filechooser_font()` sets a bigger font, and the window, paddings and columns follow
- Minimal dependencies: X11 only

## Example usage

```c
// example_main.c

// Optional: override visual defaults before including the implementation
#define FC_DEFAULT_WIDTH   400
#define FC_DEFAULT_HEIGHT  500

// Include the implementation (it pulls in xfileselect.h itself)
#include "xfileselect.c"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *path = x11_filechooser(
        "/home/user",                 // start_path (NULL => current dir)
        "Open File",                  // window title
        "Select a MIDI file",         // header text (shown above file list)
        ".mid,.midi,.cmf",            // extension filter (NULL or "" => all)
        FC_MODE_FILE,                 // FC_MODE_FILE or FC_MODE_DIR
        "[q/Esc]: Cancel [Enter]: Open"  // status/help line
    );

    if (path) {
        printf("Chosen: %s\n", path);
        free(path);
    } else {
        printf("No file chosen.\n");
    }

    return 0;
}
```

Build (the bundled `xbmfont/` must be on the include path):

```bash
gcc -I./xbmfont example_main.c -o example_main -lX11
```

or just `make`. `./example_main 2` shows the dialog at double size.

## Features

- **Modes**
  - `FC_MODE_FILE`: navigate directories, select a file.
  - `FC_MODE_DIR`: navigate directories, select a directory.
- **Filtering**
  - Comma-separated extensions, e.g. `".mid,.midi,.cmf"`.
  - Directories are always shown.
- **Visual customization**
  - Define before `#include "xfileselect.c"`:
    - `FC_DEFAULT_WIDTH`, `FC_DEFAULT_HEIGHT`
    - `FC_FONT`, `FC_FONT_SCALE`: the text font, an [xbmfont](https://github.com/realgraybox/xbmfont) font (default `xbf_fixed_6x13` at scale 1, which looks like X's own "fixed" font). Other sizes are in the xbmfont repository's `fonts/`; include the header first, e.g. `#include "fonts/xbf_fixed_10x20.h"` and `#define FC_FONT xbf_fixed_10x20`.
    - Sizes (`FC_DEFAULT_WIDTH`, paddings, `FC_FILE_TEXT_X`, `FC_INFO_TEXT_X` ...) are given for a 13 px font; with a bigger font they grow in step.
    - Color strings: `FC_HEADER_BG_COLOR`, `FC_LIST_BG_COLOR`, etc. (hex like `"0x222222"` or `"#222222"`)
    - Text: `FC_DEFAULT_HELP_TEXT`
  - Header text and window title are set per call.
- **Size at run time**
  - `x11_filechooser_font(font, scale)` sets the font for the dialogs opened after it (`NULL` = `FC_FONT`), e.g. to match the program's own text on a large screen.
- **Text**
  - File names may be UTF-8; bytes that are not valid UTF-8 are shown as Windows-1252/Latin-1, so old 8-bit names still show right.
  - A name too long for its column is shortened in the middle, so its extension stays visible; header and help line end in "…" if the window is too narrow.

## Files

- `xfileselect.h` – public API (`FCMode`, `x11_filechooser()`, `x11_filechooser_font()`).
- `xfileselect.c` – implementation (include once per project).
- `example_main.c` – minimal example program.
- `xbmfont/` – the bundled font library (`xbmfont.h`, the 6x13 font, its licence).

## Building your own program

Either:

- Include the implementation directly in one `.c` file:

  ```c
  #define FC_DEFAULT_WIDTH 400
  #include "xfileselect.c"
  ```

  xfileselect.c also compiles the xbmfont implementation. If your program
  compiles it elsewhere (because it draws its own text with xbmfont too),
  `#define FC_NO_XBMFONT_IMPLEMENTATION` before the include - or include
  xfileselect.c after your own `#define XBMFONT_IMPLEMENTATION`, as midiero
  does.

- Or compile separately:

  ```bash
  gcc -I./xbmfont -c xfileselect.c -o xfileselect.o
  gcc -I./xbmfont -o myapp myapp.c xfileselect.o -lX11
  ```

  In this case, put any `#define` visual overrides in a config header included by `xfileselect.c`.

## License

See the license text at the top of `xfileselect.c` and `xfileselect.h`.
The bundled xbmfont is zlib licensed (`xbmfont/LICENSE`); its fonts are public
domain.

