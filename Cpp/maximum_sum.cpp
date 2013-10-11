#include<iostream>
#include<algorithm>

using namespace std;

int main(int argc, char **argv){

    int list[9] = {10, -1, 5, 6, 20, -50, 100, -100, 4};

    int current_maximum = 0, previous_maximum=0;
    bool evaluating = false;

    for (int i = 0; i < 9 ;i++) {
        if(current_maximum == 0 && list[i] < 0 && previous_maximum == 0){
            continue;
        }

        if(list[i] < 0 && evaluating == false){
            previous_maximum = current_maximum;
            current_maximum = 0;
            evaluating = true;
        }

        current_maximum += list[i];

        if(evaluating ==true and current_maximum > 0){
            current_maximum += previous_maximum;
            evaluating = false;
        }
    }

    cout << "maximum sum is " << max(current_maximum, previous_maximum) << endl;

    return 0;
}
