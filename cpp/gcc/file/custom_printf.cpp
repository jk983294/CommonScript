#include <stdio.h>
#include <stdlib.h>
#include <printf.h>

struct Widget {
    int data{0};
};

int print_widget (FILE *stream, const struct printf_info *info, const void *const *args) {
    char *buffer;
    const Widget* w = *((const Widget **) (args[0]));
    int len = asprintf (&buffer, "<Widget %p: %d>", w, w->data);    // format the output into a string
    if (len == -1)
        return -1;

    // pad to the minimum field width and print to the stream
    len = fprintf (stream, "%*s", (info->left ? -info->width : info->width), buffer);
    free (buffer);  // clean up and return
    return len;
}
int print_widget_arginfo (const struct printf_info *info, size_t n, int *argtypes) {
    // always take exactly one argument and this is a pointer to the structure..
    if (n > 0)
        argtypes[0] = PA_POINTER;
    return 1;
}

int main () {
    Widget widget;
    widget.data = 42;
    // register the print function for widgets.
    register_printf_function ('W', print_widget, print_widget_arginfo);
    printf ("|%W|\n", &widget);
    printf ("|%35W|\n", &widget);
    printf ("|%-35W|\n", &widget);
return 0;
}