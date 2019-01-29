// File: a1.cpp
// Author: Daniel Palacio
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include<vector>



using namespace std;


/*
* @param - a char that will be mostly used in the base4ToBase10(string base4, int k) for conversion.
* @return - We return an int value from the char c within the paramater.
*/
int convertChar2Int(char c){
  return (int) c - '0';
}

/*
* This method returns a string representation of the integer value in base4. We convert by
* iterating through the string and then computing 4 to the power of k-1 and then converting the
* base.at(i) char to an int and multiplying that by the result of 4^k-1. We then add it to
* the result of base10 to base10. The result of base10is the final base10.
* When we encounter the char N, we initialize the local int variable (base10) to -1. We then automatically
* break the for loop and return base10 as -1.
* @return - We return the base 10 value that was converted from base 4.
*/
int base4ToBase10(string base4, int k){
  k = k-1;
  int base10 = 0;
  for(int i  = 0; (unsigned)i<base4.length();i++){
    if(base4.at(i)=='A'){
      base4.at(i)='0';
    }
    if(base4.at(i)=='C'){
      base4.at(i)='1';
    }
    if(base4.at(i)=='G'){
      base4.at(i)='2';
    }
    if(base4.at(i)=='T'){
      base4.at(i)='3';
    }
    if(base4.at(i)=='N'){
      base10 = -1;
      break;
    }
    // base4.at(i) -> This gives you the char at which the position i points to.
    base10 = base10 + pow(4,k)*(convertChar2Int(base4.at(i)));
    k--;
  }
  return base10;
}
/*
* This main function will be the center of operations. The logic behind the program is to convert the
 following characters respectfully:
 A = 0 C = 1 G = 2 T = 3
 The conversion will be taken care of witing the function base4ToBase10. While converting we will
 get a substring of the line sequence of size k. The position of the substring will increment by one (int count)
 until the end of the line. Once the final conversion to base10 from the function base4ToBase10 we will
 increment the int value within the array at position int count. <- 
*/
int main(int argc, char const *argv[]) {
  //argc is the size of the arguments l
  ifstream dna_seq(argv[1]);
  /*
  * ------------ The local variable line will be the sequence found in the specified text file.----
  */
  string line;
  int k = (int) atoi(argv[2]);
  int size_of_array = (int) pow(4,k);

  /*
  * --------------------------- Text file opens and reads through it and then sorts k-mer--------------------
  */
  while(dna_seq.is_open()){
    /*
    * ---------------- ACFT declaration,definition, and intialization---------------------
    */

    int A = 0;
    int C = 0;
    int G = 0;
    int T = 0;
    int N = 0;
    int kmer_array[size_of_array] = {0};
    /*
    * I used the non_empty_index vector to keep track of the positions of the array that were
    actually incremented. This will make it easier and faster to print out the end result.
    */
    std::vector<string> non_empty_index;
    getline(dna_seq,line);
    if(line.length()==0){
      break;
    }
    /*
    * ------- The for loop below iterates through the line (String) and increments the position count (int) in array---------------
    */
    for(int count = 0;(unsigned)count<line.length();count++){
      string kmer = line.substr(count,k);
      if(!(line.length()<k)){
        if(kmer.length()==k){
          int base10 = base4ToBase10(kmer,k);
          if(!(base10==-1)){
            if(kmer_array[base10]==0){
              non_empty_index.push_back(kmer);
              kmer_array[base10] = 1;
            }else{
              kmer_array[base10]++;
            }
          }

        }
      }

      if(line.at(count)=='A'){
        A++;
      }
      if(line.at(count)=='C'){
        C++;
      }
      if(line.at(count)=='G'){
        G++;
      }
      if(line.at(count)=='T'){
        T++;
      }
      if(line.at(count)=='N'){
        N++;
      }
    }
    /*
    *--------------- The if statement below handles the special condition when the line sequence is below
    * what the kmer count should be. --------------
    */
    if(line.length()<k){
      std::cout << 0 << " " << k << " " << line.length() << endl;
      std::cout << 1 << " " << A << " " << C << " " << G << " " << T << " " << N << endl;
    }else{
      // For this else statement we will print out the steps mentioned in the book and pick out the positions from the array
      std::cout << 0 << " " << k << " " << line.length() << endl;
      std::cout << 1 << " " << A << " " << C << " " << G << " " << T << " " << N << endl;
      for(int i = 0;i<non_empty_index.size();i++){
        std::cout << non_empty_index.at(i) << " " << kmer_array[base4ToBase10(non_empty_index.at(i),k)] << endl;
      }
    }
  }


  return 0;
}
