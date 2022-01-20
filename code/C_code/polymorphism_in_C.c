// How to implement polymorhphism in C:

// based on: https://stackoverflow.com/questions/8194250/polymorphism-in-c/8194428#8194428
// reason why we want polymorhphism is: https://youtu.be/7EmboKQH8lM?t=4584

/*
Almost all implementations of runtime polymorphism in C will use function pointers, so this is the basic building block.

Using function pointers you can create virtual tables and use it to create "objects" that will be treated uniformly, but behave differently at runtime.

C1x added generic selections, which make compile-time polymorphism via macros possible. The following example is taken from the C1x April draft, section 6.5.1.1 §5:

#define cbrt(X) _Generic((X), \
    long double: cbrtl, \
    default: cbrt, \
    float: cbrtf \
)(X)

*/

#include <stdio.h>

struct animal_vtable {
    const char* (*sound)();
};

struct animal {
    struct animal_vtable methods;
    const char* name;
};

const char* cat_sound() {
    return "meow!";
}

const char* dog_sound() {
    return "bark!";
}

void describe(struct animal *a) {
    printf("%s makes \"%s\" sound.\n", a->name, a->methods.sound());
}

struct animal cat = {{&cat_sound}, "cat"};
struct animal dog = {{&dog_sound}, "dog"};

int main() {
    describe(&cat);
    describe(&dog);

    return 0;
}
