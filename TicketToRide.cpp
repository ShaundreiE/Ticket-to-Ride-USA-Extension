#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>

using namespace std;

// ************************* CITY ************************
const int city_size = 36;
string city_list[] = {"Atlanta", "Boston", "Calgary", "Charleston", "Chicago", "Dallas", "Denver", "Duluth", "El_Paso", "Helena", "Houston", "Kansas_City", "Las_Vegas", "Little_Rock", "Los_Angeles", "Miami", "Montreal", "Nashville", "New_Orleans", "New_York", "Oklahoma_City", "Omaha", "Phoenix", "Pittsburgh", "Portland", "Raleigh", "Saint_Louis", "Salt_Lake_City", "San_Francisco", "Santa_Fe", "Sault_St._Marie", "Seattle", "Toronto", "Vancouver", "Washington", "Winnipeg"};

class City {
public:
    int city_num;
    string name;
    vector<City*> neighbours;
    
    // for Dijkstra's algorithm
    bool visited;
    int shortest;
    int length;     // how many roads to build to get here
    
    // contructor
    City(int n) {
        city_num = n;
        name = city_list[n];
        visited = false;
        shortest = 2147483647;
    }
};

City* c[36];

// ********************** DISTANCES **********************
map<string, int> distances;
bool long_enough;

// initiates distances between cities
void init_distances() { // TOTAL 78
    // ****************** LENGTH 1 ******************   5
    // VANCOUVER - SEATTLE
    distances[city_list[33] + " - " + city_list[31]] = 1;
    distances[city_list[31] + " - " + city_list[33]] = 1;
    // SEATTLE - PORTLAND
    distances[city_list[31] + " - " + city_list[24]] = 1;
    distances[city_list[24] + " - " + city_list[31]] = 1;
    // OMAHA - KANSAS_CITY
    distances[city_list[21] + " - " + city_list[11]] = 1;
    distances[city_list[11] + " - " + city_list[21]] = 1;
    // DALLAS - HOUSTON
    distances[city_list[5] + " - " + city_list[10]] = 1;
    distances[city_list[10] + " - " + city_list[5]] = 1;
    // ATLANTA - NASHVILLE
    distances[city_list[0] + " - " + city_list[17]] = 1;
    distances[city_list[17] + " - " + city_list[0]] = 1;
    
    
    // ****************** LENGTH 2 ******************   25
    // LOS_ANGELES - LAS_VEGAS
    distances[city_list[14] + " - " + city_list[12]] = 2;
    distances[city_list[12] + " - " + city_list[14]] = 2;
    // DENVER - SANTA_FE
    distances[city_list[6] + " - " + city_list[29]] = 2;
    distances[city_list[29] + " - " + city_list[6]] = 2;
    // SANTA_FE - EL_PASO
    distances[city_list[29] + " - " + city_list[8]] = 2;
    distances[city_list[8] + " - " + city_list[29]] = 2;
    // DULUTH - OMAHA
    distances[city_list[7] + " - " + city_list[21]] = 2;
    distances[city_list[21] + " - " + city_list[7]] = 2;
    // KANSAS_CITY - OKLAHOMA_CITY
    distances[city_list[11] + " - " + city_list[20]] = 2;
    distances[city_list[20] + " - " + city_list[11]] = 2;
    // OKLAHOMA_CITY - DALLAS
    distances[city_list[20] + " - " + city_list[5]] = 2;
    distances[city_list[5] + " - " + city_list[20]] = 2;
    // KANSAS_CITY - SAINT_LOUIS
    distances[city_list[11] + " - " + city_list[26]] = 2;
    distances[city_list[26] + " - " + city_list[11]] = 2;
    // OKLAHOMA_CITY - LITTLE_ROCK
    distances[city_list[20] + " - " + city_list[13]] = 2;
    distances[city_list[13] + " - " + city_list[20]] = 2;
    // DALLAS - LITTLE_ROCK
    distances[city_list[5] + " - " + city_list[13]] = 2;
    distances[city_list[13] + " - " + city_list[5]] = 2;
    // SAINT_LOUIS - CHICAGO
    distances[city_list[26] + " - " + city_list[4]] = 2;
    distances[city_list[4] + " - " + city_list[26]] = 2;
    // SAINT_LOUIS - LITTLE_ROCK
    distances[city_list[26] + " - " + city_list[13]] = 2;
    distances[city_list[13] + " - " + city_list[26]] = 2;
    // SAINT_LOUIS - NASHVILLE
    distances[city_list[26] + " - " + city_list[17]] = 2;
    distances[city_list[17] + " - " + city_list[26]] = 2;
    // HOUSTON - NEW_ORLEANS
    distances[city_list[10] + " - " + city_list[18]] = 2;
    distances[city_list[18] + " - " + city_list[10]] = 2;
    // SAULT-ST._MARIE - TORONTO
    distances[city_list[30] + " - " + city_list[32]] = 2;
    distances[city_list[32] + " - " + city_list[30]] = 2;
    // TORONTO - PITTSBURGH
    distances[city_list[32] + " - " + city_list[23]] = 2;
    distances[city_list[23] + " - " + city_list[32]] = 2;
    // PITTSBURGH - NEW_YORK
    distances[city_list[23] + " - " + city_list[19]] = 2;
    distances[city_list[19] + " - " + city_list[23]] = 2;
    // PITTSBURGH - WASHINGTON
    distances[city_list[23] + " - " + city_list[34]] = 2;
    distances[city_list[34] + " - " + city_list[23]] = 2;
    // PITTSBURGH - RALEIGH
    distances[city_list[23] + " - " + city_list[25]] = 2;
    distances[city_list[25] + " - " + city_list[23]] = 2;
    // RALEIGH - WASHINGTON
    distances[city_list[25] + " - " + city_list[34]] = 2;
    distances[city_list[34] + " - " + city_list[25]] = 2;
    // RALEIGH - ATLANTA
    distances[city_list[25] + " - " + city_list[0]] = 2;
    distances[city_list[0] + " - " + city_list[25]] = 2;
    // RALEIGH - CHARLESTON
    distances[city_list[25] + " - " + city_list[3]] = 2;
    distances[city_list[3] + " - " + city_list[25]] = 2;
    // CHARLESTON - ATLANTA
    distances[city_list[3] + " - " + city_list[0]] = 2;
    distances[city_list[0] + " - " + city_list[3]] = 2;
    // WASHINGTON - NEW_YORK
    distances[city_list[34] + " - " + city_list[19]] = 2;
    distances[city_list[19] + " - " + city_list[34]] = 2;
    // BOSTON - NEW_YORK
    distances[city_list[1] + " - " + city_list[19]] = 2;
    distances[city_list[19] + " - " + city_list[1]] = 2;
    // BOSTON - MONTREAL
    distances[city_list[1] + " - " + city_list[16]] = 2;
    distances[city_list[16] + " - " + city_list[1]] = 2;
    
    
    // ****************** LENGTH 3 ******************   17
    // VANCOUVER - CALGARY
    distances[city_list[33] + " - " + city_list[2]] = 3;
    distances[city_list[2] + " - " + city_list[33]] = 3;
    // SALT_LAKE_CITY - HELENA
    distances[city_list[27] + " - " + city_list[9]] = 3;
    distances[city_list[9] + " - " + city_list[27]] = 3;
    // SALT_LAKE_CITY - DENVER
    distances[city_list[27] + " - " + city_list[6]] = 3;
    distances[city_list[6] + " - " + city_list[27]] = 3;
    // SALT_LAKE_CITY - LAS_VEGAS
    distances[city_list[27] + " - " + city_list[12]] = 3;
    distances[city_list[12] + " - " + city_list[27]] = 3;
    // SAN_FRANCISCO - LOS_ANGELES
    distances[city_list[28] + " - " + city_list[14]] = 3;
    distances[city_list[14] + " - " + city_list[28]] = 3;
    // PHOENIX - LOS_ANGELES
    distances[city_list[22] + " - " + city_list[14]] = 3;
    distances[city_list[14] + " - " + city_list[22]] = 3;
    // PHOENIX - SANTA_FE
    distances[city_list[22] + " - " + city_list[29]] = 3;
    distances[city_list[29] + " - " + city_list[22]] = 3;
    // PHOENIX - EL_PASO
    distances[city_list[22] + " - " + city_list[8]] = 3;
    distances[city_list[8] + " - " + city_list[22]] = 3;
    // SANTA_FE - OKLAHOMA_CITY
    distances[city_list[29] + " - " + city_list[20]] = 3;
    distances[city_list[20] + " - " + city_list[29]] = 3;
    // DULUTH - SAULT_ST._MARIE
    distances[city_list[7] + " - " + city_list[30]] = 3;
    distances[city_list[30] + " - " + city_list[7]] = 3;
    // DULUTH - CHICAGO
    distances[city_list[7] + " - " + city_list[4]] = 3;
    distances[city_list[4] + " - " + city_list[7]] = 3;
    // LITTLE_ROCK - NASHVILLE
    distances[city_list[13] + " - " + city_list[17]] = 3;
    distances[city_list[17] + " - " + city_list[13]] = 3;
    // LITTLE_ROCK - NEW_ORLEANS
    distances[city_list[13] + " - " + city_list[18]] = 3;
    distances[city_list[18] + " - " + city_list[13]] = 3;
    // NASHVILLE - RALEIGH
    distances[city_list[17] + " - " + city_list[25]] = 3;
    distances[city_list[25] + " - " + city_list[17]] = 3;
    // CHICAGO - PITTSBURGH
    distances[city_list[4] + " - " + city_list[23]] = 3;
    distances[city_list[23] + " - " + city_list[4]] = 3;
    // MONTREAL - TORONTO
    distances[city_list[16] + " - " + city_list[32]] = 3;
    distances[city_list[32] + " - " + city_list[16]] = 3;
    // MONTREAL - NEW_YORK
    distances[city_list[16] + " - " + city_list[19]] = 3;
    distances[city_list[19] + " - " + city_list[16]] = 3;
    
    
    // ****************** LENGTH 4 ******************   14
    // CALGARY - SEATTLE
    distances[city_list[2] + " - " + city_list[31]] = 4;
    distances[city_list[31] + " - " + city_list[2]] = 4;
    // CALGARY - HELENA
    distances[city_list[2] + " - " + city_list[9]] = 4;
    distances[city_list[9] + " - " + city_list[2]] = 4;
    // WINNIPEG - HELENA
    distances[city_list[35] + " - " + city_list[9]] = 4;
    distances[city_list[9] + " - " + city_list[35]] = 4;
    // WINNIPEG - DULUTH
    distances[city_list[35] + " - " + city_list[7]] = 4;
    distances[city_list[7] + " - " + city_list[35]] = 4;
    // DENVER - HELENA
    distances[city_list[6] + " - " + city_list[9]] = 4;
    distances[city_list[9] + " - " + city_list[6]] = 4;
    // DENVER - OMAHA
    distances[city_list[6] + " - " + city_list[21]] = 4;
    distances[city_list[21] + " - " + city_list[6]] = 4;
    // DENVER - KANSAS_CITY
    distances[city_list[6] + " - " + city_list[11]] = 4;
    distances[city_list[11] + " - " + city_list[6]] = 4;
    // DENVER - OKLAHOMA_CITY
    distances[city_list[6] + " - " + city_list[20]] = 4;
    distances[city_list[20] + " - " + city_list[6]] = 4;
    // EL_PASO - DALLAS
    distances[city_list[8] + " - " + city_list[5]] = 4;
    distances[city_list[5] + " - " + city_list[8]] = 4;
    // CHICAGO - OMAHA
    distances[city_list[4] + " - " + city_list[21]] = 4;
    distances[city_list[21] + " - " + city_list[4]] = 4;
    // CHICAGO - TORONTO
    distances[city_list[4] + " - " + city_list[32]] = 4;
    distances[city_list[32] + " - " + city_list[4]] = 4;
    // NASHVILLE - PITTSBURGH
    distances[city_list[17] + " - " + city_list[23]] = 4;
    distances[city_list[23] + " - " + city_list[17]] = 4;
    // NEW_ORLEANS - ATLANTA
    distances[city_list[18] + " - " + city_list[0]] = 4;
    distances[city_list[0] + " - " + city_list[18]] = 4;
    // CHARLESTON - MIAMI
    distances[city_list[3] + " - " + city_list[15]] = 4;
    distances[city_list[15] + " - " + city_list[3]] = 4;
    
    
    // ****************** LENGTH 5 ******************   8
    // SAN_FRANCISCO - PORTLAND
    distances[city_list[28] + " - " + city_list[24]] = 5;
    distances[city_list[24] + " - " + city_list[28]] = 5;
    // SAN_FRANCISCO - SALT_LAKE_CITY
    distances[city_list[28] + " - " + city_list[27]] = 5;
    distances[city_list[27] + " - " + city_list[28]] = 5;
    // PHOENIX - DENVER
    distances[city_list[22] + " - " + city_list[6]] = 5;
    distances[city_list[6] + " - " + city_list[22]] = 5;
    // HELENA - OMAHA
    distances[city_list[9] + " - " + city_list[21]] = 5;
    distances[city_list[21] + " - " + city_list[9]] = 5;
    // EL_PASO - OKLAHOMA_CITY
    distances[city_list[8] + " - " + city_list[20]] = 5;
    distances[city_list[20] + " - " + city_list[8]] = 5;
    // SAULT_ST._MARIE - MONTREAL
    distances[city_list[30] + " - " + city_list[16]] = 5;
    distances[city_list[16] + " - " + city_list[30]] = 5;
    // SAINT_LOUIS - PITTSBURGH
    distances[city_list[26] + " - " + city_list[23]] = 5;
    distances[city_list[23] + " - " + city_list[26]] = 5;
    // ATLANTA - MIAMI
    distances[city_list[0] + " - " + city_list[15]] = 5;
    distances[city_list[15] + " - " + city_list[0]] = 5;
    
    
    // ****************** LENGTH 6 ******************   9
    // WINNIPEG - CALGARY
    distances[city_list[35] + " - " + city_list[2]] = 6;
    distances[city_list[2] + " - " + city_list[35]] = 6;
    // WINNIPEG - SAULT_ST._MARIE
    distances[city_list[35] + " - " + city_list[30]] = 6;
    distances[city_list[30] + " - " + city_list[35]] = 6;
    // HELENA - SEATTLE
    distances[city_list[9] + " - " + city_list[31]] = 6;
    distances[city_list[31] + " - " + city_list[9]] = 6;
    // HELENA - DULUTH
    distances[city_list[9] + " - " + city_list[7]] = 6;
    distances[city_list[7] + " - " + city_list[9]] = 6;
    // DULUTH - TORONTO
    distances[city_list[7] + " - " + city_list[32]] = 6;
    distances[city_list[32] + " - " + city_list[7]] = 6;
    // PORTLAND - SALT_LAKE_CITY
    distances[city_list[24] + " - " + city_list[27]] = 6;
    distances[city_list[27] + " - " + city_list[24]] = 6;
    // EL_PASO - LOS_ANGELES
    distances[city_list[8] + " - " + city_list[14]] = 6;
    distances[city_list[14] + " - " + city_list[8]] = 6;
    // EL_PASO - HOUSTON
    distances[city_list[8] + " - " + city_list[10]] = 6;
    distances[city_list[10] + " - " + city_list[8]] = 6;
    // NEW_ORLEANS - MIAMI
    distances[city_list[18] + " - " + city_list[15]] = 6;
    distances[city_list[15] + " - " + city_list[18]] = 6;
}

// initiates cities and their neighbours
void init_cities() {
    for (int i = 0; i < city_size; i++) {
        c[i] = new City(i);
    }
    
    // ******************** NEIGHBOURS ********************
    // 0 ATLANTA
    c[0]->neighbours.push_back(c[3]);   // CHARLESTON
    c[0]->neighbours.push_back(c[15]);  // MIAMI
    c[0]->neighbours.push_back(c[17]);  // NASHVILLE
    c[0]->neighbours.push_back(c[18]);  // NEW_ORLEANS
    c[0]->neighbours.push_back(c[25]);  // RALEIGH
    
    // 1 BOSTON
    c[1]->neighbours.push_back(c[16]);  // MONTREAL
    c[1]->neighbours.push_back(c[19]);  // NEW_YORK
    
    // 2 CALGARY
    c[2]->neighbours.push_back(c[9]);   // HELENA
    c[2]->neighbours.push_back(c[31]);  // SEATTLE
    c[2]->neighbours.push_back(c[33]);  // VANCOUVER
    c[2]->neighbours.push_back(c[35]);  // WINNIPEG
    
    // 3 CHARLESTON
    c[3]->neighbours.push_back(c[0]);   // ATLANTA
    c[3]->neighbours.push_back(c[15]);  // MIAMI
    c[3]->neighbours.push_back(c[25]);  // RALEIGH
    
    // 4 CHICAGO
    c[4]->neighbours.push_back(c[7]);   // DULUTH
    c[4]->neighbours.push_back(c[21]);  // OMAHA
    c[4]->neighbours.push_back(c[23]);  // PITTSBURGH
    c[4]->neighbours.push_back(c[26]);  // SAINT_LOUIS
    c[4]->neighbours.push_back(c[32]);  // TORONTO
    
    // 5 DALLAS
    c[5]->neighbours.push_back(c[8]);   // EL_PASO
    c[5]->neighbours.push_back(c[10]);  // HOUSTON
    c[5]->neighbours.push_back(c[13]);  // LITTLE_ROCK
    c[5]->neighbours.push_back(c[20]);  // OKLAHOMA_CITY
    
    // 6 DENVER
    c[6]->neighbours.push_back(c[9]);   // HELENA
    c[6]->neighbours.push_back(c[11]);  // KANSAS_CITY
    c[6]->neighbours.push_back(c[20]);  // OKLAHOMA_CITY
    c[6]->neighbours.push_back(c[21]);  // OMAHA
    c[6]->neighbours.push_back(c[22]);  // PHOENIX
    c[6]->neighbours.push_back(c[27]);  // SALT_LAKE_CITY
    c[6]->neighbours.push_back(c[29]);  // SANTE_FE
    
    // 7 DULUTH
    c[7]->neighbours.push_back(c[4]);   // CHICAGO
    c[7]->neighbours.push_back(c[9]);   // HELENA
    c[7]->neighbours.push_back(c[21]);  // OMAHA
    c[7]->neighbours.push_back(c[30]);  // SAULT_ST._MARIE
    c[7]->neighbours.push_back(c[32]);  // TORONTO
    c[7]->neighbours.push_back(c[35]);  // WINNIPEG
    
    // 8 EL_PASO
    c[8]->neighbours.push_back(c[5]);   // DALLAS
    c[8]->neighbours.push_back(c[10]);  // HOUSTON
    c[8]->neighbours.push_back(c[14]);  // LOS_ANGELES
    c[8]->neighbours.push_back(c[20]);  // OKLAHOMA_CITY
    c[8]->neighbours.push_back(c[22]);  // PHOENIX
    c[8]->neighbours.push_back(c[29]);  // SANTA_FE
    
    // 9 HELENA
    c[9]->neighbours.push_back(c[2]);   // CALGARY
    c[9]->neighbours.push_back(c[6]);   // DENVER
    c[9]->neighbours.push_back(c[7]);   // DULUTH
    c[9]->neighbours.push_back(c[21]);  // OMAHA
    c[9]->neighbours.push_back(c[27]);  // SALT_LAKE_CITY
    c[9]->neighbours.push_back(c[31]);  // SEATTLE
    c[9]->neighbours.push_back(c[35]);  // WINNIPEG
    
    // 10 HOUSTON
    c[10]->neighbours.push_back(c[5]);  // DALLAS
    c[10]->neighbours.push_back(c[8]);  // EL_PASO
    c[10]->neighbours.push_back(c[18]); // NEW_ORLEANS
    
    // 11 KANSAS_CITY
    c[11]->neighbours.push_back(c[6]);  // DENVER
    c[11]->neighbours.push_back(c[20]); // OKLAHOMA_CITY
    c[11]->neighbours.push_back(c[21]); // OMAHA
    c[11]->neighbours.push_back(c[26]); // SAINT_LOUIS
    
    // 12 LAS_VEGAS
    c[12]->neighbours.push_back(c[14]); // LOS_ANGELES
    c[12]->neighbours.push_back(c[27]); // SALT_LAKE_CITY
    
    // 13 LITTLE_ROCK
    c[13]->neighbours.push_back(c[5]);  // DALLAS
    c[13]->neighbours.push_back(c[17]); // NASHVILLE
    c[13]->neighbours.push_back(c[18]); // NEW_ORLEANS
    c[13]->neighbours.push_back(c[20]); // OKLAHOMA_CITY
    c[13]->neighbours.push_back(c[26]); // SAINT_LOUIS
    
    // 14 LOS_ANGELES
    c[14]->neighbours.push_back(c[8]);  // EL_PASO
    c[14]->neighbours.push_back(c[12]); // LAS_VEGAS
    c[14]->neighbours.push_back(c[22]); // PHOENIX
    c[14]->neighbours.push_back(c[28]); // SAN_FRANCISCO
    
    // 15 MIAMI
    c[15]->neighbours.push_back(c[0]);  // ATLANTA
    c[15]->neighbours.push_back(c[3]);  // CHARLESTON
    c[15]->neighbours.push_back(c[18]); // NEW_ORLEANS
    
    // 16 MONTREAL
    c[16]->neighbours.push_back(c[1]);  // BOSTON
    c[16]->neighbours.push_back(c[19]); // NEW_YORK
    c[16]->neighbours.push_back(c[30]); // SAULT_ST._MARIE
    c[16]->neighbours.push_back(c[32]); // TORONTO
    
    // 17 NASHVILLE
    c[17]->neighbours.push_back(c[0]);  // ATLANTA
    c[17]->neighbours.push_back(c[13]); // LITTLE_ROCK
    c[17]->neighbours.push_back(c[23]); // PITTSBURGH
    c[17]->neighbours.push_back(c[25]); // RALEIGH
    c[17]->neighbours.push_back(c[26]); // SAINT_LOUIS
    
    // 18 NEW_ORLEANS
    c[18]->neighbours.push_back(c[0]);  // ATLANTA
    c[18]->neighbours.push_back(c[10]); // HOUSTON
    c[18]->neighbours.push_back(c[13]); // LITTLE_ROCK
    c[18]->neighbours.push_back(c[15]); // MIAMI
    
    // 19 NEW_YORK
    c[19]->neighbours.push_back(c[1]);  // BOSTON
    c[19]->neighbours.push_back(c[16]); // MONTREAL
    c[19]->neighbours.push_back(c[23]); // PITTSBURGH
    c[19]->neighbours.push_back(c[34]); // WASHINGTON
    
    // 20 OKLAHOMA_CITY
    c[20]->neighbours.push_back(c[5]);  // DALLAS
    c[20]->neighbours.push_back(c[6]);  // DENVER
    c[20]->neighbours.push_back(c[8]);  // EL_PASO
    c[20]->neighbours.push_back(c[11]); // KANSAS_CITY
    c[20]->neighbours.push_back(c[13]); // LITTLE_ROCK
    c[20]->neighbours.push_back(c[29]); // SANTA_FE
    
    // 21 OMAHA
    c[21]->neighbours.push_back(c[4]);  // CHICAGO
    c[21]->neighbours.push_back(c[6]);  // DENVER
    c[21]->neighbours.push_back(c[7]);  // DULUTH
    c[21]->neighbours.push_back(c[9]);  // HELENA
    c[21]->neighbours.push_back(c[11]); // KANSAS_CITY

    // 22 PHOENIX
    c[22]->neighbours.push_back(c[6]);  // DENVER
    c[22]->neighbours.push_back(c[8]);  // EL_PASO
    c[22]->neighbours.push_back(c[14]); // LOS_ANGELES
    c[22]->neighbours.push_back(c[29]); // SANTA_FE
    
    // 23 PITTSBURGH
    c[23]->neighbours.push_back(c[4]);  // CHICAGO
    c[23]->neighbours.push_back(c[17]); // NASHVILLE
    c[23]->neighbours.push_back(c[19]); // NEW_YORK
    c[23]->neighbours.push_back(c[25]); // RALEIGH
    c[23]->neighbours.push_back(c[26]); // SAINT_LOUIS
    c[23]->neighbours.push_back(c[32]); // TORONTO
    c[23]->neighbours.push_back(c[34]); // WASHINGTON
    
    // 24 PORTLAND
    c[24]->neighbours.push_back(c[27]); // SALT_LAKE_CITY
    c[24]->neighbours.push_back(c[28]); // SAN_FRANCISCO
    c[24]->neighbours.push_back(c[31]); // SEATTLE
    
    // 25 RALEIGH
    c[25]->neighbours.push_back(c[0]);  // ATLANTA
    c[25]->neighbours.push_back(c[3]);  // CHARLESTON
    c[25]->neighbours.push_back(c[17]); // NASHVILLE
    c[25]->neighbours.push_back(c[23]); // PITTSBURGH
    c[25]->neighbours.push_back(c[34]); // WASHINGTON
    
    // 26 SAINT_LOUIS
    c[26]->neighbours.push_back(c[4]);  // CHICAGO
    c[26]->neighbours.push_back(c[11]); // KANSAS_CITY
    c[26]->neighbours.push_back(c[13]); // LITTLE_ROCK
    c[26]->neighbours.push_back(c[17]); // NASHVILLE
    c[26]->neighbours.push_back(c[23]); // PITTSBURGH
    
    // 27 SALT_LAKE_CITY
    c[27]->neighbours.push_back(c[6]);  // DENVER
    c[27]->neighbours.push_back(c[9]);  // HELENA
    c[27]->neighbours.push_back(c[12]); // LAS_VEGAS
    c[27]->neighbours.push_back(c[24]); // PORTLAND
    c[27]->neighbours.push_back(c[28]); // SAN_FRANCISCO
    
    // 28 SAN_FRANCISCO
    c[28]->neighbours.push_back(c[14]); // LOS_ANGELES
    c[28]->neighbours.push_back(c[24]); // PORTLAND
    c[28]->neighbours.push_back(c[27]); // SALT_LAKE_CITY
    
    // 29 SANTA_FE
    c[29]->neighbours.push_back(c[6]);  // DENVER
    c[29]->neighbours.push_back(c[8]);  // EL_PASO
    c[29]->neighbours.push_back(c[20]); // OKLAHOMA_CITY
    c[29]->neighbours.push_back(c[22]); // PHOENIX
    
    // 30 SAULT_ST._MARIE
    c[30]->neighbours.push_back(c[7]);  // DULUTH
    c[30]->neighbours.push_back(c[16]); // MONTREAL
    c[30]->neighbours.push_back(c[32]); // TORONTO
    c[30]->neighbours.push_back(c[35]); // WINNIPEG
    
    // 31 SEATTLE
    c[31]->neighbours.push_back(c[2]);  // CALGARY
    c[31]->neighbours.push_back(c[9]);  // HELENA
    c[31]->neighbours.push_back(c[24]); // PORTLAND
    c[31]->neighbours.push_back(c[33]); // VANCOUVER
    
    // 32 TORONTO
    c[32]->neighbours.push_back(c[4]);  // CHICAGO
    c[32]->neighbours.push_back(c[7]);  // DULUTH
    c[32]->neighbours.push_back(c[16]); // MONTREAL
    c[32]->neighbours.push_back(c[23]); // PITTSBURGH
    c[32]->neighbours.push_back(c[30]); // SAULT_ST._MARIE
    
    // 33 VANCOUVER
    c[33]->neighbours.push_back(c[2]);  // CALGARY
    c[33]->neighbours.push_back(c[31]); // SEATTLE
    
    // 34 WASHINGTON
    c[34]->neighbours.push_back(c[19]); // NEW_YORK
    c[34]->neighbours.push_back(c[23]); // PITTSBURGH
    c[34]->neighbours.push_back(c[25]); // RALEIGH
    
    // 35 WINNIPEG
    c[35]->neighbours.push_back(c[2]);  // CALGARY
    c[35]->neighbours.push_back(c[7]);  // DULUTH
    c[35]->neighbours.push_back(c[9]);  // HELENA
    c[35]->neighbours.push_back(c[30]); // SAULT_ST._MARIE
}

// resets shortest and visited
void reset() {  // O(city_size);
    for (int i = 0; i < city_size; i++) {
        c[i]->visited = false;
        c[i]->shortest = 2147483647;
    }
}

// finds next city to visit with lowest tentative distance
int find_next_city() {  // O(city_size)
    City *c_min = NULL;
    int min = 2147483647;
    
    for (int i = 0; i < city_size; i++) {
        if (!c[i]->visited && c[i]->shortest < min) {
            c_min = c[i];
            min = c[i]->shortest;
        }
    }
    
    if (c_min == NULL)  cout << "No more neighbours" << endl;
    return c_min->city_num;
}

// uses Dijkstra's algorithm to find shortest path from 1 city to another
int find_shortest(int cur, int destination) {   // O(city_size * (|E| + |V| log|V|)):   E = 78, V = 36
    // arrived
    if (cur == destination) {
        if (c[cur]->length > 1) long_enough = true;
        return c[cur]->shortest;
    }
    
    City *cur_city = c[cur];
    
    // consider each unvisited neighbour
    for (vector<City*>::const_iterator it = cur_city->neighbours.begin(); it != cur_city->neighbours.end(); it++) {
        City *n = *it;
        
        // haven't visited city
        if (!n->visited) {
            int new_shortest1 = cur_city->shortest + distances[cur_city->name + " - " + n->name];
            int new_shortest2 = cur_city->shortest + distances[n->name + " - " + cur_city->name];
            // safety
            if (new_shortest1 != new_shortest2) cout << "FAIL DISTANCES: " << cur_city->name << " and " << n->name << endl;
            
            // found new shortest path to that city
            if (new_shortest1 < n->shortest) {
                n->shortest = new_shortest1;
                n->length = cur_city->length + 1;
            }
        }
    }
    
    // we have finished visiting this city
    cur_city->visited = true;
    
    // visit next city
    int next = find_next_city();
    return find_shortest(next, destination);
}

// ********************** THRESHOLDS *********************
// SHORT    (threshold1 <= x < threshold2)      4 to 7
// MEDIUM   (threshold2 <= x < threshold3)      8 to 14
// LONG     (threshold3 <= x)                   15 to 23
const int threshold1 = 4;
const int threshold2 = 8;
const int threshold3 = 15;

// finds thresholds
void find_threshold() {
    int max = 0;
    int min = 2147483647;
    
    for (int i = 0; i < city_size - 1; i++) {
        for (int j = i + 1; j < city_size; j++) {
            long_enough = false;
            
            // i to j
            reset();
            c[i]->shortest = 0;
            c[i]->length = 0;
            int distance1 = find_shortest(i, j);
            cout << c[i]->name << " to " << c[j]->name << ":  " << distance1 << endl;
            
            // j to i
            reset();
            c[j]->shortest = 0;
            c[j]->length = 0;
            int distance2 = find_shortest(j, i);
            cout << c[j]->name << " to " << c[i]->name << ":  " << distance2 << endl;
            
            // safety
            if (distance1 != distance2)     cout << "FAILED" << endl;
            if (distance1 > max)    max = distance1;
            if (distance1 < min)    min = distance1;
            
            if (long_enough)    cout << distance1 << endl;
        }
    }
    cout << "MAX: " << max << endl;
    cout << "MIN: " << min << endl;
}

// generates a route with low <= shortest distance < high
// length of route must be > 1
string generate(int low, int high) {
    int src, dst, distance;
    distance = -1;
    
    while (distance < low || high <= distance) {
        src = rand() % city_size;
        dst = rand() % city_size;
        long_enough = false;
        
        reset();
        c[src]->shortest = 0;
        c[src]->length = 0;
        distance = find_shortest(src, dst);
        
        // if length == 1
        if (!long_enough)   distance = -1;
    }
    
    string s = to_string(distance) + " ";
    if (distance < 10)  s += " ";
    s += c[src]->name + " to " + c[dst]->name;
    return s;
}

string players;     // # of players

// initiates game
void init_game() {    
    string short_roads, medium_roads, long_roads;
    
    // # players
    cout << "Enter # of players:                    ";
    getline(cin, players);

    // # short roads
    cout << "Enter # short roads (length 4 to 7):   ";
    getline(cin, short_roads);
    
    // # medium roads
    cout << "Enter # medium roads (length 8 to 14): ";
    getline(cin, medium_roads);
    
    // # long roads
    cout << "Enter # long roads (length 15 to 23):  ";
    getline(cin, long_roads);
    
    // for each player
    for (int p = 1; p <= atoi(players.c_str()); p++) {
        string name;
        cout << "Enter name of Player " << p << ":  ";
        getline(cin, name);
        
        ofstream player(name + ".txt");
        player << name << endl;
        
        // short roads
        for (int s = 1; s <= atoi(short_roads.c_str()); s++) {
            player << "  Short Road " << s << ":   ";
            player << generate(threshold1, threshold2) << endl;
        }
        // medium roads
        for (int m = 1; m <= atoi(medium_roads.c_str()); m++) {
            player << "  Medium Road " << m << ":  ";
            player << generate(threshold2, threshold3) << endl;
        }
        // long roads
        for (int l = 1; l <= atoi(long_roads.c_str()); l++) {
            player << "  Long Road " << l << ":    ";
            player << generate(threshold3, 24) << endl;
        }
        player.close();
    }
}

// allow teams
void teammates() {
    int t1, t2, teams_num;
    string teams, team_size, roads, num;
    
    cout << endl << "TEAM OBJECTIVES" << endl;
    cout << "Enter \"y\" or \"n\" if teams:  ";
    getline(cin, teams);
    
    // no teams
    if (teams == "n")   cout << "NO TEAMS" << endl;
    // teams
    else if (teams == "y") {
        cout << "How many per team:  ";
        getline(cin, team_size);
        
        if (atoi(players.c_str()) % atoi(team_size.c_str()) == 1) {
            cout << "TEAM NUMBER FAIL" << endl;
            return;
        }
        
        teams_num = atoi(players.c_str()) / atoi(team_size.c_str());
        
        // type of roads
        cout << "What type of roads (0 - short, 1 - medium, 2 - long, 3 - any):  ";
        getline(cin, roads);
        
        // ************ THRESHOLDS ************
        // all short
        if (roads == "0") {
            t1 = threshold1;
            t2 = threshold2;
        }
        // all medium
        else if (roads == "1") {
            t1 = threshold2;
            t2 = threshold3;
        }
        // all long
        else if (roads == "2") {
            t1 = threshold3;
            t2 = 24;
        }
        // any
        else {
            t1 = threshold1;
            t2 = 24;
        }
        
        // # of roads
        cout << "How many shared objectives:  ";
        getline(cin, num);
        
        // for each team
        for (int t = 1; t <= teams_num; t++) {
            ofstream team("Team_" + to_string(t) + ".txt");
            team << "Team " << to_string(t) << " Shared Objectives" << endl;
            
            for (int i = 1; i <= atoi(num.c_str()); i++) {
                team << "  " << generate(t1, t2) << endl;
            }
            team.close();
        }
    }
    // fail answer
    else    cout << "TEAMS FAIL" << endl;
}

// allow monsters
void monsters() {
    string answer;
    
    cout << endl << "Enter \"y\" or \"n\" for monsters:  ";
    getline(cin, answer);
    
    // no monsters
    if (answer == "n")  cout << "NO MONSTERS" << endl;
    // monsters
    else if (answer == "y") {
        string line;
        cout << "How many monsters (1 - 36 monsters):  ";
        getline(cin, line);
        map<string, bool> city;     // where monsters are initialized
        
        int num = atoi(line.c_str());       // # of monsters
        // no monsters
        if (num == 0) {
            cout << "NO MONSTERS" << endl;
            return;
        }
        // invalid monster #
        else if (num < 0 || num > 36) {
            cout << "MONSTER NUMBER FAIL" << endl;
            return;
        }
        // monsters
        cout << "Monsters are initialized at:" << endl;
        while (num > 0) {
            int next = rand() % city_size;
            string c = city_list[next];
            
            // found a city
            if (!city[c]) {
                city[c] = true;
                num--;
                cout << c << endl;
            }
        }
    }
    // fail answer
    else    cout << "MONSTERS FAIL" << endl;
}

// player picks more objectives
void more_objectives() {
    string player, roads, num;
    int t1, t2;     // thresholds
    int x = 0;      // extension #
    
    cout << endl << "EXTENSION TO GET MORE OBJECTIVES";
    
    while(true) {
        cout << endl;
        x++;
        
        // player
        cout << "Enter name of player that wants more objectives or \"q\" to quit:  ";
        getline(cin, player);
        
        // quit
        if (player == "q")  break;
        
        // type of roads
        cout << "What type of roads (0 - short, 1 - medium, 2 - long, 3 - any):  ";
        getline(cin, roads);
        
        // ************ THRESHOLDS ************
        // all short
        if (roads == "0") {
            t1 = threshold1;
            t2 = threshold2;
        }
        // all medium
        else if (roads == "1") {
            t1 = threshold2;
            t2 = threshold3;
        }
        // all long
        else if (roads == "2") {
            t1 = threshold3;
            t2 = 24;
        }
        // any
        else {
            t1 = threshold1;
            t2 = 24;
        }
        
        // # of roads
        cout << "How many more objectives:  ";
        getline(cin, num);
        
        ofstream extend("extend" + to_string(x) + "_" + player + ".txt");
        extend << player << " More Objectives" << endl;
        
        for (int i = 1; i <= atoi(num.c_str()); i++) {
            extend << "  " << generate(t1, t2) << endl;
        }
        extend.close();
    }
    cout << "Game Finished" << endl;
}

int main() {
    srand(time(NULL));
    
    init_distances();
    init_cities();
    // find_threshold();
    init_game();
    
    // extensions
    teammates();
    monsters();
    more_objectives();
    
    // remove all text files created
    system("exec rm ./*.txt");
    
    return 0;
}