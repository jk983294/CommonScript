#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../catch.hpp"
#include "my_utils.h"
#include "IntRangeMacher.h"
#include <vector>
#include <string>

using namespace Catch::Matchers;

// test name and one or more tags
TEST_CASE( "Factorials are computed", "[factorial]" ) {
    // The REQUIRE family of macros tests an expression and aborts the test case if it fails
    // The CHECK family are equivalent but execution continues in the same test case even if the assertion fails
    CHECK( Factorial(0) == 1 );
    CHECK( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}

TEST_CASE( "Boolean are got", "[boolean]" ) {
    REQUIRE_FALSE( getValue(false) );
    CHECK_FALSE( getValue(false) );
}

TEST_CASE( "Floating point comparisons", "[floating]" ) {
    REQUIRE( getValue( 2.10001) == Approx( 2.1 ) );

    SECTION( "epsilon test" ) {
        Approx target = Approx(100).epsilon(0.01);
        REQUIRE( 100.0 == target );         // Obviously true
        REQUIRE_FALSE( 200.0 == target );   // Obviously still false
        REQUIRE( 100.5 == target );         // True, because we set target to allow up to 1% error
    }

    SECTION( "margin test" ) {
        Approx target = Approx(100).margin(5);
        REQUIRE( 100.0 == target );         // Obviously true
        REQUIRE_FALSE( 200.0 == target );   // Obviously still false
        REQUIRE( 104.0 == target );         // True, because we set target to allow absolute error up to 5
    }
}

TEST_CASE( "Throwable test", "[throw]" ) {
    REQUIRE_NOTHROW( throwIfValueTrue(false) );
    CHECK_NOTHROW( throwIfValueTrue(false) );

    REQUIRE_THROWS( throwIfValueTrue(true) );
    CHECK_THROWS( throwIfValueTrue(true) );

    REQUIRE_THROWS_AS( throwIfValueTrue(true), int );
    CHECK_THROWS_AS( throwIfValueTrue(true), int );

    REQUIRE_THROWS_WITH( throwIfValueTrue(true), Contains( "exception" ) );
    CHECK_THROWS_WITH( throwIfValueTrue(true), Contains( "exception" ) );
}

TEST_CASE( "Matcher test", "[matcher]" ) {
    std::string str{ "test it" };
    REQUIRE_THAT( str, EndsWith( "it" ) );
    REQUIRE_THAT( str, EndsWith( "IT", Catch::CaseSensitive::No ) );
    REQUIRE_THAT( str, EndsWith( "tests" ) || ( StartsWith( "test" ) && !Contains( "non sense" ) ) );

    CHECK_THAT( 3, IsBetween( 1, 10 ) );        // user defined matcher
}

TEST_CASE( "Log demo", "[log]" ) {
    std::string str{ "test it" };
    INFO( "The str is " << str );
    WARN( "The str is " << str );               // always reported but does not fail the test.
    // FAIL( "The str is " << str );            // reported and the test case fails.

    CAPTURE( str );
    CAPTURE( getValue(42) );
}


/**
 * setup/teardown approach
 * the SECTION macro contains an if statement that calls back into Catch to see if the section should be executed.
 * One leaf section is executed on each run through a TEST_CASE. The other sections are skipped.
 * Next time through the next section is executed, and so on until no new sections are encountered.
 */
TEST_CASE( "vectors", "[vector]" ) {

    std::vector<int> v( 5 );

    REQUIRE( v.size() == 5 );
    REQUIRE( v.capacity() >= 5 );

    SECTION( "resizing bigger changes size and capacity" ) {
        v.resize( 10 );

        REQUIRE( v.size() == 10 );
        REQUIRE( v.capacity() >= 10 );
    }
    SECTION( "resizing smaller changes size but not capacity" ) {
        v.resize( 0 );

        REQUIRE( v.size() == 0 );
        REQUIRE( v.capacity() >= 5 );
    }
    SECTION( "a" ) {
        v.reserve( 10 );

        REQUIRE( v.size() == 5 );
        REQUIRE( v.capacity() >= 10 );
    }
    SECTION( "b" ) {
        v.reserve( 0 );

        REQUIRE( v.size() == 5 );
        REQUIRE( v.capacity() >= 5 );
    }
}
