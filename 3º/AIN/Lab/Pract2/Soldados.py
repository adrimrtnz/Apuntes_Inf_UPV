import json 
import math
import sys
import pygomas
from spade.behaviour import OneShotBehaviour
from spade.template import Template
from spade.message import Message
from agentspeak import Actions
from agentspeak import grounded
from agentspeak.stdlib import actions
from pygomas.map import TerrainMap
from pygomas.bditroop import BDITroop
from pygomas.bdisoldier import BDISoldier
from pygomas.bdimedic import BDIMedic
from pygomas.bdifieldop import BDIFieldOp
from pygomas.ontology import HEALTH


class General(BDITroop):
    def add_custom_actions(self,actions):
        super().add_custom_actions(actions)

        @actions.add_function(".closestFriend",(tuple, tuple, ))
        def _closest_friend(soldP,friends):
            '''
            Devuelve el soldado amigo más cercano, podemos usar esta función
            pasándole una lista de médicos, una lista de fieldops o backups

            Recibe dos parametros:
                soldP: Posicion de la posición del soldado.
                friends: La lista de las posiciones de los soldados amigos que pasemos.
            
            return: La posición del médico más cercano.
            '''
            dist = [] #lista de distancias a cada médico

            #calculamos la distancia Euclidea 
            for pos in friends:
                dist += [math.sqrt(
                        math.pow(pos[0] - soldP[0], 2)
                        + math.pow(pos[2] - soldP[2], 2)
                        )]
                
            #elegimos al médico más cercano
            friend=[]; 
            distS = tuple(sorted(dist))
            if distS:
                friend+= friends[dist.index(distS[0])]
            return tuple(friend)
    

class Tropa(BDITroop):
    def add_custom_actions(self,actions):
        super().add_custom_actions(actions)

        @actions.add_function(".getAttackPosition",(tuple, ))
        def _get_attack_point(myPos, soldiersPos):
            """
            Función para formar a los atacantes y que no vayan 
            todos a lo loco

            Recibe un parámetro:
                - myPos: posición del propio soldado
                - soldiersPor: posición del resto de soldados atacantes

            return: posición a la que dirigirse
            """
            pass