# Mini-E-commerce-Cart-System
Overview
This project is a command-line based Mini E-commerce Cart System. The system allows users to:

Add products to a shopping cart.
Remove items or reduce the quantity of an item in the cart.
View the current items in the cart with total costs.
Calculate and apply dynamic discounts.
Convert the final total cost into different currencies.
Checkout to see the final price after applying discounts.

How to Run the Code
Prerequisites
A C++ compiler such as g++ is required to compile and run the code.
Steps to Run:
Clone the Repository or Copy Code: Download the source code (ecommerce.cpp) to your local machine.

Compile the Code: Use a C++ compiler like g++ to compile the program. Run the following command in the terminal or command line:
g++ ecommerce.cpp -o ecommerce
Run the Application: After compilation, run the program using:
./ecommerce
Follow the Commands: Once the program starts, you'll be prompted to enter various commands to interact with the system. Example commands:

add_to_cart P001 1 - Adds 1 Laptop to the cart.
remove_from_cart P003 1 - Removes 1 T-Shirt from the cart.
view_cart - Displays the contents of the cart.
list_discounts - Lists all available discounts.
checkout - Proceeds to checkout, applies discounts, and shows the total price.
quit - Exits the application.
Sample Commands
> add_to_cart P001 1
> add_to_cart P003 2
> view_cart
> list_discounts
> checkout
> quit
