#ifndef TESTVECTOR3_H
#define TESTVECTOR3_H

#include <iostream>
#include <limits>

using namespace std;

#define CATCH_CONFIG_MAIN
#include "../catch.h"
#include "../math/vector3.h"

TEST_CASE( "Test magnetometer sensitivity adjustment", "[Vector3]") {
    Vector3<short> v(1, 2, 3);
    v += 1;
    REQUIRE(v.getX() == 2);
    REQUIRE(v.getY() == 3);
    REQUIRE(v.getZ() == 4);

    v = v - 1;
    REQUIRE(v.getX() == 1);
    REQUIRE(v.getY() == 2);
    REQUIRE(v.getZ() == 3);

    Vector3<unsigned char> asa(1, 2, 3);
    Vector3<double> result = (((((Vector3<double>) asa) - 128) * 0.5f) /128) + 1;

    REQUIRE(fabs(result.getX() - 0.50390625d) < numeric_limits<double>::epsilon());
    REQUIRE(fabs(result.getY() - 0.5078125d) < numeric_limits<double>::epsilon());
    REQUIRE(fabs(result.getZ() - 0.51171875d) < numeric_limits<double>::epsilon());

    Vector3<short> measuredData = Vector3<short>(-3, 5, 12);
    result = result * measuredData;

    REQUIRE(fabs(result.getX() - (-1.51171875d)) < numeric_limits<double>::epsilon());
    REQUIRE(fabs(result.getY() - 2.5390625d) < numeric_limits<double>::epsilon());
    REQUIRE(fabs(result.getZ() - 6.140625d) < numeric_limits<double>::epsilon());
}

#endif // TESTVECTOR3_H

