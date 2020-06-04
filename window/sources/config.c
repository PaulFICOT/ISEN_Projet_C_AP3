#include "../includes/config.h"

/* 
  Configure window with differents widgets
  app (GtkApplication *) -> The application to start
  data (gpointer) -> Data set when the signal handler was connected
*/
void activate (GtkApplication *app) {
  GtkWidget *window;
  GtkWidget *area;
  GtkWidget *grid;
  GtkWidget *hbtnbox;
  GtkWidget *btn_reset;
  GtkWidget *btn_create;
  GtkWidget *btn_start;

  charge_system* main_charge_system = charge_system_create();

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW (window), "Simulateur d'interaction électrostatiques");
  gtk_widget_set_size_request(window, WINDOW_WIDTH, WINDOW_HEIGHT);
  gtk_window_set_resizable (GTK_WINDOW(window), FALSE);

  area = gtk_drawing_area_new();
  gtk_widget_set_size_request(area, WINDOW_WIDTH, WINDOW_HEIGHT);
  g_signal_connect(area, "draw", G_CALLBACK (prepare_surface), NULL);
  g_signal_connect(area, "configure-event", G_CALLBACK (init_surface), NULL);
  g_signal_connect(area, "button-press-event", G_CALLBACK(clicked), NULL);

  gtk_widget_set_events(area, gtk_widget_get_events(area) | GDK_BUTTON_PRESS_MASK | GDK_POINTER_MOTION_MASK);

  hbtnbox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_button_box_set_layout(GTK_BUTTON_BOX(hbtnbox), GTK_BUTTONBOX_CENTER);
  gtk_box_set_spacing(GTK_BOX(hbtnbox), 20);
  gtk_widget_set_margin_bottom(GTK_WIDGET(hbtnbox), 10); 
  gtk_widget_set_margin_top(GTK_WIDGET(hbtnbox), 10);

  btn_reset = gtk_button_new_with_label("Reset");
  btn_create = gtk_button_new_with_label("Create charge");
  btn_start = gtk_button_new_with_label("Start");

  g_signal_connect(btn_reset, "clicked", G_CALLBACK(clearSurface), area);
  g_signal_connect(btn_start, "clicked", G_CALLBACK(startProcess), main_charge_system);
  g_signal_connect(btn_create, "clicked", G_CALLBACK(displayWindowCreateCharge), initCreateChargeWindow(area, main_charge_system));

  gtk_widget_set_size_request(GTK_WIDGET(btn_reset), 100, 45);
  gtk_widget_set_size_request(GTK_WIDGET(btn_create), 100, 45);
  gtk_widget_set_size_request(GTK_WIDGET(btn_start), 100, 45);

  gtk_box_pack_start(GTK_BOX(hbtnbox), btn_reset, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(hbtnbox), btn_create, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(hbtnbox), btn_start, FALSE, FALSE, 0);

  grid = gtk_grid_new();

  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(area), 0, 0, 1, 1);

  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(hbtnbox), 0, 1, 1, 1);

  gtk_container_add(GTK_CONTAINER(window), grid);

  gtk_widget_show_all(window);
}

gboolean createChargeWindowClosed(GtkWidget *widget) {
    gtk_widget_hide(widget);
    return TRUE;
}


void checkInsertNumber(GtkWidget *widget, gchar *new_text) {
  regex_t regex;
  int reti;

  reti = regcomp(&regex, "[0-9,Ee+-]", 0);
  reti = regexec(&regex, new_text, 0, NULL, 0);

  if (reti == REG_NOMATCH) {
    g_signal_stop_emission_by_name(widget, "insert-text");
  }

  regfree(&regex);
}

GtkWidget* initCreateChargeWindow(GtkWidget* area, charge_system* main_charge_system) {
  GtkWidget *window_create_charge = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  GtkWidget *grid;
  GtkWidget *btn_create;
  GtkWidget *label_x;
  GtkWidget *spin_x;
  GtkWidget *label_y;
  GtkWidget *spin_y;
  GtkWidget *label_force;
  GtkWidget *entry_force;
  GtkWidget *label_weight;
  GtkWidget *entry_weight;
  GtkWidget *label_switch;
  GtkWidget *btn_switch;

  gtk_window_set_default_size(GTK_WINDOW(window_create_charge), WINDOW_CREATE_CHARGE_WIDTH, WINDOW_CREATE_CHARGE_HEIGHT);
  gtk_container_set_border_width(GTK_CONTAINER(window_create_charge), 10);
  gtk_window_set_resizable (GTK_WINDOW(window_create_charge), FALSE);
  gtk_window_set_position(GTK_WINDOW(window_create_charge), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW (window_create_charge), "Create charge");

  g_signal_connect(GTK_WINDOW(window_create_charge), "delete-event", G_CALLBACK(createChargeWindowClosed), NULL);

  label_x = gtk_label_new("Coordinate x");
  spin_x = gtk_spin_button_new_with_range(-50, 50, 0.01);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_x), 0);

  label_y = gtk_label_new("Coordinate y");
  spin_y = gtk_spin_button_new_with_range(-30, 30, 0.01);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_y), 0);

  label_force = gtk_label_new("Force");
  entry_force = gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(entry_force), "0");
  g_signal_connect(entry_force, "insert-text", G_CALLBACK(checkInsertNumber), NULL);

  label_weight = gtk_label_new("Weight");
  entry_weight = gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(entry_weight), "0");
  g_signal_connect(entry_weight, "insert-text", G_CALLBACK(checkInsertNumber), NULL);

  label_switch = gtk_label_new("Fixed charge ?");
  btn_switch = gtk_switch_new();

  btn_create = gtk_button_new_with_label("Create charge");

  grid = gtk_grid_new();
  gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(label_x), 0, 0, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(spin_x), 0, 1, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(label_y), 0, 2, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(spin_y), 0, 3, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(label_force), 0, 4, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(entry_force), 0, 5, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(label_weight), 0, 6, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(entry_weight), 0, 7, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(label_switch), 0, 8, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(btn_switch), 0, 9, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(btn_create), 0, 10, 2, 1);

  g_object_set_data(G_OBJECT(btn_create), "grid", grid);
  g_object_set_data(G_OBJECT(btn_create), "area", area);
  g_object_set_data(G_OBJECT(btn_create), "window", window_create_charge);
  g_object_set_data(G_OBJECT(btn_create), "charge_system", main_charge_system);
  g_signal_connect(btn_create, "clicked", G_CALLBACK(createCharge), NULL);

  gtk_container_add(GTK_CONTAINER(window_create_charge), grid);

  return window_create_charge;
}

