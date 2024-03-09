/*
FCAI - Structured Programming - 2024 - Assignment 2
Program Name:
program Description: This program is a simple encryption and decryption program using three sipmle ciphers.
Last Modification Date: 9/3/2024.
Author1: Zeyad Mohamed Arafat   20230161   s21
Author2: Youssef Ahmed Beshir   20230476   s21
Author3: John Ayman Demian      20230109   s21
Teaching Assistant:
Polybius square Cipher ---------------> Youssef Ahmed Beshir
Route Cipher -------------------------> Zeyad Mohamed Arafat
Rail fence Cipher --------------------> John Ayman Demian
*/


#include <bits/stdc++.h>
#include <cmath>
#include <cctype>
#include <string>
#include <vector>
using namespace std;


int route_key_validity(){
    // To make sure that the secret key of the route cipher is valid.
    int secret_key;
    cout << "Please enter the secret key: ";
    while ( !(cin >> secret_key) || secret_key <= 0 ){
        cout << "Please enter a valid key (valid keys are integers bigger than 0)" << endl;
        cin.clear();
        cin.ignore();
    }
    return secret_key;
}


string strip(string sentence){
    // To remove the spaces in the text in the route cipher encryption .
    string stripped_sentence;
    for(int i = 0; i < sentence.length(); i++){
        if(sentence[i] != ' '){
            stripped_sentence += sentence[i];
        }
    }
    return stripped_sentence;
}


bool poly_key_validity (const string& key){
    // Checking the validity of the cipher key and handling possible errors.
    int number;
    string ch;

    if (key.length() != 5){
        cout << "Invalid key. Key should be a length of 5 numbers only, try again." << endl;
        cout << "->";
        return false;
    }

    for (auto i : key){
        if ( ! isdigit(i)){
            cout << "Invalid key. Key should contain integer numbers only, try again." << endl;
            cout << "->";
            return false;
        }
    }

    for (auto i : key) {
        ch = i;
        number = stoi(ch);
        if (number < 1 || number > 5){
            cout << "Invalid key. Key should contain numbers of range [1, 5] only, try again." << endl;
            cout << "->";
            return false;
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 5; ++j) {
            if (key[i] == key[j]){
                cout << "Invalid key. Key should not contain the same number twice, try again." << endl;
                cout << "->";
                return false;
            }
        }
    }
    return true;
}


void polybius_square_encryption(const string& message){
    // App data
    char poly[6][6] = {{' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', 'A', 'B', 'C', 'D', 'E'},
                         {' ', 'F', 'G', 'H', 'I', 'K'},
                         {' ', 'L', 'M', 'N', 'O', 'P'},
                         {' ', 'Q', 'R', 'S', 'T', 'U'},
                         {' ', 'V', 'W', 'X', 'Y', 'Z'}};

    string keyInput;
    cout << "Enter the key: " << endl;
    cout << "->";
    cin >> keyInput;

    while (!poly_key_validity(keyInput)){
        cin >> keyInput;
    }

    // Assigning keyInput to the poly square
    string key = " ";
    key += keyInput;

    for (int i = 0; i < 6; ++i) {
        poly[0][i] = key[i];
        poly[i][0] = key[i];
    }

    string encrypted;
    encrypted = "";

    // Main cipher loop.
    for (auto ch : message){
        if (not isalpha(ch)){
            encrypted += ch;
        }
        for (int i = 1; i < 6; ++i) {
            for (int j = 1; j < 6; ++j) {
                if (toupper(ch) == poly[i][j]){
                    encrypted += poly[i][0];
                    encrypted += poly[0][j];
                }
            }
        }
    }
    cout << "Encrypted message -> " <<encrypted << endl << endl;
}


bool poly_decrypted_validity(string & encrypted){
    // Checking the validity of the decrypted message.
    for (auto i : encrypted){
        if (isalpha(i)){
            cout << "Invalid message. Encrypted messages should be digits only, try again." << endl;
            cout << "->";
            return false;
        }
    }

    string cleanEncrypted;
    for (auto i: encrypted) {
        if (!isdigit(i)) {
            continue;
        }
        else {
            cleanEncrypted += i;
        }
    }

    for (auto i : cleanEncrypted){
        string ch;
        ch = i;
        if (stoi (ch) > 5 || stoi(ch) == 0){
            cout << "Message should have numbers [1 -> 5] only, try again." << endl;
            cout << "->";
            return false;
        }
    }

    if (cleanEncrypted.length() % 2 != 0){
        cout << "Invalid message. Try again." << endl;
        cout << "->";
        return false;
    }
    return true;
}


void polybius_square_decryption(string &encrypted) {
    // App data
    string poly[6][6] = {{" ", "",  "",  "",  "",  ""},
                         {"",  "A", "B", "C", "D", "E"},
                         {"",  "F", "G", "H", "I", "K"},
                         {"",  "L", "M", "N", "O", "P"},
                         {"",  "Q", "R", "S", "T", "U"},
                         {"",  "V", "W", "X", "Y", "Z"}};

    while (!poly_decrypted_validity(encrypted)){
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, encrypted);
    }

    cout << "Enter the key." << endl;
    cout << "->";
    string keyInput;
    cin >> keyInput;

    while (!poly_key_validity(keyInput)) {
        cout << "Enter the key." << endl;
        cout << "->";
        cin >> keyInput;
    }

    // Assigning the cipher key to the poly square.
    string key = " ";
    key += keyInput;

    for (int i = 0; i < 6; ++i) {
        poly[0][i] = key[i];
        poly[i][0] = key[i];
    }

    // Assign each letter to its index according to the key.
    map<vector<string>, string> alphaKeys;

    for (int i = 1; i < 6; ++i) {
        for (int j = 1; j < 6; ++j) {
            alphaKeys[{poly[i][0], poly[0][j]}] = poly[i][j];
        }
    }

    string decrypted;
    for (int i = 0; i < encrypted.length();) {
        if (i == encrypted.length() - 1){
            decrypted += encrypted[i];
            break;
        }
        for (int j = i + 1; j < encrypted.length(); j += 2) {
            string row, column;
            row = encrypted[i];
            column = encrypted[j];
            if (!isdigit(encrypted[i])){
                decrypted += encrypted[i];
                i ++;
                j --;
            }

            else{
                decrypted += alphaKeys[{row, column}];
                i += 2;
            }
        }
    }

    cout << "Decrypted message --> "<< decrypted << endl;
}


void route_cipher_encryption(string sentence_to_encrypt){

    // Explain to the user what he needs to do in order to encrypt the text.
    cout << "Welcome to the route cipher encryption in order to encrypt some text you need to choose a secret key" << endl << endl;

    int secret_key = route_key_validity(); // Getting the secret key and checking its validity.
    int character_counter = 0; // This counter will help create the matrix of the cipher.
    string stripped_sentence = strip(sentence_to_encrypt); // Stripping the text from any spaces.
    int number_of_rows = ceil(static_cast<float>(stripped_sentence.length()) / static_cast<float>(secret_key));// Calculating the number of rows in the matrix.
    string cipher_matrix[number_of_rows][secret_key];

    // Filling the matrix with the character of the text.
    for(int i = 0; i < number_of_rows; i++){
        for (int j = 0; j < secret_key; j++){
            if(character_counter < stripped_sentence.length()){
                cipher_matrix[i][j] = stripped_sentence[character_counter];
                character_counter++;
            }
            // Filling the rest of the matrix with x's.
            else {
                cipher_matrix[i][j] = "x";
            }
        }
    }

    // the rest of the function is for the spiral iteration.
    // there is a pattern in the iteration, you go down then left then up then right and repeat, all inside the 2d array(matrix).
    int direction = 0; // creating a direction variable to switch between directions.
    // four variables to indicate the start from each direction.
    int start_down = number_of_rows-1;
    int start_up = 0;
    int start_right = secret_key-1;
    int start_left = 0;
    string encrypted_sentence;
    int counter = 0; // the counter to stop the spiral iteration when done.
    while(counter < secret_key*number_of_rows){
        if(direction == 0){ // direction 0 means going down in the matrix.
            // the start point is the top right corner [start_up][start_right].
            // while going down we are moving in the most right column (start_right) and change the row index from 0(start_up) to (start_down).
            for (int i = start_up; i <= start_down; i++){
                encrypted_sentence += cipher_matrix[i][start_right];
                counter++; // increasing the counter to stop the while loop.
            }
            start_right--; // changing the start_right value, so we don't get the same column when going down again.
            direction = 1; // changing the direction as planned in the iteration pattern.
        }
            // all the other loops work with the same logic.


        else if (direction == 1){ // direction 1 means going left in the matrix.
            for (int i = start_right; i >= start_left; i--){
                encrypted_sentence += cipher_matrix[start_down][i];
                counter++;
            }
            start_down--;
            direction = 2;
        }


        else if (direction == 2){ // direction 2 means going up in the matrix.
            for (int i = start_down; i >= start_up; i--){
                encrypted_sentence += cipher_matrix[i][start_left];
                counter++;
            }
            start_left++;
            direction = 3;
        }


        else if (direction == 3){ // direction 3 means going right in the matrix.
            for (int i = start_left; i <= start_right; i++){
                encrypted_sentence += cipher_matrix[start_up][i];
                counter++;
            }
            start_up++;
            direction = 0;
        }
    }

    cout << "Encrypted --> " << encrypted_sentence << endl << endl; // printing the encrypted text.

}


void route_cipher_decryption(string encrypted_sentence){

    // Explain to the user what he needs to do in order to decrypt the text.
    cout << "welcome to the route cipher decryption in order to decrypt some text you need to enter the secret key" << endl << endl;


    int secret_key = route_key_validity(); // getting the secret key and checking its validity.
    string stripped_sentence = strip(encrypted_sentence);// stripping the text from any spaces.
    int number_of_rows = ceil(static_cast<float>(stripped_sentence.length()) / static_cast<float>(secret_key));// calculating the number of rows in the matrix.
    string cipher_matrix[number_of_rows][secret_key];
    int direction = 0;// creating a direction variable to switch between directions.
    // four variables to indicate the start from each direction.
    int start_down = number_of_rows-1;
    int start_up = 0;
    int start_right = secret_key-1;
    int start_left = 0;
    string decrypted_sentence;
    int counter = 0;

    // filling the matrix with the character of the text in a spiral way.
    while(counter < secret_key*number_of_rows){
        // the start point is the top right corner [start_up][start_right].
        // while going down we are moving in the most right column (start_right) and change the row index from 0(start_up) to (start_down).
        if(direction == 0){
            for (int i = start_up; i <= start_down; i++){
                cipher_matrix[i][start_right] = stripped_sentence[counter]; // adding the characters of the text to the matrix.
                counter++; // increasing the counter to stop the while loop.
            }
            start_right--; // changing the start_right value, so we don't get the same column when going down again.
            direction = 1; // changing the direction as planned in the iteration pattern.
        }
            // all the other loops work with the same logic.


        else if (direction == 1){ // direction 1 means going left in the matrix.
            for (int i = start_right; i >= start_left; i--){
                cipher_matrix[start_down][i] = stripped_sentence[counter];
                counter++;
            }
            start_down--;
            direction = 2;
        }

        else if (direction == 2){ // direction 2 means going up in the matrix.
            for (int i = start_down; i >= start_up; i--){
                cipher_matrix[i][start_left] = stripped_sentence[counter];
                counter++;
            }
            start_left++;
            direction = 3;
        }

        else if (direction == 3){ // direction 3 means going right in the matrix.
            for (int i = start_left; i <= start_right; i++){
                cipher_matrix[start_up][i] = stripped_sentence[counter];
                counter++;
            }
            start_up++;
            direction = 0;
        }
    }

    // reading the characters in the matrix in the right order.
    for (int i = 0; i < number_of_rows; i++){
        for (int j = 0; j < secret_key; j++){
            decrypted_sentence += cipher_matrix[i][j]; // adding characters to the decrypted sentence
        }
    }
    cout << "Decrypted --> " <<decrypted_sentence << endl << endl; // printing the decrypted text
}


void rail_Fence_Encrypt(const string& message) {
    // set main variables
    string text = message, key, encrypted_text;
    int num;

    // print welcome message
    cout << "welcome to Rail Fence encrypt program " << endl;
        // let user select the key
        cout << "please choose the key 3 or 4 :  " ;
        cin.ignore();
        getline(cin , key ) ;
        //check validation of key
        while (key != "3" && key != "4") {
        cout << "Invalid key. Please choose the key 3 or 4: ";
        getline(cin, key);
            }
            num = stoi(key);
            if( num == 3 ) {
                // make 3 lists
                vector <char> list1 , list2 , list3;
                // make first list to collect the first row by adding 4 each loop
                for (int i = 0; i < text.length() ; i+=4) {
                    list1.push_back(text[i]);
                }
                // make second to collect second row by adding 2 each loop
                for (int j = 1 ; j < text.length(); j+=2) {
                    list2.push_back(text[j]);
                }
                // make third to collect third row by adding 4 each loop
                for (int y = 2; y < text.length(); y+=4) {
                    list3.push_back(text[y]);
                }
                // print the result of three lists
                cout << "Cipher text : ";
                for (char c : list1) {
                    cout << c;
                }
                for (char c : list2) {
                    cout << c;
                }
                for (char c : list3) {
                    cout << c;
                }
                cout << endl;
            }
            else if (num == 4) {
                // make 4 lists
                vector <char> list1 , list2 , list3 , list4 ;
                // first to collect first row by adding 6 each loop
                for (int i = 0; i < text.length() ; i+=6) {
                    list1.push_back(text[i]);
                }
                // second one to collect second row
                // but flag to iterate each loop between 4 , 2
                bool addFour = true;
                for (int j = 1; j < text.length();) {
                    list2.push_back(text[j]);
                    // here add 4 first time
                    if (addFour) {
                        j += 4;
                    // and 2 in second time
                    } else {
                        j += 2;
                    }
                    addFour = !addFour; // Toggle the flag
                }
                // third one to collect third row
                // but flag to iterate each loop between 2 , 4
                bool addTwo = true ;
                for (int y = 2 ; y < text.length(); ) {
                    list3.push_back(text[y]);
                    // here add 2 first time
                    if (addTwo) {
                        y += 2;
                    // and 4 in second time
                    } else {
                        y += 4;
                    }
                    addTwo = !addTwo; // Toggle the flag
                }
                // fourth one to collect last row by adding 6 each loop
                for (int u = 3; u < text.length(); u+=6) {
                    list4.push_back(text[u]);
                }
                // print the result of four lists
                cout << "Cipher text : ";
                for (char c : list1) {
                    cout << c;
                }
                for (char c : list2) {
                    cout << c;
                }
                for (char c : list3) {
                    cout << c;
                }
                for (char c : list4) {
                    cout << c;
                }
                cout << endl;

            }
}


void rail_Fence_Decrypt(const string& message) {
    // set main variables
    string text = message, key, decrypted_text;
    int num;
    // print welcome message
    cout << "welcome to Rail Fence encrypt program " << endl;
        // let user choose the key
        cout << "please choose the key 3 or 4 :  " ;
        cin.ignore();
        getline(cin , key ) ;
        while (key != "3" && key != "4") {
            cout << "Invalid key. Please choose the key 3 or 4: ";
            getline(cin, key);
        }
            num = stoi(key) ;
            if(num == 3 ) {
                int len = text.length();
                // set decrypt text with len = len of clear text
                decrypted_text.resize(len);
                int pos = 0;
                //make for loop to iterates in the text
                for (int i = 0; i < 3 ; ++i) {
                    int index = i;
                    // put flag
                    bool down = true;
                    while (index < len) {
                        decrypted_text[index] = text[pos++];
                        // when i == 0 or 2 it will take the letters from first row
                        if (i == 0 || i ==  2)
                            index += 4;
                        else {
                            // this line when i == 1 it will take the letters from second row
                            if (down)
                                index += 2 * (2 - i );
                            // and this when i == 1 it will take the letters from third row
                            else
                                index += 2 * i;
                            // switch flag to change the row
                            down = !down;
                        }
                    }
                }
                // print the result
                cout << "Decrypt text is :  " << decrypted_text << endl ;
            }
            else if (num == 4) {
                int len = text.length();
                // set decrypt text with len = len of clear text
                decrypted_text.resize(len);
                int pos = 0;
                //make for loop to iterates in the text
                for (int i = 0; i < 4 ; ++i) {
                    int index = i;
                    // put flag
                    bool down = true;
                    while (index < len) {
                        decrypted_text[index] = text[pos++];
                        // this line when i == 0 or 3 it will take the letters from first and fourth row
                        if (i == 0 || i ==  3)
                            index += 2 * 3;
                        else {
                            // this line when i == 1 or 2 it will take the letters from second row
                            if (down)
                                index += 2 * (3 - i );
                            // and this when i == 1 or 2 it will take the letters from third row
                            else
                                index += 2 * i;
                            // switch flag to change the row
                            down = !down;
                        }
                    }
                }
                // print the result
                cout << "Decrypt text is :  " << decrypted_text << endl ;
            }
}


int main() {
    string message, encrypted;
    cout << "Ahlan ya user ya habibi." << endl;

    while (true){
        cout << "What do you like to do?" << endl << endl;
        cout << "1- Cipher a message." << endl;
        cout << "2- Decipher a message." << endl;
        cout << "3- End." << endl;
        cout << "->";

        string menu;
        cin >> menu;

        if (menu == "3")
            break;


        else if (menu == "1"){
            cout << "Please enter the message to cipher." << endl;
            cout << "->";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, message);

            cout << "Which Cipher do you like to choose?" << endl;
            cout << "1- polybius Square cipher" << endl;
            cout << "2- route cipher" << endl;
            cout << "3- rail-fence cipher" << endl;
            cout << "->";

            string cipher_choice;
            cin >> cipher_choice;

            while(true){
                if (cipher_choice == "1"){          // For the polybius square cipher encryption.
                    polybius_square_encryption(message);
                    break;
                }

                else if (cipher_choice == "2"){     // For the route cipher encryption.
                    route_cipher_encryption(message);
                    break;
                }

                else if (cipher_choice == "3"){     // For the rail-fence cipher encryption.
                    rail_Fence_Encrypt(message);
                    break;
                }

                else{
                    cout << "please enter a valid choice" << endl;
                    break;
                }
            }
        }

        else if (menu == "2"){
            cout << "Please enter the message to decipher." << endl;
            cout << "->";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, encrypted);

            cout << "what cipher would you like to use?" << endl;
            cout << "1- polybius Square cipher" << endl;
            cout << "2- route cipher" << endl;
            cout << "3- rail-fence cipher" << endl;
            cout << "->";

            string cipher_choice;
            cin >> cipher_choice;

            while(true){
                if (cipher_choice == "1"){      // For the polybius square cipher decryption.
                    polybius_square_decryption(encrypted);
                    break;
                }
                else if (cipher_choice == "2"){ // For the route cipher decryption.
                    route_cipher_decryption(encrypted);
                    break;
                }
                else if (cipher_choice == "3"){ // For the rail-fence cipher decryption.
                    rail_Fence_Decrypt(encrypted);
                    break;
                }
                else{
                    cout << "Please enter a valid choice" << endl;
                    break;
                }
            }
        }
    }
}
