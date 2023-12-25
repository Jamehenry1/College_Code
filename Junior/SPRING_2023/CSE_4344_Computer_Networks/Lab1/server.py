#Nghia Lam
#1001699317

import socket
import os
from _thread import *
#import time <- This was just to checked if threading worked, it did work

HOST, PORT = '', 8888

lisSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
lisSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
lisSocket.bind((HOST, PORT))
lisSocket.listen(1)

print('Serving HTTP on port {PORT} ...')

#This function is Created only for the use of threading 
def thread(cliConnect):

    #This request the data from the client connection and then decodes so that it is readable to us
    reqData = cliConnect.recv(1024).decode(('utf-8'))
    print(reqData)

    #This here is just a basic responce 
    http_response = b"HTTP/1.1 200 OK \r\n\r\nYour done"
    
    fileName = ""

    #Sometimes its returns something empty im guessing, put it here just in case
    if len(reqData) > 1:
        fileName = reqData.split(" ")[1]   #Gets the name of the file
        fileName = fileName.split("/")[1]       #parse it so we only get the name with out /
    conType = reqData.split(".")[1]        #Gets the type of the file
    header = b""
    conTypeName = b""
    content = b""

    print("This is the file " + fileName)
    #print(data)
    #Checks if the path exsist and if there is a file run it and do 200
    if os.path.exists(fileName):
        with open(fileName,"rb") as file:
            content = file.read()
            header = b"HTTP/1.1 200 OK"
            if conType == "hdml":
                conTypeName = b"Content Type: text/html"
            if conType == "jpg":
                conTypeName = b"Content Type: image/jpeg"
            
            http_response = header + conTypeName + b"\n\n" + content
    #Checks if the search is page1.html and if it is switch to page2.html and sends the location        
    elif fileName == "page1.html":
        print("going to page 2")
        fileName = "page2.html"
        #This header recalls it on page 2 
        header = b"HTTP/1.1 301 Moved Permanently \r\nLocation: /page2.html"
        http_response = header

    #Didnt understand what this was so just tried to get rid of it
    elif fileName == "favicon.ico":
        print("Do nothing")
    #If nothing else worked then it's probably didnt find the file so do the error code 404
    else: 
        print("This file is not found ")
        header = b"HTTP/1.1 404 Not Found"
        http_response = header + conTypeName + b"\n\n" + content

    cliConnect.sendall(http_response)
    cliConnect.close()

while True:
    cliConnect, client_address = lisSocket.accept()
    #This calls the thread fucntion up top and then does the multitreading to it
    start_new_thread(thread, (cliConnect,))
