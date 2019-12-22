This is a basic Operating System that uses Threads in Java to stimulate the operation between user input, disks, printer threads, and printers.

* 3 main components: Users, Disks, and Printer.
* Main idea of the system is the synchronization block in Java that just allows only one thread to use the resource at a time. 
    All other threads attempting to enter the synchronized block are blocked until the thread inside the synchronized block exits the block.
* Each user input creates a User Thread that check if any disk is not used and save input to the next free sector on disk. 
* For each print command, a printer thread is created and it prints out user input to the printer.

Please see the video at this link for more info: https://youtu.be/dsqWCmZD5R8
