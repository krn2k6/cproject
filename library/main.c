#include<stdio.h>
#include<stdlib.h>

//Books
#define BOOK_FILE "books.dat"

struct Books{
    int id;
    char title[50];
    char author[50];
    char category[50];
    int copies;
    float price;
};

void displayBooks();
void addBooks();
void updateBooks();
void removeBooks();
void addToCart();
void viewCart();
void purchaseCart();
int menuBooksforCustomers();
int menuBooks();

struct Books *book = NULL;
int bookCount = 0;
int bookCapacity = 0;

int cart[100];
int cartCount = 0;

void ensureCapacity(int additional){
    if(bookCapacity >= bookCount + additional){
        return;
    }

    int newCapacity = bookCapacity ? bookCapacity * 2 : 10;
    while(newCapacity < bookCount + additional){
        newCapacity *= 2;
    }

    struct Books *newBookArray = realloc(book, newCapacity * sizeof(*newBookArray));
    if(newBookArray == NULL){
        printf("Memory allocation error\n");
        exit(1);
    }

    book = newBookArray;
    bookCapacity = newCapacity;
}

void saveBooks(){
    FILE *file = fopen(BOOK_FILE, "wb");
    if(file == NULL){
        printf("Error: unable to save books to file\n");
        return;
    }
    fwrite(&bookCount, sizeof(bookCount), 1, file);
    fwrite(book, sizeof(struct Books), bookCount, file);
    fclose(file);
}

void loadBooks(){
    FILE *file = fopen(BOOK_FILE, "rb");
    if(file == NULL){
        return;
    }
    if(fread(&bookCount, sizeof(bookCount), 1, file) != 1){
        bookCount = 0;
        fclose(file);
        return;
    }
    ensureCapacity(bookCount);
    fread(book, sizeof(struct Books), bookCount, file);
    fclose(file);
}

int findBookIndexById(int id){
    for(int i=0; i<bookCount; i++){
        if(book[i].id == id){
            return i;
        }
    }
    return -1;
}


void addBooks(){
    int n;
    printf("How many books do you want to add? ");
    scanf("%d", &n);
    if(n <= 0){
        printf("Invalid number of books.\n");
        return;
    }
    ensureCapacity(n);
    printf("==============================\n");
    for(int i=bookCount; i<bookCount+n; i++){
        printf("Book %d ID: ", i+1);
        scanf("%d", &book[i].id);
        printf("Book %d Title: ", i+1);
        scanf("%s", book[i].title);
        // fgets(book[i].title, sizeof(book[i].title), stdin);
        printf("Book %d Author: ", i+1);
        scanf("%s", book[i].author);
        // fgets(book[i].author, sizeof(book[i].author), stdin);
        printf("Book %d Category: ", i+1);
        scanf("%s", book[i].category);
        // fgets(book[i].category, sizeof(book[i].category), stdin);
        printf("How many copies of Book %d: ", i+1);
        scanf("%d", &book[i].copies);
        printf("Book %d Price: ", i+1);
        scanf("%f", &book[i].price);
        printf("\n\n");
    }
    printf("==============================\n\n");
    bookCount += n;
    saveBooks();
}

void updateBooks(){
    printf("Book ID of the book to update: ");
    int id;
    scanf("%d", &id);

    int found = 0;
    for(int i=0; i<bookCount; i++){
        if(book[i].id == id){
            found = 1;
            printf("New Book ID: ");
            scanf("%d", &book[i].id);
            printf("New Book Title: ");
            scanf("%s", book[i].title);
            printf("New Book Author: ");
            scanf("%s", book[i].author);
            printf("New Book Category: ");
            scanf("%s", book[i].category);
            printf("New number of copies: ");
            scanf("%d", &book[i].copies);
            printf("New Book Price: ");
            scanf("%f", &book[i].price);
            printf("\n\n");
            saveBooks();
            printf("Book updated successfully.\n");
            break;
        }
    }
    if(!found){
        printf("Book not found.\n");
    }
}

void removeBooks(){
    printf("Book ID of the book to delete: ");
    int id;
    scanf("%d", &id);

    int find = -1;
    for(int i=0; i<bookCount; i++){
        if(id == book[i].id){
            find = i;
            break;
        }
    }
    if(find == -1){
        printf("Book not found.\n");
        return;
    }

    for(int i=find; i<bookCount-1; i++){
        book[i] = book[i+1];
    }
    bookCount--;
    saveBooks();
    printf("Book deleted successfully.\n");
}

void addToCart(){
    printf("Book ID to add to cart: ");
    int id;
    scanf("%d", &id);

    int index = findBookIndexById(id);
    if(index < 0){
        printf("Book not found.\n");
        return;
    }
    if(book[index].copies <= 0){
        printf("No copies available.\n");
        return;
    }

    cart[cartCount] = id;
    cartCount++;
    printf("Book added to cart.\n");
}

void viewCart(){
    if(cartCount == 0){
        printf("Cart is empty.\n");
        return;
    }

    printf("Your Cart:\n");
    printf("========================================\n");
    float total = 0.0f;
    for(int i=0; i<cartCount; i++){
        int index = findBookIndexById(cart[i]);
        if(index >= 0){
            printf("Book: %s, Price: %.2f\n", book[index].title, book[index].price);
            total += book[index].price;
        }
    }
    printf("Total: %.2f\n", total);
    printf("========================================\n");
}

void purchaseCart(){
    if(cartCount == 0){
        printf("Cart is empty.\n");
        return;
    }

    float total = 0.0f;
    for(int i=0; i<cartCount; i++){
        int index = findBookIndexById(cart[i]);
        if(index >= 0){
            if(book[index].copies > 0){
                book[index].copies--;
                total += book[index].price;
            } else {
                printf("Not enough copies for %s\n", book[index].title);
            }
        }
    }
    saveBooks();
    cartCount = 0;
    printf("Purchase complete. Total paid: %.2f\n", total);
}

int menuBooksforCustomers(){
    printf("1. Display Books\n");
    printf("2. Add to Cart\n");
    printf("3. View Cart\n");
    printf("4. Purchase Cart\n");
    printf("5. Exit\n");

    int choice;
    scanf("%d", &choice);
    
    if(choice == 1){
        displayBooks();
    }
    else if(choice == 2){
        addToCart();
    }
    else if(choice == 3){
        viewCart();
    }
    else if(choice == 4){
        purchaseCart();
    }
    else if(choice == 5){
        return 0;
    }
 return 1;   
}

// int ENUM menuBooksm(){

// }

enum goodMenu{
    Add_Books = 1,
    Display_Books,
    Update_Books,
    Remove_Books,
    Exit_program,
};

int menuBooks(){
    printf("1. Add Books\n");
    printf("2. Display Books\n");
    printf("3. Update Books\n");
    printf("4. Remove Books\n");
    printf("5. Exit\n");

    int choice;
    scanf("%d", &choice);
    
    if(choice == Add_Books){
        addBooks();
    }
    else if(choice == Display_Books){
        displayBooks();
    }
    else if(choice == Update_Books){
        updateBooks();
    }
    else if(choice == Remove_Books){
        removeBooks();
    }
    else if(choice == Exit_program){
        return 0;
    }
 return 1;   
}

void displayBooks(){

    printf("All books in the library\n");
    printf("========================================\n");
    for(int i=0; i<bookCount; i++){
        printf("Book Id: %d\n", book[i].id);
        printf("Book Title: %s\n", book[i].title);
        printf("Book Author: %s\n", book[i].author);
        printf("Book Category: %s\n", book[i].category);
        printf("Number of Copies: %d\n", book[i].copies);
        printf("Book Price: %.2f\n", book[i].price);
        printf("========================================\n\n");

        printf("\n");
    }
}

int main()
{
    int choice;
    loadBooks();
    printf("\nWelcome to the Book Store Management\n");
    // printf("Are you employee or a customer: ");
    // scanf("%d", &choice);


    int flag1 = 1;
    while (flag1)
    {
        printf("\nFor Employee --> (1)\nFor Customer --> (2)\nOR just want to exit enter (0): \n\n");
    scanf("%d", &choice);
        
        if(choice == 1){
            printf("Employee LOGIN!!!\n");
            int flag = 1;
            while(flag){
                flag = menuBooks();     
                
            }
        }
        else if(choice == 2){
        printf("Customer LOGIN!!!\n");
        int flag = 1;
        while(flag){
            flag = menuBooksforCustomers();
        }

        
    }
    else if(choice == 0){
        flag1 = 0;
    }
}

    free(book);
    return 0;
}