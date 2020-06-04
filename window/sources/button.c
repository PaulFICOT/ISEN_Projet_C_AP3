#include "../includes/button.h"

void displayWindowCreateCharge(GtkWidget *widget, gpointer data) {
    /* Unused parameter but required field */
    (void) widget;
    gtk_widget_show_all(data);
}

void createCharge(GtkWidget *widget) {
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
    gdouble coord_x = (WINDOW_WIDTH/2) + (gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_x)) * 8);
    gdouble coord_y = (WINDOW_HEIGHT/2) - (gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_y)) * 8);
    double force = strtod(gtk_entry_get_text(GTK_ENTRY(entry_force)), NULL);
    double weight = strtod(gtk_entry_get_text(GTK_ENTRY(entry_weight)), NULL);
    gboolean is_fixed = gtk_switch_get_active(GTK_SWITCH(btn_switch));

    enum symbol symbol;

    if (force > 0) {
        symbol = POSITIVE;
    }else if (force < 0) {
        symbol = NEGATIVE;
    }else {
        symbol = NEUTRAL;
    }

    charge* new_charge = charge_create(
        gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_x)),
        gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_y)),
        symbol,
        force,
        weight,
        is_fixed
    );

    add_charge(main_charge_system, new_charge);

    if (is_fixed) {
        draw_fixed_charge(area, coord_x, coord_y);
    }else {
        draw_mobile_charge(area, coord_x, coord_y);
    }

    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_x), 0.0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_y), 0.0);
    gtk_entry_set_text(GTK_ENTRY(entry_force), "0");
    gtk_entry_set_text(GTK_ENTRY(entry_weight), "0");
    gtk_switch_set_active(GTK_SWITCH(btn_switch), FALSE);

    gtk_widget_hide(g_object_get_data(G_OBJECT(widget), "window"));
}

void clearSurface(GtkWidget *widget, gpointer data) {
    /* Unused parameter but required field */
    (void) widget;
    clear_surface();
    gtk_widget_queue_draw(data);
}

void startProcess(GtkWidget *widget, gpointer data) {
    charge_system* main_charge_system = g_object_get_data(G_OBJECT(widget), "charge_system");
    charge* a = charge_create(0, 0, POSITIVE, 5E-4, 5, 1);
    charge* b = charge_create(3, 6, NEGATIVE, 3.7E-4, 5, 1);
    charge* c = charge_create(5, 4, POSITIVE, 1E-4, 5, 1);
    charge* d = charge_create(5, 4, NEGATIVE, 3.2E-4, 5, 1);
    charge* e = charge_create(3, 1, POSITIVE, 2.4E-4, 5, 1);
    charge* f = charge_create(8, 1, NEGATIVE, 1.7E-4, 5, 0);
    printf("ici\n");
    add_charge(main_charge_system, a);
    printf("pas la\n");
    add_charge(main_charge_system, b);
    add_charge(main_charge_system, c);
    add_charge(main_charge_system, d);
    add_charge(main_charge_system, e);
    add_charge(main_charge_system, f);
    vector* sup = superposition_law(main_charge_system->charges, main_charge_system->charges_index, f);
    printf("%f - %f\n", sup->direction, sup->magnitude);
}
