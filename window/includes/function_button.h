#ifndef BUTTON
#define BUTTON

#include "gtk/gtk.h"
#include "window_config.h"

void display_window_create_charge_button(GtkWidget *widget, GtkWidget* window_create_charge);
void create_charge_button(GtkWidget *widget);
void clear_surface_button(GtkWidget *widget, GtkWidget *area);
void start_process_button(GtkWidget *widget, gpointer data);

#endif
