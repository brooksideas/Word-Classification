#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <limits>

using namespace std;

// Seek to the required line in the file text and parse as a string and return value
std::string GotoLine(std::ifstream &file, unsigned int num)
{
    file.seekg(std::ios::beg);
    for (int i = 0; i < num - 1; ++i)
    {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Return the specific line as a string value
    std::string lineContent((std::istreambuf_iterator<char>(file)),
                            (std::istreambuf_iterator<char>()));
    return lineContent;
}

int main(int argc, char **argv)
{
    ifstream infile;

    string read_file_name("input01.txt");

    infile.open(read_file_name);

    int T; // Test case
    int C; // Number of categories

    string tLine; // Test case Line on the file
    string cLine; // Category Line on the file
    string nLine; // Category Name Line on the file

    /* CREATE Empty Maps for future use */
    map<string, int> categoryMap1;
    map<string, int> categoryMap2;
    map<string, int> categoryMap3;

    if (infile.good())
    {

    // Get Test Case Number
    tLine = GotoLine(infile, 1);
    T = stoi(tLine);
    cout << "T =>" << tLine << endl;

    // Get Category Line
    cLine = GotoLine(infile, 2);
    C = stoi(cLine);
    cout << "C =>" << cLine << endl;

    // Get the first Category which would be on the third line immediately below the category
    int categoriesFound = 2; // Line Number of the category currently found on the file
    int categoriesCount = 0; // Terminates the loop when the count is equal to the expected number of categories
    string space_delimiter = " ";
    vector<string> words{};

    // return 0;   
    // While the number of categories is not reached loop and create Maps on the fly
    while (categoriesCount < C)
    {
        string N; // Category Name
        int W;    // Number of words in category
        int P;    // Must match this number of words in the category

        for (int i = 0; i < categoriesFound; i++)
        {
            getline(infile, nLine);
            cout << nLine << endl;
            cout << "N =>" << nLine << endl;
            nLine = nLine + " "; // add an extra space to the line to get the full line
            size_t pos = 0;
            while ((pos = nLine.find(space_delimiter)) != string::npos)
            {
                words.push_back(nLine.substr(0, pos));
                nLine.erase(0, pos + space_delimiter.length());
            }

            for (const auto &str : words)
            {
                cout << str << endl;
            }
            // Now words contain [CategoryName (N) , Number of Words in Category(W) , The required Number to Match (P)]
            cout << "Vector CNA =>" << words[0] << endl;
            cout << "W=>" << words[1] << endl;
            cout << "P =>" << words[2] << endl;
            N = words[0];
            W = stoi(words[1]);
            P = stoi(words[2]);

            // Create a category Map using category Name and initialize with the words in the category
            int categoryIterator = 1;
            // assign to the map variables accordingly by passing the i value
            switch (categoriesCount)
            {
                // first category and its consecutive values will be assigned in Map 1 and so on ...
            case 1:
                categoryMap1.insert({N, P}); // first field of the Map should hold the Category name (N) and the required Number of words to Match(P)
                // while loop to get all the following consecutive values of the Category Match Words
                while (categoryIterator < W + 1)
                {
                    int lineToFetch = categoryIterator + categoriesFound;
                    string categoryKey = GotoLine(infile, lineToFetch);
                    categoryMap1.insert({categoryKey, 0});
                    categoryIterator++;
                }
                break;
            case 2:
                categoryMap2.insert({N, P}); // first field of the Map should hold the Category name (N) and the required Number of words to Match(P)
                // while loop to get all the following consecutive values of the Category Match Words
                while (categoryIterator < W + 1)
                {
                    int lineToFetch = categoryIterator + categoriesFound;
                    string categoryKey = GotoLine(infile, lineToFetch);
                    categoryMap2.insert({categoryKey, 0});
                    categoryIterator++;
                }
                break;
            case 3:
                categoryMap3.insert({N, P}); // first field of the Map should hold the Category name (N) and the required Number of words to Match(P)
                // while loop to get all the following consecutive values of the Category Match Words
                while (categoryIterator < W + 1)
                {
                    int lineToFetch = categoryIterator + categoriesFound;
                    string categoryKey = GotoLine(infile, lineToFetch);
                    categoryMap3.insert({categoryKey, 0});
                    categoryIterator++;
                }
                break;
            default:
                break;
            }

            // testing display of the Map
            // for (auto itr = categoryMap1.begin();
            //      itr != categoryMap1.end(); ++itr)
            // {
            //     cout << itr->first << '\t'
            //          << itr->second << '\n';
            // }

            // Increase the found category to find the next categories line
            categoriesFound = categoriesFound + W + 1;

            // Increase the category count until all categories are populated
            categoriesCount++;
        }
    };
    }

    infile.close();
}