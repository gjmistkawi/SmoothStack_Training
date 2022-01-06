#include <iostream>

using namespace std;

int main() {
    string input;
    cout << "Enter a C++ type: ";
    getline(cin, input);

    if( input == "short int" ) {
        cout << sizeof(short int) << endl;
    } 
    
    else if ( input == "unsigned short int" ) {
        cout << sizeof(unsigned short int) << endl;
    } 
    
    else if ( input == "unsigned int" ) {
        cout << sizeof(unsigned int) << endl; 
    } 
    
    else if ( input == "int" ) {
        cout << sizeof(int) << endl;
    } 
    
    else if ( input == "long int" ) {
        cout << sizeof(long int) << endl; 
    } 
    
    else if ( input == "unsigned long int" ) {
        cout << sizeof(unsigned long int) << endl;
    } 
    
    else if ( input == "long long int" ) {
        cout << sizeof(long long int) << endl;  
    } 

    else if ( input == "unsigned long long int" ) {
        cout << sizeof(unsigned long long int) << endl;  
    } 
    
    else if ( input == "char" ) {
        cout << sizeof(char) << endl;   
    } 
    
    else if ( input == "float" ) {
        cout << sizeof(float) << endl;   
    } 
    
    else if ( input == "double" ) {
        cout << sizeof(double) << endl;       
    } 
    
    else if ( input == "long double" ) {
        cout << sizeof(long double) << endl;        
    } 
    
    else {
        cout << "This input is not a valid C++ type. " << endl;
    }

    return 0;
}