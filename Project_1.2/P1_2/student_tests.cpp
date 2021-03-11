#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE

#include "catch.hpp"
#include "dNode.hpp"
#include "dLinkedList.hpp"
#include "Tape.hpp"
#include "TuringMachine.hpp"

//Your tests go here.

TEST_CASE("default constrcutor", "[Tape]") {
	Tape T;

	REQUIRE(T.isEmpty());
	REQUIRE(T.getIndex() == -1);
	REQUIRE(T.getSize() == 0);

}


TEST_CASE("paramerterized constructor", "[Tape]") {
	std::vector<std::string> v = {"a", "b", "c"};
	Tape T(v);
	
	REQUIRE_FALSE(T.isEmpty());
	REQUIRE(T.getSize() == 3);

}

TEST_CASE("write blank", "[Tape]") {
	std::vector<std::string> v = { "a", "b", "c" };
	Tape T(v);

	T.moveLeft();
	T.writeBlank();
	//T.printTape();

	REQUIRE(T.readSymbol() == " ");
}

TEST_CASE("write symbol", "[Tape]") {
	std::vector<std::string> v = { "a", "b", "c" };
	Tape T(v);

	T.moveLeft();
	T.writeSymbol("s");
	//T.printTape();

	REQUIRE(T.readSymbol() == "s");
}

TEST_CASE("clear", "[Tape]") {
	std::vector<std::string> v = { "a", "b", "c" };
	Tape T(v);

	T.moveLeft();
	T.writeSymbol("s");


	T.clear();
	//T.printTape();
	REQUIRE(T.isEmpty());
	REQUIRE(T.getIndex() == -1);
	REQUIRE(T.getSize() == 0);
}

TEST_CASE("move left", "[Tape]") {
	std::vector<std::string> v = { "a", "b", "c" };
	Tape T(v);

	T.moveLeft();
	T.writeSymbol("s");
	//T.printTape();

	REQUIRE(T.readSymbol() == "s");
	REQUIRE(T.getIndex() == 1);
}

TEST_CASE("move right", "[Tape]") {
	std::vector<std::string> v = { "a", "b", "c" };
	Tape T(v);

	T.moveLeft();
	T.moveRight();
	T.writeSymbol("s");
//	T.printTape();

	REQUIRE(T.readSymbol() == "s");
	REQUIRE(T.getIndex() == 2);
	REQUIRE_FALSE(T.moveRight());
}


TEST_CASE("copy constrcutor", "[Tape]") {
	std::vector<std::string> v = { "a", "b", "c" };
	Tape T(v);

	Tape N = T;
	//N.setTape(T);

	//std::cout << N.getIndex() << std::endl;
	//N.printTape();
	
	REQUIRE(N.readSymbol() == "c");
	N.moveLeft();
	REQUIRE(N.readSymbol() == "b");
	N.moveLeft();
	REQUIRE(N.readSymbol() == "a");
	
	//REQUIRE(&N != &T);
	//std::cout << T.getIndex() << std::endl;
	
	T.writeSymbol("a");
	T.moveLeft();
	T.writeSymbol("b");
	T.moveLeft();
	T.writeSymbol("c");

	//T.printTape();
	//std::cout << N.getIndex() << std::endl;
	
	REQUIRE(N.readSymbol() == "a");
	N.moveRight();
	REQUIRE(N.readSymbol() == "b");
	N.moveRight();
	REQUIRE(N.readSymbol() == "c");
	
	
}
TEST_CASE("set tape", "[Tape]") {
	std::vector<std::string> v = { "a", "b", "c" };
	Tape T(v);

	Tape N;
	N.setTape(T);

	//std::cout << N.getIndex() << std::endl;
//	N.printTape();

	REQUIRE(N.readSymbol() == "c");
	N.moveLeft();
	REQUIRE(N.readSymbol() == "b");
	N.moveLeft();
	REQUIRE(N.readSymbol() == "a");
}
TEST_CASE("rewind", "[Tape]") {
	std::vector<std::string> v = { "a", "b", "c" };
	Tape T(v);

	REQUIRE(T.getIndex() == 2);

	T.rewind();

	REQUIRE(T.getIndex() == 0);
}


TEST_CASE("default constructor", "[Turing]") {
	TuringMachine T;

	std::vector<std::string> sym = {};
	Tape N = T.getTape();
	REQUIRE(T.getSymbols() == sym);
	REQUIRE(N.isEmpty());
}


TEST_CASE("Paramerterized constructor", "[Turing]") {
	std::vector<std::string> v = { "a", "b", "c" };
	Tape T(v);

	TuringMachine N(T, v);

	Tape ta = N.getTape();

	REQUIRE(N.getSymbols() == v);
	REQUIRE(ta.getSize() == T.getSize());

}

TEST_CASE("set symbols", "[Turing]"){
	std::vector<std::string> v = { "a", "b", "c" };
	Tape N(v);

	TuringMachine T(N, v);

	T.setSymbols(v);

	REQUIRE(T.setSymbols(v));
}

TEST_CASE("Set tape", "[Turing]") {
	std::vector<std::string> v = { "a", "b", "c" };
	Tape N(v);

	TuringMachine T(N, v);

	REQUIRE(T.setTape(N));
}

TEST_CASE("setup check", "[Turing]") {
	std::vector<std::string> v = { "a", "b", "c" };
	Tape N(v);

	TuringMachine T(N, v);

	REQUIRE(T.setupCheck());
}

TEST_CASE("pattern match", "[Turing]") {
	std::vector<std::string> v = { "a", "b", "c" };
	Tape N(v);

	TuringMachine T(N, v);

	REQUIRE(T.patternMatch());

	std::vector<std::string> m = { "c", "b", "c" };
	Tape M(m);

	TuringMachine Ta(M, m);

	REQUIRE_FALSE(Ta.patternMatch());

	std::vector<std::string> mc = { "b", "a", "c" };
	Tape Mc(mc);

	TuringMachine Tac(Mc, mc);

	REQUIRE_FALSE(Tac.patternMatch());

}