#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<fstream.h>
#include<process.h>
#include<graphics.h>
#include<dos.h>

class supermarket
{
   int pno;
   char pname[50];
   float price,qty,amt;
   public:
      void create_products()
      {
	 cout<<"\n  Enter the product no: ";
	 cin>>pno;
	 cout<<"\n  Enter the product name: ";
	 gets(pname);
	 cout<<"\n  Enter the price: ";
	 cin>>price;
      }
      void admin_menu();
      void write_products();
      void read_products();
      void delete_products();
      void search_products();
      void place_order();
      void intro();
      void head();
      void end1();
}sm;
void main()
{
   clrscr();
   sm.intro();
   char ch;
   clrscr();
   do
   {
	clrscr();
	cout<<"\n\t\t\t        _____MAIN MENU_____        ";
	cout<<"\n\n\n\t\t\t1.Operations regarding product list";
	cout<<"\n\n\t\t\t2.Place an order and print the bill";
	cout<<"\n\n\t\t\t3.Exit the program";
	cout<<"\n\n\n\t\t\tEnter your choice (1-3): ";
	cin>>ch;
	switch(ch)
       {
	   case '1':
		    clrscr();
		    sm.admin_menu();
		    break;
	  case '2':
		    clrscr();
		    sm.place_order();
		    getch();
		    break;
	  case '3':
		    sm.end1();
		    exit(0);
	  default: cout<<"\a";
       }
    }while(ch!=3);
}

void supermarket::admin_menu()
{
    clrscr();
    head();
    char ch2;
    cout<<"\t\t\t     _____OPERATIONS MENU_____     ";
    cout<<"\n\n\t\t\t1. Create product list";
    cout<<"\n\t\t\t2. Search the details of the products";
    cout<<"\n\t\t\t3. Delete a product from the list";
    cout<<"\n\t\t\t4. Display the product list";
    cout<<"\n\t\t\t5. Go back to main menu";
    cout<<"\n\n\t\t\tEnter your choice (1-6): ";
    cin>>ch2;
    switch(ch2)
    {
	case '1':
		  clrscr();
		  head();
		  write_products();
		  getch();
		  break;
	case '2':
		  clrscr();
		  head();
		  search_products();
		  getch();
		  break;

	case '3':
		  clrscr();
		  head();
		  delete_products();
		  getch();
		  break;
	case '4':
		  clrscr();
		  head();
		  read_products();
		  getch();
		  break;
	case '5':
		  break;
	default:
		  cout<<"\a";
		  admin_menu();
      }
}
void supermarket::write_products()
{
    sm.create_products();
    ofstream ofile;
    ofile.open("itemlist.dat",ios::app|ios::binary);
    ofile.write((char*)&sm,sizeof(sm));
    ofile.close();
    cout<<"\n\n\n  PRODUCT ADDED...";
}
void supermarket::read_products()
{
    ifstream ifile;
    ifile.open("itemlist.dat",ios::in|ios::binary);
    cout<<"\n Displaying all the products: \n";
    cout<<"\n\n\n\t\tNo.\t\tName\t\tPrice";
    cout<<"\n\t\t_________________________________________";
    while(ifile.read((char*)&sm,sizeof(sm)))
    {
       cout<<"\n\t\t"<<pno<<"\t\t"<<pname<<"\t\t"<<price;
    }
    cout<<"\n\n\n\t\t==========================================";
    ifile.close();
}
void supermarket::search_products()
{
    int rno,f=0;
    cout<<"\n  Enter no to searched:";
    cin>>rno;
    ifstream ifile;
    ifile.open("itemlist.dat",ios::in|ios::binary);
    cout<<"\n  Displaying Records...";
    cout<<"\n\n\n\t\tNo.\t\tName\t\tPrice";
    cout<<"\n\t\t__________________________________________";
    while(ifile.read((char*)&sm,sizeof(sm)))
   {
      if(rno==pno)
      {
	 cout<<"\n\t\t"<<pno<<"\t\t"<<pname<<"\t\t"<<price;
	 f=1;
	 cout<<"\n\n\n\t\t==========================================";
      }
   }
  if(f==0)
  cout<<"\n\t\tNO RECORD\n"
      <<"\n\n\n\t\t==========================================";
}
void supermarket::delete_products()
{
    int rno,f=0;
    cout<<"\n  Enter the no. of the product to be deleted: ";
    cin>>rno;
    ifstream ifile;
    ifile.open("itemlist.dat",ios::in|ios::binary);
    ofstream ofile;
    ofile.open("temp.dat",ios::app|ios::binary);
    while(ifile.read((char*)&sm,sizeof(sm)))
    {
      if(rno!=sm.pno)
      {
	ofile.write((char*)&sm,sizeof(sm));
	f=1;
      }
    }
    if(f==0)
       cout<<"\n\n  RECORD DELETED";
    ifile.close();
    ofile.close();
    remove("itemlist.dat");
    rename("temp.dat","itemlist.dat");
}
void supermarket::place_order()
{
    int order_arr[50],quan[50],c=0,disc;
    float damt, total = 0;
    char ch = 'Y';
    ifstream ifile;
    cout << "\n============================";
    cout << "\n PLACE YOUR ORDER";
    cout << "\n============================\n";
    do
    {
	clrscr();
	read_products();
	cout << "\n\n  Enter The Product No. Of The Product : ";
	cin >> order_arr[c];
	cout << "\n  Quantity in number : ";
	cin >> quan[c];
	c++;
	cout<<"\n  Enter the discount to be given (in %): ";
	cin>>disc;
	cout << "\n  Do You Want To Order Another Product ?(y/n):";
	cin >> ch;
    } while ((ch == 'y' || ch == 'Y')&&(!ifile.eof()));
    if(!ifile)
    {
       cout<<"\n No items in the list...Please add some items in ADMINISTRATOR SETTINGS";
       getch();
    }
    cout << "\n\n\n\t\t<<<<<<<< Thank You For Placing The Order >>>>>>>>";

    getch();
    clrscr();
    cout << "\n*********************************** INVOICE ************************************";
    cout <<"\nPr No.\tPr Name\t  Qty.\tPrice\t\tAmount\t\tAmount after discount\n "
	 <<"\n================================================================================";
    for (int x=0;x<=c;x++)
    {
	ifile.open("itemlist.dat", ios:: in );
	ifile.read((char * )&sm, sizeof(sm));
	while (!ifile.eof())
	{
	    if (pno==order_arr[x])
	    {
		amt = price*quan[x];
		damt = amt-(amt*disc/100);
		cout << order_arr[x]<<"\t"<<pname<<"\t  "<<quan[x]<<"\t"<<price<<"\t\t"<<amt<<"\t\t"<<damt;
		total += damt;
	    }
	    ifile.read((char*)&sm,sizeof(sm));
	}

	ifile.close();
    }
    cout<<"\n================================================================================";
    cout << "\n\t\t\t\t\t\t\t       TOTAL = " << total;
    cout<<"\n================================================================================";

}
void supermarket::head()
{
  char h[100]="\t\t    ---------( ADMINISTRATOR SETTINGS )-------------";
 clrscr();
 gotoxy(15,50);
 for(int i=0;i<50;i++)
 {
  delay(50);
  cout<<h[i];
 }
  cout<<"\n\n\n";
}
void supermarket::end1()
{
 char e[50]="\t\t\t      <<<<< THANK YOU >>>>>";
 clrscr();
 gotoxy(5,15);
 for(int i=0;i<30;i++)
 {
  delay(100);
  cout<<e[i];
 }
 cout<<"\n\n\n";
}
void supermarket::intro()
{
  char g[100]="\t\t\t...SUPERMARKET BILLING SYSTEM...";
 clrscr();
 gotoxy(5,15);
 for(int i=0;i<50;i++)
 {
  delay(50);
  cout<<g[i];
 }
}



















