#include <iostream>
using namespace std;
#include <termios.h>
#include <unistd.h>
#include <string>


struct book
{
string title;
string author;
string genre;
string barcode;
string status = "taken";

};



char getch(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
  return buf;
 }



int menu(string, string[], int);
int choice(int, int[], int);
void removeBook (book[], int&);
book addBook(book[], int);
void displayBook(book[], int);
int barcodeSearch(book[], int, string);
int barcodeSearchWithInput(book[], int, string);
void borrowBook(book[], int);
void returnBook(book[], int);
void changeBookData(book[], int);
void search(book[], int);




//-----------------------------------------------------------------------
int main() {

  book books[50];

  books[0].title = "IT";
  books[0].genre = "HORROR";
  books[0].author = "STEPHAN KING";
  books[0].barcode = "0001";
  books[0].status = "available";
  
  books[1].title = "THE LORD OF THE RINGS";
  books[1].genre = "FANTASY";
  books[1].author = "JOHN RONALD R TOLKIEN";
  books[1].barcode = "0002";
  books[1].status = "available";
  
  books[2].title = "PERCY JACKSON";
  books[2].genre = "FANTASY";
  books[2].author = "RICK RIORDAN";
  books[2].barcode = "0003";
  books[2].status = "available";
  
  books[3].title = "HARRY POTTER";
  books[3].genre = "FANTASY";
  books[3].author = "J. K. ROWLING";
  books[3].barcode = "0004";
  books[3].status = "available";
  
  books[4].title = "THE MERCHANT OF VENICE";
  books[4].genre = "DRAMA";
  books[4].author = "WILLIAM SHAKESPEARE";
  books[4].barcode = "0005";
  books[4].status = "available";
  
 
  int numberOfBooks = 5;
  int barcodeNumber = 6;
  int menuInput = 0;
  int menuOutput = 0;
  int secondMenu = 0;
  int secondOutput = 0;
  system("clear");

  
  string mainMenuOptions[3] = {"Customer", "Librarian", "Exit program"};
  
 string customerMenuOptions[5] = {"Browse the libary", "Search for book", "Borrow book", "Return book", "Return to previous menu"};
  
 string librarianMenuOptions[5] = {"Add books to the library collection", "Remove books from the library collection", "Modify an existing book", "Search for book", "Return to previous menu"};
  
  
  do{ 

menuInput = menu("Choose one of the following options", mainMenuOptions, 3);
    switch (menuInput)
      {
        case 1:
          system("clear");
          
          do{ 
          secondMenu = menu("Choose one of the following options", customerMenuOptions, 5);
      
          switch (secondMenu)
            {
            case 1:

              displayBook(books, numberOfBooks);
              break;
            case 2:
              search(books, numberOfBooks);
              break;
            case 3:
              borrowBook(books, numberOfBooks);
              break;
            case 4:
              returnBook(books, numberOfBooks);
              break;
            case 5:
              secondOutput = 1;
              system("clear");
                break;
              }
            
            if (secondOutput != 1)
              {
                cout << "press any key to continue.";
                getch();
                system ("clear");
                }
  
            }while (secondOutput != 1);
            break;
        
        case 2:
          system("clear");
          do{ 
          secondMenu = menu("Choose one of the following options", librarianMenuOptions, 5);
      
          switch (secondMenu)
            {
            case 1:
            
              books[numberOfBooks]=addBook(books, numberOfBooks);
              numberOfBooks++;
              break;
            case 2:
              removeBook(books, numberOfBooks);
              numberOfBooks--;
              break;
            case 3:
              changeBookData(books, numberOfBooks);
              break;
            case 4:
            search(books, numberOfBooks);

              break;
            case 5:
              secondOutput = 1;
                system("clear");

                break;
             
            }
            
            if (secondOutput != 1)
              {
                cout << "press any key to continue.";
                getch();
                system ("clear");
                }
              
            }while (secondOutput != 1);
            break;

        case 3:
          cout << "Thank you for using this program." << endl;
          menuOutput = 1;
          break;
          

        
      }
    secondOutput=0;
    
 } while (menuOutput != 1);
  
  
  return 0;
  }

//-----------------------------------------------------------------------

int menu(string question, string option[], int numberOfOptions)
{
  int answer = 0;
  do {
  cout << question << endl;

    for (int i = 0; i < numberOfOptions; i++ )
    cout << i+1 <<"- " << option[i] << endl;
  cin >> answer;

    if (answer < 1 or answer > numberOfOptions)
      {cout << "Invalid answer. Try again" << endl << "press any key to continue.";
                getch();
                system ("clear");;
      }
    } while (answer < 1 or answer > numberOfOptions);
  return answer; 
  
}



 book addBook(book books[], int number)
{
  system("clear");
  int duplicateCheck = 0;
  book bookData;
  cout << "Fill out the folliwing information in ALL CAPS please." << endl;
  
  cout << "Type the title of the new book(ALl CAPS): ";
  cin.ignore( );
  getline(cin, bookData.title);
  
  cout << "Type the author of the new book(ALl CAPS): ";
  getline(cin, bookData.author);
  
  cout << "Type the genre of the new book(ALl CAPS): ";
  getline(cin, bookData.genre);
  
  do {
    cout << "Type the barcode of the new book(4 numbers): ";
  getline(cin, bookData.barcode);
    duplicateCheck = barcodeSearchWithInput(books, number, bookData.barcode);
      if (duplicateCheck != -1)
    {
      cout << "A book already exists with that barcode. Try again with an unique barcode" << endl << "press any key to continue." << endl;
      getch();
    }
    }while(duplicateCheck != -1);
  
  bookData.status = "available";
  
  cout << bookData.title << " has been successfully added!" << endl;
  return bookData;
}

void removeBook(book books[], int &number)
{
  system("clear");
  string barcode;

    int deleteNumber = barcodeSearch(books, number, "remove");
  
      if (deleteNumber == -1)
  {
    return;
  }
      cout << books[deleteNumber].title << " had been successfully deleted!" << endl;
  
          for (int c = 1; c <= (number-1-deleteNumber);c++)
            {
              books[deleteNumber + c - 1]= books[deleteNumber + c];
            }
          
          number--;
          return;
      
}

void displayBook(book allBooks[], int number)
{
  system("clear");
  for (int i = 0; i < number; i++)
    {
      cout << allBooks[i].title << " (barcode " <<  allBooks[i].barcode << ")" << " status: " << allBooks[i].status << endl << "Writeen by: " << allBooks[i].author << endl << "Genre: " << allBooks[i].genre << endl << endl << endl;
    
    }
  
  cout << endl;
  
  return;
}

int barcodeSearch(book books[], int number, string action)
{

  int bookFound = 0;
  
  string barcode = "";
  
      cout << "Enter the barcode of the book you wish to " << action << ": ";
      cin >> barcode;  
  
    for (int i = 0; i < number; i++)
      {
        
        if (books[i].barcode == barcode)
        {
          return i;
          }
        }
  
    cout << "No book matched that barcode. Returning to previous menu." << endl;
  
  return -1;
}

int barcodeSearchWithInput(book books[], int number, string input)
{
  
  
    for (int i = 0; i < number; i++)
      {
        
        if (books[i].barcode == input)
        {
          return i;
          }
        }
  
  
  return -1;
}

void borrowBook(book books[], int number)
{
  system("clear");
  int userInput = 0;
  
  userInput = barcodeSearch(books, number, "borrow")
    ;
  if (userInput == -1)
  {

  }
    
  else if (books[userInput].status == "taken")
  {
    cout << books[userInput].title <<" is already checked out." << endl;
  }
    
  else if (books[userInput].status == "available")
  {
    
    books[userInput].status = "taken";

      cout << "Successfully borred " << books[userInput].title << "!!!" << endl; 
  }
  return;
}




void returnBook(book books[], int number)
{
  system("clear");
  int userInput = 0;
  
  userInput = barcodeSearch(books, number, "return")
    ;
  
  if (userInput == -1)
  {

  }
    
  else if (books[userInput].status == "available")
  {
    cout << books[userInput].title <<" is not checked out." << endl;
  }
    
  else if (books[userInput].status == "taken")
  {
    
    books[userInput].status = "available";

      cout << "Successfully returned " << books[userInput].title << "!!!" << endl; 
  }
  return;
}

void changeBookData(book books[], int number)
{  
  system("clear");
  string input = "";
  int arrayNumber = 0;
  int duplicateCheck = 0;
  arrayNumber = barcodeSearch(books, number, "alter");
  {
    if (arrayNumber == -1)
    {
      return;
    }
    
    cout << "Change this book's title (ALl CAPS)(Just press enter to not change anything): ";
    cin.ignore( );
    getline(cin, input);

    if (input != "")
    {
      books[arrayNumber].title = input;
    }

    cout << "Change this book's author (ALl CAPS)(Just press enter to not change anything): ";
    getline(cin, input);

    if (input != "")
    {
      books[arrayNumber].author = input;
    }

  cout << "Change this book's genre (ALl CAPS)(Just press enter to not change anything): ";
    getline(cin, input);

    if (input != "")
    {
      books[arrayNumber].genre = input;
    }
    
    do {
      duplicateCheck = -1;
      cout << "Change this book's barcode (Just press enter to not change anything): ";
    getline(cin, input);

    if (input != "")
    {
      
      
      duplicateCheck = barcodeSearchWithInput(books, number,input);
      
      books[arrayNumber].barcode = input;
    
      if (duplicateCheck != -1)
    {
      cout << "A book already exists with that barcode. Try again with an unique barcode" << endl << "press any key to continue." << endl;
      getch();
    }
      }
      
      }while(duplicateCheck != -1);
  }
  return;
}

void search(book books[], int number)
{
  int menuInput = 0;
  int found = 0;
  string userInput = "";
  system("clear");
  
  string menuArray[3] = {"Title", "Author", "Genre"};
  
  menuInput = menu("What will you be searching by?: ", menuArray, 3);

    system("clear");
  switch(menuInput)
    {
    case 1:
    cout << "What is the title of the book you are seaching for?(ALl CAPS): " ;
      cin.ignore();
      getline(cin, userInput);
      
      cout << "The total result of your search is: " << endl << endl;
        
      for (int i = 0; i < number; i++)
        {
          found = books[i].title.find(userInput);
          if (found != -1)
          {
          cout << books[i].title << " (barcode " <<  books[i].barcode << ")" << " status: " << books[i].status << endl << "Writeen by: " << books[i].author << endl << "Genre: " << books[i].genre << endl << endl << endl;
            }
        }
      break;
    case 2:
    cout << "Who is the author of the book you are seaching for?(ALl CAPS): ";
      cin.ignore();
      getline(cin, userInput);

      cout << "The total result of your search is:" << endl << endl;
        
      for (int i = 0; i < number; i++)
        {
          found = books[i].author.find(userInput);
          if (found != -1)
          {
          cout << books[i].title << " (barcode " <<  books[i].barcode << ")" << " status: " << books[i].status << endl << "Writeen by: " << books[i].author << endl << "Genre: " << books[i].genre << endl << endl << endl;
            }
        }
      break;

    case 3:
    cout << "What is the genre of the book you are seaching for?(ALl CAPS): ";
      cin.ignore();
      getline(cin, userInput);

      cout << "The total result of your search is:" << endl << endl;
        
      for (int i = 0; i < number; i++)
        {
         found = books[i].genre.find(userInput);
          if (found != -1)
          {
          cout << books[i].title << " (barcode " <<  books[i].barcode << ")" << " status: " << books[i].status << endl << "Writeen by: " << books[i].author << endl << "Genre: " << books[i].genre << endl << endl << endl;
            }
        }
      break;
      }
  
return;
}