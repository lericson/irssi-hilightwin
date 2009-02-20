/**
 * Hilight window enabler.
 *
 * Sends all hilights to a certain window, prominently named "hilight".
 * Idea stolen from cras himself, along with znx. See URL:
 *   http://scripts.irssi.org/scripts/hilightwin.pl
 *
 * (Gee, I hope there are no licensing issues here.)
 */

#include "hilightwin.h"

static void sig_print_text(TEXT_DEST_REC *dest, const char *text) {
    /* You say it best... when you say nothing at all. */
    return;
}

void hilightwin_init(void) {
    module_register(MODULE_NAME, "core");

    settings_add_bool(MODULE_NAME, "hilightwin_showprivmsg", TRUE);
    settings_check();

    signal_add("print text", (SIGNAL_FUNC)sig_print_text);
}

void hilightwin_deinit(void) {
    signal_remove("print text", (SIGNAL_FUNC)sig_print_text);
}
