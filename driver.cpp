#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct Move{
  Move* next;
  string name;
  string type;
  // string status;
  string cat;
  int pow;
  int acc;
  int pp;
  // string duration;
};

struct moveTable {
    Move** hashTable = nullptr;
    int hashTableSize;
    int numItems;
};

struct Pokemon{
    // Poninters
    Pokemon* parent;
    Pokemon* leftChild;
    Pokemon* rightChild;
    // Data
    int dexNum; //1-151
    string name; //pokemon name
    string type; //grass/fire/ect
    int hp; //hit points
    int atk; //attack
    int def; //defense
    int spd; //speed
    int spc; //special
    Move m1;
    Move m2;
    Move m3;
    Move m4;
};

struct team{
  Pokemon* mon;
  team* next;
};


void menu(){
  cout << "============Main Menu============" << endl;
  cout << "1. Add Pokemon" << endl;
  cout << "2. Print Pokemon List" << endl;
  cout << "3. Print Move List" << endl;
  cout << "4. Battle" << endl;
  cout << "5. Quit" << endl;
}

Pokemon* addMon(Pokemon* root, int dexNum, string name, string type, int hp, int atk, int def,int spd,int spc, moveTable mt,Move move1,Move move2,Move move3,Move move4){
  Pokemon* node = new Pokemon;
  node->dexNum = dexNum;
  node->name = name;
  node->type = type;
  node->hp = hp;
  node->atk = atk;
  node->def = def;
  node->spd = spd;
  node->spc = spc;
  node->leftChild = nullptr;
  node->rightChild = nullptr;
  node->m1 = move1;
  node->m2 = move2;
  node->m3 = move3;
  node->m4 = move4;

  if (root == nullptr) {
    root = node;
  }
  else{
    int check = 0;
    Pokemon* traverse = root;

    while (check == 0) {

        //if (traverse->leftChild != NULL && node->name.at(0)<traverse->name) {
        if (traverse->leftChild != NULL && node->name<traverse->name) {
          //title is earlier in alphabet and there is an entry
          traverse = traverse->leftChild;
        }
        else if (traverse->rightChild != NULL && node->name>traverse->name) {
          //title is later in alphabet and there is an entry
          traverse = traverse->rightChild;
        }
        else if (node->name<traverse->name) {
          //title is earlier and it is null
          traverse->leftChild = node;
          node->parent = traverse;
          check = 1;

        }
        else if (node->name>traverse->name) {
          //title is later and it is null
          traverse->rightChild = node;
          node->parent = traverse;
          check = 1;

        }
    }
    return root;
  }
}

Move getRandomMove(moveTable mt){
  int bin = rand() % 25;
  int exit = 0;
  while (exit != 1) {
    exit = rand() % 2;//random number to determine if the list is traversed
    Move temp = *mt.hashTable[bin];
    if (exit == 0 && temp.next != nullptr) {
      temp = *temp.next;
    }else{
      return temp;
    }
  }


}

Pokemon* loadPokemonFile(Pokemon* root,moveTable mt, string filename){
  string line;
  ifstream myfile(filename);

  if(myfile.is_open()){
    string skipline;
    getline(myfile,skipline);
    while (getline(myfile,line)) {
      stringstream ss;
      ss<<line;
      string dexNum,name,type,hp,atk,def,spd,spc,tot,avg;
      Move move1,move2,move3,move4;
      //go through comma seperated file
      getline(ss,dexNum,',');
      getline(ss,name,',');
      getline(ss,type,',');
      getline(ss,hp,',');
      getline(ss,atk,',');
      getline(ss,def,',');
      getline(ss,spd,',');
      getline(ss,spc,',');
      getline(ss,tot,',');
      getline(ss,avg,',');
      move1 = getRandomMove(mt);
      move2 = getRandomMove(mt);
      move3 = getRandomMove(mt);
      move4 = getRandomMove(mt);
      root = addMon(root,stoi(dexNum),name,type,stoi(hp),stoi(atk),stoi(def),stoi(spd),stoi(spc),mt,move1,move2,move3,move4);

      ss.clear();
    }
    myfile.close();
  }
  return root;
}

Pokemon* getMon(Pokemon* root, string name){
  if (root == nullptr) {
    return root;
  }
    Pokemon* traverse = root;
    int check = 0;
    while (check == 0) {
      if (traverse->leftChild != nullptr && name < traverse->name) {
        traverse = traverse->leftChild;
      }else if(traverse->rightChild != nullptr && name > traverse->name){
        traverse = traverse->rightChild;
      }else if(traverse->name == name){
        check = 0;
        return traverse;
      }else{
        return nullptr;
      }
    }
}

void printPokemonList(Pokemon* root){
  if (root == nullptr) return;
  printPokemonList(root->leftChild);
  cout<<root->dexNum<<"-"<<root->name<<" "<<root->type<<" hp:"<<root->hp;
  cout<<" atk:"<<root->atk<<" def:"<<root->def<<" spd:"<<root->spd<<" spc:"<<root->spc<<endl;
  printPokemonList(root->rightChild);

}

unsigned int getHash(moveTable mt, string word){
    int hashValue = 5381;
    int length = word.length();
    for (int i = 0; i < length; i++)
    {
        hashValue = ((hashValue << 5) + hashValue) + word[i];
    }
    hashValue %= mt.hashTableSize;
    return abs(hashValue);
}

moveTable addMove(moveTable mt,string nameIn,string typeIn,string catIn,int powIn,int accIn,int ppIn){
  unsigned int index = getHash(mt, nameIn);

  Move* newMove = new Move;
  newMove->next = nullptr;
  newMove->name = nameIn;
  newMove->type = typeIn;
  // newMove->string status;
  newMove->cat = catIn;
  newMove->pow = powIn;
  newMove->acc = accIn;
  newMove->pp= ppIn;
  // string duration;
  // Check that the hash value is not already used
  if (mt.hashTable[index] == nullptr)
  {// Add a new word as start of the list
      mt.hashTable[index] = newMove;
      mt.numItems++;
  }
  else
  {// Add the new word at the end of the list
      Move* temp = mt.hashTable[index];
      while (temp->next != nullptr){
          temp = temp->next;
      }
      temp->next = newMove;
      mt.numItems++;
  }
  return mt;
}

moveTable loadMoveFile(moveTable mt,string filename){
  string line;
  ifstream myfile(filename);

  if(myfile.is_open()){
    string skipline;
    getline(myfile,skipline);
    while (getline(myfile,line)) {
      stringstream ss;
      ss<<line;
      string name,type,cat,pow,acc,pp;
      //go through comma seperated file
      getline(ss,name,',');
      getline(ss,type,',');
      getline(ss,cat,',');
      getline(ss,pow,',');
      getline(ss,acc,',');
      getline(ss,pp,',');
      mt = addMove(mt,name,type,cat,stoi(pow),stoi(acc),stoi(pp));

      ss.clear();
    }
    myfile.close();
  }
  return mt;
}

void printMoveList(moveTable mt){
  for (size_t i = 0; i < mt.hashTableSize; i++) {
    cout << "bin #" << i << ": ";
    if (mt.hashTable[i] != nullptr) {
      Move* temp = mt.hashTable[i];
      while (temp->next != nullptr){
          cout << temp->name << "   ";
          temp = temp->next;
      }
      cout << temp->name;
    }
    cout <<endl;
  }
}

int typeIndex(string name){
  int index = 0;
  string types[18] = {"Normal","Fighting","Flying","Poison","Ground","Rock","Bug","Ghost","Steel","Fire","Water","Grass","Electric","Psychic","Ice","Dragon","Dark","Fairy"};
  for (int i = 0; i < 18; i++) {
    if (name == types[i]) {
      return i;
    }
  }
  return -1;
}

float* loadTypeMatchup(){
  float* typeChart = new float[324];
  int count = 0;

  string line;
  ifstream myfile("type_matchup.csv");

  if(myfile.is_open()){
    while (getline(myfile,line)) {
      stringstream ss;
      ss<<line;
      string val;
      //go through comma seperated file
      while (getline(ss,val,',')) {
        typeChart[count] = stof(val);
        // count+=sizeof(float);
        count++;
        ss.clear();
      }
    }
    myfile.close();
  }
  for (size_t i = 0; i < 18; i++) {
    cout << typeChart[i] << " ";
  }
  return typeChart;
}

float typeMatchup(float* typeChart, string typeAttMon, string typeAtt, string typeDef){
  int typeAttInd = typeIndex(typeAtt);
  int typeDefInd = typeIndex(typeDef);
  cout << typeAtt <<": "<< typeAttInd << " " << typeDef <<": "<< typeDefInd << endl;
  cout << "returning ind: " <<(18*typeAttInd)+typeDefInd << endl;
  float stab = 1;
  if (typeAttMon == typeAtt) {
    stab = 1.5;
  }
  return stab*typeChart[(18*typeAttInd)+typeDefInd];
}

team* makeTeam(Pokemon* root, int teamSize){
  int monCount = 0;
  string name;
  team* p1 = new team;
  while (monCount < teamSize) {
    cout << "Name of #"<< monCount <<" Mon: " <<endl;
    getline(cin,name);
    Pokemon* tempMon = getMon(root,name);

    if (tempMon != nullptr) {
      cout << "Adding "<< tempMon->name << endl;
      if (monCount == 0) {
        p1->mon = tempMon;
        p1->next = nullptr;
      }else{
        team* tempTeam = new team;
        tempTeam->mon = tempMon;
        tempTeam->next = nullptr;
        team* traverse = p1;
        while (traverse->next != nullptr) {
          traverse = traverse->next;
        }
        traverse->next = tempTeam;
      }
      monCount++;
    }else{
      cout << name <<" is not a Pokemon, check your spelling" << endl;
    }
  }
  return p1;
}

void battle(team* p1, team* p2){
  cout << "lets battle my dudes" << endl;
}

int main(int argc, char const *argv[]){
  if (argc > 1) {
    cout << "This program doesn't require any initial command line inupts" << endl;
    return -1;
  }
  Pokemon* root = new Pokemon;
  root = nullptr;
  moveTable mt;


  cout << "loading moves" << endl;
  mt.hashTableSize = 25;
  mt.hashTable = new Move* [mt.hashTableSize];
  for (int i = 0; i < mt.hashTableSize; i++)
  {
      mt.hashTable[i] = nullptr;
  }
  mt = loadMoveFile(mt,"pokemon_moves_attack_only.csv");
  cout << "finished loading moves" << "\n" << endl;

  cout << "loading pokemon" << endl;
  root = loadPokemonFile(root,mt,"pokemon_data.csv");
  cout << "finished loading pokemon"  << "\n"<< endl;

  cout << "loading types" << endl;
  float* typeChart = loadTypeMatchup();
  cout << "finished loading types"  << "\n"<< endl;
  // for (int i = 0; i < 10; i++) {
  //   cout << typeChart[i] << endl;
  // }
  // cout << endl;
  //
  float check = typeMatchup(typeChart,"Fighting","Fighting", "Normal");
  cout << "result: " << check << endl;
  check = typeMatchup(typeChart,"Flying","Fighting", "Normal");
  cout << "result: " << check << endl;


  int finish = 0;
  while (finish == 0) {
    menu();
    string input;
    getline(cin,input);
    int option = stoi(input);
    int newMonCount = 0;
    switch (option) {
      case 1:{
        int dexNum;
        string name,type,hp,atk,def,spd,spc,tot,avg;
        Move move1,move2,move3,move4;
        cout << "Adding Pokemon!" << endl;
        newMonCount++;
        dexNum = 151+newMonCount;
        cout << "What is the name of this Pokemon?" << endl;
        getline(cin,name);
        cout << "What is this Pokemon's type?" << endl;
        getline(cin,type);
        int check = typeIndex(type);
        if (check == -1) {
          cout << "Not a valid type, try again." << endl;
          getline(cin,type);
        }
        cout << "The Pokemon's hp?" << endl;
        getline(cin,hp);
        cout << "Attack?" << endl;
        getline(cin,atk);
        cout << "Defense?" << endl;
        getline(cin,def);
        cout << "Speed?" << endl;
        getline(cin,spd);
        cout << "Speicial?" << endl;
        getline(cin,spc);

        root = addMon(root,dexNum,name,type,stoi(hp),stoi(atk),stoi(def),stoi(spd),stoi(spc),mt,move1,move2,move3,move4);
        cout << "Nice Pokemon! It has been added to the Pokedex (Binary Tree)." << endl;
        break;
      }
      case 2:{
        cout << "Printing Pokemon list" << endl;
        printPokemonList(root);
        break;
      }
      case 3:{
        cout << "Printing moves list" << endl;
        printMoveList(mt);
        break;
      }
      case 4:{
        cout << "Lets Battle!" << endl;
        cout << "Chose the size of the teams" << endl;
        string in;
        getline(cin,in);
        int teamSize = stoi(in);

        cout << "Select "<< teamSize<< " Pokemon for Player 1." << endl;
        team* p1 = makeTeam(root,teamSize);
        cout << "Here is team 1: ";
        team* traverse = p1;
        cout << traverse->mon->name <<"--"<<traverse->mon->m1.name<<"--";
        cout << traverse->mon->m2.name<<"--"<<traverse->mon->m3.name<<"--"<<traverse->mon->m4.name << endl;
        for (size_t i = 0; i < teamSize-1; i++) {
          traverse = traverse->next;
          cout << traverse->mon->name <<"--"<<traverse->mon->m1.name<<"--";
          cout << traverse->mon->m2.name<<"--"<<traverse->mon->m3.name<<"--"<<traverse->mon->m4.name << endl;
        }
        cout << endl;

        cout << "Select "<< teamSize<< " Pokemon for Player 2." << endl;
        team* p2 = makeTeam(root,teamSize);
        cout << "Here is team 1: ";
        traverse = p2;
        cout << traverse->mon->name <<"--"<<traverse->mon->m1.name<<"--";
        cout << traverse->mon->m2.name<<"--"<<traverse->mon->m3.name<<"--"<<traverse->mon->m4.name << endl;
        for (size_t i = 0; i < teamSize-1; i++) {
          p2 = p2->next;
          cout << traverse->mon->name <<"--"<<traverse->mon->m1.name<<"--";
          cout << traverse->mon->m2.name<<"--"<<traverse->mon->m3.name<<"--"<<traverse->mon->m4.name << endl;
        }
        cout << endl;

        battle(p1,p2);
        break;
      }
      case 5:{
        cout << "Hope you had fun :P" << endl;
        finish = 1;
        break;
      }
    }
  }
}
