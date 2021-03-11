//#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE

#include "catch.hpp"
#include "RouteFinder.hpp"

// Your tests go here.

// !!!!!!
// Don't forget to replace dNode.txx and dLinkedList.txx with the correct files.

TEST_CASE("default constructor", "[RouteFinder]") {
	
	RouteFinder r;

	REQUIRE(r.getHouseNum() == 0);
	REQUIRE(r.getMaxBoxes() == 0);
	REQUIRE(r.getFinalDist() == 0);
	REQUIRE(r.getMaxDist() == 0);
	REQUIRE(r.getBoxes().empty());
	REQUIRE(r.getRouteDist().empty());
	REQUIRE(r.getBoxNum().empty());
	REQUIRE(r.getRoutes().empty());
	REQUIRE(r.getDist().empty());
	
}

TEST_CASE("parameterized constructor", "[RouteFinder]") {
	
	RouteFinder r("input2.txt");

	REQUIRE(r.getHouseNum() == 5);
	REQUIRE(r.getMaxBoxes() == 5);
	REQUIRE(r.getMaxDist() == 25);
	REQUIRE_FALSE(r.getBoxes().empty());
	REQUIRE_FALSE(r.getDist().empty());

	RouteFinder s("sample.txt");

	REQUIRE(s.getHouseNum() == 3);
	REQUIRE(s.getMaxBoxes() == 20);
	REQUIRE(s.getMaxDist() == 10);
	REQUIRE_FALSE(s.getBoxes().empty());
	REQUIRE_FALSE(s.getDist().empty());

	
	RouteFinder t("insbfias.txt");

	REQUIRE(t.getHouseNum() == 3);
	REQUIRE(t.getMaxBoxes() == 20);
	REQUIRE(t.getMaxDist() == 10);
	REQUIRE_FALSE(t.getBoxes().empty());
	REQUIRE_FALSE(t.getDist().empty());
	
}

TEST_CASE("copy constructor", "[RouteFinder]") {
	
	RouteFinder r("input2.txt");

	RouteFinder x(r);

	REQUIRE(r.getHouseNum() == 5);
	REQUIRE(r.getMaxBoxes() == 5);
	REQUIRE(r.getMaxDist() == 25);
	REQUIRE_FALSE(r.getBoxes().empty());
	REQUIRE_FALSE(r.getDist().empty());


	REQUIRE(x.getHouseNum() == 5);
	REQUIRE(x.getMaxBoxes() == 5);
	REQUIRE(x.getMaxDist() == 25);
	REQUIRE_FALSE(x.getBoxes().empty());
	REQUIRE_FALSE(x.getDist().empty());

	r.setHouseNum(7);
	r.setMaxBoxes(4);
	r.setMaxDist(2);

	REQUIRE(r.getHouseNum() == 7);
	REQUIRE(r.getMaxBoxes() == 4);
	REQUIRE(r.getMaxDist() == 2);

	REQUIRE(x.getHouseNum() == 5);
	REQUIRE(x.getMaxBoxes() == 5);
	REQUIRE(x.getMaxDist() == 25);
	REQUIRE_FALSE(x.getBoxes().empty());
	REQUIRE_FALSE(x.getDist().empty());
	
}

TEST_CASE("assignment operator", "[RouteFinder]") {
	
	RouteFinder r("input2.txt");

	RouteFinder x;

	x = r;

	REQUIRE(r.getHouseNum() == 5);
	REQUIRE(r.getMaxBoxes() == 5);
	REQUIRE(r.getMaxDist() == 25);
	REQUIRE_FALSE(r.getBoxes().empty());
	REQUIRE_FALSE(r.getDist().empty());


	REQUIRE(x.getHouseNum() == 5);
	REQUIRE(x.getMaxBoxes() == 5);
	REQUIRE(x.getMaxDist() == 25);
	REQUIRE_FALSE(x.getBoxes().empty());
	REQUIRE_FALSE(x.getDist().empty());

	r.setHouseNum(7);
	r.setMaxBoxes(4);
	r.setMaxDist(2);

	REQUIRE(r.getHouseNum() == 7);
	REQUIRE(r.getMaxBoxes() == 4);
	REQUIRE(r.getMaxDist() == 2);

	REQUIRE(x.getHouseNum() == 5);
	REQUIRE(x.getMaxBoxes() == 5);
	REQUIRE(x.getMaxDist() == 25);
	REQUIRE_FALSE(x.getBoxes().empty());
	REQUIRE_FALSE(x.getDist().empty());
	

}

TEST_CASE("solve", "[RouteFinder]") {
	
	RouteFinder r("input1.txt");

	r.solve();

	REQUIRE(r.getFinalDist() == 16.66);

	RouteFinder s("input2.txt");

	s.solve();

	REQUIRE(s.getFinalDist() == 59);

	RouteFinder x("input5.txt");

	x.solve();

	REQUIRE(x.getFinalDist() == 481);	
	
	RouteFinder t("input3.txt");

	t.solve();

	REQUIRE_FALSE(t.getFinalDist() == 39.98);
	
	RouteFinder w("input6.txt");

	w.solve();
	
	REQUIRE_FALSE(w.getFinalDist() == 63.1);
}

TEST_CASE("setters", "[RouterFinder]") {
	RouteFinder r;

	std::vector<int> test = { 1, 2, 3, 4 };

	r.setBoxes(test);

	REQUIRE(r.getBoxes() == test);

	dLinkedList<double> list;

	list.add(1);
	list.add(2);
	list.add(3);
	list.add(4);

	std::vector<dLinkedList<double>> list_vect;
	list_vect.push_back(list);

	r.setDist(list_vect);

	r.setHouseNum(5);

	REQUIRE(r.getHouseNum() == 5);

	r.setMaxBoxes(30);

	REQUIRE(r.getMaxBoxes() == 30);

	r.setMaxDist(15);

	REQUIRE(r.getMaxDist() == 15);
}