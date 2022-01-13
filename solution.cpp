#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


class Solution {
public:
    
    vector<int> func(vector<vector<int> >& intervals, vector<int>& newInterval) {
        vector<int> res;
        res.push_back(-1);
        res.push_back(-1);
        for(int i = 0; i < intervals.size(); i++) {
            if(res[0] == -1) {
                if(newInterval[0] <= intervals[i][0]) res[0] = newInterval[0];
                else if(newInterval[0] <= intervals[i][1]) res[0] = intervals[i][0];
            } else {
                break;
            }
        }
        if(res[0] == -1) {
            res[0] = newInterval[0];
        }
        for(int i = intervals.size()-1; i >= 0; i--) {
            if(res[1] == -1) {
                if(newInterval[1] >= intervals[i][1]) res[1] = newInterval[1];
                else if(newInterval[1] >= intervals[i][0]) res[1] = intervals[i][1];
            } else {
                break;
            }
        }
        if(res[1] == -1) {
            res[1] = newInterval[1];
        }
        
        return res;
    }
    
    vector<vector<int> > connect(vector<int> &mas, vector<vector<int> > &intervals) {
        vector<vector<int> > res;
        bool flag = true;
        if(mas[1] < intervals[0][0]) {
            res.push_back(mas);
            flag = false;
        }
        for(int i = 0; i < intervals.size(); i++) {
            if(i+1 < intervals.size()) {
                if(intervals[i][1] < mas[0] && intervals[i+1][0] > mas[1]) {
                    res.push_back(intervals[i]);
                    if(flag) res.push_back(mas);
                    flag = false;
                } else if(!(intervals[i][1] < mas[0] || intervals[i][0] > mas[1])) {
                    if(flag) res.push_back(mas);
                    flag = false;
                } else if(intervals[i][1] < mas[0] || intervals[i][0] > mas[1]) {
                    res.push_back(intervals[i]);
                }
            } else {
                if(intervals[i][1] < mas[0] || intervals[i][0] > mas[1])res.push_back(intervals[i]);
            }
        }
        if(flag) {
            res.push_back(mas);
        }
        return res;
    }
    
    vector<vector<int> > insert(vector<vector<int> >& intervals, vector<int>& newInterval) {
        if(intervals.size()==0) {
            vector<vector<int> > res;
            res.push_back(newInterval);
            return res;
        };
        
        vector<int> mas = func(intervals, newInterval);
        return connect(mas, intervals);
        
    }
};

int main() {
    vector<vector<int> > intervals;
    ifstream in;
    in.open("input.txt", ios::in);

    vector<int> val;

    int count = 0;
    int a;
    while (in >> a){
        count++;
        val.push_back(a);
        if(count % 2 ==0 ) {
            intervals.push_back(val);
            val.pop_back();
            val.pop_back();
        }
    }

    vector<int> newIntervals = intervals[intervals.size()-1];
    intervals.pop_back();

    Solution A;
    intervals = A.insert(intervals, newIntervals);

    cout << "[";
    for(int i = 0; i < intervals.size(); i++) {
        cout << "[";
        cout << intervals[i][0] << ", " << intervals[i][1] << "]";
    }
    cout << "]";
    return 0;
}