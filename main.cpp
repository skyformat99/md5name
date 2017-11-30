/**
    @file main.cpp
    md5name - Rename files to their md5 hashes
**/

#include <iostream>
#include <iomanip> //setprecision
#include <fstream>
#include <vector> //data is stored in vectors of char
#include "MD5.hpp" //md5 file class
#include "getinput.hpp" //for easy user input

#include <boost/filesystem.hpp> //for checking filesize, directory, etc

using namespace std;

/**
 * Return the md5 hash of the char buffer
 * @param buffer the buffer to generate the hash from
 * @return 32 character md5 hash
 */
string getMD5(const vector<char>& buffer);

/**
 * Get the relative path from a relative file path
 * (i.e "img/test.jpg" > "img/")
 * @param f the relative file path
 * @return just the path, not the file or extension, ends in '/'.
 */
string getPath(string f);

/**
 * Get the extension (".ext") from a file or file path
 * @param f file or file path
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
 * @param filename the file path to read
 * @return filesize
 */
ifstream::pos_type getFilesize(const char* filename);

/**
 * Print help message
 */
void help();

/**
 * Print usage information
 */
void usage();

const string programName = "md5name";

bool force; // if filesize over 10mb require this. defaults renaming .hidden files to .[md5]
bool verbose; // print more info to stdout
bool dryRun; // don't change any file or folder names
bool recursive; //TODO: recursive (search and rename files and files in folders in folder)

//dirs: enter and rename files if -r specified, otherwise skip and notify if not forced.
//hidden: rename to .md5 if forced, otherwise ask
//regular: rename to md5.extension
//no extension: rename to md5

//warn if overwriting a file if (not -f) or -v (i.e two of the same data w/ differing names)
//dont warn if forced and not verbose
//warn for different extensions, too

int main(int argc, char *argv[]) {
    if (argc == 1) { //Print usage if no arguments given
        usage();
        exit(0);
    }
    
    //keep track of files passed as args
    unsigned long filesProcessed = 0;

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
                    case 'v':
                        verbose = true;
                        break;
                    case 'd': dryRun = true;
                        if (verbose)
                            cout << "Dry run:\n";
                        break;
                    case 'r': recursive = true;
                        if (verbose)
                            cout << "(recursive)\n";
                    default:
                        cout << "Unknown option: \"-" << flag << "\"" << endl;
                        /* no break, print help too */
                    case 'h':
                        help();
                        break;
                }
            }
        } else {
            string filename = argv[i]; //filename and path
            /*            IF DIRECTORY           */
            if (boost::filesystem::is_directory(filename)) {
                if (recursive) { //Enter directory and rename files (recursion time woohoo)
                    chdir(filename.c_str());
                    cout << "(dev): Files to rename:\n";
                    system("ls -R");
                }
                
                if (verbose || !force) {
                    cout << "Skipping directory \"" << filename << "\"\n";
                    break;
                }
            }
            
            /*              IF FILE              */
            unsigned long filesize = boost::filesystem::file_size(filename);
            const unsigned int kB = 1024;
            
            if (filesize <= 0) {
                if (!force) { //print if not forced (even if not verbose), ignore if forced
                    cout << filename << ": ";
                    if (filesize <= 0 && !force)
                        cout << "Warning: ";
                    cout << "Filesize: " << fixed << setprecision(2) << (double)filesize / (double)kB << "kB" << endl;
                } //else rename
            }
            
            //TODO: CHECK FOR DIRECTORIES WITH -r FLAG, enter -> ls -> for each file (rename)
            
            /*          RENAME          */
            string newName = getPath(filename) + getMD5(getData(filename)) + getExt(filename); //New name
            //if verbose, print details and only rename if !dryrun.
            //if not verbose, only rename if !dryrun, otherwise be quiet.
            if (verbose) {
                cout << filename << " -> " << newName << endl;
                if (!dryRun) {
                    rename(filename.c_str(), newName.c_str());
                }
            } else if (!dryRun) {
                rename(filename.c_str(), newName.c_str());
            }
            
            filesProcessed++;
        }
    }
    if (verbose)
        cout << filesProcessed << " files processed.\n";
    //Print usage if no files passed
    if (filesProcessed == 0) {
        usage();
        exit(0);
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

void usage() {
    cout << "Usage: " << programName << " -[fvdh] filename1 ... filename2\nUse -h for help\n";
}

string getMD5(const vector<char>& buffer) {
    MD5 md5;
    md5.update(buffer.data(), (MD5::size_type)buffer.size());
    md5.finalize();
    return md5.hexdigest();
}

string getPath(string f) {
    unsigned long i;
    for (i = f.length(); i != 0; i--) {
        if (f[i] == '/') {
            return f.substr(0, i) + '/'; //start of string to last index of '/'
        }
    }
    //i = 0, no directory:
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
    for (unsigned long i = f.length(); i != 0; i--) {
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
