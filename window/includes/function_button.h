#ifndef BUTTON
#define BUTTON

#include "gtk/gtk.h"
#include "window_config.h"
#include <unistd.h>

/**
 * Show the window
 *
 * @param widget Widget of clicked button
 * @param window_charge Widget of the window
 */
void display_window_button(GtkWidget *widget, GtkWidget* window_create_charge);

/**
 * Create a new charge, add it in the system charge and draw it
 *
 * @param widget Widget of create button with parameters on it
 */
void create_charge_button(GtkWidget *widget);

/**
 * Modify a charge and redraw it on the surface
 *
 * @param widget The widget of modify button with parameters on it
 */
void modify_charge_button(GtkWidget *widget);

/**
 * Delete a charge and refresh the surface
 *
 * @param widget The widget of delete button with parameters on it
 */
void delete_charge_button(GtkWidget *widget);

/**
 * Generate charge with random characteristics
 *
 * @param widget Widget of generate button with parameters on it
 */
void generate_charge_button(GtkWidget *widget);

/**
 * Button's function to clear surface
 *
 * @param widget Widget of reset button with parameters on it
 */
void clear_surface_button(GtkWidget *widget);

/**
 * Start process with a time given (milliseconds)
 *
 * @param widget Widget of start button with parameters on it
 */
void start_process_button(GtkWidget *widget);

#endif
