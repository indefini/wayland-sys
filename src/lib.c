#include <stdio.h>
#include <string.h>
#include <wayland-server.h>

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

static void
_comp_wl_compositor_cb_surface_create(struct wl_client *client, struct wl_resource *resource, uint32_t id)
{
	//TODO
	struct wl_resource *res;
	pid_t pid;

	printf("Compositor Cb Surface Create: %d\n", id);

	/* try to create an internal surface */
	if (!(res = wl_resource_create(client, &wl_surface_interface,
					wl_resource_get_version(resource), id)))
	{
		printf("Could not create compositor surface\n");
		wl_client_post_no_memory(client);
		return;
	}

	printf("\tCreated Resource: %d\n", wl_resource_get_id(res));

	/* set implementation on resource */
	/*
	wl_resource_set_implementation(res, &_e_surface_interface, NULL,
			_e_comp_wl_surface_destroy);

	wl_client_get_credentials(client, &pid, NULL, NULL);
	if (pid == getpid()) //internal!
		ec = e_pixmap_find_client(E_PIXMAP_TYPE_WL, (int64_t)id);
		*/

}

static void
_comp_wl_compositor_cb_region_create(struct wl_client *client, struct wl_resource *resource, uint32_t id)
{
	//TODO
}

static const struct wl_compositor_interface _comp_interface =
{
   _comp_wl_compositor_cb_surface_create,
   _comp_wl_compositor_cb_region_create
};

static void
_compositor_cb_bind(struct wl_client *client, void *data, uint32_t version, uint32_t id)
{
   struct wl_resource *res;

   if (!(res = wl_resource_create(client, &wl_compositor_interface,
                            version, id)))
     {
        printf("Could not create compositor resource\n");
        wl_client_post_no_memory(client);
        return;
     }

   void* todo_data = NULL;

   wl_resource_set_implementation(res, &_comp_interface, todo_data, NULL);
}



#define COMPOSITOR_VERSION 4
void init_tmp(struct wl_display* display)
{
	void* data = NULL;

	if (!wl_global_create(display, &wl_compositor_interface,
                         COMPOSITOR_VERSION, data,
                         _compositor_cb_bind))
     {
        printf("Could not add compositor to wayland globals\n");
     }
}
