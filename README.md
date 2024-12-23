Library Management System

This project is a simple console-based library management system that enables customers and librarians to interact with a collection of books. The application provides features for searching, borrowing, returning, adding, and removing books from the library collection.

Features

For Customers:

Browse the Library:

View all available books along with their details (title, author, genre, status, and barcode).

Search for Books:

Search by title, author, or genre.

Borrow Books:

Borrow a book if it is available.

Return Books:

Return a previously borrowed book.

For Librarians:

Add Books:

Add new books to the library collection.

Remove Books:

Remove books from the library collection using their barcode.

Modify Book Details:

Update the title, author, genre, or barcode of an existing book.

Search for Books:

Search by title, author, or genre.

Implementation Details

Data Structures:

struct book:

Represents a book in the library.

Contains the following fields:

title: Title of the book.

author: Author of the book.

genre: Genre of the book.

barcode: Unique barcode identifier.

status: Availability status ("available" or "taken").

Key Functions:

menu:

Displays a menu with options and returns the user's selection.

addBook:

Prompts the librarian to enter book details and adds the new book to the collection.

removeBook:

Removes a book from the collection based on its barcode.

displayBook:

Displays all books in the library collection.

barcodeSearch:

Searches for a book using its barcode and returns the index if found.

borrowBook:

Updates the status of a book to "taken" if it is available.

returnBook:

Updates the status of a book to "available" if it is borrowed.

changeBookData:

Allows the librarian to modify the details of an existing book.

search:

Allows users to search for books by title, author, or genre.

Utility Functions:

getch:

Captures single-character input without requiring the Enter key. Used for pausing and navigation.

Setup and Usage

Compile the Code:
Use a C++ compiler, such as g++, to compile the program:

g++ library_management.cpp -o library_management

Run the Program:
Execute the compiled program:

./library_management

Follow the Prompts:

Select options from the menu to navigate through the program.

Provide the required input when prompted.

Example Books in the System

The program initializes with the following sample books:

Title

Author

Genre

Barcode

Status

IT

Stephen King

Horror

0001

Available

The Lord of the Rings

J.R.R. Tolkien

Fantasy

0002

Available

Percy Jackson

Rick Riordan

Fantasy

0003

Available

Harry Potter

J.K. Rowling

Fantasy

0004

Available

The Merchant of Venice

William Shakespeare

Drama

0005

Available

Notes

Input Format:

Enter all text in uppercase for consistency.

Barcodes must be unique and consist of exactly 4 digits.

Error Handling:

The program validates user input and prompts for correction in case of errors.

Future Enhancements

Add support for persistent storage using files or a database.

Implement a user authentication system for customers and librarians.

Add more advanced search filters and sorting options.
