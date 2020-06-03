#ifndef CONFIG
#define CONFIG

#include "gtk/gtk.h"
#include <regex.h> 
#include "./draw.h"
#include "./button.h"
#include "../../logic/includes/charge_system.h"

/*
    Window's size constant
*/
#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 480
#define WINDOW_CREATE_CHARGE_WIDTH  200
#define WINDOW_CREATE_CHARGE_HEIGHT 300

void activate (GtkApplication *app, gpointer user_data);
gboolean createChargeWindowClosed(GtkWidget *widget, GdkEvent *event, gpointer data);
void checkInsertNumber(GtkWidget *widget, gchar *new_text, gint new_text_length, gpointer position, gpointer user_data);
GtkWidget* initCreateChargeWindow();

#endif
