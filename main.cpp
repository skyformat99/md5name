/**
    @file main.cpp````````
    md5name - Rename files to their md5 hashes
**/

#include <iostream>
#include <fstream>
#include <vector>
#include "MD5.hpp" //md5 file class
#include "getinput.hpp" //for easy user input

//#include <boost/filesystem.hpp>


using namespace std;

/**
 * Return the md5 hash of the char buffer
 * @param buffer the buffer to generate the hash from
 * @return 32 character md5 hash
 */
string getMD5(vector<char> buffer);

/**
 * Get the relative path from a relative file path
 * (i.e "img/test.jpg" > "img/")
 * @param filename the relative file path
 * @return just the path, not the file or extension, ends in '/'.
 */
string getPath(string f);

/**
 * Get the extension (".ext") from a file or file path
 * @param filename file or file path
 * @return file extension
 */
string getExt(string f);

/**
 * Get the data from a full or relative file path.
 * Displays an error if it can't open.
 * @param filename the full / relative file path
 * @return data as a vector<char>
 */
vector<char> getData(string& filename);

/**
 * Get filesize in bytes
 * @param filename
 * @return filesize
 */
ifstream::pos_type getFilesize(const char* filename);

/**
 * Print help message
 */
void help();

string programName;

bool force; //if filesize over 10mb require this
bool verbose;
bool dryRun;

int main(int argc, char *argv[]) {

    programName = argv[0];

    if (argc == 1) { //Print help for no arguments
        cout << "Usage: " << programName << " -[fvdh] filename1 ... filename2\nUse -h for help\n";
        exit(0);
    }

    for (int i = 1; i < argc; ++i) { //start at 1 to skip program name in argv
        if (argv[i][0] == '-') {
            /*                       IF FLAGS                          */
            string flags = argv[i];

            //start at j=1 to skip '-'
            for (unsigned j = 1; j < flags.length(); ++j) { //check for commands in each char (i.e search "-lf" for 'l' and 'f'
                char flag = argv[i][j];
                switch (flag) {
                    case 'f': force = true;
                        break;
                    case 'v': verbose = true;
                        break;
                    case 'd': dryRun = true;
                        break;
                    default:
                        cout << "Unknown option: \"-" << flag << "\"" << endl;
                        /* no break, print help too */
                    case 'h':
                        help();
                        break;
                }
            }
        } else {
            /*              IF FILE              */
            string filename = argv[i]; //filename and path
            string newName = getPath(filename) + getMD5(getData(filename)) + getExt(filename); //New name
            //if verbose, print details and only rename if !dryrun.
            //if not verbose, only rename if !dryrun, otherwise be quiet.
            if (verbose) {
                cout << filename << " > " << newName << endl;
                if (!dryRun) {
                    rename(filename.c_str(), newName.c_str());
                }
            } else if (!dryRun) {
                rename(filename.c_str(), newName.c_str());
            }
        }
    }
    return 0;
}

void help() {
    cout << programName << " - rename files to their md5 sums\n"
         << "\tUsage: " << programName << " -[fvdh] filename1 filename2\n"
         << "\t-f: Force if file is over 10MB, also assume dotfiles rename to \".[md5]\".\n"
         << "\t-v: Verbose mode.\n"
         << "\t-d: Dry run mode. Doesn't rename files.\n"
         << "\t-h: Print this help message.\n";
}

string getMD5(vector<char> buffer) {
    MD5 md5;
    md5.update(buffer.data(), (MD5::size_type)buffer.size());
    md5.finalize();
    return md5.hexdigest();
}

string getPath(string f) {
    unsigned long i;
    for (i = f.length(); i != 0; i--) {
        if (f[i] == '/') {
            return f.substr(0, i) + '/'; //start to '/'
        }
    }
    //i = 0, no directory
    return ""; //no path
}

string getExt(string f) {
    if (f[0] == '.') {
        //TODO: IF ".EXTENTION" ASK FOR [MD5].EXTENTION OR JUST [MD5] OR .[MD5]
        cout << "Found \"" << f << "\"\nWould you like to rename to:\n1: \"[md5]." << f << "\" or\n2: \".[md5]\"";
        int choice = GetInput::getInt("Choice (1/2)", 1, 2);
        switch (choice) {
            case 1: return f;
            case 2: //return "";
            default: cout << "Fatal error\n"; exit(-1);
        }
    }
    unsigned long i;
    for (i = f.length(); i != 0; i--) {
        if (f[i] == '.') {
            return f.substr(i);
        }
    }
    //if i = 0
    return ""; //return no extension if no '.'
}

vector<char> getData(string& filename) {
    if (verbose)
        cout << filename << ": Opening..." << endl;

    unsigned filesize = static_cast<unsigned>(getFilesize(filename.c_str()));

    //Check if empty or directory
    if (filesize <= 0) {
        if (!force)
            cout << filename << ": Warning: Filesize = 0\n";
        //else {say nothing}
    }

    ifstream file(filename);
    if (file.fail()) {
        if (verbose) {
            cout << filename << ": Error: Can't open file\n";
        } else {
            cout << "Can't open " << filename;
        }
    }
    // copies all data into buffer
    vector<char> buffer((istreambuf_iterator<char>(file)),
                        (istreambuf_iterator<char>()));
    file.close();
    return buffer;
}

ifstream::pos_type getFilesize(const char *filename) {
    ifstream in(filename, ifstream::ate | ifstream::binary);
return in.tellg();
}
