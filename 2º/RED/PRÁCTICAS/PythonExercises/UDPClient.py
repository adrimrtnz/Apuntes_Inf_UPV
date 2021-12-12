from socket import *

serverName = 'hostname'
serverPort = 12000

# AF_NET indica que la red está utilizando IPv4
# SOCK_DGRAM indica que el socket es de tipo UDP
clientSocket = socket(AF_INET, SOCK_DGRAM)

message = input('Escriba una frase in minúsculas:')
clientSocket.sendto(message.encode(), (serverName, serverPort))
modifiedMessage, serverAddres = clientSocket.recvfrom(2048)

print(modifiedMessage.decode())

clientSocket.close()