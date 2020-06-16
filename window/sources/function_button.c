#include "../includes/function_button.h"
#include <stdio.h>

static gboolean state_simulation = FALSE;
char message[1024];


void display_window_button(GtkWidget *widget, GtkWidget* window_charge) {
    if (state_simulation) {
        if (strcmp(gtk_button_get_label(GTK_BUTTON(widget)), "Stop") == 0) {
            state_simulation = FALSE;
            set_log("Simulation stopped");
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
    GtkWidget *entry_force = gtk_grid_get_child_at(GTK_GRID(grid), 0, 5);
    GtkWidget *entry_weight = gtk_grid_get_child_at(GTK_GRID(grid), 0, 7);
    GtkWidget *btn_switch = gtk_grid_get_child_at(GTK_GRID(grid), 0, 9);

    /* Get all widgets' value */
    gdouble coord_x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_x));
    gdouble coord_y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_y));
    gdouble force = g_strtod(gtk_entry_get_text(GTK_ENTRY(entry_force)), NULL);
    gdouble weight = g_strtod(gtk_entry_get_text(GTK_ENTRY(entry_weight)), NULL);
    gboolean is_fixed = gtk_switch_get_active(GTK_SWITCH(btn_switch));

    int nbr_charge_system = length(main_charge_system->charges);

    if ((MAX_ENTRIES - (nbr_charge_system+1)) < 0) {
        snprintf(message, sizeof(message), "You have exceeded the maximum number of charges in the system, which is %d.", MAX_ENTRIES);
        set_log(message);
        return;
    }

    /* Check if the new charge is placeable in the charge system */
    coordinate *coord = coordinate_create(coord_x, coord_y);
    if (!charge_is_placeable(main_charge_system, coord)) {
        set_log("There is already a charge at these coordinates");
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
    gtk_entry_set_text(GTK_ENTRY(entry_force), "0,0");
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
    } else {
        set_log("There is already a charge at these coordinates");
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
        snprintf(message, sizeof(message), "You have exceeded the maximum number of charges, There is %d in the system and the maximum is %d.", nbr_charge_system, MAX_ENTRIES);
        set_log(message);
        return;
    }

    /* Generate mobile charge and check if it is placeable before add it in charge system */
    while (nbr_charge_mobile != 0) {
        charge *new_charge = random_charge(INFINITY, INFINITY, 0);
        if (charge_is_placeable(main_charge_system, new_charge->position)) {
            add_charge(main_charge_system, new_charge);
            nbr_charge_mobile--;
        }
    }

    /* Generate fixed charge */
    while (nbr_charge_fixed != 0) {
        charge *new_charge = random_charge(INFINITY, INFINITY, 1);
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

    if (length(main_charge_system->charges) == 0) {
        set_log("There is no charge in the system.");
        return;
    }

    state_simulation = TRUE;
    set_label_btn_simulation("Stop");
    set_log("Simulation started");
    redraw_surface(area, main_charge_system);
    struct timespec t={0,100};
    for (int i = 0; i < time; i++) {
        nanosleep(&t,0);
        linked_list* iterator = main_charge_system->charges;
        while (!is_null(iterator)) {
            if (!((charge*)iterator->value)->is_fixed) {
                calculate_next_pose(main_charge_system, (charge*)iterator->value);
                printf("%i: (%f, %f)\n", i, ((charge*)iterator->value)->position->x, ((charge*)iterator->value)->position->y);
            }
            forward(&iterator, 1);
        }
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
