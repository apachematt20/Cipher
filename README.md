# RC4 File Encryptor/Decryptor

A lightweight, efficient, and easy-to-use command-line utility written in C for encrypting and decrypting files using the **RC4 (Rivest Cipher 4)** stream cipher algorithm.

⚠️ **Security Disclaimer:** *The RC4 algorithm is historically significant but is now considered cryptographically broken and vulnerable to multiple attacks. This project is intended strictly for **educational purposes** and understanding how stream ciphers and the XOR operation work. Do not use this tool to secure sensitive data in modern production environments.*

# RC4 File Encryptor/Decryptor

A lightweight, efficient, and easy-to-use command-line utility written in C for encrypting and decrypting files using the **RC4 (Rivest Cipher 4)** stream cipher algorithm.

⚠️ **Security Disclaimer:** *The RC4 algorithm is historically significant but is now considered cryptographically broken and vulnerable to multiple attacks. This project is intended strictly for **educational purposes** and understanding how stream ciphers and the XOR operation work. Do not use this tool to secure sensitive data in modern production environments.*

## ✨ Features

* **Symmetric Cipher:** Uses the exact same algorithm and command to encrypt and decrypt files.
* **Memory Efficient:** Processes files in 4KB chunks, meaning it can safely encrypt/decrypt massive files (e.g., large videos or archives) without exhausting your system's RAM.
* **Universal Support:** Opens files in binary mode (`rb`/`wb`), ensuring it works flawlessly with any file type (text documents, images, executables, PDFs, etc.).
* **Safety First:** Includes a built-in safeguard to prevent users from accidentally overwriting and wiping their input files by using the same name for both input and output.

## 🚀 Getting Started

### Prerequisites
You only need a standard C compiler (like `gcc` or `clang`) installed on your system. No external libraries are required.

### Compilation
Clone the repository and compile the source code using `gcc`:

```bash
git clone https://github.com/apachematt20/Cipher.git
cd Cipher
gcc -O3 rc4_crypto.c -o rc4_crypto
(The -O3 flag is optional but recommended to optimize the execution speed).

📖 Usage
The tool requires exactly three arguments: the input file, the desired output file name, and your secret password.

Bash
./rc4_crypto <input_file> <output_file> <password>
Examples

1. Encrypting a file:
Let's say you have a file named secret.txt and want to encrypt it.

Bash
./rc4_crypto secret.txt encrypted.bin "MySuperSecretPassword!"
2. Decrypting a file:
To get your original file back, simply run the tool again, using the encrypted file as the input and providing the exact same password.

Bash
./rc4_crypto encrypted.bin decrypted.txt "MySuperSecretPassword!"
```

## Important Notes

File Overwriting: The program will intentionally block you if <input_file> and <output_file> are the same to prevent data loss. Always specify a new name for the output.

Wrong Passwords: RC4 does not check for password correctness. If you supply the wrong password during decryption, the program won't throw an error; instead, it will output scrambled, unreadable data. Enclose your password in single or double quotes to prevent the terminal from misinterpreting special characters.

## 🧠 How It Works (Technical Overview)
This tool implements the standard RC4 algorithm logic:

Key-Scheduling Algorithm (KSA): The tool initializes a 256-byte state array (S-box) using your provided password.

Pseudo-Random Generation Algorithm (PRGA): It continuously modifies the state array to generate a pseudo-random stream of bytes (the keystream).

XOR Operation: The keystream is logically XORed (^) byte-by-byte with the input file. Because (Data XOR Key) XOR Key = Data, the same code handles both encryption and decryption.

## 📄 License
This project is open-source and available under the MIT License.
