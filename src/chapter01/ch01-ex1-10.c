#include <stdio.h>

const float foot_in_meters = 0.3048;
const float meters_in_feet = 1 / foot_in_meters;
const float miles_in_feet = 5280.0;
const float miles_in_kilometers = 1.609344;
const float square_miles_in_square_kilometers = 2.589988;

// alternatives:
//const float meters_in_kilometer = 1000;
//const float miles_in_kilometers = miles_in_feet * foot_in_meters * meters_in_kilometer;
//const float square_miles_in_square_kilometers = miles_in_kilometers * miles_in_kilometers;

int main()
{
    printf("%g\n", foot_in_meters);
    printf("%g\n", meters_in_feet);
    printf("%g\n", miles_in_feet);
    printf("%g\n", miles_in_kilometers);
    printf("%g\n", square_miles_in_square_kilometers);

    return 0;
}
