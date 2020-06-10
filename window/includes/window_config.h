#ifndef CONFIG
#define CONFIG

#include "gtk/gtk.h"
#include <regex.h> 
#include "./draw.h"
#include "./function_button.h"
#include "../../logic/includes/charge_system.h"
#include "../../constants.h"

void activate(GtkApplication *app);
gboolean hide_charge_window(GtkWidget *widget);
void check_insert_entry(GtkWidget *widget, gchar *new_text);
GtkWidget* init_charge_window(GtkWidget* area, charge_system* main_charge_system, charge* a_charge);

#endif
