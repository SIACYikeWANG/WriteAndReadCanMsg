/*************************************************************************
	> File Name: readCanMsg.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年10月30日 星期一 10时44分31秒
 ************************************************************************/

#include<iostream>
#include<canlib.h>
#include<string.h>

using namespace std;

int main()
{
    canInitializeLibrary();
    canHandle hnd;
    int channel = 0;
    canStatus stat;

    hnd = canOpenChannel(channel,canOPEN_ACCEPT_VIRTUAL);
    if(hnd<0)
    {
        cout<<"Can Open not successful!"<<endl;
    }
    else
    {
        cout<<"Can Open successful!"<<endl;
    }

    stat = canSetBusParams(hnd,canBITRATE_1M,0,0,0,0,0);
    if(stat!=canOK)
    {
        cout<<"canSetBusParams not successful!"<<endl;
    }
    else
    {
        cout<<"canSetBusParams successful!"<<endl;
    }

    stat=canBusOn(hnd);
    if(stat!=canOK)
    {
        cout<<"canBusOn not successful!"<<endl;
    }
    else
    {
        cout<<"canBusOn successful!"<<endl;
    }

    unsigned char data[8];
    long id = 1234;
    unsigned int dlc = 8;
    unsigned int flags = canMSG_EXT;
    memset(data,0,sizeof(data));
    unsigned long timestamp;

    while(1)
    {
        stat = canReadWait(hnd,&id,data,&dlc,&flags,&timestamp,250);    
        cout<<"stat = "<<stat<<endl;
        // stat = canRead(hnd,1234,data,8,canMSG_EXT,&timestamp);
        if(stat!=canERR_NOMSG)
        {
            cout<<"Can Read successful!"<<endl;
            cout<<"Data is received as ";
            for(int i=0;i<8;i++)
            {
                cout<<data[i];
            }
            cout<<endl;
        }
    }

    canClose(hnd);

    return 0;
}

