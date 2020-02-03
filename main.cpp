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

//constructor
  Key (std::string f, std::string s, int t): first(f), second(s), third(t){
  }
  //comparator functor that would check if the two objects are the same
  //used in the unordered map 
  bool operator==(const Key &other) const
  { 
  return (first == other.first
            && second == other.second);
          //  && third == other.third);
  }
//friend function that can access private members, and this overloads the << operator to be used for classes
//this block prints out the output of the unordered map to console
 friend std::ostream& operator<< (std::ostream& out, const Key& rhs) {
        out << rhs.first<<" : ";
        out <<rhs.second<<" : ";
    
    }

//this block prints out the output of the unordered map to the files
friend std::ofstream& operator<< (std::ofstream& fout, const Key& rhs) {
        fout<<rhs.first<<" : ";
        fout<<rhs.second<<" : ";
       // out<<rhs.third;
    }

};

//defining the hash values of the username and password that would be used as key to the unordered map
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
  std::ofstream fout;// output stream used to write to a file 
  std::string userName;//string to store the username 
  std::string passWord;// string to store password
  int id;//string to store ID
  int trial = 0; //string to store number of trials 
  int condition = 1;//string to store case condition 
  int choice;//string to store the choice on the menu

//unordered map used to store the student info
  std::unordered_map<Key,int> setOfStud; 
  //do while loop to get the options to repeat until conditon to terminate is reached


do{
std::cout<<"Enter an option"<<std::endl;
std::cout<<"1. Exit"<<std::endl;
std::cout<<"2. Login by inserting username, password "<<std::endl;
std::cin>>choice;//enter the choice from menu
std::cout<<std::endl;



switch(choice){
case 1:
    std::cout<<"Exiting"<<std::endl;
    condition = 0;//condition to exit the loop
    break;
case 2:
  std::cout<<"Enter the name you want to enter"<<std::endl;
  std::cin>>userName;//enter user name 
  std::cout<<"Enter the password you want to enter"<<std::endl;
  std::cin>>passWord;//enter passowrd
  srand(time(NULL));//seed to generate random values 
  id = rand()%100+100000; //random numbers generated for the students 
 


    //res is used to store the values of the insert operation
     auto res= setOfStud.insert(std::make_pair(Key(userName,passWord,id),id));
     if(res.second == false){
     while (trial<5){
      std::cout << "Failed to insert with duplicate name - "<<userName << std::endl;
      //write the breach to file 
    fout.open("attemptedduplicate.txt");
    fout<< "Name" << " :: " <<"Password" << " :: " << "ID" <<std::endl;
    fout<< userName << " :: " <<passWord << " :: " << id <<std::endl;
    //write the breach to console
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
//open authenticate .txt to write the output of the inserted users
 fout.open("authenticate.txt");
 if(fout.is_open()){
 for (auto& x : setOfStud) {
      //display to file 
        fout << x.first << ": " << x.second << std::endl;
        //display to console
        std::cout << x.first << ": " << x.second << std::endl;
    }
    fout.close();//close the file 
 }
}