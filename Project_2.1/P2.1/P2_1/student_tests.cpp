#include "catch.hpp"
#include "Stack.hpp"

TEST_CASE( "Peak at empty stack", "[Stack]" )
{
  Stack<int> s;
  
  REQUIRE_THROWS_AS(s.peek(), std::range_error);
}

TEST_CASE("default constructor", "[Stack]") {
	Stack<int> s;

	REQUIRE(s.isEmpty());
	REQUIRE(s.size() == 0);

}

TEST_CASE("copy constructor", "[Stack]") {
	
	Stack<int> s;
	

	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);
	

	
	Stack<int> t(s);

	REQUIRE(t.size() == 4);
	REQUIRE(t.peek() == 4);
	t.pop();
	REQUIRE(t.peek() == 3);
	t.pop();
	REQUIRE(t.peek() == 2); 
	t.pop();
	REQUIRE(t.peek() == 1);
	
	Stack<int> w;


	w.push(1);
	w.push(2);
	w.push(3);
	w.push(4);

	Stack<int> T(w);

	w.pop();
	w.pop();
	w.pop();
	w.pop();

	w.push(5);
	w.push(6);
	w.push(7);
	w.push(8);

	REQUIRE(T.size() == 4);
	REQUIRE(T.peek() == 4);
	T.pop();
	REQUIRE(T.peek() == 3);
	T.pop();
	REQUIRE(T.peek() == 2);
	T.pop();
	REQUIRE(T.peek() == 1);
}


TEST_CASE("size", "[Stack]"){
	Stack<int> s;

	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);

	REQUIRE(s.size() == 4);
	s.pop();
	REQUIRE(s.size() == 3);
	s.pop();
	REQUIRE(s.size() == 2);
	s.pop();
	REQUIRE(s.size() == 1);
	s.pop();
	REQUIRE(s.isEmpty());
	REQUIRE(s.size() == 0);
}

TEST_CASE("is empty", "[Stack]") {
	Stack<int> s;

	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);

	s.pop();
	s.pop();
	s.pop();
	s.pop();

	REQUIRE(s.isEmpty());

	s.push(2);
	REQUIRE_FALSE(s.isEmpty());

}


TEST_CASE("push", "[Stack]") {
	Stack<int> s;

	s.push(1);
	REQUIRE(s.peek() == 1);
	s.push(2);
	REQUIRE(s.peek() == 2);
	s.push(3);
	REQUIRE(s.peek() == 3);
	s.push(4);
	REQUIRE(s.peek() == 4);
}

TEST_CASE("pop", "[Stack]") {
	Stack<int> s;

	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);

	s.pop();
	REQUIRE(s.peek() == 3);
	s.pop();
	REQUIRE(s.peek() == 2);
	s.pop();
	REQUIRE(s.peek() == 1);
	s.pop();

	REQUIRE(s.isEmpty());

	s.pop();
	REQUIRE_THROWS_AS(s.peek(), std::range_error);


}

TEST_CASE("peek", "[Stack]") {
	Stack<int> s;

	s.push(1);
	REQUIRE(s.peek() == 1);
	s.push(2);
	REQUIRE(s.peek() == 2);
	s.push(3);
	REQUIRE(s.peek() == 3);
	s.push(4);
	REQUIRE(s.peek() == 4);

	s.pop();
	REQUIRE(s.peek() == 3);
	s.pop();
	REQUIRE(s.peek() == 2);
	s.pop();
	REQUIRE(s.peek() == 1);
	s.pop();
	s.pop();

	REQUIRE_THROWS_AS(s.peek(), std::range_error);
}

TEST_CASE("clear", "[Stack]") {
	Stack<int> s;

	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);

	s.clear();

	REQUIRE(s.isEmpty());
	REQUIRE(s.size() == 0);
}