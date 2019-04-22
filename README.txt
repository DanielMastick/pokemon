To compile pokemon.exe run the command:
g++ -std=c++11 -o pokemon pokemon_driver.cpp TypeGraph.cpp Team.cpp Pokedex.cpp MoveList.cpp

Dependencies:
TypeGraph.hpp  TypeGraph.cpp
Team.hpp       Team.cpp
Pokedex.hpp    Pokedex.cpp
Movelist.hpp   MoveList.cpp

Required files:
pokemon_moves_attack_only.csv
pokemon_data.csv
type_matchup.csv


See code comments for description of code functionality