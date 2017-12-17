#include <string>
#include <cstring>
#include <iostream>
using namespace std;

int g_input_data[] =
{
    5,3,4,2,11,0,9,7,1
};

void PrintIntArray(const int* data,int data_size,bool is_print_marks=true)
{
    string log_head("array:");
    if (is_print_marks)
    {
        string log_begin(data_size,'+');
        cout << log_head+log_begin << endl;

        char log_array_size[20]={0};
        sprintf(log_array_size,"array_size:%d",data_size);
        cout << log_array_size << endl;
    }

    for(int i=0; i<data_size; i++)
    {
        cout << data[i];
        if(i!=data_size-1)
            cout << ",";
        else
            cout << "\n";
    }
    if (is_print_marks)
    {
        string log_end(data_size,'-');
        cout << log_head+log_end << endl;
    }
}


void MergeSort(int* data, int data_size)
{
    int data1_size = data_size / 2;
    if(data1_size==0)
        return;

    int* data1 = data;
    int* data2 = data+data1_size;
    int data2_size = data_size-data1_size;

    MergeSort(data1,data1_size);
    MergeSort(data2,data2_size);

    int* temp = new int[data_size];
    memset(temp,0,data_size);
    int data1_iterator=0;
    int data2_iterator=0;
    int temp_iterator = 0;
    while(data1_iterator<data1_size || data2_iterator<data2_size)
    {
        if(data1_iterator<data1_size && data2_iterator<data2_size)
        {
            if(data1[data1_iterator] < data2[data2_iterator])
            {
                temp[temp_iterator++] = data1[data1_iterator++];
            }
            else
            {
                temp[temp_iterator++] = data2[data2_iterator++];
            }
        }
        else
        {
            while(data1_iterator<data1_size)
            {
                temp[temp_iterator++] = data1[data1_iterator++];
            }

            while(data2_iterator<data2_size)
            {
                temp[temp_iterator++] = data2[data2_iterator++];
            }
        }
    }
    for(int i=0; i<data_size; i++)
    {
        data[i] = temp[i];
    }
    PrintIntArray(data,data_size,false);

    delete[] temp;
}

int main(int argc, char* argv[])
{
    cout << "argc:" << argc << endl;
    for(int i=0; i<argc; i++)
    {
        cout<<argv[i];
        if(i!=argc-1)
            cout<<",";
        else
            cout<<endl;
    }
    cout << "Hello Algorithm!" << endl;
    PrintIntArray(g_input_data,sizeof(g_input_data)/sizeof(int));
    MergeSort(g_input_data,sizeof(g_input_data)/sizeof(int));
    PrintIntArray(g_input_data,sizeof(g_input_data)/sizeof(int));
    return 0;
}









