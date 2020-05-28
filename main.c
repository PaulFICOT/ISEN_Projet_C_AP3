/*Headers*/
#include <stdio.h>
#include <stdlib.h>
#include "gtk/gtk.h"
#include "logic/includes/charge_system.h"

static void print_hello (GtkWidget *widget, gpointer data) {
  g_print ("Hello World\n");
}

static void activate (GtkApplication *app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *grid_box;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW (window), "Simulateur d'interaction électrostatiques");
  gtk_window_set_default_size(GTK_WINDOW (window), 800, 600);

  grid_box = gtk_grid_new();
  gtk_container_add (GTK_CONTAINER (window), grid_box);

  button = gtk_button_new_with_label ("Hello World");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  gtk_grid_attach(GTK_GRID (grid_box), button, 1, 1, 2, 2);

  // charge c1 = charge_create(0.0, 0.0, POSITIVE, 0.25E-6, 0, 1);
  // charge c2 = charge_create(0.052704364, 0.052704364, NEGATIVE, -0.5E-6, 0, 0);
  // printf("%f\n", coulomb_law(c1, c2));
  
  gtk_widget_show_all (window);
}

int main (int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}