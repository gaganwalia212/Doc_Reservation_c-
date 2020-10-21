#include"Patient.h"
#include"Doctor.h"
#define database_name "izbe2a6Gri"
#define username "izbe2a6Gri"
#define password "9MnXblPN0F"
MYSQL*conn;
int main()
{

    conn  = mysql_init(0);
    conn =mysql_real_connect(conn,"remotemysql.com",username,password,database_name,3306,NULL,0);

if(conn==0)
{
    cout<<"Error\n";
    mysql_close(conn);
    exit(0);
}

cout<<setw(40)<<" "<<setw(40)<<setfill('=')<<"GAME OF THRONES HOSPITAL"<<setw(20)<<" \n";
cout<<setfill(' ');
cout<<setw(62)<<" "<<"1-DOCTOR\n";
cout<<setw(62)<<" "<<"2-PATIENT\n";
cout<<setw(40)<<" "<<setw(60)<<setfill('=')<<" \n"<<setfill(' ');
cout<<setw(62)<<" ";
int input;
cin>>input;

if(input==1)
{
cout<<setfill(' ');
cout<<setw(62)<<" "<<"1-Register\n";
cout<<setw(62)<<" "<<"2-Login\n";
cout<<setw(84)<<setw('=')<<" \n"<<setfill(' ');
cout<<setw(62)<<" ";
int in;
cin>>in;
Doctor doc;
if(in==1)
    doc.reg(conn);
if(in==2)
    doc.login(conn);

    //other functionalities will  be there after login or registration

}

if(input==2)
{

cout<<setfill(' ');
cout<<setw(62)<<" "<<"1-Register\n";
cout<<setw(62)<<" "<<"2-Login\n";
cout<<setw(84)<<setw('=')<<" "<<setfill(' ')<<endl;
cout<<setw(62)<<" ";

int in;
cin>>in;
Patient p;
if(in==1)
    p.reg(conn);
if(in==2)
    p.login(conn);
cout<<endl;
cout<<setw(40)<<" "<<setw(60)<<setfill('=')<<" "<<setfill(' ');
cout<<endl;
cout<<setw(62)<<" "<<"1-Display list of doctors\n";
cout<<setw(62)<<" "<<"2-Book Appointment\n";
cin>>in;
if(in==1)
    p.display(conn);

if(in==2)
{
    p.book_appointment(conn);
}
  mysql_close(conn);
    return 0;
}
}
