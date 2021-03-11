#ifndef BBDB_HPP
#define BBDB_HPP

#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <cmath>
#include <algorithm>

class BBDB
{
public:
  /** 
   * Default constructor: read file db.csv in current directory and build indices for searching
   * throws std::runtime_error if db.csv cannot be read
   */
  BBDB();

  /**
   * Use the parameter to read the given csv file and build indices for searching
   * @param filename - name (with path) to csv file containing database information
   * throws std::runtime_error if file cannot be read
   */
  BBDB(std::string filename);

  /**
   * Search over all entries in database to find games in which a player meets or exceeds values in statistical categories provided by user
   * throws std::runtime_error if query is invalid
   * @param query - database search string consisting of statistical category and respective minimum value player must exceed
   * @return empty std::vector if there are no results that match query or vector of strings consisting of `gmDate,playDispNm,Category1Name,Category1Data,...,CategoryNName,CategoryNData' for each player in each game matching search criteria
   */
  std::vector<std::string> select(std::string query) const;

private:
	//struct to represent a player and his statistic data for a certain night and the stats for points, assists, steal, and blocks
	struct statistics {
		std::string gmDate;
		std::string playDisplayNm;
		int playPTS;
		int playAST;
		int playSTL;
		int playBLK;
	};
	//defining a struct representation for a single player
	statistics stat;
	//defining vector container to hold all the players structs data
	std::vector<statistics> statVect;
	
};

#endif
