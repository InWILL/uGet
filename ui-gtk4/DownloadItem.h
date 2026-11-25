#ifndef DOWNLOAD_ITEM_H
#define DOWNLOAD_ITEM_H

#include <glib-object.h>

typedef struct UgetNode UgetNode;

G_BEGIN_DECLS

#define DOWNLOAD_TYPE_ITEM (download_item_get_type())
G_DECLARE_FINAL_TYPE(DownloadItem, download_item, DOWNLOAD, ITEM, GObject)

DownloadItem *download_item_new(UgetNode *node);
UgetNode *download_item_get_node(DownloadItem *self);

G_END_DECLS

#endif
