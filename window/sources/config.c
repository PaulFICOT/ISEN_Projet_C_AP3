#include "../includes/config.h"

/* 
  Configure window with differents widgets
  app (GtkApplication *) -> The application to start
  data (gpointer) -> Data set when the signal handler was connected
*/
void activate (GtkApplication *app, gpointer data) {
  GtkWidget *window;
  GtkWidget *area;
  GtkWidget *grid;
  GtkWidget *hbtnbox;
  GtkWidget *btn_back;
  GtkWidget *btn_home;

  window = gtk_application_window_new (app);
  gtk_window_set_title(GTK_WINDOW (window), "Simulateur d'interaction électrostatiques");
  gtk_widget_set_size_request (window, WINDOW_WIDTH, WINDOW_HEIGHT);
  gtk_window_set_has_resize_grip (GTK_WINDOW(window), FALSE);

  area = gtk_drawing_area_new();
  gtk_widget_set_size_request (area, WINDOW_WIDTH, WINDOW_HEIGHT);
  g_signal_connect (area, "draw", G_CALLBACK (prepare_surface), NULL);
  g_signal_connect (area, "configure-event", G_CALLBACK (init_surface), NULL);
  g_signal_connect(area, "button-press-event", G_CALLBACK(clicked), NULL);

  gtk_widget_set_events(area, gtk_widget_get_events(area) | GDK_BUTTON_PRESS_MASK | GDK_POINTER_MOTION_MASK);

  hbtnbox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_button_box_set_layout(GTK_BUTTON_BOX(hbtnbox), GTK_BUTTONBOX_CENTER);
  gtk_box_set_spacing(GTK_BOX(hbtnbox), 20);
  gtk_widget_set_margin_bottom(GTK_WIDGET(hbtnbox), 10); 
  gtk_widget_set_margin_top(GTK_WIDGET(hbtnbox), 10);

  btn_back = gtk_button_new_with_label("Create charge");
  btn_home = gtk_button_new_with_label("Start");

  gtk_widget_set_size_request(GTK_WIDGET(btn_back), 100, 45);
  gtk_widget_set_size_request(GTK_WIDGET(btn_home), 100, 45);

  gtk_box_pack_start(GTK_BOX(hbtnbox), btn_back, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(hbtnbox), btn_home, FALSE, FALSE, 0);

  grid = gtk_grid_new ();

  gtk_grid_attach (GTK_GRID(grid), GTK_WIDGET(area), 0, 0, 1, 1);

  gtk_grid_attach (GTK_GRID(grid), GTK_WIDGET(hbtnbox), 0, 1, 1, 1);

  gtk_container_add (GTK_CONTAINER (window), grid);

  gtk_widget_show_all (window);
}
