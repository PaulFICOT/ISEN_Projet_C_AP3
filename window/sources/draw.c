#include "../includes/draw.h"

/* Surface cairo to contain charges */
static cairo_surface_t *surface = NULL;
static GtkWidget *window_charge = NULL;
char message[1024];

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

  return TRUE;
}

gboolean prepare_surface(GtkWidget *widget, cairo_t *cr) {
  /* Unused parameter but required field */
  (void) widget;
  cairo_set_source_surface(cr, surface, 0, 0);
  cairo_paint(cr);

  return FALSE;
}

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

coordinate* scale_coordinate(coordinate *coord) {
  return coordinate_create((WINDOW_WIDTH/2.0) + (m_to_nm(coord->x) * 20.0), (WINDOW_HEIGHT/2.0) - (m_to_nm(coord->y) * 20.0));
}

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

void redraw_surface(GtkWidget *widget, charge_system *main_charge_system) {
  clear_surface();

  /* Draw every charges */
  linked_list* iterator = main_charge_system->charges;
  while (!is_null(iterator)) {
    if (((charge*) iterator->value)->is_fixed) {
      draw_fixed_charge(widget, ((charge*) iterator->value)->position->x, ((charge*) iterator->value)->position->y);
    } else {
      draw_mobile_charge(widget, ((charge*) iterator->value)->position->x, ((charge*) iterator->value)->position->y);

      if (!get_state_simulation()) {
        vector *vector_charge = superposition_law(main_charge_system, (charge*) iterator->value);
        if (vector_charge != NULL) {
          draw_arrow(widget, vector_charge);
        }
      }
    }
    forward(&iterator, 1);
  }

  gtk_widget_queue_draw(widget);

  while (gtk_events_pending()) {
    gtk_main_iteration();
  }
}

void draw_arrow(GtkWidget *widget, vector *arrow) {
  coordinate *start = scale_coordinate(arrow->start);
  coordinate *end = scale_coordinate(coordinate_create(arrow->end->x, arrow->end->y));
  cairo_t *cr = cairo_create(surface);

  double arrow_angle = atan2(end->y - start->y, end->x - start->x) + M_PI;

  coordinate *arrow_arm_a = coordinate_create(end->x + ARROW_ARM_LENGTH * cos(arrow_angle + ARROW_DEGREES), end->y + ARROW_ARM_LENGTH * sin(arrow_angle + ARROW_DEGREES));
  coordinate *arrow_arm_b = coordinate_create(end->x + ARROW_ARM_LENGTH * cos(arrow_angle - ARROW_DEGREES), end->y + ARROW_ARM_LENGTH * sin(arrow_angle - ARROW_DEGREES));

  cairo_set_source_rgb(cr, 0, 0, 0);
  cairo_move_to(cr, start->x, start->y);
  cairo_line_to(cr, end->x, end->y);
  cairo_stroke(cr);

  cairo_move_to(cr, end->x, end->y);
  cairo_line_to(cr, arrow_arm_a->x, arrow_arm_a->y);
  cairo_stroke(cr);

  cairo_move_to(cr, end->x, end->y);
  cairo_line_to(cr, arrow_arm_b->x, arrow_arm_b->y);
  cairo_stroke(cr);

  cairo_destroy(cr);

  gtk_widget_queue_draw(widget);
}

gboolean clicked(GtkWidget *widget, GdkEventButton *mouse, charge_system *main_charge_system) {
  coordinate* coord = coordinate_create(nm_to_m((mouse->x - (WINDOW_WIDTH/2.0)) / 20.0), nm_to_m(((WINDOW_HEIGHT/2.0) - mouse->y) / 20.0));
  if (mouse->button == GDK_BUTTON_PRIMARY) {
    charge* a_charge = get_charge(main_charge_system, coord);

    if (window_charge != NULL) {
      gtk_widget_hide(window_charge);
      window_charge = NULL;
    }

    if (a_charge != NULL) {
      window_charge = init_charge_window(widget, main_charge_system, a_charge);
      gtk_widget_show_all(GTK_WIDGET(window_charge));
      gtk_window_set_keep_above(GTK_WINDOW(window_charge), TRUE);
    }else {
      int nbr_charge_system = length(main_charge_system->charges);

      if (charge_is_placeable(main_charge_system, coord) && (MAX_ENTRIES - (nbr_charge_system + 1)) >= 0 ) {
        add_charge(main_charge_system, random_charge(coord->x, coord->y, INFINITY));
        redraw_surface(widget, main_charge_system);
      }
    }
  }else if (mouse->button == GDK_BUTTON_SECONDARY) {
    snprintf(message, sizeof(message), "The electrostatic potential at (%lf, %lf) is %g V", coord->x, coord->y, electrostatic_potential(main_charge_system, coord));
    set_log(message);
  }

  return TRUE;
}
