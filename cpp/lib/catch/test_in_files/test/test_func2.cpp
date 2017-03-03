#include "../../catch.hpp"

#include "../func2.h"

TEST_CASE( "func2 are computed", "[func2]" ) {
    REQUIRE( func2(1, 1) == 1 );
    REQUIRE( func2(2, 3) == 6 );
}
