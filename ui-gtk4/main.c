#include "UgtkApp.h"

#define ROW_TYPE_ITEM (row_item_get_type())
G_DECLARE_FINAL_TYPE(RowItem, row_item, ROW, ITEM, GObject)

struct _RowItem {
    GObject parent_instance;
    char *name;
    char *role;
};

G_DEFINE_TYPE(RowItem, row_item, G_TYPE_OBJECT)

static void row_item_finalize(GObject *object) {
    RowItem *self = ROW_ITEM(object);
    g_free(self->name);
    g_free(self->role);
    G_OBJECT_CLASS(row_item_parent_class)->finalize(object);
}

static void row_item_class_init(RowItemClass *klass) {
    G_OBJECT_CLASS(klass)->finalize = row_item_finalize;
}

static void row_item_init(RowItem *self) {}

static RowItem *row_item_new(const char *name, const char *role) {
    RowItem *item = g_object_new(ROW_TYPE_ITEM, NULL);
    item->name = g_strdup(name);
    item->role = g_strdup(role);
    return item;
}

G_MODULE_EXPORT void on_name_setup(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer user_data) {
    GtkWidget *label = gtk_label_new(NULL);
    gtk_label_set_xalign(GTK_LABEL(label), 0.0);
    gtk_list_item_set_child(list_item, label);
}

G_MODULE_EXPORT void on_name_bind(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer user_data) {
    GtkWidget *label = gtk_list_item_get_child(list_item);
    RowItem *item = gtk_list_item_get_item(list_item);
    gtk_label_set_text(GTK_LABEL(label), item->name);
}

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

    GListStore *store = G_LIST_STORE(gtk_builder_get_object(builder, "my_store"));
    RowItem *item1 = row_item_new("Alice", "Admin");
    RowItem *item2 = row_item_new("Bob", "Editor");
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