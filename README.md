# Inventory Management<br>

This project was developed as part of the **Advanced Programming course (C++)** during my Bachelor's studies in Computer Engineering at the University of Isfahan.<br><br>

## Table of content
  - [Login and Sign up](#login-and-sign-up)
  - [Inventory](#inventory)
  - [Purchase](#purchase)
  - [Invoice](#invoice)
  - [Reports](#reports)
  - [Currency](#currency)<br><br><br>



## Login and Sign up

* This section presents the user authentication interface specifically designed for sellers within the Inventory Management application, allowing users to either log in to an existing account or sign up to create a new one.

![Login Window](readme-images/login-window.png)

![SignUp Window](readme-images/signup-window.png)
> The customer section has not been developed yet.


<br><br>
## Inventory

* In this section, you will find the Inventory window where you can efficiently manage your inventory by adding, removing, or editing products.

![Inventory Window](readme-images/inventory-window.png)<br><br>


* The window includes a convenient search bar that allows you to easily find products by name, category, and other criteria.

![Search bar](readme-images/search-bar.png)<br><br>


* Furthermore, the application offers a practical filtering feature that enables you to refine the product list by brand or category.

![Filter by category](readme-images/filter-by-category.png)<br><br>


* By clicking on the column headers, you can sort the products in ascending or descending order based on various attributes such as name, category, brand, and more.

![Sort](readme-images/sorting.png)<br><br>


* To add a new product, simply click on the **Add Product** button.

![Add Product](readme-images/add-product.png)<br><br>


* In case you need to modify an existing product, you can conveniently do so by double-clicking on the corresponding row in the table.

![Edit Product 1](readme-images/edit-product-sp1.png)

![Edit Product 2](readme-images/edit-product-sp2.png)
 > Note: By setting the **Available** quantity to a value greater than zero, the product will be made available for purchase by both manufacturers and customers.

<br>

* Lastly, to remove a product from your inventory, just click on the **Remove** button.

![Remove Product](readme-images/remove-product.png)<br><br><br>



## Purchase

* In this section, you can select a manufacturer and purchase products from them. The Purchase window includes a search bar and filters, similar to the Inventory window, to help you find the desired products.

![Purchase Window](readme-images/purchase-window.png)<br><br>


* To get started, use the combo box to select the preferred manufacturer from whom you wish to purchase supplies.

![Select manufacturer combo box](readme-images/select-manufacturer.png)<br><br>


* By double-clicking on an item, you can instantly access and view detailed information about the selected product.

![Product Information](readme-images/product-inf.png)<br><br>


* When you find the desired item, select it and click on the **Add to Invoice** button to add it to your invoice.

![Addd to Invoice](readme-images/add-to-invoice.png)<br><br><br>



## Invoice

* In this window, you can conveniently view your current invoice. By clicking the "Purchase" button, you can proceed to purchase the items that are included in your invoice.

![Invoice](readme-images/invoice-window.png)<br><br>


* If you navigate back to the Purchase window and add a new item from a different manufacturer, please note that the previous invoice will be automatically closed, and a new invoice will be created for the new manufacturer.

![Create new Invoice](readme-images/create-new-invoice.png)<br><br><br>



## Reports

* In this section, you have access to view your Purchase and Sales Invoice history. The Reports window provides a comprehensive overview of your past invoices.

![Reports window purchase](readme-images/reports-window-purchase.png)

![Reports window sales](readme-images/reports-window-sold.png)<br><br>


* By double-clicking on an invoice, you can navigate to the detailed information of that particular invoice.

![Invoice Details](readme-images/invoice-inf.png)<br><br>


* To save an invoice as a CSV file, simply click on the **Print** button, which allows you to generate a printable version of the invoice that can be saved in CSV format.

![Print Invoice](readme-images/print-invoice.png)

![Invoice as CSV file](readme-images/invoice-csv.png)<br><br>


* Additionally, you can view the product information within an invoice by double-clicking on the respective products.

![Invoice Products Details](readme-images/invoice-item-inf.png)<br><br><br>



## Currency

* In this section, you have the convenience of effortlessly accessing and modifying the currency settings within the application.

![Currency Window](readme-images/currency-window.png)
> Please note that some of the currency exchange rates may be outdated or incorrect.

<br>

* After modifying the currency from USD to GBP, the entire application will seamlessly update to reflect the new currency. As an illustration, here is an example of the Invoice window displaying values in GBP:

![Modify Currency 1](readme-images/change-currency-sp1.png)

![Modify Currency 2](readme-images/change-currency-sp2.png)<br><br>


* By clicking on the **Edit Exchange Rate** button, you can easily adjust the currency exchange rate according to your preferences.

![Edit Exchange Rate](readme-images/exchange-rate.png)<br><br>
