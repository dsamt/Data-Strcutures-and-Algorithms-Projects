#include <cstdlib>
#include <ctime>
#include "catch.hpp"
#include <memory>
#include "XO.hpp"

//X = -1
//O = 1

TEST_CASE("Player X immediate win")
{
	INFO("Player X eventual win");
	XO g;
	g.makeMove(-1, 2);
	g.makeMove(1, 0);
	g.makeMove(-1, 3);
	g.makeMove(1, 7);
	g.makeMove(-1, 6);
	g.makeMove(1, 8);

	g.show();

	while (!g.gameOver())
		g.makeOptimalMove();

	g.show();

	REQUIRE(g.winner() == -1);
	REQUIRE(g.getBoard().numMoves == 7);
}

TEST_CASE("Optimal block w/certain loss for O")
{
	INFO("Optimal block w/certain loss for O");
	XO g;
	g.makeMove(-1, 1);
	g.makeMove(1, 6);
	g.makeMove(-1, 5);
	g.makeMove(1, 7);
	g.makeMove(-1, 8);

	g.makeOptimalMove();

	g.show();

	REQUIRE(g.winner() == 0);
	REQUIRE(g.getBoard().numMoves == 6);
}

TEST_CASE("Player X eventual win")
{
	INFO("Player X eventual win");
	XO g;
	g.makeMove(-1, 1);
	g.makeMove(1, 6);
	g.makeMove(-1, 5);
	g.makeMove(1, 7);
	g.makeMove(-1, 8);

	while (!g.gameOver())
		g.makeOptimalMove();

	g.show();

	REQUIRE(g.winner() == -1);
	REQUIRE(g.getBoard().numMoves == 9);
}

TEST_CASE("Optimal block w/certain loss for X")
{
	INFO("Optimal block w/certain loss for X");
	XO g;
	g.makeMove(1, 1);
	g.makeMove(-1, 6);
	g.makeMove(1, 5);
	g.makeMove(-1, 7);
	g.makeMove(1, 8);

	// while(!g.gameOver())
	//   g.makeOptimalMove();

	g.makeOptimalMove();

	g.show();

	REQUIRE(g.winner() == 0);
	REQUIRE(g.getBoard().numMoves == 6);
}

TEST_CASE("Player O eventual win")
{
	INFO("Player O eventual win");
	XO g;
	g.makeMove(1, 1);
	g.makeMove(-1, 6);
	g.makeMove(1, 5);
	g.makeMove(-1, 7);
	g.makeMove(1, 8);

	while (!g.gameOver())
		g.makeOptimalMove();

	g.show();

	REQUIRE(g.winner() == 1);
	REQUIRE(g.getBoard().numMoves == 9);
}


TEST_CASE("parameterized constructor", "[XO]") {
	int8_t p[] = { -1,1,-1,1,-1,1 };
	uint8_t po[] = { 2,0,3,7,6,8 };

	XO brd(p, po, 6);

	//brd.show();

	//REQUIRE(brd.state[] == 1, 0, -1, -1, 0, 0, -1, 1, 1);
}

TEST_CASE("makeMove", "[XO]") {
	XO g;

	g.makeMove(-1, 2);
	g.makeMove(1, 0);
	g.makeMove(-1, 3);
	g.makeMove(1, 7);
	g.makeMove(-1, 6);
	g.makeMove(1, 8);

	//g.show();
}

TEST_CASE("makeMoves", "[XO]") {
	int8_t p[] = { -1,1,-1,1,-1,1 };
	uint8_t po[] = { 2,0,3,7,6,8 };

	XO brd;

	brd.makeMoves(p, po, 6);

	//brd.show();
	REQUIRE(brd.winner() == 0);
	REQUIRE(brd.getBoard().numMoves == 6);
}

TEST_CASE("game over", "[XO]") {
	XO g;

	for (int i = 0; !g.gameOver(); i++) {
		if (i == 0 || i % 2 == 0) {
			g.makeMove(-1, i);
		}
		else {
			g.makeMove(1, i);
		}
	}
	

	//g.show();
	REQUIRE(g.winner() == -1);
}
TEST_CASE("optimal move") {
	int8_t p[] = { -1,1,-1,1,-1,1 };
	uint8_t po[] = { 2,0,3,7,6,8 };

	XO brd;

	brd.makeMoves(p, po, 6);
	brd.show();

	//brd.makeOptimalMove();
	//brd.show();
	//REQUIRE(brd.winner() == -1);
}

TEST_CASE("invalid moves") {
	int8_t p[] = { -1,1,-1,1,-1,1,-1 };
	uint8_t po[] = { 2,0,3,7,6,8,2 };
	XO brd;

	REQUIRE_FALSE(brd.makeMoves(p, po, 10));

	
}