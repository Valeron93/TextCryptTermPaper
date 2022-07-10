#pragma once

#include "entry.h"
#include "crypt.h"

struct SignalData
{
    GtkWindow *window;
    GtkTextView *input;
    GtkTextView *output;
    GtkEntry *password;
};

void i_entry_show_password(GtkCheckButton *checkbox, GtkEntry *entry)
{
    gtk_entry_set_visibility(entry, gtk_check_button_get_active(checkbox));
}

void i_create_info_dialog(GtkWindow *parent, const char *msg)
{
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT | GTK_DIALOG_MODAL;
    GtkWidget *d = gtk_message_dialog_new(parent, flags, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "\n%s\n", msg);
    g_signal_connect_swapped(d, "response", G_CALLBACK(gtk_window_destroy), d);
    gtk_widget_set_size_request(d, 300, 200);
    gtk_widget_show(d);
}

void i_create_error_dialog(GtkWindow *parent, const char *msg)
{
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT | GTK_DIALOG_MODAL;
    GtkWidget *d = gtk_message_dialog_new(parent, flags, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "\n%s\n", msg);
    g_signal_connect_swapped(d, "response", G_CALLBACK(gtk_window_destroy), d);
    gtk_widget_set_size_request(d, 350, 150);
    gtk_widget_show(d);
}

void i_swap_entries(struct SignalData *sig)
{
    char *output_text = text_view_get_text(sig->output, false);
    text_view_set_text(sig->input, output_text);
    text_view_clear(sig->output);
    g_free(output_text);
}

void i_show_about_menu(GtkWindow *parent)
{
    const static char *about_text = "\nПро програму:";

    i_create_info_dialog(parent, about_text);
}

void i_encrypt_xor(struct SignalData *sig)
{
    text_view_clear(sig->output);
    const char *passwd = entry_get_text(sig->password);
    if (passwd == NULL || strlen(passwd) < 8) {
        i_create_error_dialog(sig->window, "Пароль має бути від 8 символів!");
        return;
    }
    char *input_text = text_view_get_text(sig->input, false);
    if (input_text == NULL || strlen(input_text) == 0) {
        i_create_error_dialog(sig->window, "Введений текст не може бути пустим");
        return;
    }

    char *encrypted = encrypt_xor(input_text, (char *) passwd);
    if (encrypted != NULL) {
        text_view_set_text(sig->output, encrypted);
        free(encrypted);
    }
    else {
        i_create_error_dialog(sig->window, "Виникла невідома помилка при шифруванні");
    }

    g_free(input_text);
}

void i_decrypt_xor(struct SignalData *sig)
{
    const char *passwd = entry_get_text(sig->password);
    if (passwd == NULL || strlen(passwd) < 8) {
        i_create_error_dialog(sig->window, "Пароль має бути від 8 символів!");
        return;
    }
    char *input_text = text_view_get_text(sig->input, false);
    if (input_text == NULL || strlen(input_text) == 0) {
        i_create_error_dialog(sig->window, "Введений текст не може бути пустим");
        return;
    }

    text_view_clear(sig->output);

    char *decrypted = decrypt_xor(input_text, (char *) passwd);
    if (decrypted != NULL) {

        if (g_utf8_validate(decrypted, -1, NULL)) {
            text_view_set_text(sig->output, decrypted);
        }
        else {
            i_create_error_dialog(sig->window, "Не вдалося розшифрувати текст");
        }

        free(decrypted);
    }
    else {
        i_create_error_dialog(sig->window, "Введені дані не є зашифрованим текстом");
    }

    g_free(input_text);
}
