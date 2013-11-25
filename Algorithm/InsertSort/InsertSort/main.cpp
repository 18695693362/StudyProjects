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

void InsertSort(int* data, int data_size)
{
    for(int i=1; i<data_size; i++)
    {
        for(int j=i; j>0; j--)
        {
            if(data[j]<data[j-1])
            {
                int temp = data[j-1];
                data[j-1] = data[j];
                data[j] = temp;
            }
            else
            {
                break;
            }
        }
        PrintIntArray(g_input_data,sizeof(g_input_data)/sizeof(int),false);
    }
}

int main(int argc, char* argv[])
{
    cout << "Hello Algorithm!" << endl;

    PrintIntArray(g_input_data,sizeof(g_input_data)/sizeof(int));
    InsertSort(g_input_data,sizeof(g_input_data)/sizeof(int));
    PrintIntArray(g_input_data,sizeof(g_input_data)/sizeof(int));
    return 0;
}









