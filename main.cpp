#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<memory>
#include<unistd.h>

int bookI,librno,memno;

class Book
{
  public:
    int bookID;
    std::string bookName;
    std::string bookGenre;
    bool availability;
    int borrowID;  

    Book()
    {
      bookID=-1;
      bookName="Unknown";
      bookGenre="Unknown";
      availability=false;
      borrowID=-1;
    }

    Book(std::string name,std::string genre)
    {
      bookID=bookI++;
      bookName=name;
      bookGenre=genre;
      availability=true;
      borrowID=-1;
    }

      
};

std::unordered_map<int, Book> books;

class Librarian
{
  public:
    int staffID;
    std::string staffName;

    Librarian()
    {
      staffID=-1;
      staffName="Unknown";
    }

    void Badd(std::string BookN,std::string BookG)
    {
      Book newBook(BookN,BookG);

      books[newBook.bookID]=newBook;
    }

    void Bremove(int BookID)
    {
      books.erase(BookID);
    }
};

class Member
{
  public:
    int memID;
    std::string memName;
    bool borrowStatus;

    Member()
    {
      memID=-1;
      memName="Unknown";
      borrowStatus=false;
    }

    void Bborrow(int bookID,int uID)
    {
      if(books[bookID].availability)
      {
        books[bookID].borrowID=uID;
        books[bookID].availability=false;
      }
      else
      {
        std::cout << "Book not available to borrow!" << std::endl;
      }
    }

    void Breturn(int bookID)
    {
      books[bookID].borrowID=-1;
      books[bookID].availability=true;
    }
      
};

std::unordered_map<int, Librarian> librarians;
std::unordered_map<int, Member> members;

class LMS
{
  public:
    LMS()
    {
      bookI=1001;
      librno=1;
      memno=1;
      books={};
      librarians={};
      members={};
    }

    void display()
    {
      if(books.empty())
      {
        std::cout << "No books in Library!";
        return;
      }

      std::cout << "List of Books:" << std::endl;
      std::cout << "ID" << " " << "Name" << " " << "Genre" << " " << "Availability" << std::endl;

      for(int i=1000;i<=bookI;i++)
      {
        if(books.find(i)==books.end())continue;

        std::cout << i << " " << books[i].bookName << " " << books[i].bookGenre << " ";

        if(books[i].availability)std::cout << "Yes";
        else std::cout << "No";

        std::cout << std::endl;
      }
    }
};

int main()
{
  std::cout << "Setting up Library Management System...." << std::endl;
  LMS l=LMS();

  std::cout << "Welcome to Oxform LMS!" << std::endl;
  int ch;
  bool stat=true;
  std::cout << "1)Add" << std::endl;
  std::cout << "2)Remove" << std::endl;
  std::cout << "3)Borrow" << std::endl;
  std::cout << "4)Return" << std::endl;
  std::cout << "5)Display" << std::endl;
  std::cout << "6)Add Librarian" << std::endl;
  std::cout << "7)Add Member" << std::endl;
  std::cout << "8)Exit" << std::endl;

  while(stat)
  {
    std::cout << "Choose your choice: " << std::endl;
    std::cin >> ch;
    std::cin.ignore();

    int id,uid;
    std::string name,genre;

    if(ch==1)
    {
      if(librarians.empty())
      {
        std::cout << "No librarians present!" << std::endl;
        continue;
      }
      std::cout << "Enter book name: ";
      std::getline(std::cin,name);

      std::cout << "Enter book genre: ";
      std::getline(std::cin,genre);

      Librarian l;
      l.Badd(name,genre);

    }

    else if(ch==2)
    {
      if(librarians.empty())
      {
        std::cout << "No librarians present!" << std::endl;
        continue;
      }
      std::cout << "Enter Book ID to be removed: ";
      std::cin >> id;

      Librarian l;
      l.Bremove(id);
    }

    else if(ch==3)
    {
      if(members.empty())
      {
        std::cout << "No members present!" << std::endl;
        return 0;
      }
      std::cout << "Enter Book ID to be borrowed: ";
      std::cin >> id;

      std::cout << "Enter member ID: ";
      std::cin >> uid;

      Member m;
      m.Bborrow(id,uid);
    }

    else if(ch==4)
    {
      if(members.empty())
      {
        std::cout << "No members present!" << std::endl;
        return 0;
      }
      std::cout << "Enter Book ID to be returned: ";
      std::cin >> id;

      Member m;
      m.Breturn(id);
    }
    else if(ch==5)l.display();
    else if(ch==6)
    {
      std::cout << "Enter Librarian Name: " << std::endl;
      std::getline(std::cin,name);

      Librarian l;
      l.staffID=librno++;
      l.staffName=name;

      librarians[l.staffID]=l;
    }
    else if(ch==7)
    {
      std::cout << "Enter Member Name: " << std::endl;
      std::getline(std::cin,name);

      Member m;
      m.memID=memno++;
      m.memName=name;

      members[m.memID]=m;
    }
    else if(ch==8)
    {
      stat=false;
      std::cout << "Have a nice day! Goodbye!" << std::endl;
    }
    else std::cout << "Please choose a valid choice!" << std::endl;
  }
  
  return 0;
}