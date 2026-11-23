// example_main.c

// Override visual defaults BEFORE including filemanager_xlib.c
#define FC_DEFAULT_WIDTH   400
#define FC_DEFAULT_HEIGHT  300
// Text font: any xbmfont font; this is the default, which looks like X's "fixed"
#include "fonts/xbf_fixed_6x13.h"
#define FC_FONT            xbf_fixed_6x13
#define FC_HEADER_PADDING_Y     10
#define FC_STATUS_PADDING_Y     10

#define FC_FILE_TEXT_X          10
#define FC_INFO_TEXT_X          300



// Include the implementation exactly once in one translation unit:
#include "xfileselect.c"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    // "./example_main 2": the same font scaled x2, window and columns follow
    if (argc > 1)
        x11_filechooser_font(&xbf_fixed_6x13, atoi(argv[1]));

    char *path = x11_filechooser(
        "/home/user",                 // start_path
        "My App – Open File",         // title (WM)
        "Select a MIDI file",         // header_text (shown above file list)
        ".mid,.midi,.cmf",            // filter_ext
        FC_MODE_FILE,                 // mode
        "[q/Esc]: Cancel [Enter]: Open"  // help_text
    );

    if (path) {
        printf("Chosen: %s\n", path);
        free(path);
    } else {
        printf("No file chosen.\n");
    }

    return 0;
}
