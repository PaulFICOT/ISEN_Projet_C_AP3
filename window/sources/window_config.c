#include "../includes/window_config.h"

static GtkWidget *statusbar = NULL;
static GtkWidget *btn_simulation = NULL;

gboolean close_main_window(GtkWidget *window) {
    /* If the simulation is activated then we disable the simulation before to close the window */
    if (get_state_simulation()) {
      set_state_simulation(FALSE);
    }
    gtk_widget_destroy(window);
    return TRUE;
}

void activate(GtkApplication *app) {
  GtkWidget *window;
  GtkWidget *area;
  GtkWidget *grid;
  GtkWidget *hbtnbox;
  GtkWidget *btn_reset;
  GtkWidget *btn_generate;
  GtkWidget *btn_create;
  GtkWidget *box_statusbar;

  /* Initialize the charge system */
  charge_system* main_charge_system = charge_system_create();

  /* Initialize and configure each widget */
  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW (window), "Electrostatic Interaction Simulator");
  gtk_widget_set_size_request(window, WINDOW_WIDTH, WINDOW_HEIGHT);
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
  g_signal_connect(GTK_WINDOW(window), "delete-event", G_CALLBACK(close_main_window), NULL);

  area = gtk_drawing_area_new();
  gtk_widget_set_size_request(area, WINDOW_WIDTH, WINDOW_HEIGHT);
  g_signal_connect(area, "draw", G_CALLBACK(prepare_surface), NULL);
  g_signal_connect(area, "configure-event", G_CALLBACK(init_surface), NULL);
  g_signal_connect(area, "button-press-event", G_CALLBACK(clicked), main_charge_system);
  gtk_widget_set_events(area, gtk_widget_get_events(area) | GDK_BUTTON_PRESS_MASK | GDK_POINTER_MOTION_MASK);

  hbtnbox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_button_box_set_layout(GTK_BUTTON_BOX(hbtnbox), GTK_BUTTONBOX_CENTER);
  gtk_box_set_spacing(GTK_BOX(hbtnbox), 20);
  gtk_widget_set_margin_bottom(GTK_WIDGET(hbtnbox), 10);
  gtk_widget_set_margin_top(GTK_WIDGET(hbtnbox), 10);

  btn_reset = gtk_button_new_with_label("Reset");
  g_object_set_data(G_OBJECT(btn_reset), "charge_system", main_charge_system);
  g_object_set_data(G_OBJECT(btn_reset), "area", area);
  g_signal_connect(btn_reset, "clicked", G_CALLBACK(clear_surface_button), NULL);
  gtk_widget_set_size_request(GTK_WIDGET(btn_reset), 100, 45);

  btn_generate = gtk_button_new_with_label("Generate charge(s)");
  g_signal_connect(btn_generate, "clicked", G_CALLBACK(display_window_button), init_generate_window(area, main_charge_system));
  gtk_widget_set_size_request(GTK_WIDGET(btn_generate), 100, 45);

  btn_create = gtk_button_new_with_label("Create charge");
  g_signal_connect(btn_create, "clicked", G_CALLBACK(display_window_button), init_charge_window(area, main_charge_system, NULL));
  gtk_widget_set_size_request(GTK_WIDGET(btn_create), 100, 45);

  btn_simulation = gtk_button_new_with_label("Start");
  g_object_set_data(G_OBJECT(btn_simulation), "charge_system", main_charge_system);
  g_object_set_data(G_OBJECT(btn_simulation), "area", area);
  g_signal_connect(btn_simulation, "clicked", G_CALLBACK(display_window_button), init_start_window(area, main_charge_system));
  gtk_widget_set_size_request(GTK_WIDGET(btn_simulation), 100, 45);

  gtk_box_pack_start(GTK_BOX(hbtnbox), btn_reset, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(hbtnbox), btn_generate, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(hbtnbox), btn_create, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(hbtnbox), btn_simulation, FALSE, FALSE, 0);

  statusbar = gtk_statusbar_new();
  box_statusbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start(GTK_BOX(box_statusbar), statusbar, TRUE, FALSE, 0);

  grid = gtk_grid_new();
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(area), 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(hbtnbox), 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(box_statusbar), 0, 2, 1, 1);

  gtk_container_add(GTK_CONTAINER(window), grid);

  gtk_widget_show_all(window);
}

gboolean hide_window(GtkWidget *widget) {
    gtk_widget_hide(widget);
    return TRUE;
}

void check_insert_widget(GtkWidget *widget, gchar *new_text) {
  regex_t regex;
  int reti;

  reti = regcomp(&regex, "[0-9,Ee+-]", 0);
  reti = regexec(&regex, new_text, 0, NULL, 0);

  if (reti == REG_NOMATCH) {
    g_signal_stop_emission_by_name(widget, "insert-text");
  }

  regfree(&regex);
}

GtkWidget* init_charge_window(GtkWidget* area, charge_system* main_charge_system, charge* a_charge) {
  GtkWidget *window_charge;
  GtkWidget *grid;
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
  GtkWidget *btn_charge;

  /* Initialize and set up each widget */
  window_charge = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window_charge), WINDOW_CHARGE_WIDTH, WINDOW_CHARGE_HEIGHT);
  gtk_container_set_border_width(GTK_CONTAINER(window_charge), 10);
  gtk_window_set_resizable (GTK_WINDOW(window_charge), FALSE);
  gtk_window_set_position(GTK_WINDOW(window_charge), GTK_WIN_POS_CENTER);
  g_signal_connect(GTK_WINDOW(window_charge), "delete-event", G_CALLBACK(hide_window), NULL);

  label_x = gtk_label_new("Coordinate x (m)");
  spin_x = gtk_spin_button_new_with_range(-20, 20, 0.01);

  label_y = gtk_label_new("Coordinate y (m)");
  spin_y = gtk_spin_button_new_with_range(-12, 12, 0.01);

  label_force = gtk_label_new("Charge (C)");
  entry_force = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(entry_force), 50);
  g_signal_connect(entry_force, "insert-text", G_CALLBACK(check_insert_widget), NULL);

  label_weight = gtk_label_new("Weight (kg)");
  entry_weight = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(entry_weight), 50);
  g_signal_connect(entry_weight, "insert-text", G_CALLBACK(check_insert_widget), NULL);

  label_switch = gtk_label_new("Fixed charge ?");
  btn_switch = gtk_switch_new();

  if (a_charge) {
    double charge_force = 0.0;
    char charge_weight[50];
    char charge_force_string[50];

    /* Put the sign on the number */
    if(a_charge->symbol == NEGATIVE) {
      charge_force = -a_charge->force;
    }else charge_force = a_charge->force;

    /* Convert double to char* */
    g_ascii_formatd(charge_weight, 50, "%g", a_charge->weight);
    g_ascii_formatd(charge_force_string, 50, "%g", charge_force);

    gtk_window_set_title(GTK_WINDOW (window_charge), "Modify charge");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_x), m_to_nm(a_charge->position->x));
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_y), m_to_nm(a_charge->position->y));
    gtk_entry_set_text(GTK_ENTRY(entry_force), charge_force_string);
    gtk_entry_set_text(GTK_ENTRY(entry_weight), charge_weight);
    gtk_switch_set_active(GTK_SWITCH(btn_switch), a_charge->is_fixed);
    btn_charge = gtk_button_new_with_label("Modify charge");
  }else {
    gtk_window_set_title(GTK_WINDOW (window_charge), "Create charge");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_x), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_y), 0);
    gtk_entry_set_text(GTK_ENTRY(entry_force), "0,0");
    gtk_entry_set_text(GTK_ENTRY(entry_weight), "0,0");
    btn_charge = gtk_button_new_with_label("Create charge");
  }

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
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(btn_charge), 0, 10, 2, 1);

  if (a_charge) {
    /* Create delete button */
    GtkWidget *btn_delete = gtk_button_new_with_label("Delete charge");
    g_object_set_data(G_OBJECT(btn_delete), "area", area);
    g_object_set_data(G_OBJECT(btn_delete), "charge_system", main_charge_system);
    g_object_set_data(G_OBJECT(btn_delete), "window", window_charge);
    g_object_set_data(G_OBJECT(btn_delete), "a_charge", a_charge);
    g_signal_connect(btn_delete, "clicked", G_CALLBACK(delete_charge_button), NULL);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(btn_delete), 0, 11, 2, 1);

    g_object_set_data(G_OBJECT(btn_charge), "grid", grid);
    g_object_set_data(G_OBJECT(btn_charge), "area", area);
    g_object_set_data(G_OBJECT(btn_charge), "window", window_charge);
    g_object_set_data(G_OBJECT(btn_charge), "charge_system", main_charge_system);
    g_object_set_data(G_OBJECT(btn_charge), "a_charge", a_charge);
    g_signal_connect(btn_charge, "clicked", G_CALLBACK(modify_charge_button), NULL);
  } else {
    g_object_set_data(G_OBJECT(btn_charge), "grid", grid);
    g_object_set_data(G_OBJECT(btn_charge), "area", area);
    g_object_set_data(G_OBJECT(btn_charge), "window", window_charge);
    g_object_set_data(G_OBJECT(btn_charge), "charge_system", main_charge_system);
    g_signal_connect(btn_charge, "clicked", G_CALLBACK(create_charge_button), NULL);
  }

  gtk_container_add(GTK_CONTAINER(window_charge), grid);

  return window_charge;
}

GtkWidget* init_generate_window(GtkWidget* area, charge_system* main_charge_system) {
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *label;
  GtkWidget *label_mobile;
  GtkWidget *spin_mobile;
  GtkWidget *label_fixed;
  GtkWidget *spin_fixed;
  GtkWidget *btn;

  /* Initialize and set up each widget */
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  gtk_window_set_resizable (GTK_WINDOW(window), FALSE);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW (window), "Generate charge(s)");
  g_signal_connect(GTK_WINDOW(window), "delete-event", G_CALLBACK(hide_window), NULL);

  label = gtk_label_new("How many charges should we generate ?");

  label_mobile = gtk_label_new("Mobile charge");
  spin_mobile = gtk_spin_button_new_with_range(0, MAX_ENTRIES, 1);

  label_fixed = gtk_label_new("Fixed charge");
  spin_fixed = gtk_spin_button_new_with_range(0, MAX_ENTRIES, 1);

  btn = gtk_button_new_with_label("Generate");

  grid = gtk_grid_new();
  gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(label), 0, 0, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(label_mobile), 0, 1, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(spin_mobile), 0, 2, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(label_fixed), 0, 3, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(spin_fixed), 0, 4, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(btn), 0, 5, 2, 1);

  g_object_set_data(G_OBJECT(btn), "grid", grid);
  g_object_set_data(G_OBJECT(btn), "area", area);
  g_object_set_data(G_OBJECT(btn), "window", window);
  g_object_set_data(G_OBJECT(btn), "charge_system", main_charge_system);
  g_signal_connect(btn, "clicked", G_CALLBACK(generate_charge_button), NULL);

  gtk_container_add(GTK_CONTAINER(window), grid);

  return window;
}

GtkWidget* init_start_window(GtkWidget* area, charge_system* main_charge_system) {
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *label;
  GtkWidget *spin;
  GtkWidget *label_collision;
  GtkWidget *btn_switch_collision;
  GtkWidget *btn;

  /* Initialize and set up each widget */
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  gtk_window_set_resizable (GTK_WINDOW(window), FALSE);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW (window), "Start simulation");
  g_signal_connect(GTK_WINDOW(window), "delete-event", G_CALLBACK(hide_window), NULL);

  label = gtk_label_new("Choose the simulation time (milliseconds)");
  spin = gtk_spin_button_new_with_range(1, SIMULATION_TIME, 1);

  label_collision = gtk_label_new("Actived collision ?");
  btn_switch_collision = gtk_switch_new();

  btn = gtk_button_new_with_label("Start");

  grid = gtk_grid_new();
  gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(label), 0, 0, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(spin), 0, 1, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(label_collision), 0, 2, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(btn_switch_collision), 0, 3, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(btn), 0, 4, 2, 1);

  g_object_set_data(G_OBJECT(btn), "grid", grid);
  g_object_set_data(G_OBJECT(btn), "area", area);
  g_object_set_data(G_OBJECT(btn), "window", window);
  g_object_set_data(G_OBJECT(btn), "charge_system", main_charge_system);
  g_signal_connect(btn, "clicked", G_CALLBACK(start_process_button), NULL);

  gtk_container_add(GTK_CONTAINER(window), grid);

  return window;
}

void set_log(char *message) {
  gtk_statusbar_push(GTK_STATUSBAR(statusbar), 0, message);
}

void set_label_btn_simulation(char *label) {
  gtk_button_set_label(GTK_BUTTON(btn_simulation), label);
}
