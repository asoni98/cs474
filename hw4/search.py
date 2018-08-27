import random
import sys
import minimax
import search

from kalah import Kalah
from collections import defaultdict


def depth_limited_search_strategy(depth, h):
    def fxn(pos):
        value, move = depth_limited_search(pos, depth, h)
        return move
    return fxn

def depth_limited_search(pos, depth, h):
     alphabeta(pos, depth, -h.inf, h.inf, h)


# def depth_unlimited_search_strategy(depth, h):
#     def fxn(pos):
#         value, move = depth_unlimited_search(pos, depth, h)
#         return move
#     return fxn


# def depth_unlimited_search(pos, depth, h):
#     alphabeta(pos, depth, depth, -h.inf, h.inf, h)

pTable = {} 

def alphabeta(node, depth, a, B, h):
    if (pos.game_over() or depth == 0):
        return (h.evaluate(pos), None)
    else:
        if pos.next_player() == 0:
            best_value = -h.inf
            best_move = None
            moves = pos.legal_moves()
            for move in moves:
                child = pos.result(move)
                mm, _ = alphabeta(child, depth - 1, a, B, h)#check depthStart
                a = max(a, best_value)

                if mm > best_value:
                    best_value = mm
                    best_move = move

                if B <= a:
                    return (best_value, best_move)

            return (best_value, best_move)
                
        else: 
            best_value = h.inf
            best_move = None
            moves = pos.legal_moves()
            for move in moves:
                child = pos.result(move)
                mm, _ = alphabeta(child, depth - 1, a, B, h)
                B = min(B, mm)

                if mm < best_value:
                    best_value = mm
                    best_move = move

                if B <= a:
                    return (best_value, best_move)

            return (best_value, best_move) 


