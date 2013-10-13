#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main(int argc, const char *argv[])
{
    int number_of_strings=0;
    cin >> number_of_strings;

    vector<string> horizontal_strings(number_of_strings);

    for (int i = 0; i < number_of_strings; i++) {
        cin >> horizontal_strings[i];
    }

    vector< vector<char> > vertical_strings(1);

    for (int i = 0; i < horizontal_strings.size(); i++) {
        for (int k = 0; k < horizontal_strings[i].size(); k++) {
            if(vertical_strings.size() < k + 1){
                vertical_strings.resize(k + 1);
            }
            vertical_strings[k].push_back(horizontal_strings[i][k]);
        }
    }

    for (int i = 0; i < vertical_strings.size(); i++) {
        for (int k = 0; k < vertical_strings[i].size(); k++) {
            cout << vertical_strings[i][k];
        }
        std::cout <<  std::endl;
    }

    return 0;
}
