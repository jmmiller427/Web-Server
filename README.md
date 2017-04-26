# Web-Server
Given TCP socket code already to start up a simple web server, I had to handle what file the user was looking for when they accessed the server. Then if the file was found it was then sent with a proper HTTP header and the data itself. 
All of my edits to the code given in class were made to HandleTCPClient.c

The example code was taken from http://cs.ecs.baylor.edu/~donahoo/practical/CSockets/textcode.html and then edited from there. 

This program will load any html, txt, jpg and gif file that exists in the proper directory in the server. The header status code sends the proper 200 OK header if the file does exist. One limitation of the program is the program does not send the proper 404 Not Found status code. There is an if statement to check if the file exists and if it does it goes in to create the proper 200 OK header, but if the file doesnt exist it should go into an else statement where the header will be a 404 Not Found, but the program does not go into this else statement. That is the only known limitation of the program. 
It is ran as:

./myserver <port no> <root directory path>

Then on the browser:

machine_name:port_no/file_name
