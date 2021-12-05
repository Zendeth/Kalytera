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
    // Pointer to Settings box
    GtkWidget *w_dlg_settings;

    // Pointer to image selection button
    GtkButton *btn_image_selection;
    // Pointer to image name label
    GtkWidget *g_lbl_image_name;

    //Pointer to Convert button
    GtkButton *btn_convert;

    //Pointer to Show steps
    GtkButton *btn_show_steps;

    // Pointer to Settings button
    GtkButton *btn_settings;
    // Pointer to solve button
    GtkButton *btn_solve;

    // Pointers to Settings toggle buttons
    GtkCheckButton *btn_settings_otsu;
    GtkCheckButton *btn_settings_adaptive;
    GtkCheckButton *btn_settings_denoise;
    GtkCheckButton *btn_settings_rotation;

    // Pointer to Settings apply button
    GtkButton *btn_settings_apply;
} app_widgets;

app_widgets *widgets;
gchar *ImgPath = NULL;
gchar *gridpath = NULL;

char active_adaptive = 0, active_denoise = 0, active_rotation = 0;

void Convert()
{
    SDL_Surface *image = load_img(ImgPath);
    // Binarise
    image = Binarize(image, (int)active_adaptive);

    // Noise reduction
    if (active_denoise)
    {
        image = Reduct_noise(image);
    }

    //Deskew
    if (active_rotation)
    {
        image = AutoRotate(image);
    }
    

    // Sobel
    image = SobelMain(image);

    //Hough
    image = hough(image);

    IMG_SavePNG(image, "tmp/image.png");

    // next?

    SDL_FreeSurface(image);
    
}

// Convert button function
void on_btn_convert_clicked(app_widgets *app_wdgts)
{
    // Do the conversion
    Convert();
    g_print("Convert successful");
    // Activate the Show Steps button
    if(gtk_widget_get_sensitive(GTK_WIDGET(app_wdgts->btn_show_steps)))
    {
        gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->btn_show_steps), TRUE);
    }
}

// File --> Open
void on_menuitm_open_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    gchar *image_path = NULL;        // Name of file to open from dialog box

    // Show the "Open Image" dialog box
    gtk_widget_show(app_wdgts->w_dlg_file_choose);
    
    // Check return value from Open Image dialog box 
    // to see if user clicked the Open button
    if (gtk_dialog_run(
                GTK_DIALOG(app_wdgts->w_dlg_file_choose))== GTK_RESPONSE_OK)
    {
        // Get the file name from the dialog box
        image_path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(
                                            app_wdgts->w_dlg_file_choose));
        if (image_path != NULL)
        {
            gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main),
                                                                image_path);
        }

        gtk_label_set_text(GTK_LABEL(app_wdgts->g_lbl_image_name), image_path);
    }
    ImgPath = image_path;

    // Activate the Convert button
    gtk_widget_set_sensitive(app_wdgts->btn_convert, TRUE);

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
    if (!MakeGrid("output/output.result"))
    {
        gridpath = "output/output.png";
        gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_grid), gridpath);
    }
}

// Otsu and Adaptive toggle buttons function
void on_btn_settings_otsu_toggled(GtkDialog *dialog, app_widgets *app_wdgts)
{
    if (gtk_toggle_button_get_active(app_wdgts->btn_settings_otsu))
    {
        gtk_toggle_button_set_active(app_wdgts->btn_settings_adaptive, FALSE);
        active_adaptive = 0;
    }
    g_print("Adaptive (0) = %d \n", active_adaptive);
}
void on_btn_settings_adaptive_toggled(GtkDialog *dialog, app_widgets *app_wdgts)
{
    if (gtk_toggle_button_get_active(app_wdgts->btn_settings_adaptive))
    {
        gtk_toggle_button_set_active(app_wdgts->btn_settings_otsu, FALSE);
        active_adaptive = 1;
    }
    else
    {
        active_adaptive = 0;
    }
    
    g_print("Adaptive (1) = %d \n", active_adaptive);
}

// Denoise toggle button function
void on_btn_settings_denoise_toggled(GtkDialog *dialog, app_widgets *app_wdgts)
{
    if (gtk_toggle_button_get_active(app_wdgts->btn_settings_denoise))
    {
        active_denoise = 1;
    }
    else
    {
        gtk_toggle_button_set_active(app_wdgts->btn_settings_denoise, FALSE);
        active_denoise = 0;
    }
    g_print("active denoise = %d \n", active_denoise);
}

// Rotation toggle button fonction
void on_btn_settings_rotation_toggled(GtkDialog *dialog, app_widgets *app_wdgts)
{
    if (gtk_toggle_button_get_active(app_wdgts->btn_settings_rotation))
    {
        active_rotation = 1;
    }
    else
    {
        gtk_toggle_button_set_active(app_wdgts->btn_settings_rotation, FALSE);
        active_rotation = 0;
    }
    g_print("active rotation = %d \n", active_rotation);
}

// Settings apply button
void on_btn_settings_apply_clicked(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    gtk_widget_hide(app_wdgts->w_dlg_settings);
}

// Settings button
void on_btn_settings_clicked(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    if (app_wdgts->w_dlg_settings)
    {
        // Hide the Settings dialog box
        gtk_widget_hide(app_wdgts->w_dlg_settings);
    }
    // Show the "Settings" dialog box
    gtk_widget_show(app_wdgts->w_dlg_settings);
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
    widgets->w_grid = GTK_WIDGET(gtk_builder_get_object(builder, "grid"));
    widgets->w_dlg_settings = GTK_WIDGET(gtk_builder_get_object(builder,
                                                            "dlg_settings"));
    widgets->w_dlg_about = GTK_WIDGET(gtk_builder_get_object(builder, 
                                                            "dlg_about"));
    widgets->w_dlg_file_choose = GTK_WIDGET(gtk_builder_get_object(builder,
                                                    "dlg_file_choose"));

    widgets->btn_image_selection = GTK_BUTTON(gtk_builder_get_object(builder, 
                                                    "btn_image_selection"));
    widgets->g_lbl_image_name = GTK_WIDGET(gtk_builder_get_object(builder,
                                                        "lbl_image_name"));

    widgets->btn_convert = GTK_BUTTON(gtk_builder_get_object(builder, 
                                                    "btn_convert"));

    widgets->btn_settings = GTK_BUTTON(gtk_builder_get_object(builder,
                                                        "btn_settings"));
    widgets->btn_show_steps = GTK_BUTTON(gtk_builder_get_object(builder, 
                                                        "btn_show_steps"));

    widgets->btn_solve = GTK_BUTTON(gtk_builder_get_object(builder, 
                                                    "btn_solve"));
    widgets->btn_settings_apply = GTK_BUTTON(gtk_builder_get_object(builder, 
                                                    "btn_settings_apply"));
    widgets->btn_settings_otsu = GTK_TOGGLE_BUTTON(
            gtk_builder_get_object(builder, "btn_settings_otsu"));
    widgets->btn_settings_adaptive = GTK_TOGGLE_BUTTON(
            gtk_builder_get_object(builder, "btn_settings_adaptive"));
    widgets->btn_settings_denoise = GTK_TOGGLE_BUTTON(
            gtk_builder_get_object(builder, "btn_settings_denoise"));
    widgets->btn_settings_rotation = GTK_TOGGLE_BUTTON(
            gtk_builder_get_object(builder, "btn_settings_rotation"));
    
    // Init toggle buttons
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widgets->btn_settings_otsu), TRUE);
    
    if (ImgPath == NULL)
    {
        gtk_widget_set_sensitive(GTK_WIDGET(widgets->btn_convert), FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(widgets->btn_show_steps), FALSE);
    }
    

    // Connect signal handlers
    g_signal_connect(window, "destroy",
                            G_CALLBACK(on_window_main_destroy), NULL);
    gtk_builder_connect_signals(builder, widgets);

    g_object_unref(builder);

    // Run the main loop
    gtk_main();

    // Free widgets pointers
    g_slice_free(app_widgets, widgets);

    // Exit after all done
    return EXIT_SUCCESS;
}