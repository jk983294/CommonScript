#include <iostream>
#include <malloc.h>

using namespace std;

/**
 * The address returned by malloc or realloc in GNU systems always aligned to 16 on 64-bit systems
 */

// prototype define for us
static void *my_malloc_hook(size_t, const void *);
static void my_free_hook(void *,const void *);

// some temp variable
static void *(*old_malloc_hook)(size_t, const void *);
static void (*old_free_hook)(void *, const void *);

// init function
static void my_init_hook(void){
    old_malloc_hook = __malloc_hook;
    old_free_hook = __free_hook;
    __malloc_hook = my_malloc_hook;
    __free_hook = my_free_hook;
}

// initialize hook
void (*__MALLOC_HOOK_VOLATILE __malloc_initialize_hook) (void) = my_init_hook;

static void *my_malloc_hook (size_t size, const void *caller)
{
    void *result;
    // Restore all old hooks
    __malloc_hook = old_malloc_hook;
    __free_hook = old_free_hook;
    // Call recursively
    result = malloc (size);
    // Save underlying hooks
    old_malloc_hook = __malloc_hook;
    old_free_hook = __free_hook;
    // printf might call malloc, so protect it too
    printf ("malloc (%u) returns %p\n", (unsigned int) size, result);
    // Restore our own hooks
    __malloc_hook = my_malloc_hook;
    __free_hook = my_free_hook;
    return result;
}

static void my_free_hook (void *ptr, const void *caller)
{
    // Restore all old hooks
    __malloc_hook = old_malloc_hook;
    __free_hook = old_free_hook;
    // Call recursively
    free (ptr);
    // Save underlying hooks
    old_malloc_hook = __malloc_hook;
    old_free_hook = __free_hook;
    // printf might call free, so protect it too
    printf ("freed pointer %p\n", ptr);
    // Restore our own hooks
    __malloc_hook = my_malloc_hook;
    __free_hook = my_free_hook;
}

int main()
{
    void* p1 = malloc(16);
    free(p1);

    int* p2 = new int(42);
    delete p2;
    return 0;
}
