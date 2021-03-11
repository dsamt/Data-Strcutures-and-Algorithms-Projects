#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "dNode.hpp"
#include "dLinkedList.hpp"
#include "Tape.hpp"
#include "TuringMachine.hpp"

// Your tests go here...
//assumption: testing dLinkdList methods implicity tests most dNode methods
TEST_CASE("constructor", "[dLinkedList]")
{
	dLinkedList<int> b;
	REQUIRE(b.isEmpty());
	REQUIRE(b.getCurrentSize() == 0);
	REQUIRE(b.getHead() == nullptr);
}

TEST_CASE("add", "[dLinkedList]")
{
	dLinkedList<int> b;
	b.add(4);
	REQUIRE_FALSE(b.isEmpty());
	REQUIRE(b.getCurrentSize() == 1);
	REQUIRE(b.contains(4));
	REQUIRE_FALSE(b.contains(0));
}

TEST_CASE("add several", "[dLinkedList]")
{
	dLinkedList<int> b;
	b.add(4);
	b.add(10);
	b.add(1);
	b.add(-3);
	b.add(1);
	REQUIRE_FALSE(b.isEmpty());
	REQUIRE(b.getCurrentSize() == 5);
	REQUIRE(b.contains(4));
	REQUIRE(b.contains(10));
	REQUIRE(b.contains(-3));
	REQUIRE(b.contains(1));

}

TEST_CASE("remove", "[dLinkedList]")
{
	dLinkedList<int> b;
	b.add(4);
	b.add(10);
	b.add(1);
	b.add(-3);
	b.add(1);

//	b.printList();
	//b.printReverseList();

	REQUIRE(b.remove(-3));
	REQUIRE_FALSE(b.isEmpty());
	REQUIRE(b.getCurrentSize() == 4);
	REQUIRE(b.contains(4));
	REQUIRE(b.contains(10));
	REQUIRE_FALSE(b.contains(-3));
	REQUIRE(b.contains(1));

	REQUIRE(b.remove(1));
	REQUIRE_FALSE(b.isEmpty());
	REQUIRE(b.getCurrentSize() == 3);
	REQUIRE(b.contains(4));
	REQUIRE(b.contains(10));
	REQUIRE(b.contains(1));
}

TEST_CASE("remove when empty", "[dLinkedList]")
{
	dLinkedList<int> b;
	b.add(1);
	b.add(2);
	b.add(3);

	b.remove(2);
	b.remove(3);
	b.remove(1);
	REQUIRE_FALSE(b.remove(1));
}

TEST_CASE("copy", "[dLinkedList]")
{
	dLinkedList<int> b;
	b.add(4);
	b.add(10);
	b.add(1);
	b.add(-3);
	b.add(1);

	dLinkedList<int> c = b;
	REQUIRE(c.contains(4));
	REQUIRE(c.contains(10));
	REQUIRE(c.contains(1));
	REQUIRE(c.contains(-3));
	REQUIRE(c.contains(1));
	//ensure that copy and original don't exist at same memory location
	REQUIRE(&c != &b); //doesn't prove deep copy (shallow copies occupy diff. addresses.

	//none of the above proves deep copy, as c could still point to what b points to...let's change all of B's entries
	b.remove(4);
	b.remove(10);
	b.remove(1);
	b.remove(-3);
	b.remove(1);
	b.add(5);
	b.add(11);
	b.add(2);
	b.add(-2);
	b.add(2);

	REQUIRE(c.contains(4));
	REQUIRE(c.contains(10));
	REQUIRE(c.contains(1));
	REQUIRE(c.contains(-3));
	REQUIRE(c.contains(1));
}

TEST_CASE("Get frequency of", "[dLinkedList]") {
	dLinkedList<int> b;

	b.add(4);
	b.add(4);
	b.add(4);
	b.add(4);
	b.add(4);

	REQUIRE(b.getFrequencyOf(4) == 5);
}

TEST_CASE("clear", "[dLinkedList]") {
	dLinkedList<int> b;

	b.add(4);
	b.add(4);
	b.add(4);
	b.add(4);
	b.add(4);

	b.clear();

	REQUIRE(b.getCurrentSize() == 0);
	REQUIRE(b.getFrequencyOf(4) == 0);
	REQUIRE_FALSE(b.contains(4));
}

TEST_CASE("insert at", "[dLinkedList]") {
	dLinkedList<int> b;

	b.insertAt(1, 3);

	REQUIRE(b.contains(1));
	REQUIRE(b.getIndex(1) == 0);

	b.add(4);
	b.add(5);
	b.add(6);
	b.add(7);
	b.add(8);

	b.insertAt(5, 3);

	REQUIRE(b.contains(5));
	REQUIRE(b.getIndex(5) == 3);
}

TEST_CASE("remove at", "[dLinkedList]") {
	dLinkedList<int> b;

	b.add(4);
	b.add(5);
	b.add(6);
	b.add(7);
	b.add(8);
	b.printList();

	b.removeAt(3);
	b.printList();
	REQUIRE_FALSE(b.contains(5));
}

TEST_CASE("get index", "[dLinkedList]") {
	dLinkedList<int> b;

	b.add(5);
	b.add(11);
	b.add(3);
	b.add(-2);
	b.add(2);


	REQUIRE(b.getIndex(-2) == 1);
	REQUIRE(b.getIndex(3) == 2);
}

TEST_CASE("get item", "[dLinkedList]") {
	dLinkedList<int> b;

	b.add(5);
	b.add(11);
	b.add(3);
	b.add(-2);
	b.add(2);


	REQUIRE(b.getItem(2) == 3);
	REQUIRE(b.getItem(3) == 11);
}

TEST_CASE("add front", "[dLinkedlist]") {
	dLinkedList<int> b;

	b.add(5);
	b.add(11);
	b.add(3);
	b.add(-2);
	b.add(2);
	

	b.addFront(1);
	//b.printList();


	REQUIRE(b.contains(1));
	REQUIRE(b.getIndex(1) == 0);


}

TEST_CASE("add back", "[dLinkedList]") {
	dLinkedList<int> b;

	b.add(5);
	b.add(11);
	b.add(3);
	b.add(-2);
	b.add(2);
	

	b.addBack(1);
	//b.printList();

	REQUIRE(b.contains(1));
	REQUIRE(b.getIndex(1) == 5);
}

TEST_CASE("replace", "[dLinkedList]") {
	dLinkedList<int> b;

	b.add(5);
	b.add(11);
	b.add(3);
	b.add(-2);
	b.add(2);

	b.replace(3, 4);

	REQUIRE(b.contains(4));
	REQUIRE(b.getIndex(4) == 3);
}

