#include <string>
#include <cstring>
#include <iostream>
using namespace std;

int g_input_data[] =
{
    0,30,5,1,2,11,80,3,2,1,30,0
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


void QuickSort(int* data, int data_size, int i, int key)
{
    if(data_size<=1)
    {
        return;
    }
    else
    {
        while(i!=key)
        {
            if(i<key)
            {
                if(data[i] > data[key])
                {
                    int temp = data[i];
                    data[i] = data[key];
                    data[key] = temp;

                    temp = key;
                    key = i;
                    i = temp - 1;
                }
                else
                {
                    i++;
                }
            }
            else if(i>key)
            {
                if(data[i] < data[key])
                {
                    int temp = data[i];
                    data[i] = data[key];
                    data[key] = temp;

                    temp = key;
                    key = i;
                    i = temp + 1;
                }
                else
                {
                    i--;
                }
            }
        }
        PrintIntArray(data,data_size,false);
        QuickSort(data,key,0,key-1);
        QuickSort(data+key+1,data_size-key-1,0,data_size-key-2);
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
    QuickSort(g_input_data,sizeof(g_input_data)/sizeof(int),0,sizeof(g_input_data)/sizeof(int)-1);
    PrintIntArray(g_input_data,sizeof(g_input_data)/sizeof(int));
    return 0;
}









