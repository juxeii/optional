#include <catch2/catch.hpp>
#include <tl/optional.hpp>

#include <tuple>
#include <vector>

struct takes_init_and_variadic {
  std::vector<int> v;
  std::tuple<int, int> t;
  template <class... Args>
  takes_init_and_variadic(std::initializer_list<int> l, Args &&...args)
      : v(l), t(std::forward<Args>(args)...) {}
};

TEST_CASE("Make optional", "[make_optional]") {
  auto o1 = tl::make_optional(42);
  auto o2 = tl::optional<int>(42);

  constexpr bool is_same = std::is_same<decltype(o1), tl::optional<int>>::value;
  REQUIRE(is_same);
  REQUIRE(o1 == o2);

  auto o3 = tl::make_optional<std::tuple<int, int, int, int>>(0, 1, 2, 3);
  REQUIRE(o3.filter([](auto v) { return std::get<0>(v) == 0; }).hasValue());
  REQUIRE(o3.filter([](auto v) { return std::get<1>(v) == 1; }).hasValue());
  REQUIRE(o3.filter([](auto v) { return std::get<2>(v) == 2; }).hasValue());
  REQUIRE(o3.filter([](auto v) { return std::get<3>(v) == 3; }).hasValue());

  auto o4 = tl::make_optional<std::vector<int>>({0, 1, 2, 3});
  REQUIRE(o4.filter([](auto v) { return v[0] == 0; }).hasValue());
  REQUIRE(o4.filter([](auto v) { return v[1] == 1; }).hasValue());
  REQUIRE(o4.filter([](auto v) { return v[2] == 2; }).hasValue());
  REQUIRE(o4.filter([](auto v) { return v[3] == 3; }).hasValue());

  auto i = 42;
  auto o6 = tl::make_optional<int &>(i);
  REQUIRE((std::is_same<decltype(o6), tl::optional<int &>>::value));
  REQUIRE(o6.hasValue());
  REQUIRE(o6 == 42);
}
