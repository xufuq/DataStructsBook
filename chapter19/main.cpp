#include <iostream>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

int maxPubStr(string const &str1, string const &str2, int index1, int index2){
    if (index1==str1.size()-1 && index2==str2.size()-1)
        return str1[index1]==str2[index2];
    else if (index1==str1.size()-1){
        if (str1[index1]==str2[index2])
            return true;
        else
            return maxPubStr(str1, str2, index1, index2+1);
    } else if (index2==str2.size()-1){
        if (str1[index1]==str2[index2])
            return true;
        else
            return maxPubStr(str1, str2, index1+1, index2);
    } else{
        int max1 = max(maxPubStr(str1, str2, index1+1, index2), maxPubStr(str1, str2, index1, index2+1));
        if (str1[index1]==str2[index2])
            return max(max1, maxPubStr(str1, str2, index1+1, index2+1)+1);
        else
            return max1;
    }
}

int maxSubNum(vector<int> const &nums, int startIndex, int endIndex, int &maxStart, int &maxEnd){
    if (startIndex<=endIndex){
        int start1=0, start2=0, end1=0, end2=0;
        int max2 = maxSubNum(nums, startIndex+1, endIndex, start2, end2);
        int max3 = accumulate(nums.begin()+startIndex, nums.begin()+endIndex+1, 0);
        if (endIndex<nums.size()-1){
            int max1 = maxSubNum(nums, startIndex, endIndex+1, start1, end1);
            if (max1>=max2 && max1>=max3){
                maxStart = start1;
                maxEnd = end1;
                return max1;
            } else if (max2>=max1 && max2>=max3){
                maxStart = start2;
                maxEnd = end2;
                return max2;
            } else {
                maxStart = startIndex;
                maxEnd = endIndex;
                return max3;
            }
        } else {
            if (max2>=max3){
                maxStart = start2;
                maxEnd = end2;
                return max2;
            } else {
                maxStart = startIndex;
                maxEnd = endIndex;
                return max3;
            }
        }
    } else {
        maxStart = startIndex;
        maxEnd = endIndex;
        return 0;
    }
}

int main() {
    string str1 = "agcbhcmqbdno", str2 = "ambcqnobczpyt";
    cout << maxPubStr(str1, str2, 0, 0) << endl;

    vector<int> nums = {5, 10, -20, -30, 50, -80, 100, 70, -30, 60, -40, 50};
    int maxS=0, maxE=0;
    int maxsum = maxSubNum(nums, 0, 0, maxS, maxE);
    cout << maxS << " " << maxE << " " << maxsum << endl;
    return 0;
}
