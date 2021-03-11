#include "catch.hpp"

#include "Maze.hpp"

TEST_CASE( "create valid", "[Stack]" )
{
  INFO("Hint: creating a valid mazes");

  Maze m;

  REQUIRE(m.create(10,10,0,8));

  std::cout << m;

  
  m.solve();
  std::cout << m;
}


TEST_CASE("paramaterized constructor", "[Maze]") {
	Maze m(10, 10, 0, 8);

	//REQUIRE_THROWS_AS(m, std::invalid_argument);

	std::cout << m;
}

TEST_CASE("write", "[Maze]") {
	Maze m;

	REQUIRE(m.create(100, 100, 0, 8));

	m.solve();


	REQUIRE(m.write("maze.png"));
	
}


TEST_CASE("get", "[Maze]") {
	Maze m;

	REQUIRE(m.create(10, 10, 0, 8));


	std::vector<unsigned char> w;
	w = m.get();

	REQUIRE(w.size() == 100);

}

TEST_CASE("set", "[Maze]") {
	Maze m;

	REQUIRE(m.create(10, 10, 0, 8));

	REQUIRE(m.set(m.get(), 10));

	Maze w;

	//REQUIRE_FALSE(w.create(0, 10, 0, 8));
	//REQUIRE_FALSE(w.set(w.get(), 0));

}

TEST_CASE("solve", "[maze]") {
	Maze m;

	REQUIRE(m.create(10, 10, 0, 8));

	REQUIRE_FALSE(m.solve());
}

TEST_CASE("read", "[Maze]") {
	Maze m;

	REQUIRE(m.create(10, 10, 0, 8));

	REQUIRE_FALSE(m.read("maze.png"));
}

