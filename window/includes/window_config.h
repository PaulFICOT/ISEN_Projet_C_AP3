#ifndef CONFIG
#define CONFIG

#include "gtk/gtk.h"
#include <regex.h>
#include "./draw.h"
#include "./function_button.h"
#include "../../logic/includes/charge_system.h"
#include "../../constants.h"

void activate(GtkApplication *app);
gboolean hide_window(GtkWidget *widget);
void check_insert_widget(GtkWidget *widget, gchar *new_text);
GtkWidget* init_charge_window(GtkWidget* area, charge_system* main_charge_system, charge* a_charge);
GtkWidget* init_generate_window(GtkWidget* area, charge_system* main_charge_system);
GtkWidget* init_start_window(GtkWidget* area, charge_system* main_charge_system);

#endif
