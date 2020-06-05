#include "../includes/function_button.h"
#include <stdio.h>

/*
    Show the create charge's window
    widget (GtkWidget *) -> Widget of create charge button
    window_create_charge (GtkWidget *) -> Widget of create charge's window
*/
void display_window_create_charge_button(GtkWidget *widget, GtkWidget* window_create_charge) {
    /* Unused parameter but required field */
    (void) widget;
    gtk_widget_show_all(window_create_charge);
}

/*
    Create a new charge, add in the system charge and draw it
    widget (GtkWidget *) -> Widget of create button
*/
void create_charge_button(GtkWidget *widget) {
    /* Get all parameters */
    GtkWidget *grid = g_object_get_data(G_OBJECT(widget), "grid");
    GtkWidget *area = g_object_get_data(G_OBJECT(widget), "area");
    charge_system* main_charge_system = g_object_get_data(G_OBJECT(widget), "charge_system");

    /* Get all window's widgets */
    GtkWidget *spin_x = gtk_grid_get_child_at(GTK_GRID(grid), 0, 1);
    GtkWidget *spin_y = gtk_grid_get_child_at(GTK_GRID(grid), 0, 3);
    GtkWidget *entry_force = gtk_grid_get_child_at(GTK_GRID(grid), 0, 5);
    GtkWidget *entry_weight = gtk_grid_get_child_at(GTK_GRID(grid), 0, 7);
    GtkWidget *btn_switch = gtk_grid_get_child_at(GTK_GRID(grid), 0, 9);

    /* Get all widgets' value */
    gdouble coord_x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_x));
    gdouble coord_y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_y));
    double force = strtod(gtk_entry_get_text(GTK_ENTRY(entry_force)), NULL);
    double weight = strtod(gtk_entry_get_text(GTK_ENTRY(entry_weight)), NULL);
    gboolean is_fixed = gtk_switch_get_active(GTK_SWITCH(btn_switch));

    /* Check if the new charge is placeable in the charge system */
    coordinate *coord = coordinate_create(coord_x, coord_y);
    if (!charge_is_placeable(coord, main_charge_system)) {
        return;
    }

    /* Init variables for the new charge */
    enum symbol symbol;

    if (force > 0) {
        symbol = POSITIVE;
    }else if (force < 0) {
        symbol = NEGATIVE;
    }else {
        symbol = NEUTRAL;
    }

    charge* new_charge = charge_create(
        coord_x,
        coord_y,
        symbol,
        force,
        weight,
        is_fixed
    );

    /* Add charge in the charge system, then draw the charge */
    add_charge(main_charge_system, new_charge);

    if (is_fixed) {
        draw_fixed_charge(area, coord_x, coord_y);
    }else {
        draw_mobile_charge(area, coord_x, coord_y);
    }

    /* Reset widgets' value */ 
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_x), 0.0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_y), 0.0);
    gtk_entry_set_text(GTK_ENTRY(entry_force), "0");
    gtk_entry_set_text(GTK_ENTRY(entry_weight), "0");
    gtk_switch_set_active(GTK_SWITCH(btn_switch), FALSE);

    /* Hide the window */
    gtk_widget_hide(g_object_get_data(G_OBJECT(widget), "window"));
}

/*
    Button's function to clear surface
    widget (GtkWidget *) -> Widget of reset button
    area (GtkWidget *) -> Widget of drawing area
*/
void clear_surface_button(GtkWidget *widget, GtkWidget *area) {
    /* Unused parameter but required field */
    (void) widget;
    clear_surface();
    gtk_widget_queue_draw(area);
}

void start_process_button(GtkWidget *widget, gpointer data) {
    charge_system* main_charge_system = g_object_get_data(G_OBJECT(widget), "charge_system");
    charge* a = charge_create(0, 0, POSITIVE, 5E-4, 5, 1);
    charge* b = charge_create(15, 8, NEGATIVE, 3.7E-4, 5, 1);
    charge* c = charge_create(5, 13, POSITIVE, 1E-4, 5, 1);
    charge* d = charge_create(0, 4, NEGATIVE, 3.2E-4, 5, 1);
    charge* e = charge_create(23, 1, POSITIVE, 2.4E-4, 5, 1);
    charge* f = charge_create(-4, -16, NEGATIVE, 1.7E-4, 5, 0);
    add_charge(main_charge_system, a);
    add_charge(main_charge_system, b);
    add_charge(main_charge_system, c);
    add_charge(main_charge_system, d);
    add_charge(main_charge_system, e);
    add_charge(main_charge_system, f);
    redraw_surface(g_object_get_data(G_OBJECT(widget), "area"), main_charge_system);
    sleep(4);
    return;
    for (int i = 0; i < 20; i++) {
        sleep(1);
        calculate_next_pose(f, main_charge_system->charges, main_charge_system->charges_index);
        printf("%i: (%f, %f)\n", i, f->positions[f->positions_index]->x, f->positions[f->positions_index]->y);
        f->position = f->positions[f->positions_index];
        redraw_surface(g_object_get_data(G_OBJECT(widget), "area"), main_charge_system);
    }
}
