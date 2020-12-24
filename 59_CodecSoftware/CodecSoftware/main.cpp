#include <iostream>
#include <stdio.h>
#include <string> 
#include <ctype.h>
using namespace std;

string alphabet = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
const char* algorithms[2] = { "Caesar", "RSA" };

// Get prime
bool isPrime(int n) {

	// STEP 1
	int nmin = n - 1;

	double temp_k = 1;
	double c = pow(2.00, temp_k);

	while (std::fmod(nmin,c) == 0) {
		temp_k += 1;
		c = pow(2.00, temp_k);
	}

	double k = temp_k - 1;
	int m = nmin / pow(2.00,k);
	
	// STEP 2
	// 1 < a < n-1
	int a = 2;

	// STEP 3
	// bo
	int bo = std::fmod(pow(a, m), n);
	if (bo == -1 || bo == 1) {
		return true;
	}


	// bn
	int bn = bo;
	while (true) {
		bn = std::fmod(pow(bn, 2), n);
		cout << bn;
		if (bn == nmin) {
			return true;
		}
		if (bn == -1) {
			return true;
		} else if (bn == 1) {
			return false;
		}
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

	if (isPrime(307)) {
		cout << "prime" << endl;
	}
	else {
		cout << "not prime" << endl;
	}

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
	while (true){
		cout << "Do you want to encrypt a text ? (Y/N): ";
		cin >> shouldDecryptLetter;

		if (shouldDecryptLetter == 'Y') {
			shouldDecrypt = true;
			break;
		} else if (shouldDecryptLetter == 'N') {
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

	} else if (chosenAlgo_str == "RSA") {

		// ...

	} else {

		// ...

	}

	if (shouldDecrypt) {
		cout << "---------------Decrypted text---------------" << endl;
	}
	else {
		cout << "---------------Encrypted text---------------" << endl;
	}

	cout << result << endl;






	//system("pause");
	return 0;
}

