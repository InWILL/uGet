#include <gtk/gtk.h>
#include <UgtkApp.h>

UgtkApp*  ugtk_app;

static void ugtk_statusbar_init_ui(struct UgtkStatusbar* sbar)
{
    GtkWidget *widget;
    GtkBox *hbox;

    /*
     * GTK4: replace GtkStatusbar with GtkBox
     */
    hbox =
        GTK_BOX(
            gtk_box_new(
                GTK_ORIENTATION_HORIZONTAL,
                0
            )
        );

    sbar->self = GTK_WIDGET(hbox);

    /*
     * upload speed label
     */
    widget = gtk_label_new("");

    sbar->up_speed =
        GTK_LABEL(widget);


    gtk_widget_set_size_request(
        widget,
        100,
        -1
    );

    gtk_widget_set_halign(
        widget,
        GTK_ALIGN_START
    );

    gtk_box_append(
        hbox,
        widget
    );

    gtk_box_append(
        hbox,
        gtk_label_new("↑")
    );

    gtk_box_append(
        hbox,
        gtk_separator_new(
            GTK_ORIENTATION_VERTICAL
        )
    );

    /*
     * download speed label
     */
    widget = gtk_label_new("");

    sbar->down_speed =
        GTK_LABEL(widget);


    gtk_widget_set_size_request(
        widget,
        100,
        -1
    );


    gtk_widget_set_halign(
        widget,
        GTK_ALIGN_START
    );


    gtk_box_append(
        hbox,
        widget
    );


    gtk_box_append(
        hbox,
        gtk_label_new("↓")
    );
}

void  ugtk_app_init_ui (UgtkApp* app)
{
	// Main Window and it's widgets
    ugtk_banner_init (&app->banner);
	ugtk_statusbar_init_ui (&app->statusbar);
}

static void ugtk_window_init_ui (struct UgtkWindow* window, UgtkApp* app, GtkApplication* gtk_app)
{
    GtkBox*  vbox;
    GtkBox*  lbox;    // left side vbox
    GtkBox*  rbox;    // right side vbox

    window->self = (GtkWindow*) gtk_application_window_new(gtk_app);
    gtk_window_set_title (window->self, UGTK_APP_NAME);
    gtk_window_set_default_size (window->self, 800, 600);

    // 主垂直容器
    vbox = (GtkBox*) gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
    gtk_window_set_child (window->self, GTK_WIDGET (vbox));
    
    // 【修改点1】：为了能看到效果，我们添加两个测试标签代替 banner 和 menubar
    gtk_box_append(vbox, app->banner.self);
    //gtk_box_append (vbox, gtk_label_new("====== 这里是 Banner 占位 ======"));
    gtk_box_append (vbox, gtk_label_new("====== 这里是 Menubar 占位 ======"));

    // hpaned (水平分割)
    window->hpaned = (GtkPaned*) gtk_paned_new (GTK_ORIENTATION_HORIZONTAL);
    gtk_box_append (vbox, GTK_WIDGET (window->hpaned));
    gtk_widget_set_vexpand (GTK_WIDGET (window->hpaned), TRUE);

    lbox = (GtkBox*) gtk_box_new (GTK_ORIENTATION_VERTICAL, 2);
    rbox = (GtkBox*) gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
    
    gtk_paned_set_start_child (window->hpaned, GTK_WIDGET (lbox));
    gtk_paned_set_resize_start_child (window->hpaned, FALSE);
    gtk_paned_set_shrink_start_child (window->hpaned, TRUE);

    gtk_paned_set_end_child (window->hpaned, GTK_WIDGET (rbox));
    gtk_paned_set_resize_end_child (window->hpaned, TRUE);
    gtk_paned_set_shrink_end_child (window->hpaned, FALSE);

    // 【修改点2】：给左侧 lbox 填入内容，设置足够的大小把分割线撑开
    GtkWidget *status_label = gtk_label_new ("状态 (Status)");
    gtk_widget_set_vexpand (status_label, TRUE); // 让它在垂直方向填满
    gtk_box_append (lbox, status_label);

    GtkWidget *category_label = gtk_label_new ("分类 (Category)");
    gtk_widget_set_vexpand (category_label, TRUE);
    gtk_box_append (lbox, category_label);

    // 给右侧的顶部加上 Toolbar 占位
    gtk_box_append (rbox, gtk_label_new("--- 这里是 Toolbar ---"));

    // vpaned (右侧垂直分割)
    window->vpaned = (GtkPaned*) gtk_paned_new (GTK_ORIENTATION_VERTICAL);
    gtk_box_append (rbox, GTK_WIDGET (window->vpaned));
    gtk_widget_set_vexpand (GTK_WIDGET (window->vpaned), TRUE); 

    // 【修改点3】：给 vpaned 的上下两部分加上内容
    GtkWidget *download_label = gtk_label_new("这里是下载列表 (Download List)");
    gtk_paned_set_start_child (window->vpaned, download_label);
    gtk_paned_set_resize_start_child (window->vpaned, TRUE);
    gtk_paned_set_shrink_start_child (window->vpaned, TRUE);

    GtkWidget *summary_label = gtk_label_new("这里是底部的摘要 (Summary)");
    gtk_paned_set_end_child (window->vpaned, summary_label);
    gtk_paned_set_resize_end_child (window->vpaned, FALSE);
    gtk_paned_set_shrink_end_child (window->vpaned, TRUE);

    gtk_box_append (vbox, app->statusbar.self);
    // 底部状态栏
    //gtk_box_append (vbox, gtk_label_new("--- 这里是底部 Statusbar ---"));
}

static void app_activate(GtkApplication *app, gpointer data)
{
    ugtk_app = g_malloc0 (sizeof (UgtkApp));
    ugtk_app_init_ui(ugtk_app);
    ugtk_window_init_ui(&ugtk_app->window, ugtk_app, app);

    gtk_window_present(
        GTK_WINDOW(ugtk_app->window.self)
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