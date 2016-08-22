#include <stdio.h>
#include <string.h>
#include <wayland-server.h>
#define ERR(...) fprintf(stderr, __VA_ARGS__)


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
	printf("TODO surface create\n");
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
	printf("TODO region create\n");
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
   printf("todo cb bind data\n");

   wl_resource_set_implementation(res, &_comp_interface, todo_data, NULL);
}


static void
_comp_wl_subcompositor_cb_destroy(struct wl_client *client, struct wl_resource *resource)
{
   wl_resource_destroy(resource);
}

static void
_comp_wl_subcompositor_cb_subsurface_get(struct wl_client *client, struct wl_resource *resource, uint32_t id, struct wl_resource *surface_resource, struct wl_resource *parent_resource)
{
	printf("subsurface get TODO \n");
	/*
   E_Client *ec, *epc = NULL;
   static const char where[] = "get_subsurface: wl_subsurface@";

   if (!(ec = wl_resource_get_user_data(surface_resource))) return;
   if (!(epc = wl_resource_get_user_data(parent_resource))) return;

   if (ec == epc)
     {
        wl_resource_post_error(resource, WL_SUBCOMPOSITOR_ERROR_BAD_SURFACE,
                               "%s%d: wl_surface@%d cannot be its own parent",
                               where, id, wl_resource_get_id(surface_resource));
        return;
     }

   if (e_object_is_del(E_OBJECT(ec))) return;
   if (e_object_is_del(E_OBJECT(epc))) return;

   // check if this surface is already a sub-surface
   if ((ec->comp_data) && (ec->comp_data->sub.data))
     {
        wl_resource_post_error(resource,
                               WL_SUBCOMPOSITOR_ERROR_BAD_SURFACE,
                               "%s%d: wl_surface@%d is already a sub-surface",
                               where, id, wl_resource_get_id(surface_resource));
        return;
     }

   // try to create a new subsurface
   if (!_e_comp_wl_subsurface_create(ec, epc, id, surface_resource))
     ERR("Failed to create subsurface for surface %d",
         wl_resource_get_id(surface_resource));

	 */
}




static const struct wl_subcompositor_interface _subcomp_interface =
{
   _comp_wl_subcompositor_cb_destroy,
   _comp_wl_subcompositor_cb_subsurface_get
};

static void
_comp_wl_subcompositor_cb_bind(struct wl_client *client, void *data, uint32_t version, uint32_t id)
{
   struct wl_resource *res;

   if (!(res =
         wl_resource_create(client, &wl_subcompositor_interface,
                            version, id)))
     {
        ERR("Could not create subcompositor resource");
        wl_client_post_no_memory(client);
        return;
     }

   printf("todo cb bind data, subcomp\n");
   void *todo_data = NULL;
   wl_resource_set_implementation(res, &_subcomp_interface, todo_data, NULL);

}

#define COMPOSITOR_VERSION 4
void init_tmp(struct wl_display* display)
{
	printf("TODO data init \n");
	void* data = NULL;

	if (!wl_global_create(display, &wl_compositor_interface,
                         COMPOSITOR_VERSION, data,
                         _compositor_cb_bind))
     {
        printf("Could not add compositor to wayland globals\n");
     } 

	  /* try to add subcompositor to wayland globals */
   if (!wl_global_create(display, &wl_subcompositor_interface, 1,
                         data, _comp_wl_subcompositor_cb_bind))
     {
        ERR("Could not add subcompositor to wayland globals");
     }


}
