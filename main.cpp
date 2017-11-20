#include<cstdint>
#include"Cast128.h"
#include<iostream>
#include<map>
#include<vector>

using namespace std;
int main(int argc, char* argv[]) {
	const string outFileKey = "-o";
	const string inFileKey = "-i";
	const string keyFileKey = "-k";
	const string encryptKey = "-e";
	const string decryptKey = "-d";
	const string generateKey = "-g";
	const string mode = "mode";
	map<std::string, std::string> commandLineArgs{
		{outFileKey,"out.txt"},
		{inFileKey,"in.txt"},
		{keyFileKey,"key.txt"}
	};
	std::vector< string> args;
	for (int i = 1; i < argc; ++i) {
		args.push_back(argv[i]);
	}

	for (int i = 0; i < args.size(); ++i){
		if (args[i] == outFileKey) {
			commandLineArgs[outFileKey] = args[i + 1];
			i++;
		}
		if (args[i] == inFileKey) {
			commandLineArgs[inFileKey] = args[i + 1];
			i++;
		}
		if (args[i] == keyFileKey) {
			commandLineArgs[keyFileKey] = args[i + 1];
			i++;
		}
		if (args[i] == encryptKey) {
			commandLineArgs[mode] = encryptKey;
		}
		if (args[i] == decryptKey) {
			commandLineArgs[mode] = decryptKey;
		}
		if (args[i] == generateKey) {
			commandLineArgs[mode] = generateKey;
		}		
	}
	
	if (commandLineArgs[mode] == generateKey) {
		Cast128::generateKey(commandLineArgs[outFileKey]);
	}
	if (commandLineArgs[mode] == encryptKey) {
		try {
			Cast128::Key key;
			Cast128::readKey(commandLineArgs[keyFileKey], &key);
			Cast128::encryptFile(commandLineArgs[inFileKey], commandLineArgs[outFileKey], key);
		} catch (exception e) {
			std::cout << e.what();
		}
	}
	if (commandLineArgs[mode] == decryptKey) {
		try {
			Cast128::Key key;
			Cast128::readKey(commandLineArgs[keyFileKey], &key);
			Cast128::decryptFile(commandLineArgs[inFileKey], commandLineArgs[outFileKey], key);
		} catch (exception e) {
			std::cout << e.what();
		}
	}

	/*Cast128::Key key = { 0x01234567, 0x12345678, 0x23456789, 0x3456789A };
	Cast128::Block msg = { 0x01234567, 0x89ABCDEF };
	Cast128::Block res = Cast128::encrypt(key, msg);
	Cast128::correlation("in.txt", "res.txt");*/

	return 0;
}