#pragma once

#include <gtk/gtk.h>


char *text_view_get_text(GtkTextView *text_view, gboolean hidden)
{
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(text_view);
    GtkTextIter start, end;
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    return gtk_text_buffer_get_text(buffer, &start, &end, hidden);
}

void text_view_set_text(GtkTextView *text_view, char *text)
{
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(text_view);
    gtk_text_buffer_set_text(buffer, text, -1);
}

void text_view_clear(GtkTextView *text_view)
{
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(text_view);
    GtkTextIter start, end;
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    gtk_text_buffer_delete(buffer, &start, &end);
}

const char *entry_get_text(GtkEntry *entry)
{
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(entry);
    return gtk_entry_buffer_get_text(buffer);
}

void text_view_set_margin(GtkTextView *text_view, int margin)
{
    gtk_text_view_set_bottom_margin(GTK_TEXT_VIEW(text_view), margin);
    gtk_text_view_set_top_margin(GTK_TEXT_VIEW(text_view), margin);
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(text_view), margin);
    gtk_text_view_set_right_margin(GTK_TEXT_VIEW(text_view), margin);
}

