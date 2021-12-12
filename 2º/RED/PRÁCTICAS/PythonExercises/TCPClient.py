from socket import *

serverName = 'servername'
serverPort = 12000

# SOCK_STREAM = Socket TCP
clientSocket = socket (AF_INET, SOCK_STREAM)
clientSocket.connect((serverName, serverPort))

sentence = input('Escriba una frase en minúsculas: ')
clientSocket.send(sentence.encode())
modifiedSentence = clientSocket.recv(1024)

print('From Server: ', modifiedSentence.decode())
clientSocket.close()