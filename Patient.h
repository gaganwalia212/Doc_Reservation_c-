#ifndef PATIENT_H_INCLUDED
#define PATIENT_H_INCLUDED

#include <iostream>
#include<winsock.h>
#include"mysql.h"
#include<windows.h>
#include<sstream>
#include<string>
#include<iomanip>
#include<map>
#include<stack>
using namespace std;



class Patient
{
    string id;
    string name;
    int age;
public:
    stack<string> day;
    stack<string>stack_slot;
    map<string,string> arr[3];
    map<string,string> slots;
    int login(MYSQL*conn,string,string);
    int reg(MYSQL*conn,string,string,string,string);
    void display(MYSQL*conn,string);
    void display_slot(MYSQL*conn,string,string);
    void book_appointment(MYSQL*conn);
};

int Patient ::login(MYSQL*conn,string email,string pass)
{
    MYSQL_ROW row;
    MYSQL_RES* res;



    stringstream s;
    s<<"select * from login where (email,password,user)=("<<"'"<<email<<"','"<<pass<<"',0"<<");";
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
            return 1 ;
        }
        if(i==0)
            return 0;


    }
    else
    {
        return 0;
    }

}

int Patient::reg(MYSQL*conn,string email,string pass,string age,string gender)
{
    MYSQL_ROW row;
    MYSQL_RES* res;


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

            return 0;
        }
    }
    int role=0;//for patient
    stringstream s;

    //CODE FOR OTP


    s<<"insert into patients values("<<"'"<<email<<"'"<<",'"<<pass<<"','"<<age<<"','"<<gender<<"');";
    qs=s.str();
     qstate=mysql_query(conn,qs.c_str());
    if(qstate==0)
    {
        cout<<setw(62)<<" "<<"Registration done\n";
        return 1;
    }
    else
    {
        cout<<setw(62)<<" "<<"Registration failed...please try again\n";
        return 2;

    }
    id=email;


}

void Patient::display(MYSQL*conn,string dept)
{
    MYSQL_ROW r1;

    MYSQL_RES* result;


    stringstream s;
    s<<"select * from Booking where Department='"<<dept<<"';";
    string qs=s.str();

    int q_result=mysql_query(conn,qs.c_str());
    if(q_result!=0)
    {
        cout<<setw(62)<<" "<<"Error...Please Try Later\n"<<mysql_error(conn);
        exit(0);
    }
        result=mysql_store_result(conn);
        int i=0;
        while(r1=mysql_fetch_row(result))
        {

            arr[i]["DoctorID"]      = r1[0];
            arr[i]["Department"]    = r1[1];
            arr[i]["Slot1"]         = r1[2];
            arr[i]["Slot2"]         = r1[3];
            arr[i]["Slot3"]         = r1[4];
            arr[i]["Slot4"]         = r1[5];
            arr[i]["Slot5"]         = r1[6];
            arr[i]["avail_day"]     = r1[7];
            i++;
        }
        cout<<"ethe aa raha "<<endl<<arr[0]["DoctorID"]<<endl;
        if((arr[0]["Slot1"]=="None") || (arr[0]["Slot2"]=="None") || (arr[0]["Slot3"]=="None") || (arr[0]["Slot3"]=="None") ||(arr[0]["Slot3"]=="None")||(arr[0]["Slot4"]=="None") ||(arr[0]["Slot5"]=="None"))
           {
             day.push(arr[0]["avail_day"]);
             cout<<arr[0]["avail_day"];
           }

         if((arr[1]["Slot1"]=="None") || (arr[1]["Slot2"]=="None") || (arr[1]["Slot3"]=="None") || (arr[1]["Slot3"]=="None") ||(arr[1]["Slot3"]=="None")||(arr[1]["Slot4"]=="None") ||(arr[1]["Slot5"]=="None"))
           {
             day.push(arr[1]["avail_day"]);
             cout<<arr[1]["avail_day"];
           }

         if((arr[2]["Slot1"]=="None") || (arr[2]["Slot2"]=="None") || (arr[2]["Slot3"]=="None") || (arr[2]["Slot3"]=="None") ||(arr[2]["Slot3"]=="None")||(arr[2]["Slot4"]=="None") ||(arr[2]["Slot5"]=="None"))
           {
             day.push(arr[2]["avail_day"]);
             cout<<arr[2]["avail_day"];
           }

}

void Patient::display_slot(MYSQL*conn,string dept,string day)
{
    MYSQL_ROW r1;
    MYSQL_ROW r2;
    MYSQL_ROW r3;
    MYSQL_RES* result;


    stringstream s;
    s<<"select * from Booking where avail_day = '"<<day<<"' && Department='"<<dept<<"';";
    string qs=s.str();

    int q_result=mysql_query(conn,qs.c_str());
    if(q_result!=0)
    {
        cout<<setw(62)<<" "<<"Error...Please Try Later\n"<<mysql_error(conn);
        exit(0);
    }
        result=mysql_store_result(conn);

        while(r1=mysql_fetch_row(result))
        {

            slots["DoctorID"]      = r1[0];
            slots["Department"]    = r1[1];
            slots["Slot1"]         = r1[2];
            slots["Slot2"]         = r1[3];
            slots["Slot3"]         = r1[4];
            slots["Slot4"]         = r1[5];
            slots["Slot5"]         = r1[6];
            slots["avail_day"]     = r1[7];

            cout<<slots["Slot1"];

        }
        cout<<endl<<endl<<"ethe aya:;";
        if(slots["Slot1"]=="None")
            stack_slot.push("Slot1");
        if(slots["Slot2"]=="None")
            stack_slot.push("Slot2");
        if(slots["Slot3"]=="None")
            stack_slot.push("Slot3");
        if(slots["Slot4"]=="None")
            stack_slot.push("Slot4");
        if(slots["Slot5"]=="None")
            stack_slot.push("Slot5");



}

void Patient::book_appointment(MYSQL*conn)
{


}

#endif // PATIENT_H_INCLUDED
