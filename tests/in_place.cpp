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

TEST_CASE("In place", "[in_place]") {
  tl::optional<int> o1{tl::in_place};
  tl::optional<int> o2(tl::in_place);
  REQUIRE(o1);
  REQUIRE(o1 == 0);
  REQUIRE(o2);
  REQUIRE(o2 == 0);

  tl::optional<int> o3(tl::in_place, 42);
  REQUIRE(o3 == 42);
}
