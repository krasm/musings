#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <number.hpp>

TEST_CASE("addition") {
    number_t<10> l("2345", 4);
    number_t<10> r("678", 3);

    REQUIRE(l+r == number_t<10>("3023", 4));
}

TEST_CASE("addition with carry") {
    number_t<10> l("9999", 4);
    number_t<10> r("99", 2);

    REQUIRE(l+r == number_t<10>("10098", 5));
    REQUIRE(r+l == number_t<10>("10098", 5));

}

TEST_CASE("addition an example") {
    number_t<10> l("0", 1);
    number_t<10> r("016", 3);

    REQUIRE(l+r == number_t<10>("016", 3));

}

TEST_CASE("complement1") {
    number_t<10> n("678", 3);
    REQUIRE(n.complement() == number_t<10>("321", 3));
}

TEST_CASE("complement2") {
    number_t<10> n("678", 3);
    REQUIRE(n.complement(5) == number_t<10>("99321", 5));
}

TEST_CASE("complement0") {
    number_t<10> n("0", 1);
    REQUIRE(n.complement() == number_t<10>("9", 1));
    REQUIRE(n.complement(3) == number_t<10>("999", 3));
}


TEST_CASE("simple subsctraction") {
    number_t<10> l("2345", 4);
    number_t<10> r("678", 3);

    REQUIRE(l-r == number_t<10>("1667", 4));
}

TEST_CASE("simple subsctraction 1") {
    number_t<10> l("2345", 4);
    number_t<10> r("678", 3);
    number_t<10> actual = r-l;

    REQUIRE(actual == number_t<10>("1667", 4));
    REQUIRE(actual.is_negative());
}

TEST_CASE("substraction from zero") {
    number_t<10> l("0", 1);
    number_t<10> r("678", 3);
    number_t<10> actual = l - r;
    REQUIRE(actual == number_t<10>("678", 3));
    REQUIRE(actual.is_negative());
}

TEST_CASE("substraction from zero 1") {
    number_t<10> l("0", 1);
    number_t<10> r("8", 1);
    number_t<10> actual = l - r;
    REQUIRE(actual == number_t<10>("8", 1));
    REQUIRE(actual.is_negative());
}

TEST_CASE("substracting zero") {
    number_t<10> l("0", 1);
    number_t<10> r("678", 3);
    number_t<10> actual = r - l;
    REQUIRE(actual == number_t<10>("678", 3));
    REQUIRE(not actual.is_negative());
}

TEST_CASE("multiplication 1", "[mult]") {
    number_t<10> l("5", 1);
    number_t<10> r("6", 1);

    REQUIRE(l*r == number_t<10>("30", 2));
}

TEST_CASE("multiplication 2", "[mult]") {
    number_t<10> l("5", 1);
    number_t<10> r("6", 1);

    REQUIRE(r*l == number_t<10>("30", 2));
}

TEST_CASE("multiplication 3", "[mult]") {
    number_t<10> l("5", 1);
    number_t<10> r("6", 1);
    number_t<10> zero("0", 1);
    number_t<10> actual = (zero - l) * (zero - r);
    REQUIRE(actual == number_t<10>("30", 2));
    REQUIRE(not actual.is_negative());
    actual = (zero - r) * (zero - l);
    REQUIRE(actual == number_t<10>("30", 2));
    REQUIRE(not actual.is_negative());
}

TEST_CASE("multiplication 4", "[mult]") {
    number_t<10> l("5", 1);
    number_t<10> r("6", 1);
    number_t<10> zero("0", 1);
    number_t<10> actual = (zero - l) * r;
    REQUIRE(actual == number_t<10>("30", 2));
    REQUIRE(actual.is_negative());
    actual = (zero - r) * l;
    REQUIRE(actual == number_t<10>("30", 2));
    REQUIRE(actual.is_negative());
}

TEST_CASE("bigger multiplication", "[mult]") {
    REQUIRE(number_t<10>("408", 9) == number_t<10>("12", 2) * number_t<10>("34", 2));
}
