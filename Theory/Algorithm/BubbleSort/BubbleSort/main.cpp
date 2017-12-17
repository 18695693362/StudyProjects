#include <string>
#include <iostream>
using namespace std;

int g_input_data[] =
{
    20,3,1,15,7,2,13
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

enum ETraversingDirction
{
    kTraversingDirction_Forward,
    kTraversingDirction_Backward
};

void BubbleSort(int* data, int data_size)
{
    int top_index = 0;
    int bottom_index = data_size - 1;
    int upward_iterator = bottom_index;

    while(top_index != bottom_index)
    {
        upward_iterator = bottom_index;
        int temp=0;
        while(upward_iterator!=top_index)
        {
            temp = data[upward_iterator-1];
            if(data[upward_iterator]<temp)
            {
                data[upward_iterator-1] = data[upward_iterator];
                data[upward_iterator] = temp;
            }
            upward_iterator--;
        }
        PrintIntArray(g_input_data,sizeof(g_input_data)/sizeof(int),false);
        top_index++;
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
    BubbleSort(g_input_data,sizeof(g_input_data)/sizeof(int));
    PrintIntArray(g_input_data,sizeof(g_input_data)/sizeof(int));
    return 0;
}









