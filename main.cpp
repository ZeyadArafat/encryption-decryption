#include <bits/stdc++.h>
#include <cmath>
using namespace std;


string strip(string sentece){
    string result;
    for(int i = 0; i < sentece.length(); i++){
        if(sentece[i] != ' '){
            result += sentece[i];
        }
    }
    return result;
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


bool isAlpha(const string& msg){
    for (auto i : msg){
        if (! isalpha(i))
            return false;
    }
    return true;
}


void polybiusSquareEncryption(const string& message){
    // App data
    string poly[6][6] = {{" ", "", "", "", "", ""},
                         {"", "A", "B", "C", "D", "E"},
                         {"", "F", "G", "H", "I", "K"},
                         {"", "L", "M", "N", "O", "P"},
                         {"", "Q", "R", "S", "T", "U"},
                         {"", "V", "W", "X", "Y", "Z"}};

    string keyInput;
    cout << "Enter the polybiusSquareEncryption key: " << endl;
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


void polybiusSquareDecryption(const string& encrypted) {
    string poly[6][6] = {{" ", "",  "",  "",  "",  ""},
                         {"",  "A", "B", "C", "D", "E"},
                         {"",  "F", "G", "H", "I", "K"},
                         {"",  "L", "M", "N", "O", "P"},
                         {"",  "Q", "R", "S", "T", "U"},
                         {"",  "V", "W", "X", "Y", "Z"}};

    cout << "Enter the key." << endl;
    cout << "->";
    string keyInput;
    cin >> keyInput;

    while (!keyValidity(keyInput)) {
        cout << "Enter the key." << endl;
        cout << "->";
        cin >> keyInput;
    }

    string cleanEncrypted;

    for (auto i: encrypted) {
        if (!isdigit(i)) {}
        else {
            cleanEncrypted += i;
        }
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


void route_cipher_encryption(){

    cout << "welcome to the route cipher encryption in order to encrypt some text you need to choose a secret key" << endl;
    cout << "and then enter the text you need to encrypt" << endl << endl;

    int secret_key;
    int character_counter = 0;
    string sentence_to_encrypt;
    cout << "enter the secret key: ";
    cin >> secret_key;
    cout << "enter the sentence or word you want to encrypt: ";
    cin.ignore();
    getline(cin, sentence_to_encrypt);
    string striped_sentence = strip(sentence_to_encrypt);
    int number_of_rows = ceil(static_cast<float>(striped_sentence.length()) / static_cast<float>(secret_key));
    string cipher_matrix[number_of_rows][secret_key];
    for(int i = 0; i < number_of_rows; i++){
        for (int j = 0; j < secret_key; j++){
            if(character_counter < striped_sentence.length()){
                cipher_matrix[i][j] = striped_sentence[character_counter];
                character_counter++;
            }
            else {
                cipher_matrix[i][j] = "x";
            }

        }
    }
    int direction = 0;
    int space_down = number_of_rows-1;
    int space_up = 0;
    int space_left = secret_key-1;
    int space_right = 0;
    string encrypted_sentence;
    int counter = 0;
    while(counter < secret_key*number_of_rows){
        if(direction == 0){
            for (int i = space_up; i <= space_down; i++){
                encrypted_sentence += cipher_matrix[i][space_left];
                counter++;
            }
            space_left--;
            direction = 1;
        }
        else if (direction == 1){
            for (int i = space_left; i >= space_right ; i--){
                encrypted_sentence += cipher_matrix[space_down][i];
                counter++;
            }
            space_down--;
            direction = 2;
        }

        else if (direction == 2){
            for (int i = space_down; i >= space_up; i--){
                encrypted_sentence += cipher_matrix[i][space_right];
                counter++;
            }
            space_right++;
            direction = 3;
        }
        else if (direction == 3){
            for (int i = space_right; i <= space_left; i++){
                encrypted_sentence += cipher_matrix[space_up][i];
                counter++;
            }
            space_up++;
            direction = 0;
        }
    }
    cout << encrypted_sentence << endl << endl;

}


void route_cipher_decryption(){

    cout << "welcome to the route cipher decryption in order to decrypt some text you need to enter the secret key" << endl;
    cout << "and then enter the text you need to decrypt" << endl << endl;


    int secret_key;
    string encrypted_sentence;
    cout << "enter the secret key: ";
    cin >> secret_key;
    cout << "enter the sentence or word you want to decrypt: ";
    cin.ignore();
    getline(cin, encrypted_sentence);
    string striped_sentence = strip(encrypted_sentence);
    int number_of_rows = ceil(static_cast<float>(striped_sentence.length()) / static_cast<float>(secret_key));
    string cipher_matrix[number_of_rows][secret_key];
    int direction = 0;
    int space_down = number_of_rows-1;
    int space_up = 0;
    int space_left = secret_key-1;
    int space_right = 0;
    string decrypted_sentence;
    int counter = 0;
    while(counter < secret_key*number_of_rows){
        if(direction == 0){
            for (int i = space_up; i <= space_down; i++){
                cipher_matrix[i][space_left] = striped_sentence[counter];
                counter++;
            }
            space_left--;
            direction = 1;
        }
        else if (direction == 1){
            for (int i = space_left; i >= space_right ; i--){
                cipher_matrix[space_down][i] = striped_sentence[counter];
                counter++;
            }
            space_down--;
            direction = 2;
        }

        else if (direction == 2){
            for (int i = space_down; i >= space_up; i--){
                cipher_matrix[i][space_right] = striped_sentence[counter];
                counter++;
            }
            space_right++;
            direction = 3;
        }
        else if (direction == 3){
            for (int i = space_right; i <= space_left; i++){
                cipher_matrix[space_up][i] = striped_sentence[counter];
                counter++;
            }
            space_up++;
            direction = 0;
        }
    }
    for (int i = 0; i < number_of_rows; i++){
        for (int j = 0; j < secret_key; j++){
            decrypted_sentence += cipher_matrix[i][j];
        }
    }
    cout << decrypted_sentence << endl << endl;
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
            int cipher_choice;
            cout << "what cipher would you like to use?" << endl;
            cout << "1- polybius Square cipher" << endl;
            cout << "2- route cipher" << endl;
            cout << "3- rail-fence cipher" << endl;
            cout << "->";
            cin >> cipher_choice;
            while(true){
                if (cipher_choice == 1){ // for the polybius square cipher encryption.

                    break;
                }
                else if (cipher_choice == 2){
                    route_cipher_encryption();
                    break;
                }
                else if (cipher_choice == 3){ // for the rail-fence cipher.

                    break;
                }
                else{
                    cout << "please enter a valid choice" << endl;
                }
            }
        }

        else if (menu == "2"){
            int cipher_choice;
            cout << "what cipher would you like to use?" << endl;
            cout << "1- polybius Square cipher" << endl;
            cout << "2- route cipher" << endl;
            cout << "3- rail-fence cipher" << endl;
            cout << "->";
            cin >> cipher_choice;
            while(true){
                if (cipher_choice == 1){ // for the polybius square cipher decryption.

                    break;
                }
                else if (cipher_choice == 2){
                    route_cipher_decryption();
                    break;
                }
                else if (cipher_choice == 3){ // for the rail-fence cipher decryption.

                    break;
                }
                else{
                    cout << "please enter a valid choice" << endl;
                }
            }

        }

    }


}
