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
  GtkWidget *button_box;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add (GTK_CONTAINER (window), button_box);

  button = gtk_button_new_with_label ("Hello World");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_container_add (GTK_CONTAINER (button_box), button);

  fixed_charge c1 = fixed_charge_create(0.0, 0.0, POSITIVE, 50);
  fixed_charge c2 = fixed_charge_create(3.0, 7.0, NEGATIVE, 63);
  printf("%f\n", two_points_distance(c1.position, c2.position));
  printf("%f\n", coulomb_law(c1.force, c2.force, two_points_distance(c1.position, c2.position)));

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