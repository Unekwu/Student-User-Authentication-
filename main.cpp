#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include<algorithm>
#include <iterator>
#include <ctime>
#include <fstream>

class Key
{
  public:
  std::string first;
  std::string second;
  int         third;

  Key (std::string f, std::string s, int t): first(f), second(s), third(t){
  }
  bool operator==(const Key &other) const
  { 
  return (first == other.first
            && second == other.second);
          //  && third == other.third);
  }
  
 friend std::ostream& operator<< (std::ostream& out, const Key& rhs) {
        out << rhs.first<<" : ";
        out <<rhs.second<<" : ";
    
    }
  
friend std::ofstream& operator<< (std::ofstream& fout, const Key& rhs) {
        fout<<rhs.first<<" : ";
        fout<<rhs.second<<" : ";
    }
};

namespace std {
template <>
struct hash<Key>
  {
       std::size_t operator()(const Key& k ) const
        {
            size_t res = 17;
            res = res * 31 + hash<std::string>()( k.first );
            res = res * 31 + hash<std::string>()( k.second );
            return res;
        }
    };
}


int main()
{
  std::ofstream fout;
  std::string userName;
  std::string passWord;
  int id;
  int trial = 0; 
  int condition = 1;
  int choice;


    std::unordered_map<Key,int> setOfStud; 
  do{
  std::cout<<"Enter an option"<<std::endl;
  std::cout<<"1. Exit"<<std::endl;
  std::cout<<"2. Login by inserting username, password "<<std::endl;
  std::cin>>choice;
  std::cout<<std::endl;



switch(choice){
case 1:
    std::cout<<"Exiting"<<std::endl;
    condition = 0;
    break;
case 2:
  std::cout<<"Enter the name you want to enter"<<std::endl;
  std::cin>>userName;
  std::cout<<"Enter the password you want to enter"<<std::endl;
  std::cin>>passWord;
  srand(time(NULL));
  id = rand()%100+100000;
    
     auto res= setOfStud.insert(std::make_pair(Key(userName,passWord,id),id));
     if(res.second == false){
     while (trial<5){
      std::cout << "Failed to insert with duplicate name - "<<userName << std::endl;
      fout.open("attemptedduplicate.txt");
      fout<< "Name" << " :: " <<"Password" << " :: " << "ID" <<std::endl;
      fout<< userName << " :: " <<passWord << " :: " << id <<std::endl;
      std::cout<<"unauthorized access...Try again "<<std::endl;
      std::cout<<"Enter the name you want to enter again "<<std::endl;
      std::cin>>userName;
      std::cout<<"Enter the password you want to enter again "<<std::endl;
      std::cin>>passWord;
      srand(time(NULL));
      id = rand()%100+198500;
      trial++;
      auto res= setOfStud.insert(std::make_pair(Key(userName,passWord,id),id));
     fout.close();
    }
  }
  else {
    std::cout<<"Successful Insertion"<<std::endl;
    }
    break;
  }
  
} while(condition);
 fout.open("authenticate.txt");
 if(fout.is_open()){
 for (auto& x : setOfStud) { 
        fout << x.first << ": " << x.second << std::endl;
        std::cout << x.first << ": " << x.second << std::endl;
    }
    fout.close(); 
 }
}
