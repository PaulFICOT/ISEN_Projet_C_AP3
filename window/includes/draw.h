#include "gtk/gtk.h"

gboolean init_surface(GtkWidget *widget, GdkEventConfigure *event, gpointer data);
gboolean prepare_surface(GtkWidget *widget, cairo_t *cr, gpointer data);
void draw_fixed_charge(GtkWidget *widget, gdouble x, gdouble y);
void draw_mobile_charge(GtkWidget *widget, gdouble x, gdouble y);
gboolean clicked(GtkWidget *widget, GdkEventButton *event, gpointer user_data);
