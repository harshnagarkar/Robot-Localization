#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <bitset>
#include <stdio.h> /* printf, fgets */
#include <stdlib.h>
#include <iomanip>
#include <math.h>
#include "matrix.h"
#include "robot.h"
using namespace std;


vector<int> generate_robot_position(string values);



int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        printf("Error: not enough arguments");
        exit(0);
    }
    string line;
    float sensory_error;
    std::vector<std::vector<string>> basemap;
    ifstream myfile(argv[1]);

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            std::vector<string> lineData;
            std::stringstream lineStream(line);
            int value;

            // Read an integer at a time from the line
            while (lineStream >> value)
            {
                // Add the integers from a line to a 1D array (vector)
                lineData.push_back(bitset<4>(value).to_string());
            }

            // When all the integers have been read, add the 1D array
            // into a 2D array (as one line in the 2D array)
            basemap.push_back(lineData);
        }
        myfile.close();
        // matrix m(basemap);
        // m.printbasemap();
        
        // cout << "Original matrix \n\n";
        // printbasemap(basemap);

        matrix m= matrix(basemap);
        robot r = robot(basemap.at(0).size(),basemap.size());
        // m.printbasemap();

        // printf("\n");
        double sensory_error = atof(argv[2]);
        // cout<<"Sensory error given: "<<sensory_error<<"\n";

        r.generate_sensory_error(sensory_error);

        vector<double> sensory_error_vector;
        r.generate_robot_map();
        vector<vector<long double>> trans = r.generate_transitivity_matrix(basemap);
        // cout<<" \n Best wishes \n";
        // m.printvector(trans);
        // cout<<" \n Initial vector";
        vector<long double> intitalp = r.initial_probability_table(basemap);
        // cout<<"\n J1 \n";

        vector<long double> J1 = m.multiply_matrix(trans,intitalp);

        vector<long double> Jn = J1;
        for(int g = 3;g<argc;g++){

        // cout<<" argument: "<<argv[g]<<"--------------------\n";
        
        vector<long double> bitdif=r.generate_objectivity_matrix(basemap,argv[g]);
        for(int i=0;i<bitdif.size();i++){
            // cout<<bitdif.at(i)<<" ";
        }
        // cout<<" \n";
        //J1
        // cout<<"Before Estimations: \n";
        vector<long double> before_esimation_probablities = m.multiply_vector(bitdif,Jn);
        vector<int> next_position = r.next_state(before_esimation_probablities);
        // cout<<"\n\n The next state is "<< next_position <<" \n\n";
        for(int n=0;n<next_position.size();n++){
            cout<<" "<<next_position[n];
        }
        cout<<" \n";
        vector<long double> Jnext = m.multiply_matrix(trans, r.get_estimation_probablities());
        for(int i=0;i<Jnext.size();i++){
            // cout<<Jnext.at(i)<<" ";
        }
        r.clear_estimation_probablities();
        Jn=Jnext;
        }





        // for (int i = 3; i < sizeof(argv); i++)
        // {
        //     int given_comparator = atoi(argv[i])
        // cout << "Senory error: \n\n";
        // for (int j = 0; j <= 4; j++)
        // {
        //     double error = pow(sensory_error, j) * pow((1 - sensory_error), (4 - j));
        //     sensory_error_vector.push_back(error);
        //     cout << std::showpoint << std::fixed << setprecision(4) << error;
        //     cout << "\n";
        // }
        // cout<<"\n\n";

/*
        //creating base matrix
        int matrix_len = basemap.size()*basemap.at(0).size();
        printf("%d \n matrix length",matrix_len);
        // long double m = new long double()
        std::vector<std::vector<long double>> matrix(matrix_len, std::vector<long double>(matrix_len, 0.0));

        for (int i = 0; i < basemap.size(); i++)
        {
            for (int j = 0; j < basemap.size(); j++)
            {
                string value = basemap.at(i).at(j);
                vector<int> positions = generate_robot_position(value);
                // cout<<positions;
                for(int n =0;n<positions.size();n++){
                    // printf(" %0.2f", std::to_string(1/positions.size()));
                    // matrix.at(n).at(j)=(1.0/positions.size());
                    // printf(positions.);
                    cout<<" change spot";
                }
            }
        }
*/
        // printvector(matrix);
    }
    else
        cout << "Unable to open file";

    return 0;
}

