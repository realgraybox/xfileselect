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
