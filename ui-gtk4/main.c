#include <gtk/gtk.h>


static void app_activate(GtkApplication *app, gpointer user_data) {
    GtkBuilder *builder = gtk_builder_new_from_file("builder.ui");
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    GtkWidget *button = GTK_WIDGET(gtk_builder_get_object(builder, "hello_button"));
    
    gtk_window_set_application(GTK_WINDOW(window), app);
    // Add signal connection here if needed
    
    gtk_window_present(
        GTK_WINDOW(window)
    );
    g_object_unref(builder);
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