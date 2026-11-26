#include "UgtkApp.h"
#include "DownloadItem.h"

G_MODULE_EXPORT void on_name_setup(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer user_data) {
    GtkWidget *label = gtk_label_new(NULL);
    gtk_label_set_xalign(GTK_LABEL(label), 0.0);
    gtk_list_item_set_child(list_item, label);
}

G_MODULE_EXPORT void on_value_setup(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer user_data) {
    GtkWidget *label = gtk_label_new(NULL);
    gtk_label_set_xalign(GTK_LABEL(label), 1.0);
    gtk_list_item_set_child(list_item, label);
}

G_MODULE_EXPORT void on_name_bind(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer user_data) {
    GtkWidget *label = gtk_list_item_get_child(list_item);
    DownloadItem *item = gtk_list_item_get_item(list_item);
    char *name = NULL;
    g_object_get(item, "name", &name, NULL);
    gtk_label_set_text(GTK_LABEL(label), name != NULL ? name : "");
    g_free(name);
}

G_MODULE_EXPORT void on_complete_bind(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer user_data) {
    GtkWidget *label = gtk_list_item_get_child(list_item);
    DownloadItem *item = gtk_list_item_get_item(list_item);
    guint64 complete;
    g_object_get(item, "complete", &complete, NULL);
    char *text = g_format_size_full(complete, G_FORMAT_SIZE_IEC_UNITS);
    gtk_label_set_text(GTK_LABEL(label), text);
    g_free(text);
}

G_MODULE_EXPORT void on_size_bind(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer user_data) {
    GtkWidget *label = gtk_list_item_get_child(list_item);
    DownloadItem *item = gtk_list_item_get_item(list_item);
    guint64 size;
    g_object_get(item, "size", &size, NULL);
    char *text = g_format_size_full(size, G_FORMAT_SIZE_IEC_UNITS);
    gtk_label_set_text(GTK_LABEL(label), text);
    g_free(text);
}

G_MODULE_EXPORT void on_percent_setup(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer user_data) {
    GtkWidget *progressbar = gtk_progress_bar_new();
    gtk_list_item_set_child(list_item, progressbar);
}

G_MODULE_EXPORT void on_percent_bind(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer user_data) {
    GtkWidget *progressbar = gtk_list_item_get_child(list_item);
    DownloadItem *item = gtk_list_item_get_item(list_item);
    int percent;
    g_object_get(item, "percent", &percent, NULL);
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progressbar), percent / 100.0);
    gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(progressbar), TRUE);
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progressbar), g_strdup_printf("%d%%", percent));
}

G_MODULE_EXPORT void on_elapsed_bind(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer user_data) {
    GtkWidget *label = gtk_list_item_get_child(list_item);
    DownloadItem *item = gtk_list_item_get_item(list_item);
    gint64 elapsed;
    g_object_get(item, "elapsed", &elapsed, NULL);

    gint64 hours = elapsed / 3600;
    gint64 minutes = (elapsed % 3600) / 60;
    gint64 seconds = elapsed % 60;
    char *text = hours > 0
        ? g_strdup_printf("%" G_GINT64_FORMAT ":%02" G_GINT64_FORMAT ":%02" G_GINT64_FORMAT,
                          hours, minutes, seconds)
        : g_strdup_printf("%" G_GINT64_FORMAT ":%02" G_GINT64_FORMAT,
                          minutes, seconds);
    gtk_label_set_text(GTK_LABEL(label), text);
    g_free(text);
}

G_MODULE_EXPORT void on_added_on_bind(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer user_data) {
    GtkWidget *label = gtk_list_item_get_child(list_item);
    DownloadItem *item = gtk_list_item_get_item(list_item);
    gint64 added_on;
    g_object_get(item, "added-on", &added_on, NULL);

    GDateTime *date_time = added_on > 0 ? g_date_time_new_from_unix_local(added_on) : NULL;
    char *text = date_time != NULL ? g_date_time_format(date_time, "%Y-%m-%d %H:%M") : g_strdup("");
    gtk_label_set_text(GTK_LABEL(label), text);
    g_free(text);
    g_clear_pointer(&date_time, g_date_time_unref);
}

static DownloadItem *create_demo_download(const char *name,
                                          guint64 complete,
                                          guint64 size,
                                          int percent,
                                          gint64 elapsed,
                                          gint64 added_seconds_ago)
{
    gint64 added_on = g_get_real_time() / G_USEC_PER_SEC - added_seconds_ago;

    return g_object_new(DOWNLOAD_TYPE_ITEM,
                        "name", name,
                        "complete", complete,
                        "size", size,
                        "percent", percent,
                        "elapsed", elapsed,
                        "added-on", added_on,
                        NULL);
}

static void app_activate(GtkApplication *app, gpointer user_data) {
    download_item_get_type();

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

    GListStore *store = G_LIST_STORE(gtk_builder_get_object(builder, "uget_task"));
    DownloadItem *item1 = create_demo_download(
        "debian-13.2.0-amd64-netinst.iso",
        576 * 1024 * 1024,
        768 * 1024 * 1024,
        75,
        342,
        3600);
    DownloadItem *item2 = create_demo_download(
        "uget-2.2.3.tar.gz",
        1024 * 1024,
        4 * 1024 * 1024,
        25,
        58,
        120);
    g_list_store_append(store, item1);
    g_list_store_append(store, item2);
    g_object_unref(item1);
    g_object_unref(item2);

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