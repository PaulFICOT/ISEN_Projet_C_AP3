#ifndef BUTTON
#define BUTTON

#include "gtk/gtk.h"
#include "window_config.h"
#include <unistd.h>

void display_window_button(GtkWidget *widget, GtkWidget* window_create_charge);
void create_charge_button(GtkWidget *widget);
void modify_charge_button(GtkWidget *widget);
void delete_charge_button(GtkWidget *widget);
void generate_charge_button(GtkWidget *widget);
void clear_surface_button(GtkWidget *widget);
void start_process_button(GtkWidget *widget);

#endif
