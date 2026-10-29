
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Book {
public:
    string title, author, bookID;
    int pages;
    bool borrowed;

    Book(string t, string a, int p, string id, bool b) {
        title = t;
        author = a;
        pages = p;
        bookID = id;
        borrowed = b;
    }

    void display() const {
        cout << "\nTitle: " << title
             << "\nAuthor: " << author
             << "\nPages: " << pages
             << "\nBook ID: " << bookID
             << "\nStatus: " << (borrowed ? "Borrowed" : "Available")
             << '\n';
    }
};

vector<Book> loadBooks() {
    vector<Book> books;
    ifstream file("bookData.txt");
    string line;

    if (!file) {
        cout << "Error: Cannot open bookData.txt\n";
        return books;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string title, author, pagesText, id, status;

        if (getline(ss, title, ',') &&
            getline(ss, author, ',') &&
            getline(ss, pagesText, ',') &&
            getline(ss, id, ',') &&
            getline(ss, status)) {
            try {
                int pages = stoi(pagesText);
                bool borrowed = (status == "true");
                books.emplace_back(title, author, pages, id, borrowed);
            }
            catch (...) {
                cout << "Skipping invalid book record.\n";
            }
        }
    }

    file.close();
    return books;
}

Book* findBook(vector<Book>& books, const string& id) {
    for (Book& book : books) {
        if (book.bookID == id)
            return &book;
    }
    return nullptr;
}

void viewAllBooks(const vector<Book>& books) {
    if (books.empty()) {
        cout << "No books available.\n";
        return;
    }

    cout << "\n" << string(105, '-') << '\n';
    cout << left << setw(6) << "ID"
         << setw(32) << "Title"
         << setw(28) << "Author"
         << setw(10) << "Pages"
         << setw(15) << "Status" << '\n';
    cout << string(105, '-') << '\n';

    for (const Book& book : books) {
        cout << left << setw(6) << book.bookID
             << setw(32) << book.title.substr(0, 31)
             << setw(28) << book.author.substr(0, 27)
             << setw(10) << book.pages
             << setw(15) << (book.borrowed ? "Borrowed" : "Available")
             << '\n';
    }

    cout << string(105, '-') << '\n';
}

void viewOneBook(vector<Book>& books) {
    string id;
    cout << "Enter book ID: ";
    cin >> id;

    Book* book = findBook(books, id);

    if (book != nullptr)
        book->display();
    else
        cout << "Book not found.\n";
}

void borrowBook(vector<Book>& books) {
    string id;
    cout << "Enter book ID to borrow: ";
    cin >> id;

    Book* book = findBook(books, id);

    if (book == nullptr)
        cout << "Book not found.\n";
    else if (book->borrowed)
        cout << "This book is already borrowed.\n";
    else {
        book->borrowed = true;
        cout << "Book borrowed successfully.\n";
    }
}

void returnBook(vector<Book>& books) {
    string id;
    cout << "Enter book ID to return: ";
    cin >> id;

    Book* book = findBook(books, id);

    if (book == nullptr)
        cout << "Book not found.\n";
    else if (!book->borrowed)
        cout << "This book is already available.\n";
    else {
        book->borrowed = false;
        cout << "Book returned successfully.\n";
    }
}

int main() {
    vector<Book> books = loadBooks();

    if (books.empty()) {
        cout << "No book records loaded.\n";
        return 1;
    }

    int choice;

    do {
        cout << "\n----BOOK MANAGER----\n";
        cout << "1. View all books\n";
        cout << "2. View individual book\n";
        cout << "3. Borrow a book\n";
        cout << "4. Return a book\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1: viewAllBooks(books); break;
            case 2: viewOneBook(books); break;
            case 3: borrowBook(books); break;
            case 4: returnBook(books); break;
            case 5: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice. Select 1-5.\n";
        }
    } while (choice != 5);

    return 0;
}