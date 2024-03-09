#include <bits/stdc++.h>
#include <cmath>
using namespace std;


int get_valid_key(){ // to make sure that the secret key of the route cipher is valid.
    int secret_key;
    cout << "please enter the secret key: ";
    while ( !(cin >> secret_key) || secret_key <= 0 ){
        cout << "please enter a valid key(valid keys are integers bigger than 0)" << endl;
        cin.clear();
        cin.ignore();
    }
    return secret_key;
}


string strip(string sentece){ // to remove the spaces in the text in the route cipher encryption .
    string stripped_sentence;
    for(int i = 0; i < sentece.length(); i++){
        if(sentece[i] != ' '){
            stripped_sentence += sentece[i];
        }
    }
    return stripped_sentence;
}


bool keyValidity (const string& key){
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
    string poly[6][6] = {{" ", "", "", "", "", ""},
                         {"", "A", "B", "C", "D", "E"},
                         {"", "F", "G", "H", "I", "K"},
                         {"", "L", "M", "N", "O", "P"},
                         {"", "Q", "R", "S", "T", "U"},
                         {"", "V", "W", "X", "Y", "Z"}};

    string keyInput;
    cout << "Enter the key: " << endl;
    cout << "->";
    cin >> keyInput;

    while (! keyValidity(keyInput)){
        cin >> keyInput;
    }

    // assigning keyInput to the poly square
    string key = " ";
    key += keyInput;

    for (int i = 0; i < 6; ++i) {
        poly[0][i] = key[i];
        poly[i][0] = key[i];
    }

    string encrypted;
    encrypted = "";

    for (auto ch : message){
        if (ispunct(ch) || isspace(ch)){
            encrypted += ch;
        }
        for (int i = 1; i < 6; ++i) {
            for (int j = 1; j < 6; ++j) {
                string letter;
                ch = toupper(ch);
                letter = ch;

                if (letter == poly[i][j]){
                    encrypted += poly[i][0];
                    encrypted += poly[0][j];

                }
            }
        }
    }

    cout << "Encrypted message -> " <<encrypted << endl << endl;
}


bool poly_decrypted_validity(string encrypted){
    for (auto i : encrypted){
        if (isalpha(i)){
            cout << "Invalid message. Encrypted messages should be digits only, try again." << endl;
            cout << "->";
            return false;
        }
    }

    if (encrypted.length() % 2 != 0){
        cout << "Invalid message." << endl;
        cout << "->";
        return false;
    }
    return true;
}


void polybius_square_decryption(string encrypted) {
    string poly[6][6] = {{" ", "",  "",  "",  "",  ""},
                         {"",  "A", "B", "C", "D", "E"},
                         {"",  "F", "G", "H", "I", "K"},
                         {"",  "L", "M", "N", "O", "P"},
                         {"",  "Q", "R", "S", "T", "U"},
                         {"",  "V", "W", "X", "Y", "Z"}};

    string cleanEncrypted = "";
    for (auto i: encrypted) {
        if (!isdigit(i)) {

        }
        else {
            cleanEncrypted += i;
        }
    }


    while(!poly_decrypted_validity(cleanEncrypted)){
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, encrypted);
        cleanEncrypted = "";
        for (auto i: encrypted) {
            if (!isdigit(i))
                continue;
            else {
                cleanEncrypted += i;
            }
        }
    }

    cout << "Enter the key." << endl;
    cout << "->";
    string keyInput;
    cin >> keyInput;

    while (!keyValidity(keyInput)) {
        cout << "Enter the key." << endl;
        cout << "->";
        cin >> keyInput;
    }

    // assigning keyInput to the poly square
    string key = " ";
    key += keyInput;

    for (int i = 0; i < 6; ++i) {
        poly[0][i] = key[i];
        poly[i][0] = key[i];
    }

    // assign each letter to its index according to the key.
    map<vector<string>, string> alphaKeys;

    for (int i = 1; i < 6; ++i) {
        for (int j = 1; j < 6; ++j) {
            alphaKeys[{poly[i][0], poly[0][j]}] = poly[i][j];
        }
    }

    string decrypted = "";
    for (int i = 0; i < cleanEncrypted.length(); ) {
        for (int j = i + 1; j < cleanEncrypted.length(); j += 2) {
            string row, column;
            row = cleanEncrypted[i];
            column = cleanEncrypted[j];
            decrypted += alphaKeys[{row, column}];
            i += 2;
        }
    }

    cout << decrypted << endl;

}


void route_cipher_encryption(string sentence_to_encrypt){

    // explian to the user what he needs to do in order to encrypt the text.
    cout << "welcome to the route cipher encryption in order to encrypt some text you need to choose a secret key" << endl << endl;

    int secret_key = get_valid_key(); // getting the secret key and checking it's validity.
    int character_counter = 0; // this counter will help create the matrix of the cipher.
    string stripped_sentence = strip(sentence_to_encrypt); // stripping the text from any spaces.
    int number_of_rows = ceil(static_cast<float>(stripped_sentence.length()) / static_cast<float>(secret_key));// calculating the number of rows in the matrix.
    string cipher_matrix[number_of_rows][secret_key];
    // filling the matrix with the character of the text.
    for(int i = 0; i < number_of_rows; i++){
        for (int j = 0; j < secret_key; j++){
            if(character_counter < stripped_sentence.length()){
                cipher_matrix[i][j] = stripped_sentence[character_counter];
                character_counter++;
            }
            // filling the rest of the matrix with x's.
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
            start_right--; // changing the start_right value so we don't get the same column when going down again.
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

    cout << encrypted_sentence << endl << endl; // printing the encrypted text.

}


void route_cipher_decryption(string encrypted_sentence){

    // explian to the user what he needs to do in order to decrypt the text.
    cout << "welcome to the route cipher decryption in order to decrypt some text you need to enter the secret key" << endl << endl;


    int secret_key = get_valid_key(); // getting the secret key and checking it's validity.
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
            start_right--; // changing the start_right value so we don't get the same column when going down again.
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
    cout << decrypted_sentence << endl << endl; // printing the decrypted text
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
                if (cipher_choice == "1"){ // for the polybius square cipher encryption.
                    polybius_square_encryption(message);
                    break;
                }

                else if (cipher_choice == "2"){
                    route_cipher_encryption(message);
                    break;
                }

                else if (cipher_choice == "3"){ // for the rail-fence cipher.

                    break;
                }

                else{
                    cout << "please enter a valid choice" << endl;
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
                if (cipher_choice == "1"){ // for the polybius square cipher decryption.
                    polybius_square_decryption(encrypted);
                    break;
                }
                else if (cipher_choice == "2"){
                    route_cipher_decryption(encrypted);
                    break;
                }
                else if (cipher_choice == "3"){ // for the rail-fence cipher decryption.

                    break;
                }
                else{
                    cout << "please enter a valid choice" << endl;
                }
            }
        }
    }
}
