# Hotel-Managemet-System-C
Hotel Management System A C-based console application designed to manage hotel operations, including room bookings, billing, and guest records. The system ensures data persistence by saving all records to a local file between executions. 

Guest Functions :  
-Book Room : Reserves rooms based on guest count,room preferences and stay dates. Generates a unique Guest ID for all future interactions.  
-Check Out : Removes guest data from active memory after verifying payment status.  
-Pay Bill  : Calculates total charges based on check-in & check-out dates and generates a formal bill file.   

Admin Functions :  
-Search Guest    : locates a guest's record using their unique ID.  
-View All Guests : Displays a complete list of currently checked-in guests.   
-Clear All Data  : An administrative tool to wipe all guest records from the system. 

Data Persistence :  
-Automatic Saving : Before termination, the program saves all current guest data to guests.txt and safely frees allocated memory. 
-Automatic Loading : On startup, the program automatically loads existing data from guests.txt.

Constraints & Rules :  
-Guest Names: Maximum 25 characters; no spaces allowed.  
-Booking Limit: The system supports a maximum of 100 bookings.(if limit exceeds we can use clear all data function to start bookings again)    
-To allow for room cleaning, a 1-day gap is required between different bookings for the same room (e.g., if Guest A checks out on the 5th,  
Guest B can check in on the 6th).  
-A single person can book a stay of less than one day.  
-Input Validation: Invalid inputs may cause the program to terminate to protect data integrity. Please follow on-screen instructions during run  time carefully.  

TO EXECUTE :  
Note: The following commands are designed for Linux/Unix-based terminals (including macOS and WSL). They will not work natively in Windows  Command Prompt or PowerShell.  
Ensure you have the following files in your directory:  
main.c (main function)  
mylib.c (Helper functions)  
functions.h (Header file)  
Makefile (Build instructions)   

run following commands on your terminal : 

-necessary compilation is done by running  the makefile as 'make'   
-execution is done by running './a.out'  
-to remove executables and start fresh run 'make clean'

