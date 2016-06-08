# An Irssi Hilight Window Of My Own

IRC is full of noise. It's nice to have your hilights in their own window. This
module does that.

Why is a module, I hear you ask, rather than a Perl script? Because Perl is an
abomination unto God. Irssi's script mechanism doubly so. So if you want to go
to heaven, you had better use this module instead. And remove Perl support!

## Compilation & Installation

You will need: some hundreds of irssi header files, a C compiler and linker,
and make. First download the source of irssi-hilightwin, then compile the code
using a simple `make`. If you don't have the Irssi source code, there is a
downloader provided. Just run it. Since it might download the wrong version of
Irssi, you're probably better off just reinstalling Irssi and keeping the
sources somewhere.

Irssi looks for modules in `~/.irssi/modules/`, so I suggest simply moving
`libhilightwin.so` there. Then load it into Irssi with `/load hilightwin`.
Actually, just add the line `load hilightwin` to `~/.irssi/startup`. Boom.

Then there is the windows. Create a window named `hilight` by the following incantation in Irssi:

    /window new split
    /window name hilight
    /window stick on
    /window immortal on
    /window shrink (... shrink until satisfied)
    /layout save

That's it, really.
