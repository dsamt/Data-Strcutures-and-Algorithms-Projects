#include <string>

#include "catch.hpp"
#include "bbdb.hpp"

std::string path("../"); //uncomment for submitting to grader
//std::string path(".\"); //comment when submitting to grader (Windows)
//std::string path("./"); //comment when submitting to grader (Mac/UNIX)

TEST_CASE("Parameterized constructor", "[bbdb]" )
{
  BBDB db(path + "2017-18_playerBoxScore.csv");

  REQUIRE(db.select("playPTS >= 50").size() == 13);
  REQUIRE(db.select("playPTS >= 50")[0] == "2017-11-03,LeBron James,playPTS,57");
  REQUIRE(db.select("playPTS >= 50")[1] == "2017-11-05,James Harden,playPTS,56");
  REQUIRE(db.select("playPTS >= 50")[2] == "2017-12-05,Bradley Beal,playPTS,51");
  REQUIRE(db.select("playPTS >= 50")[3] == "2017-12-20,James Harden,playPTS,51");
  REQUIRE(db.select("playPTS >= 50")[4] == "2017-12-22,James Harden,playPTS,51");
  REQUIRE(db.select("playPTS >= 50")[5] == "2018-01-01,DeMar DeRozan,playPTS,52");
  REQUIRE(db.select("playPTS >= 50")[6] == "2018-01-10,Lou Williams,playPTS,50");
  REQUIRE(db.select("playPTS >= 50")[7] == "2018-01-30,James Harden,playPTS,60");
  REQUIRE(db.select("playPTS >= 50")[8] == "2018-01-31,C.J. McCollum,playPTS,50");
  REQUIRE(db.select("playPTS >= 50")[9] == "2018-02-09,Damian Lillard,playPTS,50");
  REQUIRE(db.select("playPTS >= 50")[10] == "2018-02-14,Kevin Durant,playPTS,50");
  REQUIRE(db.select("playPTS >= 50")[11] == "2018-02-26,Anthony Davis,playPTS,53");
  REQUIRE(db.select("playPTS >= 50")[12] == "2018-03-28,Karl-Anthony Towns,playPTS,56");

  REQUIRE(db.select("playAST >= 19")[0] == "2017-12-27,Rajon Rondo,playAST,25");
  REQUIRE(db.select("playAST >= 19")[1] == "2018-01-20,Russell Westbrook,playAST,20");
  REQUIRE(db.select("playAST >= 19")[2] == "2018-02-01,Russell Westbrook,playAST,21");
  REQUIRE(db.select("playAST >= 19")[3] == "2018-04-11,Russell Westbrook,playAST,19");

  REQUIRE(db.select("playBLK >= 10")[0] == "2018-03-11,Anthony Davis,playBLK,10");

  REQUIRE(db.select("playSTL >= 7")[0] == "2017-11-20,Victor Oladipo,playSTL,7");
  REQUIRE(db.select("playSTL >= 7")[1] == "2017-11-26,Tyus Jones,playSTL,7");
  REQUIRE(db.select("playSTL >= 7")[2] == "2017-12-13,Thaddeus Young,playSTL,7");
  REQUIRE(db.select("playSTL >= 7")[3] == "2017-12-15,Chris Paul,playSTL,7");
  REQUIRE(db.select("playSTL >= 7")[4] == "2018-01-06,Willie Cauley-Stein,playSTL,7");
  REQUIRE(db.select("playSTL >= 7")[5] == "2018-01-14,DeMarcus Cousins,playSTL,7");
  REQUIRE(db.select("playSTL >= 7")[6] == "2018-01-20,Lou Williams,playSTL,10");
  REQUIRE(db.select("playSTL >= 7")[7] == "2018-01-23,Dejounte Murray,playSTL,7");
  REQUIRE(db.select("playSTL >= 7")[8] == "2018-04-01,Robert Covington,playSTL,7");

  db.select("playPTS >= 5 AND playAST >= 1 AND playSTL >= 3 AND playBLK >= 1");

  REQUIRE(db.select("playPTS >= 50 AND playAST >= 10")[0] == "2017-11-05,James Harden,playPTS,56,playAST,13");
  REQUIRE(db.select("playAST >= 10 AND playPTS >= 50")[0] == "2017-11-05,James Harden,playAST,13,playPTS,56");
  
  REQUIRE(db.select("playPTS >= 50 AND playBLK >= 2")[0] == "2017-11-03,LeBron James,playPTS,57,playBLK,2");
  REQUIRE(db.select("playAST >= 10 AND playSTL >= 4 AND playPTS >= 50 AND playBLK >= 1")[0] == "2018-01-30,James Harden,playAST,11,playSTL,4,playPTS,60,playBLK,1");
  REQUIRE(db.select("playAST >= 10 AND playSTL >= 4 AND playPTS >= 50")[0] == "2018-01-30,James Harden,playAST,11,playSTL,4,playPTS,60");

  //REQUIRE(db.select())

  BBDB bdb(path + "2017-18_playerBoxScore.csv");

  REQUIRE(bdb.select("playpats >= 50").empty());
  REQUIRE(bdb.select("playPTS >= 50 AND playPTS >= 50").empty());
  REQUIRE(bdb.select("playPTS <= 20 AND playAST >= 4 AND playBLK >= 3 AND playSTL >= 7").empty());
  REQUIRE(bdb.select("playPTS >= 50 and playAst >= 5").empty());
}

//couldn't figure out  how to test when the default constructor would throw an error
TEST_CASE("default constructor") {
	//BBDB db;
	//REQUIRE_THROWS_AS(db, std::runtime_error);
}