#include <gtk/gtk.h>


static void
app_activate(GtkApplication *app,
             gpointer data)
{
    GtkWidget *window;


    window =
        gtk_application_window_new(app);


    gtk_window_set_title(
        GTK_WINDOW(window),
        "uGet GTK4"
    );


    gtk_window_set_default_size(
        GTK_WINDOW(window),
        800,
        600
    );


    gtk_window_present(
        GTK_WINDOW(window)
    );
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