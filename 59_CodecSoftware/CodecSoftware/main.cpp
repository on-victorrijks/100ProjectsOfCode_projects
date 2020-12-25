#include <iostream>
#include <stdio.h>
#include <string> 
#include <ctype.h>
using namespace std;

string alphabet = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
const char* algorithms[2] = { "Caesar", "RSA" };

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

int getLCM(int n1, int n2) {


	if (n1 > n2) {

		int k = 1;
		int temp = n1;
		while (true) {
			if (temp % n2 == 0) {
				return temp;
			}
			k += 1;
			temp = n1 * k;
		}


	} else if (n1 < n2) {

		int k = 1;
		int temp = n2;
		while (true) {
			if (temp % n1 == 0) {
				return temp;
			}
			k += 1;
			temp = n2 * k;
		}

	} else {
		return n1;
	}

}

// Caesar

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
	string enteredText;
	int numberOfAlgorithms = sizeof(algorithms) / sizeof(algorithms[0]);
	float shouldDecrypt = false;
	bool run_main = false;
	srand(time(NULL));

	// TEST


	int p, q, n, keyLength, lcm;

	p = getPrime(-1);
	q = getPrime(p);
	n = p * q;
	lcm = getLCM((p - 1), (q - 1));


	cout << p << " : " << q << endl;
	cout << n << endl;

	// TEST

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
				shouldDecrypt = true;
				break;
			}
			else if (shouldDecryptLetter == 'N') {
				shouldDecrypt = false;
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

			// ...

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

