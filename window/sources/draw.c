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
  Scale the coordinate with the graduation
  coord (coordinate*) -> The coordinate to scale
*/
coordinate* scale_coordinate(coordinate *coord) {
  coord->x = (WINDOW_WIDTH/2.0) + (coord->x * 8.0);
  coord->y = (WINDOW_HEIGHT/2.0) - (coord->y * 8.0);

  return coord;
}

/* 
  Draw fixed charge at given coordinate
  widget (GtkWidget *) -> Drawing area's widget
  x (gdouble) -> The coordinate x of the fixed charge
  y (gdouble) -> The coordinate y of the fixed charge
*/
void draw_fixed_charge(GtkWidget *widget, gdouble x, gdouble y) {
  cairo_t *cr = cairo_create(surface);
  coordinate* coord = scale_coordinate(coordinate_create(x, y));

  cairo_set_source_rgb(cr, 0.50, 0.50, 0.50);
  /* Draw a sphere of radius CHARGE_RADIUS */
  cairo_arc(cr ,coord->x ,coord->y ,CHARGE_RADIUS ,0 , 2*G_PI);
  cairo_fill(cr);
  cairo_set_source_rgb(cr, 1, 1, 1);

  cairo_destroy(cr);

  /* Invalidate the affected region of the drawing area. */
  gtk_widget_queue_draw_area(widget, (coord->x)-CHARGE_RADIUS, (coord->y)-CHARGE_RADIUS, CHARGE_RADIUS*2, CHARGE_RADIUS*2);
}

/* 
  Draw mobile charge at given coordinate
  widget (GtkWidget *) -> Drawing area's widget
  x (gdouble) -> The coordinate x of the mobile charge
  y (gdouble) -> The coordinate y of the mobile charge
*/
void draw_mobile_charge(GtkWidget *widget, gdouble x, gdouble y) {
  cairo_t *cr = cairo_create(surface);
  coordinate* coord = scale_coordinate(coordinate_create(x, y));

  cairo_set_source_rgb(cr, 0.93, 0.83, 0.83);
  /* Draw a sphere of radius CHARGE_RADIUS */
  cairo_arc(cr ,coord->x ,coord->y ,CHARGE_RADIUS ,0 , 2*G_PI);
  cairo_fill(cr);
  cairo_set_source_rgb(cr, 1, 1, 1);

  cairo_destroy(cr);

  /* Invalidate the affected region of the drawing area. */
  gtk_widget_queue_draw_area(widget, (coord->x)-CHARGE_RADIUS, (coord->y)-CHARGE_RADIUS, CHARGE_RADIUS*2, CHARGE_RADIUS*2);
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
  while (has_next(main_charge_system->charges)) {
    if (current_charge(main_charge_system)->is_fixed) {
      draw_fixed_charge(widget, current_charge(main_charge_system)->position->x, current_charge(main_charge_system)->position->y);
    } else {
      draw_mobile_charge(widget, current_charge(main_charge_system)->position->x, current_charge(main_charge_system)->position->y);
    }
    forward(&(main_charge_system->charges), 1);
  }

  gtk_widget_queue_draw(widget);
  
  while (gtk_events_pending()) {
    gtk_main_iteration();
  }
}

/* 
  Display information of charge at mouse's coordinate
  widget (GtkWidget *) -> The object which received the signal
  mouse (GdkEventButton *) -> The GdkEventButton which triggered this signal
  main_charge_system (charge_system *) -> The system charge with all charges
*/
gboolean clicked(GtkWidget *widget, GdkEventButton *mouse, charge_system *main_charge_system) {
  /* Unused parameter but required field */
  (void) widget;
  coordinate* coord = coordinate_create((mouse->x - (WINDOW_WIDTH/2.0)) / 8.0, ((WINDOW_HEIGHT/2.0) - mouse->y) / 8.0);
  charge* a_charge = get_charge(main_charge_system, coord);

  if (a_charge != NULL) {
    printf("Charge force -> %lf\n", a_charge->force);
  }

  /* Stop other handlers from being invoked for the event */
  return TRUE;
}
