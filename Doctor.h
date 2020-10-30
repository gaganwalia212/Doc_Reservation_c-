#ifndef DOCTOR_H_INCLUDED
#define DOCTOR_H_INCLUDED

#include<cstdlib>
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
    string dept;
public:
    void login(MYSQL*conn);
    string display_appointments(MYSQL*conn);
};

void Doctor::login(MYSQL*conn)
{
    system("cls");
    cout<<setw(62)<<setfill('_')<<" "<<setfill(' ')<<"DOCTOR LOGIN";
    cout<<setw(50)<<setfill('_')<<" "<<setfill(' ')<<endl;
    MYSQL_ROW row;
    MYSQL_RES* res;
    string email,pass;
    cout<<setw(62)<<" "<<"Enter email:";
    cin>>email;
    cout<<setw(62)<<" "<<"Enter password:";
    cin>>pass;
    stringstream s;
    s<<"select * from Doctors where (email,pass)=("<<"'"<<email<<"','"<<pass<<"');";
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
            dept=row[2];
            return ;
        }
        if(i==0)
        {
            cout<<setw(62)<<" "<<"Incorrect password or email....Try Again\n";
            exit(0);
        }

    }
    else
    {
        cout<<setw(62)<<" "<<"Error in login ..please try again\n";
        exit(0);
    }
}


//this function will return a string
//each line on string will contain information about the appointment
string Doctor::display_appointments(MYSQL*conn)
{     system("cls");
    cout<<setw(62)<<setfill('_')<<" "<<setfill(' ')<<"YOUR APPOINTMENTS";
    cout<<setw(50)<<setfill('_')<<" "<<setfill(' ')<<endl;

    //string stream whose string will be returned
    stringstream final_stream;
    int success=0;
        stringstream s;
        s.clear();
        s.str("");
        s<<"Select * from Booking where Department='"<<dept<<"';";
         string q=s.str();
        int qstate=mysql_query(conn,q.c_str());
        if(qstate!=0)
        {
            cout<<setw(62)<<" "<<"Error..please try again\n";
            exit(0);
        }
        MYSQL_RES *result=mysql_store_result(conn);
        MYSQL_ROW row;
        int i=0;
        while(row=mysql_fetch_row(result))
        {

            for(int k=2;k<=6;k++)
            {
                if(strcmp(row[k],"None")!=0)
                {
                    i++;
                    stringstream temp;
                    temp<<row[7]<<":"<<" "<<"["<<k-1<<"]  "<<row[k];
                    final_stream<<temp.str()<<endl;
                }
            }
        }
        if(i==0)
        {
            return string("No Appointments\n");
        }

    return final_stream.str();
}


#endif // DOCTOR_H_INCLUDED
