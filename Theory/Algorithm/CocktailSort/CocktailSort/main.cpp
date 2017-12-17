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

void CocktailSort(int* data, int data_size)
{
    int begin_index = 0;
    int end_index = data_size - 1;
    ETraversingDirction direction = kTraversingDirction_Backward;

    int forward_iterator;
    int backward_iterator;
    while(begin_index != end_index)
    {
        backward_iterator = begin_index;
        forward_iterator = end_index;
        while(forward_iterator!=backward_iterator)
        {
            int temp=0;
            switch (direction)
            {
            case kTraversingDirction_Backward:
            {
                if(data[backward_iterator]>data[backward_iterator+1])
                {
                    temp = data[backward_iterator];
                    data[backward_iterator] = data[backward_iterator+1];
                    data[backward_iterator+1] = temp;
                }
                backward_iterator++;
                break;
            }
            case kTraversingDirction_Forward:
            {
                if(data[forward_iterator]<data[forward_iterator-1])
                {
                    temp = data[forward_iterator];
                    data[forward_iterator] = data[forward_iterator-1];
                    data[forward_iterator-1] = temp;
                }
                forward_iterator--;
                break;
            }
            default:
                break;
            }
        }
        switch (direction)
        {
        case kTraversingDirction_Backward:
        {
            direction = kTraversingDirction_Forward;
            end_index--;
            break;
        }
        case kTraversingDirction_Forward:
        {
            direction = kTraversingDirction_Backward;
            begin_index++;
            break;
        }
        default:
            break;
        }
        PrintIntArray(g_input_data,sizeof(g_input_data)/sizeof(int),false);
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
    CocktailSort(g_input_data,sizeof(g_input_data)/sizeof(int));
    PrintIntArray(g_input_data,sizeof(g_input_data)/sizeof(int));
    return 0;
}









