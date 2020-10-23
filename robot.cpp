#include "robot.h"
#include "matrix.h"

using namespace std;

robot::robot(int rlen, int clen)
{
    row_length = rlen;
    column_length = clen;
    invalid_blocks = 0;
}

void robot::generate_robot_map()
{
    int count = 0;
    for (int i = 0; i < column_length; i++)
    {
        vector<int> row;
        for (int j = 0; j < row_length; j++)
        {
            row.push_back(count);
            cout << count << " ";
            count++;
        }
        robot_map.push_back(row);
        cout << "\n";
    }
}

int robot::total_bitwise_difference(string A, string B)
{
    int count = 0;

    for (int i = 0; i < 4; i++)
    {

        if (A[i]!=B[i])
        {
            count++;
        }
    }

    // cout << "Number of different bits : " << count << endl;
    return count;
}

string robot::encode_strings(string directions)
{
    string value = "1111";
    if (directions.find("N") != string::npos)
    {
        value[0] = '0';
    }
    if (directions.find("S") != string::npos)
    {
        value[1] = '0';
    }
    if (directions.find("W") != string::npos)
    {
        value[2] = '0';
    }
    if (directions.find("E") != string::npos)
    {
        value[3] = '0';
    }
    return value;
}

vector<long double> robot::generate_objectivity_matrix(vector<vector<string>> vec, string comparison_string)
{
    cout << " objectivity ";
    vector<long double> Jt;
    string comparison = encode_strings(comparison_string);
    for (int i = 0; i < vec.size(); i++)
    {                                              // V rows{
        for (int j = 0; j < vec.at(0).size(); j++) // > columns
        {
            // cout<<"\n-"<<comparison<<"-"<<vec.at(i).at(j)<<"\n";
            int difference = total_bitwise_difference(comparison, vec.at(i).at(j));
            // cout << "\n " << difference << " \n";
            Jt.push_back(sensory_error_vector.at(difference));
        }
    }
    return Jt;
}

int robot::next_state(vector<long double> before_estimation_probablities)
{
    vector<long double> estimation_probablities;
    long double sum_of_elems = 0.000;
    cout<<"Estimation";
    for (int i = 0; i < before_estimation_probablities.size(); i++)
    {
        sum_of_elems += before_estimation_probablities.at(i);
    }
    long double max = 0.000;
    int state = 0;
    for (int i = 0; i < before_estimation_probablities.size(); i++)
    {
        if ((before_estimation_probablities.at(i) / sum_of_elems) > max)
        {
            max = (before_estimation_probablities.at(i) / sum_of_elems);
            state = i;
        }
        estimation_probablities.push_back(before_estimation_probablities.at(i) / sum_of_elems);
        cout<<"\n"<<(before_estimation_probablities.at(i)/sum_of_elems);
        estprobablities.push_back(before_estimation_probablities.at(i) / sum_of_elems);
    }
    // cout<<" sum of elements"<<sum_of_elems;
    return state;
}

vector<long double> robot::get_estimation_probablities()
{
    return estprobablities;
}
std::vector<std::vector<long double>> robot::generate_transitivity_matrix(vector<vector<string>> vec)
{
    std::vector<std::vector<long double>> transitivity_matrix(vec.size() * vec.at(0).size(), std::vector<long double>(vec.size() * vec.at(0).size(), (long double)0.0));

    int counter = 0;
    for (int i = 0; i < vec.size(); i++) // V rows
    {
        for (int j = 0; j < vec.at(0).size(); j++) // > columns
        {

            int position_val[2] = {i, j};
            vector<int> marked_values = robot::generate_robot_position(
                vec.at(i).at(j),
                position_val);

            if (vec.at(i).at(j) == "1111")
            {
                invalid_blocks++;
            }
            // cout << "counter is " << counter;
            if (!marked_values.empty())
            {
                for (int n = 0; n < marked_values.size(); n++)
                {
                    // cout << " \n postion choosen [" << marked_values[n] << "," << counter << " ] " << j << " Iternation \n";
                    
                    transitivity_matrix.at(marked_values[n]).at(counter) = 1.0 / (long double)marked_values.size();

                    // for (int i = 0; i < transitivity_matrix.size(); i++)// {
                    //     for (int j = 0; j < transitivity_matrix.at(i).size(); j++)
                    //     {
                    //         cout << transitivity_matrix.at(i).at(j) << "   ";
                    //     }
                    //     cout << "\n";
                    // }
                }
            }
            else
            {
                // cout << "empty";
            }
            counter++;
        }
    }
    return transitivity_matrix;
}

vector<int> robot::generate_robot_position(string values, int current_position[2])
{
    vector<int> positions;
    // cout << values << " \n";
    for (int i = 0; i < values.size(); i++)
    {
        if (values[i] == '0')
        {
            // cout << i << " ";
            if (i == 0)
            {
                //North
                cout << (current_position[0] - 1) << (current_position[1]);
                // cout<<"\n  Robot map"<<robot_map.at(current_position[0]-1).at(current_position[1])<<" \n";
                positions.push_back(robot_map.at(current_position[0] - 1).at(current_position[1]));
            }
            else if (i == 1)
            {
                //South
                positions.push_back(robot_map.at(current_position[0] + 1).at(current_position[1]));
                // cout << "\n  Robot map" << robot_map.at(current_position[0] + 1).at(current_position[1]) << " \n";
                // cout << (current_position[0] + 1) << (current_position[1]);
            }
            else if (i == 2)
            {
                //West
                positions.push_back(robot_map.at(current_position[0]).at(current_position[1] - 1));
                // cout<<"\n  Robot map"<<robot_map.at(current_position[0]).at(current_position[1] - 1)<<" \n";
                // cout << (current_position[0]) << (current_position[1])-1;
            }
            else
            {
                // cout<<"3 is the length postion";
                positions.push_back(robot_map.at(current_position[0]).at(current_position[1] + 1));
                // cout<<"\n  Robot map: "<<robot_map.at(current_position[0]).at(current_position[1] + 1)<<" \n";
                // cout << (current_position[0]) << (current_position[1]+1);
            }
            cout << " \n";
            // printf(" position: %d \n",i);
        }
    }
    return positions;
}

vector<long double> robot::initial_probability_table(vector<vector<string>> vec)
{
    int total = vec.size() * vec.at(0).size();
    int valid = total - invalid_blocks;
    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = 0; j < vec.at(0).size(); j++)
        {
            if (vec.at(i).at(j) != "1111")
            {
                long double val = 1.000000 / valid;
                intialvector.push_back(val);
                cout << " " << (val);
            }
            else
            {
                intialvector.push_back(0);
                cout << " " << 0.0;
            }
        }
    }
    return intialvector;
}

void robot::generate_sensory_error(double sensory_error)
{
    cout << "Senory error: \n\n";

    for (int j = 0; j <= 4; j++)
    {
        long double error = pow(sensory_error, j) * pow((1 - sensory_error), (4 - j));
        sensory_error_vector.push_back(error);

        // cout << std::showpoint << std::fixed << setprecision(4) << error;
        cout << error;
        cout << "\n";
    }
    cout << "\n\n";
}
