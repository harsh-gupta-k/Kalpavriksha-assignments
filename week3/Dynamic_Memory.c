#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct ProductDetails
{
    int productID;
    char productName[20];
    float productPrice;
    int productQuantity;
};

void input_details(struct ProductDetails *productDetail, int numberOfProducts)
{
    for (int product = 0; product < numberOfProducts; product++)
    {
        printf("Enter details for product %d:\n", product + 1);
        printf("Product ID: ");
        scanf("%d", &productDetail[product].productID);
        printf("Product Name: ");
        scanf("%s", productDetail[product].productName);
        printf("Product Price: ");
        scanf("%f", &productDetail[product].productPrice);
        printf("Product Quantity: ");
        scanf("%d", &productDetail[product].productQuantity);
    }
}

void add_new_product(struct ProductDetails **productDetail, int *numberOfProducts)
{
    (*numberOfProducts)++;
    *productDetail = (struct ProductDetails *)realloc(*productDetail, (*numberOfProducts) * sizeof(struct ProductDetails));

    if (*productDetail == NULL)
    {
        printf("Memeory reallocation failed");
        return;
    }

    printf("Enter new Product Details: \n");
    printf("Product ID: ");
    scanf("%d", &(*productDetail)[(*numberOfProducts) - 1].productID);
    printf("Product Name: ");
    scanf("%s", (*productDetail)[(*numberOfProducts) - 1].productName);
    printf("Product Price: ");
    scanf("%f", &(*productDetail)[(*numberOfProducts) - 1].productPrice);
    printf("Product Quantity: ");
    scanf("%d", &(*productDetail)[(*numberOfProducts) - 1].productQuantity);
    printf("Product added successfully!");

    printf("\n");
}

void view_products(struct ProductDetails *productDetail, int numberOfProducts)
{
    for (int product = 0; product < numberOfProducts; product++)
    {
        printf("Product ID: %d | Name: %s | Price: %.2f | Quantity: %d", productDetail[product].productID, productDetail[product].productName, productDetail[product].productPrice, productDetail[product].productQuantity);
        printf("\n");
    }
    printf("\n");
}

void update_quantity(struct ProductDetails *productDetail, int numberOfProducts)
{
    int id;
    printf("Enter Product ID to update quantity: ");
    scanf("%d", &id);

    int newQuantity;
    printf("Enter new Quantity: ");
    scanf("%d", &newQuantity);

    int found = 0;

    for (int product = 0; product < numberOfProducts; product++)
    {
        if (productDetail[product].productID == id)
        {
            productDetail[product].productQuantity = newQuantity;
            found = 1;
        }
    }
    if (found)
    {
        printf("Quantity updated successfully!\n");
    }
    else
    {
        printf("ID not found\n");
    }
    printf("\n");
}

void search_by_id(struct ProductDetails *productDetail, int numberOfProducts)
{
    int searchId;
    printf("Enter Product ID to search: ");
    scanf("%d", &searchId);

    int found = 0;
    for (int product = 0; product < numberOfProducts; product++)
    {
        if (productDetail[product].productID == searchId)
        {
            printf("Product Found : Product ID: %d | Name: %s | Price: %.2f | Quantity: %d\n", productDetail[product].productID, productDetail[product].productName, productDetail[product].productPrice, productDetail[product].productQuantity);
            found = 1;
        }
    }
    if (!found)
    {
        printf("Inavlid ID\n");
    }
    printf("\n");
}

void search_by_name(struct ProductDetails *productDetail, int numberOfProducts)
{
    char name[20];
    printf("Enter name to search (partial allowed): ");
    scanf("%s", name);

    int found = 0;
    for (int product = 0; product < numberOfProducts; product++)
    {
        if (strstr(productDetail[product].productName, name) != NULL)
        {
            printf("Product Found : Product ID: %d | Name: %s | Price: %.2f | Quantity: %d\n", productDetail[product].productID, productDetail[product].productName, productDetail[product].productPrice, productDetail[product].productQuantity);
            found = 1;
        }
    }
    if (!found)
    {
        printf("No products found matching '%s'\n", name);
    }
    printf("\n");
}

void search_by_price(struct ProductDetails *productDetail, int numberOfProducts)
{
    int minimumPrice, maximumPrice;
    printf("Enter minimum price: ");
    scanf("%d", &minimumPrice);
    printf("Enter maximum price: ");
    scanf("%d", &maximumPrice);

    int found = 0;
    for (int product = 0; product < numberOfProducts; product++)
    {
        if (productDetail[product].productPrice >= minimumPrice && productDetail[product].productPrice <= maximumPrice)
        {
            printf("Product Found : Product ID: %d | Name: %s | Price: %.2f | Quantity: %d\n", productDetail[product].productID, productDetail[product].productName, productDetail[product].productPrice, productDetail[product].productQuantity);
            found = 1;
        }
    }

    if (!found)
    {
        printf("No Product Found\n");
    }
}

void delete_by_id(struct ProductDetails **productDetail, int *numberOfProducts)
{
    int deleteId;
    printf("Enter product id to delete: ");
    scanf("%d", &deleteId);

    int found = 0;

    for (int product = 0; product < (*numberOfProducts); product++)
    {
        if ((*productDetail)[product].productID == deleteId)
        {
            found = 1;

            for (int j = product; j < (*numberOfProducts) - 1; j++)
            {
                (*productDetail)[j] = (*productDetail)[j + 1];
            }

            (*numberOfProducts)--;

            (*productDetail) = (struct ProductDetails *)realloc((*productDetail), (*numberOfProducts) * sizeof(struct ProductDetails));

            if ((*productDetail) == NULL)
            {
                printf("Reallocation failed");
                return;
            }

            printf("Producted Deleted successfully\n");
            break;
        }
    }

    if (!found)
    {
        printf("Product not found\n");
    }
}

void exit_program(struct ProductDetails *productDetail)
{
    free(productDetail);
    productDetail = NULL;

    printf("Memory released successfully. Exiting program...");
}
int main()
{
    int numberOfProducts = 0;
    printf("Enter initial number of products: ");
    scanf("%d", &numberOfProducts);

    struct ProductDetails *productDetail = (struct ProductDetails *)calloc(numberOfProducts, sizeof(struct ProductDetails));

    if (productDetail == NULL)
    {
        printf("Memory allocation failed");
        return 1;
    }

    // Getting Input about product deatils
    input_details(productDetail, numberOfProducts);

    printf("\n");

    int choice;

    do
    {
        printf("\n-------INVENTORY MENU-------\n");
        printf("1. Add New Product\n");
        printf("2. View All Products\n");
        printf("3. Update Quantity\n");
        printf("4. Search Product by ID\n");
        printf("5. Search Product by Name\n");
        printf("6. Search Product by Price Range\n");
        printf("7. Delete Product\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");
        if (choice == 1)
        {
            add_new_product(&productDetail, &numberOfProducts);   // Add New Product
        }

        else if (choice == 2)
        {
            view_products(productDetail, numberOfProducts);      // View All Products
        }
        else if (choice == 3)
        {
            update_quantity(productDetail, numberOfProducts);    // Update Quantity
        }
        else if (choice == 4)
        {
            search_by_id(productDetail, numberOfProducts);       // Search Product by ID
        }
        else if (choice == 5)
        {
            search_by_name(productDetail, numberOfProducts);     // Search Product by Name
        }
        else if (choice == 6)
        {
            search_by_price(productDetail, numberOfProducts);    // Search Product by Price
        }
        else if (choice == 7)
        {
            delete_by_id(&productDetail, &numberOfProducts);     // Delete Product
        }
        else if (choice == 8)
        {
            exit_program(productDetail);                         // Exit Program
        }

        printf("\n");

    } while (choice != 8);
}