#ifndef DOCTOR_H_INCLUDED
#define DOCTOR_H_INCLUDED

#include <iostream>
#include<winsock.h>
#include"mysql.h"
#include<windows.h>
#include<sstream>
#include<string>
#include<iomanip>
using namespace std;

class Doctor
{
    string id;
public:
    void login(MYSQL*conn);
    void reg(MYSQL*conn);
};

void Doctor::login(MYSQL*conn)
{
    MYSQL_ROW row;
    MYSQL_RES* res;
    string email,pass;
    cout<<setw(62)<<" "<<"Enter email:";
    cin>>email;
    cout<<setw(62)<<" "<<"Enter password:";
    cin>>pass;
    stringstream s;
    s<<"select * from login where (email,password,user)=("<<"'"<<email<<"','"<<pass<<"',1"<<");";
    string qs=s.str();
    int qstate=mysql_query(conn,qs.c_str());
    if(qstate==0)
    {
         res = mysql_store_result(conn);
         int i=0;
        while(row = mysql_fetch_row(res))
        {
            i=1;
            cout<<endl<<endl<<setw(62)<<" "<<"-----Welcome-----"<<endl;
            cout<<setw(62)<<" "<<setw(30)<<left<<row[0]<<setw(20)<<row[1]<<setw(20)<<row[2];
            id=row[0];
            return ;
        }
        if(i==0)
            cout<<setw(62)<<" "<<"Incorrect password or email....Try Again\n";

    }
    else
    {
        cout<<setw(62)<<" "<<"Error in login ..please try again\n";
        exit(0);
    }
}


void Doctor::reg(MYSQL*conn)
{
    MYSQL_ROW row;
    MYSQL_RES* res;

    string email,pass,confirm;
    cout<<setw(62)<<" "<<"Enter email:";
    cin>>email;
    cout<<setw(62)<<" "<<"Enter Password:";
    cin>>pass;
    cout<<setw(62)<<" "<<"Confirm Password:";
    cin>>confirm;
    while(confirm!=pass)
    {
        cout<<setw(62)<<" "<<"Password does not match\n";
        cout<<setw(62)<<" "<<"Enter Password:";
        cin>>pass;
        cout<<setw(62)<<" "<<"Confirm Password:";
        cin>>confirm;
    }
    stringstream s1;
    s1<<"select * from login where email='"<<email<<"';";

    string qs=s1.str();
    int qstate=mysql_query(conn,qs.c_str());
    if(qstate==0)
    {
        res=mysql_store_result(conn);
        int i=0;
        while(row=mysql_fetch_row(res))
            i++;

        if(i!=0)
        {
            cout<<setw(62)<<" "<<"Email address already exists\n";
            cout<<setw(62)<<" "<<"Please Login:\n";
            login(conn);
            return;
        }
    }
    int role=1;//for doctor
    stringstream s;

    //CODE FOR OTP


    s<<"insert into login values("<<"'"<<email<<"'"<<",'"<<pass<<"','"<<role<<"');";
    qs=s.str();
     qstate=mysql_query(conn,qs.c_str());
    if(qstate==0)
    {
        cout<<setw(62)<<" "<<"Registration done\n";
    }
    else
    {
        cout<<setw(62)<<" "<<"Registration failed...please try again\n";
        exit(0);
    }
    id=email;
    return ;
}


#endif // DOCTOR_H_INCLUDED
