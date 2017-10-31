/*************************************************************************
	> File Name: writeCanMsg.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年10月29日 星期日 17时11分13秒
 ************************************************************************/

#include<iostream>
#include<canlib.h>
#include<string.h>
#include<unistd.h>
using namespace std;

int main()
{
    canInitializeLibrary();
    canHandle hnd;
    canStatus stat;
    
    int channel = 0;

    hnd = canOpenChannel(channel, canOPEN_ACCEPT_VIRTUAL);
    if (hnd < 0) 
    {
        cout<<"Channel 0 Open failed!";
    }
    else
    {
        cout<<"Channel 0 is open!"<<endl;
    }
    
    stat = canSetBusParams(hnd,canBITRATE_1M, 0, 0, 0, 0, 0);
    if(stat!=canOK)
    {
        cout<<"canSetBusParams not successful!"<<endl;
    }
    else
    {
        cout<<"canSetBusParams successful!"<<endl;
    }

    stat = canBusOn(hnd);
    if(stat!=canOK)
    {
        cout<<"canBusOn not successful!"<<endl;
    }
    else
    {
        cout<<"canBusOn successful!"<<endl;
    }

    unsigned char data[8];
    for(int i=0;i<8;i++)
    {
        data[i]='a';
    }

    //cout<<"The size of is "<<sizeof(data)<<" bytes!"<<endl;

    while(1)
    {
        stat = canWrite(hnd,1234,data,8,canMSG_EXT);
        if(stat<0)
        {
            cout<<"Oops, Can Message Write unsuccessful!"<<endl;
        }
        else
        {
            cout<<"Congratulations! Can Message Write successful!"<<endl;
        }
        sleep(1);
    }

    canClose(hnd);

    return 0;
}
