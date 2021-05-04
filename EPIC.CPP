#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
struct date
 {
  int d,m,y;
  int chkdate();
 };
int date::chkdate()
{
 int maxyr=2020;
 int minyr=1500;

 if(y>maxyr || y<minyr || d>31 || m>12)
 {
  return 0;
 }

 int leap=0;
 if(y%4==0 && y%100!=0 || y%400==0)
  leap=1;

 if(m==2)
 {
  if(leap==1)
   return (d<=29);
  else
   return (d<=28);
 }
 else if(m==4 || m==6 || m==9 || m==11)
 {
  return (d<=30);
 }
 else return 1;
}


class epic
{
 private:
  int voter_id;
  char name[20];
  char fname[20];
  char gender;
  date dob;
  date doi;
  char address[80];

 public:
  void getd();
  void showd()
  {
  cout<<"\n voter id number\t";
  cout<<voter_id;
  cout<<"\nname\t";
  cout<<name;
  cout<<"\nfather's name\t";
  puts(fname);
  cout<<"gender\t";
  cout<<gender;
  cout<<"\n date of birth (dd/mm/yyyy format)\t";
  cout<<dob.d<<dob.m<<dob.y;;
  cout<<"\n date of issue (dd/mm/yyyy format)\t";
  cout<<doi.d<<doi.m<<doi.y;
  cout<<"\n address\t";
  puts(address);
  }

  char* retn()
  {
  return name;
  }

  char* retfn()
  {
  return fname;
  }

  int retvid()
  {
  return voter_id;
  }

  char retgen()
  {
  return gender;
  }

  date retdob()
  {
  return dob;
  }

  date retdoi()
  {
  return doi;
  }

};
void epic::getd()
  {
   cout<<"\nenter voter id number\t";
   cin>>voter_id;
   cout<<"\nenter name\t";
   gets(name);
   cout<<"\nenter father's name\t";
   gets(fname);
   cout<<"\nenter gender\t";
   cin>>gender;

   int dchk=0;
   while(dchk==0)
   {
    cout<<"\nenter date of birth (dd/mm/yyyy format)\t";
    cin>>dob.d>>dob.m>>dob.y;
    dchk=dob.chkdate();
    if(dchk==0)
     cout<<"invalid date";
   }

   dchk=0;
   while(dchk==0)
   {
    cout<<"\nenter date of issue \t";
    cin>>doi.d>>doi.m>>doi.y;
    dchk=doi.chkdate();
    if(dchk==0)
     cout<<"invalid date";
   }
   cout<<"\nenter address\t";
   gets(address);
  }


fstream f;
epic e,e1;
void create()
{
 f.open("epic.dat",ios::out|ios::binary);
 char ans;

 do{
  e.getd();
  f.write((char*)&e,sizeof(e));
  cout<<"do you want to continue : ";
  cin>>ans;
 }while(ans=='y');
 f.close();
}
void readall()
{
 f.open("epic.dat",ios::in|ios::binary);
 while(f.read((char*)&e,sizeof(e)))
 e.showd();
 f.close();
}

void countall()
{
 f.open("epic.dat",ios::in|ios::binary);
 int ctr=0;
 while(f.read((char*)&e,sizeof(e)))
 ctr++;
 cout<<"\nnumber of records"<<ctr;
 f.close();
}
void count_gender()
{
 char g;
 cout<<"enter gender";
 cin>>g;
 f.open("epic.dat",ios::in|ios::binary);
 int ctr=0;
 while(f.read((char*)&e,sizeof(e)))
 {
  if(e.retgen()==g)
  ctr++;
 }
 cout<<"\nnumber of records with gender"<<g<<"\t"<<ctr;
 f.close();
}

void scr_name()
{
 char sname[20];
 cout<<"enter sname";
 gets(sname);
 f.open("epic.dat",ios::in|ios::binary);
 while(f.read((char*)&e,sizeof(e)))
 {
  if(strcmpi(e.retn(),sname)==0)
  e.showd();
  break;
 }
 f.close();
}

void scr_fn()
{
 char sfn[20];
 cout<<"enter fathers name search  ";
 gets(sfn);
 f.open("epic.dat",ios::in|ios::binary);
 while(f.read((char*)&e,sizeof(e)))
 {
  if(strcmpi(e.retfn(),sfn)==0)
  e.showd();
  break;
 }
 f.close();
}

void scr_id()
{
 int sid;
 cout<<"enter voter id to be search   ";
 cin>>sid;
 f.open("epic.dat",ios::in|ios::binary);
 while(f.read((char*)&e,sizeof(e)))
 {
  if(e.retvid()==sid)
  e.showd();
  break;
 }
 f.close();
}

void count_yob()
{
 int ctr=0,yob;
 date tempd;
 cout<<"enter year";
 cin>>yob;
 f.open("epic.dat",ios::in|ios::binary);
 while(f.read((char*)&e,sizeof(e)))
 {
  tempd=e.retdob();
  if(tempd.y==yob)
  ctr++;
 }
 cout<<"\nnumber of records with same yob :\t"<<ctr;
 f.close();
}

void count_yoi()
{
 int ctr=0,yoi;
 date tempd;
 cout<<"enter year";
 cin>>yoi;
 f.open("epic.dat",ios::in|ios::binary);
 while(f.read((char*)&e,sizeof(e)))
 {
  tempd=e.retdoi();
  if(tempd.y==yoi)
  ctr++;
 }
 cout<<"\nnumber of records with same yob :\t"<<ctr;
 f.close();
}

void delfst()
{
 fstream temp;
 f.open("epic.dat",ios::in|ios::binary);
 temp.open("new.dat",ios::out|ios::binary);
 f.read((char*)&e,sizeof(e));
 while(f.read((char*)&e,sizeof(e)))
 {
  temp.write((char*)&e,sizeof(e));
 }
 temp.close();
 f.close();
 remove("epic.dat");
 rename("new.dat","epic.dat");
}

void dellst()
{
 fstream temp;
 f.open("epic.dat",ios::in|ios::binary);
 temp.open("new.dat",ios::out|ios::binary);
 f.seekg(0,ios::end);
 int lp=f.tellg();
 int s=sizeof(e),r=1;
 cout<<"\nnumber of records"<<lp/s;
 f.seekg(0);
 while(f.read((char*)&e,sizeof(e)))
 {
  if(r!=lp/s)
   temp.write((char*)&e,sizeof(e));
  r++;
 }
 temp.close();
 f.close();
 remove("epic.dat");
 rename("new.dat","epic.dat");
}

void delrecno()
{
 fstream temp;
 f.open("epic.dat",ios::in|ios::binary);
 temp.open("new.dat",ios::out|ios::binary);
 int r=1,dr;
 cout<<"\nenter rec no. to delete";
 cin>>dr;
 f.seekg(0);
 while(f.read((char*)&e,sizeof(e)))
 {
  if(r!=dr)
   temp.write((char*)&e,sizeof(e));
  r++;
 }
 temp.close();
 f.close();
 remove("epic.dat");
 rename("new.dat","epic.dat");
}

void delvid()
{
 fstream temp;
 f.open("epic.dat",ios::in|ios::binary);
 temp.open("new.dat",ios::out|ios::binary);
 int mvid;
 cout<<"\nenter voter id to delete";
 cin>>mvid;
 f.seekg(0);
 while(f.read((char*)&e,sizeof(e)))
 {
  if(e.retvid()!=mvid)
   temp.write((char*)&e,sizeof(e));
 }
 temp.close();
 f.close();
 remove("epic.dat");
 rename("new.dat","epic.dat");
}

void delname()
{
 fstream temp;
 f.open("epic.dat",ios::in|ios::binary);
 temp.open("new.dat",ios::out|ios::binary);
 char mname[20];
 cout<<"\nenter name to delete";
 cin>>mname;
 f.seekg(0);
 while(f.read((char*)&e,sizeof(e)))
 {
  if(strcmp(e.retn(),mname)!=0)
   temp.write((char*)&e,sizeof(e));
 }
 temp.close();
 f.close();
 remove("epic.dat");
 rename("new.dat","epic.dat");
}

void inslst()
{
 fstream temp;
 f.open("epic.dat",ios::in|ios::binary);
 temp.open("new.dat",ios::out|ios::binary);
 e1.getd();
 while(f.read((char*)&e,sizeof(e)))
 {
  temp.write((char*)&e,sizeof(e));
 }
 temp.write((char*)&e1,sizeof(e1));
 temp.close();
 f.close();
 remove("epic.dat");
 rename("new.dat","epic.dat");
}


void insfst()
{
 fstream temp;
 f.open("epic.dat",ios::in|ios::binary);
 temp.open("new.dat",ios::out|ios::binary);
 e1.getd();
 temp.write((char*)&e1,sizeof(e1));
 while(f.read((char*)&e,sizeof(e)))
 {
  temp.write((char*)&e,sizeof(e));
 }
 temp.close();
 f.close();
 remove("epic.dat");
 rename("new.dat","epic.dat");
}


void insnth()
{
 fstream temp;
 f.open("epic.dat",ios::in|ios::binary);
 temp.open("new.dat",ios::out|ios::binary);
 int r=0;
 int ir;
 cout<<"\nenter record number at which you want to insert";
 cin>>ir;
 e1.getd();
 while(f.read((char*)&e,sizeof(e)))
 {
  r++;
  if(ir==r)
   temp.write((char*)&e1,sizeof(e1));
  temp.write((char*)&e,sizeof(e));
 }
 temp.close();
 f.close();
 remove("epic.dat");
 rename("new.dat","epic.dat");
}

void insvid()
{
 fstream temp;
 f.open("epic.dat",ios::in|ios::binary);
 temp.open("new.dat",ios::out|ios::binary);
 int mvid;
 cout<<"\nenter voter id after which you want to insert";
 cin>>mvid;
 while(f.read((char*)&e,sizeof(e)))
 {
  temp.write((char*)&e,sizeof(e));
  if(e.retvid()==mvid)
  {
   e1.getd();
   temp.write((char*)&e1,sizeof(e1));
  }
 }
 temp.close();
 f.close();
 remove("epic.dat");
 rename("new.dat","epic.dat");
}

void insname()
{
 fstream temp;
 f.open("epic.dat",ios::in|ios::binary);
 temp.open("new.dat",ios::out|ios::binary);
 char mname[20];
 cout<<"\nenter name after which you want to insert";
 cin>>mname;
 while(f.read((char*)&e,sizeof(e)))
 {
  temp.write((char*)&e,sizeof(e));
  if(strcmpi(e.retn(),mname)==0)
  {
   e1.getd();
   temp.write((char*)&e1,sizeof(e1));
  }
 }
 temp.close();
 f.close();
 remove("epic.dat");
 rename("new.dat","epic.dat");
}

void editnth()
{
 fstream temp;
 f.open("epic.dat",ios::in|ios::binary);
 temp.open("new.dat",ios::out|ios::binary);
 int r=0;
 int rec;
 cout<<"enter rec no. to edit";
 cin>>rec;
 while(f.read((char*)&e,sizeof(e)))
 {
  r++;
  if(r==rec)
  {
   e1.getd();
   temp.write((char*)&e1,sizeof(e1));
  }
  else
  temp.write((char*)&e,sizeof(e));
 }
 temp.close();
 f.close();
 remove("epic.dat");
 rename("new.dat","epic.dat");
}

void editname()
{
 fstream temp;
 f.open("epic.dat",ios::in|ios::binary);
 temp.open("new.dat",ios::out|ios::binary);
 char mname[20];
 cout<<"enter name to edit";
 cin>>mname;
 while(f.read((char*)&e,sizeof(e)))
 {
  if(strcmpi(e.retn(),mname)==0)
  {
   e1.getd();
   temp.write((char*)&e1,sizeof(e1));
  }
  else
  temp.write((char*)&e,sizeof(e));
 }
 temp.close();
 f.close();
 remove("epic.dat");
 rename("new.dat","epic.dat");
}

void editvid()
{
 fstream temp;
 f.open("epic.dat",ios::in|ios::binary);
 temp.open("new.dat",ios::out|ios::binary);
 int mvid;
 cout<<"enter vid to edit";
 cin>>mvid;
 while(f.read((char*)&e,sizeof(e)))
 {
  if(e.retvid()==mvid)
  {
   e1.getd();
   temp.write((char*)&e1,sizeof(e1));
  }
  else
  temp.write((char*)&e,sizeof(e));
 }
 temp.close();
 f.close();
 remove("epic.dat");
 rename("new.dat","epic.dat");
}

void count_grtyr()
{
 int ctr=0,myr;
 cout<<"enter year";
 cin>>myr;
 date tempd;
 f.open("epic.dat",ios::in|ios::binary);
 while(f.read((char*)&e,sizeof(e)))
 {
  tempd=e.retdoi();
  if(tempd.y<myr)
  ctr++;
 }
 cout<<"\nnumber of records with greater age:\t"<<ctr;
 f.close();
}

void main()
{
 clrscr();
 char ans1='y';
 do
 {
 int ch,chk;
 cout<<"\n-------------------------------------------------------------------------------";
 cout<<"\n                         welcome to epic database";
 cout<<"\n-------------------------------------------------------------------------------";
 cout<<"\nwhat do you want to do? " ;
 cout<<"\n1.create database";
 cout<<"\n2.show records" ;
 cout<<"\n3.count records";
 cout<<"\n4.edit record";
 cout<<"\n5.search record";
 cout<<"\n6.delete record";
 cout<<"\n7.insert record" ;
 cout<<"\nenter your choice" ;
 cin>>ch;
 switch(ch)
 {
 case 1:
	 create();
	 break;
 case 2:
	 readall();
	 break;
 case 3:
	 int ch1;
	 cout<<"\n1.count all the records";
	 cout<<"\n2.count on gender";
	 cout<<"\n3.count on year of birth";
	 cout<<"\n4.count on year of issue";
	 cout<<"\n5.count records with age>than given age";
	 cout<<"\nenter choice";
	 cin>>ch1;
	 switch(ch1)
	   {
	     case 1:
		    countall();
		    break;

	     case 2:
		    count_gender();
		    break;
	     case 3:
		    count_yob();
		    break;
	     case 4:
		    count_yoi();
		    break;
	     case 5:
		    count_grtyr();
		    break;

	     default :
		    cout<<"wrong choice";
	    }
	 break;

 case 4:
	int ch2;
	cout<<"\n1.edit nth record ";
	cout<<"\n2.edit name";
	cout<<"\n3.edit voter id";
	cout<<"\nenter choice";
	cin>>ch2;
	switch(ch2)
	 {
	  case 1:
		 editnth();
		 break;

	  case 2:
		 editname();
		 break;

	  case 3:
		 editvid();
		 break;

	 default :
		cout<<"wrong choice";
	 }
	 break;
case 5:
       int ch3;
       cout<<"\n1.search on name" ;
       cout<<"\n2.search on id";
       cout<<"\n3.search on father's name" ;
       cout<<"\nenter choice";
       cin>>ch3;
       switch(ch3)
       {
	 case 1:
		scr_name();
		break;

	 case 2:
		scr_id();
		break;

	 case 3:
	       scr_fn();
	       break;

	 default :
	       cout<<"wrong choice";
	 }
	 break;

case 6:int ch4;
       cout<<"\n1.delete first record ";
       cout<<"\n2.delete last record";
       cout<<"\n3.delete according to record no.";
       cout<<"\n4.delete according to voter id";
       cout<<"\n5.delete according to name";
       cout<<"\nenter choice";
       cin>>ch4;
       switch(ch4)
       {
	case 1:
	       delfst();
	       break;

	case 2:
	       dellst();
	       break;

	case 3:
	       delrecno();
	       break;

	case 4:
	       delvid();
	       break;

	case 5:
	       delname();
	       break;

	default:
		cout<<"wrong choice";
		break;

	}
	 break;
 case 7:
	int ch5;
	cout<<"\n1.insert first record";
	cout<<"\n2.insert last";
	cout<<"\n3.insert nth record";
	cout<<"\n4.insert voter id";
	cout<<"\n5.insert name";
	cout<<"\nenter choice";
	cin>>ch5;
	switch(ch5)
	{
	 case 1:
		insfst();
		break;

	 case 2:
		insnth();
		break;

	 case 3:
		insvid();
		break;

	 case 4:
		insname();
		break;

	 default:
		 cout<<"\nwrong choice";
		 break;
	  }
	  break;
 default:
	 cout<<"wrong choice";
 }
 cout<<"\ndo you want to continue?";
 cin>>ans1;
 }while(ans1=='y'||ans1=='Y');
 getch();

}




