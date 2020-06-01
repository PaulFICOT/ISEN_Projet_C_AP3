#include "../includes/button.h"

void displayWindowCreateCharge(GtkWidget *widget, gpointer data) {
    gtk_widget_show_all(data);
}

void createCharge(GtkWidget *widget, gpointer data) {
    GtkWidget *grid = g_object_get_data(G_OBJECT(widget), "grid");
    GtkWidget *area = g_object_get_data(G_OBJECT(widget), "area");
    GtkWidget *spin_x = gtk_grid_get_child_at(GTK_GRID(grid), 0, 1);
    GtkWidget *spin_y = gtk_grid_get_child_at(GTK_GRID(grid), 0, 3);
    GtkWidget *btn_switch = gtk_grid_get_child_at(GTK_GRID(grid), 0, 5);
    gdouble coord_x = (WINDOW_WIDTH/2) + (gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_x)) * 8);
    gdouble coord_y = (WINDOW_HEIGHT/2) - (gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_y)) * 8);
    gboolean is_fixed = gtk_switch_get_active(GTK_SWITCH(btn_switch));

    if (is_fixed) {
        draw_fixed_charge(area, coord_x, coord_y);
    }else draw_mobile_charge(area, coord_x, coord_y);

    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_x), 0.0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_y), 0.0);
    gtk_switch_set_active(GTK_SWITCH(btn_switch), FALSE);

    gtk_widget_hide(g_object_get_data(G_OBJECT(widget), "window"));
}

void clearSurface(GtkWidget *widget, gpointer data) {
    clear_surface();
    gtk_widget_queue_draw(data);
}
