#include <string>
#include <iostream>
using namespace std;

int g_input_data[] =
{
    7,3,1,2,6,4,5,11,0
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


void BucketSort(int* data, int data_size)
{
    int bucket[20]={0};
    for(int i=0; i<data_size; i++)
    {
        bucket[data[i]] = 1;
    }
    int index = 0;
    for(int i=0; i<20; i++)
    {
        if(bucket[i]==1)
        {
            data[index] = i;
            index++;
        }
    }
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
    BucketSort(g_input_data,sizeof(g_input_data)/sizeof(int));
    PrintIntArray(g_input_data,sizeof(g_input_data)/sizeof(int));
    return 0;
}









