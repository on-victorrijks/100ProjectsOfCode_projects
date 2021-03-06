#include <iostream>
#include <stdio.h>
#include <string> 
#include <ctype.h>
using namespace std;

string alphabet = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
const char* algorithms[2] = { "Caesar", "RSA" };


// Global functions
int letterPosition(string elements, char element) {

	int position = -1;
	int n = elements.length();
	int i = 0;
	while (i < n)
	{
		if (elements[i] == element) {
			position = i;
			break;
		}
		i++;
	}

	return position;
}

bool isPrime(int n){
	// FROM : https://www.geeksforgeeks.org/c-program-to-check-prime-number/
	// Corner cases 
	if (n <= 1)
		return false;
	if (n <= 3)
		return true;

	// This is checked so that we can skip 
	// middle five numbers in below loop 
	if (n % 2 == 0 || n % 3 == 0)
		return false;

	for (int i = 5; i * i <= n; i = i + 6)
		if (n % i == 0 || n % (i + 2) == 0)
			return false;

	return true;
}

int getPrime(int except) {
	while (true) {
		int r = rand();
		if (isPrime(r) && except != r) {
			return r;
		}
	}
}

int getGCM(int n1, int n2){
	if (n1 == 0) {
		return n2;
	}
	return getGCM(n2 % n1, n1);
}

int getD(int e, int lcm) {
	for (int d = 0;; d++){
		if ((d * e) % lcm == 1) {
			return d;
		}
	}
}

int getLCM(int n1, int n2) {
	return abs(n1 * n2) / getGCM(n1, n2);
}

bool e_verificator(int e, int lcm) {
	if (1 < e && getGCM(e, lcm) == 1) {
		return true;
	}
	return false;
}

int getE(int lcm) {
	// find e
	// 1 < e < lcm
	// gcd( e, lcm ) == 1
	// e and lcm are coprime
	int potential;
	while (true) {
		potential = getPrime(lcm);
		if (e_verificator(potential, lcm)) {
			return potential;
		}
	}

}

// RSA
string rsa_encrypt(int n, int e, string text) {
	
	// Letters to numbers (11 to correct 00 mistakes)
	std::string formattedText = "11";


	for (char const& c : text) {
		int position = letterPosition(alphabet, c);

		if (position < 10) {
			formattedText += '0';
		}
		formattedText += std::to_string(position);

	}

	cout << formattedText << endl;


	// GMP Implementation necessary
	int formattedText_int = std::stol(formattedText);

	int encryptedText_int = fmod(pow(formattedText_int, e), n);

	cout << encryptedText_int << endl;

	return "";

}


// Caesar

string cipher_substitution(float decrypt, string text, int decal) {

	string result = "";

	for (char const& c : text) {

		int position = letterPosition(alphabet, c);

		if (position != -1) {
			int maxPosition = 26;
			int minPosition = 0;

			int tempPosition = position + decal;

			while ((tempPosition - maxPosition) > 0) {
				tempPosition -= maxPosition;
			}

			while (tempPosition < minPosition) {
				tempPosition += maxPosition;
			}

			char newLetter = alphabet[tempPosition];
			result += newLetter;
		}
		else {
			result += c;
		}

	}

	return result;
}

// RSA



void welcome() {
	cout << "Codec Software V1.0" << endl;
	cout << "Victor Rijks 2020" << endl;
}

void showAlgorithms() {
	for (int i = 0; i < 2; i++) {
		cout << i;
		cout << ": ";
		cout << algorithms[i] << endl;
	}
}

int main() {

	int chosenAlgoIndex;
	char shouldDecryptLetter;
	char shouldGenerateNewKeysLetter;
	string enteredText;
	int numberOfAlgorithms = sizeof(algorithms) / sizeof(algorithms[0]);
	float shouldDecrypt = false;
	float shouldGenerateNewKeys = false;
	bool run_main = true;
	srand(time(NULL));


	if (run_main) {

		welcome();
		showAlgorithms();

		// User choses algorithm
		while (true) {
			cout << "Enter the chosen algorithm index: ";
			cin >> chosenAlgoIndex;

			if (chosenAlgoIndex < numberOfAlgorithms && chosenAlgoIndex >= 0) {
				break;
			}
		}

		// User choses if he wants to encrypt/decrypt
		while (true) {
			cout << "Do you want to encrypt a text ? (Y/N): ";
			cin >> shouldDecryptLetter;

			if (shouldDecryptLetter == 'Y') {
				shouldDecrypt = false;
				break;
			}
			else if (shouldDecryptLetter == 'N') {
				shouldDecrypt = true;
				break;
			}
		}

		// User enters text
		cout << "Enter the text: ";
		cin.ignore();
		getline(cin, enteredText);

		// lower enteredText
		for (int i = 0; i < enteredText.length(); i++) {
			enteredText[i] = tolower(enteredText[i]);
		}

		// Main program

		string chosenAlgo_str = algorithms[chosenAlgoIndex];
		string result = "";

		if (chosenAlgo_str == "Caesar") {

			// Offset
			int decal_encryption = 0;
			cout << "Offset: ";
			cin >> decal_encryption;


			if (shouldDecrypt) {
				decal_encryption = -decal_encryption;
			}

			result = cipher_substitution(shouldDecrypt, enteredText, decal_encryption);

		}
		else if (chosenAlgo_str == "RSA") {

			if (shouldDecrypt) {
				// Decrypt RSA message
			} else {
				// Generate Public and private keys

				// User choses if he wants to generate keys
				while (true) {
					cout << "Do you want to generate new keys ? (Y/N): ";
					cin >> shouldGenerateNewKeysLetter;

					if (shouldGenerateNewKeysLetter == 'Y') {
						shouldGenerateNewKeys = true;
						break;
					}
					else if (shouldGenerateNewKeysLetter == 'N') {
						shouldGenerateNewKeys = false;
						break;
					}
				}

				if (shouldGenerateNewKeys) {
					// Generate new keys
					int p, q, n, keyLength, lcm, e, d;

					p = getPrime(-1);
					q = getPrime(p);
					n = p * q;
					lcm = getLCM((p - 1), (q - 1));
					e = 65537;
					if (!e_verificator(e, lcm)) {
						e = getE(lcm);
					}
					d = getD(e, lcm);

					cout << "Public KEY:" << endl;
					cout << "n: " << n << endl;
					cout << "e: " << e << endl;
					cout << "Private KEY:" << endl;
					cout << "d: " << d << endl;

				}

				if (shouldDecrypt) {
					// decrypt 
					// enter private key
					// output decrypted message
				} else {
					// encrypt

					// User enters n & e (public key)
					int inp_n, inp_e;

					cout << "n: ";
					cin >> inp_n;
					cout << "e: ";
					cin >> inp_e;

					// output encrypted message
					result = rsa_encrypt(inp_n, inp_e,enteredText);

				}
				







			}

		}
		else {

			// ...

		}

		if (shouldDecrypt) {
			cout << "---------------Decrypted text---------------" << endl;
		}
		else {
			cout << "---------------Encrypted text---------------" << endl;
		}

		cout << result << endl;
	}

	//system("pause");
	return 0;
}

