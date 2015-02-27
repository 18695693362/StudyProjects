#coding=utf-8
#author:guodong

import os
import os.path
import sys

days_in_month = [31,28,31,30,31,30,31,31,30,31,30,31]

def main():
    while True:
        month = input("Please Input Month:")
        if type(month)==int:
            print("Days in "+str(month)+" is " + str(days_in_month[month-1]))
        else:
            print("Input "+ str(month) +" isn't month! please retry!")
    
if __name__ == '__main__':
    main()
else:
    print(__name__)
    main()

