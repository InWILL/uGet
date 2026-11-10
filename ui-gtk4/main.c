#include "UgtkApp.h"


static void app_activate(GtkApplication *app, gpointer user_data) {
    GtkBuilder *builder = gtk_builder_new();
    GError *error = NULL;

     /* Load menu XML. */
    if (!gtk_builder_add_from_resource(
            builder,
            "/com/uget/gtk4/menu.ui",
            &error)) {
        g_error("Menu loading failed: %s", error->message);
    }

    /* Load window XML into the SAME builder. */
    if (!gtk_builder_add_from_resource(
            builder,
            "/com/uget/gtk4/builder.ui",
            &error)) {
        g_error("Window loading failed: %s", error->message);
    }

    GtkWindow *window = GTK_WINDOW(
        gtk_builder_get_object(builder, "window"));

    /* Set application ownership. */
    gtk_window_set_application(window, app);

    gtk_window_present(GTK_WINDOW(window));

    g_object_set_data_full(
        G_OBJECT(window),
        "ui-builder",
        builder,
        g_object_unref);
}



int main(int argc,char **argv)
{
    GtkApplication *app;
    int ret;
    
    app = 
        gtk_application_new(
            "com.uget.gtk4",
            G_APPLICATION_DEFAULT_FLAGS
        );


    g_signal_connect(
        app,
        "activate",
        G_CALLBACK(app_activate),
        NULL
    );

    ret =
        g_application_run(
            G_APPLICATION(app),
            argc,
            argv
        );


    g_object_unref(app);


    return ret;
}