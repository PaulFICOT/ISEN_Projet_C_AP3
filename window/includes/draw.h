#ifndef DRAW
#define DRAW

#include "gtk/gtk.h"
#include "window_config.h"
#include "../../logic/includes/charge_system.h"

#define CHARGE_RADIUS 14

gboolean init_surface(GtkWidget *widget);
gboolean prepare_surface(GtkWidget *widget, cairo_t *cr);
void clear_surface();
void draw_fixed_charge(GtkWidget *widget, gdouble x, gdouble y);
void draw_mobile_charge(GtkWidget *widget, gdouble x, gdouble y);
void redraw_surface(GtkWidget *widget, charge_system* main_charge_system);
gboolean clicked(GtkWidget *widget, GdkEventButton *event);

#endif
