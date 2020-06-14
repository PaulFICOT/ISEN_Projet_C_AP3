#ifndef DRAW
#define DRAW

#include "gtk/gtk.h"
#include "window_config.h"
#include "../../logic/includes/charge_system.h"
#include "../../constants.h"

/**
 * Initialize a surface
 *
 * @param widget The object which received the signal
 *
 * @return Stop other handlers from being invoked for the event
 */
gboolean init_surface(GtkWidget *widget);

/**
 * Prepare surface to draw on
 *
 * @param widget The object which received the signal
 * @param cr The cairo context to draw on
 *
 * @return Propagate the event further
 */
gboolean prepare_surface(GtkWidget *widget, cairo_t *cr);

/**
 * Clear surface
 * Draw a new surface
 */
void clear_surface();

/**
 * Scale the coordinate with the graduation
 *
 * @param coord The coordinate to scale
 *
 * @return new coordinate instance with scaled coordinate
 */
coordinate* scale_coordinate(coordinate *coord);

/**
 * Draw fixed charge at given coordinate
 *
 * @param widget Drawing area's widget
 * @param x The coordinate x of the fixed charge
 * @param y The coordinate y of the fixed charge
 */
void draw_fixed_charge(GtkWidget *widget, gdouble x, gdouble y);

/**
 * Draw mobile charge at given coordinate
 *
 * @param widget Drawing area's widget
 * @param x The coordinate x of the mobile charge
 * @param y The coordinate y of the mobile charge
 */
void draw_mobile_charge(GtkWidget *widget, gdouble x, gdouble y);

/**
 * Redraw a surface with all charges in the charge system
 *
 * @param widget The widget of drawing area
 * @param main_charge_system The charge system which contains all charges
 */
void redraw_surface(GtkWidget *widget, charge_system* main_charge_system);

/**
 * Draw arrow on the surface from a vector given
 *
 * @param widget The widget of drawing area
 * @param arrow Vector to draw the arrow
 */
void draw_arrow(GtkWidget *widget, vector *arrow);

/**
 * Display information of charge at mouse's coordinate
 *
 * @param widget The object which received the signal
 * @param mouse The GdkEventButton which triggered this signal
 * @param main_charge_system The system charge with all charges
 *
 * @return Stop other handlers from being invoked for the event
 */
gboolean clicked(GtkWidget *widget, GdkEventButton *mouse, charge_system *main_charge_system);

#endif
