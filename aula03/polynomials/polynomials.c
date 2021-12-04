#include <assert.h>
#include <math.h>
#include <stdio.h>

void displayPol(double* coef, unsigned int degree) {
    printf("Pol(x) = ");
    for(size_t i = 0; i < degree; i++) {
        printf("%f * x^%d + ", coef[i], degree - 1);
    }
    printf("%f\n", coef[degree]);
}

double computePol(double* coef, unsigned int degree, double x) {
    double result = coef[0];

    for(size_t i = 1; i <= degree; i++) {
        result = result * x + coef[i];
    }

    return result;
}

unsigned int getRealRoots(double* coef, unsigned int degree, double* root1, double* root2) {
    assert(degree == 2);
    assert(coef[0] != 0.0);
    double delta = coef[1]*coef[1] - 4.0*coef[0]*coef[2];
    
    if(delta < 0) { 
        *root1 = *root2 = 0.0;
        return 0; 
    }
    
    if(delta == 0) {
        *root1 = *root2 = -coef[1]/2.0*coef[0];
        return 1;
    }

    double aux = sqrt(delta);
    *root1 = (-coef[1] + aux) / (2.0*coef[0]);
    *root2 = (-coef[1] - aux) / (2.0*coef[0]);
    return 2;
}

int main(void) {
    
    return 0;
}