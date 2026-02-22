#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <chrono>
using namespace std;

/**
 * @brief returns the first index of elem if it exists, otherwise returns -1
 * iterativeSearch starts at the first index and iterates sequentially to the next until it either
 * finds the element or until it reaches the the end (i.e. element does not exist)
 *
 * @param v : vector of elements
 * @param elem : integer to look for
 * @return int
 */
int iterativeSearch(vector<int>v, int elem){
    // use a for loop where the index, i goes from 0 to the size of v
    for (int i = 0 ; i < sizeof(v)/sizeof(v[1]); i++) {
        if (v[i]==elem) {
            return i;
        }
    }

    return -1;
    // inside the for loop, use an if statement to check whether the element at i (e.g. v[i]) equals elem
    // inside the if statement return i   


    // outside of the for loop return -1

}

/**
 * @brief returns the index of elem, if it exists in v. Otherwise it returns -1.
 * binarySearch is recursive (i.e. function calls itself).
 * It utilizes the fact that v is increasing order (e.g. values go up and 
 * duplicates are not allowed).
 *
 * It calculates the mid from the start and end index. It compares v[mid] (i.e. value
 * at mid) with elem and decides whether to search the left half (lower values)
 * or right half (upper values).
 *
 * 
 * @param v : vector of elements
 * @param start : leftmost index (starting value is 0)
 * @param end  :rightmost index (starting value is v.size())
 * @param elem : integer to look for
 * @return int 
 */
int binarySearch(vector<int> & v, int start, int end, int elem){
        //write an if statement that checks the terminating case 
    //inside the if statement return -1
    if (start > end){
        return -1; 
    }
    // instantiate the midpoint 
    int mid = (start + end) / 2; 

    // Use if/else statements to do the following:

    // 1) update end (search left half)
    if (v[mid] < elem){
        end = mid -1; 
    }
    // 2) update start (search right half)
    else if (v[mid] > elem){
        start = mid + 1; 
    }
    else {
        return mid; 
    }
    return binarySearch(v, start, end, elem); 
    // 3) return mid (found the elem)

    // return a recursive call to binarySearch(...)



}

/**
 * @brief updates v to contain the values from filename (leave as is)
 * 
 * It is expected that the files contain values ranging from one to 
 * one hundred million in ascending order (no duplicates).
 * 
 * @param filename : string
 * @param v :vector
 */
void vecGen(string filename, vector<int> & v){
    ifstream file(filename);
    int num;
    v.clear();
    while (file.is_open() && file >> num){
        v.push_back(num);
    }
    file.close();
}

/**
 * @brief writes to file the time it took to search with respect to the
 *  size of the vector, n
 *  Number of Elements (n)	    Time (sec) 
    XXXX	                    X.XXXXX
    XXXX	                    X.XXXXX
 * @param filename (string) : filename (e.g. output_10000_numbers.csv)
 * @param times (vector<double>) : average times 
 * @param n (vector<int>) : sizes of vectors
 */
void writeTimes(string filename, const vector<double> times, const vector<int> n){
    ofstream myFile(filename);

    myFile << "Number of Elements (n)\t Time (sec) " << endl;
    for(int i = 0; i < times.size(); i++){

        myFile << n[i] << "\t" << times[i] << "\n";
    }
    myFile.close();
    cout << "Wrote to " << filename << endl;
}

/**
 * @brief computes the average of the elements in vector, a
 * 
 * @param a  vector of double
 * @return double 
 */
double average(const vector<double> a){
    double avg = 0;
    int numelems = sizeof(a)/sizeof(a[0]);
    for (int i = 0; i<numelems; i++)
    {
        avg+=a[i];
    }
    return avg/numelems;
}

int main(){
    // test elements to search for
    vector<int> elem_to_find;
    vecGen("test_elem.csv", elem_to_find);
    // size (n) of all tests 
    vector<int> file_sizes;
    vecGen("sizes.csv", file_sizes);
    
    //n list of numbers
    vector<int>v; 

    //results of times
    vector<double> times;

    //results of avg per workload size
    vector<double> avg;
    
    // create a for loop to iterate through the file sizes
    for(int i = 0; i < file_sizes.size(); i++) {
    // get the name/size of the file and assign it to string called filename
        string filename = to_string(file_sizes[i]) + ".csv";
    //call vecGen on filename and v
        vecGen(filename, v);
    // print filename (this will be good for debugging)
        cout<<filename<<endl;
    // call times.clear() // this ensures that we reset times everytime we read a new file 
        times.clear();
    // create another for loop to iterate through all the elements from elem_to_find. 
    // the code here should be nearly identical to the code from the previous lab 
        
        

        for (int j = 0; j < elem_to_find.size(); j++){
            auto start = chrono::high_resolution_clock::now();
            int found = binarySearch(v,0,v.size() - 1, elem_to_find[j]);
            auto end = chrono::high_resolution_clock::now();
            auto elapsed_time = chrono::duration_cast<std::chrono::microseconds>(end - start);
            double elapsed_time_in_usec = elapsed_time.count();
            times.push_back(elapsed_time_in_usec);
        // append the elapsed_time_in_sec to the vector,times (hint: push_back())
        // This code shuold be within the for loop that iterates 
        // through all the elements from elem_to_find
        }
        double average_time = average(times);
        avg.push_back(average_time);
    // call average on the vector, times, and save it as a double. This code should be 
    // outside the for loop that iterates through all the elements from elem_to_find
    // but within the for loop that iterates through the file sizes
        

    // append the double to avg. (hint: push_back())
    // This code should be outside the for loop that iterates through
    // all the elements from elem_to_find
    // but within the for loop that iterates through the file sizes
    
    }

    //outside both for loops call writeTimes with the appropriate parameters
    // the first parameter should be "iterativeSearch_times.csv"
    // read the function brief to complete the rest of the parameters
    writeTimes("average_binarySearch_times.csv",avg,file_sizes);

    // call avg.clear() to reset avg, so we can use it for binarySearch
    avg.clear();

    // repeat the nested for loops used for iterativeSearch, but call binarySearch instead

    for(int i = 0; i < file_sizes.size(); i++) {
    // get the name/size of the file and assign it to string called filename
        string filename = to_string(file_sizes[i]) + ".csv";
    //call vecGen on filename and v
        vecGen(filename, v);
    // print filename (this will be good for debugging)
        cout<<filename<<endl;
    // call times.clear() // this ensures that we reset times everytime we read a new file 
        times.clear();
    // create another for loop to iterate through all the elements from elem_to_find. 
    // the code here should be nearly identical to the code from the previous lab 
        
        

        for (int j = 0; j < elem_to_find.size(); j++){
            auto start = chrono::high_resolution_clock::now();
            int found = iterativeSearch(v, elem_to_find[j]);
            auto end = chrono::high_resolution_clock::now();
            auto elapsed_time = chrono::duration_cast<std::chrono::microseconds>(end - start);
            double elapsed_time_in_usec = elapsed_time.count();
            times.push_back(elapsed_time_in_usec);
        // append the elapsed_time_in_sec to the vector,times (hint: push_back())
        // This code shuold be within the for loop that iterates 
        // through all the elements from elem_to_find
        }
        double average_time = average(times);
        avg.push_back(average_time);

    }
    writeTimes("average_iterativeSearch_times.csv",avg,file_sizes);

    // call avg.clear() to reset avg, so we can use it for binarySearch
    avg.clear();
    

    //outside both for loops call writeTimes with the appropriate parameters
    // the first parameter should be "binarySearch_times.csv"
    // read the function brief to complete the rest of the parameters

}