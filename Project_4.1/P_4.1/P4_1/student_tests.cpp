#include "catch.hpp"
#include "Deque.hpp"

TEST_CASE( "Peak at empty deque", "[deque]" )
{
  Deque<int> d;
  
  REQUIRE_THROWS_AS(d.front(), std::range_error);
  REQUIRE(d.isEmpty());
}

TEST_CASE("PUSH FRONT", "[Deque]") {
	Deque<int> d;

	d.pushFront(1);
	d.pushFront(2);
	d.pushFront(3);
	d.pushFront(4);


	REQUIRE(d.front() == 4);

	Deque<int> s;

	s.pushFront(1);
	s.popBack();

	REQUIRE(s.isEmpty());

	Deque<int> q;

	for (int i = 0; i < 100; i++) {
		q.pushFront(1);
	}
	q.popBack();
	REQUIRE(q.front() == 1);
	REQUIRE(q.back() == 1);
}

TEST_CASE("push back", "[Deque]") {
	Deque<int> d;

	d.pushBack(1);
	d.pushBack(2);
	d.pushBack(3);
	d.pushBack(4);

	REQUIRE(d.back() == 4);
}

TEST_CASE("pop front", "[Deque]") {
	Deque<int> d;

	d.pushFront(1);
	d.pushFront(2);
	d.pushFront(3);
	d.pushFront(4);

	d.popFront();

	REQUIRE(d.front() == 3);

	d.popFront();
	d.popFront();
	d.popFront();

	REQUIRE(d.isEmpty());

	REQUIRE_THROWS_AS(d.popFront(), std::range_error);
}

TEST_CASE("pop back", "[DEQUE]") {
	Deque<int> d;

	d.pushBack(1);
	d.pushBack(2);
	d.pushBack(3);
	d.pushBack(4);

	d.popBack();

	REQUIRE(d.back() == 3);

	d.popBack();

	REQUIRE(d.back() == 2);

	d.popBack();

	REQUIRE(d.back() == 1);

	d.popBack();

	REQUIRE(d.isEmpty());

	REQUIRE_THROWS_AS(d.popBack(), std::range_error);
}

TEST_CASE("copy constructor", "[Deque]") {
	Deque<int> d;


	d.pushFront(1);
	REQUIRE(d.front() == 1);
	d.pushFront(2);
	REQUIRE(d.front() == 2);
	d.pushFront(3);
	REQUIRE(d.front() == 3);
	d.pushFront(4);
	REQUIRE(d.front() == 4);

	Deque<int> s(d);

	REQUIRE(s.front() == 4);
	REQUIRE(s.back() == 1);

	d.popFront();
	d.popFront();
	d.popFront();
	d.popFront();

	REQUIRE(d.isEmpty());
	REQUIRE_FALSE(s.isEmpty());

	d.pushBack(1);
	REQUIRE(d.back() == 1);
	d.pushBack(2);
	REQUIRE(d.back() == 2);
	d.pushBack(3);
	REQUIRE(d.back() == 3);
	d.pushBack(4);
	REQUIRE(d.back() == 4);

	REQUIRE(s.front() == 4);
	REQUIRE(s.back() == 1);
	
	Deque<int> a;
	Deque<int> b(a);


	REQUIRE(a.isEmpty());
	REQUIRE(b.isEmpty());
}

TEST_CASE("assignment operator", "[Deque]") {
	Deque<int> d;

	Deque<int> s;

	d.pushFront(1);
	REQUIRE(d.front() == 1);
	d.pushFront(2);
	REQUIRE(d.front() == 2);
	d.pushFront(3);
	REQUIRE(d.front() == 3);
	d.pushFront(4);
	REQUIRE(d.front() == 4);

	s = d;

	REQUIRE(s.front() == 4);
	REQUIRE(s.back() == 1);

	d.popFront();
	d.popFront();
	d.popFront();
	d.popFront();

	REQUIRE(d.isEmpty());
	REQUIRE_FALSE(s.isEmpty());

	d.pushBack(1);
	REQUIRE(d.back() == 1);
	d.pushBack(2);
	REQUIRE(d.back() == 2);
	d.pushBack(3);
	REQUIRE(d.back() == 3);
	d.pushBack(4);
	REQUIRE(d.back() == 4);

	REQUIRE(s.front() == 4);
	REQUIRE(s.back() == 1);


	Deque<int> a;
	Deque<int> b;

	a = b;

	REQUIRE(a.isEmpty());
	REQUIRE(b.isEmpty());
}