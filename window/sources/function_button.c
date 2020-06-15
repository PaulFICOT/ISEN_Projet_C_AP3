#include "../includes/function_button.h"
#include <stdio.h>

static gboolean state_simulation = FALSE;
char message[1024];

void display_window_button(GtkWidget *widget, GtkWidget* window_charge) {
    if (state_simulation) {
        if (strcmp(gtk_button_get_label(GTK_BUTTON(widget)), "Stop") == 0) {
            state_simulation = FALSE;
            set_log("Simulation has been stopped");
            set_label_btn_simulation("Start");
        }else set_log("Simulation running");
        return;
    }
    gtk_widget_show_all(window_charge);
}

void create_charge_button(GtkWidget *widget) {
    if (state_simulation) {
        set_log("Simulation running");
        return;
    }

    /* Get all parameters */
    GtkWidget *grid = g_object_get_data(G_OBJECT(widget), "grid");
    GtkWidget *area = g_object_get_data(G_OBJECT(widget), "area");
    charge_system* main_charge_system = g_object_get_data(G_OBJECT(widget), "charge_system");

    /* Get all window's widgets */
    GtkWidget *spin_x = gtk_grid_get_child_at(GTK_GRID(grid), 0, 1);
    GtkWidget *spin_y = gtk_grid_get_child_at(GTK_GRID(grid), 0, 3);
    GtkWidget *spin_force = gtk_grid_get_child_at(GTK_GRID(grid), 0, 5);
    GtkWidget *entry_weight = gtk_grid_get_child_at(GTK_GRID(grid), 0, 7);
    GtkWidget *btn_switch = gtk_grid_get_child_at(GTK_GRID(grid), 0, 9);

    /* Get all widgets' value */
    gdouble coord_x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_x));
    gdouble coord_y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_y));
    gdouble force = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_force));
    gdouble weight = g_strtod(gtk_entry_get_text(GTK_ENTRY(entry_weight)), NULL);
    gboolean is_fixed = gtk_switch_get_active(GTK_SWITCH(btn_switch));

    int nbr_charge_system = length(main_charge_system->charges);

    if ((MAX_ENTRIES - (nbr_charge_system+1)) < 0) {
        snprintf(message, sizeof(message), "You have exceeded the maximum number of charges in the system, That is %d.", MAX_ENTRIES);
        set_log(message);
        return;
    }

    /* Check if the new charge is placeable in the charge system */
    coordinate *coord = coordinate_create(coord_x, coord_y);
    if (!charge_is_placeable(main_charge_system, coord)) {
        set_log("There is already a charge at the coordinate");
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
        fabs(force),
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
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_force), 0.0);
    gtk_entry_set_text(GTK_ENTRY(entry_weight), "0,0");
    gtk_switch_set_active(GTK_SWITCH(btn_switch), FALSE);

    /* Hide the window */
    gtk_widget_hide(g_object_get_data(G_OBJECT(widget), "window"));
    set_log("");
}

void modify_charge_button(GtkWidget *widget) {
    if (state_simulation) {
        set_log("Simulation running");
        return;
    }

    charge *a_charge = g_object_get_data(G_OBJECT(widget), "a_charge");
    charge_system* main_charge_system = g_object_get_data(G_OBJECT(widget), "charge_system");
    GtkWidget *grid = g_object_get_data(G_OBJECT(widget), "grid");

    /* Get new charge's coordinate */
    GtkWidget *spin_x = gtk_grid_get_child_at(GTK_GRID(grid), 0, 1);
    GtkWidget *spin_y = gtk_grid_get_child_at(GTK_GRID(grid), 0, 3);
    coordinate *new_coord_charge = coordinate_create(gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_x)), gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_y)));

    delete(&main_charge_system->charges, a_charge);

    /* Check if the new charge's coordinate is placeable */
    if (charge_is_placeable(main_charge_system, new_coord_charge)) {
        create_charge_button(widget);
    }else {
        set_log("There is already a charge at the coordinate");
        add_charge(main_charge_system, a_charge);
    }

    redraw_surface(g_object_get_data(G_OBJECT(widget), "area"), main_charge_system);
}

void delete_charge_button(GtkWidget *widget) {
    if (state_simulation) {
        set_log("Simulation running");
        return;
    }

    charge_system* main_charge_system = g_object_get_data(G_OBJECT(widget), "charge_system");

    /* WIP delete function */
    delete(&main_charge_system->charges, g_object_get_data(G_OBJECT(widget), "a_charge"));

    /* Refresh the surface */
    redraw_surface(g_object_get_data(G_OBJECT(widget), "area"), main_charge_system);

    /* Hide the window */
    gtk_widget_hide(g_object_get_data(G_OBJECT(widget), "window"));
    set_log("");
}

void generate_charge_button(GtkWidget *widget) {
    if (state_simulation) {
        set_log("Simulation running");
        return;
    }

    /* Get all parameters */
    GtkWidget *grid = g_object_get_data(G_OBJECT(widget), "grid");
    GtkWidget *area = g_object_get_data(G_OBJECT(widget), "area");
    charge_system* main_charge_system = g_object_get_data(G_OBJECT(widget), "charge_system");

    /* Get number of charge to generate */
    GtkWidget *spin_mobile = gtk_grid_get_child_at(GTK_GRID(grid), 0, 2);
    GtkWidget *spin_fixed = gtk_grid_get_child_at(GTK_GRID(grid), 0, 4);
    gint nbr_charge_mobile = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_mobile));
    gint nbr_charge_fixed = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_fixed));
    int nbr_charge_system = length(main_charge_system->charges);

    if (nbr_charge_mobile == 0 && nbr_charge_fixed == 0) {
        set_log("You must add at least one charge");
        return;
    }

    if ((MAX_ENTRIES - (nbr_charge_mobile + nbr_charge_fixed + nbr_charge_system)) < 0) {
        snprintf(message, sizeof(message), "You have exceeded the maximum number of charges, There are %d in the system and the maximum is %d.", nbr_charge_system, MAX_ENTRIES);
        set_log(message);
        return;
    }

    /* Generate mobile charge and check if it is placeable before add it in charge system */
    while (nbr_charge_mobile != 0) {
        charge *new_charge = random_charge(0);
        if (charge_is_placeable(main_charge_system, new_charge->position)) {
            add_charge(main_charge_system, new_charge);
            nbr_charge_mobile--;
        }
    }

    /* Generate fixed charge */
    while (nbr_charge_fixed != 0) {
        charge *new_charge = random_charge(1);
        if (charge_is_placeable(main_charge_system, new_charge->position)) {
            add_charge(main_charge_system, new_charge);
            nbr_charge_fixed--;
        }
    }

    /* refresh surface with new charges */
    redraw_surface(area, main_charge_system);

    /* Reset widgets' value */
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_mobile), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_fixed), 0);

    /* Hide the window */
    gtk_widget_hide(g_object_get_data(G_OBJECT(widget), "window"));
    set_log("");
}

void clear_surface_button(GtkWidget *widget) {
    if (state_simulation) {
        set_log("Simulation running");
        return;
    }

    reset_charge_system(g_object_get_data(G_OBJECT(widget), "charge_system"));
    clear_surface();
    gtk_widget_queue_draw(g_object_get_data(G_OBJECT(widget), "area"));
    set_log("");
}

void start_process_button(GtkWidget *widget) {
    if (state_simulation) {
        set_log("Simulation already running");
        return;
    }

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
    charge* b = charge_create(0, -5, NEGATIVE, 4, 4E-5, 0);
    // charge* c = charge_create(5, 5, POSITIVE, 5E-4, 5, 1);
    // charge* d = charge_create(-5, -5, NEGATIVE, 5E-4, 5, 1);
    // charge* e = charge_create(5, 5, NEGATIVE, 5E-4, 5, 1);
    add_charge(main_charge_system, a);
    add_charge(main_charge_system, b);

    int nbr_charge_system = length(main_charge_system->charges);

    if (nbr_charge_system == 0) {
        set_log("There is no charges in the system.");
        return;
    }

    state_simulation = TRUE;
    set_label_btn_simulation("Stop");
    set_log("Simulation has been started");
    redraw_surface(area, main_charge_system);
    struct timespec t={0,100};
    for (int i = 0; i < time; i++) {
        nanosleep(&t,0);
        calculate_next_pose(main_charge_system, b);
        printf("%i: (%f, %f)\n", i, b->position->x, b->position->y);
        redraw_surface(area, main_charge_system);
        if (!state_simulation) {
            return;
        }
    }
    redraw_surface(area, main_charge_system);
    state_simulation = FALSE;
    set_log("Simulation done");
    set_label_btn_simulation("Start");
}

gboolean get_state_simulation() {
    return state_simulation;
}
