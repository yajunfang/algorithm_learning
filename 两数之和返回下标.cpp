#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int i=0;
        int j = 0;
        for (i = 0; i<nums.size() - 1; i++)
        {
            for (j = i + 1; j<nums.size(); j++)
            {
                if (nums[i] + nums[j] == target)
                {
                    return { i,j };
                }
            }
        }
        return { -1,-1 };
    };
};

void myprint(int val)
{
    cout << val << "  ";
}


void test01()
{
    vector<int>nums;
    nums.push_back(2);
    nums.push_back(7);
    nums.push_back(9);
    nums.push_back(11);
    nums.push_back(14);

    int target = 1;
    Solution s1;
    vector<int>it=s1.twoSum(nums, target);
    for_each(it.begin(), it.end(), myprint);


}

int main()
{

    test01();
	system("pause");
	return 0;

}