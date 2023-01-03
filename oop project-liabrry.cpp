#include <iostream>

using namespace std;


void header_bar()
{
    cout<<"_____________________________________________";
}
void header_custom (string s)
{
    cout<<"\n";
    header_bar();
    cout<<"\n\n\t"<<s<<endl;
    header_bar();
    cout<<"\n";
}
void login_screen()
{
    cout<<"\n\t\t\t\t";
    header_bar();
    cout<<"\n\n\t\t\t\t\t\tLogin Screen\n"<<endl;
    cout<<"\t\t\t\t";
    header_bar();
    cout<<"\n\n\t\t\t\t  (1)Teachers\t(2)Students\t"<<endl;
    cout<<"\t\t\t\t";
    header_bar();
    cout<<"\n\nPress option to login"<<endl;
}
void Student_Teacher_Screen_Menu(unsigned int an)
{
    cout<<"\n";
    header_bar();
    cout<<"\nAccount Number:"<<an;
    cout<<"\n(1) Search Books only"<<endl;
    cout<<"(2) Issued Books List"<<endl;
    cout<<"(3) Return Book"<<endl;
    cout<<"(4) Reissue Book"<<endl;

    cout<<"(5) Issue a new book"<<endl;
    cout<<"(6) Display account info"<<endl;
    cout<<"(7) Search book by Category"<<endl;
    header_bar();
    cout<<"\n";
}


class Date
{
    int Day;        //1-31 based on month
    int Month;      //1-12
    int Year;       //any year
    int checkDay(int );
    int Late_Days;

public:
    static const int Days_per_Month[13];
    Date()
    {
        Day=0;
        Month=0;
        Year=0;
    }
    Date (int dy, int mn, int yr)
    {
        if (mn>0 && mn <=12)
            Month=mn;
        else
        {
            Month=1;
            cout<<"Month "<<mn<<" invalid. Set to month 1"<<endl;
        }
        Year=yr;
        Day=checkDay(dy);
    }

    void setDay(int d)          {Day=d;}
    void setMonth(int m)        {Month=m;}
    void setYear(int y)         {Year=y;}
    void setLateDay(int LD)     {Late_Days=LD;}
    int getDay()                {return Day;}
    int getMonth()              {return Month;}
    int getYear()               {return Year;}
    int getLateDay()            {return Late_Days;}


    void Print_Date()
    {
        cout<<getDay()<<"/"<<getMonth()<<"/"<<getYear()<<endl;
    }

    void Update_Date()
    {
        cout<<"\nEnter Day: ";
        cin>>Day;
        cout<<"Enter Month: ";
        cin>>Month;
        cout<<"Year: ";
        cin>>Year;
    }
    void increment_date(int num)
    {
        int day;
        int month_new;
        setDay(getDay()+num);

        while(getDay()>Days_per_Month[getMonth()])
        //if(    getDay()>Days_per_Month[getMonth()]     )
        {
            day=getDay()-Days_per_Month[getMonth()];
            setDay(day);
            setMonth(getMonth()+1);
           //if(Days_per_Month[getMonth()]>12)
           if (getMonth()>12)
            {
                month_new=getMonth()-11;
                setMonth(month_new);
                setYear(getYear()+1);
            }
        }
        cout<<"Return Date: ";
        Print_Date();
    }

    int Total_Days(Date r_d)        //we will use this to calculate fine's days and return date
    {                       //which will give number of days, so we can then calculate the fine.
        int Fine_Day=0,Fine_Month=0, Fine_Year=0;

        /*if(r_d.getDay()>getDay())  //r_d is return day
        {
            setLateDay(r_d.getDay()-getDay() );
            if(r_d.getMonth())
        }
        else
        {
            setLateDay(getDay()-r_d.getDay());
        }*/

        if (r_d.getYear()!=getYear())   //if this condition doesn't start, year will be zero
        {
            Fine_Year=r_d.getYear()-getYear();
        }
        if (r_d.getMonth()!=getMonth())    //if this starts, month won't be zero
        {
            Fine_Month=r_d.getMonth()-getMonth();
        }
        if (r_d.getDay()!=getDay())
        {
            Fine_Day=r_d.getDay()-getDay();
        }
        else if (Fine_Year==0 && Fine_Month==0 && Fine_Day==0)
            cout<<"Returned on time"<<endl;
        else
            cout<<endl;

        //Now, we calculate total days.

        setLateDay( (Fine_Year*365) + (Fine_Month*30.417) + Fine_Day  );

        return Late_Days;
    }

    ~Date()
    {
        setDay(0);
        setMonth(0);
        setYear(0);
    }
};
const int Date:: Days_per_Month[13]={0,31,28,31,30,31,30,31, 31, 30, 31, 30, 31};
int Date::checkDay(int testday)     //returntype classname :: funcname (parameteres)
{
    //static const int Days_per_Month[13]={0,31,28,31,30,31,30,31, 31, 30, 31, 30, 31};
    if(testday > 0 && testday <= Days_per_Month[Month])
        return testday;
    if ( Month==2 && testday==29 && (Year%400==0 || (Year%4==0 && Year%100!=0)) )  //for leap year
        return testday;

    cout<<"Day "<<testday<<" invalid. Set to day 1."<<endl;
    return 1;
}

class Book
{
    string Title;
    string Author;
    unsigned long int ISBN;
    int Year_of_Publication;
    int Library_Code;
    string Category;
    string Status;
    unsigned int Account_Number; //if issued
    public:
    int Copies_of_Book;
    Date Issued_Date;
    Date Return_Date;


    friend class Library;       //This will enable it to use return date. As Library is the main system
    static int Copy_Number;
    Book()
    {
        Title=" ";
        Author=" ";
        ISBN=0;
        Year_of_Publication=0;
        Library_Code=0;
        Category=" ";
        Status=" ";
        Account_Number=0;
        Copies_of_Book=0;
        Return_Date.setDay(0);
        Return_Date.setMonth(0);
        Return_Date.setYear(0);
        Issued_Date.setDay(0);
        Issued_Date.setMonth(0);
        Issued_Date.setYear(0);
    }
    Book(string t, string a,unsigned long int isbn, int yop, int libcode, string c, string s, unsigned int an, int cob)
    {
        setTitle(t);
        setAuthor(a);
        setISBN(isbn);
        setYOP(yop);
        setLibraryCode(libcode);
        setCategory(c);
        setStatus(s);
        setAccountNum(an);
        setCopiesBook(cob);
    }

    void setTitle(string T)             {Title=T;}
    void setAuthor(string A)            {Author=A;}
    void setISBN(unsigned long int isbn){ISBN=isbn;}
    void setYOP(int yop)                {Year_of_Publication=yop;}
    void setLibraryCode(int libcode)    {Library_Code=libcode;}
    void setCategory(string c)          {Category=c;}
    void setStatus(string s)            {Status=s;}
    void setAccountNum(unsigned int an) {Account_Number=an;}
    void setCopiesBook(int cob)         {Copies_of_Book=cob;}
    void setCopyNumber(int cn)          {Copy_Number=cn;}

    string getTitle()                   {return Title;}
    string getAuthor()                  {return Author;}
    unsigned long int getISBN()         {return ISBN;}
    int getYOP()                        {return Year_of_Publication;}
    int getLibraryCode()                {return Library_Code;}
    string getCategory()                {return Category;}
    string getStatus()                  {return Status;}
    unsigned int getAccountNum()        {return Account_Number;}
    int getCopiesBook()                 {return Copies_of_Book;}
    int getCopyNumber()                 {return Copy_Number;}

    void Input_New_Book()
    {
        cout<<"\nEnter Title: ";
        cin>>Title;
        cout<<"Enter Author: ";
        cin>>Author;
        cout<<"Enter ISBN: ";
        cin>>ISBN;
        cout<<"Enter Year of Publication: ";
        cin>>Year_of_Publication;
        cout<<"Enter Library Code: ";
        cin>>Library_Code;
        cout<<"Enter Category: ";
        cin>>Category;
        cout<<"Enter Total Copies Number: ";
        cin>>Copies_of_Book;
        cout<<"Enter Status: ";
        cin>>Status;
        if(Status=="Issued")
        {
        cout<<"Enter Account Number: ";
        cin>>Account_Number;
        Issued_Date.Update_Date();
        Return_Date.setDay(0);
        Return_Date.setMonth(0);
        Return_Date.setYear(0);
        }
    }

    void Display_Book_Info()
    {
        header_custom("Display of Book info");
        cout<<"\nTitle: "<<getTitle()<<endl;
        cout<<"Author: "<<getAuthor()<<endl;
        cout<<"ISBN: "<<getISBN()<<endl;
        cout<<"Year of Publication: "<<getYOP()<<endl;
        cout<<"Library Code: "<<getLibraryCode()<<endl;
        cout<<"Category: "<<getCategory()<<endl;
        cout<<"Total Copies: "<<getCopiesBook()<<endl;
        cout<<"Status: "<<getStatus()<<endl;
        if(getStatus()=="Issued")
        {
        cout<<"Account Number: "<<getAccountNum()<<endl;
        cout<<"Return Date: ";
        Return_Date.Print_Date();
        }
        header_bar();
    }

    void Update_Status()
    {
        unsigned int AN;
        Display_Book_Info();
        cout<<"Please enter the updated status of the book: ";
        cin>>Status;                //We cannot use string in an switch, so we are using if.
            if (Status=="Lost")
            {
                cout<<"The book is lost."<<endl;
                setAccountNum(0);
            }
            else if (Status=="Available")
            {
                cout<<"Book is available now to issue."<<endl;
                setAccountNum(0);       //This indicates it doesn't have nay account number.
            }
            else if(Status=="Issued")
            {
                cout<<"The book is in possession of someone."<<endl;
                cout<<"Enter their account number:";
                cin>>AN;
                setAccountNum(AN);
            }
            else if (Status=="Order")
            {
                cout<<"The book is in process of being ordered."<<endl;
                setAccountNum(0);
            }
            else
            {
                cout<<"Wrong entry!\nBook's Status is set to default. (Available)"<<endl;
                Status="Available";
                setAccountNum(0);
            }
    cout<<"Status updated successfully!"<<endl;
    }
    void Change_Return_Date()
    {
        cout<<"Enter Return Date: ";
        Return_Date.Update_Date();
    }

};

class Newspaper_Magzines_Journals
{
    string Name;
    Date Date_Published;
    int Library_Code;
    string Status;
    string Category;
    unsigned int Account_Number;
public:
    Newspaper_Magzines_Journals()
    {
        Name="  ";
        Date_Published.setDay(0);
        Date_Published.setMonth(0);
        Date_Published.setYear(0);
        Library_Code=0;
        Status=" ";
        Category=" ";
        Account_Number=0;
    }
    Newspaper_Magzines_Journals(string n, int lc, string s, string c, Date db)
    {
        setName(n);
        setLibraryCode(lc);
        setStatus(s);
        setCategory(c);
        Date_Published=db;
    }
    void setName(string n)              {Name=n;}
    void setLibraryCode(int lc)         {Library_Code=lc;}
    void setStatus(string s)            {Status=s;}
    void setCategory(string c)          {Category=c;}
    void setAccount_Number(unsigned int an) {Account_Number=an;}

    string getName()                    {return Name;}
    int getLibraryCode()                {return Library_Code;}
    string getStatus()                  {return Status;}
    string getCategory()                {return Category;}
    unsigned int getAccount_Number()    {return Account_Number;}

    void New_NP_Mag_Jou()
    {
        header_custom("New Entry of N/M/J");
        cout<<"\nEnter Name: ";
        cin>>Name;
        cout<<"Enter Library Code: ";
        cin>>Library_Code;
        cout<<"Enter Category: ";
        cin>>Category;
        Date_Published.Update_Date();
        cout<<"Enter Status: ";
        cin>>Status;
    }

    void Display_info_NMJ()
    {
        header_custom("Display of N/M/J");
        cout<<"Name: "<<getName()<<endl;
        cout<<"Library Code: "<<getLibraryCode()<<endl;
        cout<<"Category: "<<getCategory()<<endl;
        Date_Published.Print_Date();
        cout<<"Status: "<<getStatus()<<endl;
    }
};
class Student
{
    string Name;
    unsigned int Account_Number;
    double Fine;
    int Books_Issue;

public:
    Student()
    {
        Name=" ";
        Account_Number=0;
        Fine=0;
        Books_Issue=0;
    }
    Student (string n, unsigned int an, double f, int bi)
    {
        setName(n);
        setAccount_Number(an);
        setFine(f);
        setBooksIssue(bi);
    }

    void setName(string n)                      {Name=n;}
    void setAccount_Number(unsigned int an)     {Account_Number=an;}
    void setFine(double f)                      {Fine=f;}
    void setBooksIssue(int n)                   {Books_Issue=n;}

    string getName()                            {return Name;}
    unsigned int getAccount_Number()            {return Account_Number;}
    double getFine()                            {return Fine;}
    int getBooksIssue()                         {return Books_Issue;}

    void Input_Student_info()
    {
        header_custom("Input Student info");
        cout<<"\nEnter Name: ";
        cin>>Name;
        cout<<"Enter Account Number: ";
        cin>>Account_Number;
    }
    void Display_Student_info()
    {
        header_custom("Display of Student info");
        cout<<"Name: "<<getName()<<endl;
        cout<<"Account Number: "<<getAccount_Number()<<endl;
        cout<<"Total Fine: "<<getFine()<<endl;
        cout<<"Books issued: "<<getBooksIssue()<<endl;
        header_bar();
    }
};

class Staff
{
    string Name;
    unsigned int Account_Number;
    double Fine;
    int Books_Issue;

public:
    Staff()
    {
        Name=" ";
        Account_Number=0;
        Fine=0;
        Books_Issue=0;
    }
    Staff(string n, unsigned int an, double f, int bi)
    {
        setName(n);
        setAccount_Number(an);
        setFine(f);
        setBooksIssue(bi);
    }

    void setName(string n)                      {Name=n;}
    void setAccount_Number(unsigned int an)     {Account_Number=an;}
    void setFine(double f)                      {Fine=f;}
    void setBooksIssue(int n)                   {Books_Issue=n;}

    string getName()                            {return Name;}
    unsigned int getAccount_Number()            {return Account_Number;}
    double getFine()                            {return Fine;}
    int getBooksIssue()                         {return Books_Issue;}

    void Input_Staff_info()
    {
        header_custom("Input Staff info");
        cout<<"\nEnter Name: ";
        cin>>Name;
        cout<<"Enter Account Number: ";
        cin>>Account_Number;
    }
    void Display_Staff_info()
    {
        header_custom("Display of Staff's info");
        cout<<"Name: "<<getName()<<endl;
        cout<<"Account Number: "<<getAccount_Number()<<endl;
        cout<<"Total Fine: "<<getFine()<<endl;
        cout<<"Books issued: "<<getBooksIssue()<<endl;
    }
};

class Library
{
    Book books[10];
    Student students[5];
    Staff staffs[2];
    Newspaper_Magzines_Journals nmj[5];
    int BOOKS, STUDENTS,STAFFS, NMJ;
    string Category;
    string Issue;
    string Search;                  //search a single book
    unsigned int Account_Number;    //search for a specific user
public:
    Library()
    {
        Category=" ";
        Issue=" ";
        Search=" ";
        Account_Number=0;
        BOOKS=0;
        STUDENTS=0;

        STAFFS=0;
        NMJ=0;
    }
    Library(Book b1, Book b2, Book b3, Book b4, Book b5, Student stu1, Student stu2, Student stu3,Staff s1, Newspaper_Magzines_Journals nmj)
    {
        books[0]=b1;
        books[1]=b2;
        books[2]=b3;
        books[3]=b4;
        books[4]=b5;
        students[0]=stu1;
        students[1]=stu2;
        students[2]=stu3;
        staffs[0]=s1;
        this->nmj[0]=nmj;
        Category=" ";
        Issue=" ";
        Search=" ";
        Account_Number=0;
        BOOKS=5;
        STUDENTS=3;
        STAFFS=1;
        NMJ=1;
    }
    void setCategory(string c)              {Category=c;}
    void setIssue(string i)                 {Issue=i;}
    void setSearch(string s)                {Search=s;}
    void setAccNum(unsigned int an)         {Account_Number=an;}
    void setBOOKS(int b)                    {BOOKS=b;}
    void setSTUDENTS(int s)                 {STUDENTS=s;}
    void setSTAFFS(int s1)                  {STAFFS=s1;}
    void setNMJ(int n)                      {NMJ=n;}

    string getCategory()                    {return Category;}
    string getIssue()                       {return Issue;}
    string getSearch()                      {return Search;}
    unsigned int getAccNum()                {return Account_Number;}
    int getBOOKS()                          {return BOOKS;}
    int getSTUDENTS()                       {return STUDENTS;}
    int getSTAFFS()                         {return STAFFS;}
    int getNMJ()                            {return NMJ;}

    void Issue_Book_Student()
    {
        header_custom("Issue book");
        unsigned int an;
        int num=7;
        bool check_one=false;
                cout<<"Enter account number to issue book to: ";
                cin>>an;
                setAccNum(an);
                for (int i=0 ; i<=4 ; i++)          //Since there are only 5 students
                {
                    if(getAccNum()==students[i].getAccount_Number())
                    {
                        Show_Category();
                        check_one=true;
                        if (students[i].getBooksIssue()<=3)
                        {
                        Search_Book_Issue(students[i].getAccount_Number(),num);
                        students[i].setBooksIssue(students[i].getBooksIssue()+1); //This mean increment in their book
                        }
                        else
                            cout<<"Maximum Limit reached!"<<endl;
                    }
                }
                if(check_one==false)
                    cout<<"User not found!"<<endl;
    } //issue book students function closed.


    void Issue_Book_Staff()
    {
        header_custom("Issue Book");
        unsigned int an;
        int num=21;     //days
        header_custom("Issue Book");
                cout<<"Staff:"<<endl;
                cout<<"Enter account number to issue book to: ";
                cin>>an;
                setAccNum(an);
                for (int i=0 ; i<=4 ; i++)          //Since there are only 5 students
                {
                    if(getAccNum()==staffs[i].getAccount_Number())
                    {
                        Show_Category();
                        if (staffs[i].getBooksIssue()<=5)
                        {
                        Search_Book_Issue(staffs[i].getAccount_Number(),num);
                        staffs[i].setBooksIssue(staffs[i].getBooksIssue()+1); //This mean increment in their book
                        }
                        else
                            cout<<"Maximum Limit reached!"<<endl;
                    }
                    else
                        cout<<"User not found!"<<endl;
                }
    }

    void Search_Book_Only()
    {
        bool check_one=false;
        header_custom("Search Book");
        string s;
        //char choice;
        cout<<"\nEnter Title of the book to search:"<<endl;
        cin>>s;
        setSearch(s);
        for(int i=0 ; i<=9 ; i++)
        {
            if (getSearch()==books[i].getTitle())
            {
                cout<<"Book Found!"<<endl;
                books[i].Display_Book_Info();
                check_one=true;
            }
        }
        if(check_one==false)
            cout<<"Book not found"<<endl;

    }//end of search function
    void Search_Book_Issue(unsigned int SAN, int days)       //This SAN is account number of a student
    {
        bool check_one=false;
        string s;
        cout<<"\nEnter Title of the book to search:"<<endl;
        cin>>s;
        setSearch(s);
        for(int i=0 ; i<=9 ; i++)
        {
            if (getSearch()==books[i].getTitle())
            {
                cout<<"Book Found!"<<endl;
                books[i].Display_Book_Info();
                books[i].setAccountNum(SAN);
                books[i].setStatus("Issued");
                cout<<"\nEnter Issued Date:";
                books[i].Issued_Date.Update_Date();     //Today's date will be entered here
                cout<<"Issued Date: ";
                books[i].Issued_Date.Print_Date();
                books[i].Return_Date.setDay(books[i].Issued_Date.getDay());
                books[i].Return_Date.setMonth(books[i].Issued_Date.getMonth());
                books[i].Return_Date.setYear(books[i].Issued_Date.getYear());
                books[i].Return_Date.increment_date(days);
                cout<<"Book issued for "<<days<<" days."<<endl;
                cout<<"Return Date: ";
                books[i].Return_Date.Print_Date();
                check_one=true;
            }
        }
        if(check_one==false)
                cout<<"Book not found!"<<endl;
    }//end of search issue function
    void Return_Book()
    {
        header_custom("Return Book");
        string book_title;
        bool check_one=false;
        bool check_two=false;
        int choice;
        unsigned int an;    //account number
        cout<<"Who is returning the book? [1: Student, 2: Teacher, 3: Staff]"<<endl;
        cin>>choice;
        cout<<"Enter Book Title to return: ";
        cin>>book_title;
        cout<<"Enter Account Number: ";
        cin>>an;
        setSearch(book_title);
        setAccNum(an);
        switch(choice)
        {
            case 1:
                {
                    for (int i=0 ; i<=9 ; i++)
                    {
                        if(books[i].getTitle()==getSearch())
                        {
                            for (int j=0 ; j<=4 ; j++)
                            {
                                if(getAccNum()==students[j].getAccount_Number())
                                {
                                    cout<<"Book returned!";
                                    books[i].setStatus("Available");
                                    books[i].setAccountNum(0);
                                    books[i].Return_Date.~Date();       //using destructor to set date back to 0.
                                    books[i].Issued_Date.~Date();
                                    students[j].setBooksIssue(students[j].getBooksIssue()-1);
                                    check_one=true;
                                }
                            }
                            if(check_one==false)
                                cout<<"User not found!"<<endl;
                        }
                        check_two=true;
                    }
                    if(check_two==false)
                        cout<<"Book not found!"<<endl;
                    break;
                }

            case 2:
                {
                    for (int i=0 ; i<=9 ; i++)
                    {
                        if(books[i].getTitle()==getSearch())
                        {
                            for (int j=0 ; j<=1 ; j++)
                            {
                                if(getAccNum()==staffs[j].getAccount_Number())
                                {
                                    cout<<"Book returned!";
                                    books[i].setStatus("Available");
                                    books[i].setAccountNum(0);
                                    books[i].Return_Date.~Date();       //using destructor to set date back to 0.
                                    staffs[j].setBooksIssue(staffs[j].getBooksIssue()-1);
                                    check_one=true;
                                }
                            }
                            if(check_one==false)
                                cout<<"User not found!"<<endl;
                        }
                        check_two=true;
                    }
                    if(check_two==false)
                        cout<<"Book not found!"<<endl;
                    break;
                }
            default:
                cout<<"Wrong choice! Closing window..."<<endl;
        }//switch end



    }
    void ReIssue_Book()
    {
        header_custom("Reissue Book");
        string book_title;
        bool check_one=false;
        bool check_two=false;
        int choice;
        unsigned int an;    //account number
        cout<<"Who is reissuing the book? [1: Student, 2: Teacher, 3: Staff]"<<endl;
        cin>>choice;
        cout<<"Enter Book Title to return: ";
        cin>>book_title;
        cout<<"Enter Account Number: ";
        cin>>an;
        setSearch(book_title);
        setAccNum(an);
        switch(choice)
        {
            case 1:
                {
                    for (int i=0 ; i<=9 ; i++)
                    {
                        if(books[i].getTitle()==getSearch())
                        {
                            for (int j=0 ; j<=4 ; j++)
                            {
                                if(students[j].getAccount_Number()==getAccNum())
                                {
                                    books[i].Return_Date.increment_date(7);
                                    cout<<"Book reissued successfully!"<<endl;
                                    check_one=true;
                                }
                            }
                            if(check_one==false)
                                cout<<"User not found"<<endl;
                             check_two=true;
                        }
                    }
                    if(check_two==false)
                        cout<<"Book not found!"<<endl;
                    break;
                }

            case 2:
                {
                    for (int i=0 ; i<=9 ; i++)
                    {
                        if(books[i].getTitle()==getSearch())
                        {
                            for (int j=0 ; j<=4 ; j++)
                            {
                                if(staffs[j].getAccount_Number()==getAccNum())
                                {
                                    books[i].Return_Date.increment_date(7);
                                    cout<<"Book reissued successfully!"<<endl;
                                    check_one=true;
                                }
                            }
                            if(check_one==false)
                                cout<<"User not found"<<endl;
                             check_two=true;
                        }
                    }
                    if(check_two==false)
                        cout<<"Book not found!"<<endl;
                    break;
                }
            default:
                cout<<"Wrong choice! Closing Window..."<<endl;
        } //switch closed
    }
    void Calculate_Fine()
    {
    //Need to do this by comparing date. This one is yet to do.

        header_custom("Fine Calculator");
        unsigned int an;
        double Fine_days;
        int choice;
        string book_title;
        cout<<"Who's fine you wish to calculate?\n[1: Student, 2: Teacher, 3: Staff]"<<endl;
        cin>>choice;
        cout<<"Enter Book Title: ";
        cin>>book_title;
        cout<<"Enter Account Number: ";
        cin>>an;
        setSearch(book_title);
        setAccNum(an);

        switch (choice)
        {
            case 1:
                {
                    cout<<"Student:"<<endl;
                    for(int i=0 ; i<=9 ; i++)
                    {
                        if (books[i].getTitle()==getSearch())     //finding book in book collection
                        {
                            cout<<"Book found!"<<endl;
                            books[i].Display_Book_Info();
                            for (int j=0 ; j<=4 ; j++)
                            {
                                if (students[j].getAccount_Number()==getAccNum())  //finding user in users
                                {
                                    students[j].Display_Student_info();
                                    books[i].Change_Return_Date();              //This will ask for the return date.
                                    Fine_days=books[i].Issued_Date.Total_Days(books[i].Return_Date);
                                    if(Fine_days>7)
                                    {
                                        students[j].setFine(Fine_days*10);
                                        cout<<"Total Fine: "<<students[j].getFine()<<endl;
                                    }
                                    else
                                        cout<<"No Fine"<<endl;
                                }
                            } //for loop closed of finding user
                        }
                    }//for loop close ob finding book
                    break;
                }//case 1 closed

            case 2:
                {
                    cout<<"Staffs:"<<endl;
                    for(int i=0 ; i<=9 ; i++)
                    {
                        if (books[i].getTitle()==getSearch())     //finding book in book collection
                        {
                            cout<<"Book found!"<<endl;
                            books[i].Display_Book_Info();
                            for (int j=0 ; j<=2 ; j++)
                            {
                                if (staffs[j].getAccount_Number()==getAccNum())  //finding user in users
                                {
                                    staffs[j].Display_Staff_info();
                                    books[i].Change_Return_Date();              //This will ask for the return date.
                                    Fine_days=books[i].Issued_Date.Total_Days(books[i].Return_Date);
                                    if( Fine_days>21)
                                    {
                                        staffs[j].setFine(Fine_days*10);
                                        cout<<"Total Fine: "<<staffs[j].getFine()<<endl;
                                    }
                                    else
                                        cout<<"No Fine"<<endl;
                                }
                            } //for loop closed of finding user
                        }
                    }//for loop close ob finding book
                    break;
                }//case 3 closed
            default:
                cout<<"Wrong Choice"<<endl;
        }//switch closed
    }
    void Remove_Fine()
    {
        header_custom("Remove Fine");
        unsigned int an;
        int choice;
        bool check_one=false;
        cout<<"Who's fine you want to remove? [1: Student, 2: Teacher, 3: Staff]"<<endl;
        cin>>choice;
        cout<<"Enter Account Number: ";
        cin>>an;
        setAccNum(an);
        switch(choice)
        {
            case 1:
                {
                    for (int i=0 ; i<=4 ; i++)
                    {
                        if(students[i].getAccount_Number()==getAccNum())
                        {
                            students[i].setFine(0);
                            cout<<"Fine removed successfully!"<<endl;
                            check_one=true;
                        }
                    }
                    if (check_one==false)
                        cout<<"User not found"<<endl;
                    break;
                }
            case 2:
                {
                    for (int i=0 ; i<=2 ; i++)
                    {
                        if(staffs[i].getAccount_Number()==getAccNum())
                        {
                            staffs[i].setFine(0);
                            cout<<"Fine removed successfully!"<<endl;
                            check_one=true;
                        }
                    }
                    if (check_one==false)
                        cout<<"User not found"<<endl;
                    break;
                }
            default:
                cout<<"Wrong choice"<<endl;
        }//switch close
    }
    void Show_Category()
    {
        header_custom("Categories");
        cout<<"(1)English\n(2)Maths\n(3)Computer_Science\n(4)Urdu"<<endl;
        cout<<"Please type the category [Full Name, no number]"<<endl;
        string choice;
        cin>>choice;
        setCategory(choice);
        for(int i=0 ; i<=9 ; i++)
        {
            if (books[i].getCategory()==getCategory())
            {
                books[i].Display_Book_Info();
            }
        }//for loop closed
    }
    void List_of_Issued_Books()
    {
        header_custom("List of issued books");
        for (int i=0 ; i<=9 ; i++)
        {
            if("Issued"==books[i].getStatus())
            {
                books[i].Display_Book_Info();
            }
        }
    }//closing of list of issued books
    void Enter_New_Book()  //not complete yet
    {
        header_custom("Enter New books");
        if(getBOOKS()<=9)
        {                                         //The first five books are predefined by me, so we start from index five.
            books[getBOOKS()].Input_New_Book(); //since we are using parametric construtor, it will start from 5.
            if(getBOOKS()<9)
                setBOOKS(getBOOKS()+1); //This is like BOOKS++;
        }
        else
            cout<<"Cannot enter more books"<<endl;
    }
    void Enter_New_Student()
    {
        header_custom("Enter New Students");
        if (getSTUDENTS()<=4)
        {
            students[getSTUDENTS()].Input_Student_info();
            if(getSTUDENTS()<4)
                setSTUDENTS(getSTUDENTS()+1);
        }
        else
            cout<<"Maximum capacity reached!"<<endl;
    }

    void Enter_New_Staff()
    {
        header_custom("Enter New Staff");
        if(getSTAFFS()<=2)
        {
            staffs[getSTAFFS()].Input_Staff_info();
            if (getSTAFFS()<2)
                setSTAFFS(getSTAFFS()+1);
        }
        else
            cout<<"Maximum capacity reached!"<<endl;
    }
    void Enter_New_NMJ()
    {
        header_custom("Enter new N/M/J");
        if(getNMJ()<=4)
        {
            nmj[getNMJ()].New_NP_Mag_Jou();
            if(getNMJ()<4)
                setNMJ(getNMJ()+1);
        }
        else
            cout<<"Maximum capacity reached!"<<endl;
    }
    bool Find_User(unsigned int an, int number)
    {
        setAccNum(an);
        bool check_one=false;
        switch(number)
        {

        case 1:
            {
                for (int i=0 ; i<=4 ; i++)
                {
                    if(students[i].getAccount_Number()==getAccNum())
                    {
                        cout<<"User found!"<<endl;
                        check_one=true;
                        return true;
                    }
                }
                if(check_one==false)
                {
                    cout<<"User not found"<<endl;
                    return false;
                }
                break;
            }//case student closed
        case 2:
            {
                for (int i=0 ; i<=2 ; i++)
                {
                    if(staffs[i].getAccount_Number()==getAccNum())
                    {
                        cout<<"User found!"<<endl;
                        check_one=true;
                        return true;
                    }
                }
                if(check_one==false)
                {
                    cout<<"User not found"<<endl;
                    return false;
                }
                break;
            }//case staffs closed
        default:
            cout<<"Wrong choice"<<endl;
        }
    }

    void Issued_Book_Of_Users(int n, unsigned int an)
    {
        switch (n)
        {

            case 1:
            {
                header_custom("Student's Issued Books");
                for (int i=0 ; i<=9 ; i++)
                {
                    for (int j=0; j<=4 ; j++)
                    {
                        if( (books[i].getStatus()=="Issued") && (students[j].getAccount_Number()==an)     )
                            books[i].Display_Book_Info();
                    }
                }
                break;
            }
            case 2:
            {
                header_custom("Staff's Issued Books");
                for (int i=0 ; i<=9 ; i++)
                {
                    for (int j=0; j<=2 ; j++)
                    {
                        if( (books[i].getStatus()=="Issued")     )
                            books[i].Display_Book_Info();
                    }
                }
                break;
            }
            default:
                cout<<"Wrong choice"<<endl;
        }
    }
    void Display_User_info(int n, unsigned int an)
    {
        switch (n)
        {

            case 1:
            {
                for (int i=0 ; i<=4 ; i++)
                {
                    if(an==students[i].getAccount_Number())
                        students[i].Display_Student_info();
                }
            }
            case 2:
            {
                for (int i=0 ; i<=2 ; i++)
                {
                    if(an==staffs[i].getAccount_Number())
                        staffs[i].Display_Staff_info();
                }
            }
        }
    }
    void Display_All_Accounts()
    {
        int choice;
        cout<<"Press    [1]Teachers\t [2]Students\t [3]Staff"<<endl;
        cin>>choice;
        switch(choice)
        {

        case 1:
            {
                for (int i=0 ; i<=4 ; i++)
                {
                    students[i].Display_Student_info();
                }
                break;
            }
        case 2:
            {
                for (int i=0 ; i<=2 ; i++)
                {
                    staffs[i].Display_Staff_info();
                }
                break;
            }
        default:
            cout<<"Wrong Choice!"<<endl;
        }
    }
    void Issue_NMJ()
    {
    //There is no mention of issuing Newspapers, journal and magazines.
    //So, I have left this function empty.
    //But Since it is a thing, I have made it's add a new N_M_J function, to enter new things.
    }
};

int main()
{
    cout << "Program Library System:"<<endl;

    Date NMJ (15,01,2020);

    Newspaper_Magzines_Journals nmj_one ("Dawn",103,"Archived","Newspaper", NMJ );

    Book book_1 ("Calculus","Thomas",54545454555,2010,001,"Maths","Available",0,3);
    Book book_2 ("Discrete_Structures","Gilbert",4554464654668, 2005, 002, "Maths", "Available", 0, 5);
    Book book_3 ("Harry_Potter","JK_Rowling",79454645645682,1999,003,"English","Available",0,10);
    Book book_4 ("Roblox_Lua","Gamer101",124454455,2019,004,"Computer_Science","Available",0,5);
    Book book_5 ("Seerat_Un_Nabi","Shibli_Naumani",74544515345611,1917,005,"Urdu","Available",0,5);

    Student stu_one ("Amna",120,500,0); //120 is the account number
    Student stu_two ("Fatima",121,0,0);
    Student stu_three ("Ali",122, 20,0);


    Staff sta_one ("Salman",50,30,0);   //50 is the account number


    Library lib(book_1, book_2, book_3, book_4, book_5, stu_one, stu_two, stu_three,sta_one, nmj_one);

    int choice;
    int option_menu;
    unsigned int Account_Number;
    char exit;

    while(1) //this will stay active until the user exits.
    {       //First while loop is for login screen
        login_screen();
        cin>>choice;
        cout<<"Please enter Account Number to login: ";
        cin>>Account_Number;
        switch(choice)
        {
        case 1:
            {
                while (1)
                {
                    if (lib.Find_User(Account_Number,1) == true)
                    {
                        Student_Teacher_Screen_Menu(Account_Number);
                        cout<<"Press the option from above:"<<endl;
                        cin>>option_menu;
                        switch(option_menu)
                        {
                            case 1:
                            {
                                lib.Search_Book_Only();
                                break;
                            }//search books only
                            case 2:
                            {
                                lib.Issued_Book_Of_Users(1,Account_Number);
                                break;
                            }//List all issued books
                            case 3:
                            {
                                lib.Return_Book();
                                break;
                            }
                            case 4:
                            {
                                lib.ReIssue_Book();
                                break;
                            }

                            case 5:
                            {
                                lib.Display_User_info(1,Account_Number);
                                break;
                            }
                            case 6:
                            {
                                lib.Show_Category();
                                break;
                            }
                            default:
                                cout<<"Wrong choice!"<<endl;
                        }
                    }
                    else
                        cout<<"Closing window....."<<endl;


                    cout<<"\nPress 'e' to exit or any key to continue"<<endl;
                    cin>>exit;
                    if(exit=='e')
                        break;
                }
                break;
            }//teacher login case closed
        case 2:
            {
                while (1)
                {
                    if (lib.Find_User(Account_Number,2) == true)
                    {
                        Student_Teacher_Screen_Menu(Account_Number);
                        cout<<"Press the option from above:"<<endl;
                        cin>>option_menu;
                        switch(option_menu)
                        {
                            case 1:
                            {
                                lib.Search_Book_Only();
                                break;
                            }//search books only
                            case 2:
                            {
                                lib.Issued_Book_Of_Users(2,Account_Number);
                                break;
                            }//List all issued books
                            case 3:
                            {
                                lib.Return_Book();
                                break;
                            }
                            case 4:
                            {
                                lib.ReIssue_Book();
                                break;
                            }
                            case 5:
                            {
                                lib.Issue_Book_Student();
                                break;
                            }
                            case 6:
                            {
                                lib.Display_User_info(2,Account_Number);
                                break;
                            }
                            case 7:
                            {
                                lib.Show_Category();
                                break;
                            }
                            default:
                                cout<<"Wrong choice!"<<endl;
                        }
                    }
                    else
                        cout<<"Closing window....."<<endl;


                    cout<<"\nPress 'e' to exit or any key to continue"<<endl;
                    cin>>exit;
                    if(exit=='e')
                        break;
                }
                break;
            }//student login case closed

        
        default:
            cout<<"Wrong choice!"<<endl;
        }//switch login closed

        cout<<"\nPress 'e' to exit out or press any key to login in another user."<<endl;
        cin>>exit;
        if(exit=='e')
            break;
    }

    cout<<"PROGRAM ENDED!"<<endl;
    return 0;
}
