  PIZZA SYSTEM README FILE			

  These are our valid data for logining as member, admin and superadmin:

1. Member email	    : yuxuan@gmail.com 				
   Member password	: Yuxuan123					

2. Admin email	  : zhixin@gmail.com				
   Admin password	: Zhixin123					

3. Superadmin email		 : yuxuan@gmail.com 			
   Superadmin password : Yuxuan123													

-------------------------------------------------------------------------

Requirements:
  - Dev C++ IDE 
  - Windows OS (recommended) 

Setup Instructions:
1. download the source code 
2. Ensure all data files are in the same directory: 
  - admin_id.txt
  - admin.txt
  - feedback.txt
  - member_id.txt
  - member.txt
  - order_id_counter.txt
  - product_id_counter.txt
  - product.txt
  - purchase_history.txt

3. Open Project_GR2.cpp in Dev C++ 

4. Compile with F11 or Execute → Compile & Run

-------------------------------------------------------------------------

Table of Contents：

	1.0 Introduction
	2.0 System Overview
	3.0 Main Features
		3.1 Main Menu
		3.2 Member Sign Up
		3.3 Member Login
	4.0 Member Features
		4.1 Browse Products
		4.2 View Cart
		4.3 Payment Process
		4.4 View Order History
		4.5 Rate the System
		4.6 Logout
	5.0 Admin Features
		5.1 Admin Login
		5.2 Product Management
		5.3 Member Management
		5.4 Admin Management (Superadmin only)
		5.5 View Order Records
		5.6 Manage Ratings & Feedback
		5.7 Sales Reports
		5.8 View Dashboard
    5.9 Logout

-------------------------------------------------------------------------

[1.0 Introduction]

Welcome to the Pizza Store System! This system allows customers to sign up as an account as our member and login can browse our products 
such as Pizza, Slide and Beverage, so that members can enjoy purchasing our products.
While administrators can manage the products inventory, admins, members, feedback and view business analytics.

-------------------------------------------------------------------------

[2.0 System Overview]

The system has two main module:
Members: Regular customers who can sign up, login, browse products, make purchases, and provide feedback in the system.
Admins: Store staff who manage products, view admins list, manage members, manage feedback and view sales reports and dashboard.
Superadmin: Higher-level admins with additional user management functions can manage the status of admins list, and other functions also can be managed just like admins.

-------------------------------------------------------------------------

[3.0 Main Features]

    ### 3.1 Main Menu ###

    * When you start the system, you'll see the main menu with options to:

      ===============================================================
                    WELCOME TO YESMOLAR PIZZA STORE
      ===============================================================
      1. Sign Up
      2. Member Login
      3. Admin Login
      4. Exit
      ===============================================================
      Enter your choice:



    ### 3.2 Member Sign Up ###

    * you can select "Sign Up" from the main menu. After you choose to sign up a new account, 
      it will display the sign up menu like below menu, and please enter the valid input for signing up an new account.

      ===============================================================
                        Signing Up As Member...
      ===============================================================
      _______________________________________________
      | NAME REQUIREMENTS                           |
      |_____________________________________________|
      |1. Name must have at least 5 characters      |
      |2. No special character(s) allowed           |
      |3. No number(s) allowed                      |
      |_____________________________________________|

      Enter your full name, [R] to return to the main menu:

      Enter your email (example: user@example.com):
  
      _______________________________________________
      | PASSWORD REQUIREMENTS                       |
      |_____________________________________________|
      |1. Password must be at least 8 characters    |
      |2. Password must have at least 1 uppercase   |
      |3. Password must have at least 1 lowercase   |
      |4. Password must have at least 1 number      |
      |_____________________________________________|

      Enter your new password (example: Xuanting123):

      Confirm your password: 

      Enter your contact number (example: 012-34567890):

    * When you register successful, your Member ID will be displayed after successful registration 
      and display a reminder of successful register:

      ________________________________________________________
      |Registration successful! Your Member ID: U0001        |
      |______________________________________________________|



    ### 3.3 Member Login ###

    * you can select "Member Login" from the main menu. After you choose to login the account, 
      it will display the login menu, and please enter the valid input for logging in your account.


      ===============================================================
                          Logging In As Member...
      ===============================================================

      Enter your email, [R] to return to the main menu:
    

      Enter your password:

    * When you login successful, it will display a reminder of successful login:
      ________________________________________________________
      |Logged in Successfully!			    		    		         |
      |______________________________________________________|


-------------------------------------------------------------------------

[4.0  Member Features]

    * When you login successful, the member menu will be displayed:
    ===============================================================
                        WELCOME Loy yu xuan
    ===============================================================
    1. Browse Product
    2. View My Cart
    3. View Order History
    4. Rate Our System
    5. Log Out
    ===============================================================
    Enter your choice:



    ### 4.1 Browse Products ###

    * You can select "Browse Products" from the member menu, after you enter to browse our products, you can see the categories selection:
      ===============================================================
      |                  WELCOME TO OUR PIZZA STORE!                |
      ===============================================================
      | Select a category:                                          |
      | 1. Pizza                                                    |
      | 2. Side                                                     |
      | 3. Beverage                                                 |
      | 4. Back to Main Menu                                        |
      ===============================================================
      Enter your choice :

    * You can choose a category: Pizza, Side, or Beverage that you want to browse, after you select a category, 
      it will display a lists of active products and their details based on the selected category like pizza products list:

      ----------------------------------------------------------------------
      | Product ID: 122                                                    |
      ----------------------------------------------------------------------
      | Name      : Garlic Butter Chicken Pepperoni                        |
      | Category  : Pizza                                                  |
      | Price     : RM 13.59                                               |
      |                                                                    |
      |with garlic spread, chicken pepperoni, mozzarella cheese & drizzled
      with nachos cheese sauce
      ----------------------------------------------------------------------
      ----------------------------------------------------------------------
      | Product ID: 153                                                    |
      ----------------------------------------------------------------------
      | Name      : Pepperoni Pizza                                        |
      | Category  : Pizza                                                  |
      | Price     : RM 21.00                                               |
      |                                                                    |
      |Features pepperoni.
      ----------------------------------------------------------------------

      -----------------------------------------------------------------
      _________________________________
      | Options:                        |
      | Enter Product ID to add to cart |
      | [C] View Cart                   |
      | [B] Back to Category Selection  |
      | [M] Back to Main Menu           |
      |_________________________________|
      Enter your choice:

    * Below the lists of products, there is an option menu that you can select to view the cart, back to category selection and back to the main menu. 
      Or you can directly enter a product ID, select the product attributes and quantity for adding to cart like:

      _________________________________
      | Options:                        |
      | Enter Product ID to add to cart |
      | [C] View Cart                   |
      | [B] Back to Category Selection  |
      | [M] Back to Main Menu           |
      |_________________________________|

      Enter your choice: 153
      Selecting product: Pepperoni Pizza

          __________________________
          | Available Crust:       |
          | 1. Cheesy Crust        |
          | 2. Crackin Thin        |
          | 3. Pan                 |
          | 4. Stuffed Crust       |
          |________________________|
          Select crust: 1

          ___________________________________
          | Available Size:                   |
          | 1. Personal :  6 inches           |
          | 2. Regular  :  9 inches (+ RM 12) |
          | 3. Large    : 12 inches (+ RM 24) |
          |___________________________________|
          Select size: 1

          Enter quantity : 1

          Successfully added 1 x Pepperoni Pizza to cart!



    ### 4.2 View Cart ###

      * If you select "View Cart" option from the option menu, it will display the item that you added to your cart like:
          ==================================================================
          |                            MY CART                             |
          ==================================================================
          ----------------------------------------------------------------
          | Item 1:                                                        |
          | Product ID : 121                                               |
          | Name       : Large Sweet N Sour Mushroom (Pan)                 |
          | Price      : RM 58.90                                          |
          | Quantity   : 10                                                |
          | Subtotal   : RM 589.00                                         |
          ----------------------------------------------------------------
          ----------------------------------------------------------------
          | Item 2:                                                        |
          | Product ID : 152                                               |
          | Name       : 2 pax Snackbox 2 (Garlic Aioli Dip)               |
          | Price      : RM 29.90                                          |
          | Quantity   : 1                                                 |
          | Subtotal   : RM 29.90                                          |
          ----------------------------------------------------------------
          ==================================================================
          | Total Price: RM 618.90                                         |
          ==================================================================

          ------------------------------------------------------------------
          ____________________________________
          |                                    |
          |    Options:                        |
          |  1. Delete an item from cart       |
          |  2. Edit cart item                 |
          |  3. Proceed to payment             |
          |  4. Back to product list           |
          |  5. Back to member menu            |
          |____________________________________|

          Enter your choice:

      * You can view all items in your cart with items’ details and total price. 
        There are some options that can choose to delete the item from the cart, 
        edit the cart item, proceed to payment, back to the product list and back to the member menu.



    ### 4.3 Payment Process ###

      * When you are ready to check out after shopping, you can select “Proceed to Payment”. 
        After you choose to checkout. It will display the  payment menu like:

          ==================================================================
          |                       CHECKING CART ITEMS                      |
          ==================================================================

          Choose your payment method
          1. Cash
          2. Credit card
          3. Debit card

          Your choice [0 to cancel payment]:


      * There are three payment methods that can be selected : Cash, Credit card and Debit card. 
        You must select a payment method, bank and enter card details.

      * When you successful to completed the payment with cash, it will display the reminder:

          ------------------------------------------------------------------
                                      RECEIPT
          ------------------------------------------------------------------
          Item        : Personal Vegetarian Pizza (Cheesy Crust)
          Price       : RM 15.00
          Quantity    : 1
          Total       : RM 15.00
          ==================================================================
          Payment Amount: RM 15.00
          ==================================================================
          Cash Received: RM 0.00

          Cash  : RM 20
          Change: RM 5.00

          Processing payment.....
          Payment successful! Thank you for your purchase.
          Your cart has been cleared.


      * When you successful to completed the payment with cards, it will display the reminder:

          ------------------------------------------------------------------
                                      RECEIPT
          ------------------------------------------------------------------
          Item        : Personal Pepperoni Pizza (Cheesy Crust)
          Price       : RM 21.00
          Quantity    : 1
          Total       : RM 21.00
          ==================================================================
          Payment Amount: RM 21.00
          ==================================================================

          _______________________________________________
          | We only accept: Master Card & Visa Card      |
          |______________________________________________|

          Select your bank:
          1. Maybank
          2. CIMB
          3. Public Bank
          4. RHB Bank
          5. OCBC Bank
          6. Hong Leong Bank
          7. Bank Islam

          Enter choice (1-7): 1

          Selected Bank: Maybank

          Card number (13-16 digits): 1268459574685136

          Expiry date (MM/YY): 11/26

          CVV: 152


          Processing payment...
          Validating card details.....

          Payment successful! Thank you for your purchase.
          Your cart has been cleared.



    ### 4.4 View Order History ###

      * If you select  "View Order History" from the member menu. 
        you can view your complete purchase history and you can search for specific orders by ID:

          ==================================================================
          |                      PURCHASE HISTORY                          |
          ==================================================================
          ------------------------------------------------------------------
          | Order ID: ORD10                                                |
          | Date    : 2025-06-16 17:39:00                                  |
          | Payment : Credit Card                                          |
          ------------------------------------------------------------------
          Product ID   : 153
          Product Name : Pepperoni Pizza
          Attribute 1  : Cheesy Crust
          Attribute 2  : Personal
          Quantity     : 1
          Price        : RM 21.00
          ------------------------------------------------------------------
          ------------------------------------------------------------------
          | Total Amount: RM 21.00                                         |
          ==================================================================

          ------------------------------------------------------------------
          | Order ID: ORD7                                                 |
          | Date    : 2025-06-16 17:09:05                                  |
          | Payment : Credit Card                                          |
          ------------------------------------------------------------------
          Product ID   : 121
          Product Name : Sweet N Sour Mushroom
          Attribute 1  : Pan
          Attribute 2  : Large
          Quantity     : 10
          Price        : RM 58.90
          ------------------------------------------------------------------
          Product ID   : 152
          Product Name : Snackbox 2
          Attribute 1  : Garlic Aioli Dip
          Attribute 2  : 2 pax
          Quantity     : 1
          Price        : RM 29.90
          ------------------------------------------------------------------
          Product ID   : 153
          Product Name : Pepperoni Pizza
          Attribute 1  : Cheesy Crust
          Attribute 2  : Personal
          Quantity     : 1
          Price        : RM 21.00
          ------------------------------------------------------------------
          ------------------------------------------------------------------
          | Total Amount: RM 639.90                                        |
          ==================================================================


          Do you want to search for a specific Order ID? (Y/N):



    ### 4.5 Rate the System ###

      * If you select "Rate Our System" from the member menu. you can submit your rating and feedback comments:

          ===============================================================
                                  RATE OUR SYSTEM
          ===============================================================
          Enter your rating (1-5, 5 being excellent): 5
          Enter your feedback: nice system

          Thank you for your feedback!

          Press [ENTER] to return to Member Menu.



      ### 4.6 Log Out ###

        * if you select "Log Out" from the member menu. You can return back to the main menu.


-------------------------------------------------------------------------


[5.0  Admin Features]

    ### 5.1 Member Login ###

      * you can select "Admin Login" from the main menu. After you choose to login the account, 
        it will display the login menu, and please enter the valid input for logging in your account.

          ===============================================================
                              Logging In As Admin...
          ===============================================================

          Enter your email, [R] to return to the main menu:
          

          Enter your password:

      * When you login successful, it will display a reminder of successful login:
          ________________________________________________________
              |Logged in Successfully!				|
              |______________________________________________________|



      * When a superadmin login successful, you'll see the superadmin main menu with options:

          ===============================================================
                                  WELCOME yuxuan
          ===============================================================
          1. View Product Inventory
          2. View/Edit Admin List
          3. View/Edit Member List
          4. View Order Record
          5. View Rating Record
          6. View Sales Report
          7. View Dashboard
          8. Log Out
          ===============================================================
          Enter your choice:

      * When a admin login successful, you'll see the admin main menu with options:

          ===============================================================
                                  WELCOME zhixin
          ===============================================================
          1. View Product Inventory
          2. View Admin List
          3. View/Edit Member List
          4. View Order Record
          5. View Rating Record
          6. View Sales Report
          7. View Dashboard
          8. Log Out
          ===============================================================
          Enter your choice:



    ### 5.2 Product Management ###

      * You can choose the option 1 to view product inventory, after you enter the option 1, 
        you can see the categories selection:

          ===============================================================
          | Select a category:                                          |
          | 1. Pizza                                                    |
          | 2. Side                                                     |
          | 3. Beverage                                                 |
          | 4. Back to Main Menu                                        |
          ===============================================================
          Enter your choice :

      * You can choose a category: Pizza, Side or Beverage that you want to browse, 
        after you select a category, it will display a lists of active products based on the selected category like pizza products list:

          ----------------------------------------------------------------------
          | Product ID: 100                                                    |
          ----------------------------------------------------------------------
          | Name      : Cheeseburger Beef                                      |
          | Category  : Pizza                                                  |
          | Price     : RM 18.49                                               |
          | Status    : Inactive                                               |
          |                                                                    |
          |Cheeseburger flavours with ground beef, roasted onions, tomatoes,
          pickles, topped with special cheese sauce & mozzarella cheese.
          ----------------------------------------------------------------------
          ----------------------------------------------------------------------
          | Product ID: 101                                                    |
          ----------------------------------------------------------------------
          | Name      : Cheeseburger Chicken                                   |
          | Category  : Pizza                                                  |
          | Price     : RM 18.49                                               |
          | Status    : Active                                                 |
          |                                                                    |
          |Cheeseburger flavours with chicken meat, roasted onions, tomatoes,
          pickles, topped with special cheese sauce & mozzarella cheese.
          ----------------------------------------------------------------------
          __________________________________________
          | Options:                               |
          | [1] Add New Product to This Category   |
          | [2] Edit Existing Product              |
          | [3] Change Product Status              |
          | [4] Return to Category Selection       |
          |________________________________________|

          Enter your choice:


      1) Add new product
        * If you select the "Add New Product to This Category" option from the inventory menu, 
          it will display the information that needs to enter for adding a product.

          Enter your choice: 1

          Enter product name (or 'C' to cancel): Vegetarian Pizza

          Select category
          1. Pizza
          2. Side
          3. Beverage
          Enter choice (1-3):1

          Enter price: 15

          Enter product description: Features various vegetabless, after including mushroom, onions and peppers.

          Vegetarian Pizza added successfully!
          Press [ENTER] to continue.

      2) Edit existing product
        * If you select the "Edit Existing Product" option from the inventory menu, 
          it will display the information that can be editable for the existing product. 
          To keep the current information for each field, you may leave the input empty.

          Enter your choice: 2

          Enter the Product ID to edit (or 'C' to cancel): 154

          Editing product: Vegetarian Pizza
          [Press ENTER to keep current data]

          Enter new name:

          Select category :
          1. Pizza
          2. Side
          3. Beverage

          Enter new category (1-3): 1

          Enter new price: 21

          Enter new description:

          Select status:
          1. Active
          2. Inactive

          Enter new status (1 or 2): 2

          Product updated successfully!
          Press [ENTER] to continue.

      3) Change product status
        * If you select the "Change Product Status" option from the inventory menu and enter a valid product ID, 
          it will display the editing product name and current status. 
          Then, you will then be prompted to confirm whether you want to change the product's status. 
          If you choose "Y" or "y", the product status will update successfully.

          Enter your choice: 3

          Enter the Product ID to edit (or 'C' to cancel): 154

          Editing product: Vegetarian Pizza
          Current Status : Active

          Do you want to change product status?[Y/N]: y

          Product status updated successfully!
          Press [ENTER] to continue.



      ### 5.3 Admin Management ###
      
      1) Superadmin manage admin list menu
          * If superadmin choose the option 2 to manage admin, it will display the manage admin list menu for superadmin with option: 
            View Active Admins, View Inactive Admins, Add New Admin, Change Admin Status and Return to Admin Menu.

          ===========================================================================
          |                            MANAGE ADMIN LIST                            |
          ===========================================================================
          | [1] View Active Admins                                                  |
          | [2] View Inactive Admins                                                |
          | [3] Add New Admin                                                       |
          | [4] Change Admin Status                                                 |
          | [5] Return to Admin Menu                                                |
          ===========================================================================
          Enter your choice:

      2) Admin manage admin list menu
          * If admin chooses the option 2 to manage admin, it will display the manage admin list menu for admin with option: 
            View Active Admins, View Inactive Admins and Return to Admin Menu.

          ===========================================================================
          |                            MANAGE ADMIN LIST                            |
          ===========================================================================
          | [1] View Active Admins                                                  |
          | [2] View Inactive Admins                                                |
          | [3] Return to Admin Menu                                                |
          ===========================================================================
          Enter your choice:

      3) Superadmin/admin view active admins list
          * If superadmin/admin select the "View Active Admin" option from the manage admin list,
            it will display all the active admin details then it will prompt them to choose whether they want to search for an admin or not.

          ===========================================================================
          |                          ACTIVE ADMIN LIST                              |
          ===========================================================================
          | Member ID         : A0001                                               |
          | Name              : yuxuan                                              |
          | Email             : yuxuan@gmail.com                                    |
          | Contact           : 011-2228228                                         |
          | Position          : superadmin                                          |
          ---------------------------------------------------------------------------
          | Member ID         : A0002                                               |
          | Name              : zhixin                                              |
          | Email             : zhixin@gmail.com                                    |
          | Contact           : 011-33335555                                        |
          | Position          : admin                                               |
          ---------------------------------------------------------------------------
          | Member ID         : A0003                                               |
          | Name              : celine                                              |
          | Email             : celine@gmail.com                                    |
          | Contact           : 010-2282675                                         |
          | Position          : admin                                               |
          ---------------------------------------------------------------------------

          Do you want to search admin by ID? (Y/N to return):


          If superadmin/admin enter "Y" or "y" to search for an admin, 
          it will prompt them to enter an admin ID to search, 
          then they can view the admin details in a new page.


          Do you want to search admin by ID? (Y/N to return): y

          Enter Admin ID to search (or 'C' to cancel): A0001

          ===========================================================================
          |                                ADMIN DETAILS                            |
          ===========================================================================
          | Admin ID          : A0001                                               |
          | Name              : yuxuan                                              |
          | Email             : yuxuan@gmail.com                                    |
          | Contact           : 011-2228228                                         |
          | Position          : superadmin                                          |
          | Status            : Active                                              |
          ===========================================================================

          Press [ENTER] to continue.


      4) Superadmin/admin view inactive admins list
          * If superadmin/admin select the "View Inactive Admin" option from the manage admin list, 
            it will display all the active admin details then it    will prompt them to choose whether they want to search for an admin or not.

          ===========================================================================
          |                           INACTIVE ADMIN LIST                           |
          ===========================================================================
          | Member ID         : A0004                                               |
          | Name              : xuanting                                            |
          | Email             : xuanting@gmail.com                                  |
          | Contact           : 018-7730806                                         |
          | Position          : admin                                               |
          ---------------------------------------------------------------------------

          Do you want to search admin by ID? (Y/N to return):

          * If superadmin/admin enter "Y" or "y" to seacrh for an admin, it will prompt them to enter an admin ID to search, 
            then they can view the admin details in a new page.

          Do you want to search admin by ID? (Y/N to return): y

          Enter Admin ID to search (or 'C' to cancel): A0004

          ===========================================================================
          |                                ADMIN DETAILS                            |
          ===========================================================================
          | Admin ID          : A0004                                               |
          | Name              : xuanting                                            |
          | Email             : xuanting@gmail.com                                  |
          | Contact           : 018-7730806                                         |
          | Position          : admin                                               |
          | Status            : Inactive                                            |
          ===========================================================================

          Press [ENTER] to continue.

          * If superadmin selects "Add New Admin", it will display the requirement input for a new admin. 
            Superadmin are able to add a new admin by entering the information in the correct format.

          ===========================================================================
          |                            ADD NEW ADMIN                                |
          ===========================================================================
          | Requirement:                                                            |
          | -> Name must have at least 5 characters                                 |
          | -> Name must not have special character(s)                              |
          | -> Name must not have number(s) allowed                                 |
          | -> Password need at least 8 chars                                       |
          | -> Password need one uppercase, lowercase, number                       |
          | -> Contact format: 012-3456789 or 012-34567890                          |
          ===========================================================================
          Enter admin name (or 'C' to cancel): xinrou

          Enter email (example: user@example.com): xinrou@gmail.com

          Enter password: Xinrou123

          Confirm your password: Xinrou123

          Enter contact number (example: 012-3456789): 018-7412568

          Admin xinrou added successfully!
          Press [ENTER] to continue.

          * If superadmin selects "Change Admin Status", it will display all the admin id, name, position and status. 
            Superadmin are able to change other admin status by entering their admin ID.

          ==========================================================================================
          |                                     ADMIN LIST                                         |
          ==========================================================================================
          | ID            | Name                  | Position              | Status                 |
          ==========================================================================================
          | A0001         | yuxuan                | superadmin            | Active                 |
          | A0002         | zhixin                | admin                 | Active                 |
          | A0003         | celine                | admin                 | Active                 |
          | A0004         | xuanting              | admin                 | Inactive               |
          | A0005         | xinrou                | admin                 | Active                 |
          ==========================================================================================

          Enter admin ID to change status (or 'C' to cancel): A0002

          Admin A0002 status changed successfully.

          Press [ENTER] to continue.



      ### 5.4 Member Management ###    
          
      1) Admin manage member list menu
          * If admin chooses the option 3 to manage members, it will display the manage member list menu for admin with option: 
            View Active Admins, View Inactive Admins, Change Admin Status and Return to Admin Menu.
          
          ===========================================================================
          |                            MANAGE MEMBER LIST                           |
          ===========================================================================
          | [1] View Active Members                                                 |
          | [2] View Inactive Members                                               |
          | [3] Change Member Status                                                |
          | [4] Return to Admin Menu                                                |
          ===========================================================================
          Enter your choice:

      2) Admin view active member list
          * If the superadmin/admin selects the "View Active Member" option from the manage member list, 
            it will display all the active member details then it will prompt them to choose whether they want to search for a member or not.

          ===========================================================================
          |                         ACTIVE MEMBER LIST                              |
          ===========================================================================
          | Member ID         : U0001                                               |
          | Name              : Loy yu xuan                                         |
          | Email             : yuxuan@gmail.com                                    |
          | Contact           : 011-1111111                                         |
          ---------------------------------------------------------------------------
          | Member ID         : U0002                                               |
          | Name              : Kong lee ching                                      |
          | Email             : celine@gmail.com                                    |
          | Contact           : 022-2222222                                         |
          ---------------------------------------------------------------------------
          | Member ID         : U0003                                               |
          | Name              : Wong xuan ting                                      |
          | Email             : xuanting@gmail.com                                  |
          | Contact           : 018-7730806                                         |
          ---------------------------------------------------------------------------

          Do you want to search member by ID? (Y/N to return):

          * If a superadmin/admin enters "Y" or "y" to search for a member, it will prompt them to enter an member ID to search, 
            then they can view the member details in a new page.

          Do you want to search member by ID? (Y/N to return): y

          Enter Member ID to search (or 'C' to cancel): U0001

          ===========================================================================
          |                                MEMBER DETAILS                           |
          ===========================================================================
          | Member ID         : U0001                                               |
          | Name              : Loy yu xuan                                         |
          | Email             : yuxuan@gmail.com                                    |
          | Contact           : 011-1111111                                         |
          | Status            : Active                                              |
          ===========================================================================

          Press [ENTER] to continue.


      3) Admin view inactive member list
          * If superadmin/admin select the "View Inactive Member" option from the manage member list, 
            it will display all the active member details then it will prompt them to choose whether they want to search for a member or not.

          ===========================================================================
          |                          INACTIVE MEMBER LIST                           |
          ===========================================================================
          | Member ID         : U0004                                               |
          | Name              : Pan zhi xin                                         |
          | Email             : zhixin@gmail.com                                    |
          | Contact           : 044-4444444                                         |
          ---------------------------------------------------------------------------

          Do you want to search member by ID? (Y/N to return):

          * If superadmin/admin enter "Y" or "y" to seacrh for a member, 
            it will prompt them to enter an admin ID to search, 
            then they can view the admin detas in a new page.

          Do you want to search member by ID? (Y/N to return): y

          Enter Member ID to search (or 'C' to cancel): U0004

          ===========================================================================
          |                                MEMBER DETAILS                           |
          ===========================================================================
          | Member ID         : U0004                                               |
          | Name              : Pan zhi xin                                         |
          | Email             : zhixin@gmail.com                                    |
          | Contact           : 044-4444444                                         |
          | Status            : Inactive                                            |
          ===========================================================================

          Press [ENTER] to continue.

          * If superadmin/admin select" "Change Member Status", it will display all the member id, name and status. 
            Superadmin/admin are able to change member status by entering the member ID.
          
          ===========================================================================
          |                                 MEMBER LIST                             |
          ===========================================================================
          | ID                 | Name                          | Status             |
          ===========================================================================
          | U0001              | Loy yu xuan                   | Active             |
          | U0002              | Kong lee ching                | Active             |
          | U0003              | Wong xuan ting                | Active             |
          | U0004              | Pan zhi xin                   | Inactive           |
          ===========================================================================

          Enter Member ID to change status (or 'C' to cancel): U0004

          Member U0004 status changed successfully.

          Press [ENTER] to continue.



      ### 5.5 View Order Records ###    
      
      1) Admin view orders records
          * If superadmin/admin select the "View Order Record", 
            it will display all the orders records in descending order then 
            it will prompt them to choose whether they want to search or sort the order records.

          ==================================================================
          |                        ORDERS RECORDS                          |
          ==================================================================
          ------------------------------------------------------------------
          | Order ID     : ORD6                                            |
          | Member ID    : U0002                                           |
          | Date         : 2025-06-16 18:00:41                             |
          | Payment      : Cash                                            |
          ------------------------------------------------------------------
          | Product ID   : 101                                             |
          | Product Name : Cheeseburger Chicken                            |
          | Attribute 1  : Stuffed Crust                                   |
          | Attribute 2  : Regular                                         |
          | Quantity     : 2                                               |
          | Price        : RM 30.49                                        |
          ------------------------------------------------------------------
          | Product ID   : 130                                             |
          | Product Name : Peach Tea                                       |
          | Attribute 1  : Cold                                            |
          | Attribute 2  : Tin                                             |
          | Quantity     : 1                                               |
          | Price        : RM 4.90                                         |
          ------------------------------------------------------------------
          | Product ID   : 133                                             |
          | Product Name : Mineral Water                                   |
          | Attribute 1  : Cold                                            |
          | Attribute 2  : Tin                                             |
          | Quantity     : 1                                               |
          | Price        : RM 3.00                                         |
          ------------------------------------------------------------------
          | Product ID   : 147                                             |
          | Product Name : Huts Breadstix Cinnamon                         |
          | Attribute 1  : Garlic Aioli Dip                                |
          | Attribute 2  : 1 pax                                           |
          | Quantity     : 1                                               |
          | Price        : RM 6.90                                         |
          ------------------------------------------------------------------
          | Total Amount: RM 75.78                                         |
          ==================================================================

          ------------------------------------------------------------------
          | Order ID     : ORD5                                            |
          | Member ID    : U0004                                           |
          | Date         : 2025-06-15 17:59:18                             |
          | Payment      : Credit Card                                     |
          ------------------------------------------------------------------
          | Product ID   : 109                                             |
          | Product Name : Aloha Chicken                                   |
          | Attribute 1  : Pan                                             |
          | Attribute 2  : Personal                                        |
          | Quantity     : 1                                               |
          | Price        : RM 16.09                                        |
          ------------------------------------------------------------------
          | Product ID   : 115                                             |
          | Product Name : Deluxe Cheese                                   |
          | Attribute 1  : Cheesy Crust                                    |
          | Attribute 2  : Large                                           |
          | Quantity     : 1                                               |
          | Price        : RM 40.09                                        |
          ------------------------------------------------------------------
          | Product ID   : 125                                             |
          | Product Name : Coke                                            |
          | Attribute 1  : Cold                                            |
          | Attribute 2  : Bottle                                          |
          | Quantity     : 1                                               |
          | Price        : RM 7.50                                         |
          ------------------------------------------------------------------
          | Total Amount: RM 63.68                                         |
          ==================================================================

          1. Search Orders
          2. Sort Orders
          3. Return to Admin Menu

          Enter your choice (1-3):

      2) Admin search orders records
          * If superadmin/admin select the "Search Orders" in view order records page, 
            they can choose either search records by order ID or member ID.

          Enter your choice (1-3): 1
          ---------------------------------
          |       SEARCH ORDERS BY        |
          | 1. Order ID                   |
          | 2. Member ID                  |
          | 3. Cancel                     |
          ---------------------------------

          Enter your choice (1-3):

          * Superadmin/admin can enter "1" to search the records by order ID. 
            After they enter a valid order ID, it will display the order details for that order ID in a new page.

          Enter your choice (1-3): 1
          ---------------------------------
          |       SEARCH ORDERS BY        |
          | 1. Order ID                   |
          | 2. Member ID                  |
          | 3. Cancel                     |
          ---------------------------------

          Enter your choice (1-3): 1

          Enter Order ID to search: ORD1

          ==================================================================
          |                       ORDER ID: ORD1                           |
          ==================================================================
          ------------------------------------------------------------------
          | Member ID    : U0002                                           |
          | Date         : 2025-03-12 17:58:16                             |
          | Payment      : Cash                                            |
          ------------------------------------------------------------------
          | Product ID   : 119                                             |
          | Product Name : Tangy Tuna                                      |
          | Attribute 1  : Cheesy Crust                                    |
          | Attribute 2  : Personal                                        |
          | Quantity     : 2                                               |
          | Price        : RM 13.59                                        |
          ------------------------------------------------------------------
          | Total Amount: RM 27.18                                         |
          ==================================================================

          Press [ENTER] to return to order record menu.

          * Superadmin/admin can enter "2" to search the records by member ID. 
            After they enter a valid member ID, it will display the order details for that member already purchased in a new page.

          Enter your choice (1-3): 1
          ---------------------------------
          |       SEARCH ORDERS BY        |
          | 1. Order ID                   |
          | 2. Member ID                  |
          | 3. Cancel                     |
          ---------------------------------

          Enter your choice (1-3): 2

          Enter Member ID to search: U0002

          ==================================================================
          |                 ORDERS FOR MEMBER ID: U0002                    |
          ==================================================================
          ------------------------------------------------------------------
          | Order ID     : ORD6                                            |
          | Date         : 2025-06-16 18:00:41                             |
          | Payment      : Cash                                            |
          ------------------------------------------------------------------
          | Product ID   : 101                                             |
          | Product Name : Cheeseburger Chicken                            |
          | Attribute 1  : Stuffed Crust                                   |
          | Attribute 2  : Regular                                         |
          | Quantity     : 2                                               |
          | Price        : RM 30.49                                        |
          ------------------------------------------------------------------
          | Product ID   : 130                                             |
          | Product Name : Peach Tea                                       |
          | Attribute 1  : Cold                                            |
          | Attribute 2  : Tin                                             |
          | Quantity     : 1                                               |
          | Price        : RM 4.90                                         |
          ------------------------------------------------------------------
          | Product ID   : 133                                             |
          | Product Name : Mineral Water                                   |
          | Attribute 1  : Cold                                            |
          | Attribute 2  : Tin                                             |
          | Quantity     : 1                                               |
          | Price        : RM 3.00                                         |
          ------------------------------------------------------------------
          | Product ID   : 147                                             |
          | Product Name : Huts Breadstix Cinnamon                         |
          | Attribute 1  : Garlic Aioli Dip                                |
          | Attribute 2  : 1 pax                                           |
          | Quantity     : 1                                               |
          | Price        : RM 6.90                                         |
          ------------------------------------------------------------------
          | Total Amount: RM 75.78                                         |
          ==================================================================
          ------------------------------------------------------------------
          | Order ID     : ORD2                                            |
          | Date         : 2025-04-20 18:06:28                             |
          | Payment      : Credit Card                                     |
          ------------------------------------------------------------------
          | Product ID   : 130                                             |
          | Product Name : Peach Tea                                       |
          | Attribute 1  : Cold                                            |
          | Attribute 2  : Bottle                                          |
          | Quantity     : 1                                               |
          | Price        : RM 6.90                                         |
          ------------------------------------------------------------------
          | Product ID   : 150                                             |
          | Product Name : Nacho Cheese Ball                               |
          | Attribute 1  : Garlic Aioli Dip                                |
          | Attribute 2  : 1 pax                                           |
          | Quantity     : 1                                               |
          | Price        : RM 10.90                                        |
          ------------------------------------------------------------------
          | Total Amount: RM 17.80                                         |
          ==================================================================
          ------------------------------------------------------------------
          | Order ID     : ORD1                                            |
          | Date         : 2025-03-12 17:58:16                             |
          | Payment      : Cash                                            |
          ------------------------------------------------------------------
          | Product ID   : 119                                             |
          | Product Name : Tangy Tuna                                      |
          | Attribute 1  : Cheesy Crust                                    |
          | Attribute 2  : Personal                                        |
          | Quantity     : 2                                               |
          | Price        : RM 13.59                                        |
          ------------------------------------------------------------------
          | Total Amount: RM 27.18                                         |
          ==================================================================

          Press [ENTER] to return to order record menu.


          * If superadmin/admin select the "Sort Orders" in view order records page, 
            they can choose either sort records by newest or oldest first.

          Enter your choice (1-3): 2
          ---------------------------------------------
          |              SORT ORDERS BY               |
          | 1. Date (Newest First)                    |
          | 2. Date (Oldest First)                    |
          | 3. Cancel                                 |
          ---------------------------------------------
          Enter your choice (1-3):

          * Superadmin/admin can enter "1" to sort the records by newest first. 
            Then, it will display all the sorted records in a new page.

          ==================================================================
          |                    SORTED ORDERS RECORDS                       |
          ==================================================================
          ------------------------------------------------------------------
          | Order ID     : ORD6                                            |
          | Member ID    : U0002                                           |
          | Date         : 2025-06-16 18:00:41                             |
          | Payment      : Cash                                            |
          ------------------------------------------------------------------
          | Product ID   : 101                                             |
          | Product Name : Cheeseburger Chicken                            |
          | Attribute 1  : Stuffed Crust                                   |
          | Attribute 2  : Regular                                         |
          | Quantity     : 2                                               |
          | Price        : RM 30.49                                        |
          ------------------------------------------------------------------
          | Product ID   : 130                                             |
          | Product Name : Peach Tea                                       |
          | Attribute 1  : Cold                                            |
          | Attribute 2  : Tin                                             |
          | Quantity     : 1                                               |
          | Price        : RM 4.90                                         |
          ------------------------------------------------------------------
          | Product ID   : 133                                             |
          | Product Name : Mineral Water                                   |
          | Attribute 1  : Cold                                            |
          | Attribute 2  : Tin                                             |
          | Quantity     : 1                                               |
          | Price        : RM 3.00                                         |
          ------------------------------------------------------------------
          | Product ID   : 147                                             |
          | Product Name : Huts Breadstix Cinnamon                         |
          | Attribute 1  : Garlic Aioli Dip                                |
          | Attribute 2  : 1 pax                                           |
          | Quantity     : 1                                               |
          | Price        : RM 6.90                                         |
          ------------------------------------------------------------------
          | Total Amount: RM 75.78                                         |
          ==================================================================

          ------------------------------------------------------------------
          | Order ID     : ORD5                                            |
          | Member ID    : U0004                                           |
          | Date         : 2025-06-15 17:59:18                             |
          | Payment      : Credit Card                                     |
          ------------------------------------------------------------------
          | Product ID   : 109                                             |
          | Product Name : Aloha Chicken                                   |
          | Attribute 1  : Pan                                             |
          | Attribute 2  : Personal                                        |
          | Quantity     : 1                                               |
          | Price        : RM 16.09                                        |
          ------------------------------------------------------------------
          | Product ID   : 115                                             |
          | Product Name : Deluxe Cheese                                   |
          | Attribute 1  : Cheesy Crust                                    |
          | Attribute 2  : Large                                           |
          | Quantity     : 1                                               |
          | Price        : RM 40.09                                        |
          ------------------------------------------------------------------
          | Product ID   : 125                                             |
          | Product Name : Coke                                            |
          | Attribute 1  : Cold                                            |
          | Attribute 2  : Bottle                                          |
          | Quantity     : 1                                               |
          | Price        : RM 7.50                                         |
          ------------------------------------------------------------------
          | Total Amount: RM 63.68                                         |
          ==================================================================


          Press [ENTER] to return to order record menu.

          * Superadmin/admin can enter "2" to sort the records by oldest first. 
            Then, it will display all the sorted records in a new page.

          ==================================================================
          |                    SORTED ORDERS RECORDS                       |
          ==================================================================
          ------------------------------------------------------------------
          | Order ID     : ORD1                                            |
          | Member ID    : U0002                                           |
          | Date         : 2025-03-12 17:58:16                             |
          | Payment      : Cash                                            |
          ------------------------------------------------------------------
          | Product ID   : 119                                             |
          | Product Name : Tangy Tuna                                      |
          | Attribute 1  : Cheesy Crust                                    |
          | Attribute 2  : Personal                                        |
          | Quantity     : 2                                               |
          | Price        : RM 13.59                                        |
          ------------------------------------------------------------------
          | Total Amount: RM 27.18                                         |
          ==================================================================

          ------------------------------------------------------------------
          | Order ID     : ORD2                                            |
          | Member ID    : U0002                                           |
          | Date         : 2025-04-20 18:06:28                             |
          | Payment      : Credit Card                                     |
          ------------------------------------------------------------------
          | Product ID   : 130                                             |
          | Product Name : Peach Tea                                       |
          | Attribute 1  : Cold                                            |
          | Attribute 2  : Bottle                                          |
          | Quantity     : 1                                               |
          | Price        : RM 6.90                                         |
          ------------------------------------------------------------------
          | Product ID   : 150                                             |
          | Product Name : Nacho Cheese Ball                               |
          | Attribute 1  : Garlic Aioli Dip                                |
          | Attribute 2  : 1 pax                                           |
          | Quantity     : 1                                               |
          | Price        : RM 10.90                                        |
          ------------------------------------------------------------------
          | Total Amount: RM 17.80                                         |
          ==================================================================


          Press [ENTER] to return to order record menu.



      ### 5.6 Manage Ratings & Feedback ###   

      1) Admin view rating records
          * If superadmin/admin select the "View Rating Record", it will display all the rating records 
            that members are given then it will prompt them to choose whether they want to filter feedback by rating level or sort feedback..


          ===========================================================================
          | Date & Time  : 2025-06-11 13:10:57                                      |
          ===========================================================================
          | Member ID    : U0001                                                    |
          | Rating       : 5                                                        |
          | Comment      : gooood                                                   |
          ---------------------------------------------------------------------------
          ===========================================================================
          | Date & Time  : 2025-06-11 13:17:19                                      |
          ===========================================================================
          | Member ID    : U0001                                                    |
          | Rating       : 4                                                        |
          | Comment      : Niceeee                                                  |
          ---------------------------------------------------------------------------
          1. Filter feedback by rate level
          2. Sort feedback and rating

          Enter your choice (R for return):

          * If superadmin/admin select the "Filter feedback by rate level" in the view rating records page, 
            they can enter the rating level that they want to filter and view. 
            Then, it will display the filtered record with its details based on the rating level that was entered by the admin.

          Enter the rating level to filter by (1 to 5): 5
          ===========================================================================
          |                    Filtered Feedback (Rating = 5)                       |
          ===========================================================================
          | Date & Time  : 2025-06-11 13:10:57                                      |
          ===========================================================================
          | Member ID    : U0001                                                    |
          | Rating       : 5                                                        |
          | Comment      : gooood                                                   |
          ---------------------------------------------------------------------------

          Press [ENTER] to return to feedback menu.

          * If superadmin/admin select the "Sort feedback and rating" in the view rating records page, it provides four sorting options:
            Rating (High to Low), Rating (Low to High), Date (Newest),and Date (Oldeest) and Cancel. 
            Admin can choose their preferred sorting method to view the records accordingly.

          Enter your choice (R for return): 2
          -------------------------------
          | Sort feedback by:           |
          | 1. Rating (High to Low)     |
          | 2. Rating (Low to High)     |
          | 3. Date (Newest)            |
          | 4. Date (Oldest)            |
          | 5. Cancel                   |
          -------------------------------
          Enter your choice (1-5):

          * Superadmin/admin can enter "1" to sort the records by rating level in descending order. 
            Then, it will display all the sorted records in a new page
            
          ======================================================================
          |         SORTED FEEDBACK & RATING (Rating - Highest First)          |
          ======================================================================
          | Member ID             : U0001                                      |
          | Rating                : 5                                          |
          | Comment               : gooood                                     |
          | Datetime              : 2025-06-11 13:10:57                        |
          ----------------------------------------------------------------------
          ======================================================================
          | Member ID             : U0001                                      |
          | Rating                : 4                                          |
          | Comment               : Niceeee                                    |
          | Datetime              : 2025-06-11 13:17:19                        |
          ----------------------------------------------------------------------

          Press [ENTER] to return to feedback menu.

          * Superadmin/admin can enter "2" to sort the records by rating level in ascending order. 
            Then, it will display all the sorted records in a new page

          ======================================================================
          |         SORTED FEEDBACK & RATING (Rating - Lowest First)           |
          ======================================================================
          | Member ID             : U0001                                      |
          | Rating                : 4                                          |
          | Comment               : Niceeee                                    |
          | Datetime              : 2025-06-11 13:17:19                        |
          ----------------------------------------------------------------------
          ======================================================================
          | Member ID             : U0001                                      |
          | Rating                : 5                                          |
          | Comment               : gooood                                     |
          | Datetime              : 2025-06-11 13:10:57                        |
          ----------------------------------------------------------------------

          Press [ENTER] to return to feedback menu.

          * Superadmin/admin can enter "3" to sort the records by date in descending order. 
            Then, it will display all the sorted records in a new page.

          ======================================================================
          |          SORTED FEEDBACK & RATING (Date - Newest First)            |
          ======================================================================
          | Member ID             : U0001                                      |
          | Rating                : 4                                          |
          | Comment               : Niceeee                                    |
          | Datetime              : 2025-06-11 13:17:19                        |
          ----------------------------------------------------------------------
          ======================================================================
          | Member ID             : U0001                                      |
          | Rating                : 5                                          |
          | Comment               : gooood                                     |
          | Datetime              : 2025-06-11 13:10:57                        |
          ----------------------------------------------------------------------

          Press [ENTER] to return to feedback menu.

          * Superadmin/admin can enter "4" to sort the records by date in ascending order. 
            Then, it will display all the sorted records in a new page

          ======================================================================
          |          SORTED FEEDBACK & RATING (Date - Oldest First)            |
          ======================================================================
          | Member ID             : U0001                                      |
          | Rating                : 5                                          |
          | Comment               : gooood                                     |
          | Datetime              : 2025-06-11 13:10:57                        |
          ----------------------------------------------------------------------
          ======================================================================
          | Member ID             : U0001                                      |
          | Rating                : 4                                          |
          | Comment               : Niceeee                                    |
          | Datetime              : 2025-06-11 13:17:19                        |
          ----------------------------------------------------------------------

          Press [ENTER] to return to feedback menu.



      ### 5.7 Sales Reports ###   

    1) Admin view sales report
      * If superadmin/admin select the "View Sales Report", it will display the menu of the sales report and provide 4 options: 
        View Complete Sales Report, View Sales Summary, View Sales and Return to Admin Menu.

          ===========================================================================
          |                          SALES REPORT GENERATOR                         |
          ===========================================================================
          | [1] View Complete Sales Report                                          |
          | [2] View Sales Summary                                                  |
          | [3] View Sales List                                                     |
          | [4] Return to Admin Menu                                                |
          ===========================================================================
          Enter your choice:

      
          * If superadmin/admin select the "View Complete Sales Report", 
            it will show a menu displathree 4 option Total Revenue (Sales), Quantity Sold and Return to Sales Report Menu.

          CHOICE 1: Total Revenue
          --------------------------------------
          | Sort sales report by:              |
          | 1. Total Revenue (Sales)           |
          | 2. Quantity Sold                   |
          | 3. Return to Sales Report Menu     |
          --------------------------------------
          Enter choice : 1

          +------------------------------------------------------------------------------------------------------------------+
          |                                                 SALES SUMMARY                                                    |
          +------------------------------------------------------------------------------------------------------------------+
          | Total Orders      : 6                                                                                            |
          | Total Revenue     : RM 1146.43                                                                                   |
          +------------------------------------------------------------------------------------------------------------------+
          | Top Selling Products by Revenue:                                                                                 |
          | - Sweet N Sour Mushroom                   Revenue: RM 857.30         Sold: 17                                    |
          | - Cheeseburger Chicken                    Revenue: RM 60.98          Sold: 2                                     |
          | - Deluxe Cheese                           Revenue: RM 40.09          Sold: 1                                     |
          | - Beef Pepperoni                          Revenue: RM 40.09          Sold: 1                                     |
          | - Snackbox 2                              Revenue: RM 29.90          Sold: 1                                     |
          +------------------------------------------------------------------------------------------------------------------+

          +--------------------------------------------------------------------------------------------------------+
          |                                         SALES LIST : ORDER DETAILS                                     |
          +--------------------------------------------------------------------------------------------------------+
          | No.   | Item                                                             | Qty       | Unit Price      |
          +--------------------------------------------------------------------------------------------------------+
          |     1 | Cheeseburger Chicken                                             |          2|           30.49 |
          |     2 | Peach Tea                                                        |          1|            4.90 |
          |     3 | Mineral Water                                                    |          1|            3.00 |
          |     4 | Huts Breadstix Cinnamon                                          |          1|            6.90 |
          +--------------------------------------------------------------------------------------------------------+
          |                                                                               TOTAL: |           75.78 |
          +--------------------------------------------------------------------------------------------------------+
          |     1 | Aloha Chicken                                                    |          1|           16.09 |
          |     2 | Deluxe Cheese                                                    |          1|           40.09 |
          |     3 | Coke                                                             |          1|            7.50 |
          +--------------------------------------------------------------------------------------------------------+
          |                                                                               TOTAL: |           63.68 |
          +--------------------------------------------------------------------------------------------------------+
          |     1 | Beef Pepperoni                                                   |          1|           40.09 |
          |     2 | Lemonade                                                         |          2|            4.90 |
          |     3 | Krispy Curly Fries                                               |          1|           14.90 |
          +--------------------------------------------------------------------------------------------------------+
          |                                                                               TOTAL: |           64.79 |
          +--------------------------------------------------------------------------------------------------------+
          |     1 | Sweet N Sour Mushroom                                            |          2|           46.90 |
          |     2 | Sweet N Sour Mushroom                                            |         10|           58.90 |
          |     3 | Sweet N Sour Mushroom                                            |          5|           34.90 |
          |     4 | Mineral Water                                                    |          2|            5.00 |
          |     5 | Snackbox 2                                                       |          1|           29.90 |
          +--------------------------------------------------------------------------------------------------------+
          |                                                                               TOTAL: |          897.20 |
          +--------------------------------------------------------------------------------------------------------+
          |     1 | Peach Tea                                                        |          1|            6.90 |
          |     2 | Nacho Cheese Ball                                                |          1|           10.90 |
          +--------------------------------------------------------------------------------------------------------+
          |                                                                               TOTAL: |           17.80 |
          +--------------------------------------------------------------------------------------------------------+
          |     1 | Tangy Tuna                                                       |          2|           13.59 |
          +--------------------------------------------------------------------------------------------------------+
          |                                                                               TOTAL: |           27.18 |
          +--------------------------------------------------------------------------------------------------------+

          Press [ENTER] to continue.


          CHOICE 2: Quantity Sold
          +------------------------------------------------------------------------------------------------------------------+
          |                                                 SALES SUMMARY                                                    |
          +------------------------------------------------------------------------------------------------------------------+
          | Total Orders      : 6                                                                                            |
          | Total Revenue     : RM 1146.43                                                                                   |
          +------------------------------------------------------------------------------------------------------------------+
          | Top Selling Products by Quantity Sold:                                                                           |
          | - Sweet N Sour Mushroom                   Sold: 17             Revenue: RM 857.30                                |
          | - Mineral Water                           Sold: 3              Revenue: RM 13.00                                 |
          | - Tangy Tuna                              Sold: 2              Revenue: RM 27.18                                 |
          | - Cheeseburger Chicken                    Sold: 2              Revenue: RM 60.98                                 |
          | - Peach Tea                               Sold: 2              Revenue: RM 11.80                                 |
          +------------------------------------------------------------------------------------------------------------------+
          +--------------------------------------------------------------------------------------------------------+
          |                                         SALES LIST : ORDER DETAILS                                     |
          +--------------------------------------------------------------------------------------------------------+
          | No.   | Item                                                             | Qty       | Unit Price      |
          +--------------------------------------------------------------------------------------------------------+
          |     1 | Cheeseburger Chicken                                             |          2|           30.49 |
          |     2 | Peach Tea                                                        |          1|            4.90 |
          |     3 | Mineral Water                                                    |          1|            3.00 |
          |     4 | Huts Breadstix Cinnamon                                          |          1|            6.90 |
          +--------------------------------------------------------------------------------------------------------+
          |                                                                               TOTAL: |           75.78 |
          +--------------------------------------------------------------------------------------------------------+
          |     1 | Aloha Chicken                                                    |          1|           16.09 |
          |     2 | Deluxe Cheese                                                    |          1|           40.09 |
          |     3 | Coke                                                             |          1|            7.50 |
          +--------------------------------------------------------------------------------------------------------+
          |                                                                               TOTAL: |           63.68 |
          +--------------------------------------------------------------------------------------------------------+
          |     1 | Beef Pepperoni                                                   |          1|           40.09 |
          |     2 | Lemonade                                                         |          2|            4.90 |
          |     3 | Krispy Curly Fries                                               |          1|           14.90 |
          +--------------------------------------------------------------------------------------------------------+
          |                                                                               TOTAL: |           64.79 |
          +--------------------------------------------------------------------------------------------------------+
          |     1 | Sweet N Sour Mushroom                                            |          2|           46.90 |
          |     2 | Sweet N Sour Mushroom                                            |         10|           58.90 |
          |     3 | Sweet N Sour Mushroom                                            |          5|           34.90 |
          |     4 | Mineral Water                                                    |          2|            5.00 |
          |     5 | Snackbox 2                                                       |          1|           29.90 |
          +--------------------------------------------------------------------------------------------------------+
          |                                                                               TOTAL: |          897.20 |
          +--------------------------------------------------------------------------------------------------------+
          |     1 | Peach Tea                                                        |          1|            6.90 |
          |     2 | Nacho Cheese Ball                                                |          1|           10.90 |
          +--------------------------------------------------------------------------------------------------------+
          |                                                                               TOTAL: |           17.80 |
          +--------------------------------------------------------------------------------------------------------+
          |     1 | Tangy Tuna                                                       |          2|           13.59 |
          +--------------------------------------------------------------------------------------------------------+
          |                                                                               TOTAL: |           27.18 |
          +--------------------------------------------------------------------------------------------------------+

          Press [ENTER] to continue.


      2) Admin view sales summary

          CHOICE 1: Total Revenue
          --------------------------------------
          | Sort sales summary by:             |
          | 1. Total Revenue (Sales)           |
          | 2. Quantity Sold                   |
          | 3. Return to Sales Report Menu     |
          --------------------------------------
          Enter choice : 1

          +------------------------------------------------------------------------------------------------------------------+
          |                                                 SALES SUMMARY                                                    |
          +------------------------------------------------------------------------------------------------------------------+
          | Total Orders      : 6                                                                                            |
          | Total Revenue     : RM 1146.43                                                                                   |
          +------------------------------------------------------------------------------------------------------------------+
          | Top Selling Products by Revenue:                                                                                 |
          | - Sweet N Sour Mushroom                   Revenue: RM 857.30         Sold: 17                                    |
          | - Cheeseburger Chicken                    Revenue: RM 60.98          Sold: 2                                     |
          | - Deluxe Cheese                           Revenue: RM 40.09          Sold: 1                                     |
          | - Beef Pepperoni                          Revenue: RM 40.09          Sold: 1                                     |
          | - Snackbox 2                              Revenue: RM 29.90          Sold: 1                                     |
          +------------------------------------------------------------------------------------------------------------------+

          Press [ENTER] to continue.

          CHOICE 2: Quantity Sold
          --------------------------------------
          | Sort sales summary by:             |
          | 1. Total Revenue (Sales)           |
          | 2. Quantity Sold                   |
          | 3. Return to Sales Report Menu     |
          --------------------------------------
          Enter choice : 2

          +------------------------------------------------------------------------------------------------------------------+
          |                                                 SALES SUMMARY                                                    |
          +------------------------------------------------------------------------------------------------------------------+
          | Total Orders      : 6                                                                                            |
          | Total Revenue     : RM 1146.43                                                                                   |
          +------------------------------------------------------------------------------------------------------------------+
          | Top Selling Products by Quantity Sold:                                                                           |
          | - Sweet N Sour Mushroom                   Sold: 17             Revenue: RM 857.30                                |
          | - Mineral Water                           Sold: 3              Revenue: RM 13.00                                 |
          | - Tangy Tuna                              Sold: 2              Revenue: RM 27.18                                 |
          | - Cheeseburger Chicken                    Sold: 2              Revenue: RM 60.98                                 |
          | - Peach Tea                               Sold: 2              Revenue: RM 11.80                                 |
          +------------------------------------------------------------------------------------------------------------------+

          Press [ENTER] to continue.


      3) Admin View Sales List

          +--------------------------------------------------------------------------------------------------------+
          |                                         SALES LIST : ORDER DETAILS                                     |
          +--------------------------------------------------------------------------------------------------------+
          | No.   | Item                                                             | Qty       | Unit Price      |
          +--------------------------------------------------------------------------------------------------------+
          |     1 | Cheeseburger Chicken                                             |          2|           30.49 |
          |     2 | Peach Tea                                                        |          1|            4.90 |
          |     3 | Mineral Water                                                    |          1|            3.00 |
          |     4 | Huts Breadstix Cinnamon                                          |          1|            6.90 |
          +--------------------------------------------------------------------------------------------------------+
          |                                                                               TOTAL: |           75.78 |
          +--------------------------------------------------------------------------------------------------------+
          |     1 | Aloha Chicken                                                    |          1|           16.09 |
          |     2 | Deluxe Cheese                                                    |          1|           40.09 |
          |     3 | Coke                                                             |          1|            7.50 |
          +--------------------------------------------------------------------------------------------------------+
          |                                                                               TOTAL: |           63.68 |
          +--------------------------------------------------------------------------------------------------------+
          |     1 | Beef Pepperoni                                                   |          1|           40.09 |
          |     2 | Lemonade                                                         |          2|            4.90 |
          |     3 | Krispy Curly Fries                                               |          1|           14.90 |
          +--------------------------------------------------------------------------------------------------------+
          |                                                                               TOTAL: |           64.79 |
          +--------------------------------------------------------------------------------------------------------+
          |     1 | Sweet N Sour Mushroom                                            |          2|           46.90 |
          |     2 | Sweet N Sour Mushroom                                            |         10|           58.90 |
          |     3 | Sweet N Sour Mushroom                                            |          5|           34.90 |
          |     4 | Mineral Water                                                    |          2|            5.00 |
          |     5 | Snackbox 2                                                       |          1|           29.90 |
          +--------------------------------------------------------------------------------------------------------+
          |                                                                               TOTAL: |          897.20 |
          +--------------------------------------------------------------------------------------------------------+
          |     1 | Peach Tea                                                        |          1|            6.90 |
          |     2 | Nacho Cheese Ball                                                |          1|           10.90 |
          +--------------------------------------------------------------------------------------------------------+
          |                                                                               TOTAL: |           17.80 |
          +--------------------------------------------------------------------------------------------------------+
          |     1 | Tangy Tuna                                                       |          2|           13.59 |
          +--------------------------------------------------------------------------------------------------------+
          |                                                                               TOTAL: |           27.18 |
          +--------------------------------------------------------------------------------------------------------+

          Press [ENTER] to continue.



      ### 5.8 View Dashboard ###
      * If the superadmin/admin selects "View Dashboard", the system will display an overview that includes summary statistics, 
        monthly sales, the 3 most recent orders, and a feedback summary for the entire system.

        =================================================================
        |                           DASHBOARD                           |
        =================================================================
        | SUMMARY STATISTICS:                                           |
        |---------------------------------------------------------------|
        | Products:   53 total |   51 active |    2 inactive            |
        | Members:     4 total |    4 active |    0 inactive            |
        | Orders:      6 total | Sales: RM 1146.43                      |
        |---------------------------------------------------------------|
        | MONTHLY SALES (2025):                                         |
        |---------------------------------------------------------------|
        | 01/2025: RM       0.00                                        |
        | 02/2025: RM       0.00                                        |
        | 03/2025: RM      27.18                                        |
        | 04/2025: RM      17.80                                        |
        | 05/2025: RM     897.20                                        |
        | 06/2025: RM     204.25                                        |
        | 07/2025: RM       0.00                                        |
        | 08/2025: RM       0.00                                        |
        | 09/2025: RM       0.00                                        |
        | 10/2025: RM       0.00                                        |
        | 11/2025: RM       0.00                                        |
        | 12/2025: RM       0.00                                        |
        |---------------------------------------------------------------|
        | RECENT ORDERS (Last 3)                                        |
        |---------------------------------------------------------------|
        | ORD6 - 2025-06-16 18:00:4 | RM 75.78                          |
        | ORD5 - 2025-06-15 17:59:1 | RM 63.68                          |
        | ORD4 - 2025-06-01 13:56:2 | RM 64.79                          |
        |---------------------------------------------------------------|
        | FEEDBACK SUMMARY:                                             |
        |---------------------------------------------------------------|
        | Total Ratings: 2    | Average: 4.5/5.0                        |
        |---------------------------------------------------------------|
        | 1 star: 0   (0.0  %)                                          |
        | 2 star: 0   (0.0  %)                                          |
        | 3 star: 0   (0.0  %)                                          |
        | 4 star: 1   (50.0 %)                                          |
        | 5 star: 1   (50.0 %)                                          |
        =================================================================


      ### 5.9 Log Out ###

        * if you select "Log Out" from the admin menu. You can return back to the main menu.