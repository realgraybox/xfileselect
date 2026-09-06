/*
 * Copyright (C) 2026 M. Glargaard, aka graybox
 *
 * This software is provided "as-is", without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would
 *    be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not
 *    be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */
// xfileselect.h
#ifndef FILEMANAGER_XLIB_H
#define FILEMANAGER_XLIB_H

typedef enum {
    FC_MODE_FILE,
    FC_MODE_DIR
} FCMode;

/*
 * Open a small X11 file/directory chooser dialog.
 *
 * start_path   : Initial directory (NULL => current working directory).
 * title        : Window title for WM (NULL => "Filechooser").
 * header_text  : Text shown in header above file list (NULL => no header).
 * filter_ext   : Comma-separated extension list, e.g. ".mid,.midi,.cmf".
 *                NULL or "" => no filtering (all files shown).
 * mode         : FC_MODE_FILE to select a file, FC_MODE_DIR to select a directory.
 * help_text    : Status-line help text (NULL => built-in default).
 *
 * Returns:
 *   malloc'd string with the selected path on success,
 *   NULL if canceled, error, or no selection.
 *
 * Caller must free() the returned string.
 */
char *x11_filechooser(const char *start_path,
                      const char *title,
                      const char *header_text,
                      const char *filter_ext,
                      FCMode mode,
                      const char *help_text);

#endif // FILEMANAGER_XLIB_H
