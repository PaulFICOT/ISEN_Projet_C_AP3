#ifndef CONFIG
#define CONFIG

#include "gtk/gtk.h"
#include <regex.h> 
#include "./draw.h"
#include "./function_button.h"
#include "../../logic/includes/charge_system.h"

/*
    Window's size constant
*/
#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 480
#define WINDOW_CREATE_CHARGE_WIDTH  200
#define WINDOW_CREATE_CHARGE_HEIGHT 300

void activate(GtkApplication *app);
gboolean hide_create_charge_window(GtkWidget *widget);
void check_insert_entry(GtkWidget *widget, gchar *new_text);
GtkWidget* init_create_charge_window(GtkWidget* area, charge_system* main_charge_system);

#endif
