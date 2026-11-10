#ifndef UGKTAPP_H
#define UGKTAPP_H

#include <gtk/gtk.h>

#define UGTK_APP_DIR         "uGet"
#define UGTK_APP_NAME        "uGet"
#define UGTK_APP_ICON_NAME   "uget-icon"

#define	UGTK_APP_ACCEL_PATH_NEW         "<uGet>/File/New"
#define	UGTK_APP_ACCEL_PATH_LOAD        "<uGet>/File/Load"
#define	UGTK_APP_ACCEL_PATH_SAVE        "<uGet>/File/Save"
#define	UGTK_APP_ACCEL_PATH_SAVE_ALL    "<uGet>/File/SaveAll"
#define	UGTK_APP_ACCEL_PATH_DELETE      "<uGet>/Download/Delete"
#define	UGTK_APP_ACCEL_PATH_DELETE_F    "<uGet>/Download/DeleteFile"
#define	UGTK_APP_ACCEL_PATH_OPEN        "<uGet>/Download/Open"
#define	UGTK_APP_ACCEL_PATH_OPEN_F      "<uGet>/Download/OpenFolder"
#define	UGTK_APP_ACCEL_PATH_SWITCH      "<uGet>/Download/SwitchState"

typedef struct UgtkApp        UgtkApp;

struct UgtkApp
{

};

#endif