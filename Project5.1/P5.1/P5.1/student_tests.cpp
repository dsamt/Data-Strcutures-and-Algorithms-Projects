#include "catch.hpp"
#include "treap_bst.hpp"


// Your test cases here...
//any function calls for height() are commented out for the autograder running my local tests as the randomness of priorority does not always hold the same height
//if the priorities change
TEST_CASE("default constructor", "[Treap]") {
	TreapBST<int, int> t;
	
	REQUIRE(t.empty());
}

TEST_CASE("Insert", "[Treap]") {
	TreapBST<int, int> t;

	t.insert(5, 10);
	t.insert(3, 20);
	t.insert(4, 40);
	t.insert(7, 30);
	t.insert(6, 60);
	t.insert(8, 50);

	REQUIRE_FALSE(t.empty());
	//REQUIRE(t.height() == 4);

	//t.inOrderTraverse();
	//t.print();

	t.remove(5);

	//t.print();

	TreapBST<int, int> b;

	b.insert(5, 30);

	REQUIRE_THROWS_AS(b.insert(5, 50), std::logic_error);
}

TEST_CASE("copy constructor", "[Treap]") {
	TreapBST<int, int> t;

	t.insert(5, 10);
	t.insert(3, 20);
	t.insert(4, 40);
	t.insert(7, 30);
	t.insert(6, 60);
	t.insert(8, 50);

	//REQUIRE(t.height() == 4);

	TreapBST<int, int> b(t);

	//REQUIRE(b.height() == 4);

	t.remove(4);

	//REQUIRE(b.height() == 4);
	//REQUIRE(t.height() == 3);

}

TEST_CASE("height", "[Treap]") {
	TreapBST<int, int> t;

	REQUIRE(t.empty());
	REQUIRE(t.height() == 0);
	/*
	t.insert(5, 10);
	REQUIRE(t.height() == 1);
	t.insert(3, 20);
	REQUIRE(t.height() == 2);
	t.insert(4, 40);
	REQUIRE(t.height() == 2);
	t.insert(7, 30);
	REQUIRE(t.height() == 3);
	t.insert(6, 60);
	REQUIRE(t.height() == 4);
	t.insert(8, 50);
	REQUIRE(t.height() == 4);
	*/
}

TEST_CASE("remove", "[Treap]") {
	TreapBST<int, int> t;

	REQUIRE(t.empty());
	REQUIRE(t.height() == 0);
	/*
	t.insert(5, 10);
	REQUIRE(t.height() == 1);
	t.insert(3, 20);
	REQUIRE(t.height() == 2);
	t.insert(4, 40);
	REQUIRE(t.height() == 2);
	t.insert(7, 30);
	REQUIRE(t.height() == 3);
	t.insert(6, 60);
	REQUIRE(t.height() == 4);
	t.insert(8, 50);
	t.print();
	REQUIRE(t.height() == 5);

	REQUIRE(t.height() == 5);
	t.remove(5);
	REQUIRE(t.height() == 4);
	t.remove(6);
	REQUIRE(t.height() == 3);
	t.remove(7);
	REQUIRE(t.height() == 2);
	t.remove(3);
	REQUIRE(t.height() == 2);
	t.remove(8);
	REQUIRE(t.height() == 1);
	t.remove(4);
	REQUIRE(t.height() == 0);
	REQUIRE(t.empty());
	REQUIRE_THROWS_AS(t.remove(4), std::logic_error);
	*/
}

TEST_CASE("search", "[Treap]") {
	TreapBST<int, int> t;

	t.insert(5, 10);
	t.insert(3, 20);
	t.insert(4, 40);
	t.insert(7, 30);
	t.insert(6, 60);
	t.insert(8, 50);

	bool flag = false;
	REQUIRE(t.search(5, flag) == 10);
	REQUIRE(t.search(3, flag) == 20);
	REQUIRE(t.search(4, flag) == 40);
	REQUIRE(t.search(7, flag) == 30);
	REQUIRE(t.search(6, flag) == 60);
	REQUIRE(t.search(8, flag) == 50);

}

TEST_CASE("copay assignment operator", "[Treap]") {
	TreapBST<int, int> t;

	TreapBST<int, int> b;

	t.insert(5, 10);
	t.insert(3, 20);
	t.insert(4, 40);
	t.insert(7, 30);
	t.insert(6, 60);
	t.insert(8, 50);

	//REQUIRE(t.height() == 4);

	b = t;
	//REQUIRE(b.height() == t.height());

	t.remove(3);
	t.remove(8);
	t.remove(5);

	//REQUIRE_FALSE(b.height() == t.height());

}