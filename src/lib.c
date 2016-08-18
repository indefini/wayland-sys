#include <stdio.h>
#include <string.h>
#include <wayland-server-core.h>

struct Signals
{
	struct wl_signal create;
	struct wl_signal activate;
	struct wl_signal kill;
};

struct wl_signal* create_signal()
{
	struct wl_signal* signal = calloc(1, sizeof *signal);
	return signal;
}

struct Signals* create_signals()
{
	struct Signals* signals = calloc(1, sizeof *signals);
	
	wl_signal_init(&signals->create);
	wl_signal_init(&signals->activate);
	wl_signal_init(&signals->kill);

	return signals;
}

void init_tmp(struct wl_display* display)
{

}
