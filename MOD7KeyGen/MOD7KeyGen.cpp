// MOD7KeyGen.cpp - honguyenminh

#include "stdafx.h"
#include "MOD7KeyGen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

void invalidInput(){
	cout << "Invalid input. Check your syntax or spelling and try again.\n";
	cout << "Use --help or -h for more information (case sensitive)\n";
}

int main(int argc, char *argv[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// Error code
			cout << "Fatal Error: MFC initialization failed\n";
			nRetCode = 1;
		}
		else
		{
			// Main code
			// If no argument, output info
			if (argc < 2) {
				cout << "Key generator for Windows 95/NT4.\n";
				cout << "GitHub: \n"; // TODO: add GitHub repo here
				cout << "Use --help or -h for more information\n";
			}

			else {
				// Convert pointer argv[] to string array with vector
				// Removed argv(0) or executable path
				std::vector<std::string> argList(argv + 1, argv + argc);
				

				// Help command
				if (argList[0] == "-h" || argList[0] == "--help") {
					cout << "A basic product key generator for Microsoft products that use mod7 algorithm." << endl << endl;
					cout << "Syntax:    {argument}(required)   {number of key(s)}(optional)" << endl << endl;
					cout << "Usage: {argument} is required to set key type, list below." << endl;
					cout << "Generate 1 key with the specified key type set by {argument}." << endl;
					cout << "Number of key(s) generated can be modified with the {number of key} option." << endl;
					cout << "**Warning: Only one argument can be passed at a time.**\n\n";
					cout << "Arguments list: -h   --help          Display this help." << endl;
					cout << "                -10  --10digitCD     Set key type as 10-digit for CD retails." << endl;
					cout << "                                      - Is oftenly used by Windows 95, NT,..." << endl;
					cout << "                -11  --11digitCD     Set key type as 11-digit for CD retails." << endl;
					cout << "                                      - This type can be found in Office 97,..." << endl;
					cout << "                -20  --20digitOEM    Set key type as 20-digit for OEM versions." << endl << endl;
					cout << "Example command: MOD7KeyGen.exe -11        MOD7KeyGen.exe -20 5" << endl << endl;
					cout << "                                     THIS KEYGEN HAS SUPER COW POWER.\n";
				}

				// Other commands
				else {
					int keyNum = 1; // Default number of key to generate
					int keyType = 0; //Type of Windows key to generate. Will return error if not changed


					// Arguments intepreter
					for (int i = 0; i < argc - 1; i++) {

						// Full size args (start with "--") i.e. --help --type
						if ((argList[i][0] && argList[i][1] == '-') && argList[i][1] != NULL) {
							argList[i].erase(0, 2);

							// Commands, and no switch for strings. Really cpp?
							if (argList[i] == "10digitCD"){
								keyType = 10;
							}
							else if (argList[i] == "11digitCD"){
								keyType = 11;
							}
							else if (argList[i] == "20digitOEM"){
								keyType = 20;
							}
							else {invalidInput(); return nRetCode;} // Error handling
						}

						// Shorthand args (start with "-") i.e. -h -t
						else if (argList[i][0] == '-' && argList[i][1] != NULL) {
							argList[i].erase(0, 1);
							// Commands, string switch no
							if (argList[i] == "10"){
								keyType = 10;
							}
							else if (argList[i] == "11"){
								keyType = 11;
							}
							else if (argList[i] == "20"){
								keyType = 20;
							}
							else {invalidInput(); return nRetCode;} // Error handling

							// Deprecated. Not that useful syntax, replaced by no dash arguments.
							// Can be reused as dash args accept external args
							/*else if (argList[i] == "n"){
								if (i + 1 < argc - 1) { // check if i+1 exists
									keyNum = atoi(argv[i + 2]);						// Number of keys to generate
									i++;
									//Error handler
									if (keyNum == NULL){
										invalidInput(); break;
									}
								}
								else {invalidInput(); break;}
							}*/						 
						}
						else {
							keyNum = atoi(argv[i + 1]);
							if (keyNum == NULL) {
								invalidInput(); return nRetCode;
							}
							break;
						}
					}


/*-----------------------------------------------------------------------------------------------------------------*/

					//Actual algorithm
					if (keyType == 0){
						cout << "Error: No Key type specified. Use -h or --help for more info.\n";
						return nRetCode;
					}
					else {
						// Random initialization
						// Initialize random device to create true random unsigned int for seed
						std::random_device randomDevice;
						unsigned seed = randomDevice();

						// Initialize random engine to make quick psuedo random int with true random seed
						std::default_random_engine randomEngine(seed);

						// Initialize uniform dist to limit range of random
						std::uniform_int_distribution<int> uniDist(0, 9);


						string key;
						// 10-digit retail CD key
						if (keyType == 10) {
							for (int k = 0; k < keyNum; k++) {
								//First 3 digits
								do {
									for (int i = 0; i < 3; i++) {
										key.append(to_string(uniDist(randomEngine)));
									}
								} while (
									key == "333" &&
									key == "444" &&
									key == "555" &&
									key == "666" &&
									key == "777" &&
									key == "888" &&
									key == "999"
									);
								//Last 7 digits
								int tempSum; string lastPart;
								do {
									tempSum = 0;
									lastPart = "";
									int temp;
									for (int i = 0; i < 7; i++) {
										temp = uniDist(randomEngine);
										tempSum += temp;
										lastPart.append(to_string(temp));
									}
								} while (tempSum % 7 != 0 || lastPart[6] - '0' == 0 || lastPart[6] - '0' >= 8);
								key.append("-" + lastPart);
								cout << key << endl; // Output
								key = "";			// Reset key for next loop
							}
						}

						// 11-digit retail CD key (i.e. Office 97)
						else if (keyType == 11) {
							for (int k = 0; k < keyNum; k++) {
								// First 4 digits
								// Generate first 3 digits randomly
								for (int i = 0; i < 3; i++) { key.append(to_string(uniDist(randomEngine))); }
								// Last one is 3rd digit + 1 or + 2, overflow if > 9
								if ((key[2] - '0') + 1 > 9) { key.append("0"); }
								else { key.append(to_string((key[2] - '0') + 1)); }

								// Last 7 digits, same with 10digit key
								int tempSum; string lastPart;
								do {
									tempSum = 0;
									lastPart = "";
									int temp;
									for (int i = 0; i < 7; i++) {
										temp = uniDist(randomEngine);
										tempSum += temp;
										lastPart.append(to_string(temp));
									}
								} while (tempSum % 7 != 0 || lastPart[6] - '0' == 0 || lastPart[6] - '0' >= 8);
								key.append("-" + lastPart);
								cout << key << endl; // Output
								key = "";			// Reset key for next loop
							}
						}



						// 20-digit OEM key
						else if (keyType == 20) {
							for (int k = 0; k < keyNum; k++) {
								// First 5-digit segment, represent key printing date
								// - First 3 digits is days in a year, 001 to 366
								std::uniform_int_distribution<int> dateDist(1, 366); // Set another random limit with uni dist
								int temp = dateDist(randomEngine);					// Get temp, then check, if 1 digit add 00, 2 digits add 0
								if (temp < 10) { key.append("00" + to_string(temp)); }
								else if (temp < 100) { key.append("0" + to_string(temp)); }
								else { key.append(to_string(temp)); }			 // If full 3 digits, append to key normally

								// - Next 2 digits is the year, 95 to 03 (95,96,97,98,99,00,01,02,03) is valid
								string yearArr[9] = { "95", "96", "97", "98", "99", "00", "01", "02", "03" };
								temp = 9;
								while (temp == 9) { temp = uniDist(randomEngine); }

								key.append(yearArr[temp]);

								// Second is OEM
								key.append("-OEM-0"); //Append 0, explained later

								// Third seven-digit segment, same with above but first digit here must be 0, which is already appended
								int tempSum; string lastPart;
								do {
									tempSum = 0;
									lastPart = "";
									int temp;
									for (int i = 0; i < 6; i++) {
										temp = uniDist(randomEngine);
										tempSum += temp;
										lastPart.append(to_string(temp));
									}
								} while (tempSum % 7 != 0 || lastPart[5] - '0' == 0 || lastPart[5] - '0' >= 8);
								key.append(lastPart + "-");

								// Last five-digit segment can be anything, so randomly created
								for (int i = 0; i < 5; i++) {
									key.append(to_string(uniDist(randomEngine)));
								}
								cout << key << endl;
								key = "";
							}
						}
					}
				}
			}
		}
	}
	else
	{
		// Another error code
		printf("Fatal Error: GetModuleHandle failed\n");
		nRetCode = 1;
	}

	return nRetCode; // If == 1, something happened, if == 0, something should happen happened (no error)
}
