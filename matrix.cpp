#include "matrix.h"

using namespace std;

matrix::matrix(vector<vector<string>> inputmap)
{
    basemap = inputmap;
}

void matrix::printbasemap()
{

    for (int i = 0; i < basemap.size(); i++)
    {
        for (int j = 0; j < basemap[i].size(); j++)
        {
            cout << basemap[i][j] << " ";
        }
        cout << "\n";
    }
}

vector<long double> matrix::multiply_vector(vector<long double> vec1,vector<long double> vec2){
    vector<long double> ans;
    for(int i =0;i<vec1.size();i++){
        ans.push_back(vec1.at(i)*vec2.at(i));
    }
    return ans;
}

void matrix::printvector(vector<std::vector<long double>> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = 0; j < vec.at(i).size(); j++)
        {
            cout << vec.at(i).at(j) << " ";
        }
        cout << "\n";
    }
}

vector<long double> matrix::multiply_matrix(vector<std::vector<long double>> A,
              std::vector<long double> B)
{
    // cout<<" \n multiply"<< A.size()<<" "<<B.size()<<" \n";
    std::vector<long double> res;
    int i, j, k;
    for (i = 0; i < A.size(); i++)
    {
        vector<long double> row = A.at(i);

            vector<long double> column = B;
            long double sum =0.0;
            for(int k =0;k<A.size();k++){
                // cout<<" "<<row.at(k)<<"*"<<column.at(k)<<" ";
                sum=sum+row.at(k)*column.at(k);
            }
            cout<<sum;
            res.push_back(sum);
            sum=0;
            cout<<" \n";
    }
    return res;
}