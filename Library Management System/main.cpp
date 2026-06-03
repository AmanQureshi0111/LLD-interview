#include <iostream>
#include <vector>

using namespace std;

class Book {

    string title;
    string author;

public:

    Book(
        string title,
        string author
    )
    : title(title),
      author(author) {}

    string getTitle() {
        return title;
    }
};

class BookItem {

    int copyId;
    Book* book;
    bool issued;

public:

    BookItem(
        int copyId,
        Book* book
    )
    : copyId(copyId),
      book(book),
      issued(false) {}

    Book* getBook() {
        return book;
    }

    int getCopyId() {
        return copyId;
    }

    bool isIssued() {
        return issued;
    }

    void issue() {
        issued = true;
    }

    void returnBook() {
        issued = false;
    }
};

class Member {

    string name;

public:

    Member(string name)
        : name(name) {}

    string getName() {
        return name;
    }
};

class Library {

    vector<BookItem*> books;

public:

    void addBook(
        BookItem* item
    ) {

        books.push_back(
            item
        );
    }

    void searchBook(
        string title
    ) {

        for(
            auto item :
            books
        ) {

            if(
                item->getBook()
                    ->getTitle()
                == title
            ) {

                cout
                    << "Copy Found : "
                    << item->getCopyId()
                    << endl;
            }
        }
    }

    bool issueBook(
        string title,
        Member* member
    ) {

        for(
            auto item :
            books
        ) {

            if(
                item->getBook()
                    ->getTitle()
                == title
                &&
                !item->isIssued()
            ) {

                item->issue();

                cout
                    << member->getName()
                    << " borrowed "
                    << title
                    << endl;

                return true;
            }
        }

        return false;
    }

    bool returnBook(
        string title
    ) {

        for(
            auto item :
            books
        ) {

            if(
                item->getBook()
                    ->getTitle()
                == title
                &&
                item->isIssued()
            ) {

                item->returnBook();

                cout
                    << title
                    << " returned"
                    << endl;

                return true;
            }
        }

        return false;
    }
};

int main() {

    Book cleanCode(
        "Clean Code",
        "Robert Martin"
    );

    BookItem copy1(
        1,
        &cleanCode
    );

    BookItem copy2(
        2,
        &cleanCode
    );

    Member aman(
        "Aman"
    );

    Library library;

    library.addBook(
        &copy1
    );

    library.addBook(
        &copy2
    );

    library.searchBook(
        "Clean Code"
    );

    library.issueBook(
        "Clean Code",
        &aman
    );

    library.returnBook(
        "Clean Code"
    );
}