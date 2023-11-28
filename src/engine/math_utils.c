#include "utils.h"

// Rotates a vector v by angle a
v2 rotatev2(v2 v, f32 a) {
    return (v2) {
        (v.x * cos(a)) - (v.y * sin(a)),
        (v.x * sin(a)) + (v.y * cos(a)),
    };
}

/**
 * Calculates the intersection point of two line segments given their endpoints.
 *
 * @param a0 Endpoint of the first line segment (start).
 * @param a1 Endpoint of the first line segment (end).
 * @param b0 Endpoint of the second line segment (start).
 * @param b1 Endpoint of the second line segment (end).
 *
 * @return Intersection point of the line segments as a 2D vector (v2).
 *         If the segments do not intersect or are parallel, returns { NAN, NAN }.
 */
v2 intersect_segments(v2 a0, v2 a1, v2 b0, v2 b1) {
    // Calculate determinant to check if the segmeents are parallel
    const f32 d =
        ((a0.x - a1.x) * (b0.y - b1.y))
            - ((a0.y - a1.y) * (b0.x - b1.x));
    
    // If segments are parallel or almost parallel, return NaN (no intersection).
    if (fabsf(d) < 0.000001f)
        return (v2) {
            { NAN, NAN }
        };
    
    // Calculate parameters for line intersection.
    const f32
        t = (((a0.x - b0.x) * (b0.y - b1.y))
                - ((a0.y - b0.y) * (b0.x - b1.x))) / d,
        u = (((a0.x - b0.x) * (a0.y - a1.y))
                - ((a0.y - b0.y) * (a0.x - a1.x))) / d;

    // Check if intersection point lies within both line segments.
    return (t >= 0 && t <= 1 && u >= 0 && u <= 1) ?
        ((v2) {
            a0.x + (t * (a1.x - a0.x)),
            a0.y + (t * (a1.y - a0.y)) })
        : ((v2) { NAN, NAN }); // Return NaN if segments do not intersect.
}
