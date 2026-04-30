#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void) {
    printf("Sizes (bytes):\n");
    printf("  char      : %zu\n", sizeof(char));
    printf("  short     : %zu\n", sizeof(short));
    printf("  int       : %zu\n", sizeof(int));
    printf("  long      : %zu\n", sizeof(long));
    printf("  float     : %zu\n", sizeof(float));
    printf("  double    : %zu\n\n", sizeof(double));

    printf("int range  : %d to %d\n", INT_MIN, INT_MAX);
    printf("float dig  : %d (decimal digits)\n", FLT_DIG);
    printf("float min>0: %e\n", FLT_MIN);
    printf("float max  : %e\n", FLT_MAX);
    printf("double dig : %d (decimal digits)\n", DBL_DIG);
    printf("double min>0: %e\n", DBL_MIN);
    printf("double max : %e\n", DBL_MAX);
    return 0;
}
