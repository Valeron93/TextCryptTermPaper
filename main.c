#include "base64.h"
#include "interface.h"

static void on_activate(GtkApplication *app)
{

    struct SignalData *sig_data = malloc(sizeof(struct SignalData));

    // window
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Шифрування текстів");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_window_set_resizable(GTK_WINDOW(window), false);
    gtk_window_present(GTK_WINDOW(window));
    sig_data->window = GTK_WINDOW(window);
    ///////////////////////


    // fixed layout
    GtkWidget *fixed_layout = gtk_fixed_new();
    gtk_window_set_child(GTK_WINDOW(window), fixed_layout);
    ///////////////////////

    // about button
    GtkWidget *about_button = gtk_button_new_with_label("Про програму");
    gtk_widget_set_size_request(about_button, 200, 30);
    gtk_fixed_put(GTK_FIXED(fixed_layout), about_button, 455, 276);
    g_signal_connect_swapped(about_button, "clicked", G_CALLBACK(i_show_about_menu), window);
    /////////////////


    // encrypt button
    GtkWidget *encrypt_button = gtk_button_new_with_label("Зашифрувати");
    gtk_widget_set_size_request(encrypt_button, 200, 30);
    g_signal_connect_swapped(encrypt_button, "clicked", G_CALLBACK(i_encrypt_xor), sig_data);
    gtk_fixed_put(GTK_FIXED(fixed_layout), encrypt_button, 250, 276);
    ///////////////////////


    // decrypt button
    GtkWidget *decrypt_button = gtk_button_new_with_label("Розшифрувати");
    gtk_widget_set_size_request(decrypt_button, 200, 30);
    g_signal_connect_swapped(decrypt_button, "clicked", G_CALLBACK(i_decrypt_xor), sig_data);
    gtk_fixed_put(GTK_FIXED(fixed_layout), decrypt_button, 250, 320);
    ///////////////////////


    // swap button
    GtkWidget *swap_button = gtk_button_new_with_label("Вихідний → Вхідний");
    g_signal_connect_swapped(swap_button, "clicked", G_CALLBACK(i_swap_entries), sig_data);
    gtk_widget_set_size_request(swap_button, 200, 20);
    gtk_fixed_put(GTK_FIXED(fixed_layout), swap_button, 455, 320);
    ///////////////////////

    // input label
    GtkWidget *input_label = gtk_label_new("Вхідний текст");
    gtk_fixed_put(GTK_FIXED(fixed_layout), input_label, 15, 10);
    //////////////////

    // input text view
    GtkWidget *input = gtk_text_view_new();
    sig_data->input  = GTK_TEXT_VIEW(input);
    text_view_set_margin(GTK_TEXT_VIEW(input), 5);
    gtk_text_view_set_accepts_tab(GTK_TEXT_VIEW(input), false);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(input), GTK_WRAP_WORD_CHAR);
    GtkWidget *input_scrolled_window = gtk_scrolled_window_new();
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(input_scrolled_window), input);
    gtk_widget_set_size_request(input_scrolled_window, 800, 220);
    gtk_fixed_put(GTK_FIXED(fixed_layout), input_scrolled_window, 10, 30);
    ///////////////////////


    // output text view
    GtkWidget *output = gtk_text_view_new();
    sig_data->output = GTK_TEXT_VIEW(output);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(output), false);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(output), GTK_WRAP_WORD_CHAR);
    text_view_set_margin(GTK_TEXT_VIEW(output), 5);
    GtkWidget *outputWindow = gtk_scrolled_window_new();
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(outputWindow), output);
    gtk_widget_set_size_request(outputWindow, 800, 220);
    gtk_fixed_put(GTK_FIXED(fixed_layout), outputWindow, 10, 370);
    ///////////////////////

    // output label
    GtkWidget *output_label = gtk_label_new("Вихідний текст");
    gtk_fixed_put(GTK_FIXED(fixed_layout), output_label, 15, 350);
    //////////////////

    // password label
    GtkWidget *password_label = gtk_label_new("Пароль");
    gtk_fixed_put(GTK_FIXED(fixed_layout), password_label, 15, 260);
    //////////////////

    // password text view
    GtkWidget *password = gtk_entry_new();
    sig_data->password = GTK_ENTRY(password);
    gtk_widget_set_size_request(password, 200, 20);
    gtk_fixed_put(GTK_FIXED(fixed_layout), password, 10, 275);
    gtk_entry_set_visibility(GTK_ENTRY(password), false);
    ///////////////////////

    // show password checkbox
    GtkWidget *checkbox = gtk_check_button_new_with_label("показати пароль");
    gtk_check_button_set_active(GTK_CHECK_BUTTON(checkbox), false);
    g_signal_connect(checkbox, "toggled", G_CALLBACK(i_entry_show_password), GTK_ENTRY(password));
    gtk_fixed_put(GTK_FIXED(fixed_layout), checkbox, 10, 310);
    //////////////////////

}

int main(int argc, char **argv)
{
    GtkApplication *app = gtk_application_new("com.valeron.crypt", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    return g_application_run(G_APPLICATION(app), argc, argv);
}