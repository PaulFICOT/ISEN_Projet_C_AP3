#ifndef CONFIG
#define CONFIG

#include "gtk/gtk.h"
#include <regex.h>
#include "./draw.h"
#include "./function_button.h"
#include "../../logic/includes/charge_system.h"
#include "../../constants.h"

/**
 * Configure main window with different widgets and show it
 *
 * @param app The application to start
 */
void activate(GtkApplication *app);

/**
 * Hide the window
 *
 * @param widget The object which received the signal
 *
 * @return Stop other handlers from being invoked for the event
 */
gboolean hide_window(GtkWidget *widget);

/**
 * Check the user's input in the widget
 *
 * @param widget The widget which received the signal
 * @param new_text Text typed by the user
 */
void check_insert_widget(GtkWidget *widget, gchar *new_text);

/**
 * Configure a charge window with differents widgets, then return it
 *
 * @param area Widget of drawing area
 * @param main_charge_system The charge system which contains all charges
 * @param a_charge The charge to modify if NULL it's a create charge window
 *
 * @return create a window instance with all widgets set up
 */
GtkWidget* init_charge_window(GtkWidget* area, charge_system* main_charge_system, charge* a_charge);

/**
 * Configure a generate charge window with differents widgets, then return it
 *
 * @param area Widget of drawing area
 * @param main_charge_system The charge system which contains all charges
 *
 * @return create a window instance with all widgets set up
 */
GtkWidget* init_generate_window(GtkWidget* area, charge_system* main_charge_system);

/**
 * Configure a start simulation window with differents widgets, then return it
 *
 * @param area Widget of drawing area
 * @param main_charge_system The charge system which contains all charges
 *
 * @return create a window instance with all widgets set up
 */
GtkWidget* init_start_window(GtkWidget* area, charge_system* main_charge_system);

/**
 * Get the instance of the statusbar widget
 *
 * @return the current instance of the widget
 */
GtkWidget* get_statusbar();

#endif
