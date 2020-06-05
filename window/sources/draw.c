#include "../includes/draw.h"

/* Surface cairo to contain charges */
static cairo_surface_t *surface = NULL;

/* 
  Initialize a surface
  widget (GtkWidget *) -> The object which received the signal
*/
gboolean init_surface(GtkWidget *widget) {
  surface = gdk_window_create_similar_surface(gtk_widget_get_window (widget),
                                               CAIRO_CONTENT_COLOR,
                                               gtk_widget_get_allocated_width (widget),
                                               gtk_widget_get_allocated_height (widget));

  cairo_t *cr = cairo_create(surface);

  cairo_set_source_rgb(cr, 1, 1, 1);
  /* Paint all surface to white */
  cairo_paint(cr);

  /* Add graduation background on surface */
  cairo_surface_t* image = cairo_image_surface_create_from_png("graduation.png");
  cairo_set_source_surface(cr, image, 0, 0);
  cairo_paint(cr); 

  cairo_destroy(cr);

  /* Stop other handlers from being invoked for the event */
  return TRUE;
}

/* 
  Prepare surface to draw on
  widget (GtkWidget *) -> The object which received the signal
  cr (cairo_t *) -> The cairo context to draw to
*/
gboolean prepare_surface(GtkWidget *widget, cairo_t *cr) {
  /* Unused parameter but required field */
  (void) widget;
  cairo_set_source_surface(cr, surface, 0, 0);
  cairo_paint(cr);

  /* Propagate the event further */
  return FALSE;
}

/* 
  Clear surface
  Draw a new surface
*/
void clear_surface() {
  cairo_t *cr = cairo_create(surface);

  cairo_set_source_rgb(cr, 1, 1, 1);
  /* Paint all surface to white */
  cairo_paint(cr);

  /* Add graduation background on surface */
  cairo_surface_t* image = cairo_image_surface_create_from_png("graduation.png");
  cairo_set_source_surface(cr, image, 0, 0);
  cairo_paint(cr); 

  cairo_destroy (cr);
}

/* 
  Draw fixed charge at given coordinate
  widget (GtkWidget *) -> Drawing area's widget
  x (gdouble) -> The coordinate x of the fixed charge
  y (gdouble) -> The coordinate y of the fixed charge
*/
void draw_fixed_charge(GtkWidget *widget, gdouble x, gdouble y) {
  cairo_t *cr = cairo_create(surface);

  /* Scale the coordinate with the graduation */
  x = (WINDOW_WIDTH/2) + (x * 8);
  y = (WINDOW_HEIGHT/2) - (y * 8);

  cairo_set_source_rgb(cr, 0.50, 0.50, 0.50);
  /* Draw a sphere of radius CHARGE_RADIUS */
  cairo_arc(cr ,x ,y ,CHARGE_RADIUS ,0 , 2*G_PI);
  cairo_fill(cr);
  cairo_set_source_rgb(cr, 1, 1, 1);

  cairo_destroy(cr);

  /* Invalidate the affected region of the drawing area. */
  gtk_widget_queue_draw_area(widget, x-CHARGE_RADIUS, y-CHARGE_RADIUS, CHARGE_RADIUS*2, CHARGE_RADIUS*2);
}

/* 
  Draw mobile charge at given coordinate
  widget (GtkWidget *) -> Drawing area's widget
  x (gdouble) -> The coordinate x of the mobile charge
  y (gdouble) -> The coordinate y of the mobile charge
*/
void draw_mobile_charge(GtkWidget *widget, gdouble x, gdouble y) {
  cairo_t *cr = cairo_create(surface);

  /* Scale the coordinate with the graduation */
  x = (WINDOW_WIDTH/2) + (x * 8);
  y = (WINDOW_HEIGHT/2) - (y * 8);

  cairo_set_source_rgb(cr, 0.93, 0.83, 0.83);
  /* Draw a sphere of radius CHARGE_RADIUS */
  cairo_arc(cr ,x ,y ,CHARGE_RADIUS ,0 , 2*G_PI);
  cairo_fill(cr);
  cairo_set_source_rgb(cr, 1, 1, 1);

  cairo_destroy(cr);

  /* Invalidate the affected region of the drawing area. */
  gtk_widget_queue_draw_area(widget, x-CHARGE_RADIUS, y-CHARGE_RADIUS, CHARGE_RADIUS*2, CHARGE_RADIUS*2);
}

/*
  Redraw a surface with all charges in the charge system
  widget (GtkWidget*) -> The widget of drawing area
  main_charge_system (charge_system*) -> The charge system which contains all charges
*/
void redraw_surface(GtkWidget *widget, charge_system *main_charge_system) {
  clear_surface();
  
  /* Draw every charges */
  backtrack(&(main_charge_system->charges));
  while (main_charge_system->charges != NULL) {
    if (((charge*)main_charge_system->charges->value)->is_fixed) {
      draw_fixed_charge(widget, ((charge*)main_charge_system->charges->value)->position->x, ((charge*)main_charge_system->charges->value)->position->y);
    } else {
      draw_mobile_charge(widget, ((charge*)main_charge_system->charges->value)->position->x, ((charge*)main_charge_system->charges->value)->position->y);
    }
    main_charge_system->charges = main_charge_system->charges->next;
  }
}

/* 
  Draw charge in relation to the mouse click
  widget (GtkWidget *) -> The object which received the signal
  event (GdkEventButton *) -> The GdkEventButton which triggered this signal
*/
gboolean clicked(GtkWidget *widget, GdkEventButton *event) {
    /* Draw fixed charge if user uses primary button else draw mobile charge */
    if (event->button == GDK_BUTTON_PRIMARY) {
      draw_fixed_charge(widget, event->x, event->y);
    } else if (event->button == GDK_BUTTON_SECONDARY) {
      draw_mobile_charge(widget, event->x, event->y);
    }

    /* Stop other handlers from being invoked for the event */
    return TRUE;
}
