#!/usr/bin/env python
"""Convert irssi UI formats into C source code."""

import sys
import optparse
import datetime
from itertools import chain, tee

# Option parser.
parser = optparse.OptionParser()
parser.add_option("--code", dest="code", default="module-formats.c", metavar="FILE",
    help="Actual definition is written to FILE.")
parser.add_option("--header", dest="header", default="module-formats.h", metavar="FILE",
    help="Header definition and enum is written to FILE.")
parser.add_option("--screen", "-n", dest="screen", action="store_true",
    default=False, help="Write all output to screen instead of separate files."
                        "Code is written to stdout, header to stderr.")

# Static texts.
prelude = """/**
 * THIS IS A GENERATED FILE.
 * DO NOT EDIT THIS, AS IT WILL BE OVERWRITTEN."""
code_prelude = """#include "module.h"
#include "formats.h"

FORMAT_REC ui_fmts[] = {"""
code_postlude = "};"
header_prelude = """#include "formats.h"

enum {"""
header_postlude = """};

extern FORMAT_REC ui_fmts[TXT_COUNT+1];"""

# Tokens.
module_name = object()
section_header = object()
format_def = object()

# TODO Make it work with UTF-8. (Impossible?)

def parse_signature(sign):
    if "(" not in sign or sign.endswith("()"):
        return sign.rstrip("()"), ()
    name, args = sign.split("(", 1)
    if not args.endswith(")"):
        raise ValueError("invalid signature: %r" % sign)
    args = map(str.strip, args[:-1].split(","))
    return name, args

def parse_lines(it):
    for line in it:
        line = line.rstrip("\r\n")
        if not line:
            continue
        elif line.startswith("-- "):
            yield module_name, (line[3:],)
        elif line.startswith("-> "):
            yield section_header, (line[3:],)
        else:
            signature, trail = line.split(" ", 1)
            format = trail.lstrip(" \t")
            yield format_def, (parse_signature(signature), format)

def generate_code(it):
    yield prelude
    yield " * " + str(datetime.datetime.now())
    yield " */"
    yield ""
    yield code_prelude
    for token, args in it:
        if token is module_name:
            yield '\t{ MODULE_NAME, "%s", 0 },' % args
        elif token is section_header:
            yield '\t{ NULL, "%s", 0 },' % args
        elif token is format_def:
            (name, types), format = args
            types = [("format_" + t).upper() for t in types]
            yield '\t{ "%s", "%s", %d, { %s }},' % (name, format, len(types),
                                                    ", ".join(types) or 0)
    yield "\t{ NULL, NULL, 0 }"
    yield code_postlude

def generate_header(it):
    yield prelude
    yield " * " + str(datetime.datetime.now())
    yield " */"
    yield ""
    yield header_prelude
    pad_no = 0
    for token, args in it:
        if token is module_name:
            name = "TXT_MODULE_NAME"
        elif token is section_header:
            pad_no += 1
            name = "TXT_PAD_%d" % pad_no
        elif token is format_def:
            name = ("txt_" + args[0][0]).upper()
        yield "\t%s," % name
    yield "\tTXT_COUNT"
    yield header_postlude

if __name__ == "__main__":
    opts, args = parser.parse_args()
    if opts.screen:
        code_fp, header_fp = sys.stdout, sys.stderr
    else:
        code_fp, header_fp = open(opts.code, "w"), open(opts.header, "w")
    fnames = args or ("ui-formats.txt",)
    inputs = chain(*tuple(parse_lines(open(fn)) for fn in fnames))
    code_lines, header_lines = tee(inputs, 2)
    code_gen = generate_code(code_lines)
    header_gen = generate_header(header_lines)
    for gen, fp in (code_gen, code_fp), (header_gen, header_fp):
        for line in gen:
            fp.write(line.replace("\t", "    ") + "\n")
        fp.close()
