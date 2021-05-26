#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <string.h>
#include <number.hpp>

TEST_CASE("copy operator") {
    number_t<10> l = number_t<10>("135792468", 9);
    number_t<10> r = l;
    REQUIRE(l == r);
}

TEST_CASE("copy operator 1") {
    number_t<10> l = number_t<10>("57", 2);
    number_t<10> r = l;
    REQUIRE(number_t<10>("57", 2) == r);
}


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

TEST_CASE("addition negative numbers 1") {
    number_t<10> l = number_t<10>("0", 1) - number_t<10>("13", 2);
    number_t<10> r = number_t<10>("0", 1) - number_t<10>("57", 2);
    number_t<10> result = l + r;

    REQUIRE(l.is_negative());
    REQUIRE(r.is_negative());
    REQUIRE(result.is_negative());
    REQUIRE(number_t<10>("70", 2) == result);
}

TEST_CASE("addition negative numbers 2") {
    number_t<10> l = number_t<10>("13", 2);
    number_t<10> r = number_t<10>("0", 1) - number_t<10>("57", 2);
    number_t<10> result = l + r;

    REQUIRE(r.is_negative());
    REQUIRE(number_t<10>("57", 2) == r);
    REQUIRE(number_t<10>("44", 2) == result);
    REQUIRE(result.is_negative());
}

TEST_CASE("addition negative numbers 3") {
    number_t<10> l = number_t<10>("0", 1) - number_t<10>("13", 2);
    number_t<10> r = number_t<10>("57", 2);
    number_t<10> result = l + r;

    REQUIRE(number_t<10>("44", 2) == result);
    REQUIRE(not result.is_negative());
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

TEST_CASE("simple subsctraction 2") {
    number_t<10> l("13", 2);
    number_t<10> r("57", 2);
    number_t<10> actual = l - r;

    REQUIRE(actual == number_t<10>("44", 2));
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

TEST_CASE("multiplication steps", "[mult]") {
    number_t<10> h1{"12", 2};
    number_t<10> l1{"34", 2};
    number_t<10> h2{"56", 2};
    number_t<10> l2{"78", 2};

    REQUIRE(number_t<10>{"2652", 4} == number_t<10>{"34", 2} * number_t<10>{"78", 2});

    REQUIRE(number_t<10>{"6164", 4} == (l1 + h1) * (l2 + h2));
}

TEST_CASE("bigger multiplication", "[mult]") {
    REQUIRE(number_t<10>("408", 3) == number_t<10>("12", 2) * number_t<10>("34", 2));
}

TEST_CASE("bigger multiplication 1a", "[mult]") {
    REQUIRE(number_t<10>("838102050", 9) == number_t<10>("12345", 5) * number_t<10>("67890", 5));
}

TEST_CASE("non symetric numbers", "[mult]") {
    REQUIRE(number_t<10>("56088", 5) == number_t<10>("123", 3) * number_t<10>("456", 3));
}

TEST_CASE("non symetric numbers 1", "[mult]") {
    REQUIRE(number_t<10>("7006652", 7) == number_t<10>("1234", 4) * number_t<10>("5678", 4));
}

TEST_CASE("multiplication and addition", "[mult]") {
    number_t<10> l{"19", 2};
    number_t<10> r{"231", 3};
    number_t<10> res = (l + r) * (l - r);

    REQUIRE((l-r).is_negative());
    REQUIRE(not (l+r).is_negative());
    REQUIRE(number_t<10>("53000", 5) == res);
    REQUIRE(res.is_negative());
}

TEST_CASE("big numbers 1", "[mult]") {
    number_t<10> l{"1357924681", 10}; // 18F0IA9
    number_t<10> r{"3579135792463", 13}; // 385AHS5AF
    number_t<10> res = (l + r) * (l - r);

    REQUIRE((l-r).is_negative());
    REQUIRE(not (l+r).is_negative());
    REQUIRE(number_t<10>("12810211176930307738654608", 26) == res); // AJ2LF0V4QEPC6ULSG
    REQUIRE(res.is_negative());
}

TEST_CASE("big numbers 1 (32base)", "[mult]") {
    number_t<32> l{"18F0IA9", 7}; // 18F0IA9
    number_t<32> r{"385AHS5AF", 9}; // 385AHS5AF
    number_t<32> res = (l + r) * (l - r);

    REQUIRE((l-r).is_negative());
    REQUIRE(not (l+r).is_negative());
    REQUIRE(number_t<32>("AJ2LF0V4QEPC6ULSG", 17) == res); // AJ2LF0V4QEPC6ULSG
    REQUIRE(res.is_negative());
}
