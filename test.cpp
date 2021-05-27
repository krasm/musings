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


TEST_CASE("simple subsctraction", "[sub]") {
    number_t<10> l("2345", 4);
    number_t<10> r("678", 3);

    REQUIRE(l-r == number_t<10>("1667", 4));
}

TEST_CASE("simple subsctraction 1", "[sub]") {
    number_t<10> l("2345", 4);
    number_t<10> r("678", 3);
    number_t<10> actual = r-l;

    REQUIRE(actual == number_t<10>("1667", 4));
    REQUIRE(actual.is_negative());
}

TEST_CASE("simple subsctraction 2", "[sub]") {
    number_t<10> l("13", 2);
    number_t<10> r("57", 2);
    number_t<10> actual = l - r;

    REQUIRE(actual == number_t<10>("44", 2));
    REQUIRE(actual.is_negative());
}


TEST_CASE("substraction from zero", "[sub]") {
    number_t<10> l("0", 1);
    number_t<10> r("678", 3);
    number_t<10> actual = l - r;
    REQUIRE(actual == number_t<10>("678", 3));
    REQUIRE(actual.is_negative());
}

TEST_CASE("substraction from zero 1", "[sub]") {
    number_t<10> l("0", 1);
    number_t<10> r("8", 1);
    number_t<10> actual = l - r;
    REQUIRE(actual == number_t<10>("8", 1));
    REQUIRE(actual.is_negative());
}

TEST_CASE("substracting zero", "[sub]") {
    number_t<10> l("0", 1);
    number_t<10> r("678", 3);
    number_t<10> actual = r - l;
    REQUIRE(actual == number_t<10>("678", 3));
    REQUIRE(not actual.is_negative());
}

TEST_CASE("smaller - bigger", "[sub]") {
    number_t<10> l("20", 2);
    number_t<10> r("678", 3);
    number_t<10> actual = l - r;
    REQUIRE(actual == number_t<10>("658", 3));
    REQUIRE(actual.is_negative());
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
    number_t<10> l("-5", 2);
    number_t<10> r("-6", 2);
    number_t<10> actual = l * r;

    REQUIRE(actual == number_t<10>("30", 2));
    REQUIRE(not actual.is_negative());
}

TEST_CASE("multiplication 4", "[mult]") {
    number_t<10> l("-5", 2);
    number_t<10> r("6", 1);
    number_t<10> actual = l * r;
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

    std::cout << "HERE- " << (l - r) << std::endl;
    std::cout << "HERE+ " << (l + r) << std::endl;

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

TEST_CASE("big numbers 2 (32base)", "[mult]") {
    number_t<32> l{"14PC0MJ", 7}; // 1234567891
    number_t<32> r{"TDSQ5H", 6};  // 987654321
    number_t<32> res = l * r;     // 1219326312114007011 --> 11QVAQ89DFAV3

    REQUIRE(number_t<32>("11QVAQ89DFAV3", 13) == res);
    REQUIRE(not res.is_negative());
}

TEST_CASE("big numbers 2 (10base)", "[mult]") {
    number_t<10> l{"1234567891", 10};
    number_t<10> r{"987654321", 9};
    number_t<10> res = (l + r) * (l - r);

    REQUIRE(number_t<10>("0548696819698216840", 19) == res);
    REQUIRE(not res.is_negative());
}

TEST_CASE("mult_a", "[mult]") {
    number_t<10> l = number_t<10>{"123456789123456789123456789", 27};
    number_t<10> r = number_t<10>{"851", 3};
    number_t<10> res = l * r;

    REQUIRE(number_t<10>{"105061727544061727544061727439", 30} == res);
}

TEST_CASE("mult_b", "[mult]") {
    number_t<32> l = number_t<32>{"363RUV5OTHJTU08NOL", 18};  // 123456789123456789123456789
    number_t<32> r = number_t<32>{"QJ", 2};                   // 851
    number_t<32> res = l * r;

    REQUIRE(res == number_t<32>{"2KRP0ON6LPRL5518G4MF", 20}); //  105061727544061721869293715456
}

TEST_CASE("mult_c", "[mult]") {
    number_t<32> l{"4I7", 3};
    number_t<32> r{"93", 2};
    number_t<32> res = l * r;

    REQUIRE(res == number_t<32>{"19HLL", 5});
}

const char * l = "1265828374914119790432443892245057448670781343822578314415759138479792925121170886498844789659382033346086056733662147807962998398729004339782236795968138704985198637211742210131597281901737837500857402398952983171640143499750388529120062733164109205";

const char * r = "7358962464594238631920301985037411448944675896428422499770454955441471864955969199908607778539748771241223112222964042489519660108266830409793540041254201127727724812109964048481907106805212095348248297828065464619022448330620883612305083852382524015";

const char * expected = "9315183497611330883146766583804165932087484831792626108317011103375088254951213374405863278113105530481553699528875570843645745570938639788785975040219956587540836292710471590081885761045661035777138286960146359698138152794937162948804354382435627616719452135777975248653743553516421822072790702790880837453106793585313806904958156208312507080531653121505899645703622407320200143380842634765748867685513146077982120070558752613216065513118741815905516975577750891684634989047153858151866366995058075";
const char * expected_square = "-52552007080569189457509291237342673422559104112502912557859955352245263171564006401600852635051216891031309226716374949863992869369840031138232826586548299504790382313162750077206050003587021862430448857275091208156376794189202159960511740036419541870623981758368383059949625085647289518466260645039779098910935699127166689235669558356576852519294498439814176139687824696782971697639206955660754753765574617474294933822121884672208186209824467824325046689829866851315136195438991085751289820885988200";

TEST_CASE("mult_d", "[mult]") {
    number_t<10> ll{l, strlen(l)};
    number_t<10> rr{r, strlen(r)};
    number_t<10> res = ll * rr;
    REQUIRE(number_t<10>{expected, strlen(expected)} == res);

    res = (ll + rr) * (ll - rr);
    REQUIRE(number_t<10>{expected_square, strlen(expected_square)} == res);
}


const char * l1 = "5L1AJ62HKSBOB6V9TSU9CLPHSMRGDOJ3T61FRTS2EBG32HJ4QMVFVLCSIVO1UEC60L044A45B3KLD8QQOB123IOO45K30V4P4COPMFCILHOU8DDNJO48KV5FDD1PLHLHQ6GF32QOG2AV4P61VENQ66DF3768QGFLJICNCL";
const char * r1 = "41G1QK";

const char * expected1 = "MSL6OALBR175TRP685O5DV6SP4EO736BHQ032NSQEN3K0KIKJJN6L0IB3E7O64KSOO2HLUBE1H4E4P0ANQQ2SN9LF5C0T7VTCBQTMC7GC5S56OLH81ELIUV1ABO5AOECN1FDN5SV63OHG59B5ESOOFBS721M0BJBH5LFL9HRHV4";
const char * expected_square1 = "";


TEST_CASE("mult_d (32base)", "[mult]") {
    number_t<32> ll{l1, strlen(l1)};
    number_t<32> rr{r1, strlen(r1)};
    number_t<32> res = ll * rr;

    REQUIRE(number_t<32>{expected1, strlen(expected1)} == res);

    res = (ll + rr) * (ll - rr);
}
