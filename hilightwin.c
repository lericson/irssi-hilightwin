/**
 * Hilight window enabler.
 *
 * Sends all hilights to a certain window, prominently named "hilight".
 * Idea stolen from cras himself, along with znx. See URL:
 *   http://scripts.irssi.org/scripts/hilightwin.pl
 *
 * (Gee, I hope there are no licensing issues here.)
 */

#include "module.h"
#include "module-formats.h"

#include <core/modules.h>
#include <core/signals.h>
#include <core/settings.h>
#include <core/levels.h>

#include <fe-common/core/printtext.h>

#define HILIGHTWIN_NAME "hilight"

static void sig_print_text(TEXT_DEST_REC *dest, const char *text) {
    /* TODO Move this to a static global, so as to remove a function call/line
            printed. */
    int level = settings_get_level("hilightwin_level");

    if ((dest->level & level) && !(dest->level & MSGLEVEL_NOHILIGHT)) {
        WINDOW_REC *win = window_find_name(HILIGHTWIN_NAME);
        TEXT_DEST_REC new_dest;

        if (win == NULL) {
            printtext(dest->server, NULL, MSGLEVEL_CLIENTNOTICE,
                      "hilightwin cannot find window");
            return;
        }

        /* TODO Some context would be nice, I guess... */
        printtext_window(win, MSGLEVEL_NOHILIGHT | dest->level,
                         "%s/%s: %s", dest->server_tag, dest->target, text);
    }
}

void hilightwin_init(void) {
    module_register(MODULE_NAME, "core");

    settings_add_level(MODULE_NAME, "hilightwin_level", "HILIGHT");
    settings_check();

    signal_add("print text", (SIGNAL_FUNC)sig_print_text);
}

void hilightwin_deinit(void) {
    signal_remove("print text", (SIGNAL_FUNC)sig_print_text);
}
