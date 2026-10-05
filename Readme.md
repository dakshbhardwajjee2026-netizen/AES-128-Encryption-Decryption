# Project:-  AES + Vigenere Encryption/Decryption with dual input mode

# This a c-program that demonstrates AES-128  block encryption and decryption alon with basic cypher implmentation like Vigenere encryption/decryption without using any external libraries all the operations and functions have been written in this project only using functions. 

The project basically has 5 layers:-
1) **CLI**: command line interface where main() reads the user command using argc and argv, validates it, chooses AES or Vigenère, and chooses file or string mode as instructed in the problem statement.
2) **Data Represting Layer**: This includes processing the input and arrange it according to the requirements of the algorithm like handling padding then binary to hex and hex to binary conversion
3) **AES Logic Layer**: 16 byte blocks is transformed to a matrix called state which is moved through multiple operations such as SubBytes,ShiftRows,Mix COlumns,AddRoundKey, Key Expansion repetedly for 10 rounds with 11 modified keys(176 bytes).
4) **File/String Handling**: After the logic of encryption and decryption the mode of input output is handled according to the command given by the user if the string is given then the processes are handled in memory and if the file mode is selected then the operations are handled through file handling in c and fgetc,fputc,fopen,fclose functions.
5) **Vigenere**:- This is a basic cipher technique in which letters are shifted by repeating keyletters. Non-letters are copied unchanged and do not consume a key-character. It is basically a logical Reasoning based technique to encode and decode a file or string.


# Command Line Guide:-
The basic structure of the command that can be provided to this program is:- 

**encrypt/decrypt aes file <input_file> <output_file> <32-char-hex-key>**
**encrypt/decrypt aes string <text> - <32-char-hex-key>**
**encrypt/decrypt vigenere file <input_file> <output_file> <key>**
**encrypt/decrypt vigenere string <text> - <key>**

The input and output file both are txt, first the aes logic layer gives the binary output but it is converted to the hex string through bit operations.


# Scope of Improvements:- 
1) I have missed the error handling part like if the file is not loaded properly then what to do as I could not able to figure out how to do error handling in c.
2) I have directly added the s_box and inverse s_box table as they were publicly avaiable for lookup operations but I studied that this can also be mathematically evaluated.
3) The codebase can be organised in a better way with proper sequence of functions
4) I have tested it with many examples but may have skipped some edge cases and these edge cases should be handles with proper error handling.


# Learnings:-
1) Project helped me to enter into the cryptography domain which was very difficult for me
2) Helped me to understand bitwise manipulation deeply which was my weaker point earlier
3) Learnt file handling in c which was new for me in comparison to python
4) Learrnt to handle unknown situations by researching about the topic and working behind it.
