#include "../includes/function_button.h"
#include <stdio.h>

/*
    Show the window
    widget (GtkWidget *) -> Widget of clicked button
    window_charge (GtkWidget *) -> Widget of the window
*/
void display_window_button(GtkWidget *widget, GtkWidget* window_charge) {
    /* Unused parameter but required field */
    (void) widget;
    gtk_widget_show_all(window_charge);
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
    if (!charge_is_placeable(main_charge_system, coord)) {
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

    /* Refresh surface */
    redraw_surface(area, main_charge_system);

    /* Reset widgets' values */
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_x), 0.0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_y), 0.0);
    gtk_entry_set_text(GTK_ENTRY(entry_force), "0");
    gtk_entry_set_text(GTK_ENTRY(entry_weight), "0");
    gtk_switch_set_active(GTK_SWITCH(btn_switch), FALSE);

    /* Hide the window */
    gtk_widget_hide(g_object_get_data(G_OBJECT(widget), "window"));
}

void modify_charge_button(GtkWidget *widget) {
    charge *a_charge = g_object_get_data(G_OBJECT(widget), "a_charge");
    charge_system* main_charge_system = g_object_get_data(G_OBJECT(widget), "charge_system");

    delete_charge(main_charge_system, a_charge);

    if (charge_is_placeable(main_charge_system, a_charge->position)) {
        create_charge_button(widget);
    }else {
        add_charge(main_charge_system, a_charge);
    }

    redraw_surface(g_object_get_data(G_OBJECT(widget), "area"), main_charge_system);
}

void delete_charge_button(GtkWidget *widget) {
    charge_system* main_charge_system = g_object_get_data(G_OBJECT(widget), "charge_system");

    /* WIP delete function */
    delete_charge(main_charge_system, g_object_get_data(G_OBJECT(widget), "a_charge"));

    /* Refresh the surface */
    redraw_surface(g_object_get_data(G_OBJECT(widget), "area"), main_charge_system);

    /* Hide the window */
    gtk_widget_hide(g_object_get_data(G_OBJECT(widget), "window"));
}

/*
    Generate charge with random characteristics
    widget (GtkWidget *) -> Widget of generate button
*/
void generate_charge_button(GtkWidget *widget) {
    /* Get all parameters */
    GtkWidget *grid = g_object_get_data(G_OBJECT(widget), "grid");
    GtkWidget *area = g_object_get_data(G_OBJECT(widget), "area");
    charge_system* main_charge_system = g_object_get_data(G_OBJECT(widget), "charge_system");

    /* Get number of charge to generate */
    GtkWidget *spin = gtk_grid_get_child_at(GTK_GRID(grid), 0, 1);
    gdouble nbr_charge = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin));

    /* Generate charge and check if it is placeable before add it in charge system */
    while (nbr_charge != 0) {
        charge *new_charge = random_charge();
        if (charge_is_placeable(main_charge_system, new_charge->position)) {
            add_charge(main_charge_system, new_charge);
            nbr_charge--;
        }
    }

    /* refresh surface with new charges */
    redraw_surface(area, main_charge_system);

    /* Reset widgets' value */
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin), 0);

    /* Hide the window */
    gtk_widget_hide(g_object_get_data(G_OBJECT(widget), "window"));
}

/*
    Button's function to clear surface
    widget (GtkWidget *) -> Widget of reset button
*/
void clear_surface_button(GtkWidget *widget) {
    reset_charge_system(g_object_get_data(G_OBJECT(widget), "charge_system"));
    clear_surface();
    gtk_widget_queue_draw(g_object_get_data(G_OBJECT(widget), "area"));
}

void start_process_button(GtkWidget *widget) {
    charge_system* main_charge_system = g_object_get_data(G_OBJECT(widget), "charge_system");
    GtkWidget *area = g_object_get_data(G_OBJECT(widget), "area");
    GtkWidget *grid = g_object_get_data(G_OBJECT(widget), "grid");

    /* Get all window's widgets */
    GtkWidget *spin = gtk_grid_get_child_at(GTK_GRID(grid), 0, 1);
    gint time = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin));
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin), 0);

    /* Hide the window */
    gtk_widget_hide(g_object_get_data(G_OBJECT(widget), "window"));
    // charge* a = charge_create(0, 0, POSITIVE, 5E-4, 5, 1);
    // charge* b = charge_create(15, 8, NEGATIVE, 3.7E-4, 5, 0);
    // charge* c = charge_create(5, 13, POSITIVE, 1E-4, 5, 1);
    // charge* d = charge_create(0, 4, NEGATIVE, 3.2E-4, 5, 1);
    // charge* e = charge_create(23, 1, POSITIVE, 2.4E-4, 5, 1);
    // charge* f = charge_create(-4, -16, NEGATIVE, 1.7E-4, 5, 0);
    // add_charge(main_charge_system, a);
    // add_charge(main_charge_system, b);
    // add_charge(main_charge_system, c);
    // add_charge(main_charge_system, d);
    // add_charge(main_charge_system, e);
    // add_charge(main_charge_system, f);
    // redraw_surface(g_object_get_data(G_OBJECT(widget), "area"), main_charge_system);
    // for (int i = 0; i < 5; i++) {
    //     sleep(1);
    //     calculate_next_pose(main_charge_system, b);
    //     printf("%i: (%f, %f)\n", i, b->positions[b->positions_index]->x, b->positions[b->positions_index]->y);
    //     b->position = b->positions[b->positions_index];
    //     redraw_surface(g_object_get_data(G_OBJECT(widget), "area"), main_charge_system);
    // }
    // redraw_surface(g_object_get_data(G_OBJECT(widget), "area"), main_charge_system);
    charge* a = charge_create(0, 0, POSITIVE, 3, 3E-4, 1);
    charge* b = charge_create(-5, -5, NEGATIVE, 4, 4E-5, 0);
    // charge* c = charge_create(5, 5, POSITIVE, 5E-4, 5, 1);
    // charge* d = charge_create(-5, -5, NEGATIVE, 5E-4, 5, 1);
    // charge* e = charge_create(5, 5, NEGATIVE, 5E-4, 5, 1);
    add_charge(main_charge_system, a);
    add_charge(main_charge_system, b);
    redraw_surface(area, main_charge_system);
    struct timespec t={0,100};
    for (int i = 0; i < (time+1); i++) {
        nanosleep(&t,0);
        backtrack(&main_charge_system->charges);
        calculate_next_pose(main_charge_system, b);
        printf("%i: (%f, %f)\n", i, b->positions[b->positions_index]->x, b->positions[b->positions_index]->y);
        b->position = b->positions[b->positions_index];
        redraw_surface(area, main_charge_system);
    }
    redraw_surface(area, main_charge_system);
}
