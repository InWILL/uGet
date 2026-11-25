#include "DownloadItem.h"

struct _DownloadItem {
    GObject parent_instance;
    UgetNode *node; /* Borrowed; the node owner must outlive this item. */
    char *name;
    guint64 complete;
    guint64 size;
    int percent;
    gint64 elapsed;
    gint64 added_on;
};

G_DEFINE_TYPE(DownloadItem, download_item, G_TYPE_OBJECT)

enum {
    PROP_0,
    PROP_NAME,
    PROP_COMPLETE,
    PROP_SIZE,
    PROP_PERCENT,
    PROP_ELAPSED,
    PROP_ADDED_ON,
    N_PROPERTIES
};

static GParamSpec *properties[N_PROPERTIES];

static void download_item_get_property(GObject *object,
                                       guint property_id,
                                       GValue *value,
                                       GParamSpec *pspec)
{
    DownloadItem *self = DOWNLOAD_ITEM(object);

    switch (property_id) {
    case PROP_NAME:
        g_value_set_string(value, self->name);
        break;
    case PROP_COMPLETE:
        g_value_set_uint64(value, self->complete);
        break;
    case PROP_SIZE:
        g_value_set_uint64(value, self->size);
        break;
    case PROP_PERCENT:
        g_value_set_int(value, self->percent);
        break;
    case PROP_ELAPSED:
        g_value_set_int64(value, self->elapsed);
        break;
    case PROP_ADDED_ON:
        g_value_set_int64(value, self->added_on);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
    }
}

static void download_item_set_property(GObject *object,
                                       guint property_id,
                                       const GValue *value,
                                       GParamSpec *pspec)
{
    DownloadItem *self = DOWNLOAD_ITEM(object);

    switch (property_id) {
    case PROP_NAME:
        g_free(self->name);
        self->name = g_value_dup_string(value);
        break;
    case PROP_COMPLETE:
        self->complete = g_value_get_uint64(value);
        break;
    case PROP_SIZE:
        self->size = g_value_get_uint64(value);
        break;
    case PROP_PERCENT:
        self->percent = g_value_get_int(value);
        break;
    case PROP_ELAPSED:
        self->elapsed = g_value_get_int64(value);
        break;
    case PROP_ADDED_ON:
        self->added_on = g_value_get_int64(value);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
    }
}

static void download_item_finalize(GObject *object)
{
    DownloadItem *self = DOWNLOAD_ITEM(object);
    g_clear_pointer(&self->name, g_free);
    G_OBJECT_CLASS(download_item_parent_class)->finalize(object);
}

static void download_item_class_init(DownloadItemClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS(klass);

    object_class->get_property = download_item_get_property;
    object_class->set_property = download_item_set_property;
    object_class->finalize = download_item_finalize;

    properties[PROP_NAME] =
        g_param_spec_string("name", "Name", "Download name", NULL,
                            G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);
    properties[PROP_COMPLETE] =
        g_param_spec_uint64("complete", "Complete", "Downloaded bytes",
                            0, G_MAXUINT64, 0,
                            G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);
    properties[PROP_SIZE] =
        g_param_spec_uint64("size", "Size", "Total download size in bytes",
                            0, G_MAXUINT64, 0,
                            G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);
    properties[PROP_PERCENT] =
        g_param_spec_int("percent", "Percent", "Download completion percentage",
                         0, 100, 0,
                         G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);
    properties[PROP_ELAPSED] =
        g_param_spec_int64("elapsed", "Elapsed", "Elapsed download time in seconds",
                           0, G_MAXINT64, 0,
                           G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);
    properties[PROP_ADDED_ON] =
        g_param_spec_int64("added-on", "Added on",
                           "Unix timestamp when the download was added",
                           0, G_MAXINT64, 0,
                           G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);

    g_object_class_install_properties(object_class, N_PROPERTIES, properties);
}

static void download_item_init(DownloadItem *self)
{
}

DownloadItem *download_item_new(UgetNode *node)
{
    DownloadItem *self = g_object_new(DOWNLOAD_TYPE_ITEM, NULL);
    self->node = node;
    return self;
}

UgetNode *download_item_get_node(DownloadItem *self)
{
    g_return_val_if_fail(DOWNLOAD_IS_ITEM(self), NULL);
    return self->node;
}
