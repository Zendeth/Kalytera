/*
// Graphical interface
// Author: Hafid HOUSNI
*/

#include "gui.h"

GtkBuilder *builder;
GtkWindow *window;
GError *error;

// Place all widgets on this structure
typedef struct {
    // Pointer to file chooser dialog box
    GtkWidget *w_dlg_file_choose;
    // Pointer to image widget
    GtkWidget *w_img_main;
    // Pointer to grid widget
    GtkWidget *w_grid;
    // Pointer to about dialog box
    GtkWidget *w_dlg_about;

    // Pointer to image selection button
    GtkButton *btn_image_selection;
    // Pointer to image name label
    GtkWidget *g_lbl_image_name;

    // Pointer to solve button
    GtkButton *btn_solve;
} app_widgets;

app_widgets *widgets;
gchar *ImgPath;
gchar *gridpath;

// File --> Open
void on_menuitm_open_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    gchar *image_path = NULL;        // Name of file to open from dialog box

    // Show the "Open Image" dialog box
    gtk_widget_show(app_wdgts->w_dlg_file_choose);
    
    // Check return value from Open Image dialog box 
    // to see if user clicked the Open button
    if (gtk_dialog_run(
                GTK_DIALOG(app_wdgts->w_dlg_file_choose))== GTK_RESPONSE_OK){
        // Get the file name from the dialog box
        image_path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(
                                            app_wdgts->w_dlg_file_choose));
        if (image_path != NULL) {
            gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main),
                                                                image_path);
        }

        gtk_label_set_text(GTK_LABEL(app_wdgts->g_lbl_image_name), image_path);
    }
    ImgPath = image_path;

    // Finished with the "Open Image" dialog box, so hide it
    gtk_widget_hide(app_wdgts->w_dlg_file_choose);
}

// File --> Quit
void on_menuitm_close_activate()
{
    gtk_main_quit();
}

// Solve button
void on_btn_solve_clicked(app_widgets *app_wdgts)
{
    MakeGrid("output/output");
    gridpath = "output/output.png";
    gtk_image_set_from_file(GTK_IMAGE(widgets->w_grid), gridpath);
}

// Image selection button
void on_btn_image_selection_clicked(GtkMenuItem *menuitem, 
                                                    app_widgets *app_wdgts)
{
    on_menuitm_open_activate(menuitem, app_wdgts);
}

// Help --> About
void on_menuitm_about_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    gtk_widget_show(app_wdgts->w_dlg_about);
}

// About dialog box Close button
void on_dlg_about_response(GtkDialog *dialog, gint response_id, 
                                                    app_widgets *app_wdgts)
{
    gtk_widget_hide(app_wdgts->w_dlg_about);
}

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}

// Main launcher function
int launch_gui()
{
    // Init GTK
    gtk_init(NULL, NULL);

    // Load the UI (Exit if an en error occurs)
    builder = gtk_builder_new();
    error = NULL;
    widgets = g_slice_new(app_widgets);

    if(gtk_builder_add_from_file(builder, "assets/config.glade", &error) == 0)
    {
        g_printerr("Error loading config.glade file: %s\n", error->message);
        g_clear_error(&error);
        return EXIT_FAILURE;
    }

    // Gets the widgets
    window = GTK_WINDOW(gtk_builder_get_object(builder, "window_main"));
    widgets->w_img_main = GTK_WIDGET(gtk_builder_get_object(builder,
                                                            "img_main"));
    widgets->w_grid = GTK_WIDGET(gtk_builder_get_object(builder,
                                                        "grid"));
    widgets->w_dlg_about = GTK_WIDGET(gtk_builder_get_object(builder, 
                                                            "dlg_about"));
    widgets->w_dlg_file_choose = GTK_WIDGET(gtk_builder_get_object(builder,
                                                    "dlg_file_choose"));
    widgets->btn_image_selection = GTK_BUTTON(gtk_builder_get_object(builder, 
                                                    "btn_image_selection"));
    widgets->g_lbl_image_name = GTK_WIDGET(gtk_builder_get_object(builder,
                                                        "lbl_image_name"));
    widgets->btn_solve = GTK_BUTTON(gtk_builder_get_object(builder, 
                                                    "btn_solve"));
    // Connect signal handlers
    g_signal_connect(window, "destroy",
                            G_CALLBACK(on_window_main_destroy), NULL);
    gtk_builder_connect_signals(builder, widgets);

    // Init toggle buttons

    g_object_unref(builder);

    // Run the main loop
    gtk_main();

    // Free widgets pointers
    g_slice_free(app_widgets, widgets);

    // Exit after all done
    return EXIT_SUCCESS;
}