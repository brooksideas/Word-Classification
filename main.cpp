#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <limits>
#include <sstream>

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

// Get the specific category key
std::string getCategoryKey(std::string categoryKeyLine)
{
    std::istringstream str(categoryKeyLine);
    vector<string> result{};

    for (std::string categoryKeyLine; str >> categoryKeyLine;)
        result.push_back(categoryKeyLine);

    return result[0];
}

// Break all the research paper words and insert them in a research vector
std::vector<std::string> getResearchKey(std::string researchKeyLine)
{
    std::istringstream str(researchKeyLine);
    vector<string> research{};

    for (std::string researchKeyLine; str >> researchKeyLine;)
        research.push_back(researchKeyLine);

    return research;
}

// Return the final result from the TEST case
std::string returnTestResults(std::vector<std::string> research, std::vector<std::string> researchPaper, std::unordered_map<std::string, int> categoryMap)
{
    string testResult, categoryName;
    int sum = 0, expectedMatch = 0;

    for (int i = 0; i < researchPaper.size() - 1; i++)
    {

        // Only works if the word from the paper matches the value from category key ; p.e key is found
        if (categoryMap.find(researchPaper[i]) != categoryMap.end())
        {
            auto categoryFound = categoryMap.find(researchPaper[i]);
            // insert a value of 1 to the one found in the category
            categoryMap.at(categoryFound->first) = 1;
        }
    }

    /* Now we have all the category maps and the respective values if they are found in the research paper */
    for (auto i = categoryMap.begin(); i != categoryMap.end(); i++)
    {
        // first one holds the category and expected match so skip
        if (i->second < 2)
        {
            sum = sum + i->second;
        }
        cout << "FINDIN-->" << i->first << "--->" << i->second << endl;
        // this is the category name to be displayed if match found (N)
        categoryName = i->first;
        // this is the final expected Match of the category (P)
        expectedMatch = i->second;
    }

    // return the final value
    if (expectedMatch == sum)
    {
        testResult = categoryName;
        cout << testResult << endl;
        return testResult;
    }
    else
    {
        testResult = "SQF Problem";

        cout << "FAILED" << expectedMatch << "SUM " << sum << endl;
        cout << testResult << endl;
        return testResult;
    }
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
    string rLine; // Research written lines

    /* CREATE Empty Maps for future use */
    std::unordered_map<string, int> categoryMap1;
    std::unordered_map<string, int> categoryMap2;
    std::unordered_map<string, int> categoryMap3;

    if (infile.good())
    {
        
        // Get Test Case Number
        tLine = GotoLine(infile, 1);
        T = stoi(tLine);
        cout << "T =>" << tLine << endl;

        // Get Category Line
        cLine = GotoLine(infile, 2);
        C = stoi(cLine);
        cout << "C =>" << C << endl;

        // Get the first Category which would be on the third line immediately below the category
        int categoriesFound = 3; // Line Number of the category currently found on the file
        int categoriesCount = 0; // Terminates the loop when the count is equal to the expected number of categories
        string space_delimiter = " ";
        vector<string> words{};

        // While the number of categories is not reached loop and create Maps on the fly
        while (categoriesCount < C)
        {
            string N; // Category Name
            int W;    // Number of words in category
            int P;    // Must match this number of words in the category

            // Clear out the words vector to use it for the new incoming line
            words.clear();
            cout << "FLUSH =>" << sizeof(words) << endl;
            nLine = GotoLine(infile, categoriesFound); // gets the top section of the category line
            cout << "NLINE =>" << nLine << endl;
            nLine = nLine + " "; // add an extra space to the line to get the full line

            std::istringstream iss(nLine);
            for (std::string nLine; iss >> nLine;)
                words.push_back(nLine);

            // Now words contain [CategoryName (N) , Number of Words in Category(W) , The required Number to Match (P)]
            cout << "N =>" << words[0] << endl;
            cout << "W=>" << words[1] << endl;
            cout << "P =>" << words[2] << endl;
            cout << "Category Found " << categoriesFound << endl;
            N = words[0];
            W = stoi(words[1]); // converts to integer
            P = stoi(words[2]);

            // Use the iterator to get the following words of the category
            int categoryIterator = 1;
            // assign to the map variables accordingly by passing the i value
            switch (categoriesCount)
            {
                // first category and its consecutive values will be assigned in Map 1 and so on ...
            case 0:
                categoryMap1.insert({N, P}); // first field of the Map should hold the Category name (N) and the required Number of words to Match(P)
                cout << "Category 1 " << categoryIterator << categoriesFound << endl;
                // while loop to get all the following consecutive values of the Category Match Words
                while (categoryIterator < W + 1)
                {
                    int lineToFetch = categoryIterator + categoriesFound;
                    string categoryKey = GotoLine(infile, lineToFetch);

                    categoryKey = getCategoryKey(categoryKey);
                    cout << "Category 1 INSERT" << categoryKey << endl;
                    categoryMap1.insert({categoryKey, 0});
                    categoryIterator++;
                }

                cout << "MAP 1 INSERTED ===>" << categoryMap1["Graph"] << endl;
                break;
            case 1:
                categoryMap2.insert({N, P}); // first field of the Map should hold the Category name (N) and the required Number of words to Match(P)
                cout << "Category 2 " << N << P << endl;
                // while loop to get all the following consecutive values of the Category Match Words
                while (categoryIterator < W + 1)
                {
                    int lineToFetch = categoryIterator + categoriesFound;
                    string categoryKey = GotoLine(infile, lineToFetch);
                    categoryKey = getCategoryKey(categoryKey);
                    categoryMap2.insert({categoryKey, 0});
                    categoryIterator++;
                }
                break;
            case 2:
                categoryMap3.insert({N, P}); // first field of the Map should hold the Category name (N) and the required Number of words to Match(P)
                cout << "Category 3  " << N << P << endl;
                // while loop to get all the following consecutive values of the Category Match Words
                while (categoryIterator < W + 1)
                {
                    int lineToFetch = categoryIterator + categoriesFound;
                    string categoryKey = GotoLine(infile, lineToFetch);
                    categoryKey = getCategoryKey(categoryKey);
                    categoryMap3.insert({categoryKey, 0});
                    categoryIterator++;
                }
                break;
            default:
                break;
            }

            // testing display of the Map
            for (auto itr = categoryMap2.begin();
                 itr != categoryMap2.end(); ++itr)
            {
                cout << "MAP 2" << itr->first << '\t'
                     << itr->second << '\n';
            }

            // Increase the found category to find the next categories line
            categoriesFound = categoriesFound + W + 1;

            // Increase the category count until all categories are populated
            categoriesCount++;
            cout << "CC =>" << categoriesCount << categoriesFound << endl;
        };

        /* Now that we have found all the categories and test cases to be fulfilled
             let us go through the research paper and look for a match
          */

        // gets the research papers sentences line by line until an empty line is found
        rLine = GotoLine(infile, categoriesFound);
        vector<string> research{};
        vector<string> researchPaper{};
        // As long as there is a research paper line to be fetched keep on looping
        while (rLine.empty() != 1 && rLine.at(0) != ' ')
        {
            cout << "BREAKING ->" << rLine.at(0) << endl;
            if (rLine.at(0) == ' ')
            {
                cout << "BREAK" << endl;
                return ' ';
            }
            rLine = GotoLine(infile, categoriesFound);

            // clear out the research vector here
            research.clear();
            cout << "RESEARCH" << rLine.empty() << endl;

            research = getResearchKey(rLine);
            // traverse through the vector and copy into the research paper vector to search the keys in
            for (int i = 0; i < research.size(); i++)
                researchPaper.push_back(research[i]);
            cout << "RESEARCH first word--->" << researchPaper.size() << endl;
            categoriesFound++;
        }

        /* Now that we have the category key value Map and all the research on one vector
           let us traverse through the vector and search for the key in the category map */
        cout << "Test case 1" << endl;
        if (categoryMap1.size() != 0)
            returnTestResults(research, researchPaper, categoryMap1);
        if (categoryMap2.size() != 0)
            returnTestResults(research, researchPaper, categoryMap2);
        if (categoryMap3.size() != 0)
            returnTestResults(research, researchPaper, categoryMap3);

        infile.close();
    }
}