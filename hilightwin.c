/**
 * Hilight window enabler.
 *
 * Sends all hilights to a certain window, prominently named "hilight".
 * Idea stolen from cras himself, along with znx. See URL:
 *   http://scripts.irssi.org/scripts/hilightwin.pl
 *
 * (Gee, I hope there are no licensing issues here.)
 */

#include <irssi/irssi-config.h>
#include <irssi/irssi-version.h>

#include "common.h"
#include "core/modules.h"
#include "core/signals.h"
#include "core/settings.h"
#include "core/levels.h"
#include "fe-common/core/printtext.h"

#define MODULE_NAME "hilightwin"
#define HILIGHTWIN_NAME "hilight"

static void sig_print_text(TEXT_DEST_REC *dest, const char *text) {
    int level = settings_get_level("hilightwin_level");
    WINDOW_REC *win = window_find_name(HILIGHTWIN_NAME);

    if (!(dest->level & level) || (dest->level & MSGLEVEL_NOHILIGHT)) {
        return;
    }

    if (win == NULL) {
        printtext(NULL, NULL, MSGLEVEL_CLIENTNOTICE,
                  "hilightwin cannot find window with name: %s",
                  HILIGHTWIN_NAME);
        return;
    }

    printtext_window(win, MSGLEVEL_NOHILIGHT | dest->level,
                     "%s/%s: %s", dest->server_tag, dest->target, text);
}

void hilightwin_init(void) {
    module_register(MODULE_NAME, "core");

    settings_add_level(MODULE_NAME, "hilightwin_level", "HILIGHT");
    settings_check();

    signal_add("print text", (SIGNAL_FUNC)sig_print_text);

    printtext(NULL, NULL, MSGLEVEL_CLIENTNOTICE,
              "%s loaded for %s", MODULE_NAME, PACKAGE_STRING);
}

void hilightwin_deinit(void) {
    signal_remove("print text", (SIGNAL_FUNC)sig_print_text);
}
