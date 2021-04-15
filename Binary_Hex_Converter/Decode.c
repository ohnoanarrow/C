#include <stdio.h>
#include <math.h>

int main() {

    unsigned input;

    printf("\n\nPlease enter a float value: ");
    scanf("%f", &input);

    // Bit masking to get the values
    unsigned sign = input & 0x80000000;
    unsigned exponent = input & 0x7f800000;
    unsigned significand = input & 0x007fffff;

    printf("\nYour value in hex: 0x%4x", input);

    printf("\nYour value in binary: ");


    printf("%u", sign >>31);
    printf(" ");

    // For loops to print sign, significand and exponent in binary
    int i;
    for (i = 30; i>= 23; i--){
        int mask = exponent & 1<<i;

    // Forces it to print in binary
    if (mask != 0){
            printf("1");
        } else{
             printf("0");
        }

    }

    printf(" ");

    for (i = 22; i>=0; i--){
        int mask = significand & 1<<i;

        if (mask != 0){
            printf("1");
        } else{
             printf("0");
        }
    }


    if (sign == 0){
        printf("\nSign: +");
    } else {
        printf("\nSign: -");
    }

    // Calculating exponent
    exponent >>= 23;
    exponent -= 127;
    printf("\nExponent: 2^%d", exponent);

    // Calculating significand
    float signif = significand/pow(2,23);
    signif += 1;
    printf("\nSignificand: %f", signif);


    printf("\n\n");


        return 0;
}
