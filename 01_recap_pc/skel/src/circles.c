/* IORDACHE MADALINA GABRIELA 313CA */
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/* define structure to hold coordinates of the center of circle and radius */

typedef struct circle {
    int x, y, r;
} Circle;

int main(void)
{
    int N, i = 0, j = 0, counter = 0;
    struct circle* circles;
    /* read number of circles */
    scanf("%d", &N);
    circles = (struct circle*)malloc(N * sizeof(struct circle));

    /* read coordinates and radius for N circles */
    for(i = 0; i < N; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        circles[i].x = a;
        circles[i].y = b;
        circles[i].r = c;
    }
    /* compare every circle to the rest of circles */
    for(i = 0; i < N-1; i++) {
        struct circle circle1 = circles[i];
        for (j = i + 1; j < N; j++) {
            struct circle circle2 = circles[j];
            int distance = (circle1.x - circle2.x) * (circle1.x - circle2.x) +
                           (circle1.y - circle2.y) * (circle1.y - circle2.y);
            int radius = (circle1.r + circle2.r) * (circle1.r + circle2.r);
            if( distance == radius || distance < radius) {
                /* count number of intersectons of N given circles */
                counter++;
            }
        }
    }
    printf("%d\n", counter);

    /* deallocate memory */
    free(circles);

    return 0;
}
