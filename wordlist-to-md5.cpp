#include <iostream>
#include <fstream>
#include <string>
#include <openssl/md5.h>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
    return 1;
  }

  string input_file = argv[1];
  string output_file = argv[2];

  cout << "Input file: " << input_file << endl;
  cout << "Output file: " << output_file << endl;

  // Open the input file
  ifstream wordlist(input_file);

  if (!wordlist.is_open()) {
    cerr << "Failed to open " << input_file << endl;
    return 1;
  }

  // Open the output file
  ofstream outfile(output_file);

  if (!outfile.is_open()) {
    cerr << "Failed to open " << output_file << endl;
    return 1;
  }

  // Read each line of the wordlist file
  string line;
  while (getline(wordlist, line)) {
    // Calculate the MD5 hash of the word
    unsigned char md[MD5_DIGEST_LENGTH];
    MD5((unsigned char *)line.c_str(), line.length(), md);
    // Print the MD5 hash to the output file
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
      outfile << hex << setw(2) << setfill('0') << (int)md[i];
    }
    outfile << endl;

    // Debug output
    cout << "Processed: " << line << endl;
  }

  return 0;
}
