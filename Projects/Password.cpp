#include <iostream>
#include <sqlite3.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> //for std::ostringstream
#include <iomanip> //for std::setw, std::hex, and std::setfill
#include <openssl/conf.h>
#include <openssl/evp.h>//for all other OpenSSL function calls
#include <openssl/err.h>
#include <string.h> 
#include <openssl/sha.h> //for SHA512_DIGEST_LENGTH
using namespace std;

static void clearScreen();
static int getValidInt();
static int createDB(const char* s);
static int createTable(const char* s);
static int InsertData(const char* s);
static int selectData(const char* s);
static int callback(void* NotUsed, int argc, char** argv, char** azColName);
static int updateData(const char* s);
static int createDelete(const char* s);

unsigned char key[32] = { 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
                          0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35,
                          0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33,
                          0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31 };

unsigned char iv[16] = { 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
                         0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35 };


string encrypt(const string& plaintext, unsigned char* key, unsigned char* iv) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        cerr << "Failed to create cipher context" << endl;
        return "";
    }

    int len;
    int ciphertext_len;
    unsigned char ciphertext[128];

    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
    EVP_EncryptUpdate(ctx, ciphertext, &len, (unsigned char*)plaintext.c_str(), plaintext.length());
    ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;
    EVP_CIPHER_CTX_free(ctx);

    return string((char*)ciphertext, ciphertext_len);
}

string decrypt(const string& ciphertext, unsigned char* key, unsigned char* iv) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        cerr << "Failed to create cipher context" << endl;
        return "";
    }

    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
        cerr << "Failed to initialize decryption" << endl;
        EVP_CIPHER_CTX_free(ctx);
        return "";
    }

    unsigned char decrypttext[128];
    int len = 0, decrypt_len = 0;

    if (1 != EVP_DecryptUpdate(ctx, decrypttext, &len, (unsigned char*)ciphertext.c_str(), ciphertext.length())) {
        cerr << "Failed to decrypt" << endl;
        EVP_CIPHER_CTX_free(ctx);
        return "";
    }
    decrypt_len = len;

    if (1 != EVP_DecryptFinal_ex(ctx, decrypttext + len, &len)) {
        cerr << "Failed to finalize decryption" << endl;
        EVP_CIPHER_CTX_free(ctx);
        return "";
    }
    decrypt_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return string((char*)decrypttext, decrypt_len);
}

//helper function to print the digest bytes as a hex string
std::string bytes_to_hex_string(const std::vector<uint8_t>& bytes)
{
    std::ostringstream stream;
    for (uint8_t b : bytes)
    {
        stream << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(b);
    }
    return stream.str();
}

//perform the SHA3-512 hash
std::string sha3_512(const std::string& input)
{
    uint32_t digest_length = SHA512_DIGEST_LENGTH;
    const EVP_MD* algorithm = EVP_sha3_512();
    uint8_t* digest = static_cast<uint8_t*>(OPENSSL_malloc(digest_length));
    EVP_MD_CTX* context = EVP_MD_CTX_new();
    EVP_DigestInit_ex(context, algorithm, nullptr);
    EVP_DigestUpdate(context, input.c_str(), input.size());
    EVP_DigestFinal_ex(context, digest, &digest_length);
    EVP_MD_CTX_destroy(context);
    std::string output = bytes_to_hex_string(std::vector<uint8_t>(digest, digest + digest_length));
    OPENSSL_free(digest);
    return output;
}

int main() {
    fstream MyFile("C:\\Users\\Wei Jun\\Documents\\passcode.txt", ios::in); 

    if (!MyFile.is_open()) { 
        cerr << "Error: Could not open the file!" << endl;
        return 1;
    }
    string MPW;
    getline(MyFile, MPW);
    while (true) {
        string s;
        cout << "ENTER MASTER PASSWORD:";
        cin >> s;
        if (sha3_512(s) == MPW) {
            break;
        }
        cout << "\n";
    }
    const char* dir = "C:\\Users\\Wei Jun\\Documents\\DataBase.db";  
    sqlite3* DB = nullptr;

    createDB(dir);
    createTable(dir);




    while (true) {
        clearScreen();
        cout << "Welcome to Secure Password Manager" << endl;
        cout << "1. Add new credentials\n";
        cout << "2. View stored credentials\n";
        cout << "3. Update credentials\n";
        cout << "4. Delete credentials\n";
        cout << "5. Change master password\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: \n";
        int ans = getValidInt();
        while (ans < 1 || ans>6) {
            cout << "Please Insert a Valid Option" << endl;
            int ans = getValidInt();
        }
        if (ans == 1) {
            clearScreen();
            InsertData(dir);
        }
        else if (ans == 2) {
            clearScreen();
            selectData(dir);
            cout << "Press Enter to go back...";
            cin.ignore(); 
            cin.get();   
        }
        else if (ans == 3) {
            clearScreen();
            selectData(dir);
            updateData(dir);
        }
        else if (ans == 4) {
            clearScreen();
            selectData(dir);
            createDelete(dir);
        }
        else if (ans == 5) {
            string newp;
            cout << "New Master Password: ";
            cin >> newp;
            MyFile.close();
            ofstream outFile("C:\\Users\\Wei Jun\\Documents\\passcode.txt", ios::trunc);

            if (!outFile) {
                cerr << "Error: Could not open the file for writing!" << endl;
            }
            else {
                outFile << sha3_512(newp);
                outFile.close(); 
                cout << "Master password updated successfully!" << endl;
            }
        }
        else if (ans == 6) {
            break;
        }
    }
    MyFile.close();
    return 0;
}

static void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

static int updateData(const char* s) {
    sqlite3* DB;
    char* messageError;
    int exit = sqlite3_open(s, &DB);
    string ID;
    cout << "Enter ID: " << endl;
    cin >> ID;
    string password = "";

    while (password.length() < 8) {
        cout << "Please Insert your Password (Must have at least 8 characters)" << endl;
        cin >> password;
    }
    string encryptedPassword = encrypt(password, key, iv);

    string sql("UPDATE PASSWORDS SET PASSWORD = '" + encryptedPassword + "' WHERE ID ='" + ID + "'");

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cerr << "Error Insert" << endl;
        sqlite3_free(messageError);
    }
    else {
        cout << "Records created Successfully"<<endl;
    }
    return 0;
    
}

static int getValidInt() {
    int value;
    while (true) {
        cin >> value;
        if (cin.fail()) {
            cin.clear(); // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid input. Please enter a valid number: ";
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}


static int selectData(const char* s) {
    sqlite3* DB;
    int exit = sqlite3_open(s, &DB);
    if (exit != SQLITE_OK) {
        cerr << "Error opening database: " << sqlite3_errmsg(DB) << endl;
        return exit;
    }

    string sql = "SELECT ID, PROGRAM, USERNAME, PASSWORD FROM PASSWORDS;";
    sqlite3_stmt* stmt;

    exit = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);
    if (exit != SQLITE_OK) {
        cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << endl;
        sqlite3_close(DB);
        return exit;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        string program = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        string encryptedPassword = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        string decryptedPassword = decrypt(encryptedPassword, key, iv);

        cout << "ID: " << id << endl;
        cout << "Program: " << program << endl;
        cout << "Username: " << username << endl;
        cout << "Password: " << decryptedPassword << endl;
        cout << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);
    return 0;
}


static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << endl; 
    }
    cout << endl;
    return 0;
}

static int createDelete(const char* s) {
    sqlite3* DB;
    int exit = sqlite3_open(s, &DB);
    if (exit != SQLITE_OK) {
        cerr << "Error opening database: " << sqlite3_errmsg(DB) << endl;
        return exit;
    }

    string ID;
    cout << "Enter ID: ";
    cin >> ID;

    string ans;
    cout << "Are you sure you want to DELETE this? (y/n): ";
    cin >> ans;

    while (ans != "y" && ans != "n") {
        cout << "Invalid input. Are you sure you want to DELETE this? (y/n): ";
        cin >> ans;
    }

    if (ans == "n") {
        sqlite3_close(DB);
        return 0;
    }

    string sql = "DELETE FROM PASSWORDS WHERE ID = " + ID + ";"; 

    char* messageError = nullptr;
    exit = sqlite3_exec(DB, sql.c_str(), nullptr, 0, &messageError);

    if (exit != SQLITE_OK) {
        cerr << "Error deleting record: " << (messageError ? messageError : "Unknown error") << endl;
        sqlite3_free(messageError);
    }
    else {
        cout << "Record deleted successfully." << endl;
    }

    sqlite3_close(DB); 
    return 0;
}


static int InsertData(const char* s) {
    sqlite3* DB;
    char* messageError;
    int exit = sqlite3_open(s, &DB);
    string program;
    cout << "Please Insert Program Name" << endl;
    cin >> program;
    string username;
    cout << "Please Insert your Username" << endl;
    cin >> username;
    string password = "";
    while (password.length() < 8) {
        cout << "Please Insert your Password (Must have at least 8 characters)" << endl;
        cin >> password;
    }

    string encryptedPassword = encrypt(password, key, iv);

    string sql = "INSERT INTO PASSWORDS (PROGRAM, USERNAME, PASSWORD) VALUES('" + program + "', '" + username + "', '" + encryptedPassword + "');";
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cerr << "Error Insert" << endl;
        sqlite3_free(messageError);
    }
    else {
        cout << "Records created successfully" << endl;
    }
    return 0;
}


static int createDB(const char* s) {
    sqlite3* DB;
    int exit = sqlite3_open(s, &DB);
    if (exit != SQLITE_OK) {
        cerr << "Error opening database: " << sqlite3_errmsg(DB) << endl;
        sqlite3_close(DB);
        return exit;
    }

    return 0;
}

static int createTable(const char* s) {
    sqlite3* DB;

    string sql = "CREATE TABLE IF NOT EXISTS PASSWORDS ("
        "ID INTEGER PRIMARY KEY, "
        "PROGRAM TEXT NOT NULL, "
        "USERNAME TEXT NOT NULL, "
        "PASSWORD TEXT NOT NULL );";


    try {
        int exit = 0;
        exit = sqlite3_open(s, &DB);

        char* messageError;
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

        if (exit != SQLITE_OK) {
            cerr << "Error Create Table: " << (messageError ? messageError : "Unknown error") << endl;
            if (messageError) sqlite3_free(messageError); 
        }
        else {
            cout << "Table created Successfully" << endl;
        }
        sqlite3_close(DB);
    }
    catch (const exception& e) {
        cerr << e.what();
    }
    return 0;
}