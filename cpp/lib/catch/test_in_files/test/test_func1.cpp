#include "../../catch.hpp"

#include "../func1.h"

TEST_CASE( "func1 are computed", "[func1]" ) {
    REQUIRE( func1(1, 1) == 2 );
    REQUIRE( func1(2, 3) == 5 );
}
