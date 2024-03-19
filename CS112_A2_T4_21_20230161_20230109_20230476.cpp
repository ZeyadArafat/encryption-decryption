/*
File: CS112_A2_T4_21_20230161_20230109_20230476.cpp
Purpose: An encryption-decryption program with 10 different ciphers
Authors:
    Zeyad Mohamed Arafat - 20230161   s21   zeyadarafat833@gmail.com
    John Ayman Demian    - 20230109   s21   johnayman03@gmail.com
    Youssef Ahmed Beshir - 20230476   s21   youssefahmedbeshir@gmail.com

Zeyad Mohamed Arafat:
    Route Cipher
    Atbash Cipher
    Simple substitution Cipher
    Baconian Cipher

John Ayman Demian:
    Rail fence Cipher
    Affine Cipher
    Morse Code

Youssef Ahmed Beshir:
    Polybius square Cipher
    XOR Cipher
    Vignere Cipher
*/


#include <bits/stdc++.h>
using namespace std;


string strip(const string& sentence){
    // To remove spaces from text
    string strippedSentence;
    for(char i : sentence){
        if(i != ' '){
            strippedSentence += i;
        }
    }
    return strippedSentence;
}


// Baconian Cipher
void baconian_encryption(string textToEncrypt){
    string encryptedText = "";
    // Store the Baconian cipher mappings for each letter
    map<char, string> encryptionMap = {
            {'A', "aaaaa"}, {'B', "aaaab"}, {'C', "aaaba"}, {'D', "aaabb"}, {'E', "aabaa"}, {'F', "aabab"}, {'G', "aabba"},
            {'H', "aabbb"}, {'I', "abaaa"}, {'J', "abaab"}, {'K', "ababa"}, {'L', "ababb"}, {'M', "abbaa"}, {'N', "abbab"},
            {'O', "abbba"}, {'P', "abbbb"}, {'Q', "baaaa"}, {'R', "baaab"}, {'S', "baaba"}, {'T', "baabb"}, {'U', "babaa"},
            {'V', "babab"}, {'W', "babba"}, {'X', "babbb"}, {'Y', "bbaaa"}, {'Z', "bbaab"}};

    for (int i = 0; i < textToEncrypt.length(); i++){
        if (isalpha(textToEncrypt[i])){
            // Append the Baconian code for the corresponding uppercase letter to the encrypted text
            encryptedText += encryptionMap[toupper(textToEncrypt[i])];
        }
        else{
            // If the character is not an alphabet, append it to the encrypted text
            encryptedText += textToEncrypt[i];
        }

    }
    cout << encryptedText << endl << endl;
}


void baconian_decryption(string textToDecrypt){
    string decryptedText = "", code = "";
    // Store the Baconian cipher mappings for each code
    map<string, string > decryptionMap = {
            {"aaaaa", "A"}, {"aaaab", "B"}, {"aaaba", "C"}, {"aaabb", "D"}, {"aabaa", "E"}, {"aabab", "F"}, {"aabba", "G"},
            {"aabbb", "H"}, {"abaaa", "I"}, {"abaab", "J"}, {"ababa", "K"}, {"ababb", "L"}, {"abbaa", "M"}, {"abbab", "N"},
            {"abbba", "O"}, {"abbbb", "P"}, {"baaaa", "Q"}, {"baaab", "R"}, {"baaba", "S"}, {"baabb", "T"}, {"babaa", "U"},
            {"babab", "V"}, {"babba", "V"}, {"babbb", "X"}, {"bbaaa", "Y"}, {"bbaab", "Z"}};

    for (int i = 0; i < textToDecrypt.length(); i++){
        if (isalpha(textToDecrypt[i])){
            // Append the character to the code
            code += textToDecrypt[i];
            if (code.length() % 5 == 0 ){
                decryptedText += decryptionMap[code];
                code = "";
            }

        }
        else{
            // If the character is not an alphabet, simply append it to the decrypted text
            decryptedText += textToDecrypt[i];
        }

    }
    cout << decryptedText << endl << endl;
}



// XOR Cipher
bool isHexa(string message){
    message = strip(message);
    // Decrypted messages in hexa should only be length of even numbers
    if (message.length() % 2 != 0){
        cout << "Invalid message, try again" << endl;
        cout << "->";
        return false;
    }
    // Make sure that input is a valid hexadecimal number
    for(auto i: message){
        if((i < '0' || i > '9') && (i < 'A' || i > 'F')){
            cout << "Invalid Hexadecimal input, try again." << endl;
            cout << "->";
            return false;
        }
    }
    return true;
}


void xor_encryption(const string& message){
    string keyInput, key, output, hexaOutput;
    key = "";
    cout << "Welcome to the XOR cipher, a secret key of any number of characters (letters, digits) is required."
         << endl << endl;
    cout << "Enter the secret key" << endl;
    cout << "->";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, keyInput);

    // Setting the key, (Assigning each character in the message to the key).
    int counter = 0;
    for (int i = 0; i < message.length(); ++i) {
        if (counter == keyInput.length()){
            counter = 0;
        }
        key += keyInput[counter];
        counter++;
    }

    // Binary to hexadecimal map
    map <string, char> binary_to_hexa = {
            {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'},
            {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'},
            {"1000", '8'}, {"1001", '9'}, {"1010", 'A'}, {"1011", 'B'},
            {"1100", 'C'}, {"1101", 'D'}, {"1110", 'E'}, {"1111", 'F'}
    };

    for (int i = 0; i < message.length(); ++i) {
        // converting each character to its binary representation.
        bitset<8> binaryMsg (message[i]);
        bitset<8> binaryKey (key[i]);

        // Performing the XOR operation.
        bitset<8> xor_operation;
        xor_operation = binaryKey ^ binaryMsg;

        string binaryGroups, hexa;

        for (int j = 0; j < (xor_operation.to_string().length()); j += 4) {
            // converting each 4 bits to hexadecimal.
            binaryGroups = (xor_operation.to_string()).substr(j, 4);
            hexa = binary_to_hexa[binaryGroups];
            hexaOutput += hexa;
        }
        hexaOutput += " ";

        // converting binary back to characters.
        auto c = static_cast <char> (xor_operation.to_ulong());
        output += c;
    }

    cout << endl;
    cout << "Output: " << endl;
    cout << "- Plain text: " << output << endl;
    cout << "- Hexa: " << hexaOutput << endl << endl;
}


void xor_decryption(string message){
    // Checking validity
    while(!isHexa(message)){
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, message);
    }
    // Removing Spaces
    message = strip(message);
    string keyInput, key, output;
    key = "";

    cout << "Welcome to the XOR cipher, a secret key of any number of characters (letters, digits) is required."
         << endl << endl;
    cout << "Enter the secret key." << endl;
    cout << "->";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, keyInput);

    // Setting the key, (Assigning each character in the message to the key).
    int counter = 0;
    for (int i = 0; i < message.length(); ++i) {
        if (counter == keyInput.length()){
            counter = 0;
        }
        key += keyInput[counter];
        counter++;
    }

    // Hexa to binary map
    map <char, string> hexa_to_binary = {
            {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
            {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
            {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
            {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}
    };

    string hexa_group, binaryStr;
    int k = 0;
    for (int i = 0; i < message.length(); i += 2) {
        // Converting each two hexadecimal bits to binary
        hexa_group = message.substr(i, 2);

        for (char j : hexa_group) {
            binaryStr += hexa_to_binary[j];
        }

        bitset<8> binary(binaryStr);
        bitset<8> kk (key[k]);
        k++;

        binaryStr = "";
        // Performing the XOR operation
        bitset<8> xor_operation;
        xor_operation = binary ^ kk;
        // Converting back to characters
        auto c = static_cast <char> (xor_operation.to_ulong());
        output += c;
    }
    cout << "Message: " << output << endl << endl;
}


// Vignere Cipher
bool keyword_validity(const string& key){
    for(auto i : key){
        if(not isalpha(i)){
            cout << "Invalid key. Key should contain alphabetic letters only, try again" << endl;
            cout << "->";
            return false;
        }
    }

    if (key.length() > 8){
        cout << "Invalid key. Key cannot be more than 8 letters, try again" << endl;
        cout << "->";
        return false;
    }
    return true;
}


void vignere_encryption(string message){
    int ascii1 = 0, ascii2 = 0;
    string keyWordInput, keyWord, encrypted;
    char  encoding;
    encrypted = "";

    while(message.length() > 80){
        cout << "Invalid message. Messages cannot be more than 80 characters, try again";
        cout << "->";
        getline(cin, message);
    }

    cout << "Welcome to vignere Cipher, A key of 1 - 8 letters is required." << endl << endl;
    cout << "Enter the key word" << endl;
    cout << "->";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, keyWordInput);

    // Checking Validity
    while(not keyword_validity(keyWordInput)){
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, keyWordInput);
    }

    // Setting the key, (Assigning each character to the key)
    int counter = 0;
    for (int i = 0; i < message.length(); ++i) {
        if (counter == keyWordInput.length()){
            counter = 0;
        }
        keyWord += keyWordInput[counter];
        counter++;
    }

    for (int i = 0; i < message.length(); i++){
        if (!(isalpha(message[i]))){
            encrypted += message[i];
        }
        else{
            ascii1 = int(toupper(message[i]));
            ascii2 = int(toupper(keyWord[i]));
            encoding = char(((ascii2 + ascii1) % 26) + 65);
            encrypted += encoding;
            counter++;
        }
    }
    cout << "Encrypted message: " << encrypted << endl << endl;
}


void vignere_decryption(string message){
    int ascii1 = 0, ascii2 = 0;
    string keyWordInput, keyWord, decrypted;
    char decoding;
    decrypted = "";

    while(message.length() > 80){
        cout << "Invalid message. Messages cannot be more than 80 characters, try again" << endl;
        cout << "->";
        getline(cin, message);
    }

    cout << "Welcome to vignere Cipher, A key of 1 - 8 letters is required." << endl << endl;
    cout << "Enter the key word" << endl;
    cout << "->";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, keyWordInput);

    while(not keyword_validity(keyWordInput)){
        getline(cin, keyWordInput);
    }

    // Setting the key, (Assigning each character to the key)
    int counter = 0;
    for (int i = 0; i < message.length(); ++i) {
        if (counter == keyWordInput.length()){
            counter = 0;
        }
        keyWord += keyWordInput[counter];
        counter++;
    }

    for (int i = 0; i < message.length(); i++){
        if (!(isalpha(message[i]))){
            decrypted += message[i];
        }
        else{
            ascii1 = int(toupper(message[i]));
            ascii2 = int(toupper(keyWord[i]));
            decoding = char(((ascii1 - ascii2 + 26) % 26) + 65);
            decrypted += decoding;
            counter++;
        }
    }
    cout << "Message: "<< decrypted << endl << endl;
}


// Affine Cipher
// Function to calculate the modulo operation with positive numbers
int modulo(int a, int b) {
    return (a % b + b) % b;
}

// Function to encrypt text using the Affine Cipher
void encryptAffineCipher(const string& text) {
    // Check if the input text contains only letters and spaces
    bool valid_input = all_of(text.begin(), text.end(), [](char c) { return isalpha(c) || c == ' '; });
    if (!valid_input) {
        cout << "Input text contains non-letter characters other than spaces. Encryption cannot be performed." << endl;
        return;
    }
    // Map to store the affine characters
    map<char, int> affine_map = {
            {'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4},
            {'f', 5}, {'g', 6}, {'h', 7}, {'i', 8}, {'j', 9},
            {'k', 10}, {'l', 11}, {'m', 12}, {'n', 13}, {'o', 14},
            {'p', 15}, {'q', 16}, {'r', 17}, {'s', 18}, {'t', 19},
            {'u', 20}, {'v', 21}, {'w', 22}, {'x', 23}, {'y', 24},
            {'z', 25}
    };

    // Map to store the reverse mapping for decryption
    map<int, char> reverse_affine_map;
    for (const auto& pair : affine_map) {
        reverse_affine_map[pair.second] = pair.first;
    }
    // set variables
    string clear_text, cipher_text;
    int a, b, result;

    // Input loop for obtaining valid values of a and b
    while (true) {
        cout << "Enter (a, b): ";
        cin >> a >> b;

        // Check if both a and b are positive integers
        if (a > 0 && b > 0) {
            break; // Exit the loop if both are valid
        } else {
            cout << "Please enter positive numbers only." << endl;
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }
    }
    // Process the input text
    for (char i : text) {
        if (isalpha(i)) {
            clear_text += tolower(i); // Convert to lowercase
        }
    }

    // Apply the affine cipher and build the cipher text
    for (char i : clear_text) {
        result = (a * affine_map[i] + b) % 26;
        cipher_text += toupper(reverse_affine_map[result]); // Convert to uppercase
    }

    cout << "Cipher text: " << cipher_text << endl << endl;
}

// Function to decrypt text encrypted using the Affine Cipher
void decryptAffineCipher(const string& text) {
    // Check if the input text contains only letters and spaces
    bool valid_input = all_of(text.begin(), text.end(), [](char c) { return isalpha(c) || c == ' '; });
    if (!valid_input) {
        cout << "Input text contains non-letter characters other than spaces. Decryption cannot be performed." << endl;
        return;
    }

    // Your existing code remains unchanged below this point
    map<char, int> affine_map = {
            {'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4},
            {'f', 5}, {'g', 6}, {'h', 7}, {'i', 8}, {'j', 9},
            {'k', 10}, {'l', 11}, {'m', 12}, {'n', 13}, {'o', 14},
            {'p', 15}, {'q', 16}, {'r', 17}, {'s', 18}, {'t', 19},
            {'u', 20}, {'v', 21}, {'w', 22}, {'x', 23}, {'y', 24},
            {'z', 25}
    };

    map<int, char> reverse_affine_map;
    for (const auto& pair : affine_map) {
        reverse_affine_map[pair.second] = pair.first;
    }

    string clear_text, decipher_text;
    int b, c, result;

    while (true) {
        cout << "Enter (b, c): ";
        cin >> b >> c;

        if (b > 0 && c > 0) {
            break;
        } else {
            cout << "Please enter positive numbers only." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    for (char i : text) {
        if (isalpha(i)) {
            clear_text += tolower(i);
        }
    }

    for (char i : clear_text) {
        result = modulo(c * (affine_map[i] - b), 26);
        decipher_text += toupper(reverse_affine_map[result]);
    }

    cout << "Deciphered text: " << decipher_text << endl << endl;
}

// Polybius square Cipher
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
    cout << "Welcome to the polybius cipher, A key of numbers from 1 to 5 in any order is required" << endl << endl;
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

    cout << "Welcome to the polybius cipher, A key of numbers from 1 to 5 in any order is required" << endl << endl;
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

    cout << "Decrypted message --> "<< decrypted << endl << endl;
}



// Route Cipher
int route_key_validity(){
    // To make sure that the secret key of the route cipher is valid.
    int secretKey;
    cout << "Please enter the secret key: ";
    while (!(cin >> secretKey) || secretKey <= 0 ){
        cout << "Please enter a valid key (valid keys are integers bigger than 0)." << endl;
        cin.clear();
        cin.ignore();
    }
    return secretKey;
}


void route_cipher_encryption(const string& sentence_to_encrypt){

    // Explain to the user what he needs to do in order to encrypt the text.
    cout << "Welcome to the route cipher encryptedText in order to encrypt some text you need to choose a secret key" << endl << endl;

    int secretKey = route_key_validity();            // getting the secret key and checking its validity.

    int characterCounter = 0;                        // this counter will help create the matrix of the cipher.
    // stripping the text from any spaces.
    string strippedSentence = strip(sentence_to_encrypt);

    // calculating the number of rows in the matrix.
    int nRows = ceil(static_cast<float>(strippedSentence.length()) / static_cast<float>(secretKey));
    string cipherMatrix[nRows][secretKey];

    // filling the matrix with the character of the text.
    for(int i = 0; i < nRows; i++){
        for (int j = 0; j < secretKey; j++){
            if(characterCounter < strippedSentence.length()){
                cipherMatrix[i][j] = strippedSentence[characterCounter];
                characterCounter++;
            }
                // filling the rest of the matrix with x's.
            else {
                cipherMatrix[i][j] = "x";
            }
        }
    }

    // the rest of the function is for the spiral iteration.
    // there is a pattern in the iteration, you go down then left then up then right and repeat,
    // all inside the 2d array(matrix).
    int direction = 0;          // creating a direction variable to switch between directions.

    // four variables to indicate the start from each direction.
    int startDown = nRows - 1;
    int startUp = 0;
    int startRight = secretKey - 1;
    int startLeft = 0;

    string encryptedSentence;
    int counter = 0;            // the counter to stop the spiral iteration when done.

    while(counter < secretKey * nRows){
        if(direction == 0){ // direction 0 means going down in the matrix.
            // the start point is the top right corner [startUp][startRight].
            // while going down we are moving in the most right column (startRight)
            // and change the row index from 0(startUp) to (startDown).
            for (int i = startUp; i <= startDown; i++){
                encryptedSentence += cipherMatrix[i][startRight];
                counter++; // increasing the counter to stop the while loop.
            }
            startRight--; // changing the startRight value, so we don't get the same column when going down again.
            direction = 1; // changing the direction as planned in the iteration pattern.
        }
            // all the other loops work with the same logic.

        else if (direction == 1){       // direction 1 means going left in the matrix.
            for (int i = startRight; i >= startLeft; i--){
                encryptedSentence += cipherMatrix[startDown][i];
                counter++;
            }
            startDown--;
            direction = 2;
        }

        else if (direction == 2){       // direction 2 means going up in the matrix.
            for (int i = startDown; i >= startUp; i--){
                encryptedSentence += cipherMatrix[i][startLeft];
                counter++;
            }
            startLeft++;
            direction = 3;
        }

        else if (direction == 3){       // direction 3 means going right in the matrix.
            for (int i = startLeft; i <= startRight; i++){
                encryptedSentence += cipherMatrix[startUp][i];
                counter++;
            }
            startUp++;
            direction = 0;
        }
    }

    cout << encryptedSentence << endl << endl; // printing the encrypted text.

}


void route_cipher_decryption(const string& encrypted_sentence){

    // Explain to the user what he needs to do in order to decrypt the text.
    cout << "Welcome to the route cipher decryption in order to decrypt some text you need to enter the secret key" << endl << endl;


    int secretKey = route_key_validity();       // getting the secret key and checking its validity.
    string strippedSentence = strip(encrypted_sentence);    // stripping the text from any spaces.

    // calculating the number of rows in the matrix.
    int nRows = ceil(static_cast<float>(strippedSentence.length()) / static_cast<float>(secretKey));
    string cipherMatrix[nRows][secretKey];
    int direction = 0;// creating a direction variable to switch between directions.

    // four variables to indicate the start from each direction.
    int startDown = nRows - 1;
    int startUp = 0;
    int startRight = secretKey - 1;
    int startLeft = 0;

    string decrypted_sentence;
    int counter = 0;

    // filling the matrix with the character of the text in a spiral way.
    while(counter < secretKey * nRows){
        // the start point is the top right corner [startUp][startRight].
        // while going down we are moving in the most right column (startRight)
        // and change the row index from 0(startUp) to (startDown).
        if(direction == 0){
            for (int i = startUp; i <= startDown; i++){
                cipherMatrix[i][startRight] = strippedSentence[counter]; // adding the characters of the text to the matrix.
                counter++; // increasing the counter to stop the while loop.
            }
            startRight--; // changing the startRight value, so we don't get the same column when going down again.
            direction = 1; // changing the direction as planned in the iteration pattern.
        }
            // all the other loops work with the same logic.


        else if (direction == 1){ // direction 1 means going left in the matrix.
            for (int i = startRight; i >= startLeft; i--){
                cipherMatrix[startDown][i] = strippedSentence[counter];
                counter++;
            }
            startDown--;
            direction = 2;
        }

        else if (direction == 2){ // direction 2 means going up in the matrix.
            for (int i = startDown; i >= startUp; i--){
                cipherMatrix[i][startLeft] = strippedSentence[counter];
                counter++;
            }
            startLeft++;
            direction = 3;
        }

        else if (direction == 3){ // direction 3 means going right in the matrix.
            for (int i = startLeft; i <= startRight; i++){
                cipherMatrix[startUp][i] = strippedSentence[counter];
                counter++;
            }
            startUp++;
            direction = 0;
        }
    }

    // reading the characters in the matrix in the right order.
    for (int i = 0; i < nRows; i++){
        for (int j = 0; j < secretKey; j++){
            decrypted_sentence += cipherMatrix[i][j]; // adding characters to the decrypted sentence
        }
    }
    cout << decrypted_sentence << endl << endl; // printing the decrypted text
}


// Morse code Cipher
void morse_code_cipher(const string& text) {
    // set morse map
    map <char , string>  morse_cipher = {
            {'a' , ".-"}, {'b' , "-..."}, {'c' , "-.-."} ,{'d' , "-.."} , {'e',"."} ,
            {'f' , "..-." },{'g' , "--."} , {'h',"...."},{'i',".."}, {'j',".---"} , {'k',"-.-" },
            {'l',".-.."},{'m',"--"},{'n' , "-."},{'o',"---"},{'p',".--."},{'q',"--.-"},
            {'r' , ".-."} , {'s' , "..."} , {'t' , "-" } , {'u',"..-" } , {'v',"...-" } , {'w',".--" } ,
            {'x' , "-..-" } , {'y',"-.--" } , {'z',"--.."},{'1',".----"},{'2',"..---"},{'3',"...--"},
            {'4',"....-"},{'5',"....."},{'6',"-...."},{'7',"--..."},{'8',"---.."},{'9',"----."},{'0',"-----"} } ;
    // set main variables
    string clear_text , cipher_text;
    cipher_text = "" ;
    // check input validation
    for (char i : text)
    {
        // clear text to contain only letters and numbers
        if(isalpha(i) || isdigit(i)){
            clear_text += tolower(i) ;
            // If the character is a space
        } else if (i == ' ') {
            // Add a space to the clear_text directly
            clear_text += " ";
        }
    }
    // collect char
    for (char i : clear_text)
    {
        if (i == ' ') {
            cipher_text += "   "; // Add three spaces for word separation
        } else {
            cipher_text += morse_cipher[i]; // Add Morse code for the current character
            cipher_text += " "; // Add one space between letters
        }
    }
    // print result
    if (cipher_text == ""){
        cout << "The entered text contains only special charcters can not ciphered ,pls enter letters or numbers. "<< endl << endl;
    } else

        cout <<"ciphered text : " <<cipher_text << endl << endl;
}

void morse_code_decipher(const string& text) {
    bool valid_input = all_of(text.begin(), text.end(), [](char c) {
        return  c == ' ' || c == '.' || c == '-';
    });

    if (!valid_input) {
        cout << "Input text not contains spaces, periods, or hyphens. Encryption cannot be performed." << endl;
        return;
    }
    // set the morse table
    map<string, char> morse_decipher = {
            {".-", 'a'}, {"-...", 'b'}, {"-.-.", 'c'}, {"-..", 'd'}, {".", 'e'},
            {"..-.", 'f'}, {"--.", 'g'}, {"....", 'h'}, {"..", 'i'}, {".---", 'j'}, {"-.-", 'k'},
            {".-..", 'l'}, {"--", 'm'}, {"-.", 'n'}, {"---", 'o'}, {".--.", 'p'}, {"--.-", 'q'},
            {".-.", 'r'}, {"...", 's'}, {"-", 't'}, {"..-", 'u'}, {"...-", 'v'}, {".--", 'w'},
            {"-..-", 'x'}, {"-.--", 'y'}, {"--..", 'z'}, {".----", '1'}, {"..---", '2'}, {"...--", '3'},
            {"....-", '4'}, {".....", '5'}, {"-....", '6'}, {"--...", '7'}, {"---..", '8'}, {"----.", '9'}, {"-----", '0'}};
    // set main variables
    string decipher_text, morse_char;
    decipher_text = "";
    // make for loop to check validation of input
    for (char i : text) {
        //if text contain (. , -) add it to convert
        if (i == '.' || i == '-') {
            morse_char += i;
            // if space add it to separation
        } else if (i == ' ') {
            if (!morse_char.empty()) {
                // convert all char
                decipher_text += morse_decipher[morse_char];
                morse_char = "";
            } else {
                decipher_text += " "; // Add space for word separation
            }
        }
    }
    // check all char converted
    if (!morse_char.empty()) {
        decipher_text += morse_decipher[morse_char];
    }
    // print result
    cout <<"deciphered text : " <<decipher_text << endl << endl;
}


// Rail fence Cipher
void rail_Fence_Encrypt(const string& message) {
    // check validation of the entered text contain letters to cipher and ignore others
    int letter_count = count_if(message.begin(), message.end(), [](char c) {
        return isalpha(c);
    });
    if (letter_count == 0) {
        cout << "Input text must contain at least one letter. Encryption cannot be performed." << endl;
        return;
    }
    // set main variables
    string clear_text = message,text, key, encryptedText;
    int num;
    // this loop to clear text from non-alphabetic letters before start
    for (char i : clear_text) {
        if (isalpha(i)){
            text += i ;
        }
    }
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
    if (num == 3) {
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
    string clear_text = message,text, key, decryptedText;
    int num;
    // this loop to remove non-alphabetic letters from text before start
    for (char i : clear_text) {
        if (isalpha(i)){
            text += i ;
        }
    }
    // print welcome message
    cout << "welcome to Rail Fence encrypt program " << endl;
    // let user choose the key
    cout << "please choose the key 3 or 4: " ;
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
        decryptedText.resize(len);
        int pos = 0;
        //make for loop to iterates in the text
        for (int i = 0; i < 3 ; ++i) {
            int index = i;
            // put flag
            bool down = true;
            while (index < len) {
                decryptedText[index] = text[pos++];
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
        if (decryptedText == ""){
            cout <<"The encrypted text you entered not contains any letter to be deciphered,pls enter valid text " << endl << endl ;
        } else
            cout << "Decrypt text is :  " << decryptedText << endl ;
    }
    else if (num == 4) {
        int len = text.length();
        // set decrypt text with len = len of clear text
        decryptedText.resize(len);
        int pos = 0;
        //make for loop to iterates in the text
        for (int i = 0; i < 4 ; ++i) {
            int index = i;
            // put flag
            bool down = true;
            while (index < len) {
                decryptedText[index] = text[pos++];
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
        if (decryptedText == ""){
            cout << "The encrypted text you entered not contains any letter to be deciphered , pls enter valid text : " << endl << endl ;
        } else
            cout << "Decrypt text is :  " << decryptedText << endl ;
    }
}


// Simple substitution Cipher
string lower_case(string key){
    for (char & i : key){
        i = tolower(i);
    }
    return key;
}


bool simpleSub_Key_Validity(const string& key){
    // check the validity of the simple substitution key.
    for (char i : key) {
        if (!isalpha(i))return false;
    }
    return true;
}


string complete_simple_sub_Key(string key){
    // complete the key of the simple substitution cipher if needed.
    string alpha = "abcdefghijklmnoprqstuvwxyz";
    int letterIndex;
    for (char i : key) {
        // iterate through the given key and remove it from the alpha.
        letterIndex = alpha.find(tolower(i));
        alpha.erase(alpha.begin()+letterIndex);
    }
    // add the remaining alpha to the key.
    key += alpha;
    return key;
}


void simple_sub_encryption(const string& textToEncrypt){
    // Welcome message with explanation
    cout << "Welcome to the simple substitution encryption, in order to get your text encrypted you need to enter a secret key" << endl;
    cout << "the key is any sequence of alphabetic characters (maximum 25 character)" << endl;
    string key, encryptedText;
    encryptedText = "";
    string alpha = "abcdefghijklmnoprqstuvwxyz";
    int encryptionIndex;

    cout << "please enter a secret key: ";
    cin >> key;
    key = lower_case(key);

    // Checking validity
    while (!(simpleSub_Key_Validity(key))){
        cout << "please enter a valid key" << endl;
        cin >> key;
    }

    if (simpleSub_Key_Validity(key)) {
        if (key.length() < 25) {
            // If key length is less than 25, complete the key with remaining alphabet characters
            key = complete_simple_sub_Key(key);
        }
        for (char i : textToEncrypt) {
            if (isalpha(i)){
                // Find index of character in the alphabet
                encryptionIndex = alpha.find(tolower(i));
                // Encrypt the character using the key
                encryptedText += key[encryptionIndex];
            }
            else{
                // If character is not an alphabet, add it to the encrypted text
                encryptedText += i;
            }
        }
    }
    cout << encryptedText << endl << endl;
}


void simple_sub_decryption(const string& textToDecrypt){
    // Welcome message with explanation
    cout << "welcome to the simple substitution decryption, in order to get your text decrypted you need to enter the secret key" << endl;
    cout << "the key is any sequence of alphabetic characters (maximum 25 character)" << endl;
    string key, encryptedText;
    encryptedText = "";
    string alpha = "abcdefghijklmnoprqstuvwxyz";
    int decryptionIndex;

    cout << "please enter the secret key: ";
    cin >> key;
    key = lower_case(key);

    while (!(simpleSub_Key_Validity(key))){
        cout << "please enter a valid key" << endl;
        cin >> key;
    }

    if (simpleSub_Key_Validity(key)) {
        if (key.length() < 25) {
            // If key length is less than 25, complete the key with remaining alphabet characters
            key = complete_simple_sub_Key(key);
        }
        for (char i : textToDecrypt) {
            if (isalpha(i)){
                // Find index of character in the alphabet
                decryptionIndex = key.find(tolower(i));
                encryptedText += alpha[decryptionIndex];
            }
            else{
                // If character is not an alphabet, add it to the encrypted text
                encryptedText += i;
            }
        }
    }
    cout << encryptedText << endl << endl;
}


// Atbash Cipher
bool atbash_key_validity(const string& key){
    // Checking the validity of the atbash key.
    if((key == "2") or (key == "4")) return true;
    return false;
}


void atbash_encryption(string textToEncrypt){
    // explain the cipher to the user.
    cout << "Welcome to atbash encryption, in order to get some text encrypted you need to enter a secret key" << endl;
    cout << "valid keys are (2, 4)" << endl;
    string key, encryptedText;
    encryptedText = "";

    cout << "please enter a secret key: ";
    cin >> key; // get the key form user.

    while (!atbash_key_validity(key)){ // check the validity of the key (if not valid ask the user to input it again).
        cout << "please enter a valid key" << endl;
        cin >> key;
    }

    if (key == "2"){ // if the key is "2", split the alphabet to two halfs.
        string firstAlpha = "ABCDEFGHIJKLM", secondAlpha = "ZYXWVUTSRQPON";
        for (char i : textToEncrypt){ // iterate through each character of the text.
            if (isalpha(i)){ // if the character is alpha search for it in one of the halfs and get its index.
                if (int(toupper(i)) <= 77){
                    int letterIndex = firstAlpha.find(toupper(i));
                    // add the same index from the other half.
                    encryptedText += secondAlpha[letterIndex];
                }
                else{
                    int letterIndex = secondAlpha.find(toupper(i));
                    encryptedText += firstAlpha[letterIndex];
                }
            }
            else{// if the character is not alpha leave it as it is.
                encryptedText += i;
            }
        }

    }
    else if (key == "4"){ // if the key is "4", split the alphabet to four parts.
        // the same logic goes for the key "4" as in the key "2".
        string firstAlpha = "ABCDEF", secondAlpha = "MLKJIH", thirdAlpha = "NOPQRS", fourthAlpha = "ZYXWVU";
        for (int i = 0; i < textToEncrypt.length(); i++){
            if (isalpha(textToEncrypt[i])){
                if (int(toupper(textToEncrypt[i])) > 84){
                    int letterIndex = fourthAlpha.find(toupper(textToEncrypt[i]));
                    encryptedText += thirdAlpha[letterIndex];
                }
                else if (int(toupper(textToEncrypt[i])) == 84){
                    encryptedText += "T";
                }
                else if (int(toupper(textToEncrypt[i])) > 77){
                    int letterIndex = thirdAlpha.find(toupper(textToEncrypt[i]));
                    encryptedText += fourthAlpha[letterIndex];
                }
                else if (int(toupper(textToEncrypt[i])) > 71){
                    int letterIndex = secondAlpha.find(toupper(textToEncrypt[i]));
                    encryptedText += firstAlpha[letterIndex];
                }
                else if (int(toupper(textToEncrypt[i])) == 71){
                    encryptedText += "G";
                }
                else if (int(toupper(textToEncrypt[i])) < 71){
                    int letterIndex = firstAlpha.find(toupper(textToEncrypt[i]));
                    encryptedText += secondAlpha[letterIndex];
                }
            }
            else{
                encryptedText += textToEncrypt[i];
            }

        }

    }
    cout << encryptedText << endl << endl;
}


void atbash_decryption(string textToDecrypt){
    // this is the same as the encryption function, but the printed messages are diffrent.
    cout << "Welcome to atbash decryption, in order to get some text decrypted you need to enter the secret key" << endl;
    cout << "valid keys are (2, 4)" << endl;
    string key, decryptedText;
    decryptedText = "";

    cout << "please enter a secret key: ";
    cin >> key;

    while (!atbash_key_validity(key)){
        cout << "please enter a valid key" << endl;
        cin >> key;
    }

    if (key == "2"){
        string firstAlpha = "ABCDEFGHIJKLM", secondAlpha = "ZYXWVUTSRQPON";
        for (char i : textToDecrypt){
            if (isalpha(i)){
                if (int(toupper(i)) <= 77){
                    int letterIndex = firstAlpha.find(toupper(i));
                    decryptedText += secondAlpha[letterIndex];
                }
                else
                {
                    int letterIndex = secondAlpha.find(toupper(i));
                    decryptedText += firstAlpha[letterIndex];
                }
            }
            else{
                decryptedText += i;
            }
        }

    }
    else if (key == "4"){
        string firstAlpha = "ABCDEF", secondAlpha = "MLKJIH", thirdAlpha = "NOPQRS", fourthAlpha = "ZYXWVU";
        for (int i = 0; i < textToDecrypt.length(); i++){
            if (isalpha(textToDecrypt[i])){
                if (int(toupper(textToDecrypt[i])) > 84){
                    int letterIndex = fourthAlpha.find(toupper(textToDecrypt[i]));
                    decryptedText += thirdAlpha[letterIndex];
                }
                else if (int(toupper(textToDecrypt[i])) == 84){
                    decryptedText += "T";
                }
                else if (int(toupper(textToDecrypt[i])) > 77){
                    int letterIndex = thirdAlpha.find(toupper(textToDecrypt[i]));
                    decryptedText += fourthAlpha[letterIndex];
                }
                else if (int(toupper(textToDecrypt[i])) > 71){
                    int letterIndex = secondAlpha.find(toupper(textToDecrypt[i]));
                    decryptedText += firstAlpha[letterIndex];
                }
                else if (int(toupper(textToDecrypt[i])) == 71){
                    decryptedText += "G";
                }
                else if (int(toupper(textToDecrypt[i])) < 71){
                    int letterIndex = firstAlpha.find(toupper(textToDecrypt[i]));
                    decryptedText += secondAlpha[letterIndex];
                }
            }
            else{
                decryptedText += textToDecrypt[i];
            }

        }

    }
    cout << decryptedText << endl << endl;
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
            cout << "0- Affine cipher" << endl ;
            cout << "1- Route cipher" << endl;
            cout << "2- Atbash cipher" << endl;
            cout << "3- Vignere cipher" << endl;
            cout << "4- Baconian cipher" << endl;
            cout << "5- Simple substitution cipher" << endl;
            cout << "6- Polybius Square cipher" << endl;
            cout << "7- Morse code cipher" << endl;
            cout << "8- XOR cipher" << endl;
            cout << "9- Rail-fence cipher" << endl;
            cout << "->";

            string cipherChoice;
            cin >> cipherChoice;

            while(true){
                if (cipherChoice == "0"){
                    encryptAffineCipher(message);
                    break;
                }
                else if (cipherChoice == "1"){
                    route_cipher_encryption(message);
                    break;
                }
                else if (cipherChoice == "2"){
                    atbash_encryption(message);
                    break;
                }
                else if (cipherChoice == "3"){
                    vignere_encryption(message);
                    break;
                }
                else if (cipherChoice == "4"){
                    baconian_encryption(message);
                    break;
                }
                else if (cipherChoice == "5"){
                    simple_sub_encryption(message);
                    break;
                }
                else if (cipherChoice == "6"){
                    polybius_square_encryption(message);
                    break;
                }
                else if (cipherChoice == "7"){
                    morse_code_cipher(message);
                    break;
                }
                else if (cipherChoice == "8"){
                    xor_encryption(message);
                    break;
                }
                else if (cipherChoice == "9"){
                    rail_Fence_Encrypt(message);
                    break;
                }
                else{
                    cout << "Please enter a valid choice" << endl << endl;
                    break;
                }
            }
        }

        else if (menu == "2"){
            cout << "Please enter the message to decipher." << endl;
            cout << "->";

//            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, encrypted);

            cout << "What cipher would you like to use?" << endl;
            cout << "0- Affine cipher" << endl ;
            cout << "1- Route cipher" << endl;
            cout << "2- Atbash cipher" << endl;
            cout << "3- Vignere cipher" << endl;
            cout << "4- Baconian cipher" << endl;
            cout << "5- Simple substitution cipher" << endl;
            cout << "6- Polybius Square cipher" << endl;
            cout << "7- Morse code cipher" << endl;
            cout << "8- XOR cipher" << endl;
            cout << "9- Rail-fence cipher" << endl;
            cout << "->";

            string cipher_choice;
            cin >> cipher_choice;

            while(true){
                if (cipher_choice == "0"){
                    decryptAffineCipher(encrypted);
                    break;
                }
                else if (cipher_choice == "1"){
                    route_cipher_decryption(encrypted);
                    break;
                }
                else if (cipher_choice == "2"){
                    atbash_decryption(encrypted);
                    break;
                }
                else if (cipher_choice == "3"){
                    vignere_decryption(encrypted);
                    break;
                }
                else if (cipher_choice == "4"){
                    baconian_decryption(encrypted);
                    break;
                }
                else if (cipher_choice == "5"){
                    simple_sub_decryption(encrypted);
                    break;
                }
                else if (cipher_choice == "6"){
                    polybius_square_decryption(encrypted);
                    break;
                }
                else if (cipher_choice == "7"){
                    morse_code_decipher(encrypted);
                    break;
                }
                else if (cipher_choice == "8"){
                    xor_decryption(encrypted);
                    break;
                }
                else if (cipher_choice == "9"){
                    rail_Fence_Decrypt(encrypted);
                    break;
                }
                else{
                    cout << "Please enter a valid choice" << endl << endl;
                    break;
                }
            }
        }
        else{
            cout << "Invalid choice." << endl << endl;
        }
    }
}
