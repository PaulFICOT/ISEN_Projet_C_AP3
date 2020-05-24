#include "../includes/draw.h"

/* Surface cairo to contain charges */
static cairo_surface_t *surface = NULL;

/* 
  Initialize a surface
  widget (GtkWidget *) -> The object which received the signal
  event (GdkEventConfigure *) -> The GdkEventConfigure which triggered this signal
  data (gpointer) -> Data set when the signal handler was connected
*/
gboolean init_surface(GtkWidget *widget, GdkEventConfigure *event, gpointer data) {
  surface = gdk_window_create_similar_surface (gtk_widget_get_window (widget),
                                               CAIRO_CONTENT_COLOR,
                                               gtk_widget_get_allocated_width (widget),
                                               gtk_widget_get_allocated_height (widget));

  cairo_t *cr = cairo_create (surface);

  cairo_set_source_rgb (cr, 1, 1, 1);
  /* Paint all surface to white */
  cairo_paint (cr);

  cairo_destroy (cr);

  /* Stop other handlers from being invoked for the event */
  return TRUE;
}

/* 
  Prepare surface to draw on
  widget (GtkWidget *) -> The object which received the signal
  cr (cairo_t *) -> The cairo context to draw to
  data (gpointer) -> Data set when the signal handler was connected
*/
gboolean prepare_surface(GtkWidget *widget, cairo_t *cr, gpointer data) {
  cairo_set_source_surface (cr, surface, 0, 0);
  cairo_paint (cr);

  /* Propagate the event further */
  return FALSE;
}

/* 
  Draw fixed charge at given coordinate
  widget (GtkWidget *) -> Drawing area's widget
  x (gdouble) -> The coordinate x of the fixed charge
  y (gdouble) -> The coordinate y of the fixed charge
*/
void draw_fixed_charge(GtkWidget *widget, gdouble x, gdouble y) {
  cairo_t *cr = cairo_create (surface);

  cairo_set_source_rgb (cr, 0.50, 0.50, 0.50);
  /* Draw a sphere of radius 14 */
  cairo_arc (cr ,x ,y ,14 ,0 , 2*G_PI);
  cairo_fill (cr);
  cairo_set_source_rgb (cr, 1, 1, 1);

  cairo_destroy (cr);

  /* Invalidate the affected region of the drawing area. */
  gtk_widget_queue_draw_area (widget, x-14, y-14, 28, 28);
}

/* 
  Draw mobile charge at given coordinate
  widget (GtkWidget *) -> Drawing area's widget
  x (gdouble) -> The coordinate x of the mobile charge
  y (gdouble) -> The coordinate y of the mobile charge
*/
void draw_mobile_charge(GtkWidget *widget, gdouble x, gdouble y) {
  cairo_t *cr = cairo_create (surface);

  cairo_set_source_rgb (cr, 0.93, 0.83, 0.83);
  /* Draw a sphere of radius 14 */
  cairo_arc (cr ,x ,y ,14 ,0 , 2*G_PI);
  cairo_fill (cr);
  cairo_set_source_rgb (cr, 1, 1, 1);

  cairo_destroy (cr);

  /* Invalidate the affected region of the drawing area. */
  gtk_widget_queue_draw_area (widget, x-14, y-14, 28, 28);
}

/* 
  Draw charge in relation to the mouse click
  widget (GtkWidget *) -> The object which received the signal
  event (GdkEventButton *) -> The GdkEventButton which triggered this signal
  data (gpointer) -> Data set when the signal handler was connected
*/
gboolean clicked(GtkWidget *widget, GdkEventButton *event, gpointer data) {
    /* Draw fixed charge if user uses primary button else draw mobile charge */
    if (event->button == GDK_BUTTON_PRIMARY) {
      draw_fixed_charge (widget, event->x, event->y);
    } else if (event->button == GDK_BUTTON_SECONDARY) {
      draw_mobile_charge (widget, event->x, event->y);
    }

    /* Stop other handlers from being invoked for the event */
    return TRUE;
}
