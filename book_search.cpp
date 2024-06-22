//project1.cpp
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <chrono>

using namespace std;

class Book{
    public:
        int ISBN;
        string language;
        string condition;
        int pN;

        Book(){
            ISBN = 0;
            language = " ";
            condition = " ";
        }

        //2 overloaded operators
        friend bool operator== (const Book& rB, const Book& nB);
        friend bool operator< (const Book& rB, const Book& nB);

        void setISBN(int isbn){
            ISBN = isbn;
        }

        void setLanguage(string lang){
            language = lang;
        }

        void setCondition(string cond){
            condition = cond;
            if(condition == "new"){
                pN = 0;
            } else if(condition == "used"){
                pN = 1;
            } else if(condition == "digital"){
                pN = 2;
            }
        }

        int getISBN(){
            return ISBN;
        }

        string getLanguage(){
            return language;
        }

        int getCondition(){
            return pN;
        }
};

//overloaded operator (checks if both books the same)
bool operator== (const Book& rB, const Book& nB){
    return (rB.ISBN == nB.ISBN &&
            rB.condition == nB.condition &&
            rB.language == nB.language);
}

//overloaded operator (used to sort in specified order)
//pN is an associated value with each book (custom order new(0)->used(1)->digital(2))
bool operator< (const Book& rB, const Book& nB){
    if(rB.ISBN == nB.ISBN){
        if(rB.condition == nB.condition){
            return rB.language > nB.language;
        } else{
            return rB.pN < nB.pN;
        }
    } else{
        return rB.ISBN > nB.ISBN;
    }
}

int linearSearch(vector<Book>& rB, vector<Book>& nB){
    int count = 0;
    //each book in newBooks is compared to each book in requestedBooks
    for(int i = 0; i < (int)nB.size(); i++){
        for(int j = 0; j < (int)rB.size(); j++){
            if(nB[i] == rB[j]){
                count += 1;
            }
        }
    }

    return count;
}

int binarySearch(vector<Book>& nB, Book item){
    int l = 0;
    int r = (int)nB.size() - 1;
    int m;
    int count = 0;

    while(l <= r){
        m = (r + l) / 2;
        if(nB[m] == item){
            count += 1;
            break;
        } else if(item < nB[m]){
            r = (m - 1);
        } else {
            l = (m + 1);
        }
    } 

    return count; 
}

bool fillVect(string fileName, vector<Book>& vector){
    string dat;
    ifstream file;
    file.open(fileName);

    if(file.is_open()){
        while(getline(file, dat)){
            istringstream iss(dat);
            
            Book *bk;
            getline(iss, dat, ',');
            bk = new Book;
            bk->setISBN(stoi(dat));
            getline(iss, dat, ',');
            bk->setLanguage(dat);
            getline(iss, dat, ' ');
            bk->setCondition(dat);
            vector.push_back(*bk);
        }

        file.close();
        
        return true;
    }

    cerr << "File could not be opened.\n";

    return false;
}

int main(int argc, char* argv[]){
    char choice;
    bool validChoice = true;
    int totalCount = 0;
    string fileNewBook;
    string fileReqBook;
    fileNewBook = argv[1];
    fileReqBook = argv[2];
    vector<Book> newBooks;
    vector<Book> requestedBooks;

    if(argc != 4){
        cerr << "Wrong number of arguments\n";
        return -1;
    }

    //output file opened and check if works
    ofstream outFile;
    outFile.open(argv[3]);

    if(!outFile.is_open()){
        cerr << "File could not be opened.\n";
        return -1;
    }

    chrono::high_resolution_clock::time_point start;

    //if files newBooks and requestedBooks can't open, exit
    if((fillVect(fileNewBook, newBooks) == false) || 
        (fillVect(fileReqBook, requestedBooks) == false)){
            return -1;
    }

    start = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();
    double elapsed_us;

    while(validChoice){
        cout << "Choice of search method ([l]inear, [b]inary)?";
        cin >> choice;

        switch(choice){
            case 'l':
                int returnedCount;
                start = chrono::high_resolution_clock::now();

                returnedCount = linearSearch(requestedBooks, newBooks);
                validChoice = false;

                end = chrono::high_resolution_clock::now();
                elapsed_us = chrono::duration<double, micro>(end - start).count();
                cout << "CPU time: " << elapsed_us << " microseconds." << endl;

                outFile << returnedCount << endl;
                outFile.close();

                break;
            case 'b':
                start = chrono::high_resolution_clock::now();
                sort(newBooks.begin(), newBooks.end());
                
                /*for every book in  requestedBooks, send it to binary search 
                and compare it to all books in newBooks*/
                for(int i = 0; i < (int)requestedBooks.size(); i++){
                    totalCount += binarySearch(newBooks, requestedBooks[i]);
                }

                end = chrono::high_resolution_clock::now();
                elapsed_us = chrono::duration<double, micro>(end - start).count();
                cout << "CPU time: " << elapsed_us << " microseconds." << endl;

                outFile << totalCount << endl;
                outFile.close();

                validChoice = false;
                break;
            default:
                cerr << "Incorrect choice\n";
                break;
        }
    }

    return 0;
}