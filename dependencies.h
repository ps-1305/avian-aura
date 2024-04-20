#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include <stdbool.h>

// *functions
#include "authenticateUser.c"
#include "main.c"
#include "signup.c"

#define NEW_GTK_TOPLEVEL "new"
#define DESTROY_OLD_TOPLEVEL "destroy"

#ifndef DEPENDENCIES_H

bool login(const char* username,const char* password);
void signup_init(int argc, char* argv[]);
void main_fn_init(int argc, char* argv[]);
static void destroy_window(GtkWidget *window, gpointer data);
void airways_callback(GtkWidget *widget, GdkEvent *event);
void railways_callback(GtkWidget *widget, GdkEvent *event);
void bus_callback(GtkWidget *widget, GdkEvent *event);
void wayfarer_callback(GtkWidget *widget, GdkEvent *event);

#endif