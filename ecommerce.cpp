#include <iostream>
#include <vector>
#include <unordered_map>
#include <iomanip> // For setting precision

using namespace std;

// Product Class
class Product {
public:
    string id, name, category;
    double price;

    Product(string id, string name, double price, string category)
        : id(id), name(name), price(price), category(category) {}
};

// CartItem Class to hold products and their quantities in the cart
class CartItem {
public:
    Product product;
    int quantity;

    CartItem(Product product, int quantity)
        : product(product), quantity(quantity) {}

    // Marking the getTotalCost method as const
    double getTotalCost() const {
        return product.price * quantity;
    }
};

// Cart Class to handle cart operations
class Cart {
private:
    vector<CartItem> items;

public:
    void addToCart(Product product, int quantity) {
        for (auto &item : items) {
            if (item.product.id == product.id) {
                item.quantity += quantity;
                return;
            }
        }
        items.push_back(CartItem(product, quantity));
    }

    void removeFromCart(string productId, int quantity) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->product.id == productId) {
                if (quantity >= it->quantity) {
                    cout << "Removed all " << it->product.name << "(s) from the cart.\n";
                    items.erase(it);
                } else {
                    it->quantity -= quantity;
                    cout << "Reduced quantity of " << it->product.name << " to " << it->quantity << ".\n";
                }
                return;
            }
        }
        cout << "Product not found in cart.\n";
    }

    void viewCart() const {
        if (items.empty()) {
            cout << "Your cart is empty.\n";
            return;
        }

        cout << "Your Cart:\n";
        double totalCost = 0;
        for (const auto &item : items) {
            cout << item.product.name << " - Quantity: " << item.quantity
                 << ", Price: " << item.product.price << " USD"
                 << ", Total: " << item.getTotalCost() << " USD\n";
            totalCost += item.getTotalCost();
        }
        cout << "Total (before discounts): " << totalCost << " USD\n";
    }

    double getTotalCost() const {
        double totalCost = 0;
        for (const auto &item : items) {
            totalCost += item.getTotalCost();
        }
        return totalCost;
    }

    vector<CartItem> &getItems() {
        return items;
    }

    bool isEmpty() const {
        return items.empty();
    }
};

// Discount System
class DiscountSystem {
public:
    double applyDiscounts(Cart &cart) {
        double totalDiscount = 0;
        for (auto &item : cart.getItems()) {
            if (item.product.category == "Fashion" && item.quantity >= 2) {
                // Buy 1 Get 1 Free for Fashion items
                int freeItems = item.quantity / 2;
                totalDiscount += freeItems * item.product.price;
                cout << "Buy 1 Get 1 Free on " << item.product.name << " applied.\n";
            } else if (item.product.category == "Electronics") {
                // 10% Off for Electronics
                totalDiscount += 0.10 * item.getTotalCost();
                cout << "10% Off on " << item.product.name << " applied.\n";
            }
        }
        cout << "Total Discount: " << totalDiscount << " USD\n";
        return totalDiscount;
    }

    void listDiscounts() {
        cout << "Available Discounts:\n";
        cout << "1. Buy 1 Get 1 Free on Fashion items\n";
        cout << "2. 10% Off on Electronics\n";
    }
};

// Currency Conversion
class CurrencyConverter {
    unordered_map<string, double> conversionRates;

public:
    CurrencyConverter() {
        conversionRates["EUR"] = 0.85;
        conversionRates["GBP"] = 0.75;
    }

    double convert(double amount, string currency) {
        return amount * getConversionRate(currency);
    }

    void showAvailableCurrencies() {
        cout << "Available Currencies: EUR, GBP\n";
    }

    double getConversionRate(string currency) {
        if (conversionRates.find(currency) != conversionRates.end()) {
            return conversionRates[currency];
        }
        return 1; // No conversion if currency is not found
    }
};

// Pre-populate product catalog
vector<Product> productCatalog = {
    Product("P001", "Laptop", 1000.00, "Electronics"),
    Product("P002", "Phone", 500.00, "Electronics"),
    Product("P003", "T-Shirt", 20.00, "Fashion")
};

// Function to find product by ID
Product* findProductById(string productId) {
    for (auto &product : productCatalog) {
        if (product.id == productId) {
            return &product; // Return pointer to found product
        }
    }
    return nullptr; // Return null pointer if product is not found
}

int main() {
    Cart cart;
    DiscountSystem discountSystem;
    CurrencyConverter currencyConverter;

    string command, productId, currency;
    int quantity;

    while (true) {
        cout << "\nEnter a command (add_to_cart, remove_from_cart, view_cart, list_discounts, checkout, quit): ";
        cin >> command;

        if (command == "add_to_cart") {
            cin >> productId >> quantity;
            Product* product = findProductById(productId);
            if (product) {
                cart.addToCart(*product, quantity);
                cout << "Added " << quantity << " " << product->name << "(s) to the cart.\n";
            } else {
                cout << "Product with ID " << productId << " not found.\n";
            }
        } else if (command == "remove_from_cart") {
            cin >> productId >> quantity;
            cart.removeFromCart(productId, quantity);
        } else if (command == "view_cart") {
            cart.viewCart();
        } else if (command == "list_discounts") {
            discountSystem.listDiscounts();
        } else if (command == "checkout") {
            if (cart.isEmpty()) {
                cout << "Your cart is empty. Add items to proceed with checkout.\n";
                continue;
            }
            cout << "Applying discounts...\n";
            double discount = discountSystem.applyDiscounts(cart);

            double finalTotal = cart.getTotalCost() - discount;
            cout << fixed << setprecision(2) << "Final Total in USD: " << finalTotal << " USD\n";

            cout << "Would you like to view it in a different currency? (yes/no): ";
            string response;
            cin >> response;

            if (response == "yes") {
                currencyConverter.showAvailableCurrencies();
                cout << "Enter currency: ";
                cin >> currency;
                if (currencyConverter.getConversionRate(currency) != 1) {
                    double convertedTotal = currencyConverter.convert(finalTotal, currency);
                    double rate = currencyConverter.getConversionRate(currency);
                    cout << fixed << setprecision(2) << "Final Total in " << currency << ": " << convertedTotal << " " << currency << " (Conversion rate: " << rate << ")\n";
                } else {
                    cout << "Unsupported currency.\n";
                }
            }
        } else if (command == "quit") {
            cout << "Thank you for shopping! Exiting...\n";
            break;
        } else {
            cout << "Invalid command. Available commands: add_to_cart, remove_from_cart, view_cart, list_discounts, checkout, quit.\n";
        }
    }
    return 0;
}
